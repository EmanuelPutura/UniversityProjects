#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date.h"

Date* createDate(const char* string_date) {
	if (getCharacterOccurences(string_date, '/') != 2) return NULL;
	int day = getDayFromString(string_date);
	if (day == -1) return NULL;
	int month = getMonthFromString(string_date);
	if (month == -1) return NULL;
	int year = getYearFromString(string_date);
	if (year == -1) return NULL;

	Date* date = (Date*)malloc(sizeof(Date));
	if (date == NULL) return NULL;

	date->day = day, date->month = month, date->year = year;
	return date;
}

int getDayFromString(const char* date) {
	char aux_string[101];
	strcpy(aux_string, date);

	const char* delimiter = "/";
	char* token = strtok(aux_string, delimiter);
	if (token != NULL) return atoi(token);
	return -1;
}

int getMonthFromString(const char* date) {
	char aux_string[101];
	strcpy(aux_string, date);

	const char* delimiter = "/";
	char* token = strtok(aux_string, delimiter);
	if (token != NULL)
		token = strtok(NULL, delimiter);
	if (token != NULL) return atoi(token);
	return -1;
}

int getYearFromString(const char* date) {
	char aux_string[101];
	strcpy(aux_string, date);

	const char* delimiter = "/";
	char* token = strtok(aux_string, delimiter);
	if (token == NULL) return -1;
	token = strtok(NULL, delimiter);
	if (token == NULL) return -1;
	token = strtok(NULL, delimiter);
	if (token == NULL) return -1;
	return atoi(token);
}

int getDateDay(Date* date) {
	return date->day;
}

int getDateMonth(Date* date) {
	return date->month;
}

int getDateYear(Date* date) {
	return date->year;
}

void setDateDay(Date* date, int day) {
	date->day = day;
}

void setDateMonth(Date* date, int month) {
	date->month = month;
}

void setDateYear(Date* date, int year) {
	date->year = year;
}

void convertIntToString(int integer, char* string, const char delimiter) {
	sprintf(string, "%d", integer);
	int n = strlen(string);
	string[n] = delimiter;
	string[n + 1] = 0;
}

bool leapDateYear(Date* date) {
	return (((date->year % 4 == 0) && (date->year % 100 != 0)) || (date->year % 400 == 0));
}

int getCharacterOccurences(const char* string, const char character) {
	int number_of_occurences = 0;
	for (size_t i = 0; i < strlen(string); ++i)
		if (string[i] == character) number_of_occurences++;
	return number_of_occurences;
}

void dateToString(Date* date, char* string_representation) {
	convertIntToString(date->day, string_representation, '/');
	convertIntToString(date->month, string_representation + strlen(string_representation), '/');
	convertIntToString(date->year, string_representation + strlen(string_representation), 0);
}

bool equalDates(Date* date1, Date* date2) {
	return date1->day == date2->day && date1->month == date2->month && date1->year == date2->year;
}

bool greaterDate(Date* date1, Date* date2) {
	if (date1->year != date2->year) return date1->year > date2->year;
	if (date1->month != date2->month) return date1->month > date2->month;
	if (date1->day != date2->day) return date1->day > date2->day;
	return false;
}

bool greaterOrEqualDate(Date* date1, Date* date2) {
	return greaterDate(date1, date2) || equalDates(date1, date2);
}

void swapDates(Date* date1, Date* date2) {
	int day = date2->day, month = date2->month, year = date2->year;

	date2->day = date1->day;
	date2->month = date1->month;
	date2->year = date1->year;

	date1->day = day;
	date1->month = month;
	date1->year = year;
}

void destroyDate(Date* date) {
	free(date);
}