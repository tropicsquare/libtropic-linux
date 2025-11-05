cmake_minimum_required(VERSION 3.21.0)

include(FetchContent)

###########################################################################
#                                                                         #
#   Define project's name                                                 #
#                                                                         #
###########################################################################
project(libtropic_linux
        VERSION 0.1.0
        DESCRIPTION "Example of libtropic usage in Linux environment using kernel SPI driver"
        LANGUAGES C)

###########################################################################
#                                                                         #
#   Paths and setup                                                       #
#                                                                         #
###########################################################################
set(PATH_LIBTROPIC ${CMAKE_CURRENT_SOURCE_DIR}/../libtropic/)

# Optional prefix to tests registered to CTest. Useful when running same test against
# different chips to differentiate them by their name in JUnit output.
if (NOT DEFINED CTEST_PREFIX)
    set(CTEST_PREFIX "")
endif()

###########################################################################
#                                                                         #
#   Options                                                               #
#                                                                         #
###########################################################################

# Select CAL
set(LT_CAL "" CACHE STRING "Set a CAL (Crypto Abstraction Layer)")
set_property(CACHE LT_CAL PROPERTY STRINGS "trezor_crypto" "mbedtls_v4")

###########################################################################
#                                                                         #
#   Add libtropic library and set it up                                   #
#                                                                         #
###########################################################################

# Add path to libtropic's repository root folder
add_subdirectory(${PATH_LIBTROPIC} "libtropic")

# Customize libtropic's compilation
target_compile_options(tropic PRIVATE -ffunction-sections -fdata-sections)

###########################################################################
#                                                                         #
#   Crypto backend handling                                               #
#                                                                         #
#   Note: The libtropic consumer does not have to do this in his          #
#   application, we do this to quickly switch crypto backends.            #
#   Refer to the libtropic documentation for more info about what should  #
#   be done by the consumer.                                              #
#                                                                         #
###########################################################################

# Developers who integrate Libtropic do not have to use these variables
# It's used in model's main.c to switch crypto contexts without manual changes
set(LT_USE_TREZOR_CRYPTO 0 CACHE INTERNAL "")
set(LT_USE_MBEDTLS_V4 0 CACHE INTERNAL "")

# Handle LT_CAL
if(LT_CAL STREQUAL "trezor_crypto")
    message(STATUS "Crypto provider set to trezor_crypto")
    add_subdirectory("${PATH_LIBTROPIC}cal/trezor_crypto" "trezor_crypto_cal")
    
    # Developers who integrate Libtropic do not have to use this variable
    # It's used in model's main.c to switch crypto contexts without manual changes
    set(LT_USE_TREZOR_CRYPTO 1)

    add_subdirectory("${PATH_LIBTROPIC}/vendor/trezor_crypto/" "trezor_crypto")
    target_compile_definitions(trezor_crypto PRIVATE AES_VAR USE_INSECURE_PRNG)
    target_link_libraries(tropic PUBLIC trezor_crypto)
elseif(LT_CAL STREQUAL "mbedtls_v4")
    message(STATUS "Crypto provider set to mbedtls_v4")
    add_subdirectory("${PATH_LIBTROPIC}cal/mbedtls_v4" "mbedtls_v4_cal")

    # Developers who integrate Libtropic do not have to use this variable
    # It's used in model's main.c to switch crypto contexts without manual changes
    set(LT_USE_MBEDTLS_V4 1)

    # Fetch MbedTLS v4.0.0
    FetchContent_Declare(
        mbedtls
        URL https://github.com/Mbed-TLS/mbedtls/releases/download/mbedtls-4.0.0/mbedtls-4.0.0.tar.bz2
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    set(ENABLE_TESTING OFF CACHE BOOL "Disable mbedtls_v4 test building.")
    set(ENABLE_PROGRAMS OFF CACHE BOOL "Disable mbedtls_v4 examples building.")
    FetchContent_MakeAvailable(mbedtls)

    target_link_libraries(tropic PUBLIC mbedtls)
else()
    get_property(lt_cal_choices CACHE LT_CAL PROPERTY STRINGS)
    message(FATAL_ERROR "Incorrect CAL set to LT_CAL!\nSupported CALs by the model: ${lt_cal_choices}")
endif()

target_sources(tropic PRIVATE ${LT_CAL_SRCS})
target_include_directories(tropic PUBLIC ${LT_CAL_INC_DIRS})


###########################################################################
#                                                                         #
#   SOURCES                                                               #
#   Define project sources.                                               #
#                                                                         #
###########################################################################

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
    ${PATH_LIBTROPIC}/hal/port/unix/libtropic_port_unix_spi.c
)

