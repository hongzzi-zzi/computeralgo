#include <stdio.h>
#include <stdlib.h>

#define N 7

typedef struct Edge{
    int vNum1;
    int vNum2;
    int weight;
    struct Edge *next;
}Edge;

typedef struct IncidentEdge{
    int adjVertex;//인접정점
    int weight;
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

void insertEdge(int v1, int v2,int weight){
    Edge*p=(Edge*)malloc(sizeof(Edge));
    p->vNum1=v1;
    p->vNum2=v2;
    p->weight=weight;
    p->next=NULL;
    Edge *q=eHead;
    if(q==NULL)
        eHead=p;
    else{
        while(q->next!=NULL)
            q=q->next;
        q->next=p;
    }
    //무방향그래프니까 2번
    Vertex *v=findVertex(v1);
    insertIncidentEdge(v,v2,p);
    v=findVertex(v2);
    insertIncidentEdge(v,v1,p);
}

Edge* e[14];
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

void printEdge(){
    Edge *p=eHead;
    int i=0;
    for(;p!=NULL;p=p->next)
        e[i++]=p;
    
    //오름차순정렬
    int least;
    Edge *temp;
    for(i=0;i<13;i++){
        least=i;
        for(int j=i+1;j<14;j++)
            if(e[j]->weight < e[least]->weight)
                least=j;
        SWAP(e[i],e[least],temp);
    }

    for(i=0;i<14;i++)
        printf("[%d - %d (%d)]",e[i]->vNum1,e[i]->vNum2,e[i]->weight);
    printf("\n");
}

int v[N];
void initSet(){
    for(int i=0;i<N;i++)
        v[i]=-1;
}


int vFind(int vNum){
    if(v[vNum]==-1)
        return vNum;
    while(v[vNum]!=-1)
        vNum=v[vNum];
    return vNum;
}

void vUnion(int vNum1, int vNum2){
    int r1=vFind(vNum1);
    int r2=vFind(vNum2);

    if(r1!=r2)
        v[r2]=r1;
    
}

void kruskal(){
    int eCnt=0;
    int v1, v2;
    int i=0;//배열인덱스
    initSet();
    Edge *p;
    while(eCnt<N){
        p=e[i];
        v1=vFind(p->vNum1-1);
        v2=vFind(p->vNum2-1);

        if(v1!=v2){
            printf("간선 [%d -%d (%d)] 선택\n",p->vNum1,p->vNum2,p->weight);
            eCnt++;
            vUnion(v1, v2);
        }
        i++;
    }
}

int main(){
    for(int i=0;i<N;i++)
        makeVertices();
    
    insertEdge(1,2,10);insertEdge(1,3,15);insertEdge(1,4,8);insertEdge(1,5,27);
    insertEdge(2,4,25);insertEdge(2,5,4);
    insertEdge(3,4,13);insertEdge(3,6,32);insertEdge(3,7,8);
    insertEdge(4,5,10);insertEdge(4,6,19);insertEdge(4,7,22);
    insertEdge(5,7,25);
    insertEdge(6,7,15);

    printEdge();
    kruskal();
    return 0;
}