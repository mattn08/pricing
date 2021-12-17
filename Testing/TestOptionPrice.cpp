#include <gtest/gtest.h>
#include "Black_scholes.h"
#include <iostream>

using namespace std;

TEST(PriceTest, SingleOption) {

  double S = 100.0;
  double K = 100.0;
  double r = 0.05;
  double v = 0.2;
  double T = 1.0;

  double call = call_price(S, K, r, v, T);

  EXPECT_FLOAT_EQ(call, 10.450576);
}

TEST(PriceTest, CallOption) {

  double S = 14.58;
  double K = 17.0;
  double r = 0.05;
  double v = 0.84;
  // July 15th 2022
  double T = 0.6;

  double call = call_price(S, K, r, v, T);

  EXPECT_FLOAT_EQ(call, 3.0733445);
}