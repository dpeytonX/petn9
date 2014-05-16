#CMAKE_PATH_PREFIX=/opt/Qt/5.2.1/gcc
project (petn9)

cmake_minimum_required (VERSION 2.8.11)
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

#find QT libs
find_package (Qt5Core REQUIRED)
get_target_property(QtCore_location Qt5::Core LOCATION)
find_package (Qt5Gui REQUIRED)
get_target_property(QtGui_location Qt5::Gui LOCATION)
find_package (Qt5Qml REQUIRED)
get_target_property(QtQml_location Qt5::Qml LOCATION)
#qt5_use_package (petn9 Core Gui Qml)

set (petn9_VERSION_MAJOR 1)
set (petn9_VERSION_MINOR 1)
set (petn9_LOG_FORMAT "TRACE")

configure_file (
  "${PROJECT_SOURCE_DIR}/petn9.h.in"
  "${PROJECT_BINARY_DIR}/petn9.h"
  )
  
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

set (petn9_SOURCES converter.cpp main.cpp)
set (petn9_HEADER converter.h)
set (petn9_MOC_HEADERS converter.h)
set (petn9_RESOURCES qml.qrc)
qt5_wrap_cpp(petn9_MOC ${petn9_MOC_HEADERS})
qt5_add_resources(petn9_RESOURCES_RCC ${petn9_RESOURCES})

add_executable (petn9 ${petn9_SOURCES} ${petn9_HEADER} ${petn9_RESOURCES_RCC} ${petn9_MOC})
target_link_libraries (petn9 Qt5::Core)
target_link_libraries (petn9 Qt5::Gui)
target_link_libraries (petn9 Qt5::Qml)

install (TARGETS petn9 DESTINATION bin)
install (FILES ${petn9_HEADER} DESTINATION include)
