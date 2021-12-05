#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#define SIZE 15

//사전구조체
//(키, 값)
//주요작업: 탐색, 삽입, 삭제
typedef struct{
    int key;//키
    char value[10];//값
}element;


typedef struct{
    element dict[SIZE];//사전 배열
    int size;//사전배열 몇개차있는지 크기
}DictType;

void init(DictType*d){
    d->size=0;
}


//키 삽입
void insertKey(DictType*d){
    for(int i=0;i<SIZE;i++){
        d->dict[i].key=rand()%30+1;
        for(int j=0;j<i;j++){//키값중복없애기
            if(d->dict[i].key==d->dict[j].key)
                i--;
        }
    }
}

//값 삽입
void insertValue(DictType*d){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<6;j++){
            d->dict[i].value[j]=rand()%26+97;//문자열 아스키코드값
        }
        d->size++;
    }
}


void makeDict(DictType*d){
    insertKey(d);
    insertValue(d);
}


void printDict(DictType*d){
    printf("key value\n================\n");
    for(int i=0;i<d->size;i++){
        printf("%2d ",d->dict[i]);
        for(int j=0;j<5;j++){
            printf("%c",d->dict[i].value[j]);
        }
        printf("\n");
    }
}

//삽입정렬
void insertion_sort(DictType*d){
    int i,j;
    element item;
    for(i=1;i<SIZE;i++){
        item=d->dict[i];
        for(j=i-1;j>=0&&d->dict[j].key>item.key;j--){
            d->dict[j+1]=d->dict[j];
        }
        d->dict[j+1]=item;
    }
}

//이진탐색: 배열 - O(log n)/ 연결리스트 - O(n)
//재귀할때마다 후보항복들의 수가 반감
int rFindElement(DictType*d,int key, int l, int r){
    int mid;
    if(l<=r){
        mid=(l+r)/2;
        if(key==d->dict[mid].key)
            return mid;
        else if(key<d->dict[mid].key)
            return rFindElement(d,key,l,mid-1);
        else
            return rFindElement(d,key,mid+1,r);
    }
    return -1;
}

//선형탐색:O(n)
int FindElement(DictType*d,int key, int l, int r){
    int mid;
    while(l<=r){
        mid=(l+r)/2;
        if(key==d->dict[mid].key)
            return mid;
        else if(key<d->dict[mid].key)
            r=mid-1;
        else
            l=mid+1;

    }
    return -1;
}

//삭제
element removeElement(DictType*d, int key){
    int index=FindElement(d,key,0,d->size-1);
    if(index==-1){
        printf("삭제할 요소가 없습니다.\n");
        element item=d->dict[index];
        return item;
        //교수님코드는 실행안되서 바꿈
        //printf("삭제할 요소가 없습니다.\n");
        //return;
    }
    else{
        element item=d->dict[index];
        for(int i=index;i<d->size-1;i++){
            d->dict[i]=d->dict[i+1];
        }
        d->size--;
        return item;
    }
}

int main(){
    DictType d;
    init(&d);
    makeDict(&d);
    printDict(&d);
    getchar();

    printf("\n");
    insertion_sort(&d);
    printDict(&d);
    getchar();

    printf("\n검색할 키값을 입력: ");
    int key;
    scanf("%d",&key);
    int index=rFindElement(&d,key,0,SIZE-1);
    if(index==-1)
        printf("검색 실퍄\n");
    else{
        printf("\n위치 %d에서 키: %d, 값:",index+1,key);
        for(int j=0;j<5;j++){
            printf("%c",d.dict[index].value[j]);
        }
        printf(" 이 검색되었음\n");
    }

    printf("삭제할 키값을 입력: ");
    scanf("%d",&key);
    removeElement(&d,key);
    printDict(&d);

    return 0;
}