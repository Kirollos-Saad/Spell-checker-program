#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char*word;
    struct Node *right,*left;
} Node;
Node* New_Node(char*str)
{
    Node *n=malloc(sizeof(Node));
    n->word=malloc(strlen(str)+1);
    strcpy(n->word,str);
    n->right=n->left=NULL;
    return n;
}
Node* Insert_Node(Node*root,char*str)
{
    if(!root) return New_Node(str);
    if((strcasecmp(str, root->word))<0)
        root->left= Insert_Node(root->left, str);
    else if ((strcasecmp(str, root->word))>0)
        root->right=Insert_Node(root->right,str);
    return root;
}

Node* Search(Node*root,char*key, Node**p)
{
    if(!root||!strcasecmp(root->word, key))
        return root;
    else if((strcasecmp(key, root->word))<0)
    {
        if(!root->left)
            *p=root;
        return Search(root->left, key,p);
    }
    else
    {
        if(!root->right)
            *p=root;
        return Search(root->right,key,p);
    }

}
Node*Get_Min(Node*root)
{
    if(!root||!root->left)  return root;
    return Get_Min(root->left);
}
Node* Get_Max(Node*root)
{
    if(!root||!root->right)	return root;
    return Get_Max(root->right);
}
Node* Get_Successor(Node*root,Node*n)
{
    if (!root||!n) return NULL;
    if(n->right)
        return Get_Min(n->right);
    Node*current=root;
    Node*successor=NULL;
    while(current&&current!=n)
    {
        if((strcasecmp(n->word,current->word))<0)
        {
            successor=current;
            current=current->left;
        }
        else
            current=current->right;
    }
    return successor;
}
Node*Get_Predecessor(Node*root,Node*n)
{
    if (!root||!n) return NULL;
    if(n->left)
        return Get_Max(n->left);
    Node*current=root;
    Node*predecessor=NULL;
    while(current&&current!=n)
    {
        if(strcasecmp(n->word,current->word)<0)
            current=current->left;
        else
        {
            predecessor=current;
            current=current->right;
        }
    }
    return predecessor;
}
int count (Node *t)
{
    if (t==NULL) return 0;
    else
        return 1+ count(t->left)+count(t->right);
}
int max (int x,int y)
{
    return x>y? x:y;
}
int height(Node *t)
{
    if (t==NULL) return -1;
    else
        return 1+ max(height(t->left),height(t->right)) ;
}
Node *loadfile(char *filename)
{
    FILE *f=fopen(filename,"r");
    if(!f)
    {
        printf("Error Loading the dictionary \n");
        return NULL;
    }
    Node*root=NULL;
    char str[100];
    while(!feof(f))
    {
        fscanf(f,"%s\n",str);
        root=Insert_Node(root, str);
    }
    fclose(f);
    printf("Dictionary Loaded Successfully...!\n");
    printf("..................................\n");
    printf("Size = %d\n", count(root));
    printf("..................................\n");
    printf("Height = %d\n", height(root));
    printf("..................................\n");
    return root;
}
void Check(Node*root,char*str)
{
    Node* buffer=NULL;
    Node* Pred = NULL;
    Node* succ = NULL;
    printf("%s -\t",str);
    if(Search(root, str,&buffer ))
        printf("Correct");
    else
    {
        Pred = Get_Predecessor(root,buffer);
        succ = Get_Successor(root,buffer);
        printf("Incorrect,Suggestions : %s ",buffer->word);
        if(Pred)
            printf("%s ",Pred->word);
        if(succ)
            printf("%s",succ->word);
    }
    printf("\n");
}
void Check_String(Node*root,char*str)
{
    char * token = strtok(str," ");
    while(token)
    {
        Check(root,token);;
        token=strtok(NULL," ");
    }
}

int main ()
{
    Node*root=loadfile("EN-US-Dictionary.txt");
    if(!root)
    {
        printf("ERROR\n");
        exit(-1);
    }
    char str [1000];
    printf("Enter a sentence :");
    gets(str);
    Check_String(root,str);

    return 0;
}
