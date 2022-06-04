add_executable(sample sample.cxx)

include_directories(../mypascal_lib)
target_link_libraries(sample PUBLIC
  mypascal_lib
)