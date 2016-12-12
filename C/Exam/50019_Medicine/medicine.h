typedef struct Ingredient{
	int weight;
	char name[128];
} Ingredient;

typedef struct Medicine {
	int nAct, nInact, weight;
	Ingredient Act[2];
	Ingredient Inact[5];
} Medicine;

void init(Medicine *medicine);
int addActive(Medicine *medicine, char *name, int weight);
int addInactive(Medicine *medicine, char *name, int weight);
void print(Medicine *medicine);
int totalWeight(Medicine *medicine);
char *maxIngredient(Medicine *medicine);
