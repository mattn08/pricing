
#include <cmath>
#include "VanillaOption.h"
#include "StatsUtil.h"


void VanillaOption::init() {

	K = 100.0;
	r = 0.05; // 5% interest rate   
	T = 1.0; // One year until maturity
	S = 100.0; // Option is "at the money" as spot equals the strike
	sigma = 0.2; // Volatility is 20%
}

void VanillaOption::copy(const VanillaOption& rhs) {

	K = rhs.getK();
	r = rhs.getr();
	T = rhs.getT();
	S = rhs.getS();
	sigma = rhs.getsigma();
}

VanillaOption::VanillaOption() { init(); }
VanillaOption::VanillaOption(const double& _K, const double& _r,
							 const double& _T, const double& _S,
							 const double& _sigma) {
	K = _K;
	r = _r;
	T = _T;
	S = _S;
	sigma = _sigma ;
}

// Copy constructor
VanillaOption::VanillaOption(const VanillaOption& rhs) {
	copy(rhs);
}

// Assignment operator
VanillaOption& VanillaOption::operator=(const VanillaOption& rhs) {
    if (this == &rhs) return *this;
    copy(rhs);
    return *this;
}


// Public access for the strike price, K
double VanillaOption::getK() const { return K; }
// Other accessors
double VanillaOption::getsigma() const { return sigma; }
double VanillaOption::getS() const { return S; }
double VanillaOption::getT() const { return T; }
double VanillaOption::getr() const { return r; }

double VanillaOption::calccallprice() const {
	double sigma_sqrt_T = sigma * sqrt(T);
	double d_1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / sigma_sqrt_T;
	double d_2 = d_1 - sigma_sqrt_T;
	return S * norm_cdf(d_1) - K * exp(-r*T) * norm_cdf(d_2);
}

double VanillaOption::calcputprice() const {
	double sigma_sqrt_T = sigma * sqrt(T);
	double d_1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / sigma_sqrt_T;
	double d_2 = d_1 - sigma_sqrt_T;
	return K * exp(-r*T) * norm_cdf(-d_2) - S * norm_cdf(-d_1);
}
