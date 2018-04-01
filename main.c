//
//  main.c
//  Linear_Array
//
//  Created by Louis on 2018/3/25.
//  Copyright © 2018 Louis.Aeilot.D. All rights reserved.
//

//Head
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include <string.h>

//Something
void LA_UI(){
    printf("->                Welcome              <-\n");
    printf("->            By Louis Studio          <-\n");
    printf("->              Linear Array           <-\n");
}

// insert code here...
typedef struct LA{
    int unit;       //单元大小（单位字节）
    void * data;    //地址
    int size;       //当前大小
    int cap;        //容量
}LA;
void LA_Init( LA * arr , int unit , int cap){      //初始化
    arr->unit=unit;
    arr->cap=cap;
    arr->data=malloc(cap * unit);
    arr->size=0;
}
void LA_Free( LA * arr ){        //内存释放
    free(arr->data);
}

void* LA_at( LA* arr,int index)
{
    char* buffer=(char*)arr->data;
    char* data=buffer+index*arr->unit;
    return (void*)data;
}

/*
 *LA_Insert insert num data at pos to array
 *arr
 *pos
 *num
 *data
 **/
void LA_Insert( LA * arr , int pos , int num , void * data){        //插入
    if(pos>arr->size || pos<0) return;
    //resize array capacity
    if (arr->cap<arr->size+num) {
        while(arr->cap<arr->size+num)
        {
            arr->cap=2*arr->cap+1;
        }
        arr->data=realloc(arr->data, arr->cap*arr->unit);
    }
    //rightside data moving
    char* buffer=(char*)arr->data;
    if(pos<arr->size)
    {
        memmove(buffer + ( pos + num )*arr->unit, buffer + pos*arr->unit, (arr->size-pos)*arr->unit);
    }
    //copy data
    memcpy( buffer + pos*arr->unit, data, num*arr->unit);
    arr->size+=num;
}
void LA_PushBack( LA * arr , void * data){        //尾插入1
    ///resize buffer
    if (arr->cap<=arr->size+1) {
        arr->cap=2*arr->cap+1;
        arr->data=realloc(arr->data, arr->cap*arr->unit);
    }
    ///copy data
    char* buffer=(char*)arr->data;
    memcpy(buffer + arr->size*arr->unit, data, arr->unit);
    arr->size+=1;
}
void LA_PushFront( LA * arr , void * data){        //头插入1
    ///resize buffer
    if (arr->cap<=arr->size+1) {
        arr->cap=2*arr->cap+1;
        arr->data=realloc(arr->data, arr->cap*arr->unit);
    }
    ///move data
    char* buffer=(char*)arr->data;
    if (arr->size>0) {
        memmove(buffer+arr->unit, buffer, arr->size*arr->unit);
    }
    ///copy data
    memcpy(buffer, data, arr->unit);
    arr->size+=1;
}
void LA_Erase( LA * arr , int pos , int num){        //删除
    if (pos<0 || pos+num>=arr->size) return;
    ///move data
    char* buffer=(char*)arr->data;
    if (pos+num<arr->size-1)
    {
        memmove(buffer + pos*arr->unit, buffer + (pos + num)*arr->unit , (arr->size-(pos+num))*arr->unit);
    }
    ///change size
    arr->size-=num;
}
void LA_PopBack( LA * arr){        //尾删除1
    if(arr->size<=0) return;
    arr->size-=1;
}
void LA_PopFront( LA * arr ){        //头删除1
    if(arr->size<=0) return;
    ///move data
    char* buffer=(char*)arr->data;
    if (arr->size>1)
    {
        memmove(buffer, buffer + arr->unit , (arr->size-1)*arr->unit);
    }
    ///change size
    arr->size-=1;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    LA User;
    LA_UI();
    int num , input;
    printf("Please input integer number,press 'e' to stop.\n");
    LA_Init(&User, sizeof(int), num);
    while(1)
    {
        char line[256];
        char* data=fgets(line,256,stdin);
        if(strncmp(data,"e",1)==0) break;
        if(!data) continue;
        if(!isdigit(data[0]))  continue;
        sscanf(line,"%d",&input);
        LA_PushBack(&User, &input);
    }
    printf("---------------------OUTPUT\n");
    for(int i=0;i<User.size;i++)
    {
        void* at=LA_at(&User,i);
        int tmp=*(int*)at;
        printf("%d,%d\n",i+1,tmp);
    }
    printf("---------------------Test 2\n");
     for (int i = 0; i<10; i++) {
        int tmp=3*i+2;
        LA_Insert(&User, i, 1, &tmp);
    }
    
    for(int i=0;i<User.size;i++)
    {
        void* at=LA_at(&User,i);
        int tmp=*(int*)at;
        printf("%d,%d\n",i,tmp);
    }
    int tmp=5;
    LA_Insert(&User,5,1,&tmp);
    printf("->--------------------<-\n");
    for(int i=0;i<User.size;i++)
    {
        void* at=LA_at(&User,i);
        int tmp=*(int*)at;
        printf("%d,%d\n",i,tmp);
    }
    LA_Free(&User);
    return 0;
}
