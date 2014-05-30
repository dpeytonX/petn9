project (petn9)

cmake_minimum_required (VERSION 2.8.11)
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

#Qt requirements
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
set (petn9_VERSION_MINOR 2)
set (petn9_LOG_FORMAT "TRACE")
set (petn9_RANDOM_WORLDS 1)
set (petn9_NEW_DB 0)
set (petn9_ALLOW_JP 1)

set (PROJECT_SOURCE_DIR "src")
set (PROJECT_RESOURCE_DIR "resources")

configure_file (
  "${PROJECT_SOURCE_DIR}/petn9.h.in"
  "${PROJECT_BINARY_DIR}/petn9.h"
  )
  
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/models")
include_directories("${PROJECT_SOURCE_DIR}/models/qtdeclarative-helper")

#sub directories
add_subdirectory ("${PROJECT_SOURCE_DIR}/models")

set (petn9_SOURCES "${PROJECT_SOURCE_DIR}/main.cpp"
			"${PROJECT_SOURCE_DIR}/manager.cpp"
			"${PROJECT_SOURCE_DIR}/databasemanager.cpp"
			"${PROJECT_SOURCE_DIR}/models/qtdeclarative-helper/declarativelist.cpp")
set (petn9_MOC_HEADERS "${PROJECT_SOURCE_DIR}/manager.h"
			"${PROJECT_SOURCE_DIR}/databasemanager.h" )
set (petn9_HEADER ${petn9_MOC_HEADERS}
			"${PROJECT_BINARY_DIR}/petn9.h"
			"${PROJECT_SOURCE_DIR}/models/qtdeclarative-helper/declarativelist.h"
			"${PROJECT_SOURCE_DIR}/models/qtdeclarative-helper/declarativelist_global.h")
set (petn9_RESOURCES "${PROJECT_RESOURCE_DIR}/petn9.qrc"
			"${PROJECT_RESOURCE_DIR}/icons.qrc"
			"${PROJECT_RESOURCE_DIR}/images.qrc"
			"${PROJECT_RESOURCE_DIR}/qml.qrc"
			"${PROJECT_RESOURCE_DIR}/translations.qrc")
set (petn9_DESKTOP "${PROJECT_RESOURCE_DIR}/petn9.desktop")
set (petn9_ICONS "${PROJECT_RESOURCE_DIR}/petn9.svg")

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
install (FILES ${petn9_HEADER} DESTINATION include/petn9)
install (FILES ${petn9_DESKTOP} DESTINATION share/applications)
install (FILES ${petn9_ICONS} DESTINATION share/icons/hicolor/scalable/apps)
