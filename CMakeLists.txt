cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


include(InstallRequiredSystemLibraries)

    if (MINGW)
       add_link_options(-static -static-libstdc++ -static-libgcc)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>)
    endif()

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)

  if(NOT BUILD_SHARED_LIBS)
        set(SFML_USE_STATIC_STD_LIBS ON CACHE BOOL "Link SFML with static standard libraries" FORCE)
  endif()

FetchContent_MakeAvailable(SFML)

FetchContent_MakeAvailable(SFML)
FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.91.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)
set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG v3.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(ImGui-SFML)


add_executable(main src/main.cpp "src/Vec2.cpp" "src/Vec2.h" "src/Components.h" "src/Components.cpp" "src/SimpleEntity.cpp" "src/SimpleEntity.h" "src/EntityManager.cpp" "src/EntityManager.h" "src/Game.cpp" "src/Game.h" "src/AssetManager.h" "src/AssetManager.cpp" "src/Action.cpp" "src/Action.h" "src/GameEngine.cpp" "src/GameEngine.h" "src/Scene.h" "src/Scene.cpp" "src/Scene_Menu.cpp"  "src/Scene_Play.cpp"  "src/UIElement.h" "src/UIElement.cpp" "src/UIManager.h" "src/UIManager.cpp" "src/TestUIElement.h" "src/TestUIElement.cpp" "src/Scene_Play.h" "src/Scene_Menu.h")
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics ImGui-SFML::ImGui-SFML)


add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:main>/assets"
)
