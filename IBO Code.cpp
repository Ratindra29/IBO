/*
Ratindra Singh 

Following are the functions that can be performed
    1.Insert IBO
    2.Delete IBO
    3.Add sale score
    4.Highest scorer in each level
    5.IBO with maximum number of descendants
    6.IBO with score greater than Mentor
    7.Display tree


    [A] The root node with ID 0 has already been inserted.
        This node is the only node in level 1 and new IBOs can be inserted to this node.
        The root node cannot be deleted.

    [B] Along with IDs a tracking ID is stored within each tree node.
        This facilitates the Insertion and deletion Functions by finding the node in O(l) time complexity.
        Here l represents the level of the node to be found.
        Thus helps in Reducing time complexity.

    [C] The maximum descendants in each level are calculated only if changes like insertion and deletion are made.
        If no changes made the already computed values are displayed.

    [C]Time Complexities of each function
        1.Insertion:            Here time complexity is same as that required to find the mentor node i.e.  O(l)
                                where l represents the level of the mentor node.
                                The new node is assigned a tracking id accordingly.

        2.Deletion:             O(l) required for finding the node after which a recursive function is called
                                which changes the tracking IDs of the children of the deleted nodes.

                                The maximum limit of a node to have at most 3 children is satisfied.
                                refer to the node to be deleted as deletednode and its parent as parent node.
                                if no of children of parent(excluding deleted node) + no of children of deleted node <=3
                                Then children of deleted node become children of parent.
                                else
                                node with maximum score from deleted node's children is found, this becomes child of parent
                                and the the function is then recursively called for this maxnode and its children

        3.Add salescore:        Here complexity is  O(l) required for finding the node. This is done using a recursive function.
                                Bonus is added after every 100+ sale score. This bonus is of 10 points and is given to the IBO and its mentor

        4.Highest scorer:       Time complexity is O(n). All level wise traversals use a queue.

        5.Maximum descendants:  Time Complexity is O(n) for traversal.
                                The calculation of descendants is a recursive function and it implements DYNAMIC PROGRAMMING
                                The values of the calculated descendants is stored in a lookup table (array)
                                So the values need not be recomputed. Space complexity O(n) array.

        6.Greater score than mentor:
                                O(n-k) time complexity where k is the number of leaf nodes.











 */






#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX_Q_SIZE 100
#define MAX_NODES 100
#define MAX_HEIGHT 20


typedef struct TreeNodeTag
{
    int IBO_id;
    int tracking_id;
    int mentoring_score;
    int sale_score;
    struct TreeNodeTag *left;
    struct TreeNodeTag *middle;
    struct TreeNodeTag *right;
}treeNode;



void printGivenLevel(treeNode* root, int level);
void printLevelOrder(treeNode* root);
int InsertIBO(treeNode *root,int mentor_path,float   mul);
int height(treeNode* node);
int maxOf3(int a,int b, int c);
treeNode* MakeNode(int path);
int Insert(treeNode*root, int mentor_path);
void AddSaleScore(treeNode* root);
int salescore(treeNode *root,int path, int category ,int mul,int* bonus);
void HighestScoreInEachLevel(treeNode* root);
treeNode** createQueue(int *, int *);
void enQueue(treeNode **, int *, treeNode *);
treeNode*deQueue(treeNode **, int *);
int descendants(treeNode* root,int index);
int calculate_Descendants(treeNode* root,int index);
//void SetIndex(treeNode*root);
//int GetIndex(treeNode*node,int start);
void Max_descendants_on_each_level(treeNode* root);
int Score_greater_than_mentor(treeNode*root);
treeNode* find_parent_node(treeNode * root,int path, int* mul,int*child);
treeNode* nextchild(treeNode* parent,int i);
void Change_tracking_id(treeNode* parent, treeNode *child,int mul,int i,treeNode* deleted_node);
void Change(treeNode *parent, treeNode* deleted_node,int mul);
treeNode* find_max_node(treeNode* node,int *i);
void Delete(treeNode* root, int path);
//treeNode* Deleteroot(treeNode* root);



