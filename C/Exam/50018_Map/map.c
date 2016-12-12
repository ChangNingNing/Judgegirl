#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init(Map *map){
	map->num = 0;
	return;
}

int map(Map *map, const int key, const char *value){
	int pos = map->num;
	for(int i=0; i<map->num; i++){
		if(map->node[i].key == key){
			pos = i;
			break;
		}
	}

	if(pos == map->num){
		map->node[pos].key = key;
		strcpy(map->node[pos].value, value);
		map->num++;
		return 1;
	}
	strcpy(map->node[pos].value, value);
	return 0;
}

int numPairs(Map *map){ return map->num; }


int compare(const void *a, const void *b) { return ((Node *)a)->key - ((Node *)b)->key; }

void print(Map *map){
	qsort(map->node, map->num, sizeof(map->node[0]), compare);
	printf("----- map begin -----\n");
	for(int i=0; i<map->num; i++){
		printf("%d ", map->node[i].key);
		printf("%s\n", map->node[i].value);
	}
	printf("----- end       -----\n");
	return;
}

const char *getValue(Map *map, const int key){
	for(int i=0; i<map->num; i++){
		if(map->node[i].key == key)
			return map->node[i].value;
	}
	return NULL;
}

int unmap(Map *map, int key){
	int pos = -1;
	for(int i=0; i<map->num; i++){
		if(map->node[i].key == key){
			pos = i;
			break;
		}
	}
	if(pos < 0) return 0;
	
	for(int i=pos; i < map->num-1; i++){
		map->node[i].key = map->node[i+1].key;
		strcpy(map->node[i].value, map->node[i+1].value);
	}
	map->num--;
	return 1;
}

int compare2(const void *a, const void *b){ return *(int *)a - *(int *)b; }

int reverseMap(Map *map, const char *value, int keys[]){
	int n = 0;
	for(int i=0; i<map->num; i++){
		if(!strcmp(map->node[i].value, value))
			keys[n++] = map->node[i].key;
	}
	qsort(keys, n, sizeof(keys[0]), compare2);
	return n;
}
