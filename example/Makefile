
GPP_FLAGS = -std=c++17 -Wall -O -g
GTEST_FLAGS = -lpthread -lgtest_main -lgtest  -lpthread
RUBRICSCORE = ../rubricscore
RUBRIC_JSON = rubric.json

MODULE = product
MODULE_HPP = ${MODULE}.hpp
TEST_CPP = ${MODULE}_test.cpp
TEST_EXECUTABLE = ${MODULE}_test
TEST_XML = ${MODULE}_test.xml

grade: ${RUBRICSCORE} ${TEST_EXECUTABLE}
	# delete stale test results from previous runs
	rm -f ${TEST_XML}
	# || true allows make to continue the build even if some tests fail
	./${TEST_EXECUTABLE} --gtest_output=xml:${TEST_XML} || true
	${RUBRICSCORE} ${RUBRIC_JSON} ${TEST_XML}

${TEST_EXECUTABLE}: libraries ${MODULE_HPP} ${TEST_CPP}
	g++ ${GPP_FLAGS} ${GTEST_FLAGS} ${TEST_CPP} -o ${TEST_EXECUTABLE}

libraries: /usr/lib/libgtest.a

/usr/lib/libgtest.a:
	@echo -e "google test library not installed\n"
	@echo -e "Installing libgtest-dev. Please provide the password when asked\n"
	@sudo apt-get -y install libgtest-dev cmake
	@sudo apt-get install cmake # install cmake
	@echo -e "\nConfiguring libgtest-dev\n"
	@cd /usr/src/gtest; sudo cmake CMakeLists.txt; sudo make; sudo cp *.a /usr/lib
	@echo -e "Finished installing google test library\n"

clean:
		rm -f ${TEST_EXECUTABLE} ${TEST_XML}
