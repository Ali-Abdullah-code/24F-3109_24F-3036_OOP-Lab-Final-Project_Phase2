#include "StrongHold.h"

void TradeSystem::legalTrade(Kingdom &from, Kingdom &to, string resource, int amount)
{
    try
    {
        Resource &resFrom = from.getResource(resource);
        Resource &goldTo = to.getResource("Gold");

        if (resFrom.getAmount() < amount)
        {
            throw "Not enough " + resource + "!";
        }

        resFrom.consume(amount);
        goldTo.setAmount(goldTo.getAmount() + (amount * 2));
        logTrade(from.getName(), to.getName(), resource, amount, false);
    }
    catch (const string &error)
    {
        cout << "\033[31m" << error << "\033[0m" << endl; // Print in red
    }
}

void TradeSystem::smuggle(Kingdom &from, Kingdom &to, string resource, int amount)
{
    try
    {
        if ((rand() % 100) < (SMUGGLE_RISK * 100))
        {
            throw "Smuggling detected! Resources confiscated!";
        }
        Resource &resFrom = from.getResource(resource);
        Resource &resTo = to.getResource(resource);

        resFrom.consume(amount);
        resTo.setAmount(resTo.getAmount() + amount);
        logTrade(from.getName(), to.getName(), resource, amount, true);
    }
    catch (const char *error)
    {
        cout << "\033[31m" << error << "\033[0m" << endl; // Print in red
        from.getResource("Gold").consume(amount);
    }
}

void TradeSystem::logTrade(const string &from, const string &to, const string &res, int amt, bool isSmuggle)
{
    ofstream logFile("trade_log.txt", ios::app);
    if (logFile.is_open())
    {
        logFile << "[" << (isSmuggle ? "SMUGGLE" : "TRADE") << "] "
                << from << " -> " << to << ": "
                << amt << " " << res << "\n";
        logFile.close();
    }
}