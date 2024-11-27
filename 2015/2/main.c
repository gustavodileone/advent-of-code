#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FILENAME "./input"
#define FILEMODE "r"
#define DELIMITER_INPUT "x"
#define PADDING 8

// Matando uma barata com uma bazuca! :D
unsigned int parseDimensions(char* line) {
    char* slength = strtok(line, DELIMITER_INPUT);
    char* swidth = strtok(NULL, DELIMITER_INPUT);
    char* sheight = strtok(NULL, DELIMITER_INPUT);
    if(!slength || !swidth || !sheight) exit(1);

    unsigned char length = strtol(slength, NULL, 0);
    unsigned char width = strtol(swidth, NULL, 0);
    unsigned char height = strtol(sheight, NULL, 0);

    return (length << (PADDING * 2)) + (width << (PADDING)) + height;
}

unsigned char getLength(unsigned int dimensions) {
    return dimensions >> (PADDING * 2);
}

unsigned char getWidth(unsigned int dimensions) {
    return dimensions >> PADDING;
}

unsigned char getHeight(unsigned int dimensions) {
    return dimensions;
}

unsigned int smallestSide(unsigned int side1, unsigned int side2, unsigned int side3) {
    int smallest = side1 < side2 ? side1 : side2;
    smallest = smallest < side3 ? smallest : side3;

    return smallest;
}

unsigned int calculatePaper(unsigned int dimensions) {
    unsigned char length = getLength(dimensions);
    unsigned char width = getWidth(dimensions);
    unsigned char height = getHeight(dimensions);

    int side1 = length * width;
    int side2 = width * height;
    int side3 = height * length;
    int smallest = smallestSide(side1, side2, side3);

    return (2 * side1) + (2 * side2) + (2 * side3) + (smallest);
}

unsigned int calculateWrap(unsigned int dimensions) {
    unsigned char length = getLength(dimensions);
    unsigned char width = getWidth(dimensions);
    unsigned char height = getHeight(dimensions);

    int side1 = length + length + width + width;
    int side2 = width + width + height + height;
    int side3 = height + height + length + length;
    int smallest = smallestSide(side1, side2, side3);

    return smallest;
}

unsigned int calculateBow(unsigned int dimensions) {
    return getLength(dimensions) * getWidth(dimensions) * getHeight(dimensions);
}

int main() {
    FILE* f = fopen(FILENAME, FILEMODE);

    unsigned int paper = 0;
    unsigned int ribbon = 0;

    char line[256] = {0};
    while(fgets(line, sizeof(line) / sizeof(line[0]), f) != NULL) {
        unsigned int dimensions = parseDimensions(line);
        paper += calculatePaper(dimensions);
        ribbon += calculateWrap(dimensions) + calculateBow(dimensions);
    }

    printf("Paper: %u\n", paper);
    printf("Ribbon: %u\n", ribbon);

    fclose(f);

    return EXIT_SUCCESS;
}