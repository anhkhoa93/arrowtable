#include "../operation/xmlfile.h"

#include "gtest/gtest.h"

class XMLFileTest : public ::testing::Test
{
protected:
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
    // Class members declared here can be used by all tests in the test suite
    // for Foo.
};

TEST_F(XMLFileTest, MethodConvertSuccess)
{
    const std::string input_filepath = "resource/01.xml";

    XMLFile *xml = new XMLFile();
    ifstream input;
    input.open(input_filepath);
    string outputfile = "tests/01.xml.arrow";
    bool result = xml->convert(input, outputfile);
    EXPECT_EQ(result, true);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}