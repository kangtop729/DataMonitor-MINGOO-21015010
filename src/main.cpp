#ifdef _DEBUG
#include <gtest/gtest.h>
#else
#include <iostream>
#include <string>
#include "Repository/JsonItemReader.h"
#include "View/SummaryView.h"

namespace
{
    void ShowCurrentData(const JsonItemReader& reader, const SummaryView& view)
    {
        const auto items = reader.FindAll();
        view.ShowAll(items);
        view.ShowSummary(items);
    }
}
#endif

int main(int argc, char** argv)
{
#ifdef _DEBUG
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    JsonItemReader reader("items.json");
    SummaryView view;

    std::cout << "DataMonitor PoC (read-only viewer)\n";
    ShowCurrentData(reader, view);

    std::string command;
    while (true)
    {
        std::cout << "\nCommand (r=refresh, q=quit): ";
        if (!(std::cin >> command) || command == "q")
        {
            break;
        }

        if (command == "r")
        {
            ShowCurrentData(reader, view);
        }
        else
        {
            std::cout << "Unknown command.\n";
        }
    }

    return 0;
#endif
}
