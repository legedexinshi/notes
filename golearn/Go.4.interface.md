####方法
Go 没有类。然而，仍然可以在结构体类型上定义方法。

方法接收者 出现在 func 关键字和方法名之间的参数中。  

	type Vertex struct {
		X, Y float64
	}

	func (v *Vertex) Abs() float64 {
		return math.Sqrt(v.X*v.X + v.Y*v.Y)
	}

	func main() {
		v := &Vertex{3, 4}
		fmt.Println(v.Abs())
	}  
  
你可以对包中的 任意 类型定义任意方法，而不仅仅是针对结构体。
但是，不能对来自其他包的类型或基础类型定义方法。

	type MyFloat float64

	func (f MyFloat) Abs() float64 {
		if f < 0 {
			return float64(-f)
		}
		return float64(f)
	}
  
方法可以与命名类型或命名类型的指针关联。  
若使用指针接收，可避免方法调用中拷贝值，也可以修改接收者指向的值  

	func (v ＊Vertex) Scale(f float64) // change value *v
	func (v Vertex) Scale(f float64)
	
接口类型是由一组方法定义的集合。  
接口类型的值可以存放实现这些方法的任何值。    

	type Abser interface {
		Abs() float64
	}
	func (v *Vertex) Abs() float64 {
		return math.Sqrt(v.X*v.X + v.Y*v.Y)
	}
	var a Abser
	a = &Vertex{3, 4}
	a = Vertex{3, 4} // false
	
Stringer 是一个可以用字符串描述自己的类型。`fmt`包 （还有许多其他包）使用这个来进行输出。
	
	func (p Person) String() string {
		return fmt.Sprintf("%v (%v years)", p.Name, p.Age)
	}
	a := Person{"Arthur Dent", 42}
	z := Person{"Zaphod Beeblebrox", 9001}
	fmt.Println(a, z)  

与 fmt.Stringer 类似， error 类型是一个内建接口：  
fmt 包在输出时也会试图匹配 error  

	type error interface {
    	Error() string
	}
	i, err := strconv.Atoi("42")
	if err != nil {
	}
	
io 包指定了 io.Reader 接口， 它表示从数据流结尾读取。

	func (T) Read(b []byte) (n int, err error)
	
练习: io.Reader 封装

	type rot13Reader struct {
		r io.Reader
	}

	func (a rot13Reader) Read(b []byte) (int, error) {
		x, y := a.r.Read(b)
		for z := 0; z < x; z++ {
			if b[z] < 'a' + 13 {
				b[z] += 13
			} else {
				b[z] -= 13
			}
		}
		return x, y
	}
	
image , net ....I

