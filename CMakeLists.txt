cmake_minimum_required(VERSION 3.19)
project(ImageDownloader)

set(CMAKE_CXX_STANDARD 14)

set(CURL_LIBRARIES /usr/lib64/libcurl.so)
include_directories(include)
add_executable(ImageDownloader src/main.cpp src/Application.cpp src/DownloadManager.cpp)

target_link_libraries(ImageDownloader ${CURL_LIBRARIES} pthread)