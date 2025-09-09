cmake_minimum_required(VERSION 3.10)
project(ModelLoader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# Set pkg-config path for UCRT64
set(ENV{PKG_CONFIG_PATH} "C:/msys64/ucrt64/lib/pkgconfig")

# Find GTK4 using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

# Include directories
include_directories(
    ${GTK4_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/../model_loading/src
    ${PROJECT_SOURCE_DIR}/../model_loading/dependencies/include
    ${PROJECT_SOURCE_DIR}/../model_loading/include
)

# Add compile flags
add_compile_options(${GTK4_CFLAGS_OTHER} -fdiagnostics-color=always -g)

# Source files
set(SOURCES
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/../model_loading/src/mesh.cpp
    ${PROJECT_SOURCE_DIR}/../model_loading/src/texture_loader.cpp
    ${PROJECT_SOURCE_DIR}/../model_loading/src/model_loader.cpp
    ${PROJECT_SOURCE_DIR}/../model_loading/src/shaders/shader.cpp
    ${PROJECT_SOURCE_DIR}/../model_loading/src/model.cpp

)

# Create executable
add_executable(ModelLoader ${SOURCES})

# Link directories
target_link_directories(ModelLoader PRIVATE
    ${PROJECT_SOURCE_DIR}/dependencies/lib
    "C:/Users/HP/OneDrive/Documentos/Cyrus/Projects/model_loading/dependencies/lib"
)

# Link libraries (keyword signature only)
target_link_libraries(ModelLoader PRIVATE
    ${GTK4_LIBRARIES}
    glfw3dll
    glad
    assimp
    z
)

# Optional: suppress console window
set_target_properties(ModelLoader PROPERTIES WIN32_EXECUTABLE TRUE)
