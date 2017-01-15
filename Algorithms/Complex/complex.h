#ifndef _S16_complex_H__
#define _S16_complex_H__
#include <ostream>
#include <cmath>

class complex {
public:
  complex(double n, double d) : re_(n), im_(d) { }
  complex(double n) : re_(n), im_(0) { }
  ~complex() { }
  double re() { return re_; }
  double im() { return im_; }
  double norm() { return std::sqrt(re_ * re_ + im_ * im_); }
  complex operator+(complex r);
  complex operator-(complex r);
  complex operator*(complex r);
  complex operator/(complex r);
  void operator+=(complex r);
  void operator-=(complex r);
  void operator*=(complex r);
  void operator/=(complex r);
  bool operator==(complex r);

private:
  double re_;
  double im_;
};

std::ostream& operator << (std::ostream& os, complex r) {
  os << r.re() << " + " << r.im() << "i";
  return os;
}

complex complex::operator+(complex r) {
  return complex(re_ + r.re_, im_ + r.im_);
}

complex complex::operator-(complex r) {
  return complex(re_ - r.re_, im_ - r.im_);
}

complex complex::operator*(complex r) {
  return complex(re_ * r.re_ - im_ * r.im_, re_ * r.im_ + r.re_ * im_);
}

complex complex::operator/(complex r) {
  double denom = r.re_ * r.re_ + r.im_ * r.im_;
  return complex((re_*r.re_ + im_*r.im_)/denom, -(re_*r.im_ - r.re_*im_)/denom);
}

void complex::operator+=(complex r) {
  re_ += r.re_;
  im_ += r.im_;  
}

void complex::operator-=(complex r) {
  re_ -= r.re_;
  im_ -= r.im_;
}

void complex::operator*=(complex r) {
  double temp = re_;
  re_ = re_ * r.re_ - (im_ * r.im_);
  im_ = temp * r.im_ + r.re_ * im_;
}

void complex::operator/=(complex r) {
  int temp = re_;
  double denom = r.re_ * r.re_ + r.im_ * r.im_;
  re_ = (re_*r.re_ + im_*r.im_)/denom;
  im_ = -(temp*r.im_ - r.re_*im_)/denom;
}

bool complex::operator==(complex r) {
  return re_ == r.re_ && im_ == r.im_;
}

#endif // _S16_complex_H__