#pragma once

#include <string>
#include "Repository/IItemReader.h"

class JsonItemReader : public IItemReader
{
public:
    explicit JsonItemReader(std::string filePath);

    std::vector<Item> FindAll() const override;

private:
    std::string filePath;
};
