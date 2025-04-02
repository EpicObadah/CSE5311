#include <stdio.h>
#include <stdlib.h>
#define RED 1
#define BLACK 0

typedef struct Node
{
    int key;
    int color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

typedef struct RBT
{
    Node *root;
    Node *nil;
} RBT;

Node* newNode(RBT *tree, int key); 
void leftRotate(RBT *tree, Node *x);
void rightRotate(RBT *tree, Node *y); 
void insertFixup(RBT *tree, Node *z); 
void insert(RBT *tree, int key); 
Node* search(RBT *tree, int key); 
Node* minimum(RBT *tree, Node *node);
Node* maximum(RBT *tree, Node *node);
void inorderTraversal(RBT *tree, Node *node);

int main()
{
    RBT* tree = (RBT*)malloc(sizeof(RBT));
    tree->nil = (Node*)malloc(sizeof(Node));
    tree->nil->color = BLACK;
    tree->root = tree->nil;
    int keys[] = {20, 15, 25, 10, 5, 1, 30, 35, 40};
    for (int i = 0; i < sizeof(keys)/sizeof(int); i++) 
    {
        insert(tree, keys[i]);
    }
    
    printf("Inorder Traversal: ");
    inorderTraversal(tree, tree->root);
    printf("\n");
    
    printf("Min: %d\n", minimum(tree, tree->root)->key);
    printf("Max: %d\n", maximum(tree, tree->root)->key);
    
    int searchKey = 25;
    Node *searchResult = search(tree, searchKey);
    if (searchResult != tree->nil)
    {
        printf("Found %d in tree\n", searchResult->key);
    }
    else
    {
        printf("%d not found\n", searchKey);
    }

    free(tree);
    return 0;
}

Node* newNode(RBT *tree, int key) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->color = RED;
    newNode->left = tree->nil;
    newNode->right = tree->nil;
    newNode->parent = tree->nil;
    return newNode;
}



//used pseudocode from the book on page 313
void leftRotate(RBT *tree, Node *x) 
{
    Node *y = x->right;
    x->right = y->left;

    if (y->left != tree->nil)
    {
        y->left->parent = x;   
    }
    y->parent = x->parent;
    if (x->parent == tree->nil)
    {
        tree->root = y;
    }    
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }    
    else
    {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

//Similar implementation from the book to leftRotate
void rightRotate(RBT *tree, Node *y) 
{
    Node *x = y->left;
    y->left = x->right;

    if (x->right != tree->nil)
    {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == tree->nil)
    {
        tree->root = x;
    }    
    else if (y == y->parent->right)
    {
        y->parent->right = x;
    }    
    else
    {
        y->parent->left = x;
    }

    x->right = y;
    y->parent = x;
}

//used pseudocode from book
void insertFixup(RBT *tree, Node *z) 
{
    while (z->parent->color == RED) 
    {
        if (z->parent == z->parent->parent->left) 
        {
            Node *y = z->parent->parent->right;
            if (y->color == RED) 
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } 
            else 
            {
                if (z == z->parent->right) 
                {
                    z = z->parent;
                    leftRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        } 
        else 
        {
            Node *y = z->parent->parent->left;
            if (y->color == RED) 
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } 
            
            else 
            {
                if (z == z->parent->left) 
                {
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

//used pseudocode frmo the book.
void insert(RBT *tree, int key) 
{
    Node *z = newNode(tree, key);
    Node *y = tree->nil;
    Node *x = tree->root;
    while (x != tree->nil) 
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == tree->nil)
    {
        tree->root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    insertFixup(tree, z);
}

Node* search(RBT *tree, int key) 
{
    Node *current = tree->root;
    while (current != tree->nil && key != current->key) 
    {
        if (key < current->key)
        {
            current = current->left;
        }    
        else
        {
            current = current->right;
        }
    }
    return current;
}

Node* minimum(RBT *tree, Node *node) 
{
    while (node->left != tree->nil)
    {
        node = node->left;
    }
    return node;
}

Node* maximum(RBT *tree, Node *node) 
{
    while (node->right != tree->nil)
    {
        node = node->right;
    }
    return node;
}

void inorderTraversal(RBT *tree, Node *node) 
{
    if (node != tree->nil) 
    {
        inorderTraversal(tree, node->left);
        printf("%d ", node->key);
        inorderTraversal(tree, node->right);
    }
}