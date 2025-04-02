#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

typedef struct AVLTree
{
    Node *root;
} AVLTree;

int getHeight(Node *node);
int getBalance(Node *node);
Node* createNode(int key);
Node* rotateRight(Node* y); 
Node* rotateLeft(Node* x);
Node* insert(Node* node, int key); 
Node* findMin(Node* node);
Node* deleteNode(Node* root, int key); 
Node* search(Node* root, int key);
void inorderTraversal(Node *root);

int main()
{
    AVLTree* tree = (AVLTree*)malloc(sizeof(AVLTree));
    tree->root = NULL;
    
    int numToFind = 0;
    int numToDelete = 0;
    tree->root = insert(tree->root, 10);
    tree->root = insert(tree->root, 20);
    tree->root = insert(tree->root, 30);
    tree->root = insert(tree->root, 40);
    tree->root = insert(tree->root, 50);
    tree->root = insert(tree->root, 25);
    
    printf("In-order traversal: ");
    inorderTraversal(tree->root);
    printf("\n");
    
    numToDelete = 10;
    tree->root = deleteNode(tree->root, numToDelete);
    printf("After deleting %d: ", numToDelete);
    inorderTraversal(tree->root);
    printf("\n");
    
    numToFind = 30;
    Node* found = search(tree->root, numToFind);
    
    if (found)
    {
        printf("Searching for %d: Found\n", numToFind);
    }
    else
    {
        printf("Searching for %d: Not Found\n", numToFind);
    }
    
    printf("Minimum value: %d\n", findMin(tree->root)->key);
    
    return 0;
}

int getHeight(Node *node)
{
    if (node)
    {
        return node->height;
    }
    else
    {
        return 0;
    }
}

int getBalance(Node *node) 
{
    if (node)
    {
        return getHeight(node->left) - getHeight(node->right);
    }
    else
    {
        return 0;
    }
}

Node* createNode(int key) 
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

Node* rotateRight(Node* y) 
{
    Node* x = y->left;
    Node* temp = x->right; //saving the right child of node x
    
    x->right = y;
    y->left = temp;
    
    if (getHeight(y->left) > getHeight(y->right))
    {
        y->height = 1 + getHeight(y->left);
    }
    else
    {
        y->height = 1 + getHeight(y->right);
    }
    
    if (getHeight(x->left) > getHeight(x->right))
    {
        x->height = 1 + getHeight(x->left);
    }
    else
    {
        x->height = 1 + getHeight(x->right);
    }
    
    return x;
}

Node* rotateLeft(Node* x) 
{
    Node* y = x->right;
    Node* temp = y->left; //saving the left child of node y
    
    y->left = x;
    x->right = temp; 
    
    if (getHeight(x->left) > getHeight(x->right))
    {
        x->height = 1 + getHeight(x->left);
    }
    else
    {
        x->height = 1 + getHeight(x->right);
    }
    
    if (getHeight(y->left) > getHeight(y->right))
    {
        y->height = 1 + getHeight(y->left);
    }
    else
    {
        y->height = 1 + getHeight(y->right);
    }
    
    
    return y;
}

Node* insert(Node* node, int key) 
{
    if (!node) 
    {
        return createNode(key);
    }

    if (key < node->key)
    {
        node->left = insert(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key);
    }
    else
    {
        return node; 
    }

    if (getHeight(node->left) > getHeight(node->right))
    {
        node->height = 1 + getHeight(node->left);
    }
    else
    {
        node->height = 1 + getHeight(node->right);
    }

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
    {
        return rotateRight(node);
    }
    if (balance < -1 && key > node->right->key)
    {
        return rotateLeft(node);
    }
    if (balance > 1 && key > node->left->key) 
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key) 
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

Node* findMin(Node* node) 
{
    while (node->left)
    {
        node = node->left;
    }
    return node;
}

Node* deleteNode(Node* root, int key) 
{
    if (!root)
    {
        return root;  
    }

    if (key < root->key)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = deleteNode(root->right, key);
    }
    else 
    {
        Node* temp;
        if (!root->left)
        {
            temp = root->right;
            free(root);
            return temp;
        }
        else if (!root->right)
        {
            temp = root->left;
            free(root);
            return temp;
        }
        temp = findMin(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    if (getHeight(root->left) > getHeight(root->right))
    {
        root->height = 1 + getHeight(root->left);
    }
    else
    {
        root->height = 1 + getHeight(root->right);
    }
    
    
    int balance = getBalance(root);
    
    if (balance > 1 && getBalance(root->left) >= 0)
    {
        return rotateRight(root);
    }
    if (balance > 1 && getBalance(root->left) < 0) 
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
    {
        return rotateLeft(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) 
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Node* search(Node* root, int key) 
{
    if (!root || root->key == key)
    {
        return root;
    }    
    if (key < root->key)
    {
        return search(root->left, key);
    }    
    return search(root->right, key);
}

void inorderTraversal(Node *root) 
{
    if (root) 
    {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}