//_____________GLOBAL VARIABLES___________________

int des_array[MAX_NODES];
int Total_Nodes=0;
int path_Array[MAX_NODES];
int changed=0;
int Max_scorer_array[MAX_HEIGHT];







int main()
{

    treeNode* root=MakeNode(0);
    root->IBO_id=0;
    int path,id;
    int f = 0, a;
    char ch = 'y';
    for(int i=0;i<MAX_NODES;i++)
    {
        path_Array[i]=-1;
    }
    path_Array[0]=0;
    printf(  "_______________________________________________________________________________________________________\n\n");
    printf("                                    MULTILEVEL MARKETING PROBLEM\n");
    printf("\n_______________________________________________________________________________________________________\n\n");
    printf("The root node with ID 0 has already been inserted.\nThis node is the only node in level 1 and new IBOs can be inserted to this node.\nThe root node cannot be deleted.\n\n");


    while (ch == 'y'||ch == 'Y') {
        printf("Choose\n1.Insert IBO\n2.Delete IBO\n3.Add sale score\n4.Highest scorer in each level\n5.IBO with maximum number of descendants\n6.IBO with score greater than Mentor\n7.Display tree\n8.Exit\n\n");
        scanf("%d", &f);
        printf("\n-------------------------------------------------------------------------------------------------------\n\n");
        switch(f) {
            case 1 : printf("Enter ID of mentor\n");
                     scanf("%d", &id);
                     path=path_Array[id];
                     if(path==-1)
                     {
                         printf("INVALID MENTOR ID!! Insertion Failed!!\n");
                     }
                     else
                     {
                         id=Insert(root,path);
                         if(id!=-1)
                         {
                             printf("ID of new IBO   : %d\n",id);
                             printf("Path of new IBO : %d\n",path_Array[id]);
                             Total_Nodes++;
                         }
                     }
                     changed=1;
                     printf("\n-------------------------------------------------------------------------------------------------------\n\n");

                     break;
            case 2 :printf("Enter ID of mentor\n");
                     scanf("%d", &id);
                     path=path_Array[id];
                     if(path==-1)
                     {
                         printf("INVALID MENTOR ID!! Deletion Failed!!\n");
                     }
                     else
                     {
                            Delete(root,path);

                         {
                             printf("deleted\n");
                         }
                     }
                     changed=1;
                     printf("\n-------------------------------------------------------------------------------------------------------\n\n");
                     break;
            case 3 : AddSaleScore(root);
                     printf("\n-------------------------------------------------------------------------------------------------------\n\n");
                     break;
            case 4 : HighestScoreInEachLevel(root);
                     printf("\n-------------------------------------------------------------------------------------------------------\n\n");
                     break;
            case 5 : Max_descendants_on_each_level(root);
                     printf("\n-------------------------------------------------------------------------------------------------------\n\n");
                     break;
            case 6 : a=Score_greater_than_mentor(root);
                        if(a==0)
                            printf("NO RESULTS!\n");
                        printf("\n-------------------------------------------------------------------------------------------------------\n\n");

                     break;
            case 7 : printLevelOrder(root);
                     printf("\n-------------------------------------------------------------------------------------------------------\n\n");
                     break;
            case 8 : exit(1);
                     break;
            default : printf("invalid\n");
                      break;
        }
    }


return 0;
}

    int Insert(treeNode*root, int mentor_path)
{
   int id= InsertIBO(root,mentor_path,0.1);
   if(id!=-1)
   {
       if(mentor_path!=0)
       {
           root->mentoring_score+=10;
       }
   }

    return id;
}




