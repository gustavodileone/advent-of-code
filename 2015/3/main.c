#include <stdio.h>
#include <stdlib.h>

#define NORTH '^'
#define SOUTH 'v'
#define EAST  '>'
#define WEST  '<'

#define FILENAME "./input"
#define FILEMODE "r"

#define MAPSIZE 10000

typedef struct Worker {
    int x, y;
    struct Worker* next;
} Worker;

typedef struct Node {
    int x, y;
    int visited;
    struct Node* next;
} Node;

typedef struct Map {
    int length;
    struct Node* nodes[MAPSIZE];
} Map;

Node* node_init(int x, int y, int visited) {
    Node* node = malloc(sizeof(node));
    node->x = x;
    node->y = y;
    node->visited = visited;

    return node;
}

Map* map_init() {
    Map* map = malloc(sizeof(Map));
    map->length = 0;

    return map;
}

unsigned long map_hash(int x, int y) {
    unsigned long hash = 5381;
    int key = x + y;

    return (((hash << 5) + hash) + key) % MAPSIZE;
}

int map_get(Map* map, int x, int y) {
    unsigned long hash = map_hash(x, y);
    if(map->nodes[hash] == NULL) return -1;

    Node* item = map->nodes[hash];
    while(item != NULL) {
        if(item->x == x && item->y == y) return item->visited;
        item = item->next;
    }

    return -1;
}

void map_set(Map* map, int x, int y, int visited) {
    unsigned long hash = map_hash(x, y);
    if(map->nodes[hash] == NULL) {
        map->nodes[hash] = node_init(x, y, visited);
        return;
    }

    Node* item = map->nodes[hash];
    while(item != NULL) {
        if(item->x == x && item->y == y) {
            item->visited = visited;
            return;
        }

        if(item->next == NULL) {
            item->next = node_init(x, y, visited);
            return;
        }

        item = item->next;
    }
}

int main() {
    Map* map = map_init();
    FILE* f = fopen(FILENAME, FILEMODE);

    int houses = 1;
    char c;

    Worker santa = {0};
    santa.x = 0;
    santa.y = 0;

    Worker robo = {0};
    santa.x = 0;
    santa.y = 0;

    robo.next = &santa;
    santa.next = &robo;

    map_set(map, 0, 0, 1);

    Worker* turn = &santa;

    while((c = fgetc(f)) != EOF) {
        switch(c) {
            case NORTH:
                turn->y++;
            break;

            case SOUTH:
                turn->y--;
            break;

            case WEST:
                turn->x--;
            break;

            case EAST: 
                turn->x++;
            break;

            default:
                fprintf(stderr, "Invalid char '%c'!\n", c);
                exit(1);
            break;
        }

        int visited = map_get(map, turn->x, turn->y);
        if(visited == -1) {
            map_set(map, turn->x, turn->y, 1);
            houses++;
        }
        
        turn = turn->next;
    }

    printf("Houses: %d\n", houses);

    fclose(f);

    return EXIT_SUCCESS;
}