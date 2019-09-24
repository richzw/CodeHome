type Promise struct {
    wg  sync.WaitGroup
    res string
    err error
}

func NewPromise(f func() (string, error)) *Promise {
    p := &Promise{}
    p.wg.Add(1)
    go func() {
        p.res, p.err = f()
        p.wg.Done()
    }()
    return p
}

func (p *Promise) Then(r func(string), e func(error)) {
    go func() {
        p.wg.Wait()
        if p.err != nil {
            e(p.err)
            return
        }
        r(p.res)
    }()
}


// Channel example ...
type Comp struct {
    value interface{}
    ok    bool
}

type Future chan Comp

func future(f func() (interface{}, bool)) Future {
    future := make(chan Comp)

    go func() {
        v, o := f()
        c := Comp{v, o}
        for {
            future <- c
        }
    }()

    return future
}


type Promise struct {
    lock chan int
    ft   Future
    full bool
}

func promise() Promise {
    return Promise{make(chan int, 1), make(chan Comp), false}
}

func (pr Promise) future() Future {
    return pr.ft
}
