cmake_minimum_required(VERSION 3.16)

project(glaurino_lizardino LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported)
if(ipo_supported)
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
endif()

add_executable(
  glaurino_lizardino
  src/main.cpp
  src/benchmark.h
  src/benchmark.cpp
  src/bitbase.h
  src/bitbase.cpp
  src/bitboard.h
  src/bitboard.cpp
  src/book.h
  src/book.cpp
  src/color.h
  src/color.cpp
  src/depth.h
  src/direction.h
  src/direction.cpp
  src/endgame.h
  src/endgame.cpp
  src/evaluate.h
  src/evaluate.cpp
  src/history.h
  src/history.cpp
  src/main.cpp
  src/material.h
  src/material.cpp
  src/misc.h
  src/misc.cpp
  src/move.h
  src/move.cpp
  src/movegen.h
  src/movegen.cpp
  src/movepick.h
  src/movepick.cpp
  src/pawns.h
  src/pawns.cpp
  src/phase.h
  src/piece.h
  src/piece.cpp
  src/position.h
  src/position.cpp
  src/psqtab.h
  src/san.h
  src/san.cpp
  src/scale.h
  src/search.h
  src/search.cpp
  src/square.h
  src/square.cpp
  src/thread.h
  src/tt.h
  src/tt.cpp
  src/types.h
  src/uci.h
  src/uci.cpp
  src/ucioption.h
  src/ucioption.cpp
  src/value.h
  src/value.cpp
  src/glaurino_lizardino/genrand/igenrand.h
  src/glaurino_lizardino/genrand/genrandfactory.h
  src/glaurino_lizardino/genrand/genrandfactory.cpp
  src/glaurino_lizardino/genrand/impl/genrandmersenne.hpp
  src/glaurino_lizardino/genrand/impl/genrandstd.hpp
  src/glaurino_lizardino/popcount/ipopcount.h
  src/glaurino_lizardino/popcount/popcountfactory.h
  src/glaurino_lizardino/popcount/popcountfactory.cpp
  src/glaurino_lizardino/popcount/impl/popcountloop.hpp
  src/glaurino_lizardino/popcount/impl/popcountstd.hpp
  src/glaurino_lizardino/popcount/impl/popcountswar32.hpp
  src/glaurino_lizardino/popcount/impl/popcountswar64.hpp)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  if(MINGW OR WIN32)
    target_link_options(glaurino_lizardino PRIVATE $<$<CONFIG:Release>:-static>)
  elseif(UNIX AND NOT APPLE)
    target_link_options(
      glaurino_lizardino PRIVATE $<$<CONFIG:Release>:-static-libgcc>
      $<$<CONFIG:Release>:-static-libstdc++>)
  endif()
endif()

include(GNUInstallDirs)
install(
  TARGETS glaurino_lizardino
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
