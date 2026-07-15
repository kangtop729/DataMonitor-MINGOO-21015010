#pragma once

#include <iostream>
#include <vector>
#include "Model/Item.h"

class SummaryView
{
public:
    explicit SummaryView(std::ostream& out = std::cout);

    void ShowAll(const std::vector<Item>& items) const;
    void ShowSummary(const std::vector<Item>& items) const;

private:
    std::ostream& output;
};
