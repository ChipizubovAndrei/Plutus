project(plutus-kernel)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Widgets
)

file(GLOB kernel_SRC "*h" "*cpp")

qt_add_executable(${PROJECT_NAME} ${kernel_SRC})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        Qt::Widgets
        plutus-core
        MoneyOperationBrowser
)

install(DIRECTORY ../storage DESTINATION CMAKE_BINARY_DIR)
