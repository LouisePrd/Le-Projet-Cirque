cmake_minimum_required(VERSION 3.20)
project(SimpleCpp)

# Déclare l'exécutable principal
add_executable(${PROJECT_NAME})

# Utilise C++20
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Répertoire de sortie pour les exécutables
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# Désactive les extensions spécifiques du compilateur
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF)

# Inclut tous les fichiers sources du projet
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS src/*)
target_sources(${PROJECT_NAME} PRIVATE ${MY_SOURCES})

# Inclut les headers du dossier src/
target_include_directories(${PROJECT_NAME} PRIVATE src)

# === Dépendances ===

# quick-imgui
add_subdirectory(lib/quick_imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE quick_imgui::quick_imgui)

# GLM
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/glm-master)
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/lib/glm-master/glm/glm.hpp")
    message(FATAL_ERROR "GLM not found! Did you download it into lib/glm-master?")
endif()

# STB
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/stb)

