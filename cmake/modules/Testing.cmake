ENABLE_TESTING()
INCLUDE( CTest )

IF ( CMAKE_COMPILER_IS_GNUCC )
	SET( CMAKE_C_FLAGS_PROFILING "-g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wwrite-strings -fprofile-arcs -ftest-coverage" CACHE STRING "Profiling Compiler Flags" ) 
	# SET( CMAKE_C_FLAGS_PROFILING "-g -O0 -Wall -W -Wextra -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wwrite-strings -pedantic -fprofile-arcs -ftest-coverage" CACHE STRING "Profiling Compiler Flags" )
	SET( CMAKE_CXX_FLAGS_PROFILING "-g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wwrite-strings -fprofile-arcs -ftest-coverage" CACHE STRING "Profiling Compiler Flags" ) 
	SET( CMAKE_SHARED_LINKER_FLAGS_PROFILING " -fprofile-arcs -ftest-coverage" CACHE STRING "Profiling Linker Flags" )
	SET( CMAKE_MODULE_LINKER_FLAGS_PROFILING " -fprofile-arcs -ftest-coverage" CACHE STRING "Profiling Linker Flags" )
	SET( CMAKE_EXEC_LINKER_FLAGS_PROFILING " -fprofile-arcs -ftest-coverage" CACHE STRING "Profiling Linker Flags" )
ENDIF ( CMAKE_COMPILER_IS_GNUCC )

MACRO( BUILD_CHECK_TEST _testName _testSource ) 

	if(COMMAND cmake_policy)
		cmake_policy(SET CMP0003 NEW)
		## The macro ADD_CHECK_TEST creates false warning.
		cmake_policy(SET CMP0002 OLD)
	endif(COMMAND cmake_policy)
	ADD_EXECUTABLE( ${_testName} ${_testSource} )
	TARGET_LINK_LIBRARIES( ${_testName} ${ARGN} )

ENDMACRO( BUILD_CHECK_TEST )

MACRO( ADD_CHECK_TEST _testName _testSource ) 

	if(COMMAND cmake_policy)
		cmake_policy(SET CMP0003 NEW)
		## The macro ADD_CHECK_TEST creates false warning.
		cmake_policy(SET CMP0002 OLD)
	endif(COMMAND cmake_policy)
	BUILD_CHECK_TEST( ${_testName} ${_testSource} ${ARGN} )
	#	ADD_EXECUTABLE( ${_testName} ${_testSource} )
	#	TARGET_LINK_LIBRARIES( ${_testName} ${ARGN} )
	ADD_TEST( ${_testName} ${CMAKE_CURRENT_BINARY_DIR}/${_testName} )

ENDMACRO( ADD_CHECK_TEST )

MACRO( OSYNC_TESTCASE _testSource _testDest ) 

	if(COMMAND cmake_policy)
		cmake_policy(SET CMP0003 NEW)
		## The macro ADD_CHECK_TEST creates false warning.
		cmake_policy(SET CMP0002 OLD)
	endif(COMMAND cmake_policy)

	# 1st Argument is the testcase name
	# 2nd Argument is the executable name
        # 3rd Argument the testcase name, again, as argument for the executable
	ADD_TEST( ${_testDest} ${_testSource} ${_testDest} )

ENDMACRO( OSYNC_TESTCASE )


MACRO( OSYNC_TESTCASE_DISABLED _testSource _testDest _ticket ) 

	OSYNC_TESTCASE( ${_testSource} ${_testDest} ) 
	SET( CTEST_CUSTOM_TESTS_IGNORE ${CTEST_CUSTOM_TESTS_IGNORE} "${_testDest}" )

	MESSAGE( STATUS "Testcase \"${_testDest}\" disabled/ignored! ${TICKETURL}${_ticket}" )

ENDMACRO( OSYNC_TESTCASE_DISABLED )

