#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <signal.h>
#include <string.h>

#define SEM_KEY     0x4321

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

void sigchld_handler(int sig) {
    int s;
    waitpid(-1, &s, 0);
}

int main() {
    int i, ret, semid;
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sigchld_handler;
    ret = sigaction(SIGCHLD, &sa, NULL);

    // create a semaphore with two counter
    semid = semget(SEM_KEY, 2, IPC_CREAT|0600);
	
    //union semun su1,su2;
	unsigned short init_cntrs[] = {0,1}; 
	union semun su;
	su.array = init_cntrs;
	ret = semctl(semid, 0, SETALL, su);
   
    struct sembuf ops[2];
    ret = fork();
	
    if(ret == 0) {// child process -- print SUNBEAM
	
        char *str = "SUNBEAM\n";
        while(1){
        //p(s2)
        ops[0].sem_num = 1;
        ops[0].sem_op = -1;
        ops[0].sem_flg = 0;
        ret = semop(semid, ops, 1);
        for(i=0; str[i]!='\0'; i++) {
            write(1, &str[i], 1); // print 1 char to stdout
            sleep(1);
        }
        // V(s1);
        ops[0].sem_num = 0;
        ops[0].sem_op = +1;
        ops[0].sem_flg = 0;
        ret = semop(semid, ops, 1);
        // ...
//        _exit(0);
    }
	}
	
    else {// parent process -- print INFOTECH
	while(1){
        
        // P(s1);
        ops[0].sem_num = 0;
        ops[0].sem_op = -1;
        ops[0].sem_flg = 0;
        ret = semop(semid, ops, 1);
	char *str = "INFOTECH\n";
        for(i=0; str[i]!='\0'; i++) {
            write(1, &str[i], 1); // print 1 char to stdout
            sleep(1);
        }
		//v(s2)
        ops[0].sem_num = 1;
        ops[0].sem_op = +1;
        ops[0].sem_flg = 0;
        ret = semop(semid, ops, 1);
        // ...

        // destroy semaphore
       // semctl(semid, 0, IPC_RMID);
    }
	}
    return 0;
}
