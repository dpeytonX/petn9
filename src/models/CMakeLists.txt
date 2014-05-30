find_package (Qt5Core REQUIRED)
get_target_property(QtCore_location Qt5::Core LOCATION)
find_package (Qt5Qml REQUIRED)
get_target_property(QtQml_location Qt5::Qml LOCATION)

include_directories("qtdeclarative-helper")

set (petn9models_SOURCES pet.cpp spritemodel.cpp qtdeclarative-helper/declarativelist.cpp)
set (petn9models_MOC_HEADERS pet.h spritemodel.h )
set (petn9models_HEADER ${petn9_MOC_HEADERS}
				qtdeclarative-helper/declarativelist.h 
				qtdeclarative-helper/declarativelist_global.h)
qt5_wrap_cpp(petn9models_MOC ${petn9models_MOC_HEADERS})

add_library(petn9models ${petn9models_SOURCES} ${petn9models_HEADER} ${petn9models_MOC})
target_link_libraries(petn9models Qt5::Core)
target_link_libraries(petn9models Qt5::Qml)
