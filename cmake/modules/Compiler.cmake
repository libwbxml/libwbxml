# Copyright (c) 2007 Daniel Gollub <gollub@b1-systems.de>

IF ( CMAKE_COMPILER_IS_GNUCC )
  SET( SYMBOLS_VISIBILITY "-fvisibility=hidden" )
  SET( CMAKE_C_FLAGS_HACKING "-O2 -fmessage-length=0 -Wall -Werror -D_FORTIFY_SOURCE=2 -fstack-protector -g" CACHE STRING "Developer C Compiler Flags" )
  SET( CMAKE_CXX_FLAGS_HACKING "-O2 -fmessage-length=0 -Wall -Werror -D_FORTIFY_SOURCE=2 -fstack-protector -g" CACHE STRING "Developer C++ Compiler Flags" )
ENDIF ( CMAKE_COMPILER_IS_GNUCC )

IF (CMAKE_SYSTEM MATCHES "SunOS-5*.")
  SET( SYMBOLS_VISIBILITY "-xldscope=hidden" )
ENDIF (CMAKE_SYSTEM MATCHES "SunOS-5*.")

IF ( SYMBOLS_VISIBILITY )
  INCLUDE( CheckCCompilerFlag )
  check_c_compiler_flag( ${SYMBOLS_VISIBILITY} COMPILER_SUPPORTS_VISIBILITY )
ENDIF ( SYMBOLS_VISIBILITY )

IF (NOT COMPILER_SUPPORTS_VISIBILITY)
  SET( SYMBOLS_VISIBILITY "" )
ENDIF (NOT COMPILER_SUPPORTS_VISIBILITY)

IF ( MSVC )
  # Some compiler options for MSVC to not print non-sense warnings.
  ADD_DEFINITIONS ( -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE )
ENDIF ( MSVC )
