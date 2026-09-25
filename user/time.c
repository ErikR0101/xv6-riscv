#include "kernel/types.h"
#include "user/user.h"
#include "kernel/pstat.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: time <command>\n");
        exit(1);
    }

    int start_time = uptime();
    int pid = fork();

    if (pid < 0) {
        printf("fork failed\n");
        exit(1);
    } else if (pid == 0) {
        exec(argv[1], &argv[1]);
        printf("exec %s failed\n", argv[1]);
        exit(1);
    } else {
        int status;
        struct rusage r;
        
        // Call wait2 to get both exit status and rusage data
        wait2(&status, &r);
        
        int end_time = uptime();
        int elapsed = end_time - start_time;
        int cputime = r.cputime;
        
        
        int cpu_percent = (elapsed > 0) ? ((cputime * 100) / elapsed) : 0;
        
        // print all 
        printf("elapsed time: %d ticks, cpu time: %d ticks, %d%% CPU\n", elapsed, cputime, cpu_percent);
    }
    
    exit(0);
}
