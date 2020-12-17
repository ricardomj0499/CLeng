#include <limits.h> /* PATH_MAX */
#include <stdio.h>
#include <stdlib.h>
int main(void) {
    char buf[PATH_MAX]; /* PATH_MAX incudes the \0 so +1 is not required */
    char *res = realpath("maze.jpg", buf);
    if (res) {
        printf("This source is at %s\n", buf);
    } else {
        perror("realpath");
        exit(EXIT_FAILURE);
    }
    return 0;
}