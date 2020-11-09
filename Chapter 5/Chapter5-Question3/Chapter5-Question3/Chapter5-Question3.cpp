// Chapter5-Question3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
#include <math.h>

const double DEGREE_TO_RADIAN = M_PI / 180;

double sind(double degrees);
double cosd(double degrees);
double tand(double degrees);

double sind(double degrees)
{
	return std::sin(degrees * DEGREE_TO_RADIAN);
}

double cosd(double degrees)
{
	return std::cos(degrees * DEGREE_TO_RADIAN);
}

double tand(double degrees)
{
	return std::tan(degrees * DEGREE_TO_RADIAN);
}


int main()
{
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "sin(0) = " << sind(0) << std::endl;
	std::cout << "sin(30) = " << sind(30) << std::endl;
	std::cout << "sin(90) = " << sind(90) << std::endl;

	std::cout << "cos(0) = " << cosd(0) << std::endl;
	std::cout << "cos(60) = " << cosd(60) << std::endl;
	std::cout << "cos(90) = " << cosd(90) << std::endl;

	std::cout << "tan(0) = " << tand(0) << std::endl;
	std::cout << "tan(45) = " << tand(45) << std::endl;
}
