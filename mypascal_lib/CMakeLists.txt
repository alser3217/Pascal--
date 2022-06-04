
include_directories("include")
include_directories("src")

set (Headers
  include/compiler.hxx
  include/handler.hxx
  include/lexer.hxx
  include/parser.hxx
  include/postfix.hxx
  include/variable.hxx
  include/data.hxx
  include/hierarchy_list.hxx
  include/hash_table.hxx
  include/executor.hxx
  include/exception.hxx
)

set (Sources
  src/compiler.cxx
  src/handler.cxx
  src/lexer.cxx
  src/parser.cxx
  src/postfix.cxx
  src/variable.cxx
  src/data.cxx
  src/hierarchy_list.cxx
  src/hash_table.cxx
  src/executor.cxx
  src/exception.cxx
)

add_library(
  mypascal_lib STATIC ${Sources} ${Headers})