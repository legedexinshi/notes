####指针,数组，闭包

类型 *T 是指向类型 T 的值的指针。其零值是 nil 。

	var p *int
	i := 42
	p = &i
	*p = 21  
	
与 C 不同，Go 没有指针运算。  
  
一个结构体（ struct ）就是一个字段的集合。    
结构体指针访问也用dot
  
	type Vertex struct {
		X int
		Y int
	}
	v := Vertex{1, 2}
	v.X = 4
	p := &v
	p.x = 1e9

结构体文法表示通过结构体字段的值作为列表来新分配一个结构体。

	var (
		v1 = Vertex{1, 2}  // 类型为 Vertex
		v2 = Vertex{Y: 1}  // X:0 被省略
		v3 = Vertex{}      // X:0 和 Y:0
		p  = &Vertex{1, 2} // 类型为 *Vertex
	)
	
类型 [n]T 是一个有 n 个类型为 T 的值的数组。

	var a [10]int
	a[0] = "Hello"
	
一个 slice 会指向一个序列的值，并且包含了长度信息。  
[]T 是一个元素类型为 T 的 slice。  
len(s) 返回 slice s 的长度。

	s := []int{2, 3, 5, 7, 11, 13}
	fmt.Println("s ==", s)  

slice 可以包含任意的类型，包括另一个 slice。  

	game := [][]string{
		[]string{"_", "_", "_"},
		[]string{"_", "_", "_"},
		[]string{"_", "_", "_"},
	}  

slice 可以重新切片，创建一个新的 slice 值指向相同的数组。  

	s[lo:hi]  

区间左闭右开，lo省略为0，hi省略为len()  

slice 由函数 make 创建。这会分配一个全是零值的数组并且返回一个 slice 指向这个数组

	a := make([]int, 5, 10)  // len(a)=5 cap(a)=10
	
slice 的零值是 nil 。  
一个 nil 的 slice 的长度和容量是 0。  
  
向 slice 的末尾添加元素是一种常见的操作，因此 Go 提供了一个内建函数 append 。   
如果 s 的底层数组太小，而不能容纳所有值时，会分配一个更大的数组。 返回的 slice 会指向这个新分配的数组。

	func append(s []T, vs ...T) []T  

当使用 for 循环遍历一个 slice 时，每次迭代 range 将返回两个值。 第一个是当前下标（序号），第二个是该下标所对应元素的一个拷贝。

	for i, v := range pow {
		fmt.Printf("2**%d = %d\n", i, v)
	}
	
可以通过赋值给 _ 来忽略序号和值  
如果只需要索引值，去掉 “ , value ” 的部分即可。

	for _, value := range pow 
	for key[,_] := range pow 
	  
map 在使用之前必须用 make 来创建；值为 nil 的 map 是空的，并且不能对其赋值。

	type Vertex struct {
		Lat, Long float64
	}
	var m map[string]Vertex

	func main() {
		m = make(map[string]Vertex)
		m["Bell Labs"] = Vertex{
			40.68433, -74.39967,
		}
		fmt.Println(m["Bell Labs"])
	}  

map 的文法跟结构体文法相似，不过必须有键名。

	var m = map[string]Vertex{
		"Bell Labs": Vertex{
			40.68433, -74.39967,
		},
		"Google": Vertex{
			37.42202, -122.08408,
		},
	}

若顶级类型只是一个类型名，你可以在文法的元素中省略它。  

通过双赋值检测某个键存在 elem, ok = m[key]  

	m := make(map[string]int)

	m["Answer"] = 42
	fmt.Println("The value:", m["Answer"])

	m["Answer"] = 48
	fmt.Println("The value:", m["Answer"])

	delete(m, "Answer")
	fmt.Println("The value:", m["Answer"])

	v, ok := m["Answer"]
	fmt.Println("The value:", v, "Present?", ok)
  
函数也是值。他们可以像其他值一样传递，比如，函数值可以作为函数的参数或者返回值。

	var hypot func(float64, float64) float64 
	= func(x, y float64) float64 {
		return math.Sqrt(x*x + y*y)
	}  

Go 函数可以是一个闭包。闭包是一个函数值，它引用了函数体之外的变量。 这个函数可以对这个引用的变量进行访问和赋值；换句话说这个函数被“绑定”在这个变量上。

例如，函数 adder 返回一个闭包。每个返回的闭包都被绑定到其各自的 sum 变量上

	func adder() func(int) int {
		sum := 0
		return func(x int) int {
			sum += x
			return sum
		}
	}

	func main() {
		pos, neg := adder(), adder()
		for i := 0; i < 10; i++ {
			fmt.Println(
				pos(i),
				neg(-2*i),
			)
		}
	}


	