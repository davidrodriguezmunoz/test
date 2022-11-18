# Determine source directory
set(TEST_SRCDIR "${CMAKE_CURRENT_SOURCE_DIR}/src/")
# Arguments for test programs
set(TCINPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Inputs/CHANNEL_2-TELECOMMAND-2022-03-14-121208_Analysis.txt" CACHE FILEPATH "Input File for TCTest")
set(TMINPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Inputs/CHANNEL_2-TELEMETRY-2022-03-14-121208_Analysis.txt" CACHE FILEPATH "Input File for TCTest")
set(PTD_INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Inputs/CHANNEL_2-SCIENTIFIC-2022-03-14-121208_Analysis.txt" CACHE FILEPATH "Input File for TCTest")


# Function to prepare generic test
function (do_test target)

	add_executable(${target} "${TEST_SRCDIR}/${target}.c")
	target_link_libraries(${target} PRIVATE ${PROJECT_NAME} pthread)
	add_test(NAME ${target} COMMAND ${target} ${ARGN})
	# set_tests_properties(${target} PROPERTIES
		# FAIL_REGULAR_EXPRESSION ": FAIL")
	
endfunction(do_test)

# Add tests
do_test(TC_test ${TCINPUT_FILE} )
do_test(TM_test ${TMINPUT_FILE} )
do_test(PTD_test ${TMINPUT_FILE} ${PTD_INPUT_FILE} )
