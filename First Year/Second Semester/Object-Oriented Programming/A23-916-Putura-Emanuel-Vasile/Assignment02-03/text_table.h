/*
*  TextTable Module - implements the TextTable structure, providing an easy way to create simple ASCII tables
*/

#pragma once

#include "dynamic_array.h"

#include <stdarg.h> 
#include <stdbool.h>

/*
*  TextTable structure
*/
typedef struct {
	DynamicArray* dArray; // a dynamic array consisting of elements representing rows in the table
	int rows, columns;	  // number of rows/columns in the table 
	int* column_size;	  // array keeping the size of each column in the table
} TextTable;

/*
*  Creates a TextTable object
*  <param columns> - positive integer represeting the number of columns in the table
*  <returns> - the created TextTable object
*/
TextTable* createTextTable(int columns);

/*
*  Adds a row to a TextTable object. The function takes a variable number of parameters
*  <param text_table> - pointer to TextTable
*  <param header> - bool, true if the added row should be considered as a header, false else
*  <param argc> - positive integer representing the number of parameters (without the first three of them) of the function
*  <param ...> - the function takes a variable number of parameters representing the data to be added in each cell in the added row. Note that the function can take less parameters than the
*  number of its columns, in which case the empty string is considered as cell data
*  <returns> - 0 on success, -1 on failure
*/
int addRowTextTable(TextTable* text_table, bool header, int argc, ...);

/*
*  Generic use function that removes all occurences of a character from a string
*  <param string> - pointer to char, representing the first character of a string
*  <param character> - a character to be removed from a given string
*/
void removeCharTextTable(char* string, const char character);

/*
*  Gets the width (in number of characters) of a TextTable object
*  <param text_table> - pointer to TextTable
*  <returns> - the width of the text table in number of characters
*/
int getWidthTextTable(TextTable* text_table);

/*
*  Gets the width (in number of characters) of some columns of a TextTable object
*  <param text_table> - pointer to TextTable
*  <param columns> - positive integer representing the number of columns to be taken into consideration when computing the width of the text table
*  <returns> - the width of the text table in number of characters
*/
int getPartialWidthTextTable(TextTable* text_table, int columns);

/*
*  Gets the data from a TextTable cell
*  <param text_table> - pointer to TextTable
*  <param row> - positive integer representing a row of the table
*  <param column> - positive integer representing a column of the table
*  <returns> - pointer to char representing the first character of the found data in a certain table cell
*/
char* getCellDataTextTable(TextTable* text_table, int row, int column);

/*
*  Sets the size of a TextTable column
*  <param text_table> - pointer to TextTable
*  <param column> - positive integer representing a column in the text table
*  <param size> - the new size of the column
*  <returns> - -1 if the update failed, 0 else
*/
int setColSizeTextTable(TextTable* text_table, int column, int size);

/*
*  Sets the data from a TextTable cell
*  <param text_table> - pointer to TextTable
*  <param row> - positive integer representing a row of the table
*  <param column> - positive integer representing a column of the table
*  <param value> - pointer to char representing the first character of a string containing the new value of a text table cell
*  <param span> - positive integer representing how many consecutive columns starting with the given one should have their data updated
*  <returns> - 0 on success, -1 on failure
*/
int setCellDataTextTable(TextTable* text_table, int row, int column, char* value, int span);

/*
*  Resizes a TextTable object. This is automatically done if the length of a string provided as cell data in the table is greater than the previous size of the column
*  <param text_table> - pointer to TextTable
*  <param header> - bool, is true if the table has a header, false else
*  <param column> - positive integer representing a column of the table (the one to be resized)
*  <param size> - the new size of the given column
*/
void resizeTextTable(TextTable* text_table, bool header, int column, int size);

/*
*  Builds the delimitator between two TextTable rows
*  <param text_table> - pointer to TextTable
*  <param line> - pointer to char representing the first character of a text table row to be built as a delimitator
*  <param delimitator> - character representing a delimitator between two rows
*/
void buildRowDelimTextTable(TextTable* text_table, char* line, char delimitator);

/*
*  Adds a row to a TextTable object. It is used internally.
*  <param text_table> - pointer to TextTable
*  <param row> - pointer to char representing the first character of a text table row
*/
void addTextTable(TextTable* text_table, char* row);

/*
*  Gets the string representation of a TextTable object
*  <param text_table> - pointer to TextTable
*  <returns> - pointer to char representing the first character of the string representation of the table
*/
char* getStringReprTextTable(TextTable* text_table);

/*
*  Destroys a TextTable object
*  <param text_table> - pointer to TextTable
*/
void destroyTextTable(TextTable* text_table);
