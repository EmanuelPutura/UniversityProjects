#define _CRT_SECURE_NO_WARNINGS
#define BUFSIZE 1000

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "consoleUI.h"
#include "text_table.h"

ConsoleUI* createConsoleUI(MaterialsService* materials_service) {
	ConsoleUI* consoleUI = (ConsoleUI*)malloc(sizeof(ConsoleUI));
	if (consoleUI == NULL) return NULL;

	consoleUI->materials_service = materials_service;

	return consoleUI;
}

bool isPositiveIntegerUI(const char* string) {
	for (size_t i = 0; i < strlen(string); ++i)
		if (!isdigit(string[i])) return false;
	return true;
}

void getStringFromUserUI(char* string, const char* message) {
	printf("%s", message);
	fgets(string, BUFSIZE, stdin);
	string[strcspn(string, "\n")] = 0;
}

void getUserCommandUI(char* command) {
	printf("command > ");
	fgets(command, BUFSIZE, stdin);
	command[strcspn(command, "\n")] = 0;
	printf("\n");
}

int getUserIntegerCommandUI(const char* command, int max_command) {
	int integer_command = atoi(command);
	
	if (!isPositiveIntegerUI(command)) {
		printf("'%s' is not a valid command\n", command);
		return 0;
	}

	if (!integer_command || integer_command < 1 || integer_command > max_command) {
		printf("'%s' is not a valid command\n", command);
		return 0;
	}
	return integer_command;
}

void printMenuUI() {
	printf("-----------------------------------\"Bread'n Bagel\" Bakery Application-----------------------------------\n");
	printf(" 1. Add a material to the bakery\n");
	printf(" 2. Update a material from the bakery\n");
	printf(" 3. Remove a material from the bakery\n");
	printf(" 4. Display all materials\n");
	printf(" 5. Display all available materials past their expiration date, containing a given string\n   (if empty - all materials are considered)\n");
	printf(" 6. Display all the available materials containing a given string, sorted descending by supplier\n");
	printf(" 7. Display all materials from a given supplier, which are in short supply (quantity less\n   than a user-provided value), sorted by their quantities\n");
	printf(" 8. Display all materials expiring in a given year and containing a given string, sorted by name\n");
	printf(" 9. Undo the last operation\n");
	printf("10. Redo\n");
	printf("exit - Exit the application\n");
	printf("--------------------------------------------------------------------------------------------------------\n");
}

void runMenuUI(ConsoleUI* consoleUI) {
	int integer_command = 0;
	addDefaultMaterialsService(consoleUI->materials_service);

	void (*commands[])(ConsoleUI*) = {NULL, addMaterialUI, updateMaterialUI, removeMaterialUI, printMaterialsUI, findMaterialsPastExpDateUI, \
						findMaterialsStrSortedBySupplierUI, printShortInSupplyUI, printOption8MaterialsUI, undoUI, redoUI};
	char* command = (char*)malloc(BUFSIZE * sizeof(char));
	if (command == NULL) return;

	bool running = true;
	while (running) {
		printMenuUI();
		getUserCommandUI(command);
		if (!strcmp(command, "exit")) {
			running = false;
			continue;
		}
		integer_command = getUserIntegerCommandUI(command, 10);
		if (integer_command) (*commands[integer_command])(consoleUI);
	}

	free(command);
}

void printMaterialsUI(ConsoleUI* consoleUI) {
	char* representation = getRepoTextTableService(consoleUI->materials_service);
	printf("%s\n", representation);
	free(representation);
}

void addMaterialUI(ConsoleUI* consoleUI) {
	char name[BUFSIZE], supplier[BUFSIZE], quantity[BUFSIZE], expiration_date[BUFSIZE];
	getStringFromUserUI(name, "Please input the name of the material: ");
	getStringFromUserUI(supplier, "Please input the supplier of the material: ");
	getStringFromUserUI(quantity, "Please input the quantity of the material: ");

	if (!isPositiveIntegerUI(quantity)) {
		printf("Invalid input.\n");
		return;
	}
	
	int int_quantity = atoi(quantity);
	getStringFromUserUI(expiration_date, "Please input the expiration date of the material (MM/DD/YY): ");
	if (addMaterialService(consoleUI->materials_service, name, supplier, &int_quantity, expiration_date, true)) printf("Invalid material.\n");
	else printf("\nThe material has been added.\n");
}

