#include <pthread.h>

int pthread_equal(pthread_t tid1, pthread_t tid2);
pthread_t pthread_self(void);
int pthread_create(pthread_t *restrict tidp, 
					const pthread_attr_t *restrict attr,
					void *(*start_rtn)(void *), void *restrict arg);
					// 0 ok
void pthread_exit(void *rval_ptr);
int pthread_join(pthread_t thread, void **rval_ptr);  // 0 ok
int pthread_cancel(pthread_t tid);
void pthread_cleanup_push(void (*rtn)(void *), void *arg);
void pthread_cleanup_pop(int execute); // run if execute not 0 自然退出不会调用
int pthread_detach(pthread_t tid); // won't be jioned

pthread_mutex_t var = PTHREAD_MUTEX_INITIALIZER;
int pthread_mutex_init(pthread_mutex_t *restrict mutex,
						const pthread_mutexattr_t *restrict attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);// 释放动态互斥前调用

int pthread_mutex_lock,trylock,unlock(pthread_mutex_t *mutex);
// 当2个锁时，需确保上锁顺序确保不会死锁

int pthread_rwlock_init(pthread_rwlock_t *rwlock, 
						const pthread_rwlockattr_t *attr);
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
int pthread_rwlock_rd,wr,un lock(pthread_rwlock_t *rwlock);

pthread_cond_t var = PTHREAD_COND_INITIALIZER;// static
int pthread_cond_init(pthread_cond_t *cond,
						pthread_condattr_t *attr);// dynamic
int pthread_cond_destroy(pthread_cond_t *cond);
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);

int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);

/* while (judge_cond) pthread_cond_wait(&cond, &mutex);
 * in case that thread wake before fun return and unlock but cond change */


int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);

int pthread_attr_getdetachstate(pthread_attr_t *attr, int *detachstate);
int pthread_attr_setdetachstate(pthread_attr_t *attr, int *detachstate);
// PTHREAD_CREATE_DETACHED/JOINABLE
int pthread_attr_getstack/setstack(...) //stackaddr
int pthread_attr_get/set stacksize(...) //stacksize
int pthread_attr_get/set guardsize(...)

int pthread_mutex/rwlock/cond attr_get/set pshared(...);	

pthread_once_t initflag = PTHREAD_ONCE_INIT; // not local
int pthread_once(pthread_once_t *initflag, void (*initfn) (void));

int pthread_key_create(pthread_key_t *keyp, void (*destr) (void *));
// .._create(&key, free);    dif for each thread
int pthread_key_delete(pthread_key_t *key);
void *pthread_getspecific(pthread_key_t key);
int pthread_setspecific(pthread_key_t key, const void *value);

int pthread_setcancelstate(int state, int *oldstate);
// PTHREAD_CANCEL_ENABLE/DISABLE
void pthread_testcancel(void);
int pthread_setcanceltype(int type, int *oldtype);

pread/pwrite replace the lseek read ops;

