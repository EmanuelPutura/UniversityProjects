#define _CRT_SECURE_NO_WARNINGS

#include "text_table.h"

#include <stdlib.h>
#include <string.h>

#ifndef CELL_PADDING
#define CELL_PADDING 10
#endif

#ifndef ARRAY_CAPACITY
#define ARRAY_CAPACITY 100
#endif

#ifndef BUFSIZE
#define BUFSIZE 1000
#endif

TextTable* createTextTable(int columns) {
	TextTable* text_table = (TextTable*)malloc(sizeof(TextTable));
	if (text_table == NULL) return NULL;
	text_table->dArray = createDynamicArray(ARRAY_CAPACITY);
	if (text_table->dArray == NULL) return NULL;
	
	text_table->columns = columns;
	text_table->rows = 0;

	text_table->column_size = (int*)malloc(columns * sizeof(int));
	if (text_table->column_size == NULL) return NULL;

	return text_table;
}

void removeCharTextTable(char* string, const char character) {
	int count = 0;
	for (int i = 0; string[i]; i++)
		if (string[i] != character)
			string[count++] = string[i];
	string[count] = '\0';
}

int getWidthTextTable(TextTable* text_table) {
	int width = text_table->columns + 1;
	for (int i = 0; i < text_table->columns; ++i)
		width += text_table->column_size[i];
	return width;
}

int getPartialWidthTextTable(TextTable* text_table, int columns) {
	int width = columns + 1;
	for (int i = 0; i < columns; ++i)
		width += text_table->column_size[i];
	return width;
}

char* getCellDataTextTable(TextTable* text_table, int row, int column) {
	if (row < 0 || column < 0 || row >= text_table->rows || column >= text_table->columns) return NULL;
	
	char line[BUFSIZE];
	strcpy(line, getElementDA(text_table->dArray, row * 2 + 1));
	removeCharTextTable(line, ' ');

	int count = 0;
	char* return_str = (char*)malloc(BUFSIZE * sizeof(char));

	char* token = strtok(line, "|");

	while (token != NULL) {
		if (count == column) break;
		token = strtok(NULL, "|");
		count++;
	}

	if (token == NULL) return NULL;
	strcpy(return_str, token);

	return return_str;
}

int setColSizeTextTable(TextTable* text_table, int column, int size) {
	if (column < 0 || column >= text_table->columns) return -1;
	text_table->column_size[column] = size;
	return 0;
}

void setAllColsSizeTextTable(TextTable* text_table, int argc, ...) {
	if (argc != text_table->columns) return -1;

	va_list args;
	va_start(args, argc);

	for (int i = 0; i < argc; ++i)
		text_table->column_size[i] = va_arg(args, int);

	va_end(args);
}

int setCellDataTextTable(TextTable* text_table, int row, int column, char* value, int span) {
	if (row < 0 || column < 0 || row >= text_table->rows || column >= text_table->columns) return NULL;
	char** data = getDataDA(text_table->dArray);

	char* line = getElementDA(text_table->dArray, 2 * row + 1);
	int partial_width_end = getPartialWidthTextTable(text_table, column + 1);
	int partial_width_start = partial_width_end - text_table->column_size[column] - 1;
	partial_width_end += span;
	int length = partial_width_end - partial_width_start + 1, size = (length - strlen(value));
	
	for (int j = partial_width_start; j < partial_width_start + size / 2; ++j)
		data[2 * row + 1][j] = ' ';
	
	strcpy(data[2 * row + 1] + partial_width_start + size / 2, value);
	
	for (int j = partial_width_start + size / 2 + strlen(value); j < partial_width_end; ++j)
		data[2 * row + 1][j] = ' ';

	free(value);
}

void resizeTextTable(TextTable* text_table, bool header, int column, int size) {
	char** data = getDataDA(text_table->dArray);

	int difference = size - text_table->column_size[column];
	int width = getWidthTextTable(text_table), partial_width_end = getPartialWidthTextTable(text_table, column + 1);
	int partial_width_start = partial_width_end - text_table->column_size[column] - 1;

	for (int i = 0; i < text_table->rows * 2 + 1; ++i) {
		for (int j = width + difference; j > partial_width_end; --j)
			data[i][j] = data[i][j - difference];
		for (int j = partial_width_start; j < partial_width_end + difference - 1; ++j)
			if (i == 2 && header) data[i][j] = '=';
			else if (i % 2 == 0) data[i][j] = '-';
			else setCellDataTextTable(text_table, (i - 1) / 2, column, getCellDataTextTable(text_table, (i - 1) / 2, column), difference - 2);
 	}

	text_table->column_size[column] = size;
}

void buildRowDelimTextTable(TextTable* text_table, char* line, char delimitator) {
	int width = getWidthTextTable(text_table);
	
	line[0] = '+';
	int last_position = 0, last_index = 0;

	for (int i = 1; i < width - 1; ++i) {
		line[i] = delimitator;
		if (text_table->column_size[last_index] == (i - last_position - 1)) {
			line[i] = '+';
			last_index++;
			last_position = i;
		}
	}
	line[width - 1] = '+';
	line[width] = 0;
}

int addRowTextTable(TextTable* text_table, bool header, int argc, ...) {
	if (argc > text_table->columns) return -1;
	if (header && text_table->rows) return -1;

	char delimitator = '-';
	if (header) delimitator = '=';

	va_list args;
	va_start(args, argc);

	char* row = (char*)malloc(BUFSIZE * sizeof(char));
	if (row == NULL) return NULL;

	int current_width = 1;
	for (int i = 0; i < text_table->columns; ++i) {
		strcpy(row + current_width - 1, "|");
		
		char* column_data = "";
		if (i < argc) column_data = va_arg(args, char*);
		
		if (!text_table->rows) setColSizeTextTable(text_table, i, strlen(column_data) + CELL_PADDING);

		if (text_table->column_size[i] < strlen(column_data) + 2)
			resizeTextTable(text_table, true, i, strlen(column_data) + CELL_PADDING);

		for (int j = 0; j < (text_table->column_size[i] - strlen(column_data)) / 2; ++j) {
			strcpy(row + current_width, " ");
			current_width++;
		}

		strcpy(row + current_width, column_data);
		current_width += strlen(column_data);

		int size = text_table->column_size[i] - strlen(column_data);
		size += size % 2;
		size /= 2;
		for (int j = 0; j < size; ++j) {
			strcpy(row + current_width, " ");
			current_width++;
		}

		current_width++;
	}
	strcpy(row + current_width - 1, "|");
	
	if (!text_table->rows) {
		char* row_a = (char*)malloc(BUFSIZE * sizeof(char));
		if (row_a == NULL) return -1;

		buildRowDelimTextTable(text_table, row_a, '-');
		addTextTable(text_table, row_a);
	}

	char* row_b = (char*)malloc(BUFSIZE * sizeof(char));
	if (row_b == NULL) return -1;

	buildRowDelimTextTable(text_table, row_b, delimitator);

	addTextTable(text_table, row);
	addTextTable(text_table, row_b);

	va_end(args);

	text_table->rows++;
	return 0;
}

void addTextTable(TextTable* text_table, char* row) {
	addDA(text_table->dArray, row);
}

void destroyTextTable(TextTable* text_table) {
	destroyDynamicArray(text_table->dArray, &free);
	free(text_table->column_size);
	free(text_table);
}
