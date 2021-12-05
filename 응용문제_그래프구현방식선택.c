#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct Vertex{
    int no;
    int weight;
    struct Vertex *next;
}Vertex;

typedef struct{
    int vCnt;
    Vertex *v[N];
}Graph;

void init(Graph *G){
    G->vCnt=0;
    for(int i=0;i<N;i++)
        G->v[i]=NULL;
}

void makeVerTex(Graph *G){
    G->vCnt++;
}

void insertEdge(Graph *G, int w, int v1, int v2){
    Vertex *p=(Vertex*)malloc(sizeof(Vertex));
    p->weight=w;
    p->no=v1+1;
    p->next=G->v[v2];
    G->v[v2]=p;

    Vertex *q=(Vertex*)malloc(sizeof(Vertex));
    q->weight=w;
    q->no=v2+1;
    q->next=G->v[v1];
    G->v[v1]=q;
}

void print(Graph *G){
    for(int i=0;i<G->vCnt;i++){
        Vertex*v=G->v[i];
        printf("V[%d] : ",i+1);
        while(v!=NULL){
            printf("[%d (%d)] ",v->no, v->weight);
            v=v->next;
        }
        printf("\n");
    }
}

void process(Graph *G, int n){
    Vertex *p=G->v[n];
    while(p!=NULL){
        printf("[%d (%d)] ",p->no, p->weight);
        p=p->next;
    }
    printf("\n");
}

void process2(Graph *G, int v1, int v2, int w){
    Vertex *p=G->v[v1];
    while(p!=NULL){
        if(p->no==v2){
            p->weight=w;
            return;
        }
        else
            p=p->next;
    }
}

int main(){
    Graph G;
    init(&G);
    for(int i=0;i<6;i++)
        makeVerTex(&G);

    insertEdge(&G,1,0,1);
    insertEdge(&G,1,0,2);
    insertEdge(&G,1,0,3);
    insertEdge(&G,2,0,5);
    insertEdge(&G,1,1,2);
    insertEdge(&G,4,2,4);
    insertEdge(&G,3,4,5);
    print(&G);

    char cmd;
    return 0;
}