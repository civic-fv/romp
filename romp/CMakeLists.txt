# Define resources.
macro(add_xxd output input)
    add_custom_command(
        OUTPUT ${output}
        COMMAND python3 "${CMAKE_SOURCE_DIR}/misc/xxd.py" "${input}" "${CMAKE_CURRENT_BINARY_DIR}/${output}"
        MAIN_DEPENDENCY "${input}"
        DEPENDS "${CMAKE_SOURCE_DIR}/misc/xxd.py"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
    list(APPEND ROMP_XXD_SOURCES "${output}")
endmacro()
add_xxd(resources_manpage.cpp doc/romp.1)                                   # the man/help page
add_xxd(resources_romp-rw_include.cpp resources/romp-rw/include.hpp)        # the includes for the genrated model checker
add_xxd(resources_romp-rw_decl.cpp resources/romp-rw/decl.hpp)              # the genral declrations for the genrated model checker
add_xxd(resources_romp-rw_writers.cpp resources/romp-rw/writers.hpp)        # the writers used to write to console in the genrated model checker
add_xxd(resources_romp-rw_error.cpp resources/romp-rw/error.hpp)            # the error handling classes and functions
add_xxd(resources_romp-rw_types.cpp resources/romp-rw/types.hpp)            # the type templates for the genrated model checker
add_xxd(resources_romp-rw_hash.cpp resources/romp-rw/hash.hpp)              # the hahser templates for the genrated model checker
add_xxd(resources_romp-rw_options.cpp resources/romp-rw/options.hpp)        # file with CLI config options
add_xxd(resources_romp-rw_walker.cpp resources/romp-rw/walker.hpp)          # our main definition and code file for the random walker and associated algorithms
add_xxd(resources_romp-rw_bfs.cpp resources/romp-rw/bfs.hpp)                # our main definition and code file for the preliminary BFS
add_xxd(resources_romp-rw_impls.cpp resources/romp-rw/impls.hpp)            # just some random implementations of functions that need to have everythign else declared and impl'ed first
add_xxd(resources_romp-rw_main.cpp resources/romp-rw/main.hpp)              # file with our main function
#add_xxd(resources_lib_nlohmann_json.cpp resources/lib/nlohmann_json.hpp)   # convert jsonlib too

# NB (Chloe 2024-08-04): Best to avoid network resources in build scripts
# add_custom_command(# retrieve verified version of the json lib we use nlohmann/json (https://github.com/nlohmann/json)
#   OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/resources/lib/nlohmann_json.hpp
#   COMMAND curl -L https://github.com/nlohmann/json/releases/download/v3.10.5/json.hpp > ${CMAKE_CURRENT_SOURCE_DIR}/resources/lib/nlohmann_json.hpp
#   # MAIN_DEPENDENCY resources/lib/nlohmann_json.hpp
#   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

string(APPEND CMAKE_CXX_FLAGS_DEBUG " -DDEBUG -D_ROMP_DEV_DEBUG_INCLUDE_DIR='\"${CMAKE_CURRENT_SOURCE_DIR}/resources\"'")

add_executable(romp
  ../common/escape.cc
  ../common/help.cc
  src/nested_escape.cpp
  src/CodeGenerator.cpp
  src/check.cc
  src/ModelGenerator.cpp
  src/generate_state_stream.cpp
  src/generate_metadata.cpp
  src/generate_callers.cpp
  src/ScalarEnumGenerator.cpp
  # src/compares_complex_values.cc
  # src/SigPerm.cpp
  src/main.cc
  # src/options.cc
  src/romp_def.cpp
  # src/ModelSplitter.cpp
  # src/CTypeGenerator.cpp
  src/SigPerm.cpp
  src/NestedError.cpp
  src/StateSpaceCalc.cpp
  src/generate.cpp
  )

target_sources(romp PRIVATE "${ROMP_XXD_SOURCES}")

target_include_directories(romp
  PRIVATE
  src
  ${CMAKE_CURRENT_BINARY_DIR}/../libmurphi)

target_link_libraries(romp
  libmurphi)

# Compress manpage
add_custom_target(man-romp
  ALL
  DEPENDS romp.1.gz)
add_custom_command(
  OUTPUT romp.1.gz
  COMMAND gzip -9 --no-name --to-stdout doc/romp.1 >${CMAKE_CURRENT_BINARY_DIR}/romp.1.gz
  MAIN_DEPENDENCY doc/romp.1
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS romp
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/romp.1.gz
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
