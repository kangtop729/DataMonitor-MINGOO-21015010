#include "JsonItemReader.h"

#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include "Serialization/ItemSerialization.h"

JsonItemReader::JsonItemReader(std::string filePath)
    : filePath(std::move(filePath))
{
}

std::vector<Item> JsonItemReader::FindAll() const
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        return {};
    }

    nlohmann::json j;
    try
    {
        file >> j;
    }
    catch (const nlohmann::json::parse_error&)
    {
        throw std::runtime_error("Failed to parse JSON file: " + filePath);
    }

    return j.get<std::vector<Item>>();
}
