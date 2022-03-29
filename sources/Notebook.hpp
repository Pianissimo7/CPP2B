#include "Direction.hpp"
#include <iostream>
#include <string>
#include <map>

using namespace std;

namespace ariel {
    class Notebook {
        public:
            Notebook();
            ~Notebook();
            void write(int page, int row, int column, ariel::Direction, string text);
            string read(int page, int row, int column, ariel::Direction, int length);
            void erase(int page, int row, int column, ariel::Direction, int length);
            void show(int page);
            void add_row(int page_number, int row_number);
            void add_page(int page_number);
        private:
            const char empty_char = '_';
            const char erase_char = '~';
            const int min_char = 32;
            const int max_char = 125;
            const int row_size = 100;
            const string empty_row = "____________________________________________________________________________________________________";
            map<int, map<int, string>> notebook;
    };
}