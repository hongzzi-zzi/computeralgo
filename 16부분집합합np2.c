#include <stdio.h>
#include <stdlib.h>

int c[15][150];

void calculate_subset_sum(int s[], int n, int m){
    //시가ㄴ복잡도 n^2
    int i,j;
    //동적프로그래밍기법
    for(i=0;i<=n;i++)
        c[i][0]=1;
 
    for(i=1;i<=m;i++)
        c[0][i]=0;

    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            c[i][j]=0;

            if(j>=s[i-1])
                if(c[i-1][j-s[i-1]]==1)
                    c[i][j]=1;

            if(c[i-1][j]==1)
                c[i][j]=1;
        }
    }
}

int main(){
    int m,n;
    printf("input m, n");
    scanf("%d %d",&m,&n);

    int *s=(int*)malloc(sizeof(int)*n);//동적배열생성
    for(int i=0;i<n;i++)
        scanf("%d",&s[i]);

    calculate_subset_sum(s,n,m);

    //possible나오게 어케하노 ssibal..
    //몬개소리야 ~~~~~~~~~~~~~
    return 0;
}