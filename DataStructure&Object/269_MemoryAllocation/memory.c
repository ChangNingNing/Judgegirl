#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

void initMemory(Memory *memory, int length){
	memory->start = 0;
	memory->length = length;
	memory->next = NULL;
	return;
}

void printMemory(Memory *memory){
	Memory *current = memory;
	printf("==========\n");
	while(current != NULL && current->start>=0){
		printf("start %d, length %d\n", current->start, current->length);
		current = current->next;
	}
	return;
}

void allocateMemory(Memory *memory, int start, int length){
	Memory *pre = NULL;
	Memory *current = memory;
	while(current!=NULL){
		if(current->start + current->length - 1 >= start){
			if(current->start + current->length< start + length) return;
			
			if(current->start == start && current->length == length){
				if(pre!=NULL){
					pre->next = current->next;
					free(current);
					break;
				}
				else if(current->next!=NULL){
					Memory *tmp = current->next;
					current->start = tmp->start;
					current->length = tmp->length;
					current->next = tmp->next;
					free(tmp);
					break;
				}
				else{
					current->start = -1;
				}
			}
			else if(current->start == start){
				current->start += length;
				current->length -= length;
				break;
			}
			else if(current->start+current->length == start+length){
				current->length -= length;
				break;
			}


			Memory *tmp1 = malloc(sizeof(Memory));
			tmp1->start = start + length;
			tmp1->length = current->start + current->length - (start + length);

			current->length = start - current->start;

			tmp1->next = current->next;
			current->next = tmp1;
			break;
		}
		pre = current;
		current = current->next;
	}
	return;
}

void freeMemory(Memory *memory, int start, int length){
	Memory *pre = NULL;
	Memory *cur = memory;
	while(cur!=NULL){
		if(cur->start > start){
			if(pre==NULL){
				if(start+length == cur->start){	
					cur->start = start;
					cur->length += length;
				}
				else{
					Memory *tmp1 = malloc(sizeof(Memory));
					tmp1->start = cur->start;
					tmp1->length = cur->length;
					tmp1->next = cur->next;

					cur->start = start;
					cur->length = length;
					cur->next = tmp1;
				}
			}
			else if(pre->start + pre->length == start && start+length==cur->start){
				pre->length += length + cur->length;
				pre->next = cur->next;
				free(cur);
			}
			else if(pre->start + pre->length == start){
				pre->length += length;
			}
			else if(start + length == cur->start){
				cur->start = start;
				cur->length += length;
			}
			else{
				Memory *tmp1 = malloc(sizeof(Memory));
				tmp1->start = start;
				tmp1->length = length;
				tmp1->next = cur;
				pre->next = tmp1;
			}
			break;
		}
		if(cur->start<0){
			cur->start = start;
			cur->length = length;
			cur->next = NULL;
			break;
		}
		pre = cur;
		cur = cur->next;
	}
	if(cur==NULL){
		if(pre->start + pre->length == start){
			pre->length += length;
		}
		else{
			Memory *tmp1 = malloc(sizeof(Memory));
			tmp1->start = start;
			tmp1->length = length;
			tmp1->next = pre->next;
			pre->next = tmp1;
		}
	}
	return;
}
