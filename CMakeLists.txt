cmake_minimum_required(VERSION 3.5)

project(FluidSimulation)

file(GLOB HEADERS
	"${PROJECT_SOURCE_DIR}/*.h")
file(GLOB SOURCES
	"${PROJECT_SOURCE_DIR}/*.cpp")

set(EXECUTABLE_OUTPUT_PATH "bin")
add_executable(fl_sim ${SOURCES} ${HEADERS})
set_target_properties(
	fl_sim PROPERTIES
	CXX_STANDART 17
	CXX_STANDART_REQUIRED ON
)


#find and link SFML
find_package(SFML 2.5 REQUIRED COMPONENTS
			graphics window system audio)
target_link_libraries(fl_sim sfml-graphics)

#copy dynamic libraries into work directory
if (WIN32)
	string(REPLACE "lib\\cmake\\SFML" "bin" SFML_BIN_DIR ${SFML_DIR})
	add_custom_command(TARGET fl_sim POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy_directory
				${SFML_BIN_DIR}
				$<TARGET_FILE_DIR:fl_sim>)
endif()


#copy font into work directory
add_custom_command(TARGET fl_sim POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy
			${CMAKE_SOURCE_DIR}/RobotoSlabRegular.ttf
			$<TARGET_FILE_DIR:fl_sim>)
