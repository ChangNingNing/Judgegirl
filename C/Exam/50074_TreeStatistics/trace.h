typedef struct ChildList ChildList;
typedef struct Node{
        ChildList* list;
}Node;
struct ChildList{
        Node* node;
        ChildList* next;
};
typedef struct Answer{
        int InternalNode;
        int Leaf;
        int MaxBranchFactor;
        int Depth;
}Answer;
void trace(Node* root,Answer* ans);
