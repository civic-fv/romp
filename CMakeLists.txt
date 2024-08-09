cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

project(romp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This seems to be some magic to get libraries to install correctly.
include(GNUInstallDirs)

include(CheckCXXCompilerFlag)
include(CheckLinkerFlag)


find_package(Python3 REQUIRED COMPONENTS Interpreter)


# enable even more warnings if the compiler supports them
macro(try_add_cxx_warn_flag flag)
    CHECK_CXX_COMPILER_FLAG("-W${flag}" HAS_WARNING_${flag})
    if(HAS_WARNING_${flag})
        string(APPEND WARN_CXX_FLAGS " -W${flag}")
    else()
        message(WARNING "C++ compiler ${CMAKE_CXX_COMPILER} is missing the ${flag} warning")
    endif()
endmacro()

foreach(f IN ITEMS cast-qual cast-align logical-op write-strings format=2
                   strict-aliasing=1 pointer-arith missing-declarations
                   unknown-pragmas shadow undef)
    try_add_cxx_warn_flag(${f})
endforeach()
string(APPEND WARN_CXX_FLAGS " -W -Wall -Wextra")
if(NOT DEFINED ROMP_DIST)
    string(APPEND WARN_CXX_FLAGS " -Werror -Wno-error=unknown-pragmas")
endif()

CHECK_CXX_COMPILER_FLAG(-fno-sanitize=all HAS_SANITIZER)
if(HAS_SANITIZER)
    CHECK_CXX_COMPILER_FLAG(-fno-sanitize-trap=all HAS_SANITIZER_TRAP)
    CHECK_CXX_COMPILER_FLAG(-fsanitize-ignorelist=/dev/null HAS_SANITIZER_IGNORE_LIST)

    block(SCOPE_FOR VARIABLES PROPAGATE SANITIZER_CXX_FLAGS)
        # clang's CFI sanitizer requires link-time optimization and non-overridable symbols
        set(SANITIZER_cfi_ADD_CXX_FLAGS "-flto;-fvisibility=protected")

        macro(check_sanitizer sanitizer)
            # NB: linker flag because some sanitizers require runtime support
            CHECK_LINKER_FLAG(CXX "${SANITIZER_${sanitizer}_ADD_CXX_FLAGS};-fsanitize=${sanitizer}" HAS_SANITIZER_${sanitizer})
            if(NOT HAS_SANITIZER_${sanitizer})
                message(SEND_ERROR "Sanitizer ${sanitizer} is not supported by C++ compiler ${CMAKE_CXX_COMPILER}")
            endif()
        endmacro()

        foreach(san IN LISTS ROMP_USE_SANITIZERS)
            check_sanitizer(${san})
            list(APPEND SANITIZER_CXX_FLAGS_BASE "${SANITIZER_${san}_ADD_CXX_FLAGS}")
        endforeach()

        if(NOT DEFINED ROMP_USE_SANITIZERS OR ROMP_USE_SANITIZERS STREQUAL "")
            set(SANITIZER_CXX_FLAGS "")
        else()
            list(JOIN ROMP_USE_SANITIZERS "," sanitize_arg)
            CHECK_LINKER_FLAG(CXX "${SANITIZER_CXX_FLAGS_BASE};-fsanitize=${sanitize_arg}" SANITIZERS_COMPATIBLE_${sanitize_arg})
            if(NOT SANITIZERS_COMPATIBLE_${sanitize_arg})
                message(SEND_ERROR "C++ compiler ${CMAKE_CXX_COMPILER} does not support simultaneously enabling ${ROMP_USE_SANITIZERS} sanitizers")
            endif()

            list(JOIN SANITIZER_CXX_FLAGS_BASE " " SANITIZER_CXX_FLAGS)
            string(APPEND SANITIZER_CXX_FLAGS " -fsanitize=${sanitize_arg} -fno-sanitize-recover=all")
            if(HAS_SANITIZER_TRAP)
                string(APPEND SANITIZER_CXX_FLAGS " -fno-sanitize-trap=all")
            endif()
            if(HAS_SANITIZER_IGNORE_LIST)
                string(APPEND SANITIZER_CXX_FLAGS " -fsanitize-ignorelist=\"${CMAKE_SOURCE_DIR}/sanitizer-known-issues.txt\"")
            endif()
        endif()
    endblock()
endif()

string(APPEND CMAKE_CXX_FLAGS " ${WARN_CXX_FLAGS} ${SANITIZER_CXX_FLAGS}")

# Enable --as-needed, present on GNU ld on Linux, to minimise dependencies.
CHECK_LINKER_FLAG(CXX "-Wl,--as-needed" HAS_LINK_AS_NEEDED)
if(HAS_LINK_AS_NEEDED)
    string(APPEND CMAKE_EXE_LINKER_FLAGS    " -Wl,--as-needed")
    string(APPEND CMAKE_SHARED_LINKER_FLAGS " -Wl,--as-needed")
endif()

enable_testing()

add_subdirectory(libmurphi)
# add_subdirectory(murphi2c)
add_subdirectory(romp)
add_subdirectory(tests)

# add_custom_target(check
#   COMMAND env PATH=${CMAKE_CURRENT_BINARY_DIR}/romp:${CMAKE_CURRENT_BINARY_DIR}/murphi2c:${CMAKE_CURRENT_BINARY_DIR}/murphi2murphi:${CMAKE_CURRENT_BINARY_DIR}/murphi2uclid:${CMAKE_CURRENT_BINARY_DIR}/murphi2xml:${CMAKE_CURRENT_BINARY_DIR}/tests/murphi-comment-ls:$ENV{PATH}
#     ${CMAKE_CURRENT_SOURCE_DIR}/tests/run-tests.py --verbose)
# add_dependencies(check murphi2cpp murphi2murphi murphi2uclid murphi2xml romp)
# if(NOT CMAKE_CROSSCOMPILING)
#   add_dependencies(check murphi-comment-ls)
# endif()

add_custom_target(format
  COMMAND git ls-files -z '**/*.cc' '**/*.h' '**/*.cpp' '**/*.hpp' |
    xargs -0 -- clang-format -i --style=file
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# custom clean
# add_custom_target(clean-tests-global
#   OUTPUT none.txt
#   COMMAND rm *.test ; rm *.test.cpp ; rm -R traces ; rm -R ../traces
#   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests
# )
