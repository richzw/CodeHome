// source: https://go101.org/article/nil.html


- `nil` is a predeclared identifier in Go
- `nil` can reprensent zero values of many types
- predeclared `nil` has not a default type

 ```golang
 	_ = (*struct{})(nil)
	_ = []int(nil)
	_ = map[int]bool(nil)
	_ = chan string(nil)
	_ = (func())(nil)
	_ = interface{}(nil)
 ```
- predeclared `nil` is not keyword in Go

 ```golang
 nil := 123
 fmt.Println(nil)  // 123
 ```

- the size of nil values with types of different kinds may be different

 ```golang
 	var p *struct{} = nil
	fmt.Println( unsafe.Sizeof( p ) ) // 8

	var s []int = nil
	fmt.Println( unsafe.Sizeof( s ) ) // 24

	var m map[int]bool = nil
	fmt.Println( unsafe.Sizeof( m ) ) // 8
 ```

- two nil values of two differnt types may be not compatible

 ```go
 // Compilation failure reason: mismatched types.
 var _ = (*int)(nil) == (*bool)(nil)         // error
 type IntPtr *int
 // The underlying of type IntPtr is *int.
 var _ = IntPtr(nil) == (*int)(nil)
 
 // Every type in Go implements interface{} type.
 var _ = (interface{})(nil) == (*int)(nil)
 
 // Values of a directional channel type can be
 // converted to the bidirectional channel type
 // which has the same element type.
 var _ = (chan int)(nil) == (chan<- int)(nil)
 ```

- Two Nil Values of the Same Type May Be Not Comparable

 ```go
 // map, slice and function types don't support comparison. Comparing two values, including nil values, of an incomparable types is illegal. 
 // The following comparisons fail to compile.
 var _ = ([]int)(nil) == ([]int)(nil)
 var _ = (map[string]int)(nil) == (map[string]int)(nil)
 
 // The following lines compile okay.
 var _ = ([]int)(nil) == nil
 var _ = (map[string]int)(nil) == nil
 var _ = (func())(nil) == nil
 ```

- Two Nil Values May Be Not Equal

```go
fmt.Println( (interface{})(nil) == (*int)(nil) ) // false
```

- Retrieving Elements From Nil Maps Will Not Panic

```go
fmt.Println( (map[string]int)(nil)["key"] ) // 0
fmt.Println( (map[int]bool)(nil)[123] )     // false
fmt.Println( (map[int]*int64)(nil)[123] )   // <nil>
```

- It Is Legal to Range Over Nil Channels, Maps, Slices, and Array Pointers

```go
for range []int(nil) {
	fmt.Println("Hello")
}

for range map[string]string(nil) {
	fmt.Println("world")
}

for i := range (*[5]int)(nil) { // output 1 2 3 4 5
	fmt.Println(i)
}

for range chan bool(nil) { // block here
	fmt.Println("Bye")
}
```

- Invoking Methods Through Non-Interface Nil Receiver Arguments Will Not Panic

```go
type Slice []bool

func (s Slice) Length() int {
	return len(s)
}

func (s Slice) Modify(i int, x bool) {
	s[i] = x // panic if s is nil
}

func (p *Slice) DoNothing() {
}

func (p *Slice) Append(x bool) {
	*p = append(*p, x) // panic if p is nil
}

func main() {
	// The following selectors will not cause panics.
	_ = ((Slice)(nil)).Length
	_ = ((Slice)(nil)).Modify
	_ = ((*Slice)(nil)).DoNothing
	_ = ((*Slice)(nil)).Append

	// The following two lines will also not panic.
	_ = ((Slice)(nil)).Length()
	((*Slice)(nil)).DoNothing()
```

- 


