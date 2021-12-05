#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define TRUE 1
#define FALSE 0

typedef struct{
    int n,m;
    int adj_mat[SIZE][SIZE];
}GraphType;

void init(GraphType *g){
    for(int row=0;row<SIZE;row++)
        for(int col=0;col<SIZE;col++)
            g->adj_mat[row][col]=0;
}

void insert_dege(GraphType *g, int start, int end){
    if((start >= g->n)||(end >= g->n)){
        printf("간선을 추가할 수 없습니다.\n");
        return;
    }
    g->adj_mat[start][end]=1;//방향그래프에선 이거한개만
    //무방향그래프인경우
    //g->adj_mat[end][start]=1;도 같이 해줘야함
}

void print_adj_mat(GraphType *g){
    printf("\n");
    for(int row=0;row<g->n;row++){
        printf("|");
        for(int col=0;col<g->n;col++)
            printf("%d  ",g->adj_mat[row][col]);
        printf("|\n");
    }
}

void dfs_mat(GraphType *g, int visited[], int v){
    visited[v]=TRUE;
    printf("정점 [%d] ",v+1);
    for(int w=0;w<g->n;w++)
        if(g->adj_mat[v][w] && !visited[w])
            dfs_mat(g, visited,w);
}

void rev_mat(GraphType *g, int v){
    GraphType r;
    init(&r);
    r.n=g->n;
    int visited[SIZE]={FALSE};

    for(int row=0;row<g->n;row++)
        for(int col=0;col<g->n;col++)
            r.adj_mat[col][row]=g->adj_mat[row][col];//행 열 을 열 행 으로 바꾸기 (reverse)

    print_adj_mat(&r);
    printf("\n");
    dfs_mat(&r, visited, v-1);
}

int main(){
    GraphType g;
    init(&g);
    int n, m, v;
    int start, end;
    printf("정점과 간선의 갯수를 입력하세요 \n ");
    scanf("%d %d",&g.n, &g.m);
    getchar();

    for(int i=0;i<g.m;i++){
        scanf("%d %d",&start, &end);
        getchar();
        insert_dege(&g, start-1, end-1);
    }
    print_adj_mat(&g);

    int visited[SIZE]={FALSE};

    printf("\n깊이우선탐색을 시작할 정점을 입력하세요\n");
    scanf("%d",&v);
    getchar();
    dfs_mat(&g, visited, v-1);
    rev_mat(&g, v);




    return 0;
}