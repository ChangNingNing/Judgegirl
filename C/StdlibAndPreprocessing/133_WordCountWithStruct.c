#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct string_count {
        char seen[80];
        int count;
};

int compare(const void *a, const void *b){
	struct string_count tmp1 = *(struct string_count *)a;
	struct string_count tmp2 = *(struct string_count *)b;
	if(tmp1.count!=tmp2.count) return tmp1.count-tmp2.count;
	return strncmp(tmp1.seen, tmp2.seen, 80);
}

int compare_and_add(char *string, struct string_count strings[]) {
        int index = 0;
	while(strings[index].count!=0){
		if(strncmp(strings[index].seen, string, 80)==0){
			strings[index].count++;
			return 1;
		}
		index++;
	}
	strncpy(strings[index].seen, string, 80);
	strings[index].count++;
	return 0;
	
}
void sort(struct string_count strings[]) {
	int index = 0;
        while(strings[index].count!=0){
		index++;
	}
	qsort((void *)strings, index, sizeof(strings[0]), compare);
}
void print(struct string_count strings[]) {
	int index = 0;
        while(strings[index].count!=0){
		printf("%d %s\n", strings[index].count, strings[index].seen);
		index++;
	}
}


/* your uploaded code will be here */
/*
int main() {
        struct string_count strings[20];
        int i;
        for( i=0 ; i<20 ; i++ )
                strings[i].count = 0;
        compare_and_add( "This", strings );
        compare_and_add( "is", strings );
        compare_and_add( "an", strings );
        compare_and_add( "apple,", strings );
        compare_and_add( "and", strings );
        compare_and_add( "this", strings );
        compare_and_add( "is", strings );
        compare_and_add( "a", strings );
        compare_and_add( "book.", strings );
        sort( strings );
        print( strings );
        return 0;
}
*/
