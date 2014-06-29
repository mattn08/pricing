
#pragma once
#include "Black_scholes.h"

class FDM
{
public:
	FDM();
	~FDM();
};

// This uses the forward difference approximation to calculate the Delta of
// a call option
double call_delta_fdm(const double S, const double K, const double r, const
	double v, const double T, const double delta_S) {

	return (call_price(S + delta_S, K, r, v, T) - call_price(S, K, r, v, T)) /
		delta_S;
}

// This uses the centred difference approximation to calculate the Gamma of
// a call option
double call_gamma_fdm(const double S, const double K, const double r, const
	double v, const double T, const double delta_S) {

	return (call_price(S + delta_S, K, r, v, T) - 2*call_price(S, K, r, v, T)
		+ call_price(S - delta_S, K, r, v, T)) / (delta_S * delta_S);
}
