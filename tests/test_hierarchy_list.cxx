
#include "gtest/gtest.h"
#include "include/hierarchy_list.hxx"

TEST (HString, can_create_hstring) {

  ASSERT_NO_THROW (MyPascal::HString str());
}

TEST (HString, can_get_data) {
  MyPascal::HString str("data", 2, 10, MyPascal::Type::ASSIGN);

  EXPECT_EQ ("data", str.get_data());
}

TEST (HString, can_get_level) {
  MyPascal::HString str("data", 2, 10, MyPascal::Type::ASSIGN);

  EXPECT_EQ (2, str.get_level());
}

TEST (HString, can_get_line_number) {
  MyPascal::HString str("data", 2, 10, MyPascal::Type::ASSIGN);

  EXPECT_EQ (10, str.get_lnumber());
}

TEST (HString, can_get_type) {
  MyPascal::HString str("data", 2, 10, MyPascal::Type::ASSIGN);

  EXPECT_EQ (MyPascal::Type::ASSIGN, str.get_type());
}

TEST (HString, can_set_type) {
  MyPascal::HString str;

  ASSERT_NO_THROW (str.set_type(MyPascal::Type::ASSIGN));
}

TEST (HLink, can_create_hlink) {

  ASSERT_NO_THROW (MyPascal::HLink link());
}

TEST (HList, can_create_hlist) {

  ASSERT_NO_THROW (MyPascal::HList list());
}

TEST (HList, can_insert_next) {
  MyPascal::HList list;
  MyPascal::HString str;

  ASSERT_NO_THROW (list.insert_next(str));
}

TEST (HList, can_insert_down) {
  MyPascal::HList list;
  MyPascal::HString str1, str2;
  list.insert_next(str1);

  ASSERT_NO_THROW (list.insert_down(str2));
}

TEST (HList, can_pop) {
  MyPascal::HList list;
  MyPascal::HString str1, str2;

  list.insert_next(str1);
  list.insert_down(str2);

  ASSERT_NO_THROW (list.pop());
}

TEST (HList, can_get_head) {
  MyPascal::HList list;

  ASSERT_NO_THROW (list.get_head());
}