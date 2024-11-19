#include<stdio.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd , ret;
	int buf1[100];
	fd = open("/tmp/myfifo",O_WRONLY);
	if(fd < 0)
	{
		perror("open() Failed\n");
		_exit(1);
	}
	printf("Enter the 2 numbers: ");
	scanf("%d%d",&buf1[0],&buf1[1]);
	ret = write(fd, buf1, sizeof(buf1));
	
	fd = open("/tmp/myfifo",O_RDONLY);
	if(fd < 0)
	{
		perror("open() Failed\n");
		_exit(1);
	}
	ret = read(fd,buf1,sizeof(buf1));
	printf("p1: Addition = %d",buf1[2]);
	close(fd);
	
	return 0;
}

