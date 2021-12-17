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

  double call = call_price(100, 101, 1.01, 10, 1);
  EXPECT_EQ(call, 10.4506);
}
