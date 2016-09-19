
### Asynchronous IO

**Asynchronous IO** refers to an interface where you supply a callback to an IO operation, which is invoked when the operation completes.
This invocation often happens to an entirely different thread to the one that originally made the request, but this is not necessarily 
the case. Asynchronous IO is a manifestation of the **`"proactor" pattern`**.

One common way to implement asynchronous IO is to have a **thread pool** whose threads are used to make the normal blocking IO requests,
and execute the appropriate _callbacks_ when these return. The less common implementation approach is to avoid a thread pool, and just
push the actual asynchronous operations down into the kernel. This alternative solution obviously has the disadvantage that it depends on
operating system specific support for making async operations

_Linux has at least two implementations of async IO:_

  - POSIX AIO (`aio_read` et al). This is implemented on Linux by glibc, but other POSIX systems (Solaris, OS X etc) have their own 
  implementations. The glibc implementation is simply a thread pool based one — I'm not sure about the other systems.
  - Linux kernel AIO (`io_submit` et al). No thread pool is used here, but it has quite a few limitations (e.g. it only works for files, 
  not sockets, and has alignment restrictions on file reads) and does not seem to be used much in practice.


### Non-blocking IO

**Non-blocking IO** refers to an interface where IO operations will return immediately with a special error code if called when they are 
in a state that would otherwise cause them to block. So for example, a non-blocking `recv` will return immediately with a `EAGAIN` or 
`EWOULDBLOCK` error code if no data is available on the socket, and likewise `send` will return immediately with an error if the OS send 
buffers are full. Generally APIs providing non-blocking IO will also provide some sort of interface where you can efficiently wait for 
certain operations to enter a state where invoking the non-blocking IO operation will actually make some progress rather than 
immediately returning. APIs in this style are implementations of the **`reactor pattern`**.

`select`, `poll` and `epoll`
