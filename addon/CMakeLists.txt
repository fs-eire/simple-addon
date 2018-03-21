# Files to compile
file(GLOB SOURCE_FILES 
    "addon.cpp"
    "platform/*.cpp"
    )

# The addon name
set(TARGET_NAME "${PROJECT_NAME}")

# The generated library
add_library(${TARGET_NAME} SHARED ${SOURCE_FILES} )

set_target_properties(${TARGET_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

# Rpath definitions

if (APPLE)
    set_target_properties(${TARGET_NAME} PROPERTIES INSTALL_RPATH "@loader_path")
else ()
    set_target_properties(${TARGET_NAME} PROPERTIES INSTALL_RPATH "$ORIGIN/")
endif()

set_target_properties(${TARGET_NAME} PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH_USE_LINK_PATH FALSE)

# Include directories
target_include_directories(${TARGET_NAME} PRIVATE
     "D:\\eire\\prototype\\node\\src"
     "D:\\eire\\prototype\\node\\deps\\v8\\include"
     "D:\\eire\\prototype\\node\\deps\\uv\\include"
    PUBLIC
    ${PROJECT_SOURCE_DIR}/addon
    ${PROJECT_SOURCE_DIR}/inc)

# Using the V8 functions exported from node.exe
target_link_libraries(${TARGET_NAME} PRIVATE "D:\\eire\\prototype\\node\\Debug\\node.lib")


target_compile_definitions(${TARGET_NAME} PRIVATE USING_V8_SHARED)

# Compiler definitions
target_compile_definitions(${TARGET_NAME} PRIVATE BUILDING_NODE_EXTENSION NAPA_BINDING_EXPORTS)
