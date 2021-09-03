
#define USE_MATH_DEFINES

/* Constants rounded for 21 decimals. */
#define M_E 2.71828182845904523536
#define M_LOG2E 1.44269504088896340736
#define M_LOG10E 0.434294481903251827651
#define M_LN2 0.693147180559945309417
#define M_LN10 2.30258509299404568402
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#define M_PI_4 0.785398163397448309616
#define M_1_PI 0.318309886183790671538
#define M_2_PI 0.636619772367581343076
#define M_1_SQRTPI 0.564189583547756286948
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2 1.41421356237309504880
#define M_SQRT_2 0.707106781186547524401

#include <iostream>
#include <cmath>
#include "StatsUtil.h"


// Standard normal probability density function
double norm_pdf(const double& x) {
	return (1.0 / (pow(2*M_PI, 0.5))) * exp (-0.5*x*x);
}

// An approximation to the cumulative distribution function
// for the standard normal distribution
// Note: This is a recursive function
double norm_cdf(const double& x) {
	double k = 1.0/(1.0 + 0.2316419*x);
	double k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 +
			   k*(-1.821255978 + 1.330274429*k))));

	if (x >= 0.0) {
		return (1.0 - (1.0 / (pow(2*M_PI, 0.5))) * exp (-0.5*x*x) * k_sum);
	} else {
		return 1.0 - norm_cdf(-x);
	}
}

// This calculates d_j, for j in {1 ,2}. This term appears in the closed
// form solution for the European call or put price
double d_j(const int& j, const double& S, const double& K, const double& r,
	const double& v, const double& T) {
	return (log (S/K) + (r + (pow(-1.0, j-1))*0.5*v*v)*T) / (v*(pow(T, 0.5)));
}

// Calculate the European vanilla call price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T
double call_price(const double& S , const double& K, const double& r ,
const double& v , const double& T) {
	return S * norm_cdf(d_j(1, S, K, r, v, T))-K*exp(-r*T) *
			   norm_cdf(d_j(2, S, K, r, v, T));
}

// Calculate the European vanilla put price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T
double put_price(const double& S, const double& K, const double& r,
				 const double& v, const double& T) {
	return -S * norm_cdf(-d_j(1, S, K, r, v, T))+K*exp(-r*T) *
			   norm_cdf(-d_j(2, S, K, r, v, T));
}

int unused_main (int argc, char argv) {
	// First we create the parameter list
	double S = 100.0; // Option price
	double K = 95.0; // Strike price
	double r = 0.1; // Risk-free rate (5%)
	double v = 0.5; // Volatility of the underlying (20%)
	double T = 0.25; // One year until expiry
	// Then we calculate the call / put values
	double call = call_price(S, K, r, v, T);
	double put = put_price(S, K, r, v, T);

	// Finally we output the parameters and prices
	std::cout << "Underlying:     " << S << std::endl;
	std::cout << "Strike:         " << K << std::endl;
	std::cout << "Risk-Free Rate: " << r << std::endl;
	std::cout << "Volatility:    " << v << std::endl;
	std::cout << "Maturity:       " << T << std::endl;

	std::cout << "Call Price:     " << call << std::endl;
	std::cout << "Put Price:      " << put << std::endl;
	return 0;
}

// ===========
// MONTE CARLO
// ===========
// A simple implementation of the Box-Muller algorithm, used to generate
// gaussian random numbers necessary for the Monte Carlo method below
// Note that C++11 actually provides std::normaldistribution<> in
// the <random> library, which can be used instead of this function

double gaussian_box_muller() {
	double x = 0.0;
	double y = 0.0;
	double euclid_sq = 0.0;

	// Continue generating two uniform random variables
	// until the square of their "euclidean distance"
	// is less than unity

	do {
		x = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
		y = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
		euclid_sq = x*x + y*y;
	} while (euclid_sq >= 1.0);

	return x*sqrt(-2*log(euclid_sq) / euclid_sq);
}



