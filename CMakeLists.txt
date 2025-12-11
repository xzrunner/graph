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

target_include_directories(${PROJECT_NAME} PRIVATE include external/objcomp/include external/sm external/guard/include external/ogdf/include)
