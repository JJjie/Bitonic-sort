//
//  C_Time.hpp
//  Bitonic
//
//  Created by 胡文杰 on 16/5/22.
//  Copyright © 2016年 胡文杰. All rights reserved.
//

#ifndef C_Time_hpp
#define C_Time_hpp

#include <stdio.h>
#include <iostream>
#include <ctime>
using namespace std;

class CTimer
{
public:
    CTimer()
    {
        _start=clock();
    }
    
    ~CTimer()
    {
        _end=clock();
        cout<< "运行时间为：" <<float(_end - _start) / CLK_TCK <<endl;
    }
private:
    clock_t _start;
    clock_t _end;
};


#endif /* C_Time_hpp */
