#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
struct node
{
       int value;
       node *left, *right,*parent;
};
typedef struct node Node;
Node *Search(Node *, int);
void Insert(Node **);
void Delete(Node **, Node **);
void InOrder(Node *);
void createBST(Node *);
int check(Node *);
Node *inpredecessor(Node *);
int main()
{
    Node *root = NULL;
    int ch;
    while(1)
    {
            printf("\n1:To create a BST\n2:To Insert a node into BST\n3: To Delete a node from BST\n4:Inorder Traversal of BST\n5:Exit\n");
            scanf("%d",&ch);
            switch(ch)
            {
                      case 1: 
				           {
				              Node *node = (Node *)malloc(1*sizeof(Node));
				              root = node;
				              node->parent = NULL;
                              createBST(node);
				              break;
				           }
                      case 2: Insert(&root);
                              break;
                      case 3: 
                            {  int item;
                              printf("\nEnter the node value to be deleted      :");
                              scanf("%d",&item);
                              Node *node = Search(root, item);
                              Delete(&root, &node);
                              break;
                            }
                      case 4: InOrder(root);
                              break;
                      case 5: exit(0);          
            }
    }
}
Node *Search(Node *root, int item)
{
     Node *loc = NULL;
     while(root != NULL)
     {
         if(root->value == item)
         {
                loc = root;
                break;
         }
         else if(root->value < item)
                root = root->right;
         else
                root = root->left;
     }
     return(loc);
}
void Insert(Node **root)
{
     int item;
     Node *ptr = *root, *save = NULL;
     printf("Enter the value of node             :");
     scanf("%d", &item);
     while(ptr != NULL)
     {
               save = ptr;
               if(ptr->value == item)
               {
                       printf("\nNode with %d value is already present in the tree",item);
                       return;
               }
               else if(ptr->value < item)
                       ptr = ptr->right;
               else
                       ptr = ptr->left;
     }
     Node *node = (Node *)malloc(1*sizeof(Node));
     node->value = item;
     node->left = NULL;
     node->right = NULL;
     if(save == NULL)
     {
             node->parent = NULL;
             *root = node;
     }
     else if(item < save->value)
          save->left = node;
     else
         save->right = node;
     node->parent = save;       
}
void Delete(Node **root, Node **node)
{
      if(*root == NULL)
      {
              printf("\nBST is Empty");
              return;
      }
      else if(*node == NULL)
      {
           printf("\nNode with value is not found in BST");
           return;
      }
      else if(*node != NULL)
      {
           if((*node)->parent == NULL)
           {
                   if(((*node)->left == NULL) && ((*node)->right == NULL))
                   {
                                  *root = NULL;
                                  free(node);
                   }
                   else if(((*node)->left == NULL) || ((*node)->right == NULL))
                   {
                        if((*node)->left != NULL)
                              *root = (*root)->left;
                        else
                              *root = (*root)->right;
                        (*root)->parent = NULL;
                        free(node);
                   }
                   else
                   {
                                   Node *predecessor = inpredecessor(*node);
                                   (*node)->value = predecessor->value;
                                   Delete(root,&predecessor);
                   }     
           }
           else
           {
                   if(((*node)->left == NULL) && ((*node)->right == NULL))
                   {
                         if((*node)->parent->left == *node)
                                (*node)->parent->left = NULL;
                         else
                                (*node)->parent->right = NULL;
                         free(*node);
                   }
                   else if(((*node)->left == NULL) || ((*node)->right == NULL))
                   {
                        if((*node)->left != NULL)
                        {
                              if((*node)->parent->left == *node)
                                      (*node)->parent->left = (*node)->left;
                              else
                                      (*node)->parent->right = (*node)->left;
                              (*node)->left->parent = (*node)->parent;
                        }
                        else
                        {
                              if((*node)->parent->left == *node)
                                     (*node)->parent->left = (*node)->right;
                              else
                                     (*node)->parent->right = (*node)->right;
                              (*node)->right->parent = (*node)->parent;
                        }
                        free(*node);
                   }
                   else
                   {
                               Node *predecessor = inpredecessor(*node);
                               (*node)->value = predecessor->value;
                               Delete(root,&predecessor);
                   }
           }
      }
      //printf("\n%d has been deleted from BST successfully", item);
}
void InOrder(Node *root)
{
     Node *stack[10];
     int top = 0;
     stack[top] = NULL;
     printf("\n\nInOrder Traversal of Binary Tree is              :  ");
     while(root != NULL)
     {
             sos :   
             while(root != NULL)
             {
                        top++;
                        stack[top] = root;      
                        root = root->left;
             }
             root = stack[top];
             top--;
             while(root != NULL)
             {
                       printf("  %d", root->value);          
                       if(root->right != NULL)
                       {
                           root = root->right;
                           goto sos;    
                       }
                       root = stack[top];
                       top--; 
             }   
     }
}
Node *inpredecessor(Node *ptr)
{
     ptr = ptr->left;
     while(ptr->right != NULL)
             ptr = ptr->right;
     return(ptr);
}                     
void createBST(Node *ptr)
{
	char ch;
        if(ptr->parent == NULL)
	{
		printf("\nEnter the value of Node	:");
		scanf("%d",&ptr->value);
	}
	else
	{
		do
		{
			printf("\nEnter the value of Node	:");
		        scanf("%d",&ptr->value);
		}while(check(ptr));
	}
	printf("\nNode %d has left child (Y/N)	:", ptr->value);
	ch = getche();
	fflush(stdin);
	if(ch == 'y' || ch == 'Y')
	{
		Node *leftchild = (Node *)malloc(1*sizeof(Node));
		leftchild->parent = ptr;
		ptr->left = leftchild; 
		createBST(leftchild);
	}
	else
		ptr->left = NULL;
	printf("\nNode %d has right child (1/0)	:", ptr->value);
	ch = getche();
	fflush(stdin);
	if(ch == 'y' || ch == 'Y')
	{
		Node *rightchild = (Node *)malloc(1*sizeof(Node));
		rightchild->parent = ptr;
		ptr->right = rightchild; 
		createBST(rightchild);
	}
	else
		ptr->right = NULL;	
}
int check(Node *ptr)
{
	if(ptr == ptr->parent->left)
	{
		if(ptr->value > ptr->parent->value)
		{
			printf("\nLeft child node must be less than the Parent node");
			return 1;		
		}	
	}
	else
	{
		if(ptr->value < ptr->parent->value)
		{
			printf("\nRight child node must be greater than the Parent node");
			return 1;
		}
	}
	return 0;
}
