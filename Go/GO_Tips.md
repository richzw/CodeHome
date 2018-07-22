
https://i6448038.github.io/2017/07/28/GolangDetails/

https://i6448038.github.io/2017/10/06/GolangDetailsTwo/

https://go101.org/article/container.html#iteration


```
package main
import (
    "fmt"
)
type test struct {
    name string
}
func (t *test) getName(){
    fmt.Println("hello world")
}
func main() {
    var t *test
    t = nil
    t.getName()
}
```

```
用for range来遍历数组或者map的时候，被遍历的指针是不变的，每次遍历仅执行struct值的拷贝
import "fmt"
type student struct{
    Name string
    Age  int
}
func main(){
    var stus []student
    stus = []student{
        {Name:"one", Age: 18},
        {Name:"two", Age: 19},
    }
    data := make(map[int]*student)
    for i, v := range stus{
        data[i] = &v   //应该改为：data[i] = &stus[i]
    }
    for i, v := range data{
        fmt.Printf("key=%d, value=%v \n", i,v)
    }
}
```

```
func main(){
    a := 1
    defer print(function(a))
    a = 2;
}
func function(num int) int{
    return num
}
func print(num int){
    fmt.Println(num)
}
```

