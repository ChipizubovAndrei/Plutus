project(plutus-database)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Sql)

file(GLOB database_SRC "*h" "*cpp")

add_library(${PROJECT_NAME} STATIC ${database_SRC})

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Core
        plutus-core
)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt::Sql)
