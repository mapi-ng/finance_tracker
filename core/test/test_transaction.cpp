#include <gtest/gtest.h>

#include <chrono>

import Transaction;

using namespace std::literals::chrono_literals;

class TransactionTest : public ::testing::Test {
 public:
  void SetUp() override {}
  void TearDown() override {}

 protected:
  std::chrono::year_month_day date_{2021y, std::chrono::January, 21d};
};

TEST_F(TransactionTest, BuildTransaction) {
  const auto transaction = core::TransactionBuilder(date_, 1)
                               .description("Test")
                               .category("Shopping")
                               .build();
  EXPECT_FALSE(transaction.getId().is_nil());
  EXPECT_EQ(transaction.getAmount(), 1);
  EXPECT_EQ(transaction.getDate(), date_);
  EXPECT_EQ(transaction.getDescription(), "Test");
  EXPECT_EQ(transaction.getCategory(), "Shopping");
}

TEST_F(TransactionTest, DistinctId) {
  const auto transaction = core::TransactionBuilder(date_, 1)
                               .description("Test")
                               .category("Shopping")
                               .build();
  const auto transaction_same = core::TransactionBuilder(date_, 1)
                                    .description("Test")
                                    .category("Shopping")
                                    .build();
  const auto transaction_other = core::TransactionBuilder(date_, 2)
                                     .description("Test")
                                     .category("Shopping")
                                     .build();
  EXPECT_EQ(transaction_same.getId(), transaction.getId());
  EXPECT_NE(transaction_other.getId(), transaction.getId());
}

TEST_F(TransactionTest, InvalidTransaction) {
  // Invalid date
  EXPECT_THROW(core::TransactionBuilder({}, 1)
                   .description("Desc")
                   .category("Cat")
                   .build(),
               core::TransactionException);
  // Invalid amount
  EXPECT_THROW(core::TransactionBuilder(date_, 0)
                   .description("Desc")
                   .category("Cat")
                   .build(),
               core::TransactionException);
  // Invalid description and category
  EXPECT_THROW(core::TransactionBuilder(date_, 1)
                   .description("")
                   .category("Cat")
                   .build(),
               core::TransactionException);
  EXPECT_THROW(core::TransactionBuilder(date_, 1)
                   .description("Desc")
                   .category("")
                   .build(),
               core::TransactionException);
}