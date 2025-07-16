include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

function (get_all_test_files_from a_module_dir result)
file(GLOB_RECURSE ALL_CPP_FILES CONFIGURE_DEPENDS
    "${a_module_dir}/*.cpp"
    )

    set(TEST_SOURCES "")
    foreach(file ${ALL_CPP_FILES})
        get_filename_component(dir "${file}" DIRECTORY)
        if(dir MATCHES ".*/.*__tests__.*(/|$)")
            list(APPEND TEST_SOURCES "${file}")
        endif()
    endforeach()

    set(${result} ${TEST_SOURCES} PARENT_SCOPE)
endfunction()

function (get_test_helper_files_from a_module_dir result)
    get_all_test_files_from(${a_module_dir} EXTRA_TEST_SOURCES)

    # Exclude files ending with `_tests.cpp`
    foreach(file_path ${EXTRA_TEST_SOURCES})
        if(file_path MATCHES "_tests\\.cpp$")
            list(REMOVE_ITEM EXTRA_TEST_SOURCES "${file_path}")
        endif()
    endforeach()

    set(${result} ${EXTRA_TEST_SOURCES} PARENT_SCOPE)
endfunction()

function(register_module_tests module_name module_dir)
    set(optional_extra_test_deps ${ARGV2})  # get the 3rd argument manually (if provided)

    get_all_test_files_from(${module_dir} TEST_SOURCES)
    
    if(optional_extra_test_deps)
        get_test_helper_files_from(${optional_extra_test_deps} EXTRA_TEST_SOURCES)
        list(APPEND TEST_SOURCES ${EXTRA_TEST_SOURCES})
    endif()

    # debug
    # message(${module_dir})
    
    # if(${module_dir} MATCHES ".*src/DuplicationDetection$")
    #     message("!!!!!!! ${module_dir} \n")
    #     foreach(file_path ${TEST_SOURCES})
    #         message("found this: " ${file_path})
    #     endforeach()
    #     message("==============================\n")
    # endif()

    if(TEST_SOURCES)
        set(target_name "${module_name}_tests")
        add_executable(${target_name} ${TEST_SOURCES})
        target_link_libraries(${target_name}
            PRIVATE
                ${module_name}
                GTest::gtest_main
        )
        add_test(NAME ${target_name} COMMAND ${target_name})
        set_tests_properties(${target_name} PROPERTIES LABELS "${module_name}")
    else()
        message("I haven't found anything for ${module_name}")
    endif()
endfunction()
