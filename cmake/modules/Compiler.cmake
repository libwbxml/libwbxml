# Copyright (c) 2007 Daniel Gollub <dgollub@suse.de>

IF ( WIN32 )
	SET( SYMBOLS_VISIBILITY "" )
ENDIF ( WIN32 )

IF ( CMAKE_COMPILER_IS_GNUCC ) 
	SET( SYMBOLS_VISIBILITY "-fvisibility=hidden" )
	SET( CMAKE_C_FLAGS_HACKING "-O2 -fmessage-length=0 -Wall -D_FORTIFY_SOURCE=2 -fstack-protector -g" CACHE STRING "Developer C Compiler Flags" )
	SET( CMAKE_CXX_FLAGS_HACKING "-O2 -fmessage-length=0 -Wall -D_FORTIFY_SOURCE=2 -fstack-protector -g" CACHE STRING "Developer C++ Compiler Flags" )
ENDIF ( CMAKE_COMPILER_IS_GNUCC ) 

IF (CMAKE_SYSTEM MATCHES "SunOS-5*.")	
	SET( SYMBOLS_VISIBILITY "-xldscope=hidden" )
ENDIF (CMAKE_SYSTEM MATCHES "SunOS-5*.")	
