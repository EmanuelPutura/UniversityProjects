/*
*  Date Module - implements a Date structure, representing a calendar date
*/

#pragma once
#include <stdbool.h>

/*
*  Date structure. Handles dates
*/
typedef struct {
	int day, month, year;
} Date;

/*
*  Creates a date object from a string representing a date in the format DD/MM/YY
*  <param string_date> - pointer to the first character of the string representating of a date
*  <returns> a pointer to the created Date object, or NULL if the object could not be created
*/
Date* createDate(const char* string_date);

/*
*  Gets the day from a string representation of a date in the format DD/MM/YY
*  <param date> - pointer to the first character of the string representating of a date
*  <returns> - an integer representing the date's day, or -1 if the date's format is invalid
*/
int getDayFromString(const char* date);

/*
*  Gets the month from a string representation of a date in the format DD/MM/YY
*  <param date> - pointer to the first character of the string representating of a date
*  <returns> - an integer representing the date's month, or -1 if the date's format is invalid
*/
int getMonthFromString(const char* date);

/*
*  Gets the year from a string representation of a date in the format DD/MM/YY
*  <param date> - pointer to the first character of the string representating of a date
*  <returns> - an integer representing the date's year, or -1 if the date's format is invalid
*/
int getYearFromString(const char* date);

/*
*  Gets the day of a date
*  <param date> - pointer to a Date object
*  <returns> - an integer representing the date's day
*/
int getDateDay(Date* date);

/*
*  Gets the month of a date
*  <param date> - pointer to a Date object
*  <returns> - an integer representing the date's month
*/
int getDateMonth(Date* date);

/*
*  Gets the year of a date
*  <param date> - pointer to a Date object
*  <returns> - an integer representing the date's year
*/
int getDateYear(Date* date);

/*
*  Sets the day of a date
*  <param date> - pointer to a Date object
*/
void setDateDay(Date* date, int day);

/*
*  Sets the month of a date
*  <param date> - pointer to a Date object
*/
void setDateMonth(Date* date, int month);

/*
*  Sets the year of a date
*  <param date> - pointer to a Date object
*/
void setDateYear(Date* date, int year);

/*
*  Converts an integer to a string (used in other Date specialized functions)
*  <param integer> - the integer to be converted to a string
*  <param string> - output parameter, pointer to the first character of the converted integer
*  <param delimiter> - character representing a delimiter to be placed at the end of the conversion
*/
void convertIntToString(int integer, char* string, const char delimiter);

/*
*  Checks if a date's year is leap or not
*  <param date> - pointer to a Date object
*  <returns> - true if the given date's year is leap, false else
*/
bool leapDateYear(Date* date);

/*
*  Gets the number of occurences of a character in a string (used in other Date specialized functions)
*  <param string> - pointer to the first character of a string where a given character must be searched for
*  <param character> - the character to be searched for
*  <returns> - the number of occurences of the given character in the given string
*/
int getCharacterOccurences(const char* string, const char character);

/*
*  Converts a date to a string representation of it, in the format DD/MM/YY
*  <param date> - pointer to a Date object
*  <param string_representation> - output parameter, pointer to the first character of a string representing the converted date
*/
void dateToString(Date* date, char* string_representation);

/*
*  Checks if two dates are equal. Two dates are equal if and only if their day, month and year are equal
*  <param date1> - pointer to a Date object, the first date
*  <param date2> - pointer to a Date object, the second date
*  <returns> - true if the two dates are equal, false else
*/
bool equalDates(Date* date1, Date* date2);

/*
*  Checks if a date is greater than another one. A date is greater than another one if and only if its year is greater, or else its month is greater, or else its day is greater
*  <param date1> - pointer to a Date object, the first date
*  <param date2> - pointer to a Date object, the second date
*  <returns> - true if the first date is greater than the second one, false else
*/
bool greaterDate(Date* date1, Date* date2);

/*
*  Swaps the attributes of two dates
*/
void swapDates(Date* date1, Date* date2);

/*
*  Frees the memory allocated for a Date object
*  <param date> - pointer to a Date object, representing the object to be destroyed
*/
void destroyDate(Date* date);