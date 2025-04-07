#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
int main()
{
    struct dirent *dptr;
    char buff[100];
    DIR *dirp;
    printf("\n\n ENTER DIRECTORY NAME: ");
    scanf("%s", buff);
    if ((dirp = opendir(buff)) == NULL)
    {
        printf("The given directory does not exist\n");
        exit(1);
    }
    printf("\nContents of directory %s:\n", buff);
    while ((dptr = readdir(dirp)) != NULL)
    {
        printf("%s\n", dptr->d_name);
    }
    closedir(dirp);
    return 0;
}