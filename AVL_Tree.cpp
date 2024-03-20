#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
struct node
{
       int info,bfactor;
       node *left, *right,*parent;
};
typedef struct node Node;
void createTree(Node *);
void InOrder(Node *);
void PreOrder(Node *);
void Left_Rotation(Node *,Node **);
//Node *search(Node *,int);
void Right_Rotation(Node *,Node **);
void Insert(Node **);
int main()
{
    Node *root = NULL,*ptr;
    int value;
    /*printf("Do u want to create a binary tree (Y/N) :");
    char choice = getche();
    fflush(stdin);
    if((choice == 'y') || (choice == 'Y'))
    {
               Node *node = (Node *)malloc(1*sizeof(Node));
               root = node;
               node->parent=NULL;
               createTree(node);
    }*/
    while(1)
    {
            printf("\nEnter\n1.To insert into AVL Tree\n2.For Preorder and Inorder Traversal\n");
            scanf("%d",&value);
            switch(value)
            {
                         case 1:Insert(&root);
                                break;
                         case 2:PreOrder(root);
                                InOrder(root);             
            }        
    }
    /*printf("\nEnter the value of node to be search         :");
    scanf("%d",&value);
    ptr =search(root,value);
    if(ptr != NULL)
         printf("\nFound");
    else
         printf("\nNot Found");*/
    getch();
}
void createTree(Node *node)
{
    printf("\nEnter the value of node  :"); 
    scanf("%d", &node->info);
    printf("\nNode %d has left child  (Y/N)  :", node->info);
    char choice = getche();
    if((choice == 'y') || (choice == 'Y'))
    {
               Node *leftchild = (Node *)malloc(1*sizeof(Node));
               node->left = leftchild;
               leftchild->parent=node;
               createTree(leftchild);
    }
    else if((choice == 'n') || (choice == 'N'))
               node->left = NULL;    
    printf("\nNode %d has right child  (Y/N)  :", node->info);
    choice = getche();
    fflush(stdin);
    if((choice == 'y') || (choice == 'Y'))
    {
               Node *rightchild = (Node *)malloc(1*sizeof(Node));
               node->right = rightchild;
               rightchild->parent=node;
               createTree(rightchild);
    }
    else if((choice == 'n') || (choice == 'N'))
               node->right = NULL;     
}
void PreOrder(Node *root)
{
     Node *stack[10];
     int top = 0;
     stack[top] = NULL;
     printf("\n\nPre Order Traversal of Binary Tree is            :  ");
     while(root != NULL )
     {
            printf("%d   ", root->info);
            if(root->right != NULL)
            {
                      top++; 
                      stack[top] = root->right;    
            }
            if(root->left != NULL)
                      root =  root->left;
            else
            {
                    root = stack[top];
                    top--;
            }    
     }
}
void InOrder(Node *root)
{
     Node *stack[10];
     int top = 0;
     stack[top] = NULL;
     printf("\n\nInOrder Traversal of Binary Tree is              :  ");
     while(root != NULL || stack[top] != NULL)
     {
             while(root != NULL)
             {
                        top++;
                        stack[top] = root;      
                        root = root->left;
             }
             printf("  %d", stack[top]->info);         
             if(stack[top]->right != NULL)
                    root = stack[top]->right;
             top--;
     }
}
/*Node *search(Node *ptr,int value)
{
     if(ptr != NULL)
     {
           Node *temp;
           if(ptr->info == value)
               return(ptr);
           temp = search(ptr->left,value);
           if(temp != NULL)
               return(temp);
           temp = search(ptr->right,value);
           return(temp);         
     }
     return(NULL);
}*/
void Left_Rotation(Node *ptr,Node **root)
{
     Node *rchild; 
     rchild = ptr->right;
     ptr->right = rchild->left;
     if(ptr->right != NULL)
           ptr->right->parent=ptr;
     rchild->parent = ptr->parent;
     if(ptr->parent != NULL)
     {
          if(ptr == ptr->parent->left)
                 ptr->parent->left=rchild;
          else
                 ptr->parent->right=rchild;
     }
     else
         *root = rchild;
     rchild->left = ptr;
     ptr->parent = rchild;
}
void Right_Rotation(Node *ptr,Node **root)
{
     Node *lchild;
     lchild = ptr->left;
     ptr->left = lchild->right;
     if(ptr->left != NULL)
           ptr->left->parent=ptr;
     lchild->parent = ptr->parent;
     if(ptr->parent != NULL)
     {
          if(ptr == ptr->parent->left)
                 ptr->parent->left=lchild;
          else
                 ptr->parent->right=lchild;
     }
     else
         *root = lchild;
     lchild->right = ptr;
     ptr->parent = lchild;
}
void Insert(Node **root)
{
     int item;
     Node *ptr = *root, *save = NULL,*rptr;
     printf("Enter the value of node             :");
     scanf("%d", &item);
     while(ptr != NULL)
     {
               save = ptr;
               if(ptr->info == item)
               {
                       printf("\nNode with %d value is already present in the tree",item);
                       return;
               }
               else if(ptr->info < item)
                       ptr = ptr->right;
               else
                       ptr = ptr->left;
     }
     Node *node = (Node *)malloc(1*sizeof(Node));
     node->info = item;
     node->left = NULL;
     node->right = NULL;
     node->bfactor = 0;
     if(save == NULL)
          *root = node;
     else if(item < save->info)
          save->left = node;
     else
         save->right = node;
     node->parent = save;
     ptr = node;
     while(ptr->parent)
     {
            if(ptr == ptr->parent->left)
                   ptr->parent->bfactor = ptr->parent->bfactor+1;
            else
                   ptr->parent->bfactor = ptr->parent->bfactor - 1;
            if(ptr->parent->bfactor==0)
                   return;                    
            if((ptr->parent->bfactor>1)|| (ptr->parent->bfactor<-1))
                       break;
            ptr = ptr->parent;                
     }
     ptr = ptr->parent;
     if(ptr== NULL)
              return;
     if((item >ptr->info)&& (item> ptr->right->info))
     {
                 Left_Rotation(ptr,root);  //RR Rotation
                 ptr->bfactor=ptr->parent->bfactor=0;
      }
     else if((item < ptr->info)&& (item < ptr->left->info)) // LL Rotation
     {
                 Right_Rotation(ptr,root);
                 ptr->bfactor=ptr->parent->bfactor=0;
     }
     else if((item >ptr->info)&& (item < ptr->right->info))//RL Rotation
     {
                 if(ptr->right->left->bfactor==0)
                      ptr->bfactor = ptr->right->bfactor = 0;
                 else if(ptr->right->left->bfactor==1)
                 {
                      ptr->bfactor=0;
                      ptr->right->bfactor=-1;  
                 }
                 else
                 {
                     ptr->bfactor=1;
                     ptr->right->bfactor=0;  
                 }
                 ptr->right->left->bfactor=0;
                 Right_Rotation(ptr->right,root);
                 Left_Rotation(ptr,root);        
     }
     else   //LR Rotation
     {
                 if(ptr->left->right->bfactor==0)
                      ptr->bfactor = ptr->left->bfactor = 0;
                 else if(ptr->left->right->bfactor==1)
                 {
                      ptr->bfactor=-1;
                      ptr->left->bfactor=0;  
                 }
                 else
                 {
                     ptr->bfactor=0;
                     ptr->left->bfactor=1;  
                 }
                 ptr->left->right->bfactor=0;
                 Left_Rotation(ptr->left,root);
                 Right_Rotation(ptr,root);
     }   
}
