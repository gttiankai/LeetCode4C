# Sets the minimum version of CMake required to build your native library.
# This ensures that a certain set of CMake features is available to
# your build.

cmake_minimum_required(VERSION 3.4.1)

# Specifies a library name, specifies whether the library is STATIC or
# SHARED, and provides relative paths to the source code. You can
# define multiple libraries by adding multiple add.library() commands,
# and CMake builds them for you. When you build your app, Gradle
# automatically packages shared libraries with your APK.


add_library( # Specifies the name of the library.
        xhook

        # Sets the library as a shared library.
        STATIC

        # Provides a relative path to your source file(s).
        app/src/main/cpp/libxhook/xh_core.c
        app/src/main/cpp/libxhook/xh_elf.c
        app/src/main/cpp/libxhook/xh_jni.c
        app/src/main/cpp/libxhook/xh_log.c
        app/src/main/cpp/libxhook/xh_util.c
        app/src/main/cpp/libxhook/xh_version.c
        app/src/main/cpp/libxhook/xhook.c
        )

add_library( # Specifies the name of the library.
        hook_js

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        #app/src/main/cpp/hook_js.c
        app/src/main/cpp/hook_js.cpp
        app/src/main/cpp/asset_manager_hook.cpp
        app/src/main/cpp/zip_utils_hook.cpp
        app/src/main/cpp/rc4.c
        app/src/main/cpp/asset_hook.cpp
        app/src/main/cpp/libutils_hook.cpp
        )


include_directories(src/main/cpp/libxhook)

find_library( # Defines the name of the path variable that stores the
        # location of the NDK library.
        log-lib

        # Specifies the name of the NDK library that
        # CMake needs to locate.
        log)

# Links your native library against one or more other native libraries.
target_link_libraries( # Specifies the target library.
        hook_js

        # Links the log library to the target library.
        xhook
        ${log-lib})