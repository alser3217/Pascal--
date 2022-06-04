
#include "gtest/gtest.h"
#include "include/executor.hxx"

TEST (Executor, can_create_executor) {

  ASSERT_NO_THROW (MyPascal::Executor ex);
}