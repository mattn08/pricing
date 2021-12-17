

  set(BINARY TestOptionPrice)
  file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

  set(SOURCES ${TEST_SOURCES})

  add_executable(${BINARY} ${TEST_SOURCES})
  add_test(NAME ${BINARY} COMMAND ${BINARY})

  message(STATUS "Project Name: ${CMAKE_PROJECT_NAME}")

  target_link_libraries(${BINARY} PRIVATE ${CMAKE_PROJECT_NAME}_lib gtest gtest_main)