include_directories(
    ${PATH_LIBTROPIC}/hal/port/unix
)

###########################################################################
#                                                                         #
#   EXAMPLES CONFIGURATION                                                #
#                                                                         #
###########################################################################

if (LT_BUILD_EXAMPLES)

    # So we can include preprocessed example registry (lt_ex_registry.c.inc).
    include_directories(${CMAKE_CURRENT_BINARY_DIR}/libtropic)

    # Loop through examples defined in libtropic and prepare environment.
    foreach(example_name IN LISTS LIBTROPIC_EXAMPLE_LIST)

        # Create a correct macro from example name.
        string(TOUPPER ${example_name} example_macro)
        string(REPLACE " " "_" example_macro ${example_macro})

        set(exe_name ${example_name})

        # Define executable (separate for each example) and link dependencies.
        add_executable(${exe_name} ${SOURCES})
        target_link_libraries(${exe_name} PRIVATE tropic)

        # Apply the strict compilation flags
        # (they are already applied for libtropic from the libtropic's CMakeLists.txt)
        if(LT_STRICT_COMP_FLAGS)
            target_link_libraries(${exe_name} PRIVATE libtropic::strict_comp_flags)
        endif()

        # Enable example registry using LT_BUILD_EXAMPLES and choose correct example for the binary.
        target_compile_definitions(${exe_name} PRIVATE LT_BUILD_EXAMPLES)
        target_compile_definitions(${exe_name} PRIVATE ${example_macro})
        
        # Developers who integrate Libtropic do not have to use these variables
        # It's used in model's main.c to switch crypto contexts without manual changes
        target_compile_definitions(${exe_name} PRIVATE
            LT_USE_TREZOR_CRYPTO=${LT_USE_TREZOR_CRYPTO}
            LT_USE_MBEDTLS_V4=${LT_USE_MBEDTLS_V4}
        )

    endforeach()

endif()

###########################################################################
#                                                                         #
# FUNCTIONAL TESTS CONFIGURATION                                          #
#                                                                         #
# This section will automatically configure CTest for launching tests     #
# defined in libtropic. Do NOT hardcode any test definitions here.        #
# Define them in libtropic.                                               #
#                                                                         #
# To build functional tests, use -DLT_BUILD_TESTS=1 in cmake invocation.  #
#                                                                         #
###########################################################################

if(LT_BUILD_TESTS)
    # Enable CTest.
    enable_testing()
    
    # So we can include preprocessed test registry (lt_test_registry.c.inc).
    include_directories(${CMAKE_CURRENT_BINARY_DIR}/libtropic)

    # Loop through tests defined in libtropic and prepare environment.
    foreach(test_name IN LISTS LIBTROPIC_TEST_LIST)
    
        # Create a correct macro from test name.
        string(TOUPPER ${test_name} test_macro)
        string(REPLACE " " "_" test_macro ${test_macro})

        set(exe_name ${test_name})

        # Define executable (separate for each test) and link dependencies.
        add_executable(${exe_name} ${SOURCES})
        target_link_libraries(${exe_name} PRIVATE tropic)

        # Apply the strict compilation flags
        # (they are already applied for libtropic from the libtropic's CMakeLists.txt)
        if(LT_STRICT_COMP_FLAGS)
            target_link_libraries(${exe_name} PRIVATE libtropic::strict_comp_flags)
        endif()

        # Enable test registry using LT_BUILD_TESTS and choose correct test for the binary.
        target_compile_definitions(${exe_name} PRIVATE LT_BUILD_TESTS)
        target_compile_definitions(${exe_name} PRIVATE ${test_macro})

        # Developers who integrate Libtropic do not have to use this variable
        # It's used in model's main.c to switch crypto contexts without manual changes
        target_compile_definitions(${exe_name} PRIVATE
            LT_USE_TREZOR_CRYPTO=${LT_USE_TREZOR_CRYPTO}
            LT_USE_MBEDTLS_V4=${LT_USE_MBEDTLS_V4}
        )

        if(CTEST_PREFIX STREQUAL "")
            set(TEST_NAME_WITH_PREFIX ${test_name})
        else()
            set(TEST_NAME_WITH_PREFIX ${CTEST_PREFIX}_${test_name})
        endif()

        # Add CTest entry.
        add_test(NAME ${TEST_NAME_WITH_PREFIX}
                 COMMAND stdbuf -oL -eL ${CMAKE_CURRENT_BINARY_DIR}/${exe_name}
        )
        set_property(TEST ${TEST_NAME_WITH_PREFIX}
                     PROPERTY FAIL_REGULAR_EXPRESSION "ERROR;WARNING"
        )
    endforeach()
endif()