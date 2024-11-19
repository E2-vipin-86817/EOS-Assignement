#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
	int fd,ret;
	int buf2[100];
	fd = open("/tmp/myfifo",O_RDONLY);
	if(fd < 0)
	{
		perror("open() failed");		
		_exit(1);
	}
	printf("p2: Waiting for message..\n");
	ret = read(fd,buf2,sizeof(buf2));
	printf("p2: message received:buf[0]=%d , buf2[1]=%d",buf2[0],buf2[1]);
	buf2[2]=buf2[0]+buf2[1];
	fd = open("/tmp/myfifo",O_WRONLY);
		if(fd < 0)
	{
		perror("open() failed");		
		_exit(1);
	}
	ret = write(fd, buf2, sizeof(buf2));
	return 0;
}
