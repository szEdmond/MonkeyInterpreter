# If you create new headers/cpp files, add them to these list!
set(HEADER_FILES
	catch.hpp
)

set(SOURCE_FILES
	catch.hpp
	tests.cpp
)

add_executable(Unit_Tests ${SOURCE_FILES})
target_link_libraries(Unit_Tests InterpreterLib)