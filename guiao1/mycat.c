#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 1024

int main() {
    ssize_t resR;
    char buffer[MAX];

    while((resR = read(STDIN_FILENO,buffer,MAX)) > 0){
        write(STDOUT_FILENO,buffer,resR);
    }
    
    return 0;
}

