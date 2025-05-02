#include <gtest/gtest.h>

import Utils;

TEST(GenerateUuid, UuidGeneration) {
  auto uuid = utils::generateUuid();
  EXPECT_FALSE(uuid.is_nil());
}

TEST(GenerateUuid, UuidFromString) {
  std::string uuid_str = "12345678-1234-5678-1234-567812345678";
  auto uuid = utils::generateUuid(uuid_str);
  EXPECT_FALSE(uuid.is_nil());
}