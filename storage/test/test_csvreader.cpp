#include <gtest/gtest.h>

import CSVReader;

TEST(CSVImporterTest, Construction) {
  std::shared_ptr<storage::CSVReader> reader;
  ASSERT_NO_THROW(reader = std::make_shared<storage::CSVReader>(
                      "test-data/test-single-record-comma.csv"));
  ASSERT_TRUE(reader);
  EXPECT_NO_THROW(reader.reset());
}

TEST(CSVImporterTest, InvalidPath) {
  EXPECT_THROW(storage::CSVReader reader("invalid_path.csv"),
               storage::CSVImporterException);
}

TEST(CSVImporterTest, ImportWithDefaultConfig) {
  const storage::CSVReader reader("test-data/test-single-record-comma.csv");
  // Headers contain commas, so inconsistent number of columns is expected
  EXPECT_THROW(std::ignore = reader.read(), storage::CSVImporterException);
}

TEST(CSVImporterTest, ImportWithCustomConfig) {
  const storage::CSVReader reader("test-data/test-single-record.csv",
                                      {.delimiter = ';'});
  const auto &results = reader.read();
  EXPECT_EQ(results.size(), 1);
}

TEST(csviMPorterTest, ImportOnlyHeader) {
  const storage::CSVReader reader("test-data/test-only-header.csv",
                                      {.delimiter = ';'});
  const auto &results = reader.read();
  EXPECT_TRUE(results.empty());
}

TEST(CSVImporterTest, ImportWithoutHeader) {
  const storage::CSVReader readerWrongConfig(
      "test-data/test-no-header.csv", {.delimiter = ';', .has_header = true});
  EXPECT_TRUE(readerWrongConfig.read().empty());

  const storage::CSVReader reader("test-data/test-no-header.csv",
                                      {.delimiter = ';', .has_header = false});
  const auto &results = reader.read();
  EXPECT_FALSE(results.empty());

  const storage::CSVRow row{
      {"0", "12"},  {"1", "CARD_TRANSACTION_OUT"}, {"2", "-79.6"},
      {"3", "CHF"}, {"4", R"("""Geneva, CH""")"},  {"5", ""}};
  EXPECT_EQ(results[0], row);
}
