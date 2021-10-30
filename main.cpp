/*
 * main.cpp
 *
 *  Created on: 2021/10/02
 *      Author: hommyo
 */

#include "./lib/opt_helper.hpp"

#include <stdio.h>
#include <string>
#include <chrono>
#include <assert.h>
#include <numeric>
using namespace std;

void test_Statistics_Welfords_online_algorithm();
void test_tprint_update_curve();
void test_tprint_update_variable();  
void test_tprint_variable();
void test_tprint_init_variable();
void test_gprint_update_curve(); 
void test_tprint_all_result();
void test_tprint_all_variables();
void test_tprint_all_statistics();

int main(void)
{
	printf("example run\n");fflush(0);

	test_gprint_update_curve();

	return 0;
}

/* # 基本統計量構造体
 *   基本統計量計算のテスト
 *   定義通りの計算と構造体のメソッドによる
 *   基本統計量の計算が一致するか検査する
 */
void test_Statistics_Welfords_online_algorithm()
{
	vector<Result> results1
	{
		Result().set_value(0.6),
		Result().set_value(0.8),
		Result().set_value(1.0),
		Result().set_value(1.2),
		Result().set_value(1.4),
    };

	//Statistics関数使用時の数値
	auto st = Statistics(results1);

	double ave = st.average();
	double var = st.variance();
	double std_dev = st.std_deviation();
	double max = st.maximum();
	double min = st.minimum();

	printf("Struct Statistics by Welford online algorithm\n");
	printf("ave=%.15f var=%.15f std_dev=%.15f max=%.15f min=%.15f\n\n" ,ave ,var ,std_dev ,max ,min);

	//定義通りに計算した場合の数値
	//average計算
	double ave2 = std::accumulate(results1.begin(), results1.end(), 0.0,
		[](double sum, const auto& result)
		{ return sum + result.get_value(); })
		/ results1.size();

	//variance計算
	double var2 = std::accumulate(results1.begin(), results1.end(), 0.0,
		[ave](double sum, const auto& result)
		{
			const auto temp = result.get_value() - ave;
			return sum + temp * temp;
		})
		/ results1.size();

	//standard_deviation 計算
	double std_dev2 = sqrt(var2);

	//maximum 計算
	double max2 = (*std::max_element(results1.begin(), results1.end(),
		[](const auto& a, const auto& b)
		{ return a.get_value() < b.get_value(); }))
		.get_value();

	//minimum 計算
	double min2 = (*std::min_element(results1.begin(), results1.end(),
		[](const auto& a, const auto& b)
		{ return a.get_value() < b.get_value(); }))
		.get_value();

	printf("calculate normal\n");
	printf("ave=%.15f var=%.15f std_dev=%.15f max=%.15f min=%.15f" ,ave2 ,var2 ,std_dev2 ,max2 ,min2);

	//同値確認
	const unsigned int acc = 1000;		// 10^-n(小数点以下n桁)まで精度を検査
	assert(std::round(ave*acc) == std::round(ave2*acc));
	assert(std::round(var*acc) == std::round(var2*acc));
	assert(std::round(std_dev*acc) == std::round(std_dev2*acc));
	assert(std::round(max*acc) == std::round(max2*acc));
	assert(std::round(min*acc) == std::round(min2*acc));

}

void test_tprint_update_curve()
{
	vector<double> test;

	for(unsigned int i = 1; i < 1000; i++)
	{
		double t = i * 0.01;
		test.emplace_back(t);
	}

	Result update_value(Result().set_update_value(test));

	update_value.tprint_update_curve("test_update_curve.csv");

}

void test_tprint_update_variable()
{
	vector<vector<double>> test;
	test.resize(20);

	for(unsigned int i = 0; i < 20; i++)
	{
		for(unsigned int j = 0; j < 10; j++)
		{
			test.at(i).emplace_back(j);
		}
	}

	Result update_variable(Result().set_update_variable(test));

	update_variable.tprint_update_variable("test_update_variable.csv");
}

void test_tprint_variable()
{
	vector<double> test;

	for(unsigned int i = 0; i < 20; i++)
	{
			test.emplace_back(i);
	}

	Result variable(Result().set_variable(test));

	variable.tprint_variable("test_variable.csv");
}

void test_tprint_init_variable()
{
	vector<double> test;

	for(unsigned int i = 0; i < 20; i++)
	{
			test.emplace_back(i);
	}

	Result variable(Result().set_init_variable(test));

	variable.tprint_init_variable("test_init_variable.csv");
}

void test_gprint_update_curve()
{
	vector<double> test;

	for(unsigned int i = 1; i < 4100; i ++)
	{
		double t = i * 0.01;
		test.emplace_back(t);
	}

	Result update_value(Result().set_update_value(test));

	update_value.gprint_update_curve("test_update_curve.png", true);

}

void test_tprint_all_result()
{
	double value = 1.0;
	double evals = 30.0;
	unsigned int iter = 500;
	clock_t time = 200;

	vector<Result> results
	{
		Result()
		.set_value(value)
		.set_evals(evals)
		.set_iter(iter)
		.set_time(time),

		Result()
		.set_value(value)
		.set_evals(evals)
		.set_iter(iter)
		.set_time(time),	

		Result()
		.set_value(value)
		.set_evals(evals)
		.set_iter(iter)
		.set_time(time),	
	};

	Result::tprint_all_result(results, "all_result.csv");
}

void test_tprint_all_variables()
{
	vector<double> test;

	for(unsigned int i = 0; i < 20; i++)
	{
			test.emplace_back(i);
	}

	vector<Result> variable
	{
		Result().set_variable(test),
		Result().set_variable(test),
		Result().set_variable(test),
		Result().set_variable(test),
		Result().set_variable(test)
	};

	Result::tprint_all_variables(variable, "all_variables.csv");
}

void test_tprint_all_statistics()
{
	vector<Result> results1
	{
		Result().set_value(0.6).set_evals(4000.0).set_time((clock_t)2000),
		Result().set_value(0.8).set_evals(5000.0).set_time((clock_t)3000),
		Result().set_value(1.0).set_evals(6000.0).set_time((clock_t)4000),
		Result().set_value(1.2).set_evals(7000.0).set_time((clock_t)5000),
		Result().set_value(1.4).set_evals(8000.0).set_time((clock_t)6000),
    };

		vector<Result> results2
	{
		Result().set_value(1.6).set_evals(2000.0).set_time((clock_t)3000),
		Result().set_value(1.8).set_evals(3000.0).set_time((clock_t)4000),
		Result().set_value(2.0).set_evals(4000.0).set_time((clock_t)5000),
		Result().set_value(2.2).set_evals(5000.0).set_time((clock_t)6000),
		Result().set_value(2.4).set_evals(6000.0).set_time((clock_t)7000),
    };

		vector<Result> results3
	{
		Result().set_value(2.6).set_evals(5000.0).set_time((clock_t)1000),
		Result().set_value(2.8).set_evals(6000.0).set_time((clock_t)2000),
		Result().set_value(3.0).set_evals(7000.0).set_time((clock_t)3000),
		Result().set_value(3.2).set_evals(8000.0).set_time((clock_t)4000),
		Result().set_value(3.4).set_evals(9000.0).set_time((clock_t)5000),
    };

	vector<Statistics> st 
	{
		Statistics(results1),
		Statistics(results2),
		Statistics(results3),		
	};

	Statistics::tprint_all_statistics(st, "all_statistics.csv");
}
