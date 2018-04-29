#include<stdio.h>

#include<unistd.h>

#include<stdlib.h>

typedef int bool;

typedef struct Node{

int id;

int time_left;

struct Node *next;

}Node;

Node* newNode(int pid,int exec_time){

Node *newnode=(Node*)malloc(sizeof(Node));

newnode->id=pid;

newnode->time_left=exec_time;

newnode->next=NULL;

return newnode;

}

bool isEmpty(Node *end){

return (end==NULL);

}

void printList(Node *end){

if(isEmpty(end))return;

Node *ptr=end->next;

while(ptr!=end){

printf("Process %d\t %d seconds left\n",ptr->id,ptr->time_left);

ptr=ptr->next;

}

printf("Process %d\t %d seconds left\n",ptr->id,ptr->time_left);

printf("\n");

}

void add(int pid,int exec_time,Node **end){

Node *newnode=newNode(pid,exec_time);

if((*end)==NULL){

newnode->next=newnode;

(*end)=newnode;

}else{

newnode->next=(*end)->next;

(*end)->next=newnode;

(*end)=newnode;

}

}

Node* createList(){

Node *end=NULL;

while(1){

int id,t;

if(scanf("%d%d",&id,&t)==EOF)break;

add(id,t,&end);

}

return end;

}

Node* removeCurrent(Node *curr,Node **end){

if(curr==NULL)return NULL;

if(curr->time_left!=0)return curr->next;

printf("Process %d has executed.\n",curr->id);

if(curr->next==curr){

//only process

free(curr);

return NULL;

}

Node *temp=curr;

Node *parent_temp=temp->next;

while(parent_temp->next!=temp)parent_temp=parent_temp->next;

parent_temp->next=temp->next;

if(curr==(*end)){

(*end)=curr->next;

}

curr=curr->next;

free(temp);

return curr;

}

Node* scanList(Node *end){

if(end==NULL)return NULL;

printList(end);

Node *curr=end->next;

while(curr!=NULL){

sleep(1);//sleep for one second

(curr->time_left)=(curr->time_left)-1;

curr=removeCurrent(curr,&end);

if(curr==NULL)end=NULL;

printList(end);

}

return NULL;

}

int main(){

Node *end=createList();

printf("\n");

printList(end);

printf("\n");

end=scanList(end);

return 0;

}

