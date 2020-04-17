type spinLock uint32

func (sl *spinLock) Lock() {
    for !atomic.CompareAndSwapUint32((*uint32)(sl), 0, 1) {
        runtime.Gosched() //without this it locks up on GOMAXPROCS > 1
    }
}

func (sl *spinLock) Unlock() {
    atomic.StoreUint32((*uint32)(sl), 0)
}

func SpinLock() sync.Locker {
    return &spinLock{}
}
