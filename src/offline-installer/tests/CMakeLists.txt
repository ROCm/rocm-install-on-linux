# ##############################################################################
# Copyright (c) 2024 Advanced Micro Devices, Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# ##############################################################################

message(STATUS "+++++++++++++++++++++++++++")
message(STATUS "ROCm Offline Installer Test")
message(STATUS "+++++++++++++++++++++++++++")

set(INSTALLER_TEST_PATH $ENV{HOME})
set(INSTALLER_TEST_NAME "rocm-offline-install.run")
set(TIMEOUT_VALUE 2000)

message(STATUS "TEST: INSTALLER_TEST_PATH = " ${INSTALLER_TEST_PATH})
message(STATUS "TEST: INSTALLER_TEST_NAME = " ${INSTALLER_TEST_NAME})
message(STATUS "TEST: URL_CONFIG = " ${URL_CONFIG})


# Usage: 
# CI test           = ctest -L ci
# ROCm Version test = ctest -L <rocm version>    ie. 6.2.x, 6.1.x, 6.0.2, 5.7.3 
# Full test         = ctest

############ rocm only ############

# 6.2.1
add_test(NAME rocm-only-6.2.1
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-only-6.2.1.config url=${URL_CONFIG})
set_tests_properties(rocm-only-6.2.1 PROPERTIES DISABLED ${IS_ROCM_621_DISABLED} TIMEOUT ${TIMEOUT_VALUE} FAIL_REGULAR_EXPRESSION "amdgpu-dkms" LABELS "6.2.1")

