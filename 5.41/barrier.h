#define MAX_SLEEP_TIME 		5
#define NUMBER_OF_THREADS	5

void *worker(void *);

int barrier_init(int);

int wait_for_others(void);

