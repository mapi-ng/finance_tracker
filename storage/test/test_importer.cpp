#include <gtest/gtest.h>

import CSVImporter;

TEST(CSVImporterTest, Construction) {
  std::shared_ptr<storage::CSVImporter> importer;
  ASSERT_NO_THROW(importer = std::make_shared<storage::CSVImporter>(
                      "test-data/test-single-record-comma.csv"));
  ASSERT_TRUE(importer);
  EXPECT_NO_THROW(importer.reset());
}

TEST(CSVImporterTest, InvalidPath) {
  EXPECT_THROW(storage::CSVImporter importer("invalid_path.csv"),
               storage::CSVImporterException);
}

TEST(CSVImporterTest, ImportWithDefaultConfig) {
  const storage::CSVImporter importer("test-data/test-single-record-comma.csv");
  // Headers contain commas, so inconsistent number of columns is expected
  EXPECT_THROW(importer.read(), storage::CSVImporterException);
}

TEST(CSVImporterTest, ImportWithCustomConfig) {
  const storage::CSVImporter importer("test-data/test-single-record.csv",
                                      {.delimiter = ';'});
  const auto &results = importer.read();
  EXPECT_EQ(results.size(), 1);
}

TEST(csviMPorterTest, ImportOnlyHeader) {
  const storage::CSVImporter importer("test-data/test-only-header.csv",
                                      {.delimiter = ';'});
  const auto &results = importer.read();
  EXPECT_TRUE(results.empty());
}

TEST(CSVImporterTest, ImportWithoutHeader) {
  const storage::CSVImporter importerWrongConfig(
      "test-data/test-no-header.csv", {.delimiter = ';', .has_header = true});
  EXPECT_TRUE(importerWrongConfig.read().empty());

  const storage::CSVImporter importer("test-data/test-no-header.csv",
                                      {.delimiter = ';', .has_header = false});
  const auto &results = importer.read();
  EXPECT_FALSE(results.empty());

  const storage::CSVRow row{
      {"0", "12"},  {"1", "CARD_TRANSACTION_OUT"}, {"2", "-79.6"},
      {"3", "CHF"}, {"4", R"("""Geneva, CH""")"},  {"5", ""}};
  EXPECT_EQ(results[0], row);
}