int InsertIBO(treeNode *root,int mentor_path,float   mul)
{
    int path;
    int id;
    treeNode *node;
   // printf("entered Insert\n"); //debug
    if((root==NULL))
    {
      //  printf("root is null\n");//debug
        path=0;
        id=Total_Nodes+1;
        path_Array[id]=path;
        node=MakeNode(path);
        node->IBO_id=id;
        root=node;
    }
    else if(root->tracking_id==mentor_path)
    {
        if(root->left==NULL)
        {
            path=mul*10 + mentor_path;
            id=Total_Nodes+1;
            path_Array[id]=path;
            node=MakeNode(path);
            node->IBO_id=id;
            root->left=node;
            root->mentoring_score+=100;
        }
        else if(root->middle==NULL)
        {
            path=mul*20 + mentor_path;
            id=Total_Nodes+1;
            path_Array[id]=path;
            node=MakeNode(path);
            node->IBO_id=id;
            root->middle=node;
            root->mentoring_score+=100;
        }
        else if(root->right==NULL)
        {
            path=mul*30 + mentor_path;
            id=Total_Nodes+1;
            path_Array[id]=path;
            node=MakeNode(path);
            node->IBO_id=id;
            root->right=node;
            root->mentoring_score+=200;
        }
        else
        {
            id=-1;
            printf("Mentor can have maximum 3 children\nINSERTION FAILED!!!!!\n");
        }
    }
    else
    {
        mul=mul*100;
        int rem=mentor_path%(int)mul;
        mul=mul/10;
        if((root->left!=NULL)&&(root->left->tracking_id==rem))
        {
            id=InsertIBO(root->left,mentor_path,mul);
            if(id!=-1)
            {
                if(root->left->tracking_id!=mentor_path)
                root->left->mentoring_score+=10;
            }


        }
        else if((root->middle!=NULL)&&(root->middle->tracking_id==rem))
        {
            id=InsertIBO(root->middle,mentor_path,mul);
            if(id!=-1)
            {
                if(root->middle->tracking_id!=mentor_path)
                root->middle->mentoring_score+=10;
            }


        }
        else if((root->right!=NULL)&&(root->right->tracking_id==rem))
        {
            id=InsertIBO(root->right,mentor_path,mul);
            if(id!=-1)
            {
                if(root->right->tracking_id!=mentor_path)
                root->right->mentoring_score+=10;
            }

        }
        else
        {
            printf("Invalid mentor path\nINSERTION FAILED!!!!\n");
            id=-1;
        }
    }
    return id;
}



void HighestScoreInEachLevel(treeNode* root)
{
	int rear, front,flag=0;
	treeNode **queue = createQueue(&front, &rear);
	treeNode *temp_node = root;
	treeNode *maxnode=NULL;
	int maxscore=-1,level=1;
	//changedmaxscore=0;



	enQueue(queue,&rear,root);
	enQueue(queue,&rear,NULL);

	while (rear!=front)
	{

        temp_node= deQueue(queue,&front);

        if(temp_node==NULL)
        {
            if((flag==1))
            {
                enQueue(queue,&rear,NULL);
                printf("--------LEVEL %d-------\n",level);
                level++;
              printf("\nHIGHEST SCORER ID   : %d\n",maxnode->IBO_id);
                printf("HIGHEST SCORER path : %d\n",maxnode->tracking_id);
                printf("mentoring score     : %d\n",maxnode->mentoring_score);
                printf("sale score          : %d\n",maxnode->sale_score);
                printf("total score         : %d\n\n",maxscore);

                maxnode=NULL;
                maxscore=-1;
            }
            flag=0;
        }
		//printf("%d ", temp_node->tracking_id);
		else
        {

            if (temp_node->left)
               {
                   flag=1;
                   enQueue(queue, &rear, temp_node->left);
               }

            if (temp_node->middle)
            {
                flag=1;
                enQueue(queue, &rear, temp_node->middle);
            }

            if (temp_node->right)
            {
                flag=1;
                enQueue(queue, &rear, temp_node->right);
            }

          if((temp_node->mentoring_score+ temp_node->sale_score)>maxscore)
          {
              maxscore=(temp_node->mentoring_score+ temp_node->sale_score);
              maxnode=temp_node;
          }
         // printf("%d ", temp_node->tracking_id);
        }
	}
                printf("--------LEVEL %d-------\n",level);
              printf("\nHIGHEST SCORER ID   : %d\n",maxnode->IBO_id);
                printf("HIGHEST SCORER path : %d\n",maxnode->tracking_id);
                printf("mentoring score     : %d\n",maxnode->mentoring_score);
                printf("sale score          : %d\n",maxnode->sale_score);
                printf("total score         : %d\n\n",maxscore);

}


