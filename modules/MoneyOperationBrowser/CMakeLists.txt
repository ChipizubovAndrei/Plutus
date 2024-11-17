project(MoneyOperationBrowser)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Sql Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} 
    COMPONENTS 
		Sql
	    Core
		Widgets	
)

file(GLOB MoneyOperationBrowser_SRC "*h" "*cpp")

add_library(${PROJECT_NAME} STATIC ${MoneyOperationBrowser_SRC})

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE
	Qt::Core
	Qt::Widgets
	plutus-core
)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt::Sql)