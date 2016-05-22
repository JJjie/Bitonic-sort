//
//  main.cpp
//  Bitonic
//
//  Created by 胡文杰 on 16/5/22.
//  Copyright © 2016年 胡文杰. All rights reserved.
//

#include <iostream>
#include "bitonic.hpp"
#include "C_Time.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    int N,M;//要排序的元素的个数/段数/参与算法的实际长度
    int i=0,flag=0;//工具变量
    
    
    cout << "请输入需要排序的元素的个数：" << endl;
    cin >> N ;
    cout << "请输入需要排序的元素的段数：" << endl;
    cin >> M ;
    
    //    通过malloc动态分配内存，高效使用内存空间
    float* data = 0;
    int* seg_id = 0;
    int* seg_start = 0;
    data = (float*)malloc(sizeof(float)*N);
    seg_id = (int*)malloc(sizeof(int)*N);
    seg_start = (int*)malloc(sizeof(int)*M);
    
    cout << "请输入需要排序的浮点数序列：（输入" << N << "个数)" << endl;
    for (i=0; i<N; i++)
        cin >> data[i];
    cout << "请输入序列的段编号：(输入" << N << "个数)" << endl;
    for (i=0; i<N; i++)
        cin >> seg_id[i];
    cout << "请输入序列的段开始值：(输入" << M+1 << "个数，注意最后一个数应该等于序列个数)" << endl;
    for (i=0; i<M+1; i++)
        cin >> seg_start[i];
    
    //    检验输入的值
    for (i=0; i<N-1; i++)
        if (seg_id[i] > seg_id[i+1] )
            flag = 1;
    for (i=0; i<=M-1; i++)
        if (seg_id[seg_start[i]] == seg_id[seg_start[i+1]])
            flag = 3;
    if (seg_start[M]!= N)
        flag = 2;
    
    if (!flag) {
        CTimer t;
        segmentedBitonicSort(data, seg_id, seg_start, N, M);
        cout<<"输入正确，排序结果是："<<endl;
        for (i = 0; i < N; i++)
            cout << data[i] << " ";
        cout << endl;
    }else if(flag == 1){
        cout<<"输入错误，序列段号应该递增。"<<endl;
    }else if(flag == 2){
        cout<<"输入错误，序列开始码最后一位值与序列个数不一致。"<<endl;
    }else if(flag == 3){
        cout<<"输入错误，序列开始码与序列段号不一致。"<<endl;
    }
    
    return 0;
}