void Max_descendants_on_each_level(treeNode* root)
{
  //  printf("entered max des on each level\n");//debug
	int rear, front,flag=0;
	//int index=0;
	int no_of_descendants=0;
	treeNode **queue = createQueue(&front, &rear);
	treeNode *temp_node = root;
	treeNode *maxnode=NULL;
	int maxval=-1,level=1;

    if(changed==1)
    {
        for(int i=0;i<Total_Nodes;i++)
       {
           des_array[i]=-1;
       }
    }
    changed=0;
    enQueue(queue,&rear,root);
	enQueue(queue,&rear,NULL);

	while (rear!=front)
	{

        temp_node= deQueue(queue,&front);

        if(temp_node==NULL)
        {

           // printf("temp null\n");//debug

            if((flag==1))
            {
                enQueue(queue,&rear,NULL);
                printf("----------LEVEL %d-----------",level++);
              printf("\nNODE ID                : %d\n",maxnode->IBO_id);
                printf("NODE path              : %d\n",maxnode->tracking_id);
                printf("number of descendants  : %d\n",maxval);

                maxnode=NULL;
                maxval=-1;
            }
            flag=0;
        }

		else
        {

            if (temp_node->left)
               {
                   flag=1;
                   enQueue(queue, &rear, temp_node->left);
               }

            if (temp_node->middle)
            {
                flag=1;
                enQueue(queue, &rear, temp_node->middle);
            }

            if (temp_node->right)
            {
                flag=1;
                enQueue(queue, &rear, temp_node->right);
            }

            no_of_descendants=descendants(root,temp_node->IBO_id);
           // index++;
          if(no_of_descendants>maxval)
          {
              maxval=no_of_descendants;
              maxnode=temp_node;
          }
          //printf("%d ", temp_node->tracking_id);
        }
	}
                printf("----------LEVEL %d-----------",level++);
                printf("\nNODE ID                : %d\n",maxnode->IBO_id);
                printf("NODE path              : %d\n",maxnode->tracking_id);
                printf("number of descendants  : %d\n",maxval);

}



int descendants(treeNode* root,int index)
{
   if(des_array[index]!=-1)
    {
        return des_array[index];
    }
    else
    {
       return calculate_Descendants(root,index);
    }
}
int calculate_Descendants(treeNode* root,int index)
{
    int i;
   // descendants_Array[index].descendants=0;
   // printf("inside calculate des\n");//debug
   des_array[index]=0;

    if((root->left==NULL)&&(root->middle==NULL)&&(root->right==NULL))
    {
        //descendants_Array[index].descendants=0;
        des_array[index]=0;
    }
    else
    {
        if(root->left)
        {
           // i=GetIndex(root->left,index+1);
            //descendants_Array[i].descendants=calculate_Descendants(root->left,i);
           // descendants_Array[index].descendants=1+descendants_Array[i].descendants;
            i=root->left->IBO_id;
            des_array[i]=calculate_Descendants(root->left,i);
            des_array[index]+=1+des_array[i];
        }
        if(root->middle)
        {
//            i=GetIndex(root->middle,i+1);
//            descendants_Array[i].descendants=calculate_Descendants(root->middle,i);
//            descendants_Array[index].descendants+=1+descendants_Array[i].descendants;
                i=root->middle->IBO_id;
                des_array[i]=calculate_Descendants(root->middle,i);
                des_array[index]+=1+des_array[i];
        }

        if(root->right)
        {
//            i=GetIndex(root->right,i+1);
//            descendants_Array[i].descendants=calculate_Descendants(root->right,i);
//            descendants_Array[index].descendants+=1+descendants_Array[i].descendants;
            i=root->right->IBO_id;
            des_array[i]=calculate_Descendants(root->right,i);
            des_array[index]+=1+des_array[i];
        }


    }
   // return descendants_Array[index].descendants;
   //printf("descendants of %d is %d\n",root->tracking_id,des_array[index]);//debug
   return des_array[index];
}


