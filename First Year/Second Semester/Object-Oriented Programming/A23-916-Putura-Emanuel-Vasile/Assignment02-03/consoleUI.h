/*
*  ConsoleUI Module - handles user input/output
*/

#pragma once

#include "materials_service.h"

/*
*  ConsoleUI structure. Handles user input/output
*/
typedef struct {
	MaterialsService* materials_service;
	MemUndoRedoService* mem_undoredo_service;
} ConsoleUI;

/*
*  Creates a ConsoleUI object
*  <param materials_service> - pointer to a MaterialsService structure representing the application's materials service
*  <returns> - a pointer to the created consoleUI structure 
*/
ConsoleUI* createConsoleUI(MaterialsService* materials_service);

/*
*  Checks if a string contains only digits
*  <param string> - pointer to the first character of a string
*  <returns> - true if the given string contains only digits, false else
*/
bool isPositiveIntegerUI(const char* string);

/*
*  Outputs a message to the user, then asks him for a command
*  <param string> - output parameter, pointer to the first character of the command the user inputs
*  <param message> - pointer to the first character of the message displayed to the user
*/
void getStringFromUserUI(char* string, const char* message);

/*
*  Gets a command from the user
*  <param command> - output parameter, pointer to the first character of the command the user inputs
*/
void getUserCommandUI(char* command);

/*
*  Checks an user command, attempts to convert it to a positive valid integer and return it
*  <param command> - pointer to the first character of the user command
*  <param max_command> - integer, assuming all the user commands are positive integers, this represents the maximum possible command
*  <returns> the converted user command (as a positive integer) or 0 if the conversion failed
*/
int getUserIntegerCommandUI(const char* command, int max_command);

/*
*  Prints the application main menu
*/
void printMenuUI();

/*
*  Runs the application's main menu
*  <param consoleUI> - pointer to a structure of type ConsoleUI
*/
void runMenuUI(ConsoleUI* consoleUI);

/*
*  Prints all the materials currently stored in the application's repository
*  <param consoleUI> - pointer to a structure of type ConsoleUI
*/
void printMaterialsUI(ConsoleUI* consoleUI);

/*
*  Adds a material to the application's repository
*  <param consoleUI> - pointer to a structure of type ConsoleUI
*/
void addMaterialUI(ConsoleUI* consoleUI);

/*
*  Updates a material from the application's repository
*  <param consoleUI> - pointer to a structure of type ConsoleUI
*/
void updateMaterialUI(ConsoleUI* consoleUI);

/*
*  Updates the name of a material from the application's repository
*  <param consoleUI> - pointer to a structure of type ConsoleUI
*/
void updateMaterialNameUI(ConsoleUI* consoleUI);

/*
*  Updates the supplier of a material from the application's repository
*  <param consoleUI> - pointer to a structure of type ConsoleUI
*/
void updateMaterialSupplierUI(ConsoleUI* consoleUI);

/*
*  Updates the quantity of a material from the application's repository
*  <param consoleUI> - pointer to a structure of type ConsoleUI
*/
void updateMaterialQuantityUI(ConsoleUI* consoleUI);

/*
*  Updates the expiration date of a material from the application's repository
*  <param consoleUI> - pointer to a structure of type ConsoleUI
*/
void updateMaterialExpirationDateUI(ConsoleUI* consoleUI);

/*
*  Removes a material from the application's repository
*  <param consoleUI> - pointer to a structure of type ConsoleUI
*/
void removeMaterialUI(ConsoleUI* consoleUI);

/*
*  Finds all the materials past their expiration date and containing a string
*  <param consoleUI> - pointer to a structure of type ConsoleUI
*/
void findMaterialsPastExpDateUI(ConsoleUI* consoleUI);

void findMaterialsStrSortedBySupplierUI(ConsoleUI* consoleUI);

void printShortInSupplyUI(ConsoleUI* consoleUI);

void printOption8MaterialsUI(ConsoleUI* consoleUI);

void undoUI(ConsoleUI* consoleUI);

void redoUI(ConsoleUI* consoleUI);

/*
*  Frees the memory allocated for a ConsoleUI structure
*  <param consoleUI> - pointer to a structure of type ConsoleUI
*/
void destroyConsoleUI(ConsoleUI* consoleUI);
