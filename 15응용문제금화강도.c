//에어텔문제 2d버전
#include <stdio.h>
#include <stdlib.h>

#define max(x,y)((x)>(y)? (x):(y))
#define min(x,y)((x)<(y)? (x):(y))

int m[8][8];
int A[8][8]={
    {1,3,7,2,11,17,16,25},
    {6,2,3,4,7,2,12,15},
    {11,4,6,8,8,1,9,14},
    {10,8,8,11,6,3,3,9},
    {0,10,9,8,7,15,17,22},
    {17,12,7,10,3,1,8,13},
    {19,25,10,15,14,11,3,3},
    {21,18,16,20,15,13,19,0}
};

int minGold(int n){
    m[0][0]=A[0][0];
    int i,j,k;
    int minRight, minDown;
    int cost;
    //교재코드그대로작성하기
}

int main(){

    return 0;
}