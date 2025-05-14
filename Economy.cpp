#include "Stronghold.h"

Economy::Economy()
{
    treasury = 0;
    taxRate = 10;
    inflation = 0;
    servicesCost = 0;
}

Economy::Economy(int initialTreasury)
{
    treasury = initialTreasury;
    taxRate = 10;
    inflation = 0;
    servicesCost = treasury / 10;
}

int Economy::getTreasury() const
{
    return treasury;
}

int Economy::getTaxRate() const
{
    return taxRate;
}

int Economy::getInflation() const
{
    return inflation;
}

int Economy::getServicesCost() const
{
    return servicesCost;
}

void Economy::setTreasury(int amount)
{
    treasury = amount;
    if (treasury < 0)
    {
        treasury = 0;
    }
}

void Economy::setTaxRate(int rate)
{
    taxRate = rate;
    if (taxRate < 0)
    {
        taxRate = 0;
    }
    else if (taxRate > 50)
    {
        taxRate = 50;
    }
    if (taxRate > 30)
    {
        inflation += 2;
    }
    else if (taxRate < 10)
    {
        inflation -= 1;
    }
    if (inflation < 0)
    {
        inflation = 0;
    }
    else if (inflation > 100)
    {
        inflation = 100;
    }
}

void Economy::collectTaxes(int amount)
{
    double inflationEffect = 1.0 - (inflation / 100.0);
    int adjustedAmount = static_cast<int>(amount * inflationEffect);
    treasury += adjustedAmount;
    if (treasury < 0)
    {
        treasury = 0;
    }
}

bool Economy::spendGold(int amount)
{
    double inflationEffect = 1.0 + (inflation / 100.0);
    int adjustedAmount = static_cast<int>(amount * inflationEffect);
    if (treasury >= adjustedAmount)
    {
        treasury -= adjustedAmount;
        return true;
    }
    return false;
}

void Economy::updateInflation()
{
    if (treasury > 10000)
    {
        inflation += 2;
    }
    else if (treasury > 5000)
    {
        inflation += 1;
    }
    if (taxRate < 10 && treasury < 5000)
    {
        inflation -= 1;
    }
    if (inflation < 0)
    {
        inflation = 0;
    }
    else if (inflation > 100)
    {
        inflation = 100;
    }
}

void Economy::updateServicesCost()
{
    int baseCost = treasury / 10;
    double inflationEffect = 1.0 + (inflation / 100.0);
    servicesCost = static_cast<int>(baseCost * inflationEffect);
    spendGold(servicesCost);
}
