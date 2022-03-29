#include "Notebook.hpp"
#include "Direction.hpp"
#include <map>
#include <iostream>
#include <stdexcept>
using namespace std;
using namespace ariel;

Notebook::Notebook() {

}  
Notebook::~Notebook() {
    
}
void Notebook::write(int page, int row, int column, ariel::Direction dir, string text) {                
    if (page < 0 || row < 0 || column < 0) {
        throw std::runtime_error("invalid input");
    }
    if (notebook.find(page) == notebook.end()) {
        add_page(page);
    }
    for (size_t i = 0 ; i < text.length() ; i++) {
        if (max_char < text[i] || text[i] < min_char || text[i] == erase_char) {
            throw std::runtime_error("invalid character");
        }
    }
    if (dir == ariel::Direction::Vertical) {
        if (column >= row_size) {
            throw std::runtime_error("the text had exceeded the page's width");
        }
        for (int i = 0 ; i < text.length() ; i++) {    
            add_row(page, row + i);
            if (notebook[page][row + i][(size_t)(column)] != empty_char) {
                throw std::runtime_error("cant write over written text");
            }
        }
        for (int i = 0 ; i < text.length() ; i++) {
            notebook[page][row + i][(size_t)column] = text[(size_t)i];
        }
    }
    else if (dir == ariel::Direction::Horizontal) {
        if (column + (int)text.length() > row_size) {
            throw std::runtime_error("the text had exceeded the page's width");
        }
        add_row(page, row);
        for (size_t i = 0 ; i < text.length() ; i++) {
            if (notebook[page][row][(size_t)column + i] != empty_char) {
                throw std::runtime_error("cant write over written text");
            }
        }
        for (size_t i = 0 ; i < text.length() ; i++) {
            notebook[page][row][(size_t)column + i] = text[i];    
        }
    }    
}
string Notebook::read(int page, int row, int column, ariel::Direction dir, int length) {
    if (page < 0 || row < 0 || column < 0 || length < 0) {
        throw std::runtime_error("invalid input");
    }
    string ret;
    if (dir == ariel::Direction::Vertical) {
        if (column >= row_size) {
            throw std::runtime_error("the read had exceeded the page's width");
        }
        for (int i = 0 ; i < length ; i++) {
            add_row(page, row + i);
            ret.push_back(notebook[page][row + i][(size_t)column]);
        }
    }
    else if (dir == ariel::Direction::Horizontal) {
        if (column + length > row_size) {
            throw std::runtime_error("the read size had exceeded the page's width");
        }
        add_row(page, row);
        for (size_t i = 0 ; i < length ; i++) {
            ret.push_back(notebook[page][row][(size_t)column + i]);
        }
    }
    return ret;
}
void Notebook::erase(int page, int row, int column, ariel::Direction dir, int length) {
    if (page < 0 || row < 0 || column < 0 || length < 0) {
        throw std::runtime_error("invalid input");
    }
    if (notebook.find(page) == notebook.end()) {
        add_page(page);
    }
    if (dir == ariel::Direction::Vertical) {
        if (column >= row_size) {
            throw std::runtime_error("the erase area had exceeded the page's width");
        }
        for (int i = 0 ; i < length ; i++) {
            add_row(page, row + i);
            notebook[page][row + i][(size_t)column] = erase_char;
        }
    }
    else if (dir == ariel::Direction::Horizontal) {
        if (column + length > row_size) {
            throw std::runtime_error("the erase area had exceeded the page's width");
        }
        add_row(page, row);
        for (size_t i = 0 ; i < length ; i++) {
            notebook[page][row][(size_t)column + i] = erase_char;
        }
    }    
}
void Notebook::show(int page) {
    if (page < 0) {
        throw std::runtime_error("invalid input");
    }
    for (auto it = notebook[page].begin(); it != notebook[page].end(); it++) {
        std::cout << it->second << ' ' << it->first << endl;
    }
}
void Notebook::add_row(int page_number, int row_number) {
    if (notebook.find(page_number) == notebook.end()) {
        add_page(page_number);
    }    
    notebook[page_number].insert(pair<int, string>(row_number, empty_row));
}
void Notebook::add_page(int page_number) {
    if (notebook.find(page_number) == notebook.end()) {
        notebook.insert(pair<int, map<int, string>>(page_number, {}));
    }
}


