# Define resources.
add_custom_command(# the man/help page 
  OUTPUT resources_manpage.cpp
  COMMAND ../misc/xxd.py doc/romp.1 ${CMAKE_CURRENT_BINARY_DIR}/resources_manpage.cpp
  MAIN_DEPENDENCY doc/romp.1
  DEPENDS ../misc/xxd.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(# the includes for the genrated model checker
  OUTPUT resources_romp-rw_include.cpp
  COMMAND ../misc/xxd.py resources/romp-rw/include.hpp ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw_include.cpp
  MAIN_DEPENDENCY resources/romp-rw/include.hpp
  DEPENDS ../misc/xxd.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(# the genral declrations for the genrated model checker
  OUTPUT resources_romp-rw_decl.cpp
  COMMAND ../misc/xxd.py resources/romp-rw/decl.hpp ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw_decl.cpp
  MAIN_DEPENDENCY resources/romp-rw/decl.hpp
  DEPENDS ../misc/xxd.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(# the writers used to write to console in the genrated model checker
  OUTPUT resources_romp-rw_writers.cpp
  COMMAND ../misc/xxd.py resources/romp-rw/writers.hpp ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw_writers.cpp
  MAIN_DEPENDENCY resources/romp-rw/writers.hpp
  DEPENDS ../misc/xxd.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(# the type templates for the genrated model checker
  OUTPUT resources_romp-rw_types.cpp
  COMMAND ../misc/xxd.py resources/romp-rw/types.hpp ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw_types.cpp
  MAIN_DEPENDENCY resources/romp-rw/types.hpp
  DEPENDS ../misc/xxd.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(# the error handling classes and functions
  OUTPUT resources_romp-rw_error.cpp
  COMMAND ../misc/xxd.py resources/romp-rw/error.hpp ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw_error.cpp
  MAIN_DEPENDENCY resources/romp-rw/error.hpp
  DEPENDS ../misc/xxd.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(# file with CLI config options
  OUTPUT resources_romp-rw_options.cpp
  COMMAND ../misc/xxd.py resources/romp-rw/options.hpp ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw_options.cpp
  MAIN_DEPENDENCY resources/romp-rw/options.hpp
  DEPENDS ../misc/xxd.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(# our main definition and code file for the random walker and associated algorithms
  OUTPUT resources_romp-rw_walker.cpp
  COMMAND ../misc/xxd.py resources/romp-rw/walker.hpp ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw_walker.cpp
  MAIN_DEPENDENCY resources/romp-rw/walker.hpp
  DEPENDS ../misc/xxd.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(# just some random implementations of functions that need to have everythign else declared and impl'ed first
  OUTPUT resources_romp-rw_impls.cpp
  COMMAND ../misc/xxd.py resources/romp-rw/impls.hpp ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw_impls.cpp
  MAIN_DEPENDENCY resources/romp-rw/impls.hpp
  DEPENDS ../misc/xxd.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(# file with our main function 
  OUTPUT resources_romp-rw_main.cpp
  COMMAND ../misc/xxd.py resources/romp-rw/main.hpp ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw_main.cpp
  MAIN_DEPENDENCY resources/romp-rw/main.hpp
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
set(CMAKE_CXX_FLAGS "${OLD_CMAKE_CXX_FLAGS} -std=c++17 ${ROMP_CMAKE_CXX_FALGS} ${ROMP_CMAKE_CXX_FLAGS}")
set(ROMP_CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -D_ROMP_DEV_DEBUG_INCLUDE_DIR='\"${CMAKE_CURRENT_SOURCE_DIR}/resources\"'")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${ROMP_CMAKE_CXX_FLAGS_DEBUG}")

add_executable(romp
  ${CMAKE_CURRENT_BINARY_DIR}/resources_manpage.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw_include.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw_decl.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw_writers.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw_types.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw_error.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw_options.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw_impls.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw_walker.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/resources_romp-rw_main.cpp
  ../common/escape.cc
  ../common/help.cc
  src/check.cc
  src/CodeGenerator.cpp
  src/ModelGenerator.cpp
  src/generate_state_stream.cpp
  src/generate_metadata.cpp
  src/generate_callers.cpp
  src/ScalarEnumGenerator.cpp
  # src/compares_complex_values.cc
  # src/SigPerm.cpp
  src/generate.cpp
  src/main.cc
  # src/options.cc
  src/romp_def.cpp
  # src/ModelSplitter.cpp
  # src/CTypeGenerator.cpp
  src/NestedError.cpp
  src/SigPerm.cpp
  src/nested_escape.cpp
  src/StateSpaceCalc.cpp
  )

target_include_directories(romp
  PRIVATE
  src
  ${CMAKE_CURRENT_BINARY_DIR}/../libromp)

target_link_libraries(romp
  libmurphi)

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
