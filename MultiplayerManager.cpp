#include "Stronghold.h"
#include <limits>

void MultiplayerManager::setupPlayers()
{
    system("cls");
    while (playerCount < 2 || playerCount > MAX_PLAYERS)
    {
        cout << "Enter number of players (2-4): ";
        if (!(cin >> playerCount) || playerCount < 2 || playerCount > MAX_PLAYERS)
        {
            cout << "Please enter a number between 2 and 4.\n";
            cin.clear();
        }
    }
    cin.ignore();

    for (int i = 0; i < playerCount; i++)
    {
        string name;
        bool validName = false;
        while (!validName)
        {
            cout << "Player " << (i + 1) << " name: ";
            getline(cin, name);
            if (name.empty())
            {
                cout << "Name cannot be empty.\n";
                continue;
            }
            validName = true;
            for (int j = 0; j < i; j++)
            {
                if (kingdoms[j].getName() == name)
                {
                    cout << "Name must be unique.\n";
                    validName = false;
                    break;
                }
            }
        }
        kingdoms[i] = Kingdom(name);
    }
}

void MultiplayerManager::nextTurn()
{
    currentPlayer = (currentPlayer + 1) % playerCount;
    if (currentPlayer == 0)
    {
        totalTurns++;
        processGlobalEvents();
    }
}

Kingdom *MultiplayerManager::getCurrentKingdom()
{
    return &kingdoms[currentPlayer];
}

Kingdom *MultiplayerManager::getKingdom(int index)
{
    if (index >= 0 && index < playerCount)
    {
        return &kingdoms[index];
    }
    return nullptr;
}

void MultiplayerManager::displayOtherKingdoms()
{
    cout << "\nOther Kingdoms:\n";
    for (int i = 0; i < playerCount; i++)
    {
        if (i != currentPlayer)
        {
            cout << "[" << (i + 1) << "] " << kingdoms[i].getName() << "\n";
        }
    }
}

void MultiplayerManager::processGlobalEvents()
{
    if (totalTurns % 3 == 0)
    {
        cout << "\n=== GLOBAL MARKET FLUCTUATION ===\n";
        for (int i = 0; i < playerCount; i++)
        {
            kingdoms[i].getResource("Gold").setAmount(kingdoms[i].getResource("Gold").getAmount() * 11 / 10);
        }
        cout << "All kingdoms gained 10% gold!\n";
        pressAnyKey();
    }
}

void MultiplayerManager::saveGameState()
{
    bool success = true;
    for (int i = 0; i < playerCount; i++)
    {
        string filename = "save_" + kingdoms[i].getName() + ".txt";
        if (!kingdoms[i].saveGame(filename))
        {
            success = false;
        }
    }
    if (!success)
    {
        cout << "Warning: Some kingdoms failed to save.\n";
    }
}

int MultiplayerManager::getPlayerCount()
{
    return playerCount;
}

int MultiplayerManager::getCurrentPlayerIndex()
{
    return currentPlayer;
}