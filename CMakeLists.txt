cmake_minimum_required(VERSION 4.0.2)

# disable standard decaying and disable extensions
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(advent VERSION 0.0.1 LANGUAGES CXX)

# enable sanitizers for all targets
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

# Common compiler options
add_library(flags INTERFACE)
target_compile_features(flags INTERFACE cxx_std_23)
target_compile_options(flags INTERFACE -Wall -Wextra -Wpedantic -Wunused -Wconversion -Wsign-conversion)

# Creates a target for specific solution and copies input if not already done
function(add_solution DAY PART)
	message(STATUS "Adding solution for ${DAY}/${PART}")
	set(COPY_TARGET ${DAY}_copy_input)
	set(SOLUTION_TARGET ${DAY}_${PART})

	if (NOT TARGET ${COPY_TARGET})
		add_custom_target(${COPY_TARGET} ALL
			${CMAKE_COMMAND} -E copy_if_different
			${CMAKE_SOURCE_DIR}/${DAY}/input.txt
			${CMAKE_BINARY_DIR}/${DAY}/input.txt
			COMMENT "copying input for ${DAY}"
		)
	endif ()

	add_executable(${SOLUTION_TARGET} ${DAY}/${PART}.cpp)
	set_target_properties(${SOLUTION_TARGET} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${DAY}"
	)
	target_link_libraries(${SOLUTION_TARGET} PRIVATE flags)
	add_dependencies(${SOLUTION_TARGET} ${COPY_TARGET})
endfunction()

# Source discovery
file(GLOB DAYS
	RELATIVE ${CMAKE_SOURCE_DIR}
	"${CMAKE_SOURCE_DIR}/day_*"
)
foreach (DAY ${DAYS})
	file(GLOB PARTS
		LIST_DIRECTORIES false
		RELATIVE "${CMAKE_SOURCE_DIR}/${DAY}"
		"${CMAKE_SOURCE_DIR}/${DAY}/part_*.cpp"
	)
	foreach (PART ${PARTS})
		cmake_path(GET PART STEM PART_NAME)
		add_solution(${DAY} ${PART_NAME})
	endforeach ()
endforeach ()
