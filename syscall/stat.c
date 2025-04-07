#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
int main()
{
    struct stat fileStat;
    if (stat("testfile.txt", &fileStat) == -1)
    {
        perror("stat failed");
        return 1;
    }
    printf("File Information:\n");
    printf("File Size: %ld bytes\n", fileStat.st_size);
    printf("Inode Number: %ld\n", fileStat.st_ino);
    printf("Last Modified Time: %s", ctime(&fileStat.st_mtime));
    printf("Number of Links: %ld\n", fileStat.st_nlink);
    return 0;
}