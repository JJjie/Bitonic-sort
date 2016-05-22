//
//  bitonic.cpp
//  Bitonic
//
//  Created by 胡文杰 on 16/5/22.
//  Copyright © 2016年 胡文杰. All rights reserved.
//

#include "bitonic.hpp"
#include <iostream>
using namespace std;
void segmentedBitonicSort(float* data, int* seg_id, int* seg_start, int n, int m);

void BitonicSort(float* ,int,bool);
void Exchange(float* ,int , int);
int GetArray(float* ,int );

const float MAXNUM = 9999.9999; //如果个数不为2的次幂个，要填充的数字

void BitonicSort(float* arr,int len ,bool asd){
    int step = len/2;
    for (;step >0 ;step /= 2) {
        for (int i = 0; i < len; i += 2*step) {
            for (int k = 0; k < step; ++k) {
                if (asd) {
                    if (arr[i + k] > arr[i + step +k])
                        Exchange(arr, i+k, i+step+k);
                }
                else {
                    if (arr[i + k] < arr[i + step +k])
                        Exchange(arr, i+k, i+step+k);
                }
            }
        }
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
    bool asd = true;//升序
    
    for (i=1; i<=m; i++) {
        L = seg_start[i] - seg_start[i-1];//段长度
        float cluster[L] ;
        for (j=0; j<L; j++) {
            cluster[j] = data[j+seg_start[i-1]];
        } //可并行
        len = GetArray(cluster,L);
        
        for (int step = 2; step <= len; step *= 2) {
            for (int i = 0; i < len; i += 2*step) {
                BitonicSort(cluster + i, step, asd);//升序
                if (i + step < len) {
                    BitonicSort(cluster + i + step, step, !asd);//逆序
                }
            }//可并行
        }
//            将分段类排序成功的覆盖回去
        for (j=0; j<L; j++) {
            data[j+seg_start[i-1]]=cluster[j];
        }
    }
}
