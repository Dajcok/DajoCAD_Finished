#include "exportOBJ.h"
#include <iostream>
#include <fstream>
#include <iostream>

void exportOBJ::exportObj(GLfloat verticies[], int size, int start, std::string path)
{
	int index = 0;
	int fragmentindex = start;
	bool firstRun = true;
	bool writeFi = false;

	std::cout << size << std::endl;

	std::ofstream *myfile = nullptr;

	if (start == 1) 
	{
		myfile = new std::ofstream(path + ".obj");
		*myfile << "v ";
	}
	else
	{
		myfile = new std::ofstream(path + ".obj", std::ofstream::app);
		*myfile << "\nv ";
	}

	while (true)
	{
		if (!writeFi)
		{
			*myfile << verticies[index] << " ";
			index++;
			if (size == index)
			{
				fragmentindex++;
				*myfile << "\nf " << fragmentindex - 2 << " " << fragmentindex - 1 << " " << fragmentindex;
				break;
			}
				

			if (index % 9 == 0)
				writeFi = true;
			
			else if ((index) % 3 == 0)
			{
				fragmentindex++;
				*myfile << "\nv ";
			}				
		}

		else
		{
			if (!firstRun)
				fragmentindex++;
			*myfile << "\nf " << fragmentindex - 2 << " " << fragmentindex - 1 << " " << fragmentindex << "\nv ";
			writeFi = false;
			firstRun = false;
		}
			
	}

	myfile->close();
}
