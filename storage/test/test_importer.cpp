#include <gtest/gtest.h>

import CSVImporter;

class ImporterTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Code to set up the test environment
  }

  void TearDown() override {
    // Code to clean up after the test
  }

  std::shared_ptr<storage::Importer> importer_;
};

TEST_F(ImporterTest, CSVImporterConstruction) {
  ASSERT_NO_THROW(importer_ =
                      std::make_shared<storage::CSVImporter>("test.csv"));
  ASSERT_TRUE(importer_);
  EXPECT_NO_THROW(importer_.reset());
}

TEST_F(ImporterTest, CSVImporterInvalidPath) {
  EXPECT_THROW(
      importer_ = std::make_shared<storage::CSVImporter>("invalid_path.csv"),
      storage::ImporterException);
}

TEST_F(ImporterTest, CSVImporterImport) {
  importer_ = std::make_shared<storage::CSVImporter>("test.csv");
  ASSERT_TRUE(importer_);
  EXPECT_TRUE(importer_->import().empty());
}

TEST_F(ImporterTest, CSVImporterWithConfig) {
  storage::CSVConfig config{.delimiter = ';', .has_header = true};

  importer_ = std::make_shared<storage::CSVImporter>("test.csv", config);
  ASSERT_TRUE(importer_);
  EXPECT_TRUE(importer_->import().empty());
}