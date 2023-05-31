#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/time.h>
#include <time.h>
#include "merce.h"

int main (int argc, char * argv[]) {
    int days = atoi(argv[1]);
    int n_navi = atoi(argv[2]);
    int n_porti = atoi(argv[3]);
    int master_msgq = atoi(argv[4]);
    int master_sem_id = atoi(argv[5]);
    int maelstrom_ore = atoi(argv[6]);
    struct mesg_buffer message;
	struct sembuf sops;
    struct timeval tv1, tv2;

	sops.sem_num = 0;
	sops.sem_flg = 0;
	sops.sem_op = -1;
	semop(master_sem_id, &sops, 1);
    tv1.tv_sec = 0;
    tv1.tv_usec = 41666666;

    message.mesg_type = 1;
    nanosleep(&tv1, &tv2);
    for(int i = 1; i < ((days + 1) * 24); i++) {
        nanosleep(&tv1, &tv2);
        if((i % maelstrom_ore) == 0) {
            strcpy(message.mesg_text, "z");
            msgsnd(master_msgq, &message, (sizeof(long) + sizeof(char) * 100), 0);
        }
        if(i % 24 == 0) {
            strcpy(message.mesg_text, "d");
            msgsnd(master_msgq, &message, (sizeof(long) + sizeof(char) * 100), 0);
        }
    }
    strcpy(message.mesg_text, "t");
    msgsnd(master_msgq, &message, (sizeof(long) + sizeof(char) * 100), 0);

    exit(0);
}