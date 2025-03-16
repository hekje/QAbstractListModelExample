cmake_minimum_required(VERSION 3.16)

project(QAbstractListModelExample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

add_executable(QAbstractListModelExample
    src/main.cpp
    src/Controller.cpp
    src/Controller.h
    src/MyObject.h
    src/QObjectListModel.h
)

qt_add_resources(RESOURCES resources.qrc)

target_link_libraries(QAbstractListModelExample PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

# Resources:
set(RESOURCE_FILES
    "qml/main.qml"
    "qml/ObjectDisplay.qml"
)

qt_add_resources(QAbstractListModelExample "QAbstractListModelExample" FILES
    ${RESOURCE_FILES}
)


