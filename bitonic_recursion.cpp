//
//  bitonic_recursion.cpp
//  Bitonic
//  递归版本
//
//  Created by 胡文杰 on 16/5/22.
//  Copyright © 2016年 胡文杰. All rights reserved.
//

#include "bitonic_recursion.hpp"
#include <iostream>
using namespace std;
void segmentedBitonicSort(float* data, int* seg_id, int* seg_start, int n, int m);

void BitonicSort(float* ,int , int, bool);
void BitonicMerge(float* ,int, int, bool);
void Exchange(float* ,int , int);
int GetArray(float* ,int n);

const float MAXNUM = 9999.9999; //如果个数不为2的次幂个，要填充的数字

void BitonicSort(float* arr,int beg,int n,bool direct)//direct:true 升序，false 降序
{
    if(n == 1)
        return;
    
    BitonicSort(arr,beg,n / 2, direct);//把前面的n/2个元素按递增排序
    BitonicSort(arr,beg + n / 2, n/2, !direct);//把后面n/2个元素按递减排序
    BitonicMerge(arr,beg, n, direct);//合并前面n/2个和后面n/2个数组。
    return;
}

void BitonicMerge(float* arr,int beg,int n,bool direct)//direct:true 升序，false 降序
{
    if(n == 1) return;
    int halfN = n >> 1; //向右移一位等同于除以2
    
    if (direct) {
        for(int i = beg; i < beg + halfN; i++)
        {
            if(arr[i] > arr[i + halfN])
                Exchange(arr,i, i + halfN);
        }
        BitonicMerge(arr,beg, halfN, direct);
        BitonicMerge(arr,beg + halfN, halfN, direct);
        
    }else{
        for(int i = beg; i < beg + halfN; i++)
        {
            if(arr[i] < arr[i + halfN])
                Exchange(arr,i, i + halfN);
        }
        BitonicMerge(arr,beg, halfN, direct);
        BitonicMerge(arr,beg + halfN, halfN, direct);
        
    }
    
}

void Exchange(float* arr,int i, int j)
{
    float temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

//规范化参与双调排序的数组
int GetArray(float* arr,int n){
    int len = 1;
    while (len < n)//循环退出的条件 len >= n
        len = len << 1;//左移一位相当于乘以2,保证序列长度为2^k个
    
    if (len > n)//如果len > n,就说明数组的个数不够，要将个数填充到len个
    {
        for (int i = n; i < len; i++)
            arr[i] = MAXNUM;
    }
    //len = n的话，说明元素的个数恰好是2的次幂个
    return len;
}

void segmentedBitonicSort(float* data, int* seg_id, int* seg_start, int n, int m){
        int i=0,j=0;
        int L=0,len=0;
    
        for (i=1; i<=m; i++) {
            L = seg_start[i] - seg_start[i-1];//段长度
            float cluster[L] ;
            for (j=0; j<L; j++) {
                cluster[j] = data[j+seg_start[i-1]];
            }
            len = GetArray(cluster,L);
            BitonicSort(cluster,0, len, true);
//            将分段类排序成功的覆盖回去
            for (j=0; j<L; j++) {
                data[j+seg_start[i-1]]=cluster[j];
            }
        }
}
