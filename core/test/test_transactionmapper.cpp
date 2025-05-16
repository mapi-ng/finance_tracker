#include <gtest/gtest.h>

#include <chrono>

import Transaction;
import CSVReader;
import Exceptions;

using namespace std::literals::chrono_literals;

TEST(TransactionMapperTest, Construction) {
  ASSERT_THROW(core::TransactionMapper("invalid-path.json"),
               utils::FailedToOpenFile);
  ASSERT_THROW(core::TransactionMapper("test-data/test-mapping-bad.json"),
               utils::FailedToOpenFile);
  ASSERT_NO_THROW(
      core::TransactionMapper transactionMapper("test-data/test-mapping.json"));
}

TEST(TransactionMapperTest, Map) {
  core::TransactionMapper transactionMapper("test-data/test-mapping.json");
  std::vector rows = {storage::CSVRow{{"DATE", "2023-10-13"},
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

TEST(TransactionMapperTest, WrongDateFormat) {
  core::TransactionMapper transactionMapper("test-data/test-mapping.json");
  std::vector rows = {storage::CSVRow{{"dateOp", "2023/10/13"},
                                      {"Amount", "100"},
                                      {"desc", "Test"}}};

  ASSERT_THROW(std::ignore = transactionMapper.map(rows),
               core::TransactionParsingError);
}

TEST(TransactionMapperTest, DateNoMapping) {
  core::TransactionMapper transactionMapper("test-data/test-mapping.json");
  std::vector rows = {storage::CSVRow{{"unsupportedDateColumn", "13-10-2023"},
                                      {"Amount", "100"},
                                      {"desc", "Test"}}};

  ASSERT_THROW(std::ignore = transactionMapper.map(rows),
               core::TransactionParsingError);
}

TEST(TransactionMapperTest, AmountNoMapping) {
  core::TransactionMapper transactionMapper("test-data/test-mapping.json");
  std::vector rows = {storage::CSVRow{{"dateOp", "13-10-2023"},
                                      {"unsupportedAmountColumn", "100"},
                                      {"desc", "Test"}}};

  ASSERT_THROW(std::ignore = transactionMapper.map(rows),
               core::TransactionParsingError);
}