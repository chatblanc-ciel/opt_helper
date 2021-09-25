/*
 * Result.cpp
 *
 *  Created on: 2021/09/25
 *      Author: hommyo
 */

#include "Result.hpp"

using namespace std;

 Statistics::Statistics(const vector<Result>& result)
 {    
    //average 計算
    for(unsigned int i = 0; i < result.size(); ++i)
    {
        auto value = result.at(i);
        ave += value;
    }   
        ave = ave / result.size();

    //variance 計算
    for(unsigned int i = 0; i < result.size(); ++i)
    {
        auto value = result.at(i);
        var += (value - ave) * (value - ave);
    } 
        var = var / (result.size() - 1);

    //standard_deviation 計算
        std_dev = sqrt(var);

    //maximum 計算
    max = 0.0;
    for(unsigned int i = 0; i < result.size(); ++i)
    {
        auto value = result.at(i);
        if(max < value )
        {
            max = value;
        }
    }   

    //minimum 計算
    mini = 100.0;
    for(unsigned int i = 0; i < result.size(); ++i)
    {
        auto value = result.at(i);
        if(mini > value )
        {
            mini = value;
        }
    }
 }