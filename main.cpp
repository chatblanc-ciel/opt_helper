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
#include <numeric>

using namespace std;

void test_Statistics_Welfords_online_algorithm();

int main(void)
{
	printf("example run\n");fflush(0);

	test_Statistics_Welfords_online_algorithm();

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
