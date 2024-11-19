#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include<string.h>

int main(int argc, char *argv[]) {
//    char web[512],*ptr, *args[32];
	int ret, err, s;
//	printf("Enter the website: ");
//	gets(web);
//	i=0;
//	ptr = strtok();
    ret = fork();
    if(ret == 0) { // child proecss
        // load new program and execute it
        err = execl("/usr/bin/firefox", "firefox", "http://sunbeaminfo.in", NULL);
        if(err < 0) {
            perror("exec() failed");
            _exit(1);
        }
    }
    else { // parent process
        // waits for child to complete
    //    waitpid(ret, &s, 0);
      //  printf("child exit status: %d\n", WEXITSTATUS(s));
    }
  //  printf("parent finished!\n");
    return 0;
}
