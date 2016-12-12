typedef struct Node {
	int key;
	char value[128];
} Node;

typedef struct Map {
	int num;
	Node node[1024];
} Map;

void init(Map *map);
int map(Map *map, const int key, const char *value);
int numPairs(Map *map);
void print(Map *map);
const char *getValue(Map *map, const int key);
int unmap(Map *map, int key);
int reverseMap(Map *map, const char *value, int keys[]);
