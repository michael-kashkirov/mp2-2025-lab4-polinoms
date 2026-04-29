#include "polinom.h"

Polinom::Polinom() {
  dummyHead = new Monom(0.0, -1);
  dummyHead->nextNode = dummyHead;
}

Polinom::Polinom(const Polinom &other) {
  dummyHead = new Monom(0.0, -1);
  dummyHead->nextNode = dummyHead;
  Monom *curr = other.dummyHead->nextNode;
  while (curr != other.dummyHead) {
    addMonom(curr->coef, curr->pwr);
    curr = curr->nextNode;
  }
}

Polinom::~Polinom() {
  Monom *curr = dummyHead->nextNode;
  while (curr != dummyHead) {
    Monom *temp = curr;
    curr = curr->nextNode;
    delete temp;
  }
  delete dummyHead;
}

void Polinom::addMonom(double v, int k) {
  if (std::abs(v) < 1e-10)
    return;

  Monom *prev = dummyHead;
  Monom *curr = dummyHead->nextNode;

  while (curr != dummyHead && curr->pwr > k) {
    prev = curr;
    curr = curr->nextNode;
  }

  if (curr != dummyHead && curr->pwr == k) {
    curr->coef += v;
    if (std::abs(curr->coef) < 1e-10) {
      prev->nextNode = curr->nextNode;
      delete curr;
    }
  } else {
    Monom *newNode = new Monom(v, k, curr);
    prev->nextNode = newNode;
  }
}

void Polinom::print() const {
  Monom *curr = dummyHead->nextNode;
  if (curr == dummyHead) {
    std::cout << "0";
    return;
  }

  bool first = true;
  while (curr != dummyHead) {
    double c = curr->coef;
    if (!first && c > 0)
      std::cout << " + ";
    if (c < 0)
      std::cout << " - ";

    double abs_c = std::abs(c);
    if (std::abs(abs_c - 1.0) > 1e-10 || curr->pwr == 0) {
      if (first && c < 0)
        std::cout << "-";
      std::cout << abs_c;
    } else if (first && c < 0) {
      std::cout << "-";
    }

    int p = curr->pwr;
    int x = p / 100;
    int y = (p / 10) % 10;
    int z = p % 10;

    if (x) {
      std::cout << "x";
      if (x > 1)
        std::cout << "^" << x;
    }
    if (y) {
      std::cout << "y";
      if (y > 1)
        std::cout << "^" << y;
    }
    if (z) {
      std::cout << "z";
      if (z > 1)
        std::cout << "^" << z;
    }

    curr = curr->nextNode;
    first = false;
  }
  std::cout << std::endl;
}

Polinom &Polinom::operator=(const Polinom &other) {
  if (this == &other)
    return *this;
  Monom *curr = dummyHead->nextNode;
  while (curr != dummyHead) {
    Monom *temp = curr;
    curr = curr->nextNode;
    delete temp;
  }
  dummyHead->nextNode = dummyHead;
  Monom *src = other.dummyHead->nextNode;
  while (src != other.dummyHead) {
    addMonom(src->coef, src->pwr);
    src = src->nextNode;
  }
  return *this;
}

Polinom Polinom::operator+(const Polinom &other) const {
  Polinom res(*this);
  Monom *src = other.dummyHead->nextNode;
  while (src != other.dummyHead) {
    res.addMonom(src->coef, src->pwr);
    src = src->nextNode;
  }
  return res;
}

Polinom Polinom::operator-(const Polinom &other) const {
  Polinom res(*this);
  Monom *src = other.dummyHead->nextNode;
  while (src != other.dummyHead) {
    res.addMonom(-src->coef, src->pwr);
    src = src->nextNode;
  }
  return res;
}

Polinom Polinom::operator*(const Polinom &other) const {
  Polinom res;
  Monom *a = dummyHead->nextNode;
  while (a != dummyHead) {
    Monom *b = other.dummyHead->nextNode;
    while (b != other.dummyHead) {
      int p1 = a->pwr, p2 = b->pwr;

      int x1 = p1 / 100, y1 = (p1 / 10) % 10, z1 = p1 % 10;
      int x2 = p2 / 100, y2 = (p2 / 10) % 10, z2 = p2 % 10;

      if (x1 + x2 > 9 || y1 + y2 > 9 || z1 + z2 > 9) {
        throw std::runtime_error("Degree overflow");
      }

      res.addMonom(a->coef * b->coef, p1 + p2);
      b = b->nextNode;
    }
    a = a->nextNode;
  }
  return res;
}

Polinom Polinom::operator*(double factor) const {
  Polinom res;
  Monom *curr = dummyHead->nextNode;
  while (curr != dummyHead) {
    res.addMonom(curr->coef * factor, curr->pwr);
    curr = curr->nextNode;
  }
  return res;
}

bool Polinom::operator==(const Polinom &other) const {
  Monom *a = dummyHead->nextNode;
  Monom *b = other.dummyHead->nextNode;
  while (a != dummyHead && b != other.dummyHead) {
    if (a->pwr != b->pwr || std::abs(a->coef - b->coef) > 1e-10)
      return false;
    a = a->nextNode;
    b = b->nextNode;
  }
  return a == dummyHead && b == other.dummyHead;
}