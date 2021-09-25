/*
 * Result.cpp
 *
 *  Created on: 2021/10/02
 *      Author: hommyo
 */

#include "./lib/Result.hpp"

#include <stdio.h>
#include <string>
#include <chrono>
#include <assert.h>

using namespace std;

void test_Statistics_Welfords_online_algorithm();

int main(void)
{
	printf("example run\n");

	test_Statistics_Welfords_online_algorithm();

	return 0;
}

/* # 基本統計量構造体
 *   基本統計量計算のテスト
 *
 */
void test_Statistics_Welfords_online_algorithm()
{
	//Statistics関数使用時のテスト
	vector<Result> results1
	{
		Result().set_value(0.6),
		Result().set_value(0.8),
		Result().set_value(1.0),
		Result().set_value(1.2),
		Result().set_value(1.4),
    };

	auto st = Statistics(results1);

	double ave = st.average();
	double var = st.variance();
	double std_dev = st.std_deviation();
	double max = st.maximum();
	double min = st.minimum();

	printf("ave=%f var=%f std_dev=%f max=%f min=%f\n\n" ,ave ,var ,std_dev ,max ,min);



	double ave2 = 0.0;
	double var2 = 0.0;
	double std_dev2 = 0.0;
	double max2 = 0.0;
	double min2 = 0.0;

    unsigned int results_len = results1.size();
   
   //average,variance計算
    for(unsigned int i = 0; i < results_len; ++i)
    {
        double value = results1.at(i).get_value();

        ave2 += value;
        var2 += value * value;	
	}
		ave2 /= results_len;
    	var2 = var2 / results_len - ave2 * ave2;

	//standard_deviation 計算
        std_dev2 = sqrt(var2);
		
	for(unsigned int i = 0; i < results_len; ++i)
    {

		double value = results1.at(i).get_value();

    //maximum 計算
        if( i==0 || max2 < value )
        {
            max2 = value;
        }

    //minimum 計算 
        if( i==0 || min2 > value )
        {
            min2 = value;
        }
    }   

	printf("ave2=%f var2=%f std_dev2=%f max2=%f min2=%f" ,ave2 ,var2 ,std_dev2 ,max2 ,min2);

	//同値確認
	assert(ave==ave2);
	assert(var==var2);
	assert(std_dev==std_dev2);
	assert(max==max2);
	assert(min==min2);

}