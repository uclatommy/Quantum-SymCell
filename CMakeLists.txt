cmake_minimum_required(VERSION 3.6)
project(SymCell)
set(CMAKE_INSTALL_PREFIX /Applications/Quantum.app/contents/resources/.kivy)
set(CMAKE_CXX_COMPILER /usr/local/llvm/bin/clang++)
set(CMAKE_CC_COMPILER /usr/local/llvm/bin/clang)
set(PYTHON_INCLUDE_DIRS /Applications/Quantum.app/Contents/Frameworks/python/3.5.2/include/python3.5m)
set(PYTHON_LIBRARIES /Applications/Quantum.app/Contents/Frameworks/python/3.5.2/lib)

add_definitions(-std=c++1y)

# Find Python and set PYTHON_INCLUDE_DIRS
# find_package( PythonLibs 3.5 REQUIRED )
find_package(symengine)

include_directories(
    .
    ${CMAKE_INSTALL_PREFIX}/include
    ${PYTHON_INCLUDE_DIRS}
    /usr/local/gtest/include
)

LINK_DIRECTORIES(
    ${PYTHON_LIBRARIES}
    /usr/local/gtest/lib
    /usr/local/lib
)

add_library(${PROJECT_NAME} SHARED
    SymCell.cpp
    SymCell/Add.cpp
    SymCell/Basic.cpp
    SymCell/Compare.cpp
    SymCell/Div.cpp
    SymCell/Expand.cpp
    SymCell/Mul.cpp
    SymCell/Pow.cpp
    SymCell/Sub.cpp
    SymCell/Subs.cpp
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
    boost_python3-mt
    python3.5m
    QuantumCell
    gtest
    symengine
)

install(TARGETS ${PROJECT_NAME} DESTINATION extensions/plugins)
install(FILES SymCell.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})
install(FILES SymCell_Config.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})
install(FILES SymCell/Add.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})
install(FILES SymCell/Basic.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})
install(FILES SymCell/Compare.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})
install(FILES SymCell/Div.cpp DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})
install(FILES SymCell/Expand.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})
install(FILES SymCell/Mul.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})
install(FILES SymCell/Pow.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})
install(FILES SymCell/Sub.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})
install(FILES SymCell/Subs.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ../post-build.sh . lib${PROJECT_NAME}.dylib)