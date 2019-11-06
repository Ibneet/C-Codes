#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int height = 0;
typedef struct node{
	int data;
	struct node *left, *right; 
}node;

node* newNode(int);

node* insertNewNode(node*, int);

node * minValueNode(node*);

node* deleteNode(node*, int);

void inorder(node*);

void preorder(node*);

void postorder(node*);

int minDepth(node *);

int maxDepth(node *);

void leftView(node*, int);


node* curr = NULL;

int main()
{
    int n,i,value,mini,maxi;
    char a[1];
	node* root = NULL;
    printf("How many nodes you want to have in your BST?\n");
    scanf("%d",&n);
    for( i=0; i<n; i++)
    {
        printf("Enter value: ");
        scanf("%d",&value);
        if(root == NULL)
        {
            root = insertNewNode(root,value);
        }
        else
        {
            insertNewNode(root,value);
        }
    }
    printf("Inorder \n");
	inorder(root);
    printf("Preorder \n");
    preorder(root);
    printf("Postorder \n");
    postorder(root);
    mini = minDepth(root);
    maxi = maxDepth(root);
    printf("Minimun depth: %d\n",mini);
    printf("Maximum depth: %d\n",maxi);
    
    printf("Do you want to delete a node? (y/n): ");
    scanf("%s",a);
    if(a[0] == 'y')
    {
        printf("Which node you want to delete: ");
        scanf("%d",&value);
        deleteNode(root,value);
    }
    printf("Inorder \n");
    inorder(root);
    printf("Preorder \n");
    preorder(root);
    printf("Postorder \n");
    postorder(root);
    printf("Left View \n");
    leftView(root,1);
}

node* newNode(int data)
{
	node* temp = (node*)malloc(sizeof(node));
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

node* insertNewNode(node* root, int data)
{
	if(root == NULL)
	{
		return newNode(data);
	}
	else if(data < root->data)
	{
		root->left = insertNewNode(root->left,data);
	}
	else
	{
		root->right = insertNewNode(root->right,data);
	}
	return root;
}

void inorder(node *root) 
{ 
    if (root != NULL) 
    { 
        inorder(root->left); 
        printf("%d \n", root->data); 
        inorder(root->right); 
    } 
}

void preorder(node *root)
{
    if (root != NULL)
    {
        preorder(root->left);
        preorder(root->right);
        printf("%d \n", root->data);
    }
}

void postorder(node *root)
{
    if (root != NULL)
    {
        printf("%d \n", root->data);
        postorder(root->left);
        postorder(root->right);
    }
}

node* minValueNode(node* node)
{
    
    curr = node;
    while (curr && curr->left != NULL)
        curr = curr->left;
    
    return curr;
}

node* deleteNode(node* root, int data)
{
    if (root == NULL)
        return root;
    
    if (data < root->data)
        root->left = deleteNode(root->left, data);
    
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    
    else
    {
        if (root->left == NULL)
        {
            node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            node *temp = root->left;
            free(root);
            return temp;
        }
        
        node* temp = minValueNode(root->right);
        
        root->data = temp->data;
        
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int minDepth(node *root)
{
    if (root == NULL)
        return 0;
    
    if (root->left == NULL && root->right == NULL)
        return 1;
    
    if (!root->left)
        return minDepth(root->right) + 1;
    
    if (!root->right)
        return minDepth(root->left) + 1;
    
    if (minDepth(root->left) < minDepth(root->right))
        return minDepth(root->left) + 1;
    else
        return minDepth(root->right) + 1;
            
}

int maxDepth(node *root)
{
    if (root == NULL)
        return 0;
    
    if (root->left == NULL && root->right == NULL)
        return 1;
    
    if (!root->left)
        return maxDepth(root->right) + 1;
    
    if (!root->right)
        return maxDepth(root->left) + 1;
    
    if (maxDepth(root->left) > maxDepth(root->right))
        return maxDepth(root->left) + 1;
        else
            return maxDepth(root->right) + 1;
}

void leftView(node* root, int level) 
{ 
    if (root == NULL) 
        return; 
  
    if (height < level) { 
        printf("%d", root->data); 
        printf("\n");
        height = level; 
    } 
  
    leftView(root->left, level + 1); 
    leftView(root->right, level + 1); 
} 
  