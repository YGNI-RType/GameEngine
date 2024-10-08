# Processor
SET(CMAKE_SYSTEM_PROCESSOR arm)
# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# (OPTIONAL) specify some CPU flags
# SET(cpu_flags "-march=armv7-a -mfloat-abi=softfp -mfpu=neon")
SET(cpu_flags "-march=armv7")

# specify the cross compiler
SET(CMAKE_C_COMPILER   /usr/bin/arm-linux-gnueabi-gcc ${cpu_flags})
SET(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++ ${cpu_flags})

SET(CMAKE_STRIP /usr/bin/arm-linux-gnueabi-strip)

# where is the target environment
SET(CMAKE_FIND_ROOT_PATH  /usr/arm-linux-gnueabi)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)