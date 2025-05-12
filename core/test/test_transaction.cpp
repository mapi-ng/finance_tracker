#include <gtest/gtest.h>

#include <chrono>

import Transaction;

using namespace std::literals::chrono_literals;

class TransactionTest : public ::testing::Test {
 public:
  void SetUp() override {}
  void TearDown() override {}

 protected:
  std::chrono::year_month_day date{2021y, std::chrono::January, 21d};
};

TEST_F(TransactionTest, BuildTransaction) {
  auto transaction =
      core::TransactionBuilder(date, 1).description("Test").build();
  EXPECT_FALSE(transaction.getId().is_nil());
  EXPECT_EQ(transaction.getAmount(), 1);
  EXPECT_EQ(transaction.getDate(), date);
  EXPECT_EQ(transaction.getDescription(), "Test");

  transaction.setDescription("New test");
  EXPECT_EQ(transaction.getDescription(), "New test");
}
