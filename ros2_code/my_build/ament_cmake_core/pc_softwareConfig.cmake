# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_pc_software_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED pc_software_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(pc_software_FOUND FALSE)
  elseif(NOT pc_software_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(pc_software_FOUND FALSE)
  endif()
  return()
endif()
set(_pc_software_CONFIG_INCLUDED TRUE)

# output package information
if(NOT pc_software_FIND_QUIETLY)
  message(STATUS "Found pc_software: 0.0.0 (${pc_software_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'pc_software' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${pc_software_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(pc_software_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${pc_software_DIR}/${_extra}")
endforeach()
