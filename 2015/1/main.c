#include <stdio.h>
#include <stdlib.h>

#define FILENAME "./input"
#define FILEMODE "r"

int main() {
    FILE* f = fopen(FILENAME, FILEMODE);
    char c;

    int floor = 0;
    int basement = -1;
    int i = 1;

    while((c = fgetc(f)) != EOF) {
        if(c == '(') floor++;
        else floor--;

        if(basement == -1 && floor <= -1)
            basement = i;

        i++;
    }

    fclose(f);

    printf(
        "floor: %d\n"
        "basement: %d\n",
        floor,
        basement
    );

    return EXIT_SUCCESS;
}