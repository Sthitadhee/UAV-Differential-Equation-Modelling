cmake_minimum_required(VERSION 3.0)
project(MyProject)

# set(SFML_DIR "/usr/local/Cellar/sfml/2.5.1_2/lib/cmake/SFML")
# set(SFML_DIR "/opt/homebrew/Cellar/SFML/2.5.1_2/include/**")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# file(GLOB_RECURSE SOURCE_FILES helper/*.cpp player/*.cpp)

include_directories(helper, player, variables)

add_executable(MyProject main.cpp helper/helper.cpp player/player.cpp)
# add_executable(MyProject main.cpp ${SOURCE_FILES})

target_link_libraries(MyProject sfml-graphics sfml-audio)

include_directories(/usr/local/Cellar/sfml/2.5.1_2/include)