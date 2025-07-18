# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

project("native-http")


#-Wall:
#启用所有常规的警告消息。这有助于发现潜在的代码问题。
#-std=c++14:
#指定 C++ 标准为 C++14。确保编译器使用 C++14 标准进行编译。
#-pthread:
#启用多线程支持，并链接 pthread 库。这对于使用线程的程序是必需的。
#-fno-omit-frame-pointer:
#不省略帧指针。这对调试和性能分析工具（如 gdb 和 perf）有帮助。
#-fexceptions:
#启用 C++ 异常处理支持。允许在代码中使用 try, catch, throw。
#-frtti:
#启用运行时类型识别 (RTTI)。允许使用 C++ 的 typeid 和 dynamic_cast 操作符。
#-ffunction-sections:
#将每个函数或数据项放入单独的段中。这可以在链接时实现更好的优化和裁剪未使用的代码。
#-O3:
#启用最高级别的优化选项。这会生成更快的代码，但可能会使编译时间更长。
add_compile_options(
        -Wall
        -std=c++17
        -pthread
        -fno-omit-frame-pointer
        -fexceptions
        -frtti
        -ffunction-sections
        -O0 # just for debug
)

include_directories(curl/modules/curl_static/include)
add_subdirectory(curl)

add_library(${CMAKE_PROJECT_NAME} SHARED
        onLoad.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME}
        curl_android
        log)