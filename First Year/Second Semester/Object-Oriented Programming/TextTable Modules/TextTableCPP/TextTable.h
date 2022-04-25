//
// Created by Emanuel on 22.03.2021.
//

#ifndef TEXTTABLE_H
#define TEXTTABLE_H

#include <vector>
#include <string>
#include <cstdarg>

class TextTable {
private:
    const int PADDING = 5, MIN_PADDING = 2;

    std::vector<std::string> rows;
    std::vector<size_t> columns_size;
    int rows_no, columns_no;
    bool header;

    std::string buildRowDelimitator(const std::string& delimitator) const;
    int getPartialWidth(int columns) const;
public:
    explicit TextTable(size_t columns) : columns_no(columns), rows_no(0), header(false) {}

    int addHeader(size_t argc, ...);
    int addRow(size_t argc, ...);
    void resize(size_t column, size_t size);

    std::string getCellData(int row, int column);
    size_t getWidth() const;

    friend std::ostream& operator<< (std::ostream& os, const TextTable& table);
};

#endif
