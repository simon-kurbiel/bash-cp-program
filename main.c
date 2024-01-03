#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char **argv)
{
    int input_fd, output_fd, open_flags;
    mode_t file_perms;
    size_t num_read;
    char buffer[BUF_SIZE];

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
    {
        printf("%s old-file new-file\n", argv[0]);
        return EXIT_FAILURE;
    }
    /*Start opening and reading the files*/
    input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1)
    {
        printf("error opening %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    open_flags = O_CREAT | O_WRONLY | O_TRUNC;
    file_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    output_fd = open(argv[2], open_flags, file_perms);
    if (output_fd == -1)
    {
        printf("error opening %s\n", argv[2]);
        return EXIT_FAILURE;
    }

    /*Start transfering the data*/
    while ((num_read = read(input_fd, buffer, BUF_SIZE)) > 0)
        if (write(output_fd, buffer, num_read) != num_read)
        {
            printf("error writing to %s\n", argv[2]);
            return EXIT_FAILURE;
        }

    return 0;
}