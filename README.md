# A simple tool to convert any file into an *.hpp file

This is a simple tool that takes as input any file, and generates an *.hpp file containing 
a byte array, that you can include in any C++ project, in order to store a resource inside your 
executable file. The `CppResource` class also provides a method to restore a file from a byte array.
   
   
The tool is very simple to use: just open a terminal (or cmd) where the executable is, and run:
   
Linux
```
./CppResourceMaker [input_file] [output_file] [resource_name]
```
Windows
```
CppResourceMaker.exe [input_file] [output_file] [resource_name]
```
where **[input_file]** is the relative path to the file you want to create the header file from, 
**[output_file]** is the relative path (without extension) of the *.hpp file to generate, and 
**[resource_name]** is the name of the byte array inside the header file.
   
The generated file contains simple header-guards to avoid multiple inclusions, and it also 
contains the byte array, in this format:
```
struct resource_name_t {
	const unsigned int size = /**  SIZE  **/;
	const char data[/**  SIZE  **/] = {
		/**  BYTES  **/
	};
};
resource_name_t resource_name;
```
This provides a **resource_name** object, by including the header file in a project.
   
In a project where you include such a resource file, you can easily also include **CppResource.cpp** 
and **CppResource.hpp**, in order to use this functionality
```
omnia::common::CppResource::load(omnia::common::String output_file_path, const char* resource_buffer, unsigned long size);
```
to re-construct the original file. The extension is automatically stored in the data, so the **output_file_path** must
be passed without any extension.

# Example (Linux)

Let's say you have a file called **image.png** inside the same directory as the program, and want to create 
a header file for it. First thing would be to generate the header file, by using the command:
```
./CppResourceMaker image.png ImageHeaderFile some_image
```

this will generate a header file named **SomeImage.hpp** with resource-name **some_image**, in the same directory
of the program.
    
Now, this is the code you would use to restore the original file:
```
#include "CppResource.hpp"
#include "SomeImage.hpp"
 
int main(int argc, char** argv)
{
	omnia::common::CppResource::load("restoredImage", some_image.data, some_image.size);
	return 0;
}
```
This would create a file called **restoredImage.png** inside the working directory of the program. Keep in mind
 that this tool is not limited to Image files, and can be used to convert any type of file into a C++ header file.
   
This little tool is part of the OmniaFramework library.

