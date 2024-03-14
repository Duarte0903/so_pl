#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *buffer = malloc(sizeof(char) * 1024);
    ssize_t bytes_read;
    int file = open(argv[1], O_RDONLY);
    int file2 = open(argv[2], O_CREAT | O_WRONLY, 0644);

    while((bytes_read = read(file, buffer, 1024)) != 0){
        ssize_t bytes_written = write(file2, buffer, bytes_read);
    }

    close(file);
    close(file2);
    
    return 0;
}