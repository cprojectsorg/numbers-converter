/*
	Numbers Converter.
	Copyright (C) 2020  Hasan Alsamra hasan@cprojects.org

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

int getHexValue(char);
char getHexChar(int);

char *convertTo(const char str[], int fromRadix, int toRadix) {
	unsigned long long int toDecimal = 0;
	unsigned long long int decimalFrom = abs(atoll(str));
	
	static char converted[200];
	memset(converted, 0, 200);
	
	decimalFrom = 0;
	for(int i=0; strlen(str)-i > 0; i++) {
		char it = str[i];
		if(fromRadix == 16)
			if(getHexValue(it) > 0)
				decimalFrom += getHexValue(it) * pow(fromRadix, strlen(str) - i - 1);
			else
				decimalFrom += atoll(&it) * pow(fromRadix, strlen(str) - i - 1);
		else
			decimalFrom += atoll(&it) * pow(fromRadix, strlen(str) - i - 1);
	}
	
	int i = 0;
	while(decimalFrom != 0) {
		long long int temp = decimalFrom % toRadix;
		
		if(toRadix == 16) {
			if(temp < 10)
				converted[i++] = temp + 48;
			else
				converted[i++] = getHexChar(temp);
		} else
			converted[i++] = (char) '0' + temp;

		decimalFrom /= toRadix;
	}
	
	if(str[0] == '-' && strlen(converted) > 0)
		converted[i] = '-';
	
	if(strlen(converted) > 1) {
		char tmp;
		int length = strlen(converted);
		
		for(int j=0; j<length-1; j++,length--) {
			tmp = converted[j];
			converted[j] = converted[length-1];
			converted[length-1] = tmp;
		}
	}
	
	return converted;
}

int getHexValue(char charNum) {
	if(tolower(charNum) == 'a')
		return 10;
	if(tolower(charNum) == 'b')
		return 11;
	if(tolower(charNum) == 'c')
		return 12;
	if(tolower(charNum) == 'd')
		return 13;
	if(tolower(charNum) == 'e')
		return 14;
	if(tolower(charNum) == 'f')
		return 15;
	return 0;
}

char getHexChar(int num) {
	if(num == 10)
		return 'A';
	if(num == 11)
		return 'B';
	if(num == 12)
		return 'C';
	if(num == 13)
		return 'D';
	if(num == 14)
		return 'E';
	if(num == 15)
		return 'F';
	return 'z';
}
