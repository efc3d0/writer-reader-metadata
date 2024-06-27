cmake_minimum_required(VERSION 3.5.0)
project(writer-reader-metadata)

set(CMAKE_CXX_STANDARD 17)

# Найти и подключить необходимые пакеты
find_package(ZLIB)
find_package(TagLib 2.0.0 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

# Указание пути к файлам ImGui
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/imgui)

# Добавление исходных файлов ImGui
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/imgui_impl_opengl2.cpp
)

# Создание исполняемого файла
add_executable(wreader main.cpp handler.cpp ${IMGUI_SOURCES})

# Включение директорий для заголовочных файлов
target_include_directories(wreader PRIVATE ${IMGUI_DIR} ${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})

# Линковка библиотек
target_link_libraries(wreader TagLib::tag glfw OpenGL::GL)
