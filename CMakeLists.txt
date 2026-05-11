cmake_minimum_required(VERSION 3.16)

project(graph)

################################################################################
# Source groups
################################################################################
set(comp
    "include/graph/EdgeStyle.h"
    "include/graph/NodeColor.h"
    "include/graph/NodePos.h"
    "include/graph/NodeRank.h"
)
source_group("comp" FILES ${comp})

set(obj
    "include/graph/Edge.h"
    "include/graph/Graph.h"
    "include/graph/Node.h"
    "source/Edge.cpp"
    "source/Graph.cpp"
    "source/Node.cpp"
)
source_group("obj" FILES ${obj})

set(tools
    "include/graph/GraphLayout.h"
    "include/graph/GraphTools.h"
    "source/GraphLayout.cpp"
    "source/GraphTools.cpp"
)
source_group("tools" FILES ${tools})

set(ALL_FILES
    ${comp}
    ${obj}
    ${tools}
)

################################################################################
# Target
################################################################################

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE external/ogdf/include)
if(TARGET objcomp)
    target_link_libraries(${PROJECT_NAME} PRIVATE objcomp)
else()
    target_include_directories(${PROJECT_NAME} PRIVATE external/objcomp/include)
endif()
if(TARGET sm)
    target_link_libraries(${PROJECT_NAME} PRIVATE sm)
else()
    target_include_directories(${PROJECT_NAME} PRIVATE external/sm)
endif()
if(TARGET guard)
    target_link_libraries(${PROJECT_NAME} PRIVATE guard)
else()
    target_include_directories(${PROJECT_NAME} PRIVATE external/guard/include)
endif()
