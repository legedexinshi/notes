###GCD
####总结
1. 向队列添加任务是线程安全的，意味着添加前不必先加锁。
2. 别在当前任务中使用 dispatch_sync添加到当前队列，建议使用async
3. 最好别用锁，等待锁的时候会导致其他任务无法被执行，建议使用串行队列
4. 最好别再任务中使用线程。

####并发队列
一次执行多个任务，数量依据情况而定。默认有一个并发队列。
	
	dispatch_queue_t aQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);

可以指定队列优先级DISPATCH_QUEUE_PRIORITY_HIGH and DISPATCH_QUEUE_PRIORITY_LOW，高优先级>默认>低优先级。

####串行队列
FIFO，一次执行一个任务，需自行创建，常用来解决资源竞争。

	dispatch_queue_t queue;
	queue = dispatch_queue_create("com.example.MyQueue", NULL);

传入队列名和属性。

####获得队列
1.  dispatch_get_current_queue。在代码块里调用获得执行队列，代码块外获取全局默认并发队列。
2.  dispatch_get_main_queue。获取分配给主线程的串行队列。

####释放队列
可以通过  dispatch_retain,  dispatch_release改变队列引用。
当队列引用计数为0时，被释放。  
可以注册析构函数。

	void myFinalizerFunction(void *context)
	{
    	MyDataContext* theData = (MyDataContext*)context;
 
	    // Clean up the contents of the structure
    	myCleanUpDataContextFunction(theData);
 
    	// Now release the structure itself.
    	free(theData);
	}
 
	dispatch_queue_t createMyQueue()
	{
    	MyDataContext*  data = (MyDataContext*) malloc(sizeof(MyDataContext));
    	myInitializeDataContextFunction(data);
 
    	// Create the queue and set the context data.
    	dispatch_queue_t serialQueue = dispatch_queue_create("com.example.CriticalTaskQueue", NULL);
    	if (serialQueue)
    	{
    	    dispatch_set_context(serialQueue, data);
    	    dispatch_set_finalizer_f(serialQueue, &myFinalizerFunction);
    	}
 
    	return serialQueue;
	}
	
####添加任务
异步: dispatch_async, dispatch_async_f  
同步: dispatch_sync, dispatch_sync_f 注意别把任务添加到当前串行队列中  

	dispatch_queue_t myCustomQueue;
	myCustomQueue = dispatch_queue_create("com.example.MyCustomQueue", NULL);
 
	dispatch_async(myCustomQueue, ^{
	    printf("Do some work here.\n");
	});
 
	printf("The first block may or may not have run.\n");
 
	dispatch_sync(myCustomQueue, ^{
	    printf("Do some more work here.\n");
	});
	printf("Both blocks have completed.\n");
	
####任务回调
异步任务一旦提交便无法掌控，可以通过在完成时调用回调来通知线程。  
见下例，建议先retain队列防止过早释放，最后release。

	void average_async(int *data, size_t len,
	   dispatch_queue_t queue, void (^block)(int))
	{
	   // Retain the queue provided by the user to make
	   // sure it does not disappear before the completion
	   // block can be called.
	   dispatch_retain(queue);
	   // Do the work on the default concurrent queue and then
	   // call the user-provided block with the results.
   	
		dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
      	int avg = average(data, len);
      	dispatch_async(queue, ^{ block(avg);});
 
      	// Release the user-provided queue when done
      	dispatch_release(queue);
    	});
    }

####并发for循环
	dispatch_queue_t queue = 	dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
 
	dispatch_apply(count, queue, ^(size_t i) {
		printf("%u\n",i);
	});

其中count是循环次数，i从0到count-1。  
注意如果每次循环操作少，并发反而会降低性能，可以通过跨步法改善。

####暂停恢复队列
可以通过dispatch_suspend暂停队列， dispatch_resume恢复队列，通过计数为0判断是否暂停。

####信号量


	// Create the semaphore, specifying the initial pool size
	dispatch_semaphore_t fd_sema = dispatch_semaphore_create(getdtablesize() / 2);
 
	// Wait for a free file descriptor
	dispatch_semaphore_wait(fd_sema, DISPATCH_TIME_FOREVER);
	fd = open("/etc/services", O_RDONLY);
 
	// Release the file descriptor when done
	close(fd);
	dispatch_semaphore_signal(fd_sema);
上例限制了同时打开fd最大数量。  
####任务组
将任务加入任务组，可以等待所有任务结束，类似join一组thread。

	dispatch_queue_t queue = 	dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
	dispatch_group_t group = dispatch_group_create();
 
	// Add a task to the group
	dispatch_group_async(group, queue, ^{
	   // Some asynchronous work
	});
 
	// Do some other work while the tasks execute.
 
	// When you cannot make any more forward progress,
	// wait on the group to block the current thread.
	dispatch_group_wait(group, DISPATCH_TIME_FOREVER);
 
	// Release the group when it is no longer needed.
	dispatch_release(group);
