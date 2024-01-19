#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
	int data;
	struct tree *leftchild;
	struct tree *rightchild;
}BinarySearchTree;

BinarySearchTree *getNode(int value);
BinarySearchTree *insert(BinarySearchTree *root, int value);
BinarySearchTree *search(BinarySearchTree *root, int value);
void update(BinarySearchTree *root, int value, int newValue);
void preOrder(BinarySearchTree *root);
void inOrder(BinarySearchTree *root);
void postOrder(BinarySearchTree *root);
void remove(BinarySearchTree *root, int value);
void destroyTree(BinarySearchTree *root);

int main(int argc, char *argv[]) {
	
	BinarySearchTree *tree = NULL;
	printf("\nInserting values...");
	tree = insert(tree,5);
	insert(tree,8);
	insert(tree,1);
	insert(tree,7);
	insert(tree,6);
	insert(tree,4);
	insert(tree,15);
	insert(tree,11);
	insert(tree,17);
	printf("\nShowing...");
	printf("\nPre order\n");
	preOrder(tree);
	printf("\nIn order\n");
	inOrder(tree);
	printf("\nPost order\n");
	postOrder(tree);
	update(tree,8,9);
	printf("\nSearching node...");
	search(tree,32);
	remove(tree,1);
	printf("\nIn order\n");
	inOrder(tree);
	
	return 0;
}

BinarySearchTree *getNode(int value){
	BinarySearchTree *node = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
	node->data = value;
	node->leftchild = node->rightchild = NULL;
	return node;
}

BinarySearchTree *insert(BinarySearchTree *root, int value){
	if(root == NULL){
		return getNode(value);
	} else if(root->data == value){
		printf("\n\nError: Value %d already exists", value);
	} else if(value < root->data){
		root->leftchild = insert(root->leftchild,value);
	} else{
		root->rightchild = insert(root->rightchild,value);
	}
	
	return root;
}

BinarySearchTree *search(BinarySearchTree *root, int value){
	if(root == NULL){
		printf("\nThe value dont exits");
		return NULL;
	} else if(root->data == value){
		return root;
	} else if(value < root->data){
		search(root->leftchild, value);
	} else{
		search(root->rightchild, value);
	}
}

void update(BinarySearchTree *root, int value, int newValue){
	if((root == search(root,value))){
		root->data = newValue;
	}
}

void preOrder(BinarySearchTree *root){
	if(root == NULL)
		return;
	printf("%d - ",root->data);
	preOrder(root->leftchild);
	preOrder(root->rightchild);
}

void inOrder(BinarySearchTree *root){
	if(root == NULL)
		return;
	inOrder(root->leftchild);
	printf("%d - ",root->data);
	inOrder(root->rightchild);
}

void postOrder(BinarySearchTree *root){
	if(root == NULL)
		return;
	postOrder(root->leftchild);
	postOrder(root->rightchild);
	printf("%d - ",root->data);
}

void remove(BinarySearchTree *root, int value){
	BinarySearchTree *nodetoDelete = search(root,value);
	if(nodetoDelete != NULL){
		if(root->leftchild == NULL && root->rightchild == NULL){
			free(nodetoDelete);
		}else{
			BinarySearchTree *explorer;
			if(explorer == nodetoDelete->leftchild){
				while(explorer->rightchild)
					explorer = explorer->rightchild;
			} else if(explorer == nodetoDelete->rightchild){
				while(explorer->leftchild)
					explorer = explorer->leftchild;
			}
			nodetoDelete->data = explorer->data;
			free(explorer);
		}
	}
}

void destroyTree(BinarySearchTree *root){
	if(root == NULL)
		return;
	destroyTree(root->leftchild);
	destroyTree(root->rightchild);
	free(root);
	root->data = 0;
	root = root->leftchild = root->rightchild = NULL;
}

