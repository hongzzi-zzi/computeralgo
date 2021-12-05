#include <stdio.h>
#include <stdlib.h>

//dfsㅡ를특화한위상정렬은 넘어감

//14.c에서 복붙해옴
typedef struct Edge{
    int vNum1;
    int vNum2;
    struct Edge *next;
}Edge;

typedef struct IncidentEdge{
    int adjVertex;//인접정점
    Edge *e;
    struct IncidentEdge *next;
}IncidentEdge;

typedef struct Vertex{
    int num;
    int isFresh;
    struct Vertex *next;
    IncidentEdge *top;
}Vertex;

Vertex *vHead=NULL;
Edge *eHead=NULL;
int vCnt;
int eCnt;
int in[6];

//원형큐도 복붙(스택으로해도댐)
#define N 10

typedef struct{
    int element[N];//배열로구현
    int front, rear;
}Queue;

void initQueue(Queue *Q){
    Q->front=0;
    Q->rear=0;
}

int isEmpty(Queue *Q){
    return Q->rear==Q->front;
}

int isFull(Queue *Q){
    return (Q->rear+1)%N==Q->front;
}

void enqueue(Queue *Q, int elem){//char elem?뭐지 int가 맞는거같은디
    if(isFull(Q)){
        printf("FULL\n");
        return;
    }
    Q->rear=(Q->rear+1)%N;
    Q->element[Q->rear]=elem;
}

int dequeue(Queue *Q){
    if(isEmpty(Q)){
        printf("EMPTY\n");
        return -1;
    }
    Q->front=(Q->front+1)%N;
    return Q->element[Q->front];
}


void makeVertices(){
    Vertex *p=(Vertex*)malloc(sizeof(Vertex));
    p->num=++vCnt;
    p->top=NULL;
    p->next=NULL;
    p->isFresh=0;
    Vertex *q=vHead;
    if(q==NULL)
        vHead=p;
    else{
        while(q->next!=NULL)
            q=q->next;
        q->next=p;
    }
}

void insertIncidentEdge(Vertex *v ,int av, Edge *e){
    IncidentEdge *p=(IncidentEdge*)malloc(sizeof(IncidentEdge));
    p->adjVertex=av;
    p->e=e;
    p->next=NULL;
    IncidentEdge *q=v->top;
    if(q==NULL)
        v->top=p;
    else{
        while(q->next!=NULL)
            q=q->next;
        q->next=p;
    }
}

Vertex *findVertex(int v){
    Vertex *p=vHead;
    while(p->num!=v)
        p=p->next;
    return p;
}

void insertEdge(int v1, int v2){
    Edge*p=(Edge*)malloc(sizeof(Edge));
    p->vNum1=v1;
    p->vNum2=v2;
    p->next=NULL;
    Edge *q=eHead;
    if(q==NULL)
        eHead=p;
    else{
        while(q->next!=NULL)
            q=q->next;
        q->next=p;
    }
    Vertex *v=findVertex(v1);
    insertIncidentEdge(v,v2,p);
    //방향있으니까 한번만 함
    //방향없으면 밑에코드도 추가
    // v=findVertex(v2);
    // insertIncidentEdge(v,v1,p);
}

void inDegree(){
    Vertex *p=vHead;
    IncidentEdge *q;
    for(;p!=NULL;p=p->next)
        for(q=p->top;q!=NULL;q=q->next)
            in[q->adjVertex-1]++;
}

void topologicalSort(){//위상정렬
    Queue q;
    initQueue(&q);
    Vertex *p;
    IncidentEdge *r;
    inDegree();

    for(int i=0;i<6;i++)
        if(in[i]==0)
            enqueue(&q, i+1);
        
    while(!isEmpty(&q)){
        int w=dequeue(&q);
        printf("[%d] ",w);
        p=findVertex(w);
        r=p->top;
        while(r!=NULL){
            in[r->adjVertex-1]--;
            if(in[r->adjVertex-1]==0)
                enqueue(&q, r->adjVertex);
            r=r->next;
        }
    }
}

void print(){
    Vertex *p=vHead;
    IncidentEdge *q;
    for(;p!=NULL;p=p->next){
        printf("정점 %d: ",p->num);
        for(q=p->top;q!=NULL;q=q->next)
            printf("[%d]  ",q->adjVertex);
        printf("\n");
    }
}

int main(){
    for(int i=0;i<6;i++)
        makeVertices();
        
    insertEdge(1,2);
    insertEdge(1,5);
    insertEdge(2,3);
    insertEdge(4,5);
    insertEdge(5,2);
    insertEdge(5,3);
    insertEdge(5,6);
    insertEdge(6,3);

    print();

    topologicalSort();
    return 0;
}