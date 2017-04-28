#ifndef __MSG_H__
#define __MSG_H__

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_SIZE  100

struct msgbuf {
      long mtype;       /* message type, must be > 0 */
      char mtext[MSG_SIZE];    /* message data */
};

#endif
