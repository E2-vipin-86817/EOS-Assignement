#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main() {
    char fifo_name[100], filename[100];

    // Get FIFO name and filename from user
    printf("Enter FIFO name: ");
    scanf("%s", fifo_name);
    printf("Enter filename to receive: ");
    scanf("%s", filename);

    // Create the FIFO
    mkfifo(fifo_name, 0666);

    // Send FIFO name and filename to server
    int fd = open("myfifo", O_WRONLY);
    write(fd, fifo_name, strlen(fifo_name) + 1);
    write(fd, filename, strlen(filename) + 1);
    close(fd);

    // Open the FIFO for reading
    fd = open(fifo_name, O_RDONLY);

    // Receive the file content and save to disk
    FILE *fp = fopen(filename, "wb");
    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = read(fd, buffer, 1024)) > 0) {
        fwrite(buffer, 1, bytes_read, fp);
    }

    // Close the FIFO and file
    close(fd);
    fclose(fp);

    return 0;
}
