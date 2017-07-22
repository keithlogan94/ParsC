#include "FileLinker.h"

#include "FileData.h"

FileLinker::FileLinker(const char * _file_path)
{
	findOtherFiles(_file_path);
}

FileLinker::FileLinker(std::vector<std::string> _files)
{
	for (auto &f : _files)
	{
		FileData file(f.c_str());
		f_data += file.data();
		f_data += "\n\n";
	}
}

FileLinker::~FileLinker()
{
}

void FileLinker::findOtherFiles(const char * _filepath)
{
	FileData file(_filepath);
	f_data += file.data();
	f_data += "\n\n";
	for (auto &l : file.dataLines())
	{
		if (l.find("#include") != std::string::npos) {
			size_t s_pos = l.find_first_of('"') + 1;
			size_t e_pos = l.find_last_of('"');
			findOtherFiles(l.substr(s_pos, e_pos - s_pos).c_str());
		}
	}
}
 