#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>
int main(int argc, char *argv[])
{
	int p[2];
	pipe(p);
	char buf[512];
	int pid = fork();
	if (pid > 0)
	{
		close(p[1]);
   		read(p[0], buf, 1);
    	
		wait(NULL);
	
  		printf("%d: received ping\n", (int)getpid());
		exit(0);
	}
	else if (pid == 0)
	{
		close(p[0]);
		char msg[] = {'c'};
   		write(p[1], msg, 1);
    	close(p[1]);

		printf("%d: received pong\n", (int)getpid());
   		exit(0);
	}
	else
	{
  		printf("fork error\n");
		exit(1);
	}
	return 0;
}
