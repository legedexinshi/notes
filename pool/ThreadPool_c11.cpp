#include "ThreadPool_c11.h"

ThreadPool:: ThreadPool () {
	myThread = NULL;
	Max_Thread = Pool_Life = 0;
}

ThreadPool:: ~ThreadPool() {
	if (Pool_Life == 0) destroy();
}

void ThreadPool::destroy () {
	unique_lock<mutex> myLock (myMutex);
	if (Pool_Life == 0) {
		printf ("already destroyed\n");
		return ;
	}
	Pool_Life = 0;
	while (taskQ.size()) taskQ.pop();
	myLock.unlock();

// can't init until destroyed
	myCond.notify_all();
	for (int i = 0; i < Max_Thread; i++) 
		myThread[i].join();
	delete []myThread;
	printf ("succeed in destroy !\n");
}

void* ThreadPool::run (void* x) {
	ThreadPool *T = (ThreadPool *)x;
	printf ("thread 0x%x begins to work\n", this_thread::get_id());
	unique_lock<mutex> myLock(T->myMutex, defer_lock);	
	while (T->Pool_Life != 0) {
		myLock.lock();
		T->myCond.wait(myLock, [&]{return (T->Pool_Life == 0 || !T->taskQ.empty());});
		if (T->Pool_Life == 0) {
			break;
		}	
		unique_ptr<Task> task = move(T->taskQ.front());
		T->taskQ.pop();
		myLock.unlock();
		task -> Run();
	}
	printf ("thread 0x%x finish work\n", this_thread::get_id());
}

void ThreadPool::init (int Max_Thread) {
	lock_guard<mutex> myLock (myMutex);
	if (Pool_Life == 1) {
		printf ("already init\n");
		return ;
	}
	Pool_Life = 1;
	this->Max_Thread = Max_Thread;
	try {
		myThread = new thread[Max_Thread];
	}
	catch (bad_alloc&) {
		printf ("new thread fail\n");
		destroy ();		
		return ;
	}
	for (int i = 0; i < Max_Thread; i++) {
		myThread[i] = thread(run, this);
	}
	sleep(1);
	printf ("succeed in initialaze for %d threads !\n", Max_Thread);
}


void ThreadPool::addtask (FUN fun, void* arg) {
	if (fun == NULL) {
		printf ("invalid function\n");
		return ;
	}
	lock_guard<mutex> myLock (myMutex);
	if(Pool_Life == 0) {
		printf ("ThreadPool already destroyed\n");
		return ;
	}
	taskQ.push(unique_ptr<Task> (new Task(fun, arg)));
	myCond.notify_one();
}

