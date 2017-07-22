#include "FileData.h"

#include <fstream>


FileData::FileData(const char *_file_name)
{
	f_lines = readFileLines(_file_name);
	f_data = readFile(_file_name);
}

FileData::~FileData()
{
}

std::string FileData::readFile(const char * _file_name)
{
	using namespace std;
	string file;
	ifstream ifs(_file_name, ios::in);
	if (ifs.is_open())
	{
		filebuf *p_buf = ifs.rdbuf();
		size_t size = p_buf->pubseekoff(0, ifs.end, ifs.in);
		p_buf->pubseekpos(0, ifs.in);
		char *buffer = new char[size];
		p_buf->sgetn(buffer, size);
		file = buffer;
		delete[] buffer;
		p_buf->close();
		ifs.close();
	}
	return file;
}

std::vector<std::string> FileData::readFileLines(const char * _file_name)
{
	using namespace std;
	vector<string> file_lines;
	ifstream ifs(_file_name, ios::in);
	if (ifs.is_open())
	{
		string line;
		while (getline(ifs, line)) {
			file_lines.push_back(line);
			line.clear();
		}
		ifs.close();
	}
	return file_lines;
}
