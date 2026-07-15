#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include "Repository/JsonItemReader.h"

namespace
{
    std::filesystem::path MakeTempFilePath()
    {
        return std::filesystem::temp_directory_path() / "DataMonitorTest_items.json";
    }

    void WriteRawJson(const std::string& path, const std::string& content)
    {
        std::ofstream file(path);
        file << content;
    }
}

class JsonItemReaderTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        filePath = MakeTempFilePath().string();
        std::filesystem::remove(filePath);
    }

    void TearDown() override
    {
        std::filesystem::remove(filePath);
    }

    std::string filePath;
};

TEST_F(JsonItemReaderTest, FindAllOnMissingFileReturnsEmptyList)
{
    JsonItemReader reader(filePath);

    EXPECT_TRUE(reader.FindAll().empty());
}

TEST_F(JsonItemReaderTest, FindAllReturnsItemsFromFile)
{
    WriteRawJson(filePath, R"([{"id":1,"name":"Widget","quantity":10}])");
    JsonItemReader reader(filePath);

    auto items = reader.FindAll();

    ASSERT_EQ(items.size(), 1u);
    EXPECT_EQ(items[0].id, 1);
    EXPECT_EQ(items[0].name, "Widget");
    EXPECT_EQ(items[0].quantity, 10);
}

TEST_F(JsonItemReaderTest, FindAllReflectsFileChangesBetweenCalls)
{
    WriteRawJson(filePath, R"([{"id":1,"name":"Widget","quantity":10}])");
    JsonItemReader reader(filePath);

    ASSERT_EQ(reader.FindAll().size(), 1u);

    WriteRawJson(filePath, R"([{"id":1,"name":"Widget","quantity":10},{"id":2,"name":"Gadget","quantity":3}])");

    EXPECT_EQ(reader.FindAll().size(), 2u);
}

TEST_F(JsonItemReaderTest, LoadingCorruptedFileThrows)
{
    WriteRawJson(filePath, "{ not valid json ");
    JsonItemReader reader(filePath);

    EXPECT_THROW(reader.FindAll(), std::runtime_error);
}
