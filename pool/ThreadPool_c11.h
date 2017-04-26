#ifndef _THPOOL_
#define _THPOOL_

#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <queue>
#include <functional>

using namespace std;

typedef function <void *(void *)> FUN;

struct Task {
	FUN fun;
	void* arg;
	Task (FUN  _fun, void* _arg): fun(_fun), arg(_arg) {}
	Task () {}
	void* Run () {
		return (void *)fun (arg);
	}
};
class ThreadPool {

	int Pool_Life;
	int Max_Thread;
	mutex myMutex;
	condition_variable myCond;
	queue <unique_ptr<Task>> taskQ;
	thread *myThread;

 public:
	ThreadPool ();
	~ThreadPool ();
	void init (int);
	void destroy ();
	void addtask (FUN, void*);	
	static void *run (void *);

};

#endif