int Score_greater_than_mentor(treeNode*root)
{
    int rear, front;
	treeNode **queue = createQueue(&front, &rear);
	treeNode *temp_node = root;
	int retval=0;

	enQueue(queue,&rear,root);


	while ((temp_node!=NULL)&&(rear!=front))
	{

        temp_node= deQueue(queue,&front);
        //printf("%d\t",temp_node->tracking_id);//debug

            if (temp_node->left)
            {
                enQueue(queue, &rear, temp_node->left);
                if((temp_node->left->mentoring_score + temp_node->left->sale_score)>(temp_node->mentoring_score + temp_node->sale_score))
                {
                    printf("IBO ID                :%d\n",temp_node->left->IBO_id);
                    printf("IBO path              :%d\n",temp_node->left->tracking_id);
                    printf("mentoring score       :%d\n",temp_node->left->mentoring_score);
                    printf("sale score            :%d\n",temp_node->left->sale_score);
                    printf("total score           :%d\n",(temp_node->left->mentoring_score+temp_node->left->sale_score));
                    printf("mentor's total score  :%d\n\n",(temp_node->mentoring_score + temp_node->sale_score));
                    retval++;
                }
            }

            if (temp_node->middle)
                {
                enQueue(queue, &rear, temp_node->middle);
                if((temp_node->middle->mentoring_score + temp_node->middle->sale_score)>(temp_node->mentoring_score + temp_node->sale_score))
                {
                    printf("IBO ID            :%d\n",temp_node->middle->IBO_id);
                    printf("IBO path          :%d\n\n",temp_node->middle->tracking_id);
                    printf("mentoring score       :%d\n",temp_node->middle->mentoring_score);
                    printf("sale score            :%d\n",temp_node->middle->sale_score);
                    printf("total score           :%d\n",(temp_node->middle->mentoring_score+temp_node->middle->sale_score));
                    printf("mentor's total score  :%d\n\n",(temp_node->mentoring_score + temp_node->sale_score));
                    retval++;
                }
            }
            if (temp_node->right)
                {
                enQueue(queue, &rear, temp_node->right);
                if((temp_node->right->mentoring_score + temp_node->right->sale_score)>(temp_node->mentoring_score + temp_node->sale_score))
                {
                    printf("IBO ID            :%d\n",temp_node->right->IBO_id);
                    printf("IBO path          :%d\n\n",temp_node->right->tracking_id);
                    printf("mentoring score       :%d\n",temp_node->right->mentoring_score);
                    printf("sale score            :%d\n",temp_node->right->sale_score);
                    printf("total score           :%d\n",(temp_node->right->mentoring_score+temp_node->right->sale_score));
                    printf("mentor's total score  :%d\n\n",(temp_node->mentoring_score + temp_node->sale_score));
                    retval++;
                }
            }



	}
    return retval;
}