add_test(NAME rocm-only-6.2.1-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-only-6.2.1-install-dryrun PROPERTIES DISABLED ${IS_ROCM_621_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "6.2.1")

# 6.2
add_test(NAME rocm-only-6.2
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-only-6.2.config)
set_tests_properties(rocm-only-6.2 PROPERTIES DISABLED ${IS_ROCM_62_DISABLED} TIMEOUT ${TIMEOUT_VALUE} FAIL_REGULAR_EXPRESSION "amdgpu-dkms" LABELS "6.2.0")

add_test(NAME rocm-only-6.2-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-only-6.2-install-dryrun PROPERTIES DISABLED ${IS_ROCM_62_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "6.2.0")

# 6.1.3
add_test(NAME rocm-only-6.1.3
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-only-6.1.3.config)
set_tests_properties(rocm-only-6.1.3 PROPERTIES DISABLED ${IS_ROCM_613_DISABLED} TIMEOUT ${TIMEOUT_VALUE} FAIL_REGULAR_EXPRESSION "amdgpu-dkms" LABELS "6.1.3")

add_test(NAME rocm-only-6.1.3-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-only-6.1.3-install-dryrun PROPERTIES DISABLED ${IS_ROCM_613_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.3")

# 6.1.2
add_test(NAME rocm-only-6.1.2
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-only-6.1.2.config)
set_tests_properties(rocm-only-6.1.2 PROPERTIES DISABLED ${IS_ROCM_612_DISABLED} TIMEOUT ${TIMEOUT_VALUE} FAIL_REGULAR_EXPRESSION "amdgpu-dkms" LABELS "6.1.2")

add_test(NAME rocm-only-6.1.2-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-only-6.1.2-install-dryrun PROPERTIES DISABLED ${IS_ROCM_612_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.2")

# 6.1.1
add_test(NAME rocm-only-6.1.1
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-only-6.1.1.config)
set_tests_properties(rocm-only-6.1.1 PROPERTIES DISABLED ${IS_ROCM_611_DISABLED} TIMEOUT ${TIMEOUT_VALUE} FAIL_REGULAR_EXPRESSION "amdgpu-dkms" LABELS "6.1.1")

add_test(NAME rocm-only-6.1.1-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-only-6.1.1-install-dryrun PROPERTIES DISABLED ${IS_ROCM_611_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.1")

# 6.1
add_test(NAME rocm-only-6.1
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-only-6.1.config)
set_tests_properties(rocm-only-6.1 PROPERTIES DISABLED ${IS_ROCM_61_DISABLED} TIMEOUT ${TIMEOUT_VALUE} FAIL_REGULAR_EXPRESSION "amdgpu-dkms" LABELS "6.1.0")

add_test(NAME rocm-only-6.1-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-only-6.1-install-dryrun PROPERTIES DISABLED ${IS_ROCM_61_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.0")

# 6.0.2
add_test(NAME rocm-only-6.0.2
        COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-only-6.0.2.config)       
set_tests_properties(rocm-only-6.0.2 PROPERTIES DISABLED ${IS_ROCM_602_DISABLED} TIMEOUT ${TIMEOUT_VALUE} FAIL_REGULAR_EXPRESSION "amdgpu-dkms" LABELS "6.0.2")

add_test(NAME rocm-only-6.0.2-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-only-6.0.2-install-dryrun PROPERTIES DISABLED ${IS_ROCM_602_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.0.2")

# 5.7.3
add_test(NAME rocm-only-5.7.3
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-only-5.7.3.config)                                 
set_tests_properties(rocm-only-5.7.3 PROPERTIES DISABLED ${IS_ROCM_573_DISABLED} TIMEOUT ${TIMEOUT_VALUE} FAIL_REGULAR_EXPRESSION "amdgpu-dkms" LABELS "5.7.3")

add_test(NAME rocm-only-5.7.3-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-only-5.7.3-install-dryrun PROPERTIES DISABLED ${IS_ROCM_573_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "5.7.3")

############ driver only ############

# 6.2.1
add_test(NAME driver-only-6.2.1
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-driver-only-6.2.1.config url=${URL_CONFIG})
set_tests_properties(driver-only-6.2.1 PROPERTIES DISABLED ${IS_ROCM_621_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "6.2.1")

add_test(NAME driver-only-6.2.1-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(driver-only-6.2.1-install-dryrun PROPERTIES DISABLED ${IS_ROCM_621_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "6.2.1")

# 6.2 
add_test(NAME driver-only-6.2
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-driver-only-6.2.config)
set_tests_properties(driver-only-6.2 PROPERTIES DISABLED ${IS_ROCM_62_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "6.2.0")

add_test(NAME driver-only-6.2-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(driver-only-6.2-install-dryrun PROPERTIES DISABLED ${IS_ROCM_62_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "6.2.0")

# 6.1.3 
add_test(NAME driver-only-6.1.3
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-driver-only-6.1.3.config)
set_tests_properties(driver-only-6.1.3 PROPERTIES DISABLED ${IS_ROCM_613_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.3")

add_test(NAME driver-only-6.1.3-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(driver-only-6.1.3-install-dryrun PROPERTIES DISABLED ${IS_ROCM_613_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.3")

# 6.1.2 
add_test(NAME driver-only-6.1.2
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-driver-only-6.1.2.config)
set_tests_properties(driver-only-6.1.2 PROPERTIES DISABLED ${IS_ROCM_612_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.2")

add_test(NAME driver-only-6.1.2-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(driver-only-6.1.2-install-dryrun PROPERTIES DISABLED ${IS_ROCM_612_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.2")

# 6.1.1 
add_test(NAME driver-only-6.1.1
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-driver-only-6.1.1.config)
set_tests_properties(driver-only-6.1.1 PROPERTIES DISABLED ${IS_ROCM_611_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.1")

add_test(NAME driver-only-6.1.1-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(driver-only-6.1.1-install-dryrun PROPERTIES DISABLED ${IS_ROCM_611_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.1")

# 6.1
add_test(NAME driver-only-6.1
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-driver-only-6.1.config)
set_tests_properties(driver-only-6.1 PROPERTIES DISABLED ${IS_ROCM_61_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.0")

add_test(NAME driver-only-6.1-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(driver-only-6.1-install-dryrun PROPERTIES DISABLED ${IS_ROCM_61_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.0")

# 6.0.2
add_test(NAME driver-only-6.0.2
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-driver-only-6.0.2.config)        
set_tests_properties(driver-only-6.0.2 PROPERTIES DISABLED ${IS_ROCM_602_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.0.2")

add_test(NAME driver-only-6.0.2-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(driver-only-6.0.2-install-dryrun PROPERTIES DISABLED ${IS_ROCM_602_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.0.2")

# 5.7.3
add_test(NAME driver-only-5.7.3
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-driver-only-5.7.3.config) 
set_tests_properties(driver-only-5.7.3 PROPERTIES DISABLED ${IS_ROCM_573_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "5.7.3")

add_test(NAME driver-only-5.7.3-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(driver-only-5.7.3-install-dryrun PROPERTIES DISABLED ${IS_ROCM_573_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "5.7.3")

############ rocm + driver ############

# 6.2.1
add_test(NAME rocm-driver-6.2.1
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-driver-6.2.1.config url=${URL_CONFIG})
set_tests_properties(rocm-driver-6.2.1 PROPERTIES DISABLED ${IS_ROCM_621_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "ci;6.2.1")

add_test(NAME rocm-driver-6.2.1-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-driver-6.2.1-install-dryrun PROPERTIES DISABLED ${IS_ROCM_621_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "ci;6.2.1")

# 6.2
add_test(NAME rocm-driver-6.2
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-driver-6.2.config)
set_tests_properties(rocm-driver-6.2 PROPERTIES DISABLED ${IS_ROCM_62_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "ci;6.2.0")

add_test(NAME rocm-driver-6.2-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-driver-6.2-install-dryrun PROPERTIES DISABLED ${IS_ROCM_62_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "ci;6.2.0")

# 6.1.3
add_test(NAME rocm-driver-6.1.3
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-driver-6.1.3.config)
set_tests_properties(rocm-driver-6.1.3 PROPERTIES DISABLED ${IS_ROCM_613_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "ci;6.1.3")

add_test(NAME rocm-driver-6.1.3-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-driver-6.1.3-install-dryrun PROPERTIES DISABLED ${IS_ROCM_613_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "ci;6.1.3")

# 6.1.2
add_test(NAME rocm-driver-6.1.2
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-driver-6.1.2.config)
set_tests_properties(rocm-driver-6.1.2 PROPERTIES DISABLED ${IS_ROCM_612_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "ci;6.1.2")

add_test(NAME rocm-driver-6.1.2-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-driver-6.1.2-install-dryrun PROPERTIES DISABLED ${IS_ROCM_612_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "ci;6.1.2")

# 6.1.1
add_test(NAME rocm-driver-6.1.1
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-driver-6.1.1.config)
set_tests_properties(rocm-driver-6.1.1 PROPERTIES DISABLED ${IS_ROCM_611_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "ci;6.1.1")

add_test(NAME rocm-driver-6.1.1-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-driver-6.1.1-install-dryrun PROPERTIES DISABLED ${IS_ROCM_611_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "ci;6.1.1")

# 6.1
add_test(NAME rocm-driver-6.1
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-driver-6.1.config)
set_tests_properties(rocm-driver-6.1 PROPERTIES DISABLED ${IS_ROCM_61_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "ci;6.1.0")

add_test(NAME rocm-driver-6.1-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-driver-6.1-install-dryrun PROPERTIES DISABLED ${IS_ROCM_61_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "ci;6.1.0")

# 6.0.2
add_test(NAME rocm-driver-6.0.2
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-driver-6.0.2.config)
set_tests_properties(rocm-driver-6.0.2 PROPERTIES DISABLED ${IS_ROCM_602_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "ci;6.0.2")

add_test(NAME rocm-driver-6.0.2-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-driver-6.0.2-install-dryrun PROPERTIES DISABLED ${IS_ROCM_602_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "ci;6.0.2")

# 5.7.3
add_test(NAME rocm-driver-5.7.3
        COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-driver-5.7.3.config)             
set_tests_properties(rocm-driver-5.7.3 PROPERTIES DISABLED ${IS_ROCM_573_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "ci;5.7.3")

add_test(NAME rocm-driver-5.7.3-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-driver-5.7.3-install-dryrun PROPERTIES DISABLED ${IS_ROCM_573_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "ci;5.7.3")

############ rocm,graphics ############

# 6.2.1
add_test(NAME rocm-graphics-6.2.1
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-graphics-6.2.1.config url=${URL_CONFIG})
set_tests_properties(rocm-graphics-6.2.1 PROPERTIES DISABLED ${IS_ROCM_621_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.2.1")

add_test(NAME rocm-graphics-6.2.1-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-graphics-6.2.1-install-dryrun PROPERTIES DISABLED ${IS_ROCM_621_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.2.1")

# 6.2
add_test(NAME rocm-graphics-6.2
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-graphics-6.2.config)
set_tests_properties(rocm-graphics-6.2 PROPERTIES DISABLED ${IS_ROCM_62_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.2.0")

add_test(NAME rocm-graphics-6.2-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-graphics-6.2-install-dryrun PROPERTIES DISABLED ${IS_ROCM_62_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.2.0")

# 6.1.3
add_test(NAME rocm-graphics-6.1.3
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-graphics-6.1.3.config)
set_tests_properties(rocm-graphics-6.1.3 PROPERTIES DISABLED ${IS_ROCM_613_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.3")

add_test(NAME rocm-graphics-6.1.3-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-graphics-6.1.3-install-dryrun PROPERTIES DISABLED ${IS_ROCM_613_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.3")

# 6.1.2
add_test(NAME rocm-graphics-6.1.2
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-graphics-6.1.2.config)
set_tests_properties(rocm-graphics-6.1.2 PROPERTIES DISABLED ${IS_ROCM_612_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.2")

add_test(NAME rocm-graphics-6.1.2-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-graphics-6.1.2-install-dryrun PROPERTIES DISABLED ${IS_ROCM_612_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.2")

# 6.1.1
add_test(NAME rocm-graphics-6.1.1
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-graphics-6.1.1.config)
set_tests_properties(rocm-graphics-6.1.1 PROPERTIES DISABLED ${IS_ROCM_611_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.1")

add_test(NAME rocm-graphics-6.1.1-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-graphics-6.1.1-install-dryrun PROPERTIES DISABLED ${IS_ROCM_611_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.1")

# 6.1
add_test(NAME rocm-graphics-6.1
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-graphics-6.1.config)
set_tests_properties(rocm-graphics-6.1 PROPERTIES DISABLED ${IS_ROCM_61_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.0")

add_test(NAME rocm-graphics-6.1-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-graphics-6.1-install-dryrun PROPERTIES DISABLED ${IS_ROCM_61_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.0")

# 6.0.2
add_test(NAME rocm-graphics-6.0.2
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-graphics-6.0.2.config)
set_tests_properties(rocm-graphics-6.0.2 PROPERTIES DISABLED ${IS_ROCM_602_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.0.2")

add_test(NAME rocm-graphics-6.0.2-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-graphics-6.0.2-install-dryrun PROPERTIES DISABLED ${IS_ROCM_602_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.0.2")

# 5.7.3
add_test(NAME rocm-graphics-5.7.3
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-rocm-graphics-5.7.3.config)
set_tests_properties(rocm-graphics-5.7.3 PROPERTIES DISABLED ${IS_ROCM_573_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "5.7.3")

add_test(NAME rocm-graphics-5.7.3-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(rocm-graphics-5.7.3-install-dryrun PROPERTIES DISABLED ${IS_ROCM_573_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "5.7.3")

############ hip,hipsdk ############

# 6.2.1
add_test(NAME hip-hiplibsdk-6.2.1
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-hip-hiplibsdk-6.2.1.config url=${URL_CONFIG})
set_tests_properties(hip-hiplibsdk-6.2.1 PROPERTIES DISABLED ${IS_ROCM_621_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.2.1")

add_test(NAME hip-hiplibsdk-6.2.1-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(hip-hiplibsdk-6.2.1-install-dryrun PROPERTIES DISABLED ${IS_ROCM_621_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.2.1")

# 6.2
add_test(NAME hip-hiplibsdk-6.2
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-hip-hiplibsdk-6.2.config)
set_tests_properties(hip-hiplibsdk-6.2 PROPERTIES DISABLED ${IS_ROCM_62_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.2.0")

add_test(NAME hip-hiplibsdk-6.2-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(hip-hiplibsdk-6.2-install-dryrun PROPERTIES DISABLED ${IS_ROCM_62_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.2.0")

# 6.1.3
add_test(NAME hip-hiplibsdk-6.1.3
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-hip-hiplibsdk-6.1.3.config)
set_tests_properties(hip-hiplibsdk-6.1.3 PROPERTIES DISABLED ${IS_ROCM_613_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.3")

add_test(NAME hip-hiplibsdk-6.1.3-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(hip-hiplibsdk-6.1.3-install-dryrun PROPERTIES DISABLED ${IS_ROCM_613_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.3")

# 6.1.2
add_test(NAME hip-hiplibsdk-6.1.2
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-hip-hiplibsdk-6.1.2.config)
set_tests_properties(hip-hiplibsdk-6.1.2 PROPERTIES DISABLED ${IS_ROCM_612_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.2")

add_test(NAME hip-hiplibsdk-6.1.2-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(hip-hiplibsdk-6.1.2-install-dryrun PROPERTIES DISABLED ${IS_ROCM_612_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.2")

# 6.1.1
add_test(NAME hip-hiplibsdk-6.1.1
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-hip-hiplibsdk-6.1.1.config)
set_tests_properties(hip-hiplibsdk-6.1.1 PROPERTIES DISABLED ${IS_ROCM_611_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.1")

add_test(NAME hip-hiplibsdk-6.1.1-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(hip-hiplibsdk-6.1.1-install-dryrun PROPERTIES DISABLED ${IS_ROCM_611_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.1")

# 6.1
add_test(NAME hip-hiplibsdk-6.1
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-hip-hiplibsdk-6.1.config)
set_tests_properties(hip-hiplibsdk-6.1 PROPERTIES DISABLED ${IS_ROCM_61_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.0")

add_test(NAME hip-hiplibsdk-6.1-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(hip-hiplibsdk-6.1-install-dryrun PROPERTIES DISABLED ${IS_ROCM_61_DISABLED}  TIMEOUT ${TIMEOUT_VALUE} LABELS "6.1.0")

# 6.0.2
add_test(NAME hip-hiplibsdk-6.0.2
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-hip-hiplibsdk-6.0.2.config)
set_tests_properties(hip-hiplibsdk-6.0.2 PROPERTIES DISABLED ${IS_ROCM_602_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.0.2")

add_test(NAME hip-hiplibsdk-6.0.2-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(hip-hiplibsdk-6.0.2-install-dryrun PROPERTIES DISABLED ${IS_ROCM_602_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "6.0.2")

# 5.7.3
add_test(NAME hip-hiplibsdk-5.7.3
         COMMAND ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}.run config=${CMAKE_SOURCE_DIR}/tests/create-test-hip-hiplibsdk-5.7.3.config)
set_tests_properties(hip-hiplibsdk-5.7.3 PROPERTIES DISABLED ${IS_ROCM_573_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "5.7.3")

add_test(NAME hip-hiplibsdk-5.7.3-install-dryrun COMMAND ${INSTALLER_TEST_PATH}/${INSTALLER_TEST_NAME} dryrun)
set_tests_properties(hip-hiplibsdk-5.7.3-install-dryrun PROPERTIES DISABLED ${IS_ROCM_573_DISABLED} TIMEOUT ${TIMEOUT_VALUE} LABELS "5.7.3")
