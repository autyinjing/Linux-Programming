/*
 * =====================================================================================
 *
 *       Filename:  ipc_private.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月20日 12时28分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>

union semun
{
        int val;
        struct semid_ds *buf;
        unsigned short int *array;
        struct seminfo *__buf;
};

/* op为-1时执行P操作，op为1时执行V操作 */
void pv(int sem_id, int op)
{
        struct sembuf sem_b;
        sem_b.sem_num = 0;
        sem_b.sem_op = op;
        sem_b.sem_flg = SEM_UNDO;
        semop(sem_id, &sem_b, 1);
}

int main(int argc, char *argv[])
{
	int sem_id = semget(IPC_PRIVATE, 1, 0666);

        union semun sem_un;
        sem_un.val = 1;
        semctl(sem_id, 0, SETVAL, sem_un);

        pid_t pid = fork();
        if (pid < 0) {
                return 1;
        } else if (pid == 0) {
                printf("Child try to get binary sem\n");
                pv(sem_id, -1);
                printf("Child get the sem and would release it after 5 seconds\n");
                sleep(5);
                pv(sem_id, 1);
                exit(0);
        } else {
                printf("Parent try to get binary sem\n");
                pv(sem_id, -1);
                printf("Parent get the sem and would release it after 5 seconds\n");
                sleep(5);
                pv(sem_id, 1);
        }

        waitpid(pid, NULL, 0);
        semctl(sem_id, 0, IPC_RMID, sem_un);

	return EXIT_SUCCESS;
}