treeNode* find_parent_node(treeNode * root,int path, int* mul,int*child)
{
    treeNode* parent_node;

    if(path!=0)
    {
        if((root->left)&& root->left->tracking_id==path)
        {
            parent_node=root;
            path_Array[root->left->IBO_id]=-1;
            *child=1;
        }
        else if((root->middle)&&root->middle->tracking_id==path)
        {
            parent_node=root;
            path_Array[root->middle->IBO_id]=-1;
            *child=2;
        }
        else if((root->right)&&root->right->tracking_id==path)
        {
            parent_node=root;
            path_Array[root->right->IBO_id]=-1;
            *child=3;
        }
        else
        {
            int rem=path%(int)(*mul);
            *mul=(*mul)*10;
            if((root->left!=NULL)&&(root->left->tracking_id==rem))
            {
                parent_node=find_parent_node(root->left,path,mul,child);

            }
            else if((root->middle!=NULL)&&(root->middle->tracking_id==rem))
            {
                 parent_node=find_parent_node(root->middle,path,mul,child);
            }
            else if((root->right!=NULL)&&(root->right->tracking_id==rem))
            {
                 parent_node=find_parent_node(root->right,path,mul,child);
            }

        }
    }
    else
    {
        parent_node=root;
    }

    return parent_node;

}
//treeNode* Deleteroot(treeNode* root)
//{
//
//}
void Delete(treeNode* root, int path)
{
    int child=0,mul=10;

    treeNode* parent_node=find_parent_node(root,path,&mul,&child);
  //  printf("mul %d child %d\n",mul,child);//debug

    treeNode* deleted_node;
    if(child==1)
    {
            deleted_node=parent_node->left;
            parent_node->left=NULL;
    }
    else if(child==2)
    {
            deleted_node=parent_node->middle;
            parent_node->middle=NULL;
    }
    else if(child==3)
    {
            deleted_node=parent_node->right;
            parent_node->right=NULL;
    }

    Change(parent_node,deleted_node,10);
    path_Array[deleted_node->IBO_id]=-1;
    free(deleted_node);

}

treeNode* find_max_node(treeNode* node,int *i)
{
    int a=-1,b=-1,c=-1;
    if(node->left)(a=node->left->mentoring_score+node->left->sale_score);
    if(node->middle)(b=node->middle->mentoring_score+node->middle->sale_score);
    if(node->right)(c=node->right->mentoring_score+node->right->sale_score);
    int max=maxOf3(a,b,c);
    if(a==max)
    {
        *i=1;
        return node->left;
    }
    if(b==max)
    {
        *i=2;
        return node->middle;
    }
    if(c==max)
    {
        *i=3;
        return node->right;
    }
}
int no_of_children(treeNode* parent_node)
{
    int i=0;
    if(parent_node->left) i++;
    if(parent_node->middle)i++;
    if(parent_node->right)i++;
    return i;
}

void Change(treeNode *parent, treeNode* deleted_node,int mul)
{


    int parent_children=no_of_children(parent);
    int deleted_node_children= no_of_children(deleted_node);
 //   printf("entered change parent path %d deleted node path %d noOfChildren deleted node %d\n",parent->tracking_id,deleted_node->tracking_id,deleted_node_children);
    if(parent_children+deleted_node_children<=3)
    {

        int i=1,j=0;
        if(j<deleted_node_children)
           {
                if(parent->left==NULL)
            {

                parent->left=nextchild(deleted_node,i);
             // if(parent->left)  printf("i %d    j %d    new lchild %d",i,j,parent->left->tracking_id);
                Change_tracking_id(parent,parent->left,10,1,deleted_node);

                i++;j++;
            }
           }
        if(j<deleted_node_children)
        {
            if(parent->middle==NULL)
            {
                parent->middle=nextchild(deleted_node,i);
               // if(parent->middle) printf("i %d    j %d    new mchild %d",i,j,parent->middle->tracking_id);
                Change_tracking_id(parent,parent->middle,10,2,deleted_node);
                i++;j++;
            }
        }
        if(j<deleted_node_children)
        {
             if(parent->right==NULL)
            {
                parent->right=nextchild(deleted_node,i);
              //  if(parent->right) printf("i %d    j %d    new rchild %d",i,j,parent->right->tracking_id);
                Change_tracking_id(parent,parent->right,10,3,deleted_node);
                i++;j++;
            }
        }
    }

    else
    {

        int i;
        treeNode* maxnode=find_max_node(deleted_node,&i);
        i==1?(deleted_node->left=NULL):(i==2?(deleted_node->middle=NULL):(deleted_node->right=NULL));
        if(parent->left==NULL)
        {
            parent->left=maxnode;
           //  if(maxnode)printf("   new lchild %d",parent->left->tracking_id);
            Change_tracking_id(parent,maxnode,10,1,deleted_node);
        }
        else if(parent->middle==NULL)
        {
            parent->middle=maxnode;
           // if(maxnode)printf("   new lchild %d",parent->middle->tracking_id);
            Change_tracking_id(parent,maxnode,10,2,deleted_node);
        }
        else if(parent->right==NULL)
        {
            parent->right=maxnode;
           // if(maxnode)printf("   new lchild %d",parent->right->tracking_id);
            Change_tracking_id(parent,maxnode,10,3,deleted_node);
        }

        Change(maxnode,deleted_node,mul);

    }
}

