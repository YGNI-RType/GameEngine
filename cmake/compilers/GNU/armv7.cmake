# Processor
set(CMAKE_SYSTEM_PROCESSOR arm)
# this one is important
set(CMAKE_SYSTEM_NAME Linux)
#this one not so much
set(CMAKE_SYSTEM_VERSION 1)

# (OPTIONAL) specify some CPU flags
# set(cpu_flags "-march=armv7-a -mfloat-abi=softfp -mfpu=neon")
set(cpu_flags "-march=armv7")

# specify the cross compiler
set(CMAKE_C_COMPILER   /usr/bin/arm-linux-gnueabi-gcc ${cpu_flags})
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++ ${cpu_flags})

set(CMAKE_STRIP /usr/bin/arm-linux-gnueabi-strip)

# where is the target environment
set(CMAKE_FIND_ROOT_PATH  /usr/arm-linux-gnueabi)

# search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)