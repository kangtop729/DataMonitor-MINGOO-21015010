#include "SummaryView.h"

SummaryView::SummaryView(std::ostream& out)
    : output(out)
{
}

void SummaryView::ShowAll(const std::vector<Item>& items) const
{
    for (const auto& item : items)
    {
        output << "[" << item.id << "] " << item.name << " x" << item.quantity << "\n";
    }
}

void SummaryView::ShowSummary(const std::vector<Item>& items) const
{
    int totalQuantity = 0;
    for (const auto& item : items)
    {
        totalQuantity += item.quantity;
    }

    output << "Total items: " << items.size() << ", Total quantity: " << totalQuantity << "\n";
}
