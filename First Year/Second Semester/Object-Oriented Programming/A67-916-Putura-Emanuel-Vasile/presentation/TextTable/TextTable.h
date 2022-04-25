//
// Created by Emanuel on 22.03.2021.
//

#ifndef TEXTTABLE_H
#define TEXTTABLE_H

#include <vector>
#include <string>
#include <cstdarg>

/**
 * TextTable Class - provides functionalities for creating simple ASCII tables
 */
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

    /**
     * Adds a header to the table. A header can be added only once, as the first row in the table
     * @param argc: the number of table columns
     * @param ...: the function takes a variable number of parameters. Argc parameters must be passed, each of them representing data in a table cell
     * @return: 0 on success, -1 on failure
     */
    int addHeader(size_t argc, ...);

    /**
     * Adds a row to the table
     * @param argc: the number of table columns
     * @param ...: the function takes a variable number of parameters. Argc parameters must be passed, each of them representing data in a table cell
     * @return: 0 on success, -1 on failure
     */
    int addRow(size_t argc, ...);

    /**
     * Resizes a whole column of the table
     * @param column: the column index
     * @param size: the new size of the column
     */
    void resize(size_t column, size_t size);

    /**
     * Gets the data in a table cell
     * @param row: a row of the table
     * @param column: a column of the table
     * @return: a string representing the table cell data
     */
    std::string getCellData(int row, int column);

    /**
     * Gets the table width in characters
     * @return: the table width in characters
     */
    size_t getWidth() const;

    inline size_t getRowsNo() const { return rows_no; }

    friend std::ostream& operator<< (std::ostream& os, const TextTable& table);
};

#endif
