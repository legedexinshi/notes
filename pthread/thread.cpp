#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

thread();		
thread( thread&& other ); // ? thread(move(thread)); replace
thread(fun, arg); // not allow for value_copy
// all thread have to be joined

Note: a thread does't have an associated thread after
	* default-constructed   * moved from  * join() already  * detach()

bool joinable();
int get_id();
native_handle   hardware_concurrency  ?
join();
detach(); // permits thread to run independently and free resource when end
swap(t1, t2)  or  t1.swap(t2);

mutex // not copy-assignable
lock() // undefined when lock is called by itself 
bool try_lock() // return if not available
unlock() // undefined when not locked

recursive_mutex // allow one thread to lock many times
timed_mutex :
	try_lock_for(), try_lock_until()
shared_mutex ?
lock_guard ?// own a mutex during its scope
unique_lock ?

condition_variable ();
notify_one(),all();
wait, wait_for, wait_until (mutex &lock) or (mutex &lock, Predicate pred);
