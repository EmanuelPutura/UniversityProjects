//
// Created by Emanuel on 21.03.2021.
//

#include "TextTable.h"

#include <iostream>
#include <string.h>

std::ostream& operator<<(std::ostream& os, const TextTable& table) {
    for (const auto& row : table.rows)
        os << row << '\n';
    return os;
}

std::string TextTable::buildRowDelimitator(const std::string& delimitator) const {
    std::string delim_row = "+";
    for (size_t i = 0; i < columns_no; ++i) {
        for (size_t j = 0; j < columns_size[i]; ++j)
            delim_row += delimitator;
        delim_row += "+";
    }
    return delim_row;
}

int TextTable::getPartialWidth(int columns) const {
    int width = columns + 1;
    for (size_t i = 0; i < columns; ++i)
        width += columns_size[i];
    return width;
}

int TextTable::addHeader(size_t argc, ...) {
    if (rows_no || argc != columns_no)
        return -1;

    va_list args;
    va_start(args, argc);

    std::string data_row = "|";
    for (size_t i = 0; i < argc; ++i) {
        char* data = va_arg(args, char*);
        columns_size.push_back(PADDING * 2 + strlen(data));

        for (size_t j = 0; j < PADDING; ++j)
            data_row += " ";
        data_row += std::string(data);
        for (size_t j = 0; j < PADDING; ++j)
            data_row += " ";
        data_row += "|";
    }

    std::string delim_now = buildRowDelimitator("-");
    rows.push_back(delim_now);
    rows.push_back(data_row);

    delim_now = buildRowDelimitator("=");
    rows.push_back(delim_now);
    rows_no++;
    header = true;

    va_end(args);
    return 0;
}

int TextTable::addRow(size_t argc, ...) {
    if (argc != columns_no)
        return -1;

    va_list args;
    va_start(args, argc);

    std::string row_data = "|";
    for (size_t i = 0; i < argc; ++i) {
        char* data = va_arg(args, char*);
        if (((int)columns_size[i] - (int)strlen(data)) < MIN_PADDING * 2) {
            resize(i, strlen(data) + MIN_PADDING * 2);
        }
        int padding = columns_size[i] - strlen(data);

        for (size_t j = 0; j < padding / 2; ++j)
            row_data += " ";
        row_data += std::string(data);
        for (size_t j = 0; j < padding / 2 + padding % 2; ++j)
            row_data += " ";
        row_data += "|";
    }

    rows.push_back(row_data);
    std::string delim_row = buildRowDelimitator("-");
    rows.push_back(delim_row);

    rows_no++;
    va_end(args);

    return 0;
}

void TextTable::resize(size_t column, size_t size) {
    for (size_t i = 0; i < rows_no; ++i) {
        std::string row_data = rows[2 * i + 1].substr(0, getPartialWidth(column));
        std::string cell_data = getCellData(i, column);

        int padding = size - cell_data.size();
        for (size_t j = 0; j < padding / 2; ++j)
            row_data += " ";
        row_data += cell_data;
        for (size_t j = 0; j < padding / 2 + padding % 2; ++j)
            row_data += " ";
        row_data += "|";

        row_data += rows[2 * i + 1].substr(getPartialWidth(column + 1));
        rows[2 * i + 1] = row_data;
    }
    columns_size[column] = size;

    rows[0] = buildRowDelimitator("-");
    for (size_t i = 0; i < rows_no; ++i)
        rows[2 * i + 2] = buildRowDelimitator("-");
    if (header) rows[2] = buildRowDelimitator("=");
}

std::string TextTable::getCellData(int row, int column) {
    int found_nonspace = 0;
    bool found = false;

    size_t partial_width = getPartialWidth(column);
    std::string data = "";

    for (size_t i = partial_width; i < partial_width + columns_size[column]; ++i) {
        data += rows[2 * row + 1][i];
        if (data[i - partial_width] != ' ' && !found) {
            found_nonspace = i - partial_width;
            found = true;
        }
    }
    data.erase(data.begin(), data.begin() + found_nonspace);

    for (size_t i = data.size() - 1; i >= 0; --i)
        if (data[i] != ' ') {
            found_nonspace = i;
            break;
        }

    data.erase(data.begin() + found_nonspace + 1, data.end());
    return data;
}

size_t TextTable::getWidth() const {
    size_t width = columns_no + 1;
    for (size_t i = 0; i < columns_no; ++i)
        width += columns_size[i];
    return width;
}
