cmake_minimum_required(VERSION 3.21)
project(engineDirectX LANGUAGES CXX)

# ---- C++ standard ----
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Windows only (DX11) ----
if (NOT WIN32)
    message(FATAL_ERROR "This project requires Windows (DirectX 11)")
endif()

# ---- Source files ----
file(GLOB_RECURSE ENGINE_SRC
        src/Engine/*.cpp
)

add_executable(app WIN32
        src/main.cpp
        ${ENGINE_SRC}
)

# ---- Include paths ----
target_include_directories(app PRIVATE
        src
        src/Engine
)

# ---- DirectX 11 ----
target_link_libraries(app PRIVATE
        d3d11
        dxgi
        d3dcompiler
)

# ---- Warnings ----
if (MSVC)
    target_compile_options(app PRIVATE /W4)
else()
    target_compile_options(app PRIVATE -Wall -Wextra)
endif()
