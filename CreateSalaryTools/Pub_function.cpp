#include "Pub_function.h"
#include <sstream>
using namespace std;

int Pub_Split(const char *str, const char *splitStr, std::vector<std::string> &outVector)
{
	if (str == NULL || strlen(str)<=0)
	{
		return 1;
	}

	char* strcopy = new char[strlen(str) + 1];
	strcpy(strcopy, str);

	char *word = strtok(strcopy, splitStr);
	outVector.push_back(word);
	while (word = strtok(nullptr, splitStr))
		outVector.push_back(word);
	
	delete[] strcopy;

	return 0;
}