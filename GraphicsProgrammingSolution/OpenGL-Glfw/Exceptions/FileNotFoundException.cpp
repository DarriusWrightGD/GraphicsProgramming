#include "FileNotFoundException.h"
#include <string>


FileNotFoundException::FileNotFoundException(const char * filePath) : filePath(filePath)
{
}


FileNotFoundException::~FileNotFoundException()
{
}

const char * FileNotFoundException::what() const throw()
{
	return(std::string("Error file path does not exist : ") + filePath).c_str();
}