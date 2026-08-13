#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./zeropad <filename>\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");

    if(fp == NULL) {
        printf("%s\n", "Error reading file");
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    fclose(fp);

    return 0;
}
