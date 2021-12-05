#include <stdio.h>
#include <stdlib.h>

#define max(x,y)((x)>(y)? (x):(y))
#define min(x,y)((x)<(y)? (x):(y))

int A[]={0, 1, 3, 6, 11, 17};
int H[]={0, 2, 5, 1, 5, 0};
int m[10];

//동적프로그래밍정방향

//왜 8이나오노 ㅅㅂ
int airtel(int n){
    m[0]=0;
    int cost;
    for(int d=1;d<n;d++){
        m[d]=10000;
        for(int k=0;k<d;k++){
            cost=m[k]+H[k]+A[d-k];
            m[d]=min(m[d],cost);
        }
    }
    return m[n-1];
}

//동적프로그래밍역방향: 정방향 반대로

//분할통치법정방향(중복호출많아서 효율떨어짐)
int rAirtelForward(int d){
    if(d==0)
        return 0;
    
    int minCost=10000;
    int cost;

    for(int k=0;k<d-1;k++){
        cost=rAirtelForward(k)+H[k]+A[d-k];
        minCost=min(minCost,cost);
    }
    return minCost;
}

//분할통치법역방향(중복호출많아서 효율떨어짐): 정방향 반대로
 

int main(){
    printf("%d\n",rAirtelForward(5));
    printf("%d\n",airtel(5));

    return 0;
}