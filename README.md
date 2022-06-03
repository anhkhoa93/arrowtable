# XML to arrow table object conversion

This project have the feature of parsing a list of XML files (in folder ./resource)
into a Apache arrowtable object.

It'll print the arrow table object and store the object to arrow file format (./output/<inputfile>.xml.arrow)

NOTE: The application running using docker container. For natively run on host machine, pls setup your own environment and add dependancy in:
- https://arrow.apache.org/install/
- arrow-env.dockerfile

## Structure
``` 
.
├── README.md => Project description
├── Dockerfile => Main dockerfile to build and run the main container
├── docker-compose.yml => Execute the main container
├── CMakeLists.txt => CMake file to build the image of main container
├── run.sh => Entrypoint to run the main container
├── arrow-env.dockerfile => Build the environment with all dependancy
├── resource => Store input xml files
├── output => Store output .arrow files after parsing (available on the main container only)
├── main.cpp => Entrypoint of the program
├── operation => Store the implementation of the logic conversion
│   └── filetype.h => Abtract class
│   └── xmlfile.h => Convert operation for XMLFile class
│   └── xmlfile.cc => Implementation
│   └── ... (Other external lib and code)...
└── tests
    ├── CMakeLists.txt => Build using gtest framework
    └── operation.cc => Unit test 
```
## Services
Service name: arrowtable
executable file: ./arrow-table

The service will read all files in ./resource folder, find valid xml files, and convert to json object, 
then convert the json object to arrow::Buffer, and then arrow::Table. Then it prints out the table and also store the table as .arrow file format in ./output folder
This all happen in container, so the service is available to deploy cross-platform using docker. 

## Setup
### Prerequisite
- Docker installed (Version use in stage is 17.03.1-ce-rc1-win3, pls find version for Linux/MacOS that nearly equal to this version)
- Had image arrowtable:latest that contain all built and dependancy
Pls download (this is public image available on hub.docker.com):
```docker pull hnakhoa93/arrowtable:latest```

### Build
- No need if we run directly from the image 


### RUN
```docker-compose up```

* Note: To verify output, can exec to the container and run the binary manually, the result in ./output folder
docker run -it hnakhoa93/arrowtable:latest bash
./arrow-table

### Rebuild on changes
- Build the image arrowtable for the main container:
```
cd ${WORKING_DIR}
docker build -t arrowtable:latest .
```

- Build the image arrow-env for the environment (that contain all arrow dependancy and gtest dependancy). This image use as base image to build arrowtable
```docker build -t arrow-env:latest -f ./arrow-env.dockerfile .```


## References:
* arrow::Table: https://arrow.apache.org/docs/cpp/api/table.html#_CPPv4N5arrow5TableE
* Dependencies: https://github.com/apache/arrow/tree/master/cpp
* Input XML (with modification): https://www.w3schools.com/xml/xml_tree.asp

## Improvement Note
- Need to have valid check of xml content
- Start multithread if there is a lots of files to process
- Need to handle case where file is extremely large

## Feature checklist
Requirements: -> done
* Without information loss (except the xml header line) -> done
* With stable/modern C++ standard -> done
* Build script -> done

Plus point:
* Document/Improvement Notes -> done
* Unit-Test -> done
* Linter -> done
