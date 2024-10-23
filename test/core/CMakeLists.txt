project(plutus-core-test)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Test)
find_package(Qt${QT_VERSION_MAJOR} 
	COMPONENTS
		Core
		Test
)

qt_add_executable(${PROJECT_NAME}
    UserTest.h UserTest.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	Qt6::Core
    Qt6::Test
	plutus-core
)

add_test(NAME Plutus.Core.UserClassTest COMMAND ${PROJECT_NAME})