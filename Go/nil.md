
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

- 


