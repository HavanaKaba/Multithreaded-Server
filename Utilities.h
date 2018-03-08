#ifndef M1_UTILITIES_H
#define M1_UTILITIES_H

#pragma once
// Milestone 1 - Utilities Interface
// Utilities.h
// Chris Szalwinski
// v1.0 - 24/10/2015
// v2.0 - 23/02/2016
#include <string>
#include <fstream>

class Utilities {
	size_t field_width;           // maximum field width needed 
	static char delimiter;        // field delimiter character
	static std::ofstream logFile; // log file
public:
	Utilities()										{ field_width = 1; }
	void setFieldWidth(size_t fw)					{ field_width = fw; }
	size_t getFieldWidth() const					{ return field_width; }
	static void setDelimiter(const char delim)		{ delimiter = delim; }
	static void setLogFile(const char* log)			{ logFile.open(log); }
	static std::ofstream& getLogFile()				{ return logFile; }
	const std::string nextToken(const std::string& str, size_t& next_pos, bool& more) {
		size_t found = 0;
		std::string temp;

		if (str.find(delimiter, next_pos) != std::string::npos) {
			found = str.find(delimiter, next_pos);
			temp = str.substr(next_pos, found - next_pos);

			// while loops to trim whitespace from strings
			while (temp[temp.size() - 1] == ' ')
				temp.erase((temp.size() - 1), 1);
			while (temp[0] == ' ')
				temp.erase(0, 1);

			if (str[found + 1] == delimiter)
				throw "*** no token found before the delimiter ***";
			else
				next_pos = found + 1;
		}
		else {
			temp = str.substr(next_pos, str.find('\n'));

			// while loops to trim whitespace from strings
			while (temp[temp.size() - 1] == ' ')
				temp.erase((temp.size() - 1), 1);
			while (temp[0] == ' ')
				temp.erase(0, 1);

			found = str.size();
			next_pos = found;
		}

		if (str.size() <= next_pos || found == 0)
			more = false;

		if (temp.size() > field_width)
			setFieldWidth(temp.size());

		return temp;
	}
};

#endif