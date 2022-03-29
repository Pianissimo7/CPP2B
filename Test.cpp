/*
 * An example of how to write unit tests.
 * Use this as a basis to build a more complete Test.cpp file.
 * 
 * IMPORTANT: Please write more tests - the tests here are only for example and are not complete.
 *
 * AUTHORS: Idan Philosoph
 * 
 * Date: 2021-02
 */

#include "doctest.h"
#include "Notebook.hpp"
using namespace ariel;

#include <string>
#include <algorithm>
using namespace std;

/*
 * Returns the input string without the whitespace characters: space, newline and tab.
 * Requires std=c++2a.
 */
string nospaces(string input) {
    std::erase(input, ' ');
    std::erase(input, '\t');
    std::erase(input, '\n');
    std::erase(input, '\r');
    return input;
}


TEST_CASE("attempting to overwrite text") {
    Notebook n;
    n.write(100, 100, 50, Direction::Horizontal, "1234");
    CHECK_THROWS(n.write(100, 100, 50, Direction::Horizontal, "1234"));
    CHECK_THROWS(n.write(100, 100, 50, Direction::Horizontal, "123"));
    CHECK_THROWS(n.write(100, 100, 50, Direction::Vertical, "123456"));
    CHECK_THROWS(n.write(100, 99, 51, Direction::Vertical, "123456"));
    n.erase(100, 99, 51, Direction::Vertical, 3);
    CHECK_THROWS(n.write(100, 99, 51, Direction::Vertical, "123456"));
}
TEST_CASE("multi page writing") {
    Notebook n;
    n.write(86, 100, 10, Direction::Horizontal, "abc");
    n.write(121, 100, 45, Direction::Horizontal, "def");
    n.write(238, 100, 78, Direction::Horizontal, "ghi");
    n.erase(566, 100, 90, Direction::Horizontal, 3);
    CHECK(n.read(86, 100, 10, Direction::Horizontal, 3) == "abc");
    CHECK(n.read(121, 100, 45, Direction::Horizontal, 3) == "def");
    CHECK(n.read(238, 100, 78, Direction::Horizontal, 3) == "ghi");
    CHECK(n.read(566, 100, 90, Direction::Horizontal, 3) == "~~~");

}
TEST_CASE("allowed areas to write over twice") {
    Notebook n;
    n.write(100, 100, 50, Direction::Horizontal, "12_34");
    n.write(100, 98, 52, Direction::Vertical, "ab_cd");
    CHECK(n.read(100, 98, 52, Direction::Vertical,5) == "ab_cd");
    CHECK(n.read(100, 100, 50, Direction::Horizontal,5) == "12_34");

    n.erase(100, 100, 50, Direction::Horizontal, 5);
    CHECK(n.read(100, 100, 50,Direction::Horizontal, 5) == "~~~~~");
    n.erase(100, 100, 50, Direction::Horizontal, 5);
    CHECK_THROWS(n.write(100, 100, 50, Direction::Horizontal, "~~~~~"));

    n.erase(100, 98, 52, Direction::Vertical, 5);
    CHECK(n.read(100,98, 52, Direction::Vertical,5) == "~~~~~");
    n.erase(100, 98, 52, Direction::Vertical, 5);
    CHECK_THROWS(n.write(100, 98,52, Direction::Vertical, "~~~~~"));
}
TEST_CASE("out of bounds input") {
    Notebook n;
    CHECK_THROWS(n.write(100, 100, 98, Direction::Horizontal, "123"));
    CHECK_THROWS(n.read(100, 100, 98, Direction::Horizontal, 4));
    CHECK_THROWS(n.erase(100, 100, 98, Direction::Horizontal, 4));
    CHECK(n.read(100, 100, 98, Direction::Horizontal, 2) == "__");
}
TEST_CASE("invalid characters") {
    Notebook n;
    CHECK_THROWS(n.write(100, 100,50, Direction::Horizontal, "\t"));
    CHECK_THROWS(n.write(100, 101,50, Direction::Horizontal, "\n"));
    CHECK_THROWS(n.write(100, 102,50, Direction::Horizontal, "\r"));
    CHECK_THROWS(n.write(100, 103,49, Direction::Horizontal, "4\t2346"));
    CHECK_THROWS(n.write(100, 104,50, Direction::Horizontal, "~"));
    CHECK(n.read(100, 100, 50, Direction::Vertical, 5)=="_____");
    CHECK(n.read(100, 103, 49, Direction::Horizontal, 6)=="______");
}
TEST_CASE("read without writing") {
    Notebook n;
    CHECK(n.read(103, 100, 50, Direction::Horizontal, 5)=="_____");
}