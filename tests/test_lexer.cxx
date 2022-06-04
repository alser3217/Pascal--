
#include "gtest/gtest.h"
#include "include/lexer.hxx"

TEST (Lexer, can_create_lexer) {

  ASSERT_NO_THROW (MyPascal::Lexer lx);
}