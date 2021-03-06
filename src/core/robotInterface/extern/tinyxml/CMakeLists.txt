# Copyright (C) 2012  iCub Facility, Istituto Italiano di Tecnologia
# Author: Daniele E. Domenichelli <daniele.domenichelli@iit.it>
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT


# TinyXML
project(ICUB_tinyxml)

set(tinyxml_SRCS
    tinyxml/tinystr.cpp
    tinyxml/tinyxml.cpp
    tinyxml/tinyxmlerror.cpp
    tinyxml/tinyxmlparser.cpp
)

set(tinyxml_HDRS
    tinyxml/tinystr.h
    tinyxml/tinyxml.h
)

add_definitions("-DTIXML_USE_STL")

add_library(ICUB_tinyxml STATIC ${tinyxml_SRCS})

if(UNIX)
    set_target_properties(ICUB_tinyxml PROPERTIES COMPILE_FLAGS -fPIC)
endif(UNIX)

set(TinyXML_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/tinyxml" CACHE PATH "TinyXML include directory" FORCE)
set(TinyXML_LIBRARY_DIRS "${CMAKE_BINARY_DIR}/lib" CACHE PATH "TinyXML library directory" FORCE)
set(TinyXML_LIBRARIES "ICUB_tinyxml" CACHE STRING "TinyXML libraries" FORCE)
mark_as_advanced(TinyXML_INCLUDE_DIRS TinyXML_LIBRARY_DIRS TinyXML_LIBRARIES)
