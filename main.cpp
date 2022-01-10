#include "CppResource.hpp"
 
 int main(int argc, char** argv)
 {
 	if (argc != 4)
 	{
 		std::cout << "\nError: Invalid arguments.\n";
 		std::cout << "Usage: <file> <out_hpp_file> <resource_name>\n\n";
 		return 1;
 	}
 	std::string file_path = argv[1];
 	std::string hpp_file_path = argv[2];
 	std::string res_name = argv[3];
 	
 	if (omnia::common::CppResource::create(file_path, hpp_file_path, res_name))
 	{
 		std::cout << "Created <" << hpp_file_path << ".hpp> file successfully.\n";
 		return 0;
 	}
 	return 2;
 }
