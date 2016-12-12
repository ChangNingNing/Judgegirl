typedef struct Row {
	char name[33];
	int score[512];
} Row;

typedef struct ExamTable{
	Row row[256];
	int dim_n;
	int nRow;
} ExamTable;

void init(ExamTable *self, int n);
void addrow(ExamTable *self, char *name, int score[]);
void print(ExamTable *self, int order[]);
