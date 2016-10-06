### Question

I'm trying to call native machine-language code. Here's what I have so far (it gets a bus error):

```c
char prog[] = {'\xc3'}; // x86 ret instruction

int main()
{
    typedef double (*dfunc)();

    dfunc d = (dfunc)(&prog[0]);
    (*d)();
    return 0;
}
```

It does correctly call the function and it gets to the ret instruction. But when it tries to execute the ret instruction, it has a SIGBUS
error. Is it because I'm executing code on a page that is not cleared for execution or something like that?

### Answer

You need to call memprotect in order to make the page where prog lives executable. The following code does make this call,
and can execute the text in prog.

```c
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>

char prog[] = {
   0x55,             // push   %rbp
   0x48, 0x89, 0xe5, // mov    %rsp,%rbp
   0xf2, 0x0f, 0x10, 0x05, 0x00, 0x00, 0x00,
       //movsd  0x0(%rip),%xmm0        # c <x+0xc>
   0x00,
   0x5d,             // pop    %rbp
   0xc3,             // retq
};

int main()
{
    long pagesize = sysconf(_SC_PAGE_SIZE);
    long page_no = (long)prog/pagesize;
    int res = mprotect((void*)(page_no*pagesize), (long)page_no+sizeof(prog), PROT_EXEC|PROT_READ|PROT_WRITE);
    if(res)
    {
        fprintf(stderr, "mprotect error:%d\n", res);
        return 1;
    }
    typedef double (*dfunc)(void);

    dfunc d = (dfunc)(&prog[0]);
    double x = (*d)();
    printf("x=%f\n", x);
    fflush(stdout);
    return 0;
}
```

----------------------------------------------------------

you must ensure prog[] is executable, however the proper way to do it, unless you're writing a JIT compiler, is to put the symbol in an 
executable area, either by using a linker script or by specifying the section in the C code if the compiler allows , e.g.:

`char prog[] __attribute__((section(".text"))) = {...}`


---------------------------------------------------------

As a non-standard extension, you'll have to read your compiler manual and check how to do it, but the GCC "asm" extension is a fairly 
standard approach.

```c
 void DoCheck(uint32_t dwSomeValue)
 {
    uint32_t dwRes;

    // Assumes dwSomeValue is not zero.
    asm ("bsfl %1,%0"
      : "=r" (dwRes)
      : "r" (dwSomeValue)
      : "cc");

    assert(dwRes > 3);
 }
 ```

