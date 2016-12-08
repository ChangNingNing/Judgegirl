#include "book.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int authorCompare(const void *a, const void *b){
	BookAuthor *A = (BookAuthor *)a, *B = (BookAuthor *)b;
	return strcmp(A->book_title, B->book_title);
}

int sellingCompare(const void *a, const void *b){
	BookSelling *A = (BookSelling *)a, *B = (BookSelling *)b;
	int flag = strcmp(A->book_title, B->book_title);
	if(flag != 0) return flag;
	return A->date - B->date;
}

BookInfoList merge(int N, int M, BookAuthor authorArr[], BookSelling sellingArr[]){
	qsort(authorArr, N, sizeof(authorArr[0]), authorCompare);
	qsort(sellingArr, M, sizeof(sellingArr[0]), sellingCompare);
	BookInfoList list;
	list.num = 0;
	for(int i=0, j=0; i<N && j<M;){
		int flag = strcmp(authorArr[i].book_title, sellingArr[j].book_title);
		if(flag < 0) i++;
		else if(flag > 0) j++;
		else{
			strcpy(list.books[list.num].book_title, authorArr[i].book_title);
			strcpy(list.books[list.num].author, authorArr[i].author);
			list.books[list.num].date = sellingArr[j].date;
			list.books[list.num].selling = sellingArr[j].selling;
			list.num++, j++;
		}
	}
	return list;
}
