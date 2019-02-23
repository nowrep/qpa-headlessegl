cmake_minimum_required(VERSION 3.1)

project(qpa-headlessegl VERSION 0.1.0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH} )

include(FeatureSummary)
include(GenerateExportHeader)
include(CMakePackageConfigHelpers)
include(QueryQmake)

set(QT_MIN_VERSION "5.12.0")
find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS Core Gui)
find_package(Qt5FontDatabaseSupport REQUIRED)
find_package(Qt5EventDispatcherSupport REQUIRED)
find_package(Qt5EglSupport REQUIRED)

set(CMAKE_AUTOMOC ON)

add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
