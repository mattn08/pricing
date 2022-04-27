
#pragma once

class VanillaOption {

private:
	void init();
	void copy(const VanillaOption& rhs) ;
	double K; // Strike
	double r; // Risk-free rate
	double T; // Maturity time
	double S; // Underlying asset price
	double sigma; // Volatility of underlying asset

public:

	VanillaOption();
	VanillaOption(const double& K, const double& r,
				  const double& T, const double& S,
				  const double& sigma);

	VanillaOption(const VanillaOption& rhs);
	VanillaOption& operator=(const VanillaOption& rhs);
	virtual ~VanillaOption() {};

	// Getters
	double getK() const;
	double getr() const;
	double getT() const;
	double getS() const;
	double getsigma() const;

	// Option price calculation methods
	double calccallprice() const;
	double calcputprice() const;
};
