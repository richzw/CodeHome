#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int glob = 6;

int
main(void)
{
    int var;
    pid_t pid;
    var = 88;
    printf("before vfork\n");
    if ((pid = vfork()) < 0) {
        printf("vfork error");
        exit(-1);
    } else if (pid == 0) {
        /* 子进程 */
        glob++;
        var++;
        return 0;
        //exit(0);
    }
    printf("pid=%d, glob=%d, var=%d\n", getpid(), glob, var);
    return 0;
    //exit(0);
}

/*
首先说一下fork和vfork的差别：
fork 是 创建一个子进程，并把父进程的内存数据copy到子进程中。
vfork是 创建一个子进程，并和父进程的内存数据share一起用。
这两个的差别是，一个是copy，一个是share。

你 man vfork 一下，你可以看到，vfork是这样的工作的，
1）保证子进程先执行。
2）当子进程调用exit()或exec()后，父进程往下执行。

那么，为什么要干出一个vfork这个玩意？ 原因是这样的—— 起初只有fork，但是很多程序在fork一个子进程后就exec一个外部程序，
于是fork需要copy父进程的数据这个动作就变得毫无意了，而且还很重，所以，搞出了个父子进程共享的vfork。
所以，vfork本就是为了exec而生。

为什么return会挂掉，exit()不会？

所以，结束子进程的调用是exit()而不是return，如果你在vfork中return了，那么，这就意味main()函数return了
，注意因为函数栈父子进程共享，所以整个程序的栈就跪了。


如果你在子进程中return，那么基本是下面的过程：
子进程的main() 函数 return了
而main()函数return后，通常会调用 exit()或相似的函数（如：exitgroup()）
这时，父进程收到子进程exit()，开始从vfork返回，但是尼玛，老子的栈都被你干废掉了，你让我怎么执行？
（注：栈会返回一个诡异一个栈地址，对于某些内核版本的实现，直接报“栈错误”就给跪了，然而，对于某些内核版本的实现，
于是有可能会再次调用main()，于是进入了一个无限循环的结果，直到vfork 调用返回 error）

好了，现在再回到 return 和 exit，return会释放局部变量，并弹栈，回到上级函数执行。exit直接退掉。
如果你用c++ 你就知道，return会调用局部对象的析构函数，exit不会。
（注：exit不是系统调用，是glibc对系统调用 _exit()或_exitgroup()的封装）

可见，子进程调用exit() 没有修改函数栈，所以，父进程得以顺利执行。
*/
