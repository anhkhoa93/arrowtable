#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <arrow/csv/api.h>
#include <arrow/io/api.h>
#include <arrow/ipc/api.h>
#include <arrow/pretty_print.h>
#include <arrow/result.h>
#include <arrow/status.h>
#include <arrow/table.h>
#include <arrow/json/api.h>
#include <arrow/buffer.h>

#include "filetype.h"

using arrow::Status;
using namespace std;

/**
 * Operation class have operation to convert xml file to arrow table object
 */
class XMLFile : FileType
{
private:
    /**
     * table is the object that create from source (xml)
     */
    std::shared_ptr<arrow::Table> table;

public:
    /**
     * Default constructor for XMLFile.
     */
    XMLFile();

    /**
     * Convert an input file with format XML to arrow table
     * Returns true if the conversion is success
     */
    bool convert(const ifstream &input, string outputFileName);
};
