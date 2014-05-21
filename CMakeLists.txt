project (petn9)

cmake_minimum_required (VERSION 2.8.11)
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

find_package (Qt5Core REQUIRED)
get_target_property(QtCore_location Qt5::Core LOCATION)
find_package (Qt5Gui REQUIRED)
get_target_property(QtGui_location Qt5::Gui LOCATION)
find_package (Qt5Qml REQUIRED)
get_target_property(QtQml_location Qt5::Qml LOCATION)
find_package (Qt5Quick REQUIRED)
get_target_property(QtQuick_location Qt5::Quick LOCATION)
find_package (Qt5Sql REQUIRED)
get_target_property(QtSql_location Qt5::Sql LOCATION)

set (petn9_VERSION_MAJOR 1)
set (petn9_VERSION_MINOR 1)
set (petn9_LOG_FORMAT "TRACE")

configure_file (
  "${PROJECT_SOURCE_DIR}/petn9.h.in"
  "${PROJECT_BINARY_DIR}/petn9.h"
  )
  
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/qtdeclarative-helper")
include_directories("${PROJECT_SOURCE_DIR}/models")

#sub directories
add_subdirectory (models)

set (petn9_SOURCES main.cpp manager.cpp databasemanager.cpp qtdeclarative-helper/declarativelist.cpp)
set (petn9_MOC_HEADERS manager.h databasemanager.h )
set (petn9_HEADER ${petn9_MOC_HEADERS} qtdeclarative-helper/declarativelist.h qtdeclarative-helper/declarativelist_global.h)
set (petn9_RESOURCES petn9.qrc images.qrc qml.qrc)
qt5_wrap_cpp(petn9_MOC ${petn9_MOC_HEADERS})
qt5_add_resources(petn9_RESOURCES_RCC ${petn9_RESOURCES})

add_executable (petn9 ${petn9_SOURCES} ${petn9_HEADER} ${petn9_RESOURCES_RCC} ${petn9_MOC})

#Linking Options
target_link_libraries (petn9 Qt5::Core)
target_link_libraries (petn9 Qt5::Gui)
target_link_libraries (petn9 Qt5::Qml)
target_link_libraries (petn9 Qt5::Quick)
target_link_libraries (petn9 Qt5::Sql)
target_link_libraries (petn9 petn9models)

install (TARGETS petn9 DESTINATION bin)
install (FILES ${petn9_HEADER} DESTINATION include)
