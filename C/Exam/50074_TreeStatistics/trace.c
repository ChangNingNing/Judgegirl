#include "trace.h"
#include <stdio.h>

int DFS(Node *root, int depth, Answer* ans){
	if(root->list == NULL){
		ans->Leaf++;
		return depth;
	}
	ans->InternalNode++;
	int branch = 0, maxD = depth;
	for(ChildList *cur=root->list; cur!=NULL; cur=cur->next, branch++){
		int tmp = DFS(cur->node, depth+1, ans);
		if(tmp > maxD) maxD = tmp;
	}
	if(branch > ans->MaxBranchFactor) ans->MaxBranchFactor = branch;
	return maxD;
}

void trace(Node* root,Answer* ans){ ans->Depth = DFS(root, 0, ans); }
