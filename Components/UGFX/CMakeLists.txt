cmake_minimum_required(VERSION 3.10)

# Put directory name to COMPONENT_NAME variable
get_filename_component(COMPONENT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
# Set component name
project(${COMPONENT_NAME})


# Файлы с исходым кодом
FILE(
    GLOB 
    SOURCE_LIB 
    # "ugfx_2.9/src/gfx_mk.c"
    "Extended/gfx_mk_extended.c"
    "ugfx_2.9/drivers/multiple/Win32/*.c"
    )


# Creating static library
add_library(${COMPONENT_NAME} STATIC ${SOURCE_LIB})

# Add includes
target_include_directories(
    ${COMPONENT_NAME}
    PUBLIC 
    Config
    ugfx_2.9
    ugfx_2.9/drivers/multiple/Win32
    Extended
    RomFiles
)


target_compile_definitions(${COMPONENT_NAME} PUBLIC "-DGDISP_SCREEN_WIDTH=240")
target_compile_definitions(${COMPONENT_NAME} PUBLIC "-DGDISP_SCREEN_HEIGHT=320")
# target_compile_definitions(${COMPONENT_NAME} PUBLIC "-DGFX_USE_OS_WIN32=GFXON")

target_link_libraries(${COMPONENT_NAME} gdi32 -static)
target_link_libraries(${COMPONENT_NAME} -mwindows -static)

