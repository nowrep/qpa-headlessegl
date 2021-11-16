cmake_minimum_required(VERSION 3.1)

project(qpa-headlessegl VERSION 0.1.0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include(FeatureSummary)

set(QT_MIN_VERSION "5.15.0")
find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS Core Gui EglSupport FontDatabaseSupport EventDispatcherSupport)
find_package(EGL REQUIRED)

set(CMAKE_AUTOMOC ON)

add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
