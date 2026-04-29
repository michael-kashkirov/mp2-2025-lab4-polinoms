#pragma once
#include <cmath>
#include <iostream>

struct Monom {
  double coef;
  int pwr;
  Monom *nextNode;

  Monom(double c = 0.0, int p = 0, Monom *n = nullptr)
      : coef(c), pwr(p), nextNode(n) {}
};

class Polinom {
private:
  Monom *dummyHead;

public:
  Polinom();
  Polinom(const Polinom &other);
  ~Polinom();

  void addMonom(double v, int k);
  void print() const;

  Polinom &operator=(const Polinom &other);
  Polinom operator+(const Polinom &other) const;
  Polinom operator-(const Polinom &other) const;
  Polinom operator*(const Polinom &other) const;
  Polinom operator*(double factor) const;
  bool operator==(const Polinom &other) const;
};