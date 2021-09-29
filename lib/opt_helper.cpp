/*
 * opt_helper.cpp
 *
 *  Created on: 2021/09/25
 *      Author: hommyo, chatblanc_ciel
 */

#include "opt_helper.hpp"

using namespace std;

/*
 *  更新曲線
 *  評価値の推移を示す
 *  
 *  tprint_update_curve(ファイルの名前を拡張子込みで入力)
 */
void Result::tprint_update_curve(const string& file_name) const
{
    FILE *csv = fopen(file_name.c_str(),"w");

    fprintf(csv, "No,Value\n");

    for(unsigned int i = 0; i < update_value.size(); i++)
    {
        fprintf(csv, "%d,%.15f\n",i + 1 ,update_value.at(i));
    }

    fclose(csv);
}


/*
 * 更新曲線 画像出力
 *
 * gprint_update_curve(ファイルの名前を拡張子込みで入力)
 * 
 */
void Result::gprint_update_curve(const string& file_name, bool logscale) const
{
    //gnuplotで出力
    FILE *gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set terminal pngcairo\n");
    fprintf(gp, "set output '%s'\n" ,file_name.c_str());
    fprintf(gp, "set grid\n");
    fprintf(gp, "set xlabel 'Number of evaluations'\n");
    fprintf(gp, "set ylabel 'Objective function value'\n");
    fprintf(gp, "set key    font 'Times New Roman,10'\n");
    fprintf(gp, "set xlabel font 'Times New Roman,12'\n");
    fprintf(gp, "set ylabel font 'Times New Roman,12'\n");
    fprintf(gp, "set tics   font 'Times New Roman,10'\n");
    fprintf(gp, "set xrange [0:%d]\n" ,update_value.size());
    //fprintf(gp, "set yrange [0:10]\n"); 
    if(logscale)
    {
        fprintf(gp, "set logscale y \n");
    }
    fprintf(gp, "plot '-' with lines title \"\n" );
    
    for(unsigned int i = 0; i < update_value.size(); i++)
    {
        fprintf(gp, "%d %.15f\n",i + 1,update_value.at(i));
    }

    fprintf(gp, "e\n");
    pclose(gp);
}

/*
 *  全出力用関数 
 *  No,Value,Evals,Iter,Time
 *  結果をまとめる関数
 *  
 *  tprint_all_result(全試行分の結果の配列)
 */
void Result::tprint_all_result(const vector<Result>& results ,const string& file_name)
{
    FILE *csv = fopen(file_name.c_str(),"w");

    fprintf(csv, "No,Value,Evals,Iter,Time[ms]\n");

    for(unsigned int i = 0; i < results.size(); i++)
    {
        fprintf(csv, "%d,%.15f,%.15f,%lld,%.15f\n",
            i + 1, results.at(i).get_value(), results.at(i).get_evals(),
            results.at(i).get_iter(), (double)results.at(i).get_time());
    }
    fclose(csv);
}

/*
 * 統計値計算関数
 * average,variance,stndard_deviation,maxmum,minimum
 *
 * Statistics(統計を計算したい結果の配列)
 */
Statistics::Statistics(const vector<Result>& results)
:ave(0.0), var(0.0), std_dev(0.0), max(0.0), min(0.0), evals_ave(0.0), time_ave(0.0)
{    
    unsigned int results_len = results.size();
    unsigned int max_index; 
    unsigned int min_index;
   
    for(unsigned int i = 0; i < results_len; ++i)
    {
        double value = results.at(i).get_value();
        double evals = results.at(i).get_evals();
        clock_t time = results.at(i).get_time();

    //evals_ave 計算
        double evals_a = evals - evals_ave;
        evals_ave += evals_a / (double)(i + 1);       

    //time_ave 計算
        clock_t time_a = time - time_ave;
        time_ave += time_a / (double)(i + 1); 

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

/*
 * 全統計出力関数 
 * No,Average,Max,Min,Std,Variance,EvalsAverage,TimeAverage
 *
 * tprint_all_statistics(全試行分の統計値の配列,ファイルの名前を拡張子込みで入力)
 */
void Statistics::tprint_all_statistics(const vector<Statistics>& value ,const string& file_name)
{
    FILE *csv = fopen(file_name.c_str(),"w");

    unsigned int value_len = value.size();

    fprintf(csv,"No,Average,Max,Min,Std,Variance,EvalsAverage,TimeAverage[ms]\n");

    for(unsigned int i = 0; i < value_len; ++i)
    {
        double ave_value = value.at(i).average();
        double min_value = value.at(i).minimum();
        double max_value = value.at(i).maximum();
        double std_value = value.at(i).std_deviation();
        double var_value = value.at(i).variance();
        double evals_ave = value.at(i).evals_average();
        clock_t time_ave = value.at(i).time_average();

        fprintf(csv,"%d,%.15f,%.15f,%.15f,%.15f,%.15f,%.15f,%.15f\n",
            i + 1, ave_value, max_value, min_value,
            std_value, var_value, evals_ave, (double)time_ave);
    }

    fclose(csv);
}