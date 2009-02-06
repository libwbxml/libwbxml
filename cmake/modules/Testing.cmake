ENABLE_TESTING()
INCLUDE( CTest )

SET( CMAKE_C_FLAGS_PROFILING "-g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wwrite-strings -fprofile-arcs -ftest-coverage" CACHE STRING "Profiling Compiler Flags" ) 
# SET( CMAKE_C_FLAGS_PROFILING "-g -O0 -Wall -W -Wextra -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wwrite-strings -pedantic -fprofile-arcs -ftest-coverage" CACHE STRING "Profiling Compiler Flags" )
SET( CMAKE_CXX_FLAGS_PROFILING "-g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wwrite-strings -fprofile-arcs -ftest-coverage" CACHE STRING "Profiling Compiler Flags" ) 
SET( CMAKE_SHARED_LINKER_FLAGS_PROFILING " -fprofile-arcs -ftest-coverage" CACHE STRING "Profiling Linker Flags" )
SET( CMAKE_MODULE_LINKER_FLAGS_PROFILING " -fprofile-arcs -ftest-coverage" CACHE STRING "Profiling Linker Flags" )
SET( CMAKE_EXEC_LINKER_FLAGS_PROFILING " -fprofile-arcs -ftest-coverage" CACHE STRING "Profiling Linker Flags" )

MACRO( ADD_CHECK_TEST _testName _testSource ) 

	if(COMMAND cmake_policy)
		cmake_policy(SET CMP0003 NEW)
		## The macro ADD_CHECK_TEST creates false warning.
		cmake_policy(SET CMP0002 OLD)
	endif(COMMAND cmake_policy)
	ADD_EXECUTABLE( ${_testName} ${_testSource} )
	TARGET_LINK_LIBRARIES( ${_testName} ${ARGN} )
	ADD_TEST( ${_testName} ${CMAKE_CURRENT_BINARY_DIR}/${_testName} )

ENDMACRO( ADD_CHECK_TEST )
