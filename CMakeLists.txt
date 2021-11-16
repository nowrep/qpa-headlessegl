cmake_minimum_required(VERSION 3.1)

project(qpa-headlessegl VERSION 0.1.0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include(FeatureSummary)

option(USE_QT6 "Use Qt6" OFF)

if(USE_QT6)
set(QT6_MIN_VERSION "6.2.0")
find_package(Qt6 ${QT6_MIN_VERSION} REQUIRED COMPONENTS Core Gui)
else()
set(QT5_MIN_VERSION "5.15.0")
find_package(Qt5 ${QT5_MIN_VERSION} REQUIRED COMPONENTS Core Gui EglSupport FontDatabaseSupport EventDispatcherSupport)
endif()

find_package(EGL REQUIRED)

set(CMAKE_AUTOMOC ON)

add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
