#pragma once

#include <string>
using namespace std;

class ValidationException
{
private:
	string message;
	int lineNumber;
public:
	ValidationException(string message)
	{
		this->lineNumber = -1;
		this->message = message;
	}
	ValidationException(int lineNumber, string message) {
		this->lineNumber = lineNumber;
		this->message = message;
	}
	bool setLineNumber(int lineNumber)
	{
		if (this->lineNumber < 0)
		{
			this->lineNumber = lineNumber;
			return true;
		}
		return false;
	}
	string getInfo(void) const
	{
		return message + " at line " + to_string(lineNumber);
	}

};