#include <stdio.h>
#include <stdlib.h>
enum nodeColor {
    R,
    B
};

struct rbNode {
    int data, color;
    struct rbNode *link[2];
};

struct rbNode *root = NULL;

struct rbNode * createNode(int data) {
    struct rbNode *newnode;
    newnode = (struct rbNode *)malloc(sizeof(struct rbNode));
    newnode->data = data;
    newnode->color = R;
    newnode->link[0] = newnode->link[1] = NULL;
    return newnode;
}

void insert (int data) {
    struct rbNode *stack[98], *ptr, *newnode, *xPtr, *yPtr;
    int dir[98], ht = 0, index;
    ptr = root;
    if (!root) {
        root = createNode(data);
        return;
    }
    stack[ht] = root;
    dir[ht++] = 0;
    while (ptr != NULL) {
        if (ptr->data == data) {
            printf("Duplicates Not Allowed!!\n");
            return;
        }
        index = (data - ptr->data) > 0 ? 1 : 0;
        stack[ht] = ptr;
        ptr = ptr->link[index];
        dir[ht++] = index;
    }
    stack[ht - 1]->link[index] = newnode = createNode(data);
    while ((ht >= 3) && (stack[ht - 1]->color == R)) {
        if (dir[ht - 2] == 0) {
            yPtr = stack[ht - 2]->link[1];
            if (yPtr != NULL && yPtr->color == R) {
                
                stack[ht - 2]->color = R;
                stack[ht - 1]->color = yPtr->color = B;
                ht = ht -2;
            } else {
                if (dir[ht - 1] == 0) {
                    yPtr = stack[ht - 1];
                } else {
                    
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->link[1];
                    xPtr->link[1] = yPtr->link[0];
                    yPtr->link[0] = xPtr;
                    stack[ht - 2]->link[0] = yPtr;
                }
                
                xPtr = stack[ht - 2];
                xPtr->color = R;
                yPtr->color = B;
                xPtr->link[0] = yPtr->link[1];
                yPtr->link[1] = xPtr;
                if (xPtr == root) {
                    root = yPtr;
                } else {
                    stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                }
                break;
            }
        } else {
            yPtr = stack[ht - 2]->link[0];
            if ((yPtr != NULL) && (yPtr->color == R)) {
                
                stack[ht - 2]->color = R;
                stack[ht - 1]->color = yPtr->color = B;
                ht = ht - 2;
            } else {
                if (dir[ht - 1] == 1) {
                    yPtr = stack[ht - 1];
                } else {
                    
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->link[0];
                    xPtr->link[0] = yPtr->link[1];
                    yPtr->link[1] = xPtr;
                    stack[ht - 2]->link[1] = yPtr;
                }
               
                xPtr = stack[ht - 2];
                yPtr->color = B;
                xPtr->color = R;
                xPtr->link[1] = yPtr->link[0];
                yPtr->link[0] = xPtr;
                if (xPtr == root) {
                    root = yPtr;
                } else {
                    stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                }
                break;
            }
        }
    }
    root->color = B;
}

