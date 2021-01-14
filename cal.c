#include <stdio.h>
#include <string.h>
#include <ctype.h>

void plus_verylongint(char x[100], char y[100], char result[101], int *error); // prototype of plus_verylongint
void minus_verylongint(char x[100], char y[100], char result[101], int *error); // prototype of minus_verylongint

int main() {
	char x[100], y[100], result[101];
	int error = 0;

	printf("X: ");
	scanf("%s", x); //scan x value
	printf("Y: ");
	scanf("%s", y); //scan y value

	plus_verylongint(x, y, result, &error); // Result = X + Y
	printf("X + Y = ");
	if (error) // if someting wrong, print the error
		printf("Error!\n");
	else // print result
		printf("%s\n", result);

	minus_verylongint(x, y, result, &error); // Result = X - Y
	printf("X - Y = ");
	if (error) // if someting wrong, print the error
		printf("Error!\n");
	else // print result
		printf("%s\n", result);

	return 0;
}

void plus_verylongint(char x[100], char y[100], char result[101], int *error) {
	int q = 0;

	//find out the real length of number represented as the string in each array
	//using <string.h>
	int i = 0;
	int j = 0;//initialization

	int length_x = strlen(x);
	while ((x[i] - '0') == 0) {
		length_x--;//decrement//neglect zero such as 002, 03,000001 ((cf)20)
		i++;
	}//length of number in x array

	int length_y = strlen(y);
	while ((y[j] - '0') == 0) {
		length_y--;//decrement//neglect zero such as 002, 03,000001 ((cf)20)
		j++;
	}//length of number in y array //i>=j

	for (int a = 0; a < strlen(x); ++a) {
		x[a] = x[a + i];
	}
	for (int a = 0; a < strlen(y); ++a) {
		y[a] = y[a + j];
	}

	//error//when not integer
	//using <ctype.h> to determine whether it is an integer or character
	for (int a = 0, b = 0; a < length_x, b < length_y; ++a, ++b) {
		if (isdigit(x[a]) == 0 || isdigit(y[b]) == 0) { *error = 1; }
	}
	
	while (length_x > -1)
	{
		if (length_y > -1) {
			result[length_x] = ((x[length_x] - '0') + (y[length_y] - '0') + q) % 10 + '0';

			if ((x[length_x] - '0') + (y[length_y] - '0') + q + '0' >= 58) q = 1;
			else q = 0;
		}
		else {
			result[length_x] = (x[length_x] - '0' + q) % 10 + '0';

			if ((x[length_x] - '0') + q + '0' >= 58) q = 1;
			else q = 0;
		}
		if (length_x == 0&&q==1) {
			for (int i = strlen(x)+1; i >= 0; i--)
			{
				result[i + 1] = result[i];
			}
			result[0] = '1';

			result[strlen(x) + 1] = 0;
		}
		else
			result[strlen(x)] = 0;

		if (result[0] == 0)
		{
			result[0] = '0';
			result[1] = 0;
		}

		length_x--;
		length_y--;
	}
}

void minus_verylongint(char x[100], char y[100], char result[101], int *error) {
	int q = 0;
	int i = 0;
	int j = 0;

	int length_x = strlen(x);
	int length_y = strlen(y);
	int num = length_x;


	for (int a = 0, b = 0; a < length_x, b < length_y; ++a, ++b) {
		if (isdigit(x[a]) == 0 || isdigit(y[b]) == 0) { *error = 1; }
	}

	while (length_x > -1) {
		if (length_y > -1) {
			if (x[length_x] + q < y[length_y]) {
				result[length_x] = (10 - (y[length_y] - '0')) + (x[length_x] - '0') + q + '0';
				q = -1;
			}
			else {
				result[length_x] = (x[length_x] - '0') - (y[length_y] - '0') + '0' + q;
				q = 0;
			}
		}
		else {
			if ((x[length_x] + q) < 48) {
				result[length_x] = 10 + q + '0';
				q = -1;
			}
			else {
				result[length_x] = x[length_x] + q;
				q = 0;
			}
		}
		result[num] = 0;

		if (result[0] == '0') {
			for (int i = 0; i < strlen(x) + 1; i++) {
				result[i] = result[i + 1];
			}

		}

		if (result[0] == 0)
		{
			result[0] = '0';
			result[1] = 0;
		}

		length_x--;
		length_y--;
	}
}