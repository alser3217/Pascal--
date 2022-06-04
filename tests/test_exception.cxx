
#include "gtest/gtest.h"
#include "include/exception.hxx"

TEST (Exception, can_create_exception) {

  ASSERT_NO_THROW (MyPascal::Exception ex);
}

TEST (Exception, can_get_info) {
  MyPascal::Exception ex;

  ASSERT_NO_THROW (ex.info());
}

TEST(Exception, can_get_code) {
  MyPascal::Exception ex(2);

  EXPECT_EQ (2, ex.get_code());
}