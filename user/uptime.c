#include "kernel/types.h"
#include "user/user.h"
//says .s in file but h is used in xv6?
int main(int argc, char *argv[]) {
    int ticks = uptime();
    printf("%d\n", ticks);
    
    exit(0);
}
