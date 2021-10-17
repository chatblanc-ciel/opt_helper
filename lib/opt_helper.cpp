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
 * # 引数
 *   file_name :string 出力するファイル名。拡張子を含めること。
 */
void Result::tprint_update_curve(const string& file_name) const
{
    FILE *csv = fopen(file_name.c_str(),"w");

    // header 印字
    fprintf(csv, "No,Value\n");

    // 係数値印字
    for(unsigned int i = 0; i < update_value.size(); i++)
    {
        fprintf(csv, "%d,%.15f\n",i + 1 ,update_value.at(i));
    }

    fclose(csv);
}

/*
 * 更新曲線 画像出力
 *
 * # 引数
 *   file_name :string 出力するファイル名。拡張子を含めること。
 *   logscale :bool y軸を対数で取るか選択 true:取る false:取らない
 */
void Result::gprint_update_curve(const string& file_name, bool logscale) const
{
    //xrangeの右端を切り上げる
    unsigned int digit = log10(update_value.size());
    int xrange = ceil( update_value.size() / pow(10.0, digit) ) * pow(10.0, digit);

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
    fprintf(gp, "set xrange [0:%d]\n" ,xrange);
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
 * # 変数の更新経歴出力
 * 
 * 変数の変遷をCSV形式で出力する
 * 
 * # 引数
 *   file_name :string 出力するファイル名。拡張子を含めること。
 */ 
void Result::tprint_update_variable(const string& file_name) const
{
    FILE *csv = fopen(file_name.c_str(),"w");

    // header 印字
    fprintf(csv, "No,");
    for(unsigned int i = 0; i < update_variable.at(i).size(); i++)
    {
        fprintf(csv, "Variable[%d],",i);
    }
    fprintf(csv, "\n");

    // 係数値印字
    for(unsigned int i = 0; i < update_variable.size(); i++)
    {
        fprintf(csv, "%d,",i + 1);
        for (unsigned int j = 0; j < update_variable.at(i).size() - 1; j++)
        {
            fprintf(csv, "%.15f,",update_variable.at(i).at(j));
        }

        fprintf(csv, "%.15f\n" ,update_variable.at(i).back());
    }
    fclose(csv);
}

/*
 * 最良変数
 * 1試行のなかで最も評価値が良かった時の変数の値を示す。
 * 
 * # 引数
 *   file_name :string 出力するファイル名。拡張子を含めること。
 */
void Result::tprint_variable(const string& file_name) const
{
    FILE *csv = fopen(file_name.c_str(),"w");

    // header 印字  
    for(unsigned int i = 0; i < variable.size(); i++)
    {
        fprintf(csv, "Variable[%d],",i);
    }
    fprintf(csv, "\n");

    // 係数値印字
    for (unsigned int i = 0; i < variable.size() - 1 ; i++)
    {
        fprintf(csv, "%.15f,",variable.at(i));
    }

    fprintf(csv, "%.15f" ,variable.back());

    fclose(csv);
}

/*
 * 開始時の最良変数
 * 最適化開始時で最も評価値が良かった時の変数の値を示す。
 * 
 * # 引数
 *   file_name :string 出力するファイル名。拡張子を含めること。
 */
void Result::tprint_init_variable(const string& file_name) const
{
    FILE *csv = fopen(file_name.c_str(),"w");

    // header 印字
    for(unsigned int i = 0; i < init_variable.size(); i++)
    {
        fprintf(csv, "Variable[%d],",i);
    }
    fprintf(csv, "\n");

    // 係数値印字
    for (unsigned int i = 0; i < init_variable.size() - 1 ; i++)
    {
        fprintf(csv, "%.15f,",init_variable.at(i));
    }
    fprintf(csv, "%.15f" ,init_variable.back());

    fclose(csv);
}

/*
 *  全出力用関数 
 *  No,Value,Evals,Iter,Time
 *  結果をまとめる関数
 *  
 * # 引数
 *   results :vector<Result> 全試行分の結果の配列
 *   file_name :string 出力するファイル名。拡張子を含めること。
 */
void Result::tprint_all_result(const vector<Result>& results ,const string& file_name)
{
    FILE *csv = fopen(file_name.c_str(),"w");

    // header 印字
    fprintf(csv, "No,Value,Evals,Iter,Time[ms]\n");

    // 係数値印字
    for(unsigned int i = 0; i < results.size(); i++)
    {
        fprintf(csv, "%d,%.15f,%.15f,%lld,%.15f\n",
            i + 1, results.at(i).get_value(), results.at(i).get_evals(),
            results.at(i).get_iter(), (double)results.at(i).get_time());
    }

    fclose(csv);
}

/*
 *  全試行分の最良値の変数をまとめる関数 
 *  No,variables
 *  結果をまとめる関数
 *  
 * # 引数
 *   results :vector<Result> 全試行分の結果の配列
 *   file_name :string 出力するファイル名。拡張子を含めること。
 */
void Result::tprint_all_variables(const vector<Result>& results ,const string& file_name)
{
    FILE *csv = fopen(file_name.c_str(),"w");

    // header 印字
    fprintf(csv, "No,");
    for(unsigned int i = 0; i < results.at(0).get_variable().size(); i++)
    {
        fprintf(csv, "Variable[%d],",i);
    }
    fprintf(csv, "\n");

    // 係数値印字
    for(unsigned int i = 0; i < results.size(); i++)
    {
        fprintf(csv, "%d,",i + 1);
        for (unsigned int j = 0; j < results.at(i).get_variable().size() - 1 ; j++)
        {
            fprintf(csv, "%.15f,",results.at(i).get_variable().at(j));
        }

        fprintf(csv, "%.15f\n" ,results.at(i).get_variable().back());
    }
    
    fclose(csv);
}

/*
 * # 基本統計量についての構造体
 * 
 * # コンストラクタ
 * `Welford online algorithm`による
 * 計算誤差を低減した基本統計量の計算を行う
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
 * # 引数
 *   stat :vector<Statistics> 全設計例分の結果の配列
 *   file_name :string 出力するファイル名。拡張子を含めること。
 */
void Statistics::tprint_all_statistics(const vector<Statistics>& stat ,const string& file_name)
{
    FILE *csv = fopen(file_name.c_str(),"w");

    unsigned int stat_len = stat.size();

    // header 印字
    fprintf(csv,"No,Average,Max,Min,Std,Variance,EvalsAverage,TimeAverage[ms]\n");

    // 係数値印字
    for(unsigned int i = 0; i < stat_len; ++i)
    {
        double ave_value = stat.at(i).average();
        double min_value = stat.at(i).minimum();
        double max_value = stat.at(i).maximum();
        double std_value = stat.at(i).std_deviation();
        double var_value = stat.at(i).variance();
        double evals_ave = stat.at(i).evals_average();
        clock_t time_ave = stat.at(i).time_average();

        fprintf(csv,"%d,%.15f,%.15f,%.15f,%.15f,%.15f,%.15f,%.15f\n",
            i + 1, ave_value, max_value, min_value,
            std_value, var_value, evals_ave, (double)time_ave);
    }

    fclose(csv);
}