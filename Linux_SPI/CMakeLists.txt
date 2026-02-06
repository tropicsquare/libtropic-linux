cmake_minimum_required(VERSION 3.21.0)

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
set(PATH_VENDOR ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/)
set(PATH_LIBTROPIC ${PATH_VENDOR}libtropic/)

include(${PATH_LIBTROPIC}cmake/strict_compile_flags.cmake)
include(${PATH_LIBTROPIC}cmake/static_asan_flags.cmake)

###########################################################################
#                                                                         #
#   Options and user configuration                                        #
#                                                                         #
###########################################################################

# Select CAL
set(LT_CAL "" CACHE STRING "Set a CAL (Crypto Abstraction Layer)")
set_property(CACHE LT_CAL PROPERTY STRINGS "trezor_crypto" "mbedtls_v4")

# Optional prefix to tests registered to CTest. Useful when running same test against
# different chips to differentiate them by their name in JUnit output.
if (NOT DEFINED CTEST_PREFIX)
    set(CTEST_PREFIX "")
endif()

option(LT_ASAN "Enable static AddressSanitizer (ASan)" OFF)
option(LT_STRICT_COMPILATION "Enable strict compilation flags" ON)

###########################################################################
#                                                                         #
#   Add libtropic library and set it up                                   #
#                                                                         #
###########################################################################

# Add path to libtropic's repository root folder
add_subdirectory(${PATH_LIBTROPIC} "libtropic")

# Customize libtropic's compilation
target_compile_options(tropic PRIVATE -ffunction-sections -fdata-sections)

if(LT_ASAN)
    message(STATUS "AddressSanitizer (ASan) is enabled for the entire project.")
    add_compile_options(${LT_ASAN_COMPILE_FLAGS})
    add_link_options(${LT_ASAN_LINK_FLAGS})
endif()

if(LT_STRICT_COMPILATION)
    message(STATUS "Enabling strict compilation flags.")
    # Enable strict compile flags for Libtropic library
    target_link_libraries(tropic PRIVATE libtropic::strict_comp_flags)
endif()

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
# It's used in main.c to switch crypto contexts without manual changes
set(LT_USE_TREZOR_CRYPTO 0 CACHE INTERNAL "")
set(LT_USE_MBEDTLS_V4 0 CACHE INTERNAL "")

# Handle LT_CAL
if(LT_CAL STREQUAL "trezor_crypto")
    message(STATUS "Crypto provider set to trezor_crypto")
    add_subdirectory("${PATH_LIBTROPIC}cal/trezor_crypto" "trezor_crypto_cal")
    
    # Developers who integrate Libtropic do not have to use this variable
    # It's used in main.c to switch crypto contexts without manual changes
    set(LT_USE_TREZOR_CRYPTO 1)

    add_subdirectory("${PATH_LIBTROPIC}/vendor/trezor_crypto/" "trezor_crypto")
    target_compile_definitions(trezor_crypto PRIVATE AES_VAR USE_INSECURE_PRNG)
    target_link_libraries(tropic PUBLIC trezor_crypto)
elseif(LT_CAL STREQUAL "mbedtls_v4")
    message(STATUS "Crypto provider set to mbedtls_v4")
    add_subdirectory("${PATH_LIBTROPIC}cal/mbedtls_v4" "mbedtls_v4_cal")

    # Developers who integrate Libtropic do not have to use this variable
    # It's used in main.c to switch crypto contexts without manual changes
    set(LT_USE_MBEDTLS_V4 1)

    set(ENABLE_TESTING OFF CACHE BOOL "Disable mbedtls_v4 test building.")
    set(ENABLE_PROGRAMS OFF CACHE BOOL "Disable mbedtls_v4 examples building.")
    add_subdirectory("${PATH_VENDOR}mbedtls_v4/" "mbedtls_v4")

    target_link_libraries(tropic PUBLIC mbedtls)
