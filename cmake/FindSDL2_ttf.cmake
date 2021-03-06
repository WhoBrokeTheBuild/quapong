# Locate SDL_ttf library
#
# This module defines:
#
# ::
#
#   SDL2_TTF_FOUND, if false, do not try to link against
#   SDL2_TTF_LIBRARY, the name of the library to link against
#   SDL2_TTF_INCLUDE_DIR, where to find the headers
#
# $SDLDIR is an environment variable that would correspond to the
# ./configure --prefix=$SDLDIR used in building SDL.
#
# Created by Eric Wing.  This was influenced by the FindSDL.cmake
# module, but with modifications to recognize OS X frameworks and
# additional Unix paths (FreeBSD, etc).

#=============================================================================
# Copyright 2005-2009 Kitware, Inc.
# Copyright 2012 Benjamin Eikel
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

SET(SDL2_TTF_SEARCH_PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw # Fink
	/opt/local # DarwinPorts
	/opt/csw # Blastwave
	/opt
	$ENV{VS140COMNTOOLS}../../VC # VS 2015
	$ENV{VS120COMNTOOLS}../../VC # VS 2013
	$ENV{VS110COMNTOOLS}../../VC # VS 2012
	$ENV{VS100COMNTOOLS}../../VC # VS 2010
	${SDL2_PATH}
)

FIND_PATH(SDL2_TTF_INCLUDE_DIR SDL_ttf.h
	HINTS
	ENV SDL2TTFDIR
	ENV SDL2DIR
	PATH_SUFFIXES include/SDL2 include
	PATHS ${SDL2_TTF_SEARCH_PATHS}
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8) 
	set(PATH_SUFFIXES lib64 lib/x64 lib/amd64 lib)
else() 
	set(PATH_SUFFIXES lib/x86 lib)
endif() 

FIND_LIBRARY(SDL2_TTF_LIBRARY
	NAMES SDL2_ttf
	HINTS
	ENV SDL2TTFDIR
	ENV SDL2DIR
	PATH_SUFFIXES ${PATH_SUFFIXES}
	PATHS ${SDL2_TTF_SEARCH_PATHS}
)

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_ttf REQUIRED_VARS SDL2_TTF_LIBRARY SDL2_TTF_INCLUDE_DIR)
