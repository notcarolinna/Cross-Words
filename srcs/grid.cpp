#include "grid.h"
#include "attribute.h"
#include <cassert>
#include <fstream>
#include <algorithm>

Grid::Grid() {
    name = "UNTITLED";
}

Grid::Grid(std::string n) {
    name = n;
}

int Grid::getRows() const { return rows_.size(); }

int Grid::getCols() const {
    if (rows_.empty()) {
        return 0;
    }
    else {
        return rows_[0].size();
    }
}

int Grid::getMaxSize() const { return std::max(getRows(), getCols()); }

char Grid::getCell(const Point& p) const {
    assert(isInside(p));
    return rows_[p.row][p.col];
}

void Grid::setCell(const Point& p, char c) {
    assert(isInside(p));
    rows_[p.row][p.col] = c;
}

bool Grid::isBlock(const Point& p) const {
    return getCell(p) == '.';
}

bool Grid::isSpace(const Point& p) const {
    return getCell(p) == '?';
}

bool Grid::isLetter(const Point& p) const {
    char c = getCell(p);
    return c >= 'A' && c <= 'Z';
}

bool Grid::isInside(const Point& p) const {
    return (p.row >= 0 && p.row < getRows() && p.col >= 0 && p.col < getCols());
}

std::string Grid::getString(const Interval& s, Attribute& attribute) const {
    int length = s.length;
    std::string temp(length, ' '); // Inicializa a string com o tamanho necessário
    for (int i = 0; i < length; i++) {
        Point p = s.getPoint(i);
        char c = getCell(p);
        if (c == '?') {
            attribute.setHasSpaces(true);
        } else if (c >= 'A' && c <= 'Z') {
            attribute.setHasLetters(true);
        }
        temp[i] = c;
    }
    return temp;
}

void Grid::writeString(const Interval& s, const std::string& t) {
    int length = s.length;
    assert(t.length() == length);
    for (int i = 0; i < length; i++) {
        Point p = s.getPoint(i);
        setCell(p, t[i]);
    }
}

bool Grid::nextPoint(Point& p, bool vertical) {
    if (vertical) {
        p.row++;
        if (p.row >= getRows()) {
            p.row = 0;
            p.col++;
        }
    }
    else {
        p.col++;
        if (p.col >= getCols()) {
            p.col = 0;
            p.row++;
        }
    }
    return isInside(p);
}

bool Grid::nextPointStopOnWrap(Point& p, bool vertical) {
    bool wrap = false;
    if (vertical) {
        p.row++;
        if (p.row >= getRows()) {
            p.row = 0;
            p.col++;
            wrap = true;
        }
    }
    else {
        p.col++;
        if (p.col >= getCols()) {
            p.col = 0;
            p.row++;
            wrap = true;
        }
    }
    return !wrap;
}

void Grid::fillIntervals(bool vertical) {
    Point p;
    while(isInside(p)) {
        while (isInside(p) && isBlock(p)) {
            nextPoint(p, vertical);
        }
        if (!isInside(p)) return;
        Point startPoint = p;

        int length = 0;
        bool continueLoop = false;
        do {
            continueLoop = nextPointStopOnWrap(p, vertical);
            length++;
        } while (continueLoop && !isBlock(p));
        intervals.push_back(Interval(startPoint, length, vertical));
    }
}

void Grid::fillIntervals() {
    assert(intervals.empty());
    fillIntervals(false);
    fillIntervals(true);
}

void Grid::loadFromFile(std::string fileName) {
    std::ifstream file;
    file.open(fileName);
    assert(file.is_open());
    while (!file.eof()) {
        std::string line;
        std::getline(file, line);
        if (!line.empty()) {
            int length = line.length();
            if (line[length-1] == '\r') {
                line = line.substr(0, length-1);
            }
            rows_.push_back(line);
        }
    }
}

void Grid::verify() const {
    int rows = rows_.size();
    int cols = rows_[0].size();
    for (int i = 0; i < rows_.size(); i++) {
        assert(rows_[i].size() == cols);
    }
}

void Grid::print() const {
    std::cout << "Grid: " << name
         << " (rows=" << getRows()
         << ", cols=" << getCols() << ")"
         << " maxSize=" << getMaxSize() << std::endl;
    for (int i = 0; i < rows_.size(); i++) {
        std::string s = rows_[i];
        std::cout << s << "  (" << s.length() << ")" << std::endl;
    }
}

void Grid::printIntervals() const {
    std::cout << "Intervals:" << std::endl;
    for (const Interval& s : intervals) {
        Attribute attribute;
        std::cout << "  " << s << " " << getString(s, attribute) << std::endl;
    }
}