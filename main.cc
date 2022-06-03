// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#endif

#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
using namespace std;

#include "operation/xmlfile.h"

/*
 * Main function will list all file from ./resource folder and read all xml files
 * and convert it to arrow table
 */
const char *inputPath = "./resource/";
const char *outputPath = "./output/";
int main()
{
    DIR *dr;
    struct dirent *en;
    dr = opendir(inputPath); // open all directory
    if (dr)
    {
        while ((en = readdir(dr)) != NULL)
        {
            cout << " \n"
                 << en->d_name; // print all directory name

            string filename = string(en->d_name);
            if (filename.find(".xml") == std::string::npos)
            {
                std::cout << "Not xml file, ignore..." << '\n';
                continue;
            }

            // Open each valid xml file
            ifstream input;
            string filepath = string(inputPath) + string(en->d_name);
            input.open(filepath);

            XMLFile *xmlFile = new XMLFile();

            // Set output filename and begin to convert
            string outputfile = string(outputPath) + string(en->d_name) + ".arrow";
            xmlFile->convert(input, outputfile);

            // close the opened file.
            input.close();
        }
        closedir(dr); // close all directory
    }
    return 0;
}
