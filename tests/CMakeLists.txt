cmake_minimum_required(VERSION 3.15)

set (Sources
  test_parser.cxx
  test_postfix.cxx
  test_table.cxx
  test_compiler.cxx
  test_exception.cxx
  test_hierarchy_list.cxx
  test_executor.cxx
  test_variable.cxx
  test_lexer.cxx
)

include_directories("../mypascal_lib")


add_executable(tests ${Sources})

target_link_libraries(tests PUBLIC
  gtest_main
  mypascal_lib
)

add_test(
  NAME tests
  COMMAND tests
)