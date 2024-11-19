#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

struct input
{
	int num1,num2;
};
struct output
{
	int sum;
};
void* sum(void *param)
{
	struct input *ip = (struct input *)param;	
	struct output *op = (struct output *)malloc(sizeof(struct output));
	op->sum=0;
	for(int i= ip->num1;i<=ip->num2;i++)
	{
		op->sum = op->sum + i;
	}
	return op;
}
int main()
{
	pthread_t th;
	struct input in = {.num1 = 1 , .num2 = 15};
	struct output *out;

	pthread_create(&th,NULL,sum,&in);
	pthread_join(th,(void**)&out);
	printf("Sum= %d\n",out->sum);
	free(out);
	return 0;
}
