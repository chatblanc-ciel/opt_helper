/*
 * opt_helper.hpp
 *
 *  Created on: 2021/10/10
 *      Author: matsu
 */

#ifndef LIB_OPT_HELPER_HPP_
#define LIB_OPT_HELPER_HPP_

#define _USE_MATH_DEFINES

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <regex>
#include <functional>

using namespace std;

struct Result
{
protected:
    double value;

public:

    Result()
    	:value(0.0)
    {}

    Result& set_value(double input)
    {
        value = input;
        return *this;
    }

    double get_value() const
    { return value; }

};

struct Statistics
{
protected:

    double ave;
    double var;
    double std_dev;
    double max;
    double min;
    Result max_result;
    Result min_result;

public:

    Statistics(const vector<Result>&);

    double average() const
    { return ave; }
    double variance() const
    { return var; }
    double std_deviation() const
    { return std_dev; }
    double maximum() const
    { return max; }
    double minimum() const
    { return min; }

};




#endif /* LIB_OPT_HELPER_HPP_ */
