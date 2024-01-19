#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#define COLOR(p)     ( (p==NULL) ? BLACK : (((BtreePtr)(p))->color) )
#define REB 1
#define BLACK 2

typedef struct Bi{
    int val;
    int pos;
    int color;

    struct Bi *parent;
    struct Bi *left_child;
    struct Bi *right_child;
} Btree, *BtreePtr;

int midSearch(const BtreePtr a, const int key) {
    if (a != NULL) {
        if (key > a->val) {
            return midSearch(a->right_child, key);
        }
        else if(key < a->val) {
            return midSearch(a->left_child, key);
        }
        else {
            return a->pos;
        }
    }
    else {
        return -1;
    }
}

void freeTree(BtreePtr b) {
    if (b->right_child !=NULL) {
        freeTree(b->right_child);
    }
    if (b->left_child != NULL) {
        freeTree(b->left_child);
    }
}

BtreePtr leftRotateRB(BtreePtr p) {
    BtreePtr b = (BtreePtr)malloc(sizeof(Btree));
    b = p->right_child;
    p->right_child = b->left_child;
    p->color = REB;

    b->color = BLACK;
    b->left_child = p;
    b->parent = p->parent;
    b->left_child->parent = b;
    return b;
}

BtreePtr rightRotateRB(BtreePtr p) {
    BtreePtr b = (BtreePtr)malloc(sizeof(Btree));
    b = p->left_child;
    p->left_child = b->right_child;
    p->color = REB;

    b->color = BLACK;
    b->right_child = p;
    b->parent = p->parent;
    b->right_child->parent = b;
    return b;
}

BtreePtr rightleftRotateRB(BtreePtr p) {
    p->right_child = rightRotateRB(p->right_child);
    p = leftRotateRB(p);
    return p;
}

BtreePtr leftrightRotateRB(BtreePtr p) {
    p->right_child = leftRotateRB(p->right_child);
    p = rightRotateRB(p);
    return p;
}

BtreePtr _checkColor(BtreePtr p) {
    int p_color = COLOR(p);

    int right = COLOR(p->right_child);
    int left = COLOR(p->left_child);

    if (right == REB && left == BLACK) {
        int right_left = COLOR(p->right_child->left_child);
        int right_right = COLOR(p->right_child->right_child);

        if (right_right == REB) {
            p = leftRotateRB(p);
        }
        else if (right_left == REB) {
            p = rightleftRotateRB(p);
        }
    }

    else if (left == REB  && right == BLACK) {
        int left_right = COLOR(p->left_child->right_child);
        int left_left = COLOR(p->left_child->left_child);

        if (left_left == REB) {
            p = rightRotateRB(p);
        }
        else if (left_right == REB) {
            p = leftrightRotateRB(p);
        }
    }

    else if (right == REB && left == REB) {
        int left_right = COLOR(p->left_child->right_child);
        int left_left = COLOR(p->left_child->left_child);
        int right_left = COLOR(p->right_child->left_child);
        int right_right = COLOR(p->right_child->right_child);

        if (left_right == REB || left_left == REB || right_left == REB || right_right == REB) {
            if (p->parent != NULL) {
                p->color = REB;
            }
            p->left_child->color = BLACK;
            p->right_child->color = BLACK;
        }
    }
    return p;
}

BtreePtr _insertRBTree(BtreePtr p, const int key, const int pos) {
    if (p == NULL) {
        BtreePtr b = (BtreePtr)malloc(sizeof(Btree));
        if (b != NULL) {
            memset(b, 0, sizeof(Btree));
            b->val = key;
            b->pos = pos;
            b->color = REB;
            p = b;
        }
        else {
            return NULL;
        }
    }
    else
    {
        if (key < p->val) {
            p->left_child = _insertRBTree(p->left_child, key, pos);
            p->left_child->parent = p;
        }
        else {
            p->right_child = _insertRBTree(p->right_child, key, pos);
            p->right_child->parent = p;
        }
    }
    p = _checkColor(p);
    return p;
}

BtreePtr insertRBTree(BtreePtr root, const int key, const int pos) {
    if (root == NULL) {
        BtreePtr p = (BtreePtr)malloc(sizeof(Btree));
        if (p != NULL) {
            memset(p, 0, sizeof(Btree));
            p->val = key;
            p->pos = pos;
            p->color = BLACK;
            root = p;
        }
        else {
            puts("No hay suficiente almacenamiento");
        }
    }
    else
    {
        root = _insertRBTree(root, key, pos);
    }
    return root;
}


int RBTreeSearch(const int *a, const int length, const int key) {
    BtreePtr root = NULL;
    int i;
    for (i = 0; i < length; i++) {
        root = insertRBTree(root, a[i], i); // Construye un árbol binario
    }
    int pos = midSearch(root, key);
         freeTree (root); // No se puede usar free (b) directamente
    return pos;
}



void main() {
    const int length = 6;
    int my_array[6] = { 5, 7, 9,11 ,8,10};
    printf("%d \n", RBTreeSearch(my_array, length, 7));
}

