package main

import "fmt"

type Vertex struct {
    X int
    Y int
}

func main() {
    fmt.Println(Vertex{1, 2})
}

type List struct {
    length int
    middle *Node
    head *Node
}

type Node struct {
    next *Node
    value string
}

func (self *List) Add(value string) {
    if value == "" {
        return
    } else if self.head == nil {
        self.head = &Node{nil, ""}
        self.middle = self.head
    }
    
    if self.middle.value < value {
        self.AddAfterNode(self.middle, value)
    } else {
        self.AddAfterNode(self.head, value)
    }
}

func (self *List) AddAfterNode(node *Node, value string) {
    current := node
    middleIndex := self.length / 2
    newNode := &Node{nil, value}

    for i := 0; ; i++ {
        if current.next == nil {
            current.next = newNode
            break;
        } else if current.next.value > value {
            newNode.next = current.next
            current.next = newNode
            break
        }

        if (i == middleIndex) {
            self.middle = current
        }

        current = current.next
    }

    self.length++ 
}

func (self *List) ToSlice() (result []string) {
    result = make([]string, self.length)

    if self.length == 0 {
        return
    }

    i := 0
    for current := self.head.next; current != nil; current = current.next {
        result[i] = current.value
        i++
    }

    return 
}

func SortSlice(strings []string, out chan<- []string) {
    sorted := &List{}

    for _, value := range strings {
        sorted.Add(value)
    }

    out <- sorted.ToSlice()
}

func JoinSortedSlices(sliceA, sliceB []string, out chan<- []string) {
    sorted := make([]string, len(sliceA) + len(sliceB))
    sliceAPos := 0
    sliceBPos := 0

    for i := 0; i < len(sorted); i++ {
        if sliceAPos >= len(sliceA) {
            sorted[i] = sliceB[sliceBPos]
            sliceBPos++
        } else if sliceBPos >= len(sliceB) {
            sorted[i] = sliceA[sliceAPos]
            sliceAPos++
        } else if sliceA[sliceAPos] < sliceB[sliceBPos] {
            sorted[i] = sliceA[sliceAPos]
            sliceAPos++
        } else {
            sorted[i] = sliceB[sliceBPos]
            sliceBPos++
        }
    }

    out <- sorted
}
