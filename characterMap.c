#include <stdio.h>
#include <stdlib.h>

#define CAPACITY_CHANGE_AMOUNT 10
#define DELETION_CHANGE_AMOUNT 10
#define DEFAULT_LIMIT_CAPACITY -1

struct data {
    int key;
    char * data;
};

struct map {
    struct data * charData;

    size_t length;
    size_t capacity;
    size_t deletions;

    int limitCapacity;
};

void * buildMap() {

    struct map * ch_map = malloc(sizeof(struct map));
    ch_map->length = 0;
    ch_map->capacity = 0;
    ch_map->limitCapacity = DEFAULT_LIMIT_CAPACITY; 
    ch_map->deletions = 0;

    return ch_map;
}

void * buildData(int key, char * data) {

    struct data * ch_data = malloc(sizeof(struct data));
    ch_data->key = key;
    ch_data->data = data;

    return ch_data;
}

int containsKey(struct map * ch_map, int key) {

    const size_t MAP_LENGTH = ch_map->length;

    if (key > MAP_LENGTH) {
        return 0;
    }

    for (size_t p_key = 0; p_key < MAP_LENGTH; p_key++) {
        if (ch_map->charData[p_key].key == key) {
            return 1;
        }
    }

    return 0;
}

int * getKeysArray(struct map * ch_map) {

    const size_t MAP_LENGTH = ch_map->length;

    if (MAP_LENGTH == 0) {
        perror("No data available. Map is empty!");
        return NULL;
    }

    int * keysArray = malloc(MAP_LENGTH * sizeof(int));

    for (size_t pKey = 0; pKey < MAP_LENGTH; pKey++) {
        keysArray[pKey] = ch_map->charData[pKey].key;
    }

    return keysArray;
}

struct data * getDataByMap(struct map * ch_map, int key) {

    const size_t MAP_LENGTH = ch_map->length;
    const int MAP_LIMIT_CAPACITY = ch_map->limitCapacity;

    if (MAP_LENGTH == 0) {
        perror("No data available. Map is empty!");
        return 0;
    }

    if (containsKey(ch_map, key) == 0) {
        perror("No data available. The map doesn't contains that key!");
        return 0;
    }

    return &ch_map->charData[key];
}

int getBiggerKey(struct map * ch_map) {

    const size_t MAP_LENGTH = ch_map->length;

    if (MAP_LENGTH == 0) {
        perror("No data available. Map is empty!");
        return 0;
    }

    int lastBigKey = 0;
    for (size_t pKey = 0; pKey < MAP_LENGTH; pKey++) {
        
        if (ch_map->charData[pKey].key > lastBigKey) {
            lastBigKey = pKey;
        }
    }

    return lastBigKey;
}

int getLowerKey(struct map * ch_map) {

    const size_t MAP_LENGTH = ch_map->length;

    if (MAP_LENGTH == 0) {
        perror("No data available. Map is empty!");
        return 0;
    }

    int lastLowerKey;
    for (size_t pKey = 0; pKey < MAP_LENGTH; pKey++) {
        
        if (ch_map->charData[pKey].key < lastLowerKey) {
            lastLowerKey = pKey;
        }
    }

    return lastLowerKey;
}

//  #define_capacityLimit(x, y)
//  Use -1 for "unlimited" capacity.
//  use X number for real limit.
int define_capacityLimit(struct map * ch_map, int limit) {
    ch_map->limitCapacity = limit;
    return 1;
}

int put(struct map * ch_map, struct data * ch_data) {

    if (containsKey(ch_map, ch_data->key) == 1) {
        ch_map->charData[ch_data->key] = *ch_data;
        return 1;
    }

    const size_t MAP_LENGTH = ch_map->length;
    const size_t MAP_CAPACITY = ch_map->capacity;
    const int MAP_LIMIT_CAPACITY = ch_map->limitCapacity;

    if (MAP_LIMIT_CAPACITY != -1 && MAP_LENGTH >= MAP_LIMIT_CAPACITY) {
        perror("Map capacity is fully. You need increase the map capacity limit!");
        return 0;
    }

    if (MAP_LENGTH >= MAP_CAPACITY) {
        ch_map->capacity = (MAP_CAPACITY + CAPACITY_CHANGE_AMOUNT);
        ch_map->charData = realloc(ch_map->charData, ch_map->capacity * sizeof(struct data));
    }

    ch_map->charData[MAP_LENGTH] = *ch_data;
    ch_map->length++;
    return 1;
}

int delete(struct map * ch_map, int key) {

    if (containsKey(ch_map, key) == 0) {
        perror("Not deleted. That key doesn't exist!");
        return 0;
    }

    if (ch_map->deletions >= DELETION_CHANGE_AMOUNT) {
        ch_map->capacity -= CAPACITY_CHANGE_AMOUNT;
        ch_map->deletions -= DELETION_CHANGE_AMOUNT;
        ch_map->charData = realloc(ch_map->charData, ch_map->capacity * sizeof(struct data));
    }

    ch_map->length--;
    ch_map->deletions++;

    free(&ch_map->charData[key]);

    return 1;
}
