#ifndef __CPP_RESOURCE_HPP__
#define __CPP_RESOURCE_HPP__

#include <iostream>
 
namespace omnia
{
	namespace common
	{
 		typedef char byte;
 		
		class CppResource
		{
			public:
				static bool create(std::string file_path, std::string hpp_file_path, std::string resource_name, bool encode_extension = true);
				static bool load(std::string file_path, const char* resource_buffer, unsigned int size);
				
			private:
				static bool createCppFile(unsigned int length, byte* buffer, std::string hpp_file_path, std::string resource_name);
		};
	}
}

#endif
