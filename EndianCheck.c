#include <stdio.h>

int main() {
    unsigned int num = 1;
    char *c = (char*)&num;

    if (*c == 1) {
        printf("The system is Little Endian.\n");
    } else {
        printf("The system is Big Endian.\n");
    }

    return 0;
}

