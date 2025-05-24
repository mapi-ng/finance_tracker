#include <gtest/gtest.h>
#include <uuid.h>

import Utils;

TEST(GenerateUuid, UuidFromData) {
  const auto uuid1 = utils::generateUuidFromData("test_data1");
  EXPECT_FALSE(uuid1.is_nil());
  const auto uuid2 = utils::generateUuidFromData("test_data2");
  EXPECT_FALSE(uuid2.is_nil());
  EXPECT_NE(uuid1, uuid2);  // Different UUIDs for different data
  const auto uuid3 = utils::generateUuidFromData("test_data1");
  EXPECT_FALSE(uuid3.is_nil());
  EXPECT_EQ(uuid1, uuid3);  // Same UUID for same data
}

TEST(GenerateUuid, UuidGeneration) {
  const auto uuid = utils::generateUuid();
  EXPECT_FALSE(uuid.is_nil());
}

TEST(GenerateUuid, UuidFromString) {
  const std::string uuid_str = "12345678-1234-5678-1234-567812345678";
  const auto id = utils::generateUuid(uuid_str);
  EXPECT_FALSE(id.is_nil());
  EXPECT_EQ(uuids::to_string(id), uuid_str);
}