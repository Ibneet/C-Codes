#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node * next;
}node;

void createQueues(int,int);
void display(node*);
void deleteNode(node*);

//*********************************************************************

int main()
{
    int q,n;
    node * head = NULL;
    printf("How many queues you want to make: ");
    scanf("%d",&q);
    printf("How many nodes you want to insert: ");
    scanf("%d",&n);
    createQueues(n,q);
    return 0;
}

//*********************************************************************

void createQueues(int n,int q)
{
    int x,b,c;
    node* index[q];
    node * temp = NULL;
    node * temp1 = NULL;
    node * rear = NULL;
    node * newNode = NULL;
    for(int j = 0 ; j < q ; j++)
    {
        node * head = NULL;
        printf("This is queue number %d \n",j+1);
        for(int i = 0 ; i < n ; i++)
        {
            temp = (node*)malloc(sizeof(node));
            printf("Enter the data to the node %d: ",i+1);
            scanf("%d" ,&(temp->data));
            temp->next = NULL;
            
            if(head == NULL)
            {
                head = temp;
            }
            else
            {
                temp1=head;
                while(temp1->next != NULL)
                    temp1 = temp1->next;
                temp1->next = temp;
            }
        }
        index[j] = head;
    }
    for( int i = 0 ; i < q ; i++ )
    {
        printf("This is queue %d\n",i+1);
        display(index[i]);
    }
    while(1)
    {
        printf("What you want to do next:\nPress 1 if you want to get into the queue\nPress 2 if you want to get something from the queue\nPress 3 to exit from the program\n");
        scanf("%d",&b);
        
        switch (b) {
            case 1:
                newNode = (node*)malloc(sizeof(node));
                printf("Enter the data to the new node: ");
                scanf("%d" ,&(newNode->data));
                newNode->next = NULL;
                printf("In which queue you want to go: ");
                scanf("%d",&x);
                temp1 = index[x-1];
                if(temp1 != NULL)
                {
                    if( temp1->next == NULL )
                        temp1->next = newNode;
                    
                    else
                    {
                    while( temp1->next != NULL)
                    {
                        temp1 = temp1->next;
                        if( temp1->next == NULL)
                            rear = temp1;
                    }
                    rear->next = newNode;
                    }
                }
                else
                {
                    temp1 = newNode;
                    index[x-1] = temp1;
                }
            
                printf("This is the updated queue %d\n",x);
                display(index[x-1]);
                break;
            case 2:
                printf("From which queue do you want to get the number: ");
                scanf("%d",&x);
                deleteNode(index[x-1]);
                index[x-1]=index[x-1]->next;
                break;
            case 3:
                exit(0);
            default:
                break;
        }
    }
}
    

//*********************************************************************

void display(node*linkedList)
{
    while(linkedList != NULL)
    {
        printf("%d\n",linkedList->data);
        linkedList = linkedList->next;
    }
}

//*********************************************************************

void deleteNode(node* linkedList)
{
    node * head = NULL;
    
    head = linkedList->next;
    linkedList->next = NULL;
    free(linkedList);
    
    printf("This is the updated queue\n");
    display(head);
}


