###基础
导入包  

	import (
		"fmt"
		"math"
	)
	import "pack"
首字母大写的名称是被导出的

	fmt.Println(math.Pi)
函数

	func add(x int, y int) int {
		return x + y;
	}
	fmt.Println(add(12, 34))  
当两个或多个连续的函数命名参数是同一类型，则除了最后一个类型之外，其他都可以省略。

	x, y int  
函数可以返回多值  

	func swap(x, y string) (string, string) {
		return y, x;
	}
	a, b := swap("aaa", "bbb")
	fmt.Println(a, b)  
裸返回，见下例  
	
	func split(sum int) (x, y int) {
		x = sum * 4 / 9
		y = sum - x
		return
	}
定义变量, 类型可省
  
	var a1, a2, a3 int = 1, 2, 3
短声明变量， 函数中可以:=代替var，注意只能在函数内使用。  

	k := 3
	
基本类型

	string

	int  int8  int16  int32  int64
	uint uint8 uint16 uint32 uint64 uintptr

	byte // uint8 的别名

	rune // int32 的别名
     	// 代表一个Unicode码

	float32 float64

	complex64 complex128
默认值为零值，0，false， “”  
类型转换， 不同类型间赋值需要显示转换。

	var f float64 = float64(i)
	u := uint(f)
类型推导，不显示指明类型的定义由右侧值推导，若为数字常量则取决于精度  
	
	var i int
	j := i // j 也是一个 int
	f := 3.142        // float64
常量，const替代var, 不能用:=定义

	const World = "世界"
	World = "over" // false
数值常量是高精度的值

	const (
		Big   = 1 << 100
		Small = Big >> 99 // 2
	)