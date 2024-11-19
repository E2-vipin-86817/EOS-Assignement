#include<stdio.h>
#include<sys/wait.h>
#include<sys/msg.h>
#include<unistd.h>

#define MQ_KEY 0x1111

typedef struct msg
{
	long id;
	int a,b,res;
}msg_t;

int main()
{
	int mqid,pid,s,ret;
	mqid = msgget(MQ_KEY, IPC_CREAT | 0600 );
	if(mqid < 0)
	{
		perror("msgget() failed");
		_exit(1);
	}
	//chlid process
	pid=fork();

	if(pid == 0)
	{
		//chlid send message
		msg_t m1;
		m1.id = 111;
		printf("child: enter the numbers: ");
		scanf("%d%d",&m1.a,&m1.b);
		ret = msgsnd(mqid, &m1 ,sizeof(msg_t)-sizeof(long),0);
		if(ret < 0)
		{
			perror("child: msgsnd() failed");
		}
		else
		{
			printf("child: message send:a=%d,b=%d\n",m1.a,m1.b);
		}
	}
	else
	{
		//parent receive message
		msg_t m2;
		printf("parent: waiting for child message\n");
		ret = msgrcv(mqid, &m2, sizeof(msg_t)-sizeof(long),111,0);
		if(ret < 0)
		{
			perror("msgrcv() failed");
		}
		else
		{
			m2.res = m2.a + m2.b;
			printf("parent: received:\na+b= %d",m2.res);
		}
		//parent cleanup child
		waitpid(pid,&s,0);
		//destroy message queue
		msgctl(mqid,IPC_RMID,NULL);
	}
	return 0;
}
