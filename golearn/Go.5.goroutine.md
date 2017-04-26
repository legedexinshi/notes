####goroutine

goroutine 是由 Go 运行时环境管理的轻量级线程。

	go say("world")
	say("hello")
	
channel 是有类型的管道，可以用 channel 操作符 <- 对其发送或者接收值。

	ch := make(chan int)
	ch <- v    // 将 v 送入 channel ch。
	v := <-ch  // 从 ch 接收，并且赋值给 v。
	
默认情况下，在另一端准备好之前，发送和接收都会阻塞。这使得 goroutine 可以在没有明确的锁或竞态变量的情况下进行同步。

channel 可以是 带缓冲的。为 make 提供第二个参数作为缓冲长度来初始化一个缓冲  
向带缓冲的 channel 发送数据的时候，只有在缓冲区满的时候才会阻塞。 而当缓冲区为空的时候接收操作会阻塞。

	ch := make(chan int, 2) // if len = 1, will be block
	ch <- 1
	ch <- 2
	fmt.Println(<-ch)
	fmt.Println(<-ch)
	
当没有值可以接收并且 channel 已经被关闭，那么Ok会被设置为false  
for 循环会不断从channel读出值，直至被关闭

	v, ok := <-ch
	for i := range c {
		fmt.Println(i)
	}

*注意：* 只有发送者才能关闭 channel，而不是接收者。向一个已经关闭的 channel 发送数据会引起 panic。 *还要注意：* channel 与文件不同；通常情况下无需关闭它们。只有在需要告诉接收者没有更多的数据的时候才有必要进行关闭，例如中断一个 range。

select 语句使得一个 goroutine 在多个通讯操作上等待。

select 会阻塞，直到条件分支中的某个可以继续执行，这时就会执行那个条件分支。当多个都准备好的时候，会随机选择一个。

	func fibonacci(c, quit chan int) {
		x, y := 0, 1
		for {
			select {
			case c <- x:
				x, y = y, x+y
			case <-quit:
				fmt.Println("quit")
				return
			}
		}
	}
	func main() {
		c := make(chan int)
		quit := make(chan int)
		go func() {
			for i := 0; i < 10; i++ {
				fmt.Println(<-c)
			}
			quit <- 0
		}()
		fibonacci(c, quit)
	}

当 select 中的其他条件分支都没有准备好的时候，default 分支会被执行。

为了非阻塞的发送或者接收，可使用 default 分支：

可以使用sync.Mutex保证互斥

	var mux sync.Mutex
	mux.Lock()
	[defer] mux.Unlock()