void delete(int data) {
    struct rbNode *stack[98], *ptr, *xPtr, *yPtr;
    struct rbNode *pPtr, *qPtr, *rPtr;
    int dir[98], ht = 0, diff, i;
    enum nodeColor color;
    
    if (!root) {
        printf("Tree not available\n");
        return;
    }
    
    ptr = root;
 
    while (ptr != NULL) {
        if ((data - ptr->data) == 0)
            break;
        diff = (data - ptr->data) > 0 ? 1 : 0;
        stack[ht] = ptr;
        dir[ht++] = diff;
        ptr = ptr->link[diff];
    }
    
    if (ptr->link[1] == NULL) {
      
        if ((ptr == root) && (ptr->link[0] == NULL)) {
            free(ptr);
            root = NULL;
        } else if (ptr == root) {
            
            root = ptr->link[0];
            free(ptr);
        } else {
          
            stack[ht - 1]->link[dir[ht - 1]] = ptr->link[0];
        }
    } else {
        xPtr = ptr->link[1];
        if (xPtr->link[0] == NULL) {
            
            xPtr->link[0] = ptr->link[0];
            color = xPtr->color;
            xPtr->color = ptr->color;
            ptr->color = color;
            
            if (ptr == root) {
                root = xPtr;
            } else {
                stack[ht - 1]->link[dir[ht - 1]] = xPtr;
            }
            
            dir[ht] = 1;
            stack[ht++] = xPtr;
        } else {
           
            i = ht++;
            while (1) {
                dir[ht] = 0;
                stack[ht++] = xPtr;
                yPtr = xPtr->link[0];
                if (!yPtr->link[0])
                    break;
                xPtr = yPtr;
            }
            
            dir[i] = 1;
            stack[i] = yPtr;
            if (i > 0)
                stack[i - 1]->link[dir[i - 1]] = yPtr;
            
            yPtr->link[0] = ptr->link[0];
            xPtr->link[0] = yPtr->link[1];
            yPtr->link[1] = ptr->link[1];
            
            if (ptr == root) {
                root = yPtr;
            }
            
            color = yPtr->color;
            yPtr->color = ptr->color;
            ptr->color = color;
        }
    }
    if (ht < 1)
        return;
    if (ptr->color == B) {
        while (1) {
            pPtr = stack[ht - 1]->link[dir[ht - 1]];
            if (pPtr && pPtr->color == R) {
                pPtr->color = B;
                break;
            }
            
            if (ht < 2)
                break;
            
            if (dir[ht - 2] == 0) {
                rPtr = stack[ht - 1]->link[1];
                
                if (!rPtr)
                    break;
                
                if (rPtr->color == R) {

                    stack[ht - 1]->color = R;
                    rPtr->color = B;
                    stack[ht - 1]->link[1] = rPtr->link[0];
                    rPtr->link[0] = stack[ht - 1];
                    
                    if (stack[ht - 1] == root) {
                        root = rPtr;
                    } else {
                        stack[ht - 2]->link[dir[ht - 2]] = rPtr;
                    }
                    dir[ht] = 0;
                    stack[ht] = stack[ht - 1];
                    stack[ht - 1] = rPtr;
                    ht++;
                    
                    rPtr = stack[ht - 1]->link[1];
                }
                
                
                if ( (!rPtr->link[0] || rPtr->link[0]->color == B) &&
                    (!rPtr->link[1] || rPtr->link[1]->color == B)) {
                   
                    rPtr->color = R;
                } else {
                    if (!rPtr->link[1] || rPtr->link[1]->color == B) {
                        
                        qPtr = rPtr->link[0];
                        rPtr->color = R;
                        qPtr->color = B;
                        rPtr->link[0] = qPtr->link[1];
                        qPtr->link[1] = rPtr;
                        rPtr = stack[ht - 1]->link[1] = qPtr;
                    }
                    rPtr->color = stack[ht - 1]->color;
                    stack[ht - 1]->color = B;
                    rPtr->link[1]->color = B;
                    stack[ht - 1]->link[1] = rPtr->link[0];
                    rPtr->link[0] = stack[ht - 1];
                    if (stack[ht - 1] == root) {
                        root = rPtr;
                    } else {
                        stack[ht - 2]->link[dir[ht - 2]] = rPtr;
                    }
                    break;
                }
            } else {
                rPtr = stack[ht - 1]->link[0];
                if (!rPtr)
                    break;
                
                if (rPtr->color == R) {
                    stack[ht - 1]->color = R;
                    rPtr->color = B;
                    stack[ht - 1]->link[0] = rPtr->link[1];
                    rPtr->link[1] = stack[ht - 1];
                    
                    if (stack[ht - 1] == root) {
                        root = rPtr;
                    } else {
                        stack[ht - 2]->link[dir[ht - 2]] = rPtr;
                    }
                    dir[ht] = 1;
                    stack[ht] = stack[ht - 1];
                    stack[ht - 1] = rPtr;
                    ht++;
                    
                    rPtr = stack[ht - 1]->link[0];
                }
                if ( (!rPtr->link[0] || rPtr->link[0]->color == B) &&
                    (!rPtr->link[1] || rPtr->link[1]->color == B)) {
                    rPtr->color = R;
                } else {
                    if (!rPtr->link[0] || rPtr->link[0]->color == B) {
                        qPtr = rPtr->link[1];
                        rPtr->color = R;
                        qPtr->color = B;
                        rPtr->link[1] = qPtr->link[0];
                        qPtr->link[0] = rPtr;
                        rPtr = stack[ht - 1]->link[0] = qPtr;
                    }
                    rPtr->color = stack[ht - 1]->color;
                    stack[ht - 1]->color = B;
                    rPtr->link[0]->color = B;
                    stack[ht - 1]->link[0] = rPtr->link[1];
                    rPtr->link[1] = stack[ht - 1];
                    if (stack[ht - 1] == root) {
                        root = rPtr;
                    } else {
                        stack[ht - 2]->link[dir[ht - 2]] = rPtr;
                    }
                    break;
                }
            }
            ht--;
        }
    }
}

void searchElement(int data) {
    struct rbNode *temp = root;
    int diff;
    
    while (temp != NULL) {
        diff = data - temp->data;
        if (diff > 0) {
            temp = temp->link[1];
        } else if (diff < 0) {
            temp = temp->link[0];
        } else {
            printf("Search Element Found!!\n");
            return;
        }
    }
    printf("Given Data Not Found in RB Tree!!\n");
    return;
}

void printRBT(struct rbNode *node) {
    if (node) {
        printRBT(node->link[0]);
        printf("%d  ", node->data);
        printRBT(node->link[1]);
    }
    return;
}

int main() {
    int ch, data;
    while (1) {
        printf("1. Insert\t2. Deletion\n");
        printf("3. Searching\t4. Print\n");
        printf("5. Exit\nEnter your choice:");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter the data to insert:");
                scanf("%d", &data);
                insert(data);
                break;
            case 2:
                printf("Enter the data to delete:");
                scanf("%d", &data);
                delete(data);
                break;
            case 3:
                printf("Enter the search element:");
                scanf("%d", &data);
                searchElement(data);
                break;
            case 4:
                printRBT(root);
                printf("\n");
                break;
            case 5:
                exit(0);
            default:
                printf("You have enteR wrong option!!\n");
                break;
        }
        printf("\n");
    }
    return 0;
}
