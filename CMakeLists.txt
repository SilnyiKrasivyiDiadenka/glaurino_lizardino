cmake_minimum_required(VERSION 3.16)

project(glaurino_lizardino LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
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
  src/lock.h
  src/main.cpp
  src/material.h
  src/material.cpp
  src/mersenne.h
  src/mersenne.cpp
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
  src/value.cpp)

find_package(Threads REQUIRED)
target_link_libraries(glaurino_lizardino PRIVATE Threads::Threads)

include(GNUInstallDirs)
install(
  TARGETS glaurino_lizardino
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
