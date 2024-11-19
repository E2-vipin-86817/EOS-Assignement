#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char cmd[512], *ptr, *args[32];
	int i, ret, err;
	struct sigaction sa;
    sigset_t s;
	sigemptyset(&s);
	sigaddset(&s, SIGINT);
	ret = sigprocmask(SIG_SETMASK,&s,NULL);
	if(ret < 0)
	{
		perror("Sigprocmask() failed");
		_exit(1);
	}
    while(1) {
        // input a command string from user, split it into multiple tokens using strtok() and
        // store their addresses into array of char*.
        // e.g. "ls -l -a /home" --> "ls", "-l", "-a", "/home" --> [ad1, ad2, ad3, ad4, NULL]
        printf("cmd> ");
        gets(cmd);
        i = 0;
        ptr = strtok(cmd, " ");
        args[i] = ptr;  i++;
        do {
            ptr = strtok(NULL, " ");
            args[i] = ptr;  i++;
        } while(ptr != NULL);
        //for(i=0; args[i]!=NULL; i++)
        //    printf("token %d : %s\n", i, args[i]);

        // implement logic for internal commands
        if(strcmp(args[0], "exit") == 0)
            _exit(0);
        else if(strcmp(args[0], "cd") == 0)
            chdir(args[1]);
        else {
            // fork() + execvp() to execute the external command with args and call wait() to avoid zombie
            ret = fork();
            if(ret == 0) {
                err = execvp(args[0], args);
                if(err < 0) {
                    perror("exec() failed");
                    _exit(1);
                }
            }
            else
                waitpid(-1, &s, 0);
        }
    }
    return 0;
}

