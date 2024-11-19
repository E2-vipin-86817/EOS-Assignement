#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int ret, arr[2], s,count=0;
    char buf1[4096] = "a",buf2[4096];
    ret = pipe(arr);
	
    if(ret < 0) {
        _exit(1);
        perror("pipe() failed");
    }
    ret = fork();
    if(ret == 0) { // child process -- writer
        close(arr[0]); // close read pipe fd
		while(1){
		write(arr[1],buf1,sizeof(buf1));
		count++;
		}
		printf("child:count=%d\n",count);
		close(arr[1]);
    }
    else { // parent process -- reader
        close(arr[1]); // close write pipe fd
        read(arr[0], buf2, sizeof(buf2));
        printf("parent: read from pipe: %s\n", buf2);
        waitpid(ret, &s, 0);
        close(arr[0]); // close read pipe fd
    }
    return 0;
    return 0;
}
