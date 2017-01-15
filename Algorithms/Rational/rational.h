#ifndef _S16_RATIONAL_H__
#define _S16_RATIONAL_H__
#include <fstream>
#include "gcd.h"
#include <cmath>

#include <iostream>
using namespace std;

class rational {
public:
  rational(int n, int d) : n_(n), d_(d) { }
  ~rational() { }
  rational simplify();
  void simplify_in_place();
  int n() { return n_; }
  int d() { return d_; }
  rational operator+(rational r);
  rational operator-(rational r);
  rational operator*(rational r);
  rational operator/(rational r);
  double to_double();
  void operator+=(rational r);
  void operator-=(rational r);
  void operator*=(rational r);
  void operator/=(rational r);
  bool operator==(rational r);

private:
  int n_;
  int d_;
};

std::ostream& operator << (std::ostream& os, rational r) {
  if (r.d() == 1) {
    os << r.n();
  } else {
    os << r.n() << "/" << r.d();
  }
  return os;
}

rational rational::simplify() {
  int g = gcd(n_, d_);
  int n = n_ / g;
  int d = d_ / g;
  if (d < 0) {
    n = -n;
    d = -d;
  }
  return rational(n, d);
}

void rational::simplify_in_place() {
  int g = gcd(n_, d_);
  n_ /= g;
  d_ /= g;
  if (d_ < 0) {
    n_ = -n_;
    d_ = -d_;
  }
}

rational rational::operator+(rational r) {
  return rational(n_ * r.d_ + r.n_ * d_, d_ * r.d_).simplify();
}

rational rational::operator-(rational r) {
  return rational(n_ * r.d_ - r.n_ * d_, d_ * r.d_).simplify();
}

rational rational::operator*(rational r) {
  return rational(n_ * r.n_, d_ * r.d_).simplify();
}

rational rational::operator/(rational r) {
  return rational(n_ * r.d_, d_ * r.n_).simplify();
}

double rational::to_double() {
  return static_cast<double>(n_) / d_;
}

void rational::operator+=(rational r) {
  n_ *= r.d_;
  r.n_ *= d_;
  n_ += r.n_;
  int new_n = d_ * r.d_;
  d_ = new_n;
  r.d_ = new_n;  
}

void rational::operator-=(rational r) {
  n_ *= r.d_;
  r.n_ *= d_;
  n_ -= r.n_;
  int new_n = d_ * r.d_;
  d_ = new_n;
  r.d_ = new_n;
}

void rational::operator*=(rational r) {
  n_ *= r.n_;
  d_ *= r.d_;
  simplify_in_place();
}

void rational::operator/=(rational r) {
  n_ *= r.d_;
  d_ *= r.n_;
  simplify_in_place();
}

bool rational::operator==(rational r) {
  return n_ == r.n_ && d_ == r.d_;
}

#endif // _S16_RATIONAL_H__