void Change_tracking_id(treeNode* parent, treeNode *child,int mul,int i,treeNode* deleted_node)
{

   if(child!=NULL)
   {
       while(mul<parent->tracking_id)
       {
           mul=mul*10;
       }
       //mul=mul*10;
       if(parent->IBO_id==0)
        child->tracking_id=i;
//       else if(deleted_node)
//        child->tracking_id=deleted_node->tracking_id;
       else
        child->tracking_id=(i*mul)+parent->tracking_id;
        path_Array[child->IBO_id]=child->tracking_id;
       //printf("inside change id mul %d path %d newchild id %d\n",mul,parent->tracking_id,child->tracking_id);
       Change_tracking_id(child,child->left,mul,1,NULL);
       Change_tracking_id(child,child->middle,mul,2,NULL);
       Change_tracking_id(child,child->right,mul,3,NULL);
   }


}

treeNode* nextchild(treeNode* parent,int i)
{
    int n=0;
    while(n<3)
    {
            if(i==1)
        {
            if(parent->left)return parent->left;
            else i=2; n++;
        }
         if(i==2)
        {
            if(parent->middle)return parent->middle;
            else i=3;n++;
        }
         if(i==3)
        {
            if(parent->right)return parent->right;
            else i=1;n++;
        }
    }


        return NULL;
}




//UTILITY FUNCTIONS FOR QUEUE
treeNode** createQueue(int *front, int *rear)
{
	treeNode **queue =
		(treeNode **)malloc(sizeof(treeNode*)*MAX_Q_SIZE);

	*front = *rear = 0;
	return queue;
}

void enQueue(treeNode **queue, int *rear, treeNode *new_node)
{
	queue[*rear] = new_node;
	(*rear)++;
}

treeNode*deQueue(treeNode **queue, int *front)
{
	(*front)++;
	return queue[*front - 1];
}


void AddSaleScore(treeNode* root)
{
    int path, category,id;
    printf("\nEnter ID of node               : ");
    scanf("%d",&id);
    while(path_Array[id]==-1)
    {
        printf("Invalid ID!! Re-enter ID     : ");
        scanf("%d",&id);
    }
    path=path_Array[id];
    printf("Enter category between 1 and 5 : ");
    scanf("%d",&category);
    while((category<1)||(category>5))
    {
        printf("Invalid category!! Re-enter    : ");
        scanf("%d",&category);
    }
    int bonus=0;
        path=salescore(root,path,category,10,&bonus);
//    if(path==-1)
//    {
//        printf("\nInvalid path!!! failed!!\n");
//    }
//    else
    {
        printf("\nSale score updated successfully\n");
        if(path==1)
        {
            printf("YAY!! BONUS 10 added to IBO and mentor on crossing another 100 sales!!\n");
        }
    }

}


