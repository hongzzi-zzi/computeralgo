#include <stdio.h>
#include <stdlib.h>

typedef struct Edge{
    int vNum1;
    int vNum2;
    int isTree;//만들어는놨는데 사용은안함
    //필요하면 int weight;
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
    p->isTree=0;
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

void dfs(Vertex *v){
    IncidentEdge *q;
    if(v->isFresh==0){
        printf("[%d] ",v->num);
        v->isFresh=1;
    }
    for(q=v->top;q!=NULL;q=q->next){
        v=findVertex(q->adjVertex);
        if(v->isFresh==0)
            dfs(v);
    }
}

// void bfs(Vertex *v){//뭔가이상해...
//     IncidentEdge *q;
//     Vertex *p;
//     if(v->isFresh==0){
//         printf("[%d] ",v->num);
//         v->isFresh=1;
//     }
//     while(v!=NULL){
//         for(q=v->top;q!=NULL;q=q->next){
//             p=findVertex(q->adjVertex);
//             if(p->isFresh==0){
//                 printf("[%d] ",p->num);
//                 p->isFresh=1;
//             }
//         }
//         v=v->next;
//         bfs(v);
//     }
// }

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
    for(int i=0;i<9;i++)
        makeVertices();
    insertEdge(1,2);
    insertEdge(1,3);
    insertEdge(2,4);
    insertEdge(2,5);
    insertEdge(3,5);
    insertEdge(3,6);
    insertEdge(4,7);
    insertEdge(5,7);
    insertEdge(5,8);
    insertEdge(6,8);
    insertEdge(7,9);
    insertEdge(8,9);


    print();

    dfs(vHead);

    // insertEdge(1,3);
    // insertEdge(1,4);
    // insertEdge(1,6);
    // insertEdge(2,3);
    // insertEdge(2,5);
    // insertEdge(3,4);
    // insertEdge(4,6);
    // insertEdge(5,6);

    // bfs(vHead);

    return 0;
}