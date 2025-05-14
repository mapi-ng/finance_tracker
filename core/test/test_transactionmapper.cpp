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
      storage::CSVRow{{"DATE", "2023-10-13"},
                      {"Credit", "100"},
                      {"Description", "Test"}},
      storage::CSVRow{{"Transaction Date", "13/10/2023"},
                      {"Debit", "100"},
                      {"ACTIVITY NAME", "Test"}},
      storage::CSVRow{{"dateOp", "13-10-2023"},
                      {"Amount", "100"},
                      {"desc", "Test"}}};

  const auto transactions = transactionMapper.map(rows);

  ASSERT_EQ(transactions.size(), 3);
  constexpr std::chrono::year_month_day expected_date{
      2023y, std::chrono::October, 13d};
  for (const auto& transaction : transactions) {
    EXPECT_EQ(transaction.getDate(), expected_date);
    EXPECT_EQ(transaction.getAmount(), 100);
    EXPECT_EQ(transaction.getDescription(), "Test");
  }
}