int salescore(treeNode *root,int path, int category, int mul,int *bonus)
{
    int retval=0,initialscore;
    if(root->tracking_id==path)
    {
        initialscore=root->sale_score;
        //a=initialscore/100 + 1;
        root->sale_score+=(category*10);
        if((root->sale_score/100)>(initialscore/100))//bonus after every 100 sales
        {
            root->sale_score+=10;
            *bonus=1;
            retval=1;
        }

    }
    else
    {
       // mul=mul*100;
        int rem=path%(int)mul;
       // mul=mul/10;
       mul=mul*10;
        if((root->left!=NULL)&&(root->left->tracking_id==rem))
        {
            retval=salescore(root->left,path,category,mul,bonus);
            if(*bonus==1)
            {
                root->sale_score+=10;
                *bonus=0;
            }
        }
        else if((root->middle!=NULL)&&(root->middle->tracking_id==rem))
        {
            retval=salescore(root->middle,path,category,mul,bonus);
            if(*bonus==1)
            {
                root->sale_score+=10;
                *bonus=0;
            }
        }
        else if((root->right!=NULL)&&(root->right->tracking_id==rem))
        {
            retval=salescore(root->right,path,category,mul,bonus);
            if(*bonus==1)
            {
                root->sale_score+=10;
                *bonus=0;
            }
        }
        else
        {
           // printf("INVALID path!! failed!!\n");
            retval=-1;
        }
    }
     return retval;
}






    treeNode* MakeNode(int path)
{
    treeNode* ptr=(treeNode*)malloc(sizeof(treeNode));
    ptr->tracking_id=path;
    ptr->IBO_id=-1;
    ptr->mentoring_score=0;
    ptr->sale_score=0;
    ptr->left=NULL;
    ptr->middle=NULL;
    ptr->right=NULL;
    return ptr;
}


int maxOf3(int a,int b, int c)
{
    if(a>b)
    {
        if(a>c)
            return a;
        else
            return c;
    }
    else
    {
        if(b>c)
            return b;
        else
            return c;
    }
}

//int height(treeNode* node)
//{
//    if (node==NULL)
//        return 0;
//    else
//    {
//        /* compute the height of each subtree */
//        int lheight = height(node->left);
//        int mheight = height(node->middle);
//        int rheight = height(node->right);
//
//        /* use the larger one */
//        return (maxOf3(lheight,mheight,rheight)+1);
//    }
//}



//
//void printLevelOrder(treeNode* root)
//{
//    int h = height(root);
//   // printf("height %d\n",h);//debug
//    int i;
//
//    for (i=1; i<=h; i++)
//        {
//            printf("----------LEVEL %d---------\n",i);
//            printGivenLevel(root, i);
//        }
//}

//void printGivenLevel(treeNode* root, int level)
//{
//    if (root == NULL)
//        return;
//    if (level == 1)
//      {
//        printf("IBO ID          : %d\n", root->IBO_id);
//        printf("IBO path        : %d\n", root->tracking_id);
//        printf("mentoring score : %d\n",root->mentoring_score);
//        printf("sale score      : %d\n\n",root->sale_score);
//      }
//    else if (level > 1)
//    {
//        printGivenLevel(root->left, level-1);
//        printGivenLevel(root->middle, level-1);
//        printGivenLevel(root->right, level-1);
//    }
//}



void printLevelOrder(treeNode* root)
{
	int rear, front,flag=0;
	treeNode **queue = createQueue(&front, &rear);
	treeNode *temp_node = root;

	int level=1;



	enQueue(queue,&rear,root);
	enQueue(queue,&rear,NULL);
	printf("--------LEVEL %d-------\n",level);
	level++;

	while (rear!=front)
	{

        temp_node= deQueue(queue,&front);

        if(temp_node==NULL)
        {
            if((flag==1))
            {
                enQueue(queue,&rear,NULL);
                printf("--------LEVEL %d-------\n",level);
                level++;
            }
            flag=0;
        }
		//printf("%d ", temp_node->tracking_id);
		else
        {

            if (temp_node->left)
               {
                   flag=1;
                   enQueue(queue, &rear, temp_node->left);
               }

            if (temp_node->middle)
            {
                flag=1;
                enQueue(queue, &rear, temp_node->middle);
            }

            if (temp_node->right)
            {
                flag=1;
                enQueue(queue, &rear, temp_node->right);
            }

           // printf("--------LEVEL %d-------\n",level);
            printf("\nIBO ID              : %d\n",temp_node->IBO_id);
            printf("IBO path            : %d\n",temp_node->tracking_id);
            printf("mentoring score     : %d\n",temp_node->mentoring_score);
            printf("sale score          : %d\n",temp_node->sale_score);


         // printf("%d ", temp_node->tracking_id);
        }
	}

}
