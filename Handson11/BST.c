#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct BST
{
    Node* root;
} BST;


Node* createNode(int value);
Node* insert(Node* key, int value);
Node* search (Node* key, int value);
Node* findMin(Node* key);
Node* findMax(Node* key);
Node* delete(Node* key, int value);
void inorderTraversal(Node* key);

int main()
{
    BST* tree = (BST*)malloc(sizeof(BST));
    tree->root = NULL;
    tree->root = insert(tree->root, 50);
    tree->root = insert(tree->root, 30);
    tree->root = insert(tree->root, 70);
    tree->root = insert(tree->root, 20);
    tree->root = insert(tree->root, 40);
    tree->root = insert(tree->root, 60);
    tree->root = insert(tree->root, 80);
    
    printf("Inorder traversal before deletion: ");
    inorderTraversal(tree->root);
    printf("\n");
    
    tree->root = delete(tree->root, 30);
    
    printf("Inorder traversal after deleting 30: ");
    inorderTraversal(tree->root);
    printf("\n");
    
    free(tree);
    return 0;
}

Node* createNode(int value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = newNode-> right = NULL;
    return newNode;
}


Node* insert(Node* key, int value)
{
    if (key == NULL)
    {
        return createNode(value);
        
    }
    if(value < key->value)
    {
        key->left = insert(key->left,value);
    }
    else 
    {
        key->right = insert(key->right, value);
    }
    return key;
}

Node* search (Node* key, int value)
{
    if (key == NULL || key->value == value) 
    {
        return key;
    }
    if (value < key->value)
    {
        return search(key->left, value);
    }
    return search(key->right, value);
}

Node* findMin(Node* key)
{
    while(key && key->left)
    {
        key = key->left;
    }
    
    return key;
}

Node* findMax(Node* key)
{
    while(key && key->right)
    {
        key = key->right;
    }
    return key;
}

Node* delete(Node* key, int value) 
{
    if (key== NULL)
    {
        return key;
    } 
    if (value < key->value)
    {
        key->left = delete(key->left, value);
    }
    else if (value > key->value) 
    {
        key->right = delete(key->right, value);
    }
    else 
    {
        if (key->left == NULL) 
        {
            Node* temp = key->right;
            free(key);
            return temp;
        } 
        else if (key->right == NULL) 
        {
            Node* temp = key->left;
            free(key);
            return temp;
        }
        Node* temp = findMin(key->right);
        key->value = temp->value;
        key->right = delete(key->right, temp->value);
    }
    return key;
}

void inorderTraversal(Node* key) 
{
    if (key) 
    {
        inorderTraversal(key->left);
        printf("%d ", key->value);
        inorderTraversal(key->right);
    }
}

