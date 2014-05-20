find_package (Qt5Core REQUIRED)
get_target_property(QtCore_location Qt5::Core LOCATION)
find_package (Qt5Qml REQUIRED)
get_target_property(QtQml_location Qt5::Qml LOCATION)

include_directories("${PROJECT_SOURCE_DIR}/qtdeclarative-helper")

add_library(petn9models pet.cpp spritemodel.cpp ${PROJECT_SOURCE_DIR}/qtdeclarative-helper/declarativelist.cpp)
target_link_libraries(petn9models Qt5::Core)
target_link_libraries(petn9models Qt5::Qml)
