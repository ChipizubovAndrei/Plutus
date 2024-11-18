project(plutus-core-test)

if(BUILD_TESTING)
	find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
	find_package(Qt${QT_VERSION_MAJOR} 
		COMPONENTS
			Core
	)

	file(GLOB core_test_SRC "*h" "*cpp")

	add_executable(${PROJECT_NAME} ${core_test_SRC} )

	target_link_libraries(${PROJECT_NAME} PRIVATE
		GTest::gtest_main
		Qt::Core
		plutus-core
	)

	include(GoogleTest)

	gtest_discover_tests(${PROJECT_NAME})
endif()