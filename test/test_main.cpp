#include "polinom.h"
#include <gtest/gtest.h>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(CorePolynomialTests, EmptyCreation) {
  Polinom pBase;
  Polinom pEmpty;
  EXPECT_TRUE(pBase == pEmpty);
}

TEST(CorePolynomialTests, DeepCopyVerification) {
  Polinom source;
  source.addMonom(2.5, 321);
  Polinom target = source;
  target.addMonom(1.5, 321);

  EXPECT_FALSE(source == target);
}

TEST(MonomialOperations, InsertSingle) {
  Polinom p;
  p.addMonom(7.2, 555);
  Polinom ref;
  ref.addMonom(7.2, 555);
  EXPECT_TRUE(p == ref);
}

TEST(MonomialOperations, MergeIdenticalPowers) {
  Polinom p;
  p.addMonom(4.0, 111);
  p.addMonom(-2.0, 111);
  p.addMonom(1.5, 111);

  Polinom ref;
  ref.addMonom(3.5, 111);
  EXPECT_TRUE(p == ref);
}

TEST(MonomialOperations, ZeroAnnihilation) {
  Polinom p;
  p.addMonom(8.8, 999);
  p.addMonom(-8.8, 999);
  Polinom empty;
  EXPECT_TRUE(p == empty);
}

TEST(ArithmeticTests, AddPolynomials) {
  Polinom pA, pB, ref;
  pA.addMonom(3.0, 222);
  pB.addMonom(4.0, 222);
  pB.addMonom(1.0, 100);

  ref.addMonom(7.0, 222);
  ref.addMonom(1.0, 100);

  EXPECT_TRUE((pA + pB) == ref);
}

TEST(ArithmeticTests, SubtractPolynomials) {
  Polinom pA, pB, ref;
  pA.addMonom(5.0, 300);
  pA.addMonom(2.0, 20);
  pB.addMonom(3.0, 300);
  pB.addMonom(2.0, 20);

  ref.addMonom(2.0, 300);
  EXPECT_TRUE((pA - pB) == ref);
}

TEST(ArithmeticTests, ScalarMult) {
  Polinom p, ref;
  p.addMonom(2.5, 100);
  ref.addMonom(-7.5, 100);
  EXPECT_TRUE((p * -3.0) == ref);
}

TEST(ArithmeticTests, MultiplyPolynomialsValid) {
  Polinom pA, pB, ref;
  pA.addMonom(2.0, 110);
  pB.addMonom(3.0, 11);

  ref.addMonom(6.0, 121);
  EXPECT_TRUE((pA * pB) == ref);
}

TEST(ArithmeticTests, MultiplyPolynomialsOverflowError) {
  Polinom pA, pB;
  pA.addMonom(1.0, 600);
  pB.addMonom(1.0, 400);
  EXPECT_THROW(pA * pB, std::runtime_error);
}

TEST(ArithmeticTests, MultiplyPolynomialsMaxBoundary) {
  Polinom pA, pB;
  pA.addMonom(1.0, 500);
  pB.addMonom(1.0, 499);
  EXPECT_NO_THROW(pA * pB);
}