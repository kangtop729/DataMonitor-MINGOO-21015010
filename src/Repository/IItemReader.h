#pragma once

#include <vector>
#include "Model/Item.h"

class IItemReader
{
public:
    virtual ~IItemReader() = default;

    virtual std::vector<Item> FindAll() const = 0;
};
