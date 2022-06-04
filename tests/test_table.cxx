
#include "gtest/gtest.h"
#include "include/hash_table.hxx"

TEST (HashTable, can_create_arr_table) {
	ASSERT_NO_THROW (MyPascal::HashTable table);
}

TEST (HashTable, can_insert_variable) {
	MyPascal::HashTable table;
	MyPascal::Variable var;

	ASSERT_NO_THROW (table.insert(var));
}

TEST (HashTable, can_find_polynomial) {
	MyPascal::HashTable table;

	ASSERT_NO_THROW (table.find("var"));
}

TEST (HashTable, cant_insert_data_with_no_unique_key) {
	MyPascal::HashTable table;
	table.insert(MyPascal::Variable("key"));

	EXPECT_EQ (false, table.insert(MyPascal::Variable("key")));
}

TEST (HashTable, cant_find_not_existing_element) {
	MyPascal::HashTable table;

	EXPECT_EQ (nullptr, table.findobj("key"));
}

TEST (HashTable, can_find_existing_element) {
	MyPascal::HashTable table;
	table.insert(MyPascal::Variable("key"));

	EXPECT_NE (nullptr, table.findobj("key"));
}

TEST (HashTable, can_find_existing_element_values) {
	MyPascal::HashTable table;
	table.insert(MyPascal::Variable("key", 5.5));

	EXPECT_EQ (5.5, table.find("key"));
}

TEST (HashTable, cant_find_not_existing_element_value) {
	MyPascal::HashTable table;

	EXPECT_EQ(DBL_MAX, table.find("key"));
}