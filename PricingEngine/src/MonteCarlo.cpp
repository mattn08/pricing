
#include <cmath>
#include <iostream>
#include <algorithm>
#include "MonteCarlo.h"


MonteCarlo::MonteCarlo()
{
}


MonteCarlo::~MonteCarlo()
{
}


// Pricing a European vanilla call option with a Monte Carlo method
// Create three separate paths, each with either an increment, non
// increment or decrement based on deltaS, the stock path parameter

void monte_carlo_call_price(const int num_sims, const double S, const double K, const double r,
	const double v, const double T, const double delta_S,
	double& price_Sp, double& price_S, double& price_Sm) {

	// Since we wish to use the same Gaussian random draws for each path, it is
	// necessary to create three separated adjusted stock paths for each
	// increment / decrement of the asset
	double sp_adjust = (S + delta_S) * exp(T*(r - 0.5*v*v));
	double s_adjust = S * exp(T*(r - 0.5*v*v));
	double sm_adjust = (S - delta_S) * exp(T*(r - 0.5*v*v));

	// These will store all three 'current' prices as the Monte Carlo
	// algorithm is carried out
	double sp_cur = 0.0;
	double s_cur = 0.0;
	double sm_cur = 0.0;
	// There are three separate pay-off sums for the final price
	double payoff_sum_p = 0.0;
	double payoff_sum = 0.0;
	double payoff_sum_m = 0.0;
	// Loop over the number of simulations
	for (int i = 0; i < num_sims; i++) {
		double gauss_bm = gaussian_box_muller(); // Random gaussian draw
		// Adjust three stock paths
		double expgauss = exp(sqrt(v*v*T)* gauss_bm); // Precalculate
		sp_cur = sp_adjust * expgauss;
		s_cur = s_adjust * expgauss;
		sm_cur = sm_adjust * expgauss;
		// Calculate the continual pay-off sum for each increment/decrement
		payoff_sum_p += std::max(sp_cur - K, 0.0);
		payoff_sum += std::max(s_cur - K, 0.0);
		payoff_sum_m += std::max(sm_cur - K, 0.0);
	}

	// There are three separate prices
	price_Sp = (payoff_sum_p / static_cast<double>(num_sims)) * exp(-r*T);
	price_S = (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
	price_Sm = (payoff_sum_m / static_cast<double>(num_sims)) * exp(-r*T);
}

double call_delta_mc(const int num_sims, const double S, const double K,
	const double r, const double v, const double T, const double delta_S) {

	// These values will be populated via the monte carlo call price function.
	// They represent the incremented Sp (S+delta_S), non-incremented S (S) and
	// decremented Sm (S-delta_S) prices.
	double price_Sp = 0.0;
	double price_S = 0.0;
	double price_Sm = 0.0;

	// Call the Monte Carlo pricer for each of the three stock paths
	// (We only need two for the Delta)
	monte_carlo_call_price(num_sims, S, K, r, v, T, delta_S, price_Sp,
		price_S, price_Sm);
	return (price_Sp - price_S) / delta_S;
}

double call_gamma_mc(const int num_sims, const double S, const double K,
	const double r, const double v, const double T, const double delta_S) {

	// These values will be populated via the monte carlo call price function.
	// They represent the incremented Sp (S+delta_S), non-incremented S (S) and
	// decremented Sm (S-delta_S) prices.
	double price_Sp = 0.0;
	double price_S = 0.0;
	double price_Sm = 0.0;

	// Call the Monte Carlo pricer for each of the three stock paths
	// (We need all three for the Gamma)
	monte_carlo_call_price(num_sims, S, K, r, v, T, delta_S, price_Sp,
			price_S, price_Sm);
	return (price_Sp - 2*price_S + price_Sm) / (delta_S * delta_S);
}

