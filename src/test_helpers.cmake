# Enable testing
include(CTest)
enable_testing()

# GoogleTest via FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

function(register_module_tests module_name module_dir)
    file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
        "${module_dir}/*__tests__/*.cpp"
    )

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