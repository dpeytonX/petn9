find_package (Qt5Core REQUIRED)
get_target_property(QtCore_location Qt5::Core LOCATION)

add_library(petn9models pet.cpp spritemodel.cpp)
target_link_libraries(petn9models Qt5::Core)
