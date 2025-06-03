#include <gtest/gtest.h>

#include <chrono>

import Transaction;
import CSVReader;

using namespace std::literals::chrono_literals;

TEST(TransactionMapperTest, Construction) {
  ASSERT_THROW(core::TransactionMapper("invalid-path.json"),
               std::runtime_error);
  ASSERT_NO_THROW(
      core::TransactionMapper transactionMapper("test-data/test-mapping.json"));
}

TEST(TransactionMapperTest, Map) {
  core::TransactionMapper transactionMapper("test-data/test-mapping.json");
  std::vector<storage::CSVRow> rows = {
      {{"DATE", "2023-10-13"}, {"Credit", "100"}, {"Description", "Test"}}};

  auto transactions = transactionMapper.map(rows);

  ASSERT_EQ(transactions.size(), 1);
  constexpr std::chrono::year_month_day expected_date{
      2023y, std::chrono::October, 13d};
  EXPECT_EQ(transactions[0].getDate(), expected_date);
  EXPECT_EQ(transactions[0].getAmount(), 100);
  EXPECT_EQ(transactions[0].getDescription(), "Test");
}