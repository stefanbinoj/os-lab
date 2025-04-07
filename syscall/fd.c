#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
    int fd;
    char data[] = "Hello, this is a test file.";
    // Open a file
    fd = open("example.txt", O_CREAT | O_WRONLY, 0644);
    if (fd < 0)
    {
        perror("open failed");
        exit(1);
    }
    printf("File opened successfully with file descriptor: %d\n", fd);
    // Write to the file
    if (write(fd, data, sizeof(data)) < 0)
    {
        perror("write failed");
        close(fd);
        exit(1);
    }
    printf("Data written to file successfully.\n");
    // Close the file
    if (close(fd) == 0)
    {
        printf("File closed successfully.\n");
    }
    else
    {
        perror("close failed");
    }
    return 0;
}