cmake_minimum_required(VERSION 3.21)
project(test_app)

#target info
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Tool chain used. https://developer.arm.com/downloads/-/gnu-a
# run time complaints similiar to "version `GLIBC_2.34' not found " mean the tool chain
# doesn't match what was used on the target platform.
# The version for GLIBC was found in "aarch64-linux-gnu/libc/usr/include/features.h" 
# Adjust to match use case.
set(CMAKE_C_COMPILER ~/Downloads/gcc-arm-8.3-2019.03-x86_64-aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER ~/Downloads/gcc-arm-8.3-2019.03-x86_64-aarch64-linux-gnu/bin/aarch64-linux-gnu-g++)

## If needed add the target rootfs generated from buildroot
# set(CMAKE_FIND_ROOT_PATH /mount/target_rootfs_from_buildroot)

set(SOURCE_FILES
    test_app.c)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
