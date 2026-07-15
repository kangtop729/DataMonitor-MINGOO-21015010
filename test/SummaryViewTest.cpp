#include <gtest/gtest.h>
#include <sstream>
#include "View/SummaryView.h"

TEST(SummaryViewTest, ShowAllPrintsEachItem)
{
    std::ostringstream out;
    SummaryView view(out);
    std::vector<Item> items = { {1, "Widget", 10}, {2, "Gadget", 3} };

    view.ShowAll(items);

    EXPECT_NE(out.str().find("Widget"), std::string::npos);
    EXPECT_NE(out.str().find("Gadget"), std::string::npos);
}

TEST(SummaryViewTest, ShowAllOnEmptyListPrintsNothing)
{
    std::ostringstream out;
    SummaryView view(out);

    view.ShowAll({});

    EXPECT_TRUE(out.str().empty());
}

TEST(SummaryViewTest, ShowSummaryPrintsTotalCountAndQuantity)
{
    std::ostringstream out;
    SummaryView view(out);
    std::vector<Item> items = { {1, "Widget", 10}, {2, "Gadget", 3} };

    view.ShowSummary(items);

    EXPECT_NE(out.str().find("2"), std::string::npos);
    EXPECT_NE(out.str().find("13"), std::string::npos);
}
