#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


void printMenu();
void run();
void readVector(int* n, int* vector);
bool isPrime(int n);
bool areTwin(int a, int b);
void findTwinNumbers(int n, int* twin_numbers);
void findDecreasingSubsequence(int n, int* vector, int* start_index, int* found_nos);
void printTwinNumbers(int n, int* vector);
void printFoundSubsequence(int* vector, int start_index, int found_nos);
int gcd(int a, int b);
int solveBonusProblem(int n, int* vector);
void printBonusProblemResult(int* vector, int length, int n);


int main() {
	run();
	return 0;
}

/*
* Prints the application main menu
*/
void printMenu()
{
	printf("\n------------------- Assignment 1 -------------------\n");
	printf("1 - Read a vector of numbers.\n");
	printf("2 - Determine the first n pairs of twin numbers, where n is a given natural and non-null number.\n");
	printf("    Two prime numbers p and q are called twin if q - p = 2.\n");
	printf("3 - Given a vector of numbers (read with command 1), find the longest decreasing contiguous subsequence.\n");
	printf("4 - Determine all the numbers smaller than a given natural and non-null number n and that are relatively prime to n\n");
	printf("5 - Exit the application.\n");
	printf("----------------------------------------------------\n");
}


/*
* Runs the application
*/
void run()
{
	int n = 0, casted_command = 0;
	int vector[101];
	char command[101];
	bool running = true;

	while (running)
	{
		printMenu();
		scanf_s("%s", command, sizeof(command));
		casted_command = (int)(strtol(command, NULL, 10));

		switch (casted_command)
		{
			case 1:
				readVector(&n, vector);
				break;
			case 2:
			{
				int twin_numbers_n = 0;
				printf("The number of twin numbers to be searched is: \n");
				scanf_s("%d", &twin_numbers_n);
				int twin_numbers[101];
				findTwinNumbers(twin_numbers_n, twin_numbers);
				printTwinNumbers(twin_numbers_n, twin_numbers);
				break;
			}
			case 3:
				if (!n)
				{
					printf("You must first use the '1' command in order to read a vector.\n");
					break;
				}
				int start_index = 0, found_nos = 1;
				findDecreasingSubsequence(n, vector, &start_index, &found_nos);
				printFoundSubsequence(vector, start_index, found_nos);
				break;
			case 4:
			{
				int no = 0;
				int numbers[101];
				printf("Please input a positive integer: ");
				scanf_s("%d", &no);
				int length = solveBonusProblem(no, numbers);
				printBonusProblemResult(numbers, length, no);
				break;
			}
			case 5:
				running = false;
				break;
			default:
				printf("'%s' is not a valid command!\n", command);
				break;
		}
	}
}


/*
* Reads a given number of elements from the console
* Input: n, vector - pointers to int
*		 n 	       - the address of the value representing how many numbers will be read from the console
*		 vector    - the address of the first element of the vector
*/
void readVector(int* n, int* vector)
{
	printf("n = ");
	scanf_s("%d", n);
	printf("\nThe elements of the vector are: \n");

	for (int i = 0; i < *n; ++i)
		scanf_s("%d", vector + i);
}


/*
* Checks if a given number is prime or not
* Input:  n - integer, n >= 0, represents the number to be checked
* Output: returns true if n is a prime number, false else
*/
bool isPrime(int n)
{
	if (n < 2) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;
	for (int d = 3; d * d <= n; d += 2)
		if (n % d == 0) return false;
	return true;
}

/*
* Checks if two given positive integers are twin numbers or not. Two positive integers p and q are called twin if they are prime and q - p = 2
* Input:  a, b - integers, a, b > 0, where a and b are the numbers to be checked
* Output: returns true if a and b are twin numbers, false else
*/
bool areTwin(int a, int b)
{
	return isPrime(a) && isPrime(b) && (b - a) == 2;
}


/*
* Finds a given number of pairs of twin positive integers. The first element from the first found pair will be stored in a given vector
* Input:  n            - integer, n >= 0, represents the number of pairs of twin integers to be searched for
*		  twin_numbers - pointer to int, represents the address of the first element from the twin numbers vector
*/
void findTwinNumbers(int n, int* twin_numbers)
{
	int found_twins = 0;
	for (int no = 2; found_twins < n; ++no)
		if (areTwin(no, no + 2))
		{
			twin_numbers[found_twins] = no;
			found_twins++;
		}
}


/*
* Finds the longest decreasing contiguous subsequence of a given vector. The addresses of the start index of the found subsequence and
* of the number of elements in it will be stored in two given pointers
* Input:  n			  - integer, n >= 0, represents the number of elements in the given vector
*		  vector	  - pointer to int, represents the address of the first element in the given vector
*		  start_index - pointer to int, represents the address of the start index of the found subsequence in the vector
*		  found_nos   - pointer to int, represents the address of the number of found elements in the subsequence
*/
void findDecreasingSubsequence(int n, int* vector, int* start_index, int* found_nos)
{
	int current_start_index = 0, current_elements_no = 1;

	for (int i = 1; i < n; ++i)
	{
		if (vector[i] <= vector[i - 1])
		{
			current_elements_no++;
			if (current_elements_no > *found_nos)
			{
				*found_nos = current_elements_no;
				*start_index = current_start_index;
			}
		}
		else
		{
			current_start_index = i;
			current_elements_no = 1;
		}
	}
}


/*
* Prints the pairs of twin integers from a vector containing on each position the first element from such a pair. The second element is 
* obtained by adding two to the first one
* Input:  n      - integer, n >= 0 , represents the number of pairs of twin numbers
*		  vector - pointer to int, represents the address of the first element of the first pair of twin numbers 
*/
void printTwinNumbers(int n, int* vector)
{
	for (int i = 0; i < n; ++i)
		printf("Pair %3d | %5d | %5d\n", i + 1, vector[i], vector[i] + 2);
}


/*
* Prints the found longest decreasing contiguous subsequence, being given the source vector, the start index in the vector and the number
* of elements in the subsequence
* Input:  vector      - pointer to int, represents the address of the first element in the source vector
*         start_index - integer, start_index >= 0, represents the start index in the source vector
*		  found_nos   - integer, found_nos >= 0, represents how many numbers have been found in the subsequence
*/
void printFoundSubsequence(int* vector, int start_index, int found_nos)
{
	printf("The longest decreasing contiguous subsequence is:\n");
	for (int i = start_index; i - start_index + 1 <= found_nos; ++i)
		printf("%d ", vector[i]);
	printf("\n(containing %d elements)\n", found_nos);
}

int gcd(int a, int b)
{
	while (b != 0)
	{
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int solveBonusProblem(int n, int* vector)
{
	int cnt = 0;
	for (int i = 1; i < n; ++i)
		if (gcd(i, n) == 1)
		{
			vector[cnt] = i;
			cnt += 1;
		}
	return cnt - 1;
}

void printBonusProblemResult(int* vector, int length, int n)
{
	printf("The numbers that are relative prime to %d are:\n", n);
	for (int i = 0; i < length; ++i)
		printf("Integer no. %2d coprime with n | %3d\n", i + 1, vector[i]);
}