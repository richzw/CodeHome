//http://code.woboq.org/userspace/glibc/malloc/malloc.c.html


1. An allocated chunk looks like this:
========

    chunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Size of previous chunk, if allocated            | |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Size of chunk, in bytes                       |M|P|
      mem-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             User data starts here...                          .
            .                                                               .
            .             (malloc_usable_size() bytes)                      .
            .                                                               |
    next-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Size of chunk                                     |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+  

2. Free chunks are stored in circular doubly-linked lists, and look like this:
========
    chunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Size of previous chunk                            |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    `head:' |             Size of chunk, in bytes                         |P|
      mem-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Forward pointer to next chunk in list             |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Back pointer to previous chunk in list            |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |             Unused space (may be 0 bytes long)                .
            .                                                               .
            .                                                               |
    next-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    `foot:' |             Size of chunk, in bytes                           |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 

why free can not be called twice?
======
You are not allowed to call free on unallocated memory, the standard states that quite clearly:

    The free function causes the space pointed to by its argument to be deallocated, that is, made available for further
    allocation. If the argument is a null pointer, no action occurs. Otherwise, if the argument does not match a pointer
    earlier returned by a memory management function, or if the space has been deallocated by a call to free or realloc,
    the behavior is undefined (slightly paraphrased, my emphasis).

What happens, for example, if the address you're double-freeing has been reallocated in the middle of a new block and the code that allocated it just happened to store something there that looked like a real malloc-block header? Like:

     +- New pointer    +- Old pointer
     v                 v
    +------------------------------------+
    |                  <Dodgy bit>       |
    +------------------------------------+

Chaos, that's what.

Memory allocation functions are a tool just like a chainsaw and, provided you use them correctly, you should have no problems. If you misuse them, however, the consequences are your own fault, either corrupting memory or worse, or cutting off one of your arms :-)

**[pointer validity](http://stackoverflow.com/questions/551069/testing-pointers-for-validity-c-c)**
