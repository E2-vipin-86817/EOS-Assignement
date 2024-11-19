#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main() {
    char fifo_name[100], filename[100];

    // Receive FIFO name and filename from client
    int fd = open("myfifo", O_RDONLY);
    read(fd, fifo_name, 100);
    read(fd, filename, 100);
    close(fd);

    // Create the requested FIFO
    mkfifo(fifo_name, 0666);

    // Open the file to be sent
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }

    // Open the FIFO for writing
    fd = open(fifo_name, O_WRONLY);

    // Send the file content through the FIFO
    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, 1024, fp)) > 0) {
        write(fd, buffer, bytes_read);
    }

    // Close the file and FIFO
    fclose(fp);
    close(fd);

    return 0;
}
