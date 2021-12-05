#include <stdio.h>
#include <stdlib.h>

#define N 100

int weight[N],value[N],cap;
int maxSet[N],maxSetSize=0,maxValue=0;

void printArr(int arr[], int n){
    for(int i=0;i<n;i++)
        printf("[%d]",arr[i]);
    printf("\n");
}

void subset(int arr[], int setSize, int n, int idx){
    if(idx==n){
        printArr(arr, setSize);
        return;
    }
    arr[setSize]=idx;

    subset(arr,setSize+1,n,idx+1);//setSize+1이면 오른쪽으로가는거 왼쪽화살표?
    subset(arr, setSize,n,idx+1);//오른쪽화살표?
}

void eval_knapsack(int arr[], int setSize){
    int currWeight=0, currValue=0;
    for(int i=0;i<setSize;i++){
        currWeight+=weight[arr[i]];
        currValue+=value[arr[i]];
    }

    if(currWeight>cap)
        return;
    if(currValue>maxValue){
        maxValue=currValue;
        maxSetSize=setSize;
        for(int i=0;i<setSize;i++)
            maxSet[i]=arr[i];
    }
}

void subset_kcpasack(int arr[], int setSize, int n, int idx){
    if(idx==n){
        eval_knapsack(arr, setSize);
        return;
    }
    arr[setSize]=idx;

    subset_kcpasack(arr,setSize+1,n,idx+1);//setSize+1이면 오른쪽으로가는거 왼쪽화살표?
    subset_kcpasack(arr, setSize,n,idx+1);//오른쪽화살표?
}

int main(){
    int arr[N],n;
    scanf("%d %d",&n,&cap);//물건개수, 가방용량

    for(int i=0;i<n;i++)
        scanf("%d",&value[i]);
    for(int i=0;i<n;i++)
        scanf("%d",&weight[i]);


    subset_kcpasack(arr,0,n,0);

    printf("Max value: %d\n",maxValue);
    printArr(maxSet,maxSetSize);
    return 0;
}