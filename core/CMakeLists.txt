project(plutus-core)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} 
    COMPONENTS 
	    Core
)

file(GLOB core_SRC "include/*h" "src/*cpp")

add_library(${PROJECT_NAME} STATIC ${core_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Core)