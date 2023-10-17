#include "CppResource.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>

namespace omnia
{
	namespace common
	{
		bool CppResource::create(std::string file_path, std::string hpp_file_path, std::string resource_name, bool encode_extension)
		{
			std::filesystem::path p(file_path);
			std::string ext = p.extension();
			
			byte* buffer = nullptr;
		 
		 	//open file
			std::ifstream infile(file_path);
			
			//get length of file
			infile.seekg(0, std::ios::end);
			unsigned int length = infile.tellg();
			if (encode_extension)
				length += ext.length() + 1;
			buffer = new byte[length];
			infile.seekg(0, std::ios::beg);
			
			if (encode_extension)
			{
				buffer[0] = ext.length();
				for (unsigned char i = 0; i < ext.length(); i++)
					buffer[i + 1] = ext[i];
			}

			//read file
			if (encode_extension)
				infile.read(buffer + ext.length() + 1, length);
			else
				infile.read(buffer, length);

			infile.close();
			
			CppResource::createCppFile(length, buffer, hpp_file_path, resource_name);
			if (!encode_extension)
				std::cout << "Warning: extension_encoding is disabled: the resulting .hpp file cannot be loaded as a file with CppResource::load, it will have to be loaded manually.\n";
			
			delete[] buffer;
		 	return true; //TODO: Error checking
		}
		
		bool CppResource::load(std::string file_path, const char* resource_buffer, unsigned int size)
		{
			unsigned char ext_len = resource_buffer[0];
			std::string ext = "";
			for (unsigned char i = 0; i < ext_len; i++)
				ext += (char)(resource_buffer[i + 1]);
		 	std::fstream bin (file_path + ext, std::ios::out | std::ios::binary);
			bin.write(resource_buffer + ext_len + 1, size - ext_len - 1);
			bin.close();
			return true; //TODO: Error checking
		}
		
		bool CppResource::createCppFile(unsigned int length, byte* buffer, std::string hpp_file_path, std::string resource_name)
		{
		 	unsigned long row_length = 20;
		 
		 	std::ostringstream str;
		 	std::string include_guard = "__" + resource_name + "_HPP__";
		 	str << "#ifndef " << include_guard << "\n";
		 	str << "#define " << include_guard << "\n\n";
		 	
		 	str << "struct " << resource_name << "_t {\n";
		 	str << "\tconst unsigned int size = " << (unsigned int)length << ";\n";
		 	str << "\tconst unsigned char data[" << (unsigned int)length << "] = {\n\t\t";
		 	
		 	for (unsigned int i = 0; i < length; i++)
		 	{
		 		if ((i + 1) % row_length == 0)
		 			str << "\n\t\t";
		 		str << (int)(unsigned char)buffer[i];
		 		if (i < length - 1)
		 			str << ", ";
		 	}
		 	
		 	str << "\n\t};\n};\n";
		 	str << resource_name << "_t " << resource_name << ";\n";
		 	str << "\n#endif\n";
		 	
		 	std::ofstream outFile;
		 	outFile.open(hpp_file_path + ".hpp");
		 	outFile << str.str();
		 	outFile.close();
		 	
		 	return true; //TODO: Error checking
		}
	}
}
