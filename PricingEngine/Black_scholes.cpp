
#include <cmath>
#include "Black_scholes.h"
#include "StatsUtil.h"


// Calculate the European vanilla call price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T
double call_price(const double S, const double K, const double r, const double v, const double T) {
	return S * norm_cdf(d_j(1, S, K, r, v, T)) - K*exp(-r*T) *norm_cdf(d_j(2,
		S, K, r, v, T));
}

// Calculate the European vanilla call Delta
double call_delta(const double S, const double K, const double r, const	double v, const double T) {
	return norm_cdf(d_j(1, S, K, r, v, T));
}

// Calculate the European vanilla call Gamma
double call_gamma(const double S, const double K, const double r, const	double v, const double T) {
	return norm_pdf(d_j(1, S, K, r, v, T)) / (S*v*sqrt(T));
}
// Calculate the European vanilla call Vega
double call_vega(const double S, const double K, const double r, const double v, const double T) {
	return S * norm_pdf(d_j(1, S, K, r, v, T)) * sqrt(T);
}

// Calculate the European vanilla call Theta
double call_theta(const double S, const double K, const double r, const double v, const double T) {
	return -(S*norm_pdf(d_j(1, S, K, r, v, T)) * v) / (2 * sqrt(T))
		- r*K*exp(-r*T) * norm_cdf(d_j(2, S, K, r, v, T));
}

// Calculate the European vanilla call Rho
double call_rho(const double S, const double K, const double r, const double v, const double T) {
	return K*T*exp(-r*T) * norm_cdf(d_j(2, S, K, r, v, T));
}

// Calculate the European vanilla put price based on
// underlying S , strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T
double put_price(const double S, const double K, const double r, const double v, const double T) {
	return -S * norm_cdf(-d_j(1, S, K, r, v, T)) + K*exp(-r*T) * norm_cdf(-d_j(2,
		S, K, r, v, T));
}

// Calculate the European vanilla put Delta
double put_delta(const double S, const double K, const double r, const double v, const double T) {
	return norm_cdf(d_j(1, S, K, r, v, T)) - 1;
}
// Calculate the European vanilla put Gamma
double put_gamma(const double S, const double K, const double r, const double v, const double T) {
	return call_gamma(S, K, r, v, T); // Identical to call by put call parity
}
// Calculate the European vanilla put Vega
double put_vega(const double S, const double K, const double r, const double v, const double T) {
	return call_vega(S, K, r, v, T); // Identical to call by put call parity
}

// Calculate the European vanilla put Theta
double put_theta(const double S, const double K, const double r, const double v, const double T) {
	return -(S*norm_pdf(d_j(1, S, K, r, v, T)) * v) / (2 * sqrt(T))
		+ r*K*exp(-r*T)*norm_cdf(-d_j(2, S, K, r, v, T));
}

// Calculate the European vanilla put Rho
double put_rho(const double S, const double K, const double r, const double v, const double T) {
	return -T*K*exp(-r*T) * norm_cdf(-d_j(2, S, K, r, v, T));
}

