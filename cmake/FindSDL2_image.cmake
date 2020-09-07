INCLUDE(FindPackageHandleStandardArgs)

IF (${EMSCRIPTEN})
  SET(SDL2_image_FOUND 1)

  add_link_options(-sUSE_SDL_IMAGE=2)
  add_link_options(-sSDL2_IMAGE_FORMATS=[\"bmp\",\"png\",\"xpm\"])

  FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_image SDL2_image_FOUND)
ELSE()
  FIND_PATH(SDL2_image_INCLUDE_DIR SDL_image.h PATH_SUFFIXES SDL2)
  FIND_LIBRARY(SDL2_image_LIBRARIES NAMES SDL2_image )

  # Set library version
  SET(SDL2_image_VERSION 2.0.0)
  SET(SDL2_image_VERSION_MAJOR 2)
  SET(SDL2_image_VERSION_MINOR 0)
  SET(SDL2_image_VERSION_PATCH 0)

  # Give output, should this be wished (this handles also QUIET and REQUIRED
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_image DEFAULT_MSG SDL2_image_LIBRARIES SDL2_image_INCLUDE_DIR)
ENDIF()


