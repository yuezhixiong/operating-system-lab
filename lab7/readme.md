'read.c' and 'write.c' are answer code of the .pdf file which requires read and write process share a part of memory in Linux and communicate via semaphore.

Used fuctions in <sys/types.h><sys/ipc.h><sys/sem.h>:

int semget(key_t key, int nsems, int semflg)

int semctl(int semid, int semnum, int cmd, union semun arg)

int semop(int semid, struct sembuf *sops, unsigned nsops)


//p opt of semaphore

struct sembuf sem_buf_p = {0, -1, SEM_UNDO};

semop(sem_id, &sem_buf_p, 1);


//p opt of semaphore

struct sembuf sem_buf_v = {0, 1, SEM_UNDO};

semop(sem_id, &sem_buf_v, 1);
