#include "CppResource.hpp"
#include <string.h>
 
 int main(int argc, char** argv)
 {
 	if (argc < 4)
 	{
 		std::cout << "\nError: Invalid arguments.\n";
 		std::cout << "Usage: <file> <out_hpp_file> <resource_name> [options]\n";
		std::cout << "Available options: \n";
		std::cout << "   [--exclude-extension]: Disables extension encoding in the output .hpp file.\n\n";
 		return 1;
 	}
 	std::string file_path = argv[1];
 	std::string hpp_file_path = argv[2];
 	std::string res_name = argv[3];

	bool encode_extension = true;
	if (argc > 4)
	{
		for (int32_t i = 4; i < argc; i++)
		{
			if (strcmp(argv[i], "--exclude-extension") == 0)
				encode_extension = false;
			else
				std::cout << "Unknown Option: " << argv[i] << "\n";
		}
	}
 	
 	if (omnia::common::CppResource::create(file_path, hpp_file_path, res_name, encode_extension))
 	{
 		std::cout << "Created <" << hpp_file_path << ".hpp> file successfully.\n";
 		return 0;
 	}
 	return 2;
 }
