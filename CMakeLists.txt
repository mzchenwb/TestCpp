cmake_minimum_required(VERSION 3.6)
project(TestCpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        transcode_aac.c
        avio_reading.c
        cpp_main.cpp
        test.cpp buf_queue.cpp buf_queue.h)
add_executable(TestCpp ${SOURCE_FILES})

include_directories(
        /home/chenwb/ffmpeg_build2/include
)
link_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
)
target_link_libraries( # Specifies the target library.
        TestCpp
        /home/chenwb/ffmpeg_build2/lib/libavcodec.so
        /home/chenwb/ffmpeg_build2/lib/libavformat.so
        /home/chenwb/ffmpeg_build2/lib/libavutil.so
        /home/chenwb/ffmpeg_build2/lib/libswresample.so
        /home/chenwb/ffmpeg_build2/lib/libavfilter.so
)