#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 10
#define INF 1000000
#define TRUE 1
#define FALSE 0

int selected[SIZE]={FALSE};
int distance[SIZE];

typedef struct{
    int n;
    int weight[SIZE][SIZE];
}GraphType;

// int get_min_vertex(int n){
//     int v,i;
//     for(i=0;i<n;i++)
//         if(!selected[i]){
//             v=i;
//             break;
//         }
//     for(i=0;i<n;i++)
//         if(!selected[i] && (distance[i] < distance[v]))
//             v=i;
//     return v;
// }

// void prim(GraphType *g, int s){
//     int i, u, v;
//     for(u=0;u<g->n;u++)
//         distance[u]=INF;
//     distance[s]=0;

//     for(i=0;i<g->n;i++){
//         u=get_min_vertex(g->n);
//         selected[u]=TRUE;
//         if(distance[u]==INF)
//             return;
//         printf("정점 %d 방문\n",u);
//         for(v=0;v<g->n;v++)
//             if(g->weight[u][v]!=INF)
//                 if(!selected[v] && g->weight[u][v] < distance[v])
//                     distance[v]=g->weight[u][v];
//     }
// }

void print_status(GraphType *g){
    static int step=1;
    printf("STEP %d: ",step++);
    printf("distance:  ");
    for(int i=0;i<g->n;i++){
        if(distance[i]==INF)
            printf("  *  ");
        else printf(" %2d ",distance[i]);
    }
    printf("\n");
    printf("        selected:  ");
    for(int i=0;i<g->n;i++)
        printf(" %2d ",selected[i]);
    printf("\n\n");
}


int choose(int n){
    int i,min,minpos;
    min=INT_MAX;
    minpos=-1;

    for(i=0;i<n;i++)
        if(distance[i]<min && !selected[i]){
            min=distance[i];
            minpos=i;
        }
    return minpos;
}


void shortest_path(GraphType *g, int s){
    int i,u,v;
    for(i=0;i<g->n;i++)
        distance[i]=g->weight[s][i];
    selected[s]=TRUE;

    for(i=0;i<g->n;i++){
        print_status(g);
        u=choose(g->n);

        selected[u]=TRUE;
        for(v=0;v<g->n;v++)
            if(!selected[v])
                if(distance[u]+g->weight[u][v] < distance[v])
                    distance[v]=distance[u]+g->weight[u][v];
    }
}

int main(){
    GraphType g={7,
    {{0,7,INF,INF,3,10,INF},
    {7,0,4,10,2,6,INF},
    {INF,4,0,2,INF,INF,INF},
    {INF,10,2,0,11,9,4},
    {3,2,INF,11,0,INF,5},
    {10,6,INF,9,INF,0,INF},
    {INF,INF,INF,4,5,INF,0}}
    };
    
    shortest_path(&g,0);
}
