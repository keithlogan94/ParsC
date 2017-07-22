#pragma once
#include <string>
#include <vector>
/*
* Functionality:
* Read and store file data
* Allow access to file data by line and buffered data
* Line data and buffer data related indexer
*/
class FileData
{
	std::vector<std::string> f_lines;
	std::string f_data;
public:
	/* Open file. Get data. Store data in two formats:
	by line, complete buffer */
	FileData(const char *_file_name);
	~FileData();

	inline const std::string& data() { return f_data; }
	inline const std::vector<std::string>& dataLines() { return f_lines; }
private:
	/* Read file contents efficiently - helper method - return buffer */
	std::string readFile(const char *_file_name);
	/* Read file contents efficently - helper method - return file lines */
	std::vector<std::string> readFileLines(const char *_file_name);
};

