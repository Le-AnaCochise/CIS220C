// Ana Le
// Chpt7 PA
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COUNT 10 		// a preprocessor directive that defines a macro named COUNT with the value 10

// Definition of the BST Node
typedef struct BSTNode {
    int key;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// Function to create a new BST node
BSTNode* createNode(int key) {
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Definition of the Binary Search Tree (BST)
typedef struct BST {
    BSTNode* root;
} BST;

// Function to create an empty BST
BST* createBST() {
    BST* tree = (BST*)malloc(sizeof(BST));
    tree->root = NULL;
    return tree;
}

BSTNode* getRoot(BST* tree) {
    return tree->root;
}

// Implement the BSTSearchRecursive PseudoCode found in PA 7.9.1
BSTNode* searchRecursive(BSTNode* node, int key) {
	// Added
	//  if the node is empty OR the key matches
	if (node == NULL || node->key == key) {
        return node;
    }
	// Go down the left subtree if the key is smaller
    if (key < node->key) {
        return searchRecursive(node->left, key);
    }
	// Go down the right subtree if the key is greater
	else if (key > node->key) {
		return searchRecursive(node->right, key);
	}
}


// Implement the BSTSearch PseudoCode found in PA 7.9.1
BSTNode* search(BST* tree, int key) {
	// Added
	return searchRecursive(tree->root, key);
}

// Function to check if the tree contains a node with the given key
bool contains(BST* tree, int key) {
    return search(tree, key) != NULL;
}

// Implement the BSTInsertRecursive PseudoCode found in Fig. 7.9.2
void insertRecursive(BSTNode* parent, BSTNode* nodeToInsert) {
	// Added
	 if (nodeToInsert->key < parent->key) {
		 // Insert into left subtree if the left child is NULL
        if (parent->left == NULL) {
            parent->left = nodeToInsert;
        } 
		else {
            insertRecursive(parent->left, nodeToInsert);
        }
    } 
	else { 		// nodeToInsert->key > parent->key
		// Insert into right subtree if the right child is NULL
        if (parent->right == NULL) {
            parent->right = nodeToInsert;
        } 
		else {
            insertRecursive(parent->right, nodeToInsert);
        }
    }   
}

// Implement the BSTInsertNode PseudoCode found in Fig. 7.9.2
void insertNode(BST* tree, BSTNode* node) {
	//Added
	// If tree is empty, set the root
	if (tree->root == NULL) {
        tree->root = node;
    } 
	else {
		// Insert recursively
        insertRecursive(tree->root, node);
    }
}

// Function to insert a key into the BST
bool insertKey(BST* tree, int key) {
    if (contains(tree, key)) {
        return false; // Duplicate keys not allowed
    }
	// Create a new node
    BSTNode* newNode = createNode(key);
	// Call insertNode method
    insertNode(tree, newNode);
    return true;
}

// Implement a printInReverseOrder function discussed in Section 7.7 
void printInReverseOrder(BSTNode* node) {
	// Added
	if (node == NULL) {
        return;
    }
	// Print the right subtree
    printInReverseOrder(node->right);
	
	// Print the node key
    printf("%d ", node->key);
	
	// Print the left subtree
    printInReverseOrder(node->left);
}

 // Function to print the binary tree in 2D using reverse inorder traversal
void print2DUtil(BSTNode* root, int space) {
    // Base case: If the node is NULL, return
    if (root == NULL) {
        return;
    }

    // Increase space for the next level
    space += COUNT;

    // First, process the right child
    print2DUtil(root->right, space);

    // Print the current node after space count
    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->key);

    // Then, process the left child
    print2DUtil(root->left, space);
}

// Wrapper function to print the tree
void print2D(BSTNode* root) {
    // Start with 0 space
    print2DUtil(root, 0);
}

// Function to free memory allocated for BST nodes
void freeTree(BSTNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Implement the main function based on the program instructions
int main() {
	// Added
	// 1. Insert the keys 35,41,13,57,3,83,88,51,38,20,11,22,27,21,48,8 into the BST in the order listed
    BST* tree = createBST();
	
    int keys[] = {35, 41, 13, 57, 3, 83, 88, 51, 38, 20, 11, 22, 27, 21, 48, 8};
    int numKeys = sizeof(keys) / sizeof(keys[0]);
    
    // Insert keys into BST
    for (int i = 0; i < numKeys; i++) {
        insertKey(tree, keys[i]);
    }
    
    // 2. Call the printInReverseOrder function
	printf("Binary Search Tree After Inserts:\n");
    printInReverseOrder(tree->root);
    printf("\n");
    
    // 3. Call the print2D function.
    print2D(tree->root);
	printf("\n");
    
    // 4. Search for an existing key: 27. Implement an if-else statement to check the return value to determine if the key was found.
    int searchKey = 27;
    if (search(tree, searchKey) != NULL) {
        printf("Found node with key = %d.\n", searchKey);
    } 
	else {
        printf("Key %d not found.\n", searchKey);
    }
	printf("\n");
	
    // 5. Search for a non-existing key: 89. Implement an if-else statement to check the return value to determine if the key was found.
    searchKey = 89;
    if (search(tree, searchKey) != NULL) {
        printf("Found node with key = %d.\n", searchKey);
    } 
	else {
        printf("Key %d not found.\n", searchKey);
    }
	
	freeTree(tree->root);
	free(tree);
   
    return 0;
}