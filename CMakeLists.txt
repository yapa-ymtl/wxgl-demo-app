cmake_minimum_required(VERSION 3.16)
project(wxgl-demo-app)

set(CMAKE_CXX_STANDARD 17)

set(wxWidgets_ROOT_DIR /opt/homebrew/lib/wx/)

find_package(wxWidgets REQUIRED COMPONENTS net core base gl)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()
add_executable(myapp 
    src/app.cpp
    src/mainframe.cpp
    src/canvas.cpp
    src/sidepanel.cpp
)
target_link_libraries(myapp ${wxWidgets_LIBRARIES})

# Copy assets to build directory
add_custom_command(TARGET myapp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:myapp>/../assets
)