#include <stdio.h>
#include <stdlib.h>

struct map {
    struct data * charData;
    int length;
    int capacity;
    int limitCapacity;

    int deletions;
};

struct data {
    int key;
    char * data;
};

void * buildMap() {

    struct map * ch_map = malloc(sizeof(struct map));
    ch_map->length = 0;
    ch_map->capacity = 0;
    ch_map->limitCapacity = -1; 
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

    const int MAP_LENGTH = ch_map->length;

    if (key > MAP_LENGTH) {
        return 1;
    }

    for (int p_key = 0; p_key < MAP_LENGTH; p_key++) {
        if (ch_map->charData[p_key].key == key) {
            return 0;
        }
    }

    return 1;
}

void * getDataByMap(struct map * ch_map, int key) {

    const int MAP_LENGTH = ch_map->length;
    const int MAP_LIMIT_CAPACITY = ch_map->limitCapacity;

    if (MAP_LENGTH == 0) {
        perror("No data available. Map is empty!");
        return NULL;
    }

    if (containsKey(ch_map, key) == 1) {
        perror("No data available. The map doesn't contains that key!");
        return NULL;
    }

    return &ch_map->charData[key];
}

//  #define_capacityLimit(x, y)
//  Use -1 for "unlimited" capacity.
//  use X number for real limit.
int define_capacityLimit(struct map * ch_map, int limit) {
    ch_map->limitCapacity = limit;
    return 0;
}

int put(struct map * ch_map, struct data * ch_data) {

    if (containsKey(ch_map, ch_data->key) == 0) {
        ch_map->charData[ch_data->key] = *ch_data;
        return 0;
    }

    const int MAP_LENGTH = ch_map->length;
    const int MAP_CAPACITY = ch_map->capacity;
    const int MAP_LIMIT_CAPACITY = ch_map->limitCapacity;

    if (MAP_LIMIT_CAPACITY != -1 && MAP_LENGTH >= MAP_LIMIT_CAPACITY) {
        perror("Map capacity is fully. You need increase the map capacity limit!");
        return 1;
    }

    if (MAP_LENGTH >= MAP_CAPACITY) {
        ch_map->capacity = (MAP_CAPACITY+10);
        ch_map->charData = realloc(ch_map->charData, ch_map->capacity * sizeof(struct data));
    }

    ch_map->length++;
    ch_map->charData[ch_data->key] = *ch_data;
    return 0;
}

int set(struct map * ch_map, int key, struct data * ch_data) {

    if (containsKey(ch_map, key) == 1) {
        perror("Not set. That key doesn't exist!");
        return 1;
    }

    ch_map->charData[key] = *ch_data;
    return 0;
}

int delete(struct map * ch_map, int key) {

    if (containsKey(ch_map, key) == 1) {
        perror("Not deleted. That key doesn''t exist!");
        return 1;
    }

    if (ch_map->deletions >= 10) {
        ch_map->capacity -= 10;
        ch_map->charData = realloc(ch_map->charData, ch_map->capacity * sizeof(struct data));
    }

    ch_map->length--;
    ch_map->deletions++;

    free(&ch_map->charData[key]);

    return 0;
}