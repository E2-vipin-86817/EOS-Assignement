#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct input {
    int num1;
    int num2;
     
};
struct output {
	int res;
   	//int sum;
}; 

void* sumofn(void *param) {

	int sum=0,i;
    struct input *ip = (struct input *)param;
    struct output *op = (struct output *)malloc(sizeof(struct output));
 //   int i, *num = (int*)param;
	if(i<=ip->num2){
		for(i=ip->num1;i<=ip->num2;i++){

     sum =i+sum;
	 op->res=sum;
	 }
	}
	//op->sum = ip->a +  ip->b;
    printf("sum = %d\n",op->res);
    //sleep(5);
    return op;
}

int main() {
    pthread_t th;
	int a,b;
	printf("enter the num1& num2:");
	scanf("%d %d ",&a, &b);
	struct input in = { .num1 = a, .num2=b };
    struct output *out;
    pthread_create(&th, NULL, sumofn, &in);
    // pthread_join() pause execution of current thread for the completion
    //  of given thread (arg1) and collect its result in out param (arg2).
    pthread_join(th, (void**)&out);
    {
        printf("main: sum=%d\n",out->res);
       
    }
   
    return 0;
}

