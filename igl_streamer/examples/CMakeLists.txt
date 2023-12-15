cmake_minimum_required(VERSION 3.8)
#project(nadjieb_mjpeg_streamer_examples LANGUAGES CXX)
set(igl_to_opencv_link_libs igl_to_opencv)
find_package(nadjieb_mjpeg_streamer REQUIRED)

find_package(OpenCV 4.2 REQUIRED)
add_executable(igl_streamer example.cpp)
target_compile_features(igl_streamer PRIVATE cxx_std_17)

target_link_libraries(igl_streamer
    PRIVATE
        nadjieb_mjpeg_streamer::nadjieb_mjpeg_streamer
        ${OpenCV_LIBS}
        ${igl_to_opencv_link_libs}
)

target_compile_options(igl_streamer PUBLIC -Wall)

install(TARGETS igl_streamer DESTINATION bin)
