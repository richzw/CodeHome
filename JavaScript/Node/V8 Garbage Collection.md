Source: http://jayconrod.com/posts/55/a-tour-of-v8-garbage-collection

-------------------------

V8 heap is divided into several different spaces:

- **New Space**: This space is relatively small and has a size of between 1MB and 8MB. Most of the objects are allocated here.
- **Old Pointer Space**: Has objects which may have pointers to other objects. If object survives long enough in New Space 
it gets promoted to Old Pointer Space.
- **Old Data Space**: Contains only raw data like strings, boxed numbers and arrays of unboxed doubles. 
Objects that have survived GC in the New Space for long enough are moved here as well.
- **Large Object Space**: Objects which are too big to fit in other spaces are created in this space. 
Each object has it’s own mmap‘ed region in memory
- **Code space**: Contains assembly code generated by the JIT compiler.
- **Cell space, property cell space, map space**: This space contains Cells, PropertyCells, and Maps. 
This is used to simplify garbage collection.

Each space is composed of pages. A page is a region of memory allocated from the operating system with mmap. 
Each page is always 1MB in size except for pages in large object space.

V8 has two built in garbage collection mechanisms: **Scavenge**, **Mark-Sweep** and **Mark-Compact**.

**Scavenge** is a very fast garbage collection technique and operates with objects in New Space. 
Scavenge is the implementation of _Cheney’s Algorithm_. The idea is very simple, New Space is divided in two equal semi-spaces: 
To-Space and From-Space. Scavenge GC occurs when To-Space is full. It simply swaps To and From spaces and copy all live objects
to To-Space or promote them to one of the old spaces if they survived two scavenges, and is then entirely erased from the space.
Scavenges are very fast however they have the overhead of keeping double sized heap and constantly copying objects in memory. 
The reason to use scavenges is because most objects die young.

**Mark-Sweep & Mark-Compact** is another type of garbage collector used in V8. The other name is full garbage collector. 
It marks all live nodes, then sweeps all dead nodes and defragments memory.