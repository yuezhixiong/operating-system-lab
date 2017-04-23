#include <pthread.h>

#define PID_MIN  	300
#define PID_MAX 	350

/* mutex lock for accessing pid_map */
pthread_mutex_t mutex;

int pid_map[PID_MAX+1];

int last;	// last pid in use
