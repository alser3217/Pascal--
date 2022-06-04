
#include "include/parser.hxx"
#include "gtest/gtest.h"

TEST (Parser, can_create_parser) {

  ASSERT_NO_THROW (MyPascal::Parser ps);
}