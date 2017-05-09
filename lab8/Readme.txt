1）按照3.3.2 对thread_huchi.c 的源代码分析，write 线程和read 线程是否应该轮流打印，各线程每次打印
一行，实际运行结果是否是这样，如果不是，请给出分析原因；
运行结果只有write打印语句，write的while循环的sem_post(&sem);语句相当于V操作能释放sem信号量资源从而继续循环

2） 请修改thread_huchi.c, 实现write 线程和read 线程的同步，从而实现轮流打印一行的效果；
删去write中的sem_post(&sem);和read中的sem_wait(&sem);详见代码11410441-sem_huchi.c