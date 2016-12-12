#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
	char name[20];
	int id;
	char phone[10];
	float grade[4];
	int birth_year;
	int birth_month;
	int birth_day;
} Student;

int main(){
	char inputName[81], outputName[81];
	scanf("%s %s", inputName, outputName);
	FILE *fin = fopen(inputName, "rb");
	FILE *fout = fopen(outputName, "w");
	Student temp;
	
	fprintf(fout, "<table border=\"1\">\n");
	fprintf(fout, "<tbody>\n");
	
	if(!fin){
		printf("123\n");
		exit(1);
	}
	while(fread(&temp, sizeof(Student), 1, fin)){
		fprintf(fout, "<tr>\n");
		fprintf(fout, "<td>%s</td>\n", temp.name);
		fprintf(fout, "<td>%d</td>\n", temp.id);
		fprintf(fout, "<td>%s</td>\n", temp.phone);
		fprintf(fout, "<td>%f, %f, %f, %f</td>\n", temp.grade[0], temp.grade[1], temp.grade[2], temp.grade[3]);
		fprintf(fout, "<td>%d, %d, %d</td>\n", temp.birth_year, temp.birth_month, temp.birth_day);
		fprintf(fout, "</tr>\n");
	}
	fprintf(fout, "</tbody>\n");
	fprintf(fout, "</table>\n");

	fclose(fin);
	fclose(fout);
	return 0;
}
