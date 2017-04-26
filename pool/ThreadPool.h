#ifndef _THPOOL_
#define _THPOOL_

#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

typedef void *(*FUNC) (void *arg);

struct Task {
	FUNC fun;
	void* arg;
	Task* next;
	Task (FUNC _fun, void* _arg, Task* _next) {
		fun = _fun; arg = _arg; next = _next;
	}
	Task () {}
	void* Run () {
		return (void *)(*fun) (arg);
	}
};
class ThreadPool {

	int Pool_Life;
	int Max_Thread;
	mutex myMutex;
	condition_variable myCond;
	Task * task_head, * task_tail;
	thread *myThread;

 public:
	ThreadPool ();
	~ThreadPool ();
	void init (int);
	void destroy ();
	void addtask (FUNC, void*);	
	static void *run (void *);

};

#endif
