#include <gtest/gtest.h>

import Utils;

TEST(GenerateUuid, UuidFromData) {
  const auto uuid1 = utils::generateUuidFromData("test_data1");
  EXPECT_FALSE(uuid1.is_nil());
  const auto uuid2 = utils::generateUuidFromData("test_data2");
  EXPECT_NE(uuid1, uuid2);  // Different UUIDs for different data
  const auto uuid3 = utils::generateUuidFromData("test_data1");
  EXPECT_EQ(uuid1, uuid3);  // Same UUID for same data
}

TEST(GenerateUuid, UuidGeneration) {
  auto uuid = utils::generateUuid();
  EXPECT_FALSE(uuid.is_nil());
}

TEST(GenerateUuid, UuidFromString) {
  std::string uuid_str = "12345678-1234-5678-1234-567812345678";
  auto uuid = utils::generateUuid(uuid_str);
  EXPECT_FALSE(uuid.is_nil());
}