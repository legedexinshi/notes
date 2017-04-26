#include "ThreadPool.h"

ThreadPool:: ThreadPool () {
	task_head = task_tail = NULL;
	myThread = NULL;
	Max_Thread = Pool_Life = 0;
	if (pthread_mutex_init(&myMutex, NULL) != 0) {
		printf ("init mutex fail\n");
		return ;
	}
	if (pthread_cond_init(&myCond, NULL) != 0) {
		printf ("init cond fail\n");
		return ;
	}
}
ThreadPool:: ~ThreadPool() {
	pthread_mutex_destroy (&myMutex);
	pthread_cond_destroy (&myCond);
}

void ThreadPool::destroy () {
	pthread_mutex_lock (&myMutex);
	if (Pool_Life == 0) {
		printf ("already destroyed\n");
		pthread_mutex_unlock (&myMutex);
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
	pthread_mutex_unlock (&myMutex);

// can't init until destroyed
	pthread_cond_broadcast (&myCond);
	for (int i = 0; i < Max_Thread; i++) 
		pthread_join (myThread[i], NULL);
	delete []myThread;

	printf ("succeed in destroy !\n");
	return;
}
void * ThreadPool::run (void* x) {
	ThreadPool *T = (ThreadPool *)x;
	printf ("thread 0x%lx begins to work\n", (unsigned long)pthread_self());
	
	while (T->Pool_Life != 0) {
		pthread_mutex_lock (&T->myMutex);
		while (T->Pool_Life != 0 && T->task_head == NULL) {
			pthread_cond_wait (&T->myCond, &T->myMutex);
		}
		if (T->Pool_Life == 0) {
			pthread_mutex_unlock (&T->myMutex);
			break;
		}	
		Task* task = T->task_head;
		T->task_head = T->task_head -> next;
		if (task == T->task_tail) T->task_tail = NULL;

		pthread_mutex_unlock (&T->myMutex);
	//	printf ("thread 0x%lx is working\n", (unsigned long)pthread_self());
		task -> Run();
	}
	printf ("thread 0x%lx finish work\n", (unsigned long)pthread_self());
	pthread_exit (NULL);
}

void ThreadPool::init (int Max_Thread) {
	pthread_mutex_lock (&myMutex);
	if (Pool_Life == 1) {
		printf ("already init\n");
		pthread_mutex_unlock (&myMutex);		
		return ;
	}
	Pool_Life = 1;
	this->Max_Thread = Max_Thread;
	task_head = task_tail = NULL;
	myThread = new pthread_t[Max_Thread];
	if (myThread == NULL) {
		printf ("new thread fail\n");
		pthread_mutex_unlock (&myMutex);
		destroy ();		
		return ;
	}
	for (int i = 0; i < Max_Thread; i++) {
		if (pthread_create (&myThread[i], NULL, run, this)) {
			printf ("create thread fail\n");
			pthread_mutex_unlock (&myMutex);
			destroy ();		
			return ;
		}
	}
	sleep(1);
	printf ("succeed in initialaze for %d threads !\n", Max_Thread);
	pthread_mutex_unlock (&myMutex);
}


void ThreadPool::addtask (FUNC fun, void* arg) {
	if (fun == NULL) {
		printf ("invalid function\n");
		return ;
	}
	pthread_mutex_lock(&myMutex);
	if(Pool_Life == 0) {
		printf ("ThreadPool already destroyed\n");
		pthread_mutex_unlock(&myMutex);
		return ;
	}
	Task* newtask = new Task (fun, arg, NULL);
	if (newtask == NULL) {
		printf ("new task fail\n");
		return ;
	}
	if (task_head != NULL) task_tail = task_tail -> next = newtask;
	else task_head = task_tail = newtask;

	pthread_cond_signal(&myCond);
	pthread_mutex_unlock(&myMutex);
}

