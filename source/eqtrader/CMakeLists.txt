cmake_minimum_required(VERSION 2.8.11)

project(eqtrader)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed. 	
set(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
 
# Find the QtWidgets library
FIND_PACKAGE(Qt5Core)
FIND_PACKAGE(Qt5Gui)
FIND_PACKAGE(Qt5Widgets)


# Add the include directories for the Qt 5 Widgets module to
# the compile lines.
include_directories(${Qt5Widgets_INCLUDE_DIRS})

QT5_WRAP_CPP(quant_hdr1_moc clientmq.h)
QT5_WRAP_CPP(quant_hdr_moc mainwindow.h )
QT5_ADD_RESOURCES(quant_RCC_SRCS qdarkstyle/style.qrc)
QT5_WRAP_UI(quant_UIS mainwindow.ui)

ADD_EXECUTABLE(eqtrader main.cpp mainwindow.cpp clientmq.cpp ctickevent.cpp clientmq.h  mainwindow.h enums.h ctickevent.h ${quant_RCC_SRCS} ${quant_UIS})
message("main.cpp mainwindow.cpp clientmq.cpp ctickevent.cpp ${quant_hdr_moc}  ${quant_hdr1_moc} enums.h ctickevent.h ${quant_RCC_SRCS} ${quant_UIS}")
#TARGET_LINK_LIBRARIES(eqtrader ${QT_LIBRARIES})

# Use the Widgets module from Qt 5.
target_link_libraries(eqtrader nanomsg)
target_link_libraries(eqtrader yaml-cpp)
target_link_libraries(eqtrader Qt5::Widgets)

