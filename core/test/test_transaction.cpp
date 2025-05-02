#include <gtest/gtest.h>

import Transaction;

class TransactionTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Initialize shared resources
  }

  void TearDown() override {
    // Clean up resources if needed
  }

  core::Transaction transaction{100};
};

TEST(TransactionUUID, UUIDGeneration) {
  core::Transaction transaction(100);
  EXPECT_FALSE(transaction.getId().is_nil());
}

TEST_F(TransactionTest, ParameterizedConstructor) {
  EXPECT_EQ(transaction.getAmount(), 100);
}

TEST_F(TransactionTest, SetAmount) {
  transaction.setAmount(200);
  EXPECT_EQ(transaction.getAmount(), 200);
}

TEST_F(TransactionTest, NegativeAmount) {
  transaction.setAmount(-50);
  EXPECT_EQ(transaction.getAmount(), -50);
}
