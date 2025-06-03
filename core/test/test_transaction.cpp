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

TEST(Transaction, UUIDGeneration) {
  core::Transaction transaction(100);
  EXPECT_FALSE(transaction.getId().is_nil());
}

TEST(Transaction, TimestampDefault) {
  auto before = std::chrono::system_clock::now();
  core::Transaction transaction(1);
  auto after = std::chrono::system_clock::now();
  auto timestamp = transaction.getTimestamp();
  EXPECT_GE(timestamp, before);
  EXPECT_LE(timestamp, after);
}

TEST(Transaction, TimestampExplicit) {
  auto arbitraryTimestamp =
      std::chrono::system_clock::now() - std::chrono::hours(24);
  core::Transaction transaction(1, arbitraryTimestamp);
  EXPECT_EQ(transaction.getTimestamp(), arbitraryTimestamp);
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
