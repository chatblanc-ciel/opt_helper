
/*
 * Result.hpp
 *
 *  Created on: 2021/09/25
 *      Author: hommyo
 *
 * This cord is written by UTF-8
 */

#define RESULT_HPP_

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
#include <complex>
#include <functional>
#include <random>

using namespace std;

struct Result
{
protected:
double value;

public:

};

struct Statistics
{
protected:

    double ave;
    double var;
    double std_dev;
    double max;
    double mini;

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
    { return mini; }  

};
