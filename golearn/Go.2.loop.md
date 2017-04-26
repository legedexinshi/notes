####循环
for
	
	sum := 0
	for i := 0; i < 10; i++ {
		sum += i
	}
	
可以省略初始化和后置语句，等同 while

	sum := 1
	for sum < 1000 {
		sum += sum
	}
	
死循环

	for {
	}
	  
if  

	if x < 0 {
	}  
跟 for 一样， if 语句可以在条件之前执行一个简单语句。

	if v := math.Pow(x, n); v < lim {
		return v
	}
if else

	if .. {
	}else {
	}
switch, 除非以 fallthrough 语句结束，否则分支会自动终止。

	switch os := runtime.GOOS; os {
	case "darwin":
		fmt.Println("OS X.")
	case "linux":
		fmt.Println("Linux.")
	default:
		// freebsd, openbsd,
		// plan9, windows...
		fmt.Printf("%s.", os)
	}
	
switch 的条件从上到下的执行，当匹配成功的时候停止。

	switch i {
		case 0:
		case f(): // if i = 0 wont go here
	}

没有条件的 switch 同 switch true 一样。  
这一构造使得可以用更清晰的形式来编写长的 if-then-else 链。  
  
defer 语句会延迟函数的执行直到上层函数返回。  
延迟调用的参数会立刻生成，但是在上层函数返回前函数都不会被调用。  

	defer fmt.Println("world")
	fmt.Println("hello")  

延迟的函数调用被压入一个栈中。当函数返回时， 会按照后进先出的顺序调用被延迟的函数调用。