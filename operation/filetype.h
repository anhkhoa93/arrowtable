#pragma once
#include <string>
using namespace std;
class FileType {
    private:
        /**
         * Header of the file, can be empty
         */
        string header = "";

        /**
         * Format of the file (json, xml,...)
         */
        string fileformat;

    public:
        // TODO: split implementation to .cc file
        /**
         * Get file header
         */        
        string getHeader() {
            return this->header;
        }
        
        /**
         * Set file header
         */
        void setHeader(string header) {
            this->header = header;
        }

        /**
         * Get file format
         */
        string getFileFormat() {
            return this->fileformat;
        }

        /**
         * Set file format
         */
        void setFileFormat(string fileformat) {
            this->fileformat = fileformat;
        }
};
