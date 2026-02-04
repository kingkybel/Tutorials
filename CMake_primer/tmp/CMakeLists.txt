cmake_minimum_required(VERSION 3.8)
project(MyProject LANGUAGES CXX)
add_executable(my_exe mini.cc)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=* -p ${CMAKE_SOURCE_DIR}/build")
execute_process(COMMAND bash -c "${CMAKE_CXX_CLANG_TIDY}"
                OUTPUT_VARIABLE CLANG_TIDY_SUCCESS)

function(dos2unix filename)
        execute_process(COMMAND bash -c "dos2unix ${filename}"
                        OUTPUT_VARIABLE DOS2UNIX_SUCCESS)
endfunction()

dos2unix(../file1.cc)
dos2unix(../file2.cc)


foreach(CPP_FILE_TARGET exe1 exe2 exe3)
        add_executable(${CPP_FILE_TARGET} ${CPP_FILE_TARGET}.cc)
        target_link_libraries(${CPP_FILE_TARGET} STATIC ${CPP_FILE_TARGET})
endforeach()

add_executable(exe1 exe1.cc)
target_link_libraries(exe1 STATIC exe1)

add_executable(exe2 exe2.cc)
target_link_libraries(exe2 STATIC exe2)

add_executable(exe3 exe3.cc)
target_link_libraries(exe3 STATIC exe3)

