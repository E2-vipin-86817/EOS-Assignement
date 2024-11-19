#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

struct input
{
	int num1,num2;
};
int add=0;
void* sum(void *param)
{
	struct input *ip = (struct input *)param;	
	//struct output *op = (struct output *)malloc(sizeof(struct output));
	
	for(int i= ip->num1;i<=ip->num2;i++)
	{
		add = add + i;
	}
	return add;
}
int main()
{
	pthread_t th;
	struct input in = {.num1 = 1 , .num2 = 15};
	//struct output *out;
	pthread_create(&th,NULL,sum,&in);
	pthread_join(th,(void**)&add);
	printf("Sum= %d\n",add);
	//free(out);
	return 0;
}
