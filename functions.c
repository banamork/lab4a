#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


const char *errmsgs[] = {"Error", "Ok", "Add to left", "Add to right", "Add to root", "Duplicate key", "Element not founded", "Element deleted", "Koren", "Tree clear"};

int D_Add(struct Tree* root_tree)
{
    int inform, rc, n;
    char *key;
    struct Node *tree_new = (struct Node*) calloc(1, sizeof(struct Node));

    printf("Enter the 1 key: ");
    scanf("%*c");
    key = get_str();
    if (key == NULL) {
        return 0; //EOF
    }



    printf("Enter the string of info: ");
    n = getInt(&inform);
    if (n == 0)
        return 0;


    tree_new->info = inform;
    tree_new->key = calloc (1, sizeof(char));
    strcpy(tree_new->key, key);


    if (root_tree->root == NULL)
    {
        tree_new->right = NULL;
        tree_new->left = NULL;
        tree_new->par = NULL;
        root_tree->root = tree_new;
        rc = 4;
    }else {

        struct Node *ptr = root_tree->root;
        struct Node *par = NULL;
        while(ptr != NULL){
            par = ptr;
            if(strcmp(tree_new->key, ptr->key)<0)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
        if(strcmp(tree_new->key , par->key)<0){
            par->left = tree_new;
            tree_new->info = inform;
            tree_new->par = par;
            tree_new->left = NULL;
            tree_new->right = NULL;
            rc = 2;
        }
        else if(strcmp(tree_new->key,par->key)>0){
            par->right = tree_new;
            tree_new->info = inform;
            tree_new->par = par;
            tree_new->left = NULL;
            tree_new->right = NULL;
            rc = 3;
        } else {
            rc = 0;
        }

    }

    printf("%s:\n%s\n", errmsgs[rc], key);


    return 1;
}

int D_Find(struct Tree* root)
{
    int  rc, n;
    char *key;

    printf("Enter the key: ");
    scanf("%*c");
    key = get_str();
    if (key == NULL) {
        return 0; //EOF
    }

    struct Node *ptr = root->root;

    struct Node *tree_new = find_recurs(ptr, key);
    if (tree_new == NULL)
        rc = 6;
    else{
        printf("information:\"%d\" %s ", tree_new->info, key);
        rc = 1;}
    printf("%s:\n%s\n", errmsgs[rc], key);
    return 1;
}

struct Node *find_recurs(struct Node *ptr,char *key){

    struct Node *res;
    if (ptr == NULL)
        return NULL;
    else{
        if(strcmp(ptr->key, key) == 0)
            res = ptr;
        else if(key < ptr->key){
            if (ptr->left == NULL)
                return res = NULL;
            res = find_recurs(ptr->left, key);
        }
        else{
            if (ptr->right == NULL)
                return NULL;
            res = find_recurs(ptr->right, key);
        }
    }
    return res;
}


int D_Delete(struct Tree* root){

    int rc, n;
    char *key;

    printf("Enter the 1 key: ");
    scanf("%*c");
    key = get_str();
    if (key == NULL) {
        return 0; //EOF
    }


    struct Node *ptr = root->root;

    struct Node *tree_delet = delete_recurs(root, ptr, key);


    if (tree_delet == NULL)
        rc = 6;
    else{
        printf("information:\"%d\" %s ", tree_delet->info, tree_delet->key);
        rc = 7;}
    printf("%s:\n%s\n", errmsgs[rc], key);
    return 1;
}
struct Node *delete_recurs(struct Tree *root, struct Node *ptr,char *key){


    struct Node *res = find_recurs(ptr, key);
    if (ptr == NULL)
        return NULL;

    struct Node *del;
    struct Node *p;
    struct Node *param = res->par;

    if (res->right == NULL && res->left == NULL)
        del = res;
    else if(res->right != NULL && res->left == NULL)
        del = res->right;
    else if(res->right == NULL && res->left != NULL)
        del = res->left;
    else{
        char *min_key = find_min_right_key(root, res->right);
        del = delete_recurs(root, ptr, min_key);

        res->info = del->info;
        strcpy(res->key,del->key);
        return del;
    }


    if (del->left != NULL)
        p = del->left;
    else
        p = del->right;
    struct Node *par = del->par;

    if (p != NULL)
        p->par = par;
    if (par == NULL)
        root->root = p;
    else if (par->left == del)
        par->left = p;
    else
        par->right = p;

    if (res != del){
        res->info = del->info;
        strcpy(res->key, del->key);
        res->right = del->right;
        res->left = del->left;
        res->par = del->par;
    }
    return del;
}

char *find_min_right_key(struct Tree* root, struct Node* res){
    struct Node *ptr = res;
    while (ptr->left !=NULL){
        ptr = ptr->left;
    }
    return ptr->key;
}

int D_Show(struct Tree* root){
    int level = 0;
    print_tree(root->root, level);
    return 1;
}
void print_tree(struct Node* tree, int level){
    if(tree){
        print_tree(tree->right, level+1);
        for(int i = 0; i<level; i++)
            printf("      ");
        printf("key: %s, info: %d\n", tree->key, tree->info);
        print_tree(tree->left, level+1);
    }
}

int D_File(struct Tree* root_tree){
        FILE *fp;
    char key_char[10];
    if ((fp = fopen("/Users/vtornik/CLabs/lab4a/Add.txt", "r")) == NULL)
    {
        printf("Не удалось открыть файл");
        getchar();
        return 0;
    }

    while (key_char) {
        int inform, rc;
        int n=0, i=0;
        char inform_1[10];
        char *key, *inform_help;
        struct Node *tree_new = (struct Node *) calloc(1, sizeof(struct Node));

        if ( NULL != fgets ( key_char, 10, fp ) ) {
            key = key_char;
            if (key == 0)
                return 0;
        }else
            return 1;

        if ( NULL != fgets ( inform_1, 100, fp ) ) {
            inform = atoi(inform_1);
            inform_help = inform_1;
            char *pos = strrchr(inform_help, '\n');
            if (pos)
                inform[pos-inform] = 0;

            if (inform == NULL) {
                return 0; //EOF
            }
        }else
            return 1;



        tree_new->info = inform;
        tree_new->key = calloc(1, sizeof(char));
        strcpy(tree_new->key, key);


        if (root_tree->root == NULL) {
            tree_new->right = NULL;
            tree_new->left = NULL;
            tree_new->par = NULL;
            root_tree->root = tree_new;
            rc = 4;
        } else {

            struct Node *ptr = root_tree->root;
            struct Node *par = NULL;
            while (ptr != NULL) {
                par = ptr;
                if (tree_new->key < ptr->key)
                    ptr = ptr->left;
                else
                    ptr = ptr->right;
            }
            if (strcmp(tree_new->key, par->key)<0) {
                par->left = tree_new;
                tree_new->info = inform;
                tree_new->par = par;
                tree_new->left = NULL;
                tree_new->right = NULL;
                rc = 2;
            } else if (strcmp(tree_new->key, par->key)>0) {
                par->right = tree_new;
                tree_new->info = inform;
                tree_new->par = par;
                tree_new->left = NULL;
                tree_new->right = NULL;
                rc = 3;
            } else
                rc = 0;

        }

        printf("%s:\n%s\n", errmsgs[rc], key);
    }
    fclose(fp);
    getchar();


    return 1;
}

int D_FindTime(struct Tree* root_tree){

    int  rc, n;
    char* key;

    printf("Enter the 1 key: ");
    scanf("%*c");
    key = get_str();
    if (key == NULL) {
        return 0; //EOF
    }

    scanf("%*c");
    clock_t begin = clock();
    struct Node *ptr = root_tree->root;

    struct Node *tree_new = find_recurs(ptr, key);
    if (tree_new == NULL)
        rc = 6;
    else{
        printf("information:\"%d\" %s ", tree_new->info, key);
        rc = 1;}
    printf("%s:\n%s\n", errmsgs[rc], key);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time of work: %lf", time_spent);
    // }

    return 1;
}

int D_Show_preOrder(struct Tree* root_tree){

    int rc, n, choice;
    printf("0. Quit\n1. Show all tree\n2. Show tree with key");
    n = getInt(&choice);
    if (n == 0)
        return 0;
    if (choice == 0){
        return 1;
    }else if(choice == 1){
        print_preoder_tree(root_tree->root);
    } else if(choice == 2){
        char* key;
        printf("Enter the 1 key: ");
        scanf("%*c");
        key = get_str();
        if (key == NULL) {
            return 0; //EOF
        }

        print_preoder_tree(find_recurs(root_tree->root, key));
    }else
        return 1;



    return 1;
}



void print_preoder_tree(struct Node* root){
    if (root) {
        printf("key: %s\t info: %d\n", root->key, root->info);
        print_preoder_tree(root->left);
        print_preoder_tree(root->right);
    }
}

int D_Find_Max(struct Tree* root){
    int  rc;
    char *key;

    struct Node *ptr = root->root;


    //struct Node *tree_new = find_recurs(ptr, key);
    if (ptr == NULL)
        rc = 9;
    else{
        while(ptr->right != NULL)
            ptr = ptr->right;
        printf("information:\"%d\" %s ", ptr->info, ptr->key);
        rc = 1;}
    printf("%s:\n%s\n", errmsgs[rc], key);
    return 1;
}

int getInt(int *a)
{
    int n;
    do{
        n = scanf("%d", a, sizeof(int));
        if (n < 0)
            return 0;
        if (n == 0){
            printf("%s\n", "Error! Repeat input");
            scanf("%*c", 0);
        }
    } while (n == 0);
    return 1;
}
char* get_str()
{
    char buf[81] = { 0 };
    char* res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf, 80);
        if (n < 0) {
            if (!res)
                return NULL;
        }
        else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = (char*)realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        }
        else
            scanf("%*c");
    } while (n > 0);

    if (len > 0)
        res[len] = '\0';
    else
        res = (char*)calloc(1, sizeof(char));

    return res;
}
int dialog(const char *msgs[], int N)
{
    char *errmsg = "";
    int rc;
    int i, n;
    do{
        puts(errmsg);
        errmsg = "You are wrong. Repeat, please!";
        for(i = 0; i < N; ++i)
            puts(msgs[i]);
        puts("Make your choice: --> ");
        n = getInt(&rc);
        if(n == 0)
            rc = 0;
    } while(rc < 0 || rc >= N);
    return rc;
}
struct Tree *tree_new(){
    struct Tree* tree_ptr = (struct Tree*) calloc (1, sizeof(struct Tree));

    return tree_ptr;
}
