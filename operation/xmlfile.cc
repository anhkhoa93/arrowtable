#include "xmlfile.h"
#include "xml2json.hpp"

/**
 * Convert an input file with format XML to arrow table
 * Returns true if the conversion is success
 */
bool XMLFile::convert(const ifstream &input, string outputFileName)
{
    ostringstream oss;
    // Read the input file and convert it to json string
    oss << input.rdbuf();

    // cout << "xml:" << oss.str().data() << endl;
    string header = "";
    auto json_str = xml2json(oss.str().data(), &header);
    this->setHeader(header);
    cout << "File header:" << this->getHeader() << endl;

    cout << json_str << endl;

    auto src = std::make_shared<arrow::Buffer>(json_str);
    auto inputStream = std::make_shared<arrow::io::BufferReader>(src);
    // Conver the json json to Arrow table object
    arrow::Status st;

    auto read_options = arrow::json::ReadOptions::Defaults();
    auto parse_options = arrow::json::ParseOptions::Defaults();

    // Instantiate TableReader from inputbuffer stream and options
    auto result = arrow::json::TableReader::Make(arrow::default_memory_pool(), inputStream, read_options,
                                                 parse_options);

    auto reader = std::move(result).ValueOrDie();

    // Read table from JSON file
    auto tableResult = reader->Read();
    auto table = std::move(tableResult).ValueOrDie();

    // Print the arrow table to confirm it parse successfully
    arrow::PrettyPrint(*table, {}, &std::cerr);
    this->table = table; // For further usage in the future

    // Write the arrow table to file
    auto output_file = arrow::io::FileOutputStream::Open(outputFileName).ValueOrDie();
    auto batch_writer = arrow::ipc::MakeFileWriter(output_file.get(), table->schema()).ValueOrDie();
    batch_writer->WriteTable(*table);
    batch_writer->Close();

    return true;
}

XMLFile::XMLFile()
{
    // Do init
}