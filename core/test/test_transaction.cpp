#include <gtest/gtest.h>

import Transaction;

TEST(TransactionTest, UUIDGeneration) {
  core::Transaction transaction(100);
  EXPECT_FALSE(transaction.getId().is_nil());
}

TEST(TransactionTest, TimestampDefault) {
  auto before = std::chrono::system_clock::now();
  core::Transaction transaction(1);
  auto after = std::chrono::system_clock::now();
  auto timestamp = transaction.getTimestamp();
  EXPECT_GE(timestamp, before);
  EXPECT_LE(timestamp, after);
}

TEST(TransactionTest, TimestampExplicit) {
  auto arbitraryTimestamp =
      std::chrono::system_clock::now() - std::chrono::hours(24);
  core::Transaction transaction(1, arbitraryTimestamp);
  EXPECT_EQ(transaction.getTimestamp(), arbitraryTimestamp);
}

TEST(TransactionTest, SetAmount) {
  core::Transaction transaction(1);
  EXPECT_EQ(transaction.getAmount(), 1);
  transaction.setAmount(200);
  EXPECT_EQ(transaction.getAmount(), 200);
}

TEST(TransactionTest, NegativeAmount) {
  core::Transaction transaction(-50);
  EXPECT_EQ(transaction.getAmount(), -50);
}
