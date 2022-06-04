
#include "gtest/gtest.h"
#include "include/compiler.hxx"

TEST (Compiler, can_create_compiler) {
  
  ASSERT_NO_THROW (MyPascal::Compiler cm);
}