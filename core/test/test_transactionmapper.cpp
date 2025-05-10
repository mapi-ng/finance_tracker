#include <gtest/gtest.h>

import TransactionMapper;

TEST(TransactionMapperTest, Construction) {
  std::shared_ptr<TransactionMapper> mapper;
  ASSERT_NO_THROW(mapper = std::make_shared<TransactionMapper>());
  ASSERT_TRUE(mapper);
  EXPECT_NO_THROW(mapper.reset());
}