# Define resources.
add_custom_command(
  OUTPUT resources_manpage.cpp
  COMMAND ../misc/xxd.py doc/romp.1 ${CMAKE_CURRENT_BINARY_DIR}/resources_manpage.cpp
  MAIN_DEPENDENCY doc/romp.1
  DEPENDS ../misc/xxd.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(
  OUTPUT resources_c_prefix.cpp
  COMMAND ../misc/xxd.py resources/c_prefix.cpp ${CMAKE_CURRENT_BINARY_DIR}/resources_c_prefix.cpp
  MAIN_DEPENDENCY resources/c_prefix.cpp
  DEPENDS ../misc/xxd.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
# add_custom_command(
#   OUTPUT resources_h_prefix.cpp
#   COMMAND ../misc/xxd.py resources/h_prefix.h ${CMAKE_CURRENT_BINARY_DIR}/resources_h_prefix.cpp
#   MAIN_DEPENDENCY resources/h_prefix.h
#   DEPENDS ../misc/xxd.py
#   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(# our main definition file for rw
  OUTPUT resources_romp-rw.cpp
  COMMAND ../misc/xxd.py resources/romp-rw.hpp ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw.cpp
  MAIN_DEPENDENCY resources/romp-rw.hpp
  DEPENDS ../misc/xxd.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(# file with our main function 
  OUTPUT resources_romp-rw-main.cpp
  COMMAND ../misc/xxd.py resources/romp-rw-main.hpp ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw-main.cpp
  MAIN_DEPENDENCY resources/romp-rw-main.hpp
  DEPENDS ../misc/xxd.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(# file with CLI config options
  OUTPUT resources_romp-rw-options.cpp
  COMMAND ../misc/xxd.py resources/romp-rw-options.hpp ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw-options.cpp
  MAIN_DEPENDENCY resources/romp-rw-options.hpp
  DEPENDS ../misc/xxd.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
# add_custom_command(# retrieve verified version of the json lib we use nlohmann/json (https://github.com/nlohmann/json)
#   OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/resources/lib/nlohmann_json.hpp
#   COMMAND curl -L https://github.com/nlohmann/json/releases/download/v3.10.5/json.hpp > ${CMAKE_CURRENT_SOURCE_DIR}/resources/lib/nlohmann_json.hpp
#   # MAIN_DEPENDENCY resources/lib/nlohmann_json.hpp
#   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
# add_custom_command(# convert jsonlib to 
#   OUTPUT resources_lib_nlohmann_json.cpp
#   COMMAND ../misc/xxd.py resources/lib/nlohmann_json.hpp ${CMAKE_CURRENT_BINARY_DIR}/resources_lib_nlohmann_json.cpp
#   MAIN_DEPENDENCY resources/lib/nlohmann_json.hpp
#   DEPENDS ../misc/xxd.py
#   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(ROMP_CMAKE_CXX_FLAGS "-Wmissing-declarations -Wunknown-pragmas")
set(CMAKE_CXX_FLAGS "${OLD_CMAKE_CXX_FLAGS} -std=c++17 ${RUMUR_CMAKE_CXX_FALGS} ${ROMP_CMAKE_CXX_FLAGS}")
set(ROMP_CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -D_ROMP_DEV_DEBUG_INCLUDE_DIR='\"${CMAKE_CURRENT_SOURCE_DIR}/resources\"'")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${ROMP_CMAKE_CXX_FLAGS_DEBUG}")

add_executable(romp
  ${CMAKE_CURRENT_BINARY_DIR}/resources_c_prefix.cpp
  # ${CMAKE_CURRENT_BINARY_DIR}/resources_h_prefix.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/resources_manpage.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw-main.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw-options.cpp
  # ${CMAKE_CURRENT_BINARY_DIR}/resources_lib_nlohmann_json.cpp
  ../common/escape.cc
  ../common/help.cc
  src/check.cc
  src/CLikeGenerator.cpp
  src/CodeGenerator.cpp
  src/compares_complex_values.cc
  src/SigPerm.cpp
  src/generate_c.cpp
  # src/generate_h.cc
  src/main.cc
  src/options.cc
  src/romp_def.cpp
  src/ModelSplitter.cpp
  src/CTypeGenerator.cpp
  src/NestedError.cpp
  src/SigPerm.cpp
  src/nested_escape.cpp
  src/StateSpaceCalc.cpp
  )

target_include_directories(romp
  PRIVATE
  src
  ${CMAKE_CURRENT_BINARY_DIR}/../librumur)

target_link_libraries(romp
  librumur)

# Compress manpage
add_custom_target(man-romp
  ALL
  DEPENDS romp.1.gz)
add_custom_command(
  OUTPUT romp.1.gz
  COMMAND gzip -9 --no-name --to-stdout doc/romp.1 >"${CMAKE_CURRENT_BINARY_DIR}/romp.1.gz"
  MAIN_DEPENDENCY doc/romp.1
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS romp
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/romp.1.gz
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
