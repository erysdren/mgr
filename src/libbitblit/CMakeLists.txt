PROJECT(bitblit C)

SET(MGR_BITBLIT_BACKEND "stub-backend" CACHE STRING "libbitblit backend renderer")
SET_PROPERTY(CACHE MGR_BITBLIT_BACKEND PROPERTY STRINGS stub-backend sdl-backend x11-backend)
MESSAGE(STATUS "bitblit-backend=${MGR_BITBLIT_BACKEND}")

SET(bitblit_SOURCES
    bitmap/bit_alloc.c
    bitmap/bit_create.c
    bitmap/bit_open.c
    bitmap/bitmaphead.c
    movie/timestamp.c  # This is used by do_event and main in mgr-server.
    seqbitmap/bit_load.c
    seqbitmap/bit_save.c
    seqbitmap/bitmapread.c
    seqbitmap/bitmapwrite.c
)

SET(bitblit_HEADERS
)

IF(MGR_ENABLE_MOVIE)
  LIST(APPEND bitblit_SOURCES
       movie/share.c)
ENDIF()

IF(MGR_BITBLIT_BACKEND MATCHES "stub-backend")
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/stub-backend)
  LIST(APPEND bitblit_SOURCES
       stub-backend/bit_blit.c
       stub-backend/bit_destroy.c
       stub-backend/bit_initscreen.c
       stub-backend/bit_line.c
       stub-backend/bit_on.c
       stub-backend/bit_point.c
       stub-backend/bit_size.c
       stub-backend/mem_rop.c
       stub-backend/palette.c
       stub-backend/screen.c)
  LIST(APPEND bitblit_HEADERS
       stub-backend/screen.h)
ENDIF()

IF(MGR_BITBLIT_BACKEND MATCHES "sdl-backend")
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/sdl-backend)
  FIND_PACKAGE(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
  FIND_PACKAGE(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
  LIST(APPEND bitblit_SOURCES
       sdl-backend/bit_blit.c
       sdl-backend/bit_destroy.c
       sdl-backend/bit_initscreen.c
       sdl-backend/bit_line.c
       sdl-backend/bit_on.c
       sdl-backend/bit_point.c
       sdl-backend/bit_size.c
       sdl-backend/mem_rop.c
       sdl-backend/palette.c
       sdl-backend/screen.c)
  LIST(APPEND bitblit_HEADERS
       sdl-backend/screen.h)
ENDIF()

IF(MGR_BITBLIT_BACKEND MATCHES "x11-backend")
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/x11-backend)
  FIND_PACKAGE(X11 REQUIRED)
  LIST(APPEND bitblit_SOURCES
       x11-backend/blit.c
       x11-backend/line.c
       x11-backend/pixel.c
       x11-backend/bitscreen.c
       x11-backend/color.c
       x11-backend/bitmisc.c
       x11-backend/bit_destroy.c
       x11-backend/bit_bytescr.c)
  LIST(APPEND bitblit_HEADERS
       x11-backend/screen.h)
ENDIF()

ADD_LIBRARY(bitblit
            STATIC
            ${bitblit_SOURCES}
            ${bitblit_HEADERS})
IF(NOT CMAKE_SYSTEM_NAME MATCHES "Emscripten")
  SET_TARGET_PROPERTIES(bitblit PROPERTIES VERSION ${MGR_VERSION})
ENDIF()

IF(MGR_BITBLIT_BACKEND MATCHES "sdl-backend")
  TARGET_LINK_LIBRARIES(bitblit PRIVATE SDL2::SDL2)
ENDIF()

IF(MGR_BITBLIT_BACKEND MATCHES "x11-backend")
  TARGET_LINK_LIBRARIES(bitblit PRIVATE ${X11_LIBRARIES})
  TARGET_INCLUDE_DIRECTORIES(bitblit PRIVATE ${X11_INCLUDE_DIRS})
ENDIF()

INSTALL(TARGETS bitblit DESTINATION lib)
