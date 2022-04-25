#include <stdio.h>
#include <crtdbg.h>
#include <stdlib.h>

#include "text_table.h"

int main() {
	int columns_no = 4;
	TextTable * textTable = createTextTable(columns_no);

	addRowTextTable(textTable, true, columns_no, "", "Capital", "Currency", "Population");
	addRowTextTable(textTable, false, columns_no, "France", "Paris", "Euro", "65,373,694");
	addRowTextTable(textTable, false, columns_no, "Romania", "Bucharest", "Leu", "19,148,003");
	addRowTextTable(textTable, false, columns_no, "Italy", "Rome", "Euro", "60,400,064");
	addRowTextTable(textTable, false, columns_no, "England", "London", "GBP", "67,886,011");
	addRowTextTable(textTable, false, columns_no, "Hungary", "Budapest", "Forint", "9,643,303");
	addRowTextTable(textTable, false, columns_no, "Spain", "Madrid", "Euro", "46,745,216");

	char* representation = getStringReprTextTable(textTable);
	printf("%s", representation);
	free(representation);
	destroyTextTable(textTable);

	_CrtDumpMemoryLeaks();

	return 0;
}