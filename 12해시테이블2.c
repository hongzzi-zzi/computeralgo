#include<stdio.h>
#include<stdlib.h>

#define M 13

typedef struct{
    int key;
    int probeCnt;
}Bucket;

typedef struct{
    Bucket A[M];
}HashType;

void initHash(HashType *HT){
    for(int i=0;i<M;i++){
            HT->A[i].key=0;//비어있는걸 0으로(키값은 0이외의 값이 들어간다 가정)
            HT->A[i].probeCnt=0;
    }
}

int h(int key){
    return key%M;
}

int h2(int key){
    return 11-(key%11);
}

int getNextBucketLinear(int v, int i){//선형조사법
    return (v+i)%M;
}

int getNextBucketQuadratic(int v, int i){//2차조사법
    return (v+i*i)%M;
}

int getNextBucketDouble(int v, int i,int key){//이중해싱법
    return (v+i*h2(key))%M;
}

int isEmpty(HashType *HT,int b){
    return HT->A[b].key==0;
}

void insertItem(HashType *HT,int key){
    int v=h(key);
    int i=0;
    int cnt=0;
    while(i<M){
        cnt++;
        int b=getNextBucketLinear(v,i);
        // int b=getNextBucketQuadratic(v,i);
        // int b=getNextBucketDouble(v,i,key);
        if(isEmpty(HT,b)){
            HT->A[b].key=key;
            HT->A[b].probeCnt=cnt;
            return;
        }
        else
            i++;
    }
}

int findElement(HashType *HT,int key){
    int v=h(key);
    int i=0;
    while(i<M){
        int b=getNextBucketLinear(v,i);
        // int b=getNextBucketQuadratic(v,i);
        // int b=getNextBucketDouble(v,i,key);
        if(isEmpty(HT,b))
            return 0;
        else if(HT->A[b].key==key)
            return key;
        else i++;
    }
    return 0;
}

int removeElement(HashType*HT, int key){
    int v=h(key);
    int i=0;

    while(i<M){
        int b=getNextBucketLinear(v,i);
        // int b=getNextBucketQuadratic(v,i);
        // int b=getNextBucketDouble(v,i,key);
        if(isEmpty(HT,b))
            return 0;
        else if(HT->A[b].key==key){
            HT->A[b].key=0;
            return key;
        }
        else i++;
    }
    return 0;
}

void printHashTable(HashType *HT){
    printf("Bucket   Key   Probe\n");
    printf("------------------------\n");
    for(int i=0;i<M;i++)
        printf("HT[%02d]: %2d   %2d\n",i,HT->A[i].key,HT->A[i].probeCnt);
    
}

int main(){
    HashType HT;
    initHash(&HT);

    insertItem(&HT,25);
    insertItem(&HT,13);
    insertItem(&HT,16);
    insertItem(&HT,15);
    insertItem(&HT,7);
    insertItem(&HT,28);
    insertItem(&HT,31);
    insertItem(&HT,20);
    insertItem(&HT,1);
    insertItem(&HT,38);

    printHashTable(&HT);

    int key;
    printf("\n탐색할 키 입력 : ");
    scanf("%d",&key);
    getchar();
    if(findElement(&HT,key))
        printf("\n키 값 %d가 존재합니다\n",key);
    else
        printf("\n키 값 %d가 존재하지 않습니다\n",key);

    printf("\n삭제할 키 입력 : ");
    scanf("%d",&key);
    getchar();
    if(removeElement(&HT,key))
        printf("\n키 값 %d가 삭제되었습니다\n",key);
    else
        printf("\n키 값 %d가 존재하지 않습니다\n",key);

    printf("\n");
    printHashTable(&HT);

    return 0;
}