void updateMaterialUI(ConsoleUI* consoleUI) {
	void (*commands[])(ConsoleUI*) = { NULL, updateMaterialNameUI, updateMaterialSupplierUI, updateMaterialQuantityUI, updateMaterialExpirationDateUI };
	char command[BUFSIZE];

	printf("1. Update the name of a material\n2. Update the supplier of a material\n3. Update the quantity of a material\n");
	printf("4. Update the expiration date of a material\n");
	
	getUserCommandUI(command);
	int integer_command = getUserIntegerCommandUI(command, 4);
	if (integer_command) (*commands[integer_command])(consoleUI);
}

void updateMaterialNameUI(ConsoleUI* consoleUI) {
	char name[BUFSIZE], supplier[BUFSIZE], expiration_date[BUFSIZE], new_name[BUFSIZE];
	getStringFromUserUI(name, "Please input the current name of the material: ");
	getStringFromUserUI(supplier, "Please input the current supplier of the material: ");
	getStringFromUserUI(expiration_date, "Please input the current expiration date of the material (MM/DD/YY): ");
	getStringFromUserUI(new_name, "Please input the new name of the material: ");

	if (updateMaterialNameService(consoleUI->materials_service, name, supplier, expiration_date, new_name, true)) printf("Invalid input.\n");
	else printf("\nThe material has been updated.\n");
}

void updateMaterialSupplierUI(ConsoleUI* consoleUI) {
	char name[BUFSIZE], supplier[BUFSIZE], expiration_date[BUFSIZE], new_supplier[BUFSIZE];
	getStringFromUserUI(name, "Please input the current name of the material: ");
	getStringFromUserUI(supplier, "Please input the current supplier of the material: ");
	getStringFromUserUI(expiration_date, "Please input the current expiration date of the material (MM/DD/YY): ");
	getStringFromUserUI(new_supplier, "Please input the new supplier of the material: ");

	if (updateMaterialSupplierService(consoleUI->materials_service, name, supplier, expiration_date, new_supplier, true)) printf("Invalid input.\n");
	else printf("\nThe material has been updated.\n");
}

void updateMaterialQuantityUI(ConsoleUI* consoleUI) {
	char name[BUFSIZE], supplier[BUFSIZE], expiration_date[BUFSIZE], new_quantity[BUFSIZE];
	getStringFromUserUI(name, "Please input the current name of the material: ");
	getStringFromUserUI(supplier, "Please input the current supplier of the material: ");
	getStringFromUserUI(expiration_date, "Please input the current expiration date of the material (MM/DD/YY): ");
	getStringFromUserUI(new_quantity, "Please input the new quantity of the material: ");

	if (!isPositiveIntegerUI(new_quantity)) {
		printf("'%s' is not a valid quantity\n", new_quantity);
		return;
	}

	int int_quantity = atoi(new_quantity);
	if (updateMaterialQuantityService(consoleUI->materials_service, name, supplier, expiration_date, &int_quantity, true)) printf("Invalid input.\n");
	else printf("\nThe material has been updated.\n");
}

void updateMaterialExpirationDateUI(ConsoleUI* consoleUI) {
	char name[BUFSIZE], supplier[BUFSIZE], expiration_date[BUFSIZE], new_expiration_date[BUFSIZE];
	getStringFromUserUI(name, "Please input the current name of the material: ");
	getStringFromUserUI(supplier, "Please input the current supplier of the material: ");
	getStringFromUserUI(expiration_date, "Please input the current expiration date of the material (MM/DD/YY): ");
	getStringFromUserUI(new_expiration_date, "Please input the new expiration date of the material (MM/DD/YY): ");

	if (updateMaterialExpirationDateService(consoleUI->materials_service, name, supplier, expiration_date, new_expiration_date, true)) printf("Invalid input.\n");
	else printf("\nThe material has been updated.\n");
}

