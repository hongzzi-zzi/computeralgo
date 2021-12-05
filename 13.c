#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char vName;
}Vertex;//정점

typedef struct{
    int eNo;//간선번호
    int weight;
    Vertex v1, v2;
}Edge;//간선

typedef struct{
    Vertex v[10];
    Edge e[30];
    int vCnt;//정점갯수
    int eCnt;//간선갯수
}Graph;//그래프

void init(Graph *G){
    G->vCnt=0;
    G->eCnt=0;
}

void makeVertex(Graph *G){
    G->v[G->vCnt].vName=97+G->vCnt;
    G->vCnt++;
}

void insertEdge(Graph *G,int w, Vertex v1, Vertex v2){
    G->e[G->eCnt].eNo=G->eCnt;
    G->e[G->eCnt].weight=w;
    G->e[G->eCnt].v1=v1;
    G->e[G->eCnt].v2=v2;
    G->eCnt++;
}

int main(){
    Graph G;
    init(&G);
    for(int i=0;i<6;i++)
        makeVertex(&G);

    insertEdge(&G,1,G.v[0],G.v[1]);
    insertEdge(&G,1,G.v[0],G.v[2]);
    insertEdge(&G,1,G.v[0],G.v[3]);
    insertEdge(&G,2,G.v[0],G.v[5]);
    insertEdge(&G,1,G.v[1],G.v[2]);
    insertEdge(&G,4,G.v[2],G.v[4]);
    insertEdge(&G,3,G.v[4],G.v[5]);

    for(int i=0;i<G.vCnt;i++)
        printf("[%c]   ",G.v[i].vName);
    printf("\n");

    for(int i=0;i<G.eCnt;i++)
        printf("[%d : %c - %c - %d]\n",G.e[i].eNo,G.e[i].v1.vName,G.e[i].v2.vName,G.e[i].weight);
    printf("\n");
    return 0;
}
