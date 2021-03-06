﻿cmake_minimum_required (VERSION 3.14)

project (LodeRunner)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
    add_compile_options (/permissive-)
endif ()

add_executable (LodeRunner WIN32)

#==========================================================
add_subdirectory (include)
add_subdirectory (include/AbstractClases/)
add_subdirectory (include/Enemy/)
add_subdirectory (include/Player/)

add_subdirectory (include/States/)

add_subdirectory (include/States/EndGame/)

add_subdirectory (include/States/Game/)
add_subdirectory (include/States/Game/GameObject/)

add_subdirectory (include/States/Menues/)
add_subdirectory (include/States/Menues/MainMenu/)
add_subdirectory (include/States/Menues/Components/)

#==========================================================

add_subdirectory (src)
add_subdirectory (src/AbstractClases/)
add_subdirectory (src/Enemy/)
add_subdirectory (src/Player/)

add_subdirectory (src/States/)

add_subdirectory (src/States/EndGame/)

add_subdirectory (src/States/Game/)
add_subdirectory (src/States/Game/GameObject/)

add_subdirectory (src/States/Menues/)
add_subdirectory (src/States/Menues/MainMenu/)
add_subdirectory (src/States/Menues/Components/)

add_subdirectory (resources)

add_subdirectory (audio)


configure_file (C:/SFML/SFML-2.5.1/bin/openal32.dll ${CMAKE_BINARY_DIR} COPYONLY)

set (SFML_STATIC_LIBRARIES TRUE)
set (SFML_DIR "C:/SFML/SFML-2.5.1/lib/cmake/SFML")

find_package (SFML 2.5 COMPONENTS graphics REQUIRED)
find_package (SFML 2.5 COMPONENTS audio REQUIRED)

set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

target_link_libraries (LodeRunner sfml-graphics sfml-main)
target_link_libraries (LodeRunner sfml-audio sfml-main)