#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"
#include "kernel/fs.h"
#include <stddef.h>

#define MSGSIZE 32

int main(int argc, char *argv[])
{
    char buf[MSGSIZE];
    read(0, buf, MSGSIZE);

    int n = read(0, buf, MSGSIZE);
    int buf_idx = 0;
    while(n > 0){
        buf_idx += n;
        n = read(0, &buf[buf_idx], MSGSIZE);    
    }

    char* xargv[MSGSIZE];
    int xargc = 0;
    for(int i = 1; i < argc; i++){
        xargv[xargc++] = argv[i];
    }

    char* p = buf;
    for(int i  = 0; i < MSGSIZE; i++){
        if(buf[i] == '\n'){
            int pid = fork();
            if(pid > 0){
                p = &buf[i + 1];
                wait(NULL);
            }else{
                buf[i] = 0;
                xargv[xargc++] = p;
                xargv[xargc] = 0;
                exec(xargv[0], xargv);
                exit(1);
            }
        }
    }    

    exit(0);
}
