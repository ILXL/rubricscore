# rubricscore: generate a grade from googletest results

This program is "glue code" that bridges the gap between googletest unit tests
and autograding of class assignments.

To use this, an instructor
- Creates starter code using GitHub Classroom.
- Writes googletest unit tests to check the functionality of student code.
  Each testsuite named in the unit test source will correspond 1:1 to a
  rubric item. When all tests in that suite pass, a submission gets 100% of the
  points for that item; when tests fail, a submission gets 0% of the points for
  that item. To give partial credit, write multiple test suites for a feature.
- Creates "rubric" which is a small JSON file that says how many points each
  testsuite is worth.
- Adjust your `Makefile` to run the unit test program with XML output; then
  run this `rubricscore` program to calculate and print a grade.

The `rubricscore` program takes an instructor-written rubric JSON file, and an
XML file created automatically by googletest, awards points for the passed
testsuites, and pretty-prints the grade breakdown and total.

```
rubricscore usage:

    rubricscore <RUBRIC-JSON-PATH> <GTEST-XML-PATH>
```

There is a small sample, complete with starter code, unit test code,
`Makefile`, and `rubric.json` in the `example` directory.

Example output:

```
~/rubricscore/example$ make
g++ -std=c++17 -Wall -O -g -lpthread -lgtest_main -lgtest  -lpthread product_test.cpp -o product_test
# delete stale test results from previous runs
rm -f product_test.xml
# || true allows make to continue the build even if some tests fail
./product_test --gtest_output=xml:product_test.xml || true
Running main() from /build/googletest-Njo5SR/googletest-1.8.1/googletest/src/gtest_main.cc
[==========] Running 3 tests from 3 test cases.
[----------] Global test environment set-up.
[----------] 1 test from ProductPositive
[ RUN      ] ProductPositive.ProductPositive
[       OK ] ProductPositive.ProductPositive (0 ms)
[----------] 1 test from ProductPositive (1 ms total)

[----------] 1 test from ProductZero
[ RUN      ] ProductZero.ProductZero
[       OK ] ProductZero.ProductZero (0 ms)
[----------] 1 test from ProductZero (0 ms total)

[----------] 1 test from ProductNegative
[ RUN      ] ProductNegative.ProductNegative
product_test.cpp:28: Failure
Expected equality of these values:
  -12
  product(-3, 4)
    Which is: 12
product_test.cpp:29: Failure
Expected equality of these values:
  -25
  product(5, -5)
    Which is: 25
[  FAILED  ] ProductNegative.ProductNegative (1 ms)
[----------] 1 test from ProductNegative (2 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 3 test cases ran. (7 ms total)
[  PASSED  ] 2 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] ProductNegative.ProductNegative

 1 FAILED TEST
../rubricscore rubric.json product_test.xml
===============================================================================
RUBRIC SCORE
===============================================================================
ProductPositive       3 /    3
ProductZero           3 /    3
ProductNegative       0 /    3
===============================================================================
TOTAL =    6 /    9
===============================================================================

~/rubricscore/example$ 
```
