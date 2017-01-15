#include "../test/logging.h"
#include "rational.h"
#include <iostream>

int main() {
  rational r1(1,2);
  rational r2(2,3);
  rational r3 = r1 + r2; // Sum
  rational r4 = r1 - r2; // Difference
  rational r5 = r1 * r2; // Product
  rational r6 = r1 / r2; // Quotient

  CHECK_EQ(r3, rational(7,6));
  CHECK_EQ(r4, rational(-1,6));
  CHECK_EQ(r5, rational(1,3));
  CHECK_EQ(r6, rational(3,4));
  CHECK_EQ(r1.to_double(), .5);

  rational temp1 = r1;
  rational temp2 = r1;
  rational temp3 = r1;
  rational temp4 = r1;
  temp1 += r2;
  temp2 -= r2;
  temp3 *= r2;
  temp4 /= r2;

  CHECK_EQ(temp1, rational(7,6));
  CHECK_EQ(temp2, rational(-1,6));
  CHECK_EQ(temp3, rational(1,3));
  CHECK_EQ(temp4, rational(3,4));

}