#include "../test/logging.h"
#include "complex.h"
#include "../numeric/exp.h"
#include <iostream>
#include <cmath>

int main() {
  complex r1(1,2);
  complex r2(2,3);
  complex r3 = r1 + r2; // Sum
  complex r4 = r1 - r2; // Difference
  complex r5 = r1 * r2; // Product
  complex r6 = r1 / r2; // Quotient

  CHECK_EQ(r3, complex(3,5));
  CHECK_EQ(r4, complex(-1,-1));
  CHECK_EQ(r5, complex(-4,7));
  CHECK_EQ(r6, complex(8/13.0,1/13.0));

  complex temp1 = r1;
  complex temp2 = r1;
  complex temp3 = r1;
  complex temp4 = r1;
  temp1 += r2;
  temp2 -= r2;
  temp3 *= r2;
  temp4 /= r2;

  CHECK_EQ(temp1, complex(3,5));
  CHECK_EQ(temp2, complex(-1,-1));
  CHECK_EQ(temp3, complex(-4,7));
  CHECK_EQ(temp4, complex(8/13.0,1/13.0));

  CHECK_EQ(complex(3,4).norm(), 5);

  complex exp_pi_i = s16::exp(complex(0, M_PI));
  CHECK_LT(fabs(exp_pi_i.re() - -1), 1e-10);
  CHECK_LT(fabs(exp_pi_i.im()), 1e-10);
  //std::cout << exp_pi_i << std::endl;
  complex exact_ans(-1, 0);
  CHECK_LT((exp_pi_i - exact_ans).norm(), 1e-10);
}