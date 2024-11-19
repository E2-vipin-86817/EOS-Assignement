#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int ret, arr[2], s;
    int buf1[32], buf2[32];
	printf("Child: Enter the 2 numbers: ");
	scanf("%d%d",&buf1[0],&buf1[1]);
    ret = pipe(arr);
    if(ret < 0) {
        _exit(1);
        perror("pipe() failed");
    }
    ret = fork();
    if(ret == 0) { // child process -- writer
        close(arr[0]); // close read pipe fd
        write(arr[1], buf1[0], sizeof(buf1));
        write(arr[1], buf1[1], sizeof(buf1));
        printf("child: written to pipe: buf1[0]=%d,buf[1]=%d\n", buf1[0],buf1[1]);
        close(arr[1]); // close write pipe fd
    }
    else { // parent process -- reader
        close(arr[1]); // close write pipe fd
        read(arr[0], buf2[0], sizeof(buf2));
        read(arr[0], buf2[1], sizeof(buf2));
        printf("parent: read from pipe:buf2[0]=%d buf2[1]=%d\n", buf2[0], buf2[1]);
		buf2[2]=buf2[0]+buf2[1];
        printf("parent: read from pipe: %d \n",buf2[2]);
        waitpid(ret, &s, 0);
        close(arr[0]); // close read pipe fd
    }
    return 0;
}
