### Question

Better performance for the following codes

```cpp
void reset_if_true(void*& ptr, bool cond)
{
    if (cond)
        ptr = nullptr;
}
```

### Answer

```cpp
void reset_if_true(void*& ptr, bool cond)
{
    if (cond)
        ptr = nullptr;
}
```

The naive solution will undoubtedly be the fastest in the majority of cases. Although it has a branch, which can be slow on modern pipelined processors, it is only slow if the branch is mispredicted. Since branch predictors are very good nowadays, unless the value of cond is extremely unpredictable, it's likely that a simple conditional branch is the fastest way to write the code.

And if it is not, a good compiler should know that and be able to optimize the code to something better, considering the target architecture. Which goes to gnasher729's point: just write the code the simple way and leave optimization in the hands of the optimizer.

Such an examination can be quite revealing. For example, let's consider x86-64, where branches can be quite expensive in cases where branch prediction is foiled (which is really the only time when this is an interesting question, so let's assume that cond is completely unpredictable). Almost all compilers are going to generate the following for the naive implementation:

```cpp
reset_if_true(void*&, bool):
    test   sil, sil              ; test 'cond'
    je     CondIsFalse
    mov    QWORD PTR [rdi], 0    ; set 'ptr' to nullptr, and fall through
  CondIsFalse:
    ret
```

This is about as tight of code as you could imagine. But if you put the branch predictor in a pathological case, it might end up being slower than using a conditional move:

```cpp
reset_if_true(void*&, bool):
    xor    eax, eax              ; pre-zero the register RAX
    test   sil, sil              ; test 'cond'
    cmove  rax, QWORD PTR [rdi]  ; if 'cond' is false, set the register RAX to 'ptr'
    mov    QWORD PTR [rdi], rax  ; set 'ptr' to the value in the register RAX
    ret                          ;  (which is either 'ptr' or 0)
```

If you decide that you want to encourage the compiler to generate branchless code because of an unpredictable condition, you might try the following:

```cpp
void reset_if_true_alt(void*& ptr, bool cond)
{
    ptr = (cond) ? nullptr : ptr;
}
```

This succeeds in persuading modern versions of Clang to generate branchless code B, but is a complete pessimization in GCC and MSVC. If you hadn't checked the generated assembly, you wouldn't have known that. If you want to force GCC and MSVC to generate branchless code, you will have to work harder. For example, you might use the variation posted in the question:

```cpp
void reset_if_true(void*& ptr, bool cond)
{
    void* p[] = { ptr, nullptr };
    ptr = p[cond];
}
```

When targeting x86, all compilers generate branchless code for that, but it is not especially pretty code. In fact, none of them generate conditional moves. Instead, you get multiple accesses to memory in order to build the array:

```cpp
reset_if_true_alt(void*&, bool):
    mov     rax, QWORD PTR [rdi]
    movzx   esi, sil
    mov     QWORD PTR [rsp-16], 0
    mov     QWORD PTR [rsp-24], rax
    mov     rax, QWORD PTR [rsp-24+rsi*8]
    mov     QWORD PTR [rdi], rax
    ret
```

### Source

http://stackoverflow.com/questions/37945626/what-is-the-fastest-way-to-update-a-variable-on-a-condition


