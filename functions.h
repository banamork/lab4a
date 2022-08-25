struct Tree{
    struct Node* root;

};


struct Node{
    char *key;
    struct Node *left;
    struct Node *right;
    int info;
    struct  Node *par;
}Node;


int D_Add(struct Tree *root);
int D_Find(struct Tree *root);
struct Node *find_recurs(struct Node *ptr,char *key);

int D_Delete(struct Tree *root);
struct Node *delete_recurs(struct Tree *root, struct Node *ptr,char *key);
char *find_min_right_key(struct Tree* root, struct Node* res);

int D_Show(struct Tree* root);
void print_tree(struct Node* root, int level);

int D_File(struct Tree* root);
int D_FindTime(struct Tree* root_tree);

int D_Show_preOrder(struct Tree* root_tree);
void print_preoder_tree(struct Node* root);

int D_Find_Max(struct Tree* root_tree);

int getInt(int *a);
char *get_str();
int dialog(const char *msgs[], int N);
struct Tree *tree_new();
