#pragma once
#include <exception>

class FileNotFoundException : public std::exception
{
public:
	FileNotFoundException(const char * filePath);
	~FileNotFoundException();
	virtual const char * what() const throw() override;
private:
	const char * filePath;
};