else()
    get_property(lt_cal_choices CACHE LT_CAL PROPERTY STRINGS)
    message(FATAL_ERROR "Incorrect CAL set to LT_CAL!\nSupported CALs: ${lt_cal_choices}")
endif()

target_sources(tropic PRIVATE ${LT_CAL_SRCS})
target_include_directories(tropic PUBLIC ${LT_CAL_INC_DIRS})


###########################################################################
#                                                                         #
#   SOURCES                                                               #
#   Define project sources.                                               #
#                                                                         #
###########################################################################

# Add SPI Linux HAL
add_subdirectory("${PATH_LIBTROPIC}hal/linux/spi" "linux_spi_hal")
target_sources(tropic PRIVATE ${LT_HAL_SRCS})
target_include_directories(tropic PUBLIC ${LT_HAL_INC_DIRS})

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
)

# Enable strict compile flags for main.c and Libtropic HAL sources
if(LT_STRICT_COMPILATION)
    set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/src/main.c ${LT_HAL_SRCS} PROPERTIES COMPILE_OPTIONS "${LT_STRICT_COMPILATION_FLAGS}")   
endif()

# Special dependencies for tests, such as signature verification libraries
if(LT_BUILD_TESTS)
    # micro-ecc library is used for ECDSA signature verification
    add_library(micro_ecc_lib STATIC
        ${PATH_VENDOR}/micro-ecc/uECC.c
    )

    target_include_directories(micro_ecc_lib PUBLIC # PUBLIC as it is also used in tropic target
        ${PATH_VENDOR}/micro-ecc
    )

    target_link_libraries(tropic PRIVATE micro_ecc_lib)

    # ed25519 library is used for EdDSA signature verification
    add_library(ed25519_lib STATIC
        ${PATH_VENDOR}/ed25519/src/verify.c
        ${PATH_VENDOR}/ed25519/src/add_scalar.c
        ${PATH_VENDOR}/ed25519/src/fe.c
        ${PATH_VENDOR}/ed25519/src/ge.c
        ${PATH_VENDOR}/ed25519/src/key_exchange.c
        ${PATH_VENDOR}/ed25519/src/keypair.c
        ${PATH_VENDOR}/ed25519/src/sc.c
        ${PATH_VENDOR}/ed25519/src/seed.c
        ${PATH_VENDOR}/ed25519/src/sha512.c
        ${PATH_VENDOR}/ed25519/src/sign.c
    )

    target_include_directories(ed25519_lib PUBLIC # PUBLIC as it is also used in tropic target
        ${PATH_VENDOR}/ed25519/src/
    )

    target_link_libraries(tropic PRIVATE ed25519_lib)
endif()

###########################################################################
#                                                                         #
#   EXAMPLES CONFIGURATION                                                #
#                                                                         #
###########################################################################

if (LT_BUILD_EXAMPLES)

    # DISABLE IRREVERSIBLE EXAMPLES FOR SAFETY
    # These examples perform irreversible operations on the TROPIC01.
    # They are disabled by default to prevent accidental usage and should
    # be normally used only with the model.
    list(REMOVE_ITEM LIBTROPIC_EXAMPLE_LIST "lt_ex_hardware_wallet")

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

        # Enable example registry using LT_BUILD_EXAMPLES and choose correct example for the binary.
        target_compile_definitions(${exe_name} PRIVATE LT_BUILD_EXAMPLES)
        target_compile_definitions(${exe_name} PRIVATE ${example_macro})
        
        # Developers who integrate Libtropic do not have to use these variables
        # It's used in main.c to switch crypto contexts without manual changes
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

        # Enable test registry using LT_BUILD_TESTS and choose correct test for the binary.
        target_compile_definitions(${exe_name} PRIVATE LT_BUILD_TESTS)
        target_compile_definitions(${exe_name} PRIVATE ${test_macro})

        # Developers who integrate Libtropic do not have to use this variable
        # It's used in main.c to switch crypto contexts without manual changes
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