void removeMaterialUI(ConsoleUI* consoleUI) {
	char name[BUFSIZE], supplier[BUFSIZE], expiration_date[BUFSIZE];
	getStringFromUserUI(name, "Please input the name of the material: ");
	getStringFromUserUI(supplier, "Please input the supplier of the material: ");
	getStringFromUserUI(expiration_date, "Please input the expiration date of the material (MM/DD/YY): ");
	
	if (removeMaterialService(consoleUI->materials_service, name, supplier, expiration_date, true)) printf("Invalid material.\n");
	else printf("\nThe material has been deleted.\n");
}

void findMaterialsPastExpDateUI(ConsoleUI* consoleUI) {
	int length = getDataLengthService(consoleUI->materials_service);
	if (!length) {
		printf("No materials added yet.\n");
		return;
	}

	char today_date[BUFSIZE], string[BUFSIZE];
	getStringFromUserUI(today_date, "Please input the reference date (MM/DD/YY) in order to check the expiration date of the products: ");
	getStringFromUserUI(string, "Please input a string: ");

	char* representation = getMaterialsStrPastExpDateService(consoleUI->materials_service, today_date, string, &length);
	printf("%s\n", representation);
	free(representation);
}

void findMaterialsStrSortedBySupplierUI(ConsoleUI* consoleUI) {
	int length = getDataLengthService(consoleUI->materials_service);
	if (!length) {
		printf("No materials added yet.\n");
		return;
	}

	char string[BUFSIZE];
	getStringFromUserUI(string, "Please input a string: ");

	char* representation = getAllContainingStringSortedBySupplier(consoleUI->materials_service, string, &length);
	printf("%s\n", representation);
	free(representation);
}

void printShortInSupplyUI(ConsoleUI* consoleUI) {
	int length = getDataLengthService(consoleUI->materials_service);
	if (!length) {
		printf("No materials added yet.\n");
		return;
	}

	char supplier[BUFSIZE], quantity[BUFSIZE], sorting_order[BUFSIZE];
	getStringFromUserUI(supplier, "Please input a supplier: ");
	getStringFromUserUI(quantity, "Please input a quantity: ");
	getStringFromUserUI(sorting_order, "Please input the sorting order(A/D): ");

	if (strcmp(sorting_order, "A") && strcmp(sorting_order, "D")) {
		printf("Invalid sorting order.\n");
		return;
	}

	if (!isPositiveIntegerUI(quantity)) {
		printf("'%s' is not a valid quantity\n", quantity);
		return;
	}

	int int_quantity = atoi(quantity);

	printf("All materials from the given supplier, which are in short supply (quantity less than the user-provided quantity),\nsorted ascending by their quantities:\n");

	char* representation = getMaterialsShortInSupplyStr(consoleUI->materials_service, supplier, sorting_order, int_quantity, &length);
	printf("%s\n", representation);
	free(representation);
}

void printOption8MaterialsUI(ConsoleUI* consoleUI) {
	int length = getDataLengthService(consoleUI->materials_service);
	if (!length) {
		printf("No materials added yet.\n");
		return;
	}

	char string[BUFSIZE], year[BUFSIZE], sorting_order[BUFSIZE];;
	getStringFromUserUI(year, "Please input an expiration date year: ");
	getStringFromUserUI(string, "Please input a string: ");
	getStringFromUserUI(sorting_order, "Please input the sorting order(A/D): ");

	if (strcmp(sorting_order, "A") && strcmp(sorting_order, "D")) {
		printf("Invalid sorting order.\n");
		return;
	}

	if (!isPositiveIntegerUI(year)) {
		printf("'%s' is not a valid year\n", year);
		return;
	}

	int int_year = atoi(year);

	char* representation = getOption8MaterialString(consoleUI->materials_service, string, int_year, sorting_order, &length);
	printf("%s\n", representation);
	free(representation);
}

void undoUI(ConsoleUI* consoleUI) {
	if (!undoMaterialsService(consoleUI->materials_service)) printf("Undo performed successfully.\n");
	else printf("Cannot undo.\n");
}

void redoUI(ConsoleUI* consoleUI) {
	if (!redoMaterialsService(consoleUI->materials_service)) printf("Redo performed successfully.\n");
	else printf("Cannot redo.\n");
}

void destroyConsoleUI(ConsoleUI* consoleUI) {
	destroyMaterialsService(consoleUI->materials_service);
	free(consoleUI);
}