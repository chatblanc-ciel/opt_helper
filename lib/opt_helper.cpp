/*
 * Result.cpp
 *
 *  Created on: 2021/09/25
 *      Author: hommyo
 */

#include "Result.hpp"

using namespace std;

 Statistics::Statistics(const vector<Result>& results)
 :ave(0.0), var(0.0), std_dev(0.0), max(0.0), min(0.0)
 {    
    unsigned int results_len = results.size();
    unsigned int max_index; 
    unsigned int min_index;
   
    for(unsigned int i = 0; i < results_len; ++i)
    {
        double value = results.at(i).get_value();

    //average 計算
        double value_a = value - ave;
        ave += value_a / (double)(i + 1);
        
    //variance 計算
        double value_b = value - ave;
        var += value_a*value_b;

    //maximum 計算
        if( i==0 || max < value )
        {
            max = value;
            max_index = i;
        }

    //minimum 計算 
        if( i==0 || min > value )
        {
            min = value;
            min_index = i;
        }
    }   
        //standard_deviation,variance 計算
        var = var / results_len;
        std_dev = sqrt(var);

        //max min Result代入
        max_result = results.at(max_index);
        min_result = results.at(min_index);
 }