#include "Stronghold.h"

void DiplomacySystem::addAlly(const string &kingdom)
{
    for (int i = 0; i < numAllies; i++)
    {
        if (allies[i] == kingdom)
        {
            cout << kingdom << " is already an ally.\n";
            return;
        }
    }
    if (numAllies < MAX_ALLIES)
    {
        allies[numAllies++] = kingdom;
    }
    else
    {
        cout << "Maximum number of allies reached.\n";
    }
}

void DiplomacySystem::addMessage(const string &msg)
{
    if (messageCount < MAX_MESSAGES)
    {
        messages[messageCount++] = msg;
    }
    else
    {
        cout << "Message limit reached.\n";
    }
}

void DiplomacySystem::displayAllies() const
{
    if (numAllies == 0)
    {
        cout << "No allies yet.\n";
    }
    else
    {
        cout << "\nAllies: ";
        for (int i = 0; i < numAllies; i++)
        {
            cout << allies[i];
            if (i < numAllies - 1)
                cout << ", ";
        }
        cout << "\n";
    }
}

void DiplomacySystem::displayMessages() const
{
    if (messageCount == 0)
    {
        cout << "No messages.\n";
    }
    else
    {
        cout << "\n=== MESSAGES ===\n";
        for (int i = 0; i < messageCount; i++)
        {
            cout << "- " << messages[i] << "\n";
        }
    }
}