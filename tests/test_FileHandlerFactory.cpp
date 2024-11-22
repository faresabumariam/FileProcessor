#include <gtest/gtest.h>
#include "FactoryUtils.h"

TEST(UtilityTest, ExtractsExtension) {
    EXPECT_EQ(getExtension("file.csv"), "csv");
    EXPECT_EQ(getExtension("file.json"), "json");
    EXPECT_EQ(getExtension("file"), "");
}
TEST(UtilityTest, HandlesEdgeCases) {
    EXPECT_EQ(getExtension("file.with.multiple.dots.json"), "json");  // Valid case
    EXPECT_EQ(getExtension("file.with.dots.txt"), "txt");  // Valid case
    EXPECT_EQ(getExtension(".hidden.json"), "json");  // Hidden file with extension
    EXPECT_EQ(getExtension(".hiddenfile"), "");  // Hidden file, no extension
    EXPECT_EQ(getExtension("file"), "");  // No dot, no extension
    EXPECT_EQ(getExtension("file."), "");  // Dot at the end, no extension
}

TEST(FileHandlerFactoryTest, ReturnsCorrectFactoryForCSV) {
    auto factory = getFactory("sample.csv");
    EXPECT_TRUE(dynamic_cast<CSVHandlerFactory*>(factory.get()) != nullptr);
}

TEST(FileHandlerFactoryTest, ReturnsCorrectFactoryForJSON) {
    auto factory = getFactory("sample.json");
    EXPECT_TRUE(dynamic_cast<JSONHandlerFactory*>(factory.get()) != nullptr);
}

TEST(FileHandlerFactoryTest, ThrowsForUnsupportedFileType) {
    EXPECT_THROW(getFactory("file.txt"), std::invalid_argument);
}

