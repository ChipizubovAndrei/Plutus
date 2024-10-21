project(plutus-core)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} 
    COMPONENTS 
	    Core
)

file(GLOB core_SRC "*h" "*cpp")

add_library(${PROJECT_NAME} STATIC ${core_SRC})

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Core)