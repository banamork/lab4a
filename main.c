#include <stdio.h>
#include "functions.h"


const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show", "5. File", "6. NULL", "7. Preorder show", "8. Find biggest key"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);



int (*fptr[])(struct Tree *) = {NULL, D_Add, D_Find, D_Delete, D_Show, D_File, NULL, D_Show_preOrder, D_Find_Max};


int main() {

    int rc;
    struct Tree *root_tree = tree_new();


    while (rc = dialog(msgs, NMsgs))
        if(!(fptr[rc](root_tree)))
            break;


    printf("That's all. Bye!\n");
    return 0;
}