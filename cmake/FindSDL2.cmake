INCLUDE(FindPackageHandleStandardArgs)

IF (${EMSCRIPTEN})
  SET(SDL2_FOUND 1)

  add_compile_options(-sUSE_SDL=2)
  add_link_options(-sUSE_SDL=2)

  FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2 SDL2_FOUND)
ELSE()
  FIND_PATH(SDL2_INCLUDE_DIR SDL.h PATH_SUFFIXES SDL2)
  FIND_LIBRARY(SDL2_LIBRARIES NAMES SDL2 )

  # Set library version
  SET(SDL2_VERSION 2.0.0)
  SET(SDL2_VERSION_MAJOR 2)
  SET(SDL2_VERSION_MINOR 0)
  SET(SDL2_VERSION_PATCH 0)

  FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2 DEFAULT_MSG SDL2_LIBRARIES SDL2_INCLUDE_DIR)  
ENDIF()
