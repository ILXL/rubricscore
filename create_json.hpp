
///////////////////////////////////////////////////////////////////////////////
// create_json.hpp
//
// Creates JSON file for unit tests output
//
// Author: Namanh Tran (namanhtran@csu.fullerton.edu)
// Last Modified: Apirl 1, 2020
///////////////////////////////////////////////////////////////////////////////

#include <boost/property_tree/ptree.hpp>

using boost::property_tree::ptree;

// Creates JSON file for unit test outputs
class UnitTestJSON {
    private:
        ptree root;
        ptree tests;
    
    public:
        // Add a test case to the JSON file
        void addTest(std::string testName, int result, int max);

        // Add the final total and max possiable points to the JSON file
        void addFinalResult(int result, int max);

        // Generate the JSON file
        void generateJSON();
};

// Add a test case to the JSON file
void UnitTestJSON::addTest(std::string testName, int result, int max) {
    ptree testInfo;
    testInfo.put("testName", testName);
    testInfo.put("testResults", result);
    testInfo.put("testMaxPoints", max);

    this->tests.push_back(std::make_pair("", testInfo));
}

// Add the final total and max possiable points to the JSON file
void UnitTestJSON::addFinalResult(int result, int max) {
    this->root.put("finalTotal", result);
    this->root.put("maxPossiable", max);
}

// Generate the JSON file
void UnitTestJSON::generateJSON() {
    // Make sure we are not creating a empty JSON file
    assert(!this->root.empty() && !this->tests.empty());

    // Add the array of tests to the JSON file
    root.add_child("tests", this->tests);

    // Create the JSON file
    write_json("resultOutput.json", root);
}