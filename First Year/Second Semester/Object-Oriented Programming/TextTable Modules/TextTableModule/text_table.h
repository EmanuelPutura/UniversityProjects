#pragma once

#include "dynamic_array.h"

#include <stdarg.h> 
#include <stdbool.h>

typedef struct {
	DynamicArray* dArray;
	int rows, columns, * column_size;
} TextTable;

TextTable* createTextTable(int columns);

void removeCharTextTable(char* string, const char character);

int getWidthTextTable(TextTable* text_table);

int getPartialWidthTextTable(TextTable* text_table, int columns);

char* getCellDataTextTable(TextTable* text_table, int row, int column);

int setColSizeTextTable(TextTable* text_table, int column, int size);

void setAllColsSizeTextTable(TextTable* text_table, int argc, ...);

int setCellDataTextTable(TextTable* text_table, int row, int column, char* value, int span);

void resizeTextTable(TextTable* text_table, bool header, int column, int size);

void buildRowDelimTextTable(TextTable* text_table, char* line, char delimitator);

int addRowTextTable(TextTable* text_table, bool header, int argc, ...);

void addTextTable(TextTable* text_table, char* row);

char* getStringReprTextTable(TextTable* text_table);

void destroyTextTable(TextTable* text_table);
#pragma once
