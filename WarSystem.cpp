#include "Stronghold.h"

void WarSystem::declareWar(const string &attacker, const string &defender)
{
    for (int i = 0; i < MAX_KINGDOMS; i++)
    {
        if (warStatus[i].empty())
        {
            warStatus[i] = attacker + " vs " + defender;
            cout << attacker << " has declared war on " << defender << "!\n";
            logEvent(attacker + " declared war on " + defender);
            break;
        }
    }
}

void WarSystem::resolveBattle(Kingdom &attacker, Kingdom &defender)
{
    int attackerStrength = attacker.getMilitary().calculateStrength();
    int defenderStrength = defender.getMilitary().calculateStrength();

    cout << attacker.getName() << " (Strength: " << attackerStrength << ") vs "
         << defender.getName() << " (Strength: " << defenderStrength << ")\n";

    if (attackerStrength > defenderStrength)
    {
        int damage = (attackerStrength - defenderStrength) / 10;
        defender.getMilitary().setSoldiers(defender.getMilitary().getSoldiers() - damage);
        attacker.getMilitary().changeMorale(10);
        defender.getMilitary().changeMorale(-10);
        cout << attacker.getName() << " wins the battle! " << defender.getName()
             << " loses " << damage << " soldiers.\n";
        logEvent(attacker.getName() + " defeated " + defender.getName() + " in battle");
    }
    else if (defenderStrength > attackerStrength)
    {
        int damage = (defenderStrength - attackerStrength) / 10;
        attacker.getMilitary().setSoldiers(attacker.getMilitary().getSoldiers() - damage);
        defender.getMilitary().changeMorale(10);
        attacker.getMilitary().changeMorale(-10);
        cout << defender.getName() << " wins the battle! " << attacker.getName()
             << " loses " << damage << " soldiers.\n";
        logEvent(defender.getName() + " defeated " + attacker.getName() + " in battle");
    }
    else
    {
        cout << "The battle is a stalemate!\n";
        attacker.getMilitary().changeMorale(-5);
        defender.getMilitary().changeMorale(-5);
        logEvent("Stalemate between " + attacker.getName() + " and " + defender.getName());
    }

    if (defender.getMilitary().getSoldiers() < 0)
    {
        defender.getMilitary().setSoldiers(0);
    }
    if (attacker.getMilitary().getSoldiers() < 0)
    {
        attacker.getMilitary().setSoldiers(0);
    }
}

void WarSystem::logEvent(const string &message)
{
    cout << "War Log: " << message << endl;
}