//prim-jarnic algo
#include <stdio.h>
#include <stdlib.h>

#define N 5
#define INF 10000

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
int dist[N];

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
    p->weight=e->weight;
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

Vertex* findVertex(int v){
    Vertex *p=vHead;
    while(p->num!=v)
        p=p->next;
    return p;
}

void insertEdge(int v1, int v2,int w){
    Edge*p=(Edge*)malloc(sizeof(Edge));
    p->vNum1=v1;
    p->vNum2=v2;
    p->weight=w;
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
    v=findVertex(v2);
    insertIncidentEdge(v,v1,p);
}

int getMinVertex(){
    int v;
    Vertex *p=vHead;
    for(;p!=NULL;p=p->next)
        if(p->isFresh==0){
            v=p->num-1;
            break;
        }

    for(p=vHead;p!=NULL;p=p->next)
        if(p->isFresh==0 &&(dist[p->num-1]<dist[v]))
            v=p->num-1;

    return v;
}

void prim(Vertex*v){
    IncidentEdge *q;
    Vertex *p;
    int u;

    for(int i=0;i<N;i++)
        dist[i]=INF;
    
    dist[v->num-1]=0;

    for(int i=0;i<N;i++){
        u=getMinVertex();
        p=findVertex(u+1);
        p->isFresh=1;
        printf("[%d] ",p->num);
        for(q=p->top;q!=NULL;q=q->next){
            p=findVertex(q->adjVertex);
            if(p->isFresh==0)
                dist[q->adjVertex-1]=q->weight;
        }
    }
    
}

void print(){
    Vertex *p=vHead;
    IncidentEdge *q;
    for(;p!=NULL;p=p->next){
        printf("정점 %d: ",p->num);
        for(q=p->top;q!=NULL;q=q->next)
            printf("[%d(%d)]  ",q->adjVertex,q->weight);
        printf("\n");
    }
}


int main(){
    for(int i=0;i<N;i++)
        makeVertices();

    insertEdge(1,2,1);
    insertEdge(1,4,2);
    insertEdge(1,5,4);
    insertEdge(2,3,6);
    insertEdge(2,5,7);
    insertEdge(3,5,5);
    insertEdge(4,5,3);

    print();
    prim(vHead);
    return 0;
}