#include "FileData.h"
#pragma once
class FileLinker
{
	std::string f_data;
public:
	static enum class e_target { C_DIR };
	FileLinker(const char *_file_path);
	FileLinker(std::vector<std::string> _files);
	~FileLinker();

	inline const std::string& getData() const { return f_data; }
private:
	void findOtherFiles(const char *_filepath);
};

