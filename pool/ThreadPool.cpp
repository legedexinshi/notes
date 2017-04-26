#include "ThreadPool.h"

ThreadPool:: ThreadPool () {
	task_head = task_tail = NULL;
	myThread = NULL;
	Max_Thread = Pool_Life = 0;
}
ThreadPool:: ~ThreadPool() {
}

void ThreadPool::destroy () {
	myMutex.lock();
	if (Pool_Life == 0) {
		printf ("already destroyed\n");
		myMutex.unlock();
		return ;
	}
	Pool_Life = 0;
	Task* task = task_head;
	while (task != NULL) {
		task = task->next;
		delete task_head;
		task_head = task;
	}
	task_tail = NULL;
	myMutex.unlock();

// can't init until destroyed
	myCond.notify_all();
	for (int i = 0; i < Max_Thread; i++) 
		myThread[i].join();
	delete []myThread;

	printf ("succeed in destroy !\n");
	return;
}
void * ThreadPool::run (void* x) {
	ThreadPool *T = (ThreadPool *)x;
	printf ("thread 0x%lx begins to work\n", (unsigned long)pthread_self());

	unique_lock<mutex> myLock(T->myMutex, defer_lock);	

	while (T->Pool_Life != 0) {
		myLock.lock();
		while (T->Pool_Life != 0 && T->task_head == NULL) {
			T->myCond.wait(myLock);
		}
		if (T->Pool_Life == 0) {
			myLock.unlock();
			break;
		}	
		Task* task = T->task_head;
		T->task_head = T->task_head -> next;
		if (task == T->task_tail) T->task_tail = NULL;

		myLock.unlock();
	//	printf ("thread 0x%lx is working\n", (unsigned long)pthread_self());
		task -> Run();
	}
	printf ("thread 0x%lx finish work\n", (unsigned long)pthread_self());
	pthread_exit (NULL);
}

void ThreadPool::init (int Max_Thread) {
	myMutex.lock();
	if (Pool_Life == 1) {
		printf ("already init\n");
		myMutex.unlock();
		return ;
	}
	Pool_Life = 1;
	this->Max_Thread = Max_Thread;
	task_head = task_tail = NULL;
	myThread = new thread[Max_Thread];
	if (myThread == NULL) {
		printf ("new thread fail\n");
		myMutex.unlock();
		destroy ();		
		return ;
	}
	for (int i = 0; i < Max_Thread; i++) {
		myThread[i] = thread(run, this);
	}
	sleep(1);
	printf ("succeed in initialaze for %d threads !\n", Max_Thread);
	myMutex.unlock();
}


void ThreadPool::addtask (FUNC fun, void* arg) {
	if (fun == NULL) {
		printf ("invalid function\n");
		return ;
	}
	myMutex.lock();
	if(Pool_Life == 0) {
		printf ("ThreadPool already destroyed\n");
		myMutex.unlock();
		return ;
	}
	Task* newtask = new Task (fun, arg, NULL);
	if (newtask == NULL) {
		printf ("new task fail\n");
		myMutex.unlock();
		return ;
	}
	if (task_head != NULL) task_tail = task_tail -> next = newtask;
	else task_head = task_tail = newtask;

	myCond.notify_one();
	myMutex.unlock();
}

