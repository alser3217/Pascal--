
#include "gtest/gtest.h"
#include "include/variable.hxx"

TEST (Variable, can_create_variable) {
  ASSERT_NO_THROW (MyPascal::Variable var());
}

TEST (Variable, can_get_variable_name) {
  MyPascal::Variable var("var", 5, MyPascal::vType::INTEGER);

  EXPECT_EQ ("var", var.get_name());
}

TEST (Variable, can_get_variable_value) {
  MyPascal::Variable var("var", 5, MyPascal::vType::INTEGER);

  EXPECT_EQ (5, var.get_value());
}

TEST (Variable, can_get_variable_type) {
  MyPascal::Variable var("var", 5, MyPascal::vType::INTEGER);

  EXPECT_EQ (MyPascal::vType::INTEGER, var.get_vtype());
}

TEST (Variable, can_set_value) {
  MyPascal::Variable var("var");

  ASSERT_NO_THROW (var.set_value(5));
}