#include "Stronghold.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <limits>



#ifdef _WIN32
#include <windows.h>
#define ENABLE_COLOR
#else
#define COLOR_RED ""
#define COLOR_GREEN ""
#define COLOR_YELLOW ""
#define COLOR_CYAN ""
#define COLOR_WHITE ""
#endif

void printColored(const string &text, int colorCode);
void printHeader(const string &title);
void pressAnyKey();
void mapMenu(Kingdom *kingdom, TextMap &worldMap);
void diplomacyMenu(Kingdom *kingdom, MultiplayerManager &mp);
void tradeMenu(Kingdom *current, MultiplayerManager &mp);

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    system("cls");
    printColored(R"(
        _____  _____  _____   _____  _   _   _____  _   _   _____  _      _____ 
       /  ___||_   _||  _  \ /  _  \| \ | | /  ___|| | | | /  _  \| |    |  _  \
       | |___   | |  | |_| | | | | ||  \| | | |  _ | |_| | | | | || |    | | | |
       \___  \  | |  |  _  / | | | || . ` | | | | ||  _  | | | | || |    | | | |
        ___| |  | |  | | \ \ | |_| || |\  | | |_| || | | | | |_| || |___ | |_| |
       /_____/  |_|  |_|  \_\/____/ |_| \_| \_____||_| |_| \____/ |_____||_____/
       )",
                 COLOR_CYAN);
    cout << "\n\n";
    printColored("Press any key to start your reign...", COLOR_YELLOW);
    _getch();

    MultiplayerManager mp;
    mp.setupPlayers();

    TextMap worldMap;
    Event events[9];
    events[0] = Event("Plague", "A terrible plague has struck your kingdom!", -20, "population");
    events[1] = Event("Bountiful Harvest", "The farmers report an excellent harvest!", 15, "economy");
    events[2] = Event("Foreign Invasion", "A neighboring kingdom has attacked your borders!", -30, "military");
    events[3] = Event("Trade Agreement", "You've secured a profitable trade agreement!", 300, "economy");
    events[4] = Event("Royal Wedding", "The royal wedding has boosted your popularity!", 25, "leadership");
    events[5] = Event("Gold Mine Discovery", "A new gold mine has been discovered!", 500, "economy");
    events[6] = Event("Military Victory", "Your troops have won a decisive victory!", 20, "military");
    events[7] = Event("Diplomatic Mission", "A diplomatic mission has improved relations!", 10, "leadership");
    events[8] = Event("War", "A war has occurred!", -12, "military");

    bool running = true;
    while (running)
    {
        Kingdom *currentKingdom = mp.getCurrentKingdom();
        system("cls");
        printHeader("KINGDOM OF " + currentKingdom->getName());
        currentKingdom->displayStatus();

        printColored("\n=== ROYAL DECREES ===\n", COLOR_CYAN);
        cout << "[1] Boost Farms (+10 Food Production, 50 gold)\n"
             << "[2] Expand Logging (+10 Wood Production, 30 gold)\n"
             << "[3] Improve Mining (+10 Stone Production, 40 gold)\n"
             << "[4] Recruit Soldiers (2 gold each)\n"
             << "[5] Train Troops (50 gold, 20 wood)\n"
             << "[6] Upgrade Armory (100 gold, 50 wood, 30 stone)\n"
             << "[7] Change Tax Rate\n"
             << "[8] Request Loan\n"
             << "[9] Repay Loan\n"
             << "[A] Conduct Bank Audit\n"
             << "[B] Trigger Event\n"
             << "[C] Advance Turn\n"
             << "[D] Diplomacy Actions\n"
             << "[W] Declare War\n"
             << "[T] Trade/Smuggle\n"
             << "[M] Map Actions\n"
             << "[F] View Messages\n"
             << "[S] Save Game\n"
             << "[L] Load Game\n"
             << "[Q] Quit Game\n\n"
             << "Your decree: ";

        char choice = _getch();
        system("cls");
        printHeader("ACTION");

        switch (toupper(choice))
        {
        case '1':
            if (currentKingdom->getEconomy().spendGold(50))
            {
                currentKingdom->getResource("Food").changeProductionRate(10);
                printColored("Farms upgraded! Food production increased.\n", COLOR_GREEN);
            }
            else
            {
                printColored("Need 50 gold!\n", COLOR_RED);
            }
            pressAnyKey();
            break;

        case '2':
            if (currentKingdom->getEconomy().spendGold(30))
            {
                currentKingdom->getResource("Wood").changeProductionRate(10);
                printColored("Logging expanded! Wood production increased.\n", COLOR_GREEN);
            }
            else
            {
                printColored("Need 30 gold!\n", COLOR_RED);
            }
            pressAnyKey();
            break;

        case '3':
            if (currentKingdom->getEconomy().spendGold(40))
            {
                currentKingdom->getResource("Stone").changeProductionRate(10);
                printColored("Mines improved! Stone production increased.\n", COLOR_GREEN);
            }
            else
            {
                printColored("Need 40 gold!\n", COLOR_RED);
            }
            pressAnyKey();
            break;

        case '4':
            cout << "How many soldiers to recruit? ";
            int amount;
            if (cin >> amount && amount >= 0)
            {
                int cost = amount * 2;
                if (currentKingdom->getEconomy().spendGold(cost))
                {
                    currentKingdom->getMilitary().recruit(amount);
                    printColored(to_string(amount) + " soldiers recruited!\n", COLOR_GREEN);
                }
                else
                {
                    printColored("Need " + to_string(cost) + " gold!\n", COLOR_RED);
                }
            }
            else
            {
                printColored("Invalid number!\n", COLOR_RED);
            }
            cin.clear();
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pressAnyKey();
            break;

        case '5':
            if (currentKingdom->getEconomy().spendGold(50) && currentKingdom->getResource("Wood").consume(20))
            {
                currentKingdom->getMilitary().train(1);
                printColored("Troops trained! Training level increased.\n", COLOR_GREEN);
            }
            else
            {
                printColored("Need 50 gold and 20 wood!\n", COLOR_RED);
            }
            pressAnyKey();
            break;

        case '6':
            if (currentKingdom->getEconomy().spendGold(100) && currentKingdom->getResource("Wood").consume(50) && currentKingdom->getResource("Stone").consume(30))
            {
                currentKingdom->getMilitary().equip(1);
                printColored("Armory upgraded! Equipment level increased.\n", COLOR_GREEN);
            }
            else
            {
                printColored("Need 100 gold, 50 wood, 30 stone!\n", COLOR_RED);
            }
            pressAnyKey();
            break;

        case '7':
            cout << "Enter new tax rate (0-50%): ";
            int rate;
            if (cin >> rate && rate >= 0 && rate <= 50)
            {
                currentKingdom->getEconomy().setTaxRate(rate);
                printColored("Tax rate set to " + to_string(rate) + "%!\n", COLOR_GREEN);
            }
            else
            {
                printColored("Invalid tax rate!\n", COLOR_RED);
            }
            cin.clear();
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pressAnyKey();
            break;

        case '8':
            cout << "Enter loan amount: ";
            int loan;
            if (cin >> loan && loan >= 0)
            {
                int approved = currentKingdom->getBank().provideLoan(loan);
                if (approved > 0)
                {
                    currentKingdom->getEconomy().setTreasury(currentKingdom->getEconomy().getTreasury() + approved);
                    printColored("Loan of " + to_string(approved) + " gold approved!\n", COLOR_GREEN);
                }
                else
                {
                    printColored("Loan request denied!\n", COLOR_RED);
                }
            }
            else
            {
                printColored("Invalid amount!\n", COLOR_RED);
            }
            cin.clear();
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pressAnyKey();
            break;

        case '9':
            cout << "Enter repayment amount: ";
            int repay;
            if (cin >> repay && repay >= 0)
            {
                if (currentKingdom->getEconomy().spendGold(repay))
                {
                    currentKingdom->getBank().collectLoanPayment(repay);
                    printColored("Repaid " + to_string(repay) + " gold!\n", COLOR_GREEN);
                }
                else
                {
                    printColored("Insufficient funds!\n", COLOR_RED);
                }
            }
            else
            {
                printColored("Invalid amount!\n", COLOR_RED);
            }
            cin.clear();
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pressAnyKey();
            break;

        case 'A':
            currentKingdom->getBank().conductAudit();
            printColored("Bank audit conducted! Corruption reduced.\n", COLOR_GREEN);
            pressAnyKey();
            break;

        case 'B':
        {
            printHeader("TRIGGER EVENT");
            cout << "[0] Plague (-20 population happiness)\n"
                 << "[1] Bountiful Harvest (+15 economy)\n"
                 << "[2] Foreign Invasion (-30 military morale)\n"
                 << "[3] Trade Agreement (+300 gold)\n"
                 << "[4] Royal Wedding (+25 leadership popularity)\n"
                 << "[5] Gold Mine Discovery (+500 gold)\n"
                 << "[6] Military Victory (+20 military morale)\n"
                 << "[7] Diplomatic Mission (+10 leadership popularity)\n"
                 << "[8] War (-12 soldiers)\n"
                 << "[9] Custom Event\n"
                 << "Choose an event: ";

            char eventChoice = _getch();
            if (eventChoice >= '0' && eventChoice <= '8')
            {
                int eventIndex = eventChoice - '0';
                currentKingdom->handleEvent(events[eventIndex]);
            }
            else if (eventChoice == '9')
            {
                system("cls");
                printHeader("CUSTOM EVENT");
                string name, description, targetSystem;
                int impact;
                cout << "Event name: ";
                getline(cin, name);
                cout << "Event description: ";
                getline(cin, description);
                cout << "Target system (population/military/economy/leadership/bank): ";
                getline(cin, targetSystem);
                cout << "Impact value (positive/negative): ";
                if (cin >> impact)
                {
                    Event customEvent(name, description, impact, targetSystem);
                    currentKingdom->handleEvent(customEvent);
                }
                else
                {
                    printColored("Invalid impact value!\n", COLOR_RED);
                }
                cin.clear();
                // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
            {
                printColored("Invalid event!\n", COLOR_RED);
            }
            pressAnyKey();
            break;
        }

        case 'C':
            printHeader("Kingdom Status");
            currentKingdom->advanceTurn();
            mp.nextTurn();
            pressAnyKey();
            break;

        case 'D':
            diplomacyMenu(currentKingdom, mp);
            break;

        case 'W':
        {
            system("cls");
            printHeader("WAR DECLARATION");
            mp.displayOtherKingdoms();
            cout << "Choose kingdom to attack (1-" << mp.getPlayerCount() << "): ";
            int target;
            if (cin >> target && target >= 1 && target <= mp.getPlayerCount() && target != mp.getCurrentPlayerIndex() + 1)
            {
                Military m;
                Kingdom *targetKingdom = mp.getKingdom(target - 1);
                currentKingdom->wars.declareWar(currentKingdom->getName(), targetKingdom->getName());
                m.attack(currentKingdom,targetKingdom);
                currentKingdom->wars.resolveBattle(*currentKingdom, *targetKingdom);
                printColored("War declared and battle resolved!\n", COLOR_GREEN);
            }
            else
            {
                printColored("Invalid target!\n", COLOR_RED);
            }
            cin.clear();
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pressAnyKey();
            break;
        }

        case 'T':
            tradeMenu(currentKingdom, mp);
            break;

        case 'M':
            mapMenu(currentKingdom, worldMap);
            break;

        case 'F':
            system("cls");
            printHeader("MESSAGES");
            currentKingdom->diplomacy.displayMessages();
            pressAnyKey();
            break;

        case 'S':
            system("cls");
            printHeader("SAVE KINGDOM");
            mp.saveGameState();
            printColored("Game saved successfully!\n", COLOR_GREEN);
            pressAnyKey();
            break;

        case 'L':
        {
            system("cls");
            printHeader("LOAD KINGDOM");
            cout << "Enter save file name: ";
            string filename;
            getline(cin, filename);
            if (currentKingdom->loadGame(filename))
            {
                printColored("Kingdom loaded successfully!\n", COLOR_GREEN);
            }
            else
            {
                printColored("Failed to load kingdom!\n", COLOR_RED);
            }
            pressAnyKey();
            break;
        }

        case 'Q':
            running = false;
            break;

        default:
            printColored("Invalid decree!\n", COLOR_RED);
            pressAnyKey();
            break;
        }
    }

    system("cls");
    printHeader("END OF REIGN");
    printColored("Your legacy will be remembered, ruler of " + mp.getCurrentKingdom()->getName() + "!\n", COLOR_YELLOW);
    pressAnyKey();
    return 0;
}

void printHeader(const string &title)
{
    system("cls");
    printColored("========================================\n", COLOR_CYAN);
    printColored("  " + title + "\n", COLOR_CYAN);
    printColored("========================================\n\n", COLOR_CYAN);
}

void printColored(const string &text, int colorCode)
{
#ifdef ENABLE_COLOR
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
#endif
    cout << text;
#ifdef ENABLE_COLOR
    SetConsoleTextAttribute(hConsole, COLOR_WHITE);
#endif
}

void pressAnyKey()
{
    cout << "\n";
    printColored("Press any key to continue...", COLOR_YELLOW);
    _getch();
}

void mapMenu(Kingdom *kingdom, TextMap &worldMap)
{
    system("cls");
    printHeader("WORLD MAP");
    worldMap.displayMap(kingdom->getLocation());

    cout << "\n[1] Move Location\n"
         << "[2] Return\n"
         << "Choice: ";

    char choice = _getch();
    if (choice == '1')
    {
        system("cls");
        printHeader("MOVE LOCATION");
        worldMap.displayMap(kingdom->getLocation());

        cout << "\nEnter destination: ";
        string dest;
        getline(cin, dest);

        if (worldMap.isValidMove(kingdom->getLocation(), dest))
        {
            kingdom->setLocation(dest);
            printColored("Moved to " + dest + "!\n", COLOR_GREEN);
        }
        else
        {
            printColored("Cannot move to " + dest + "!\n", COLOR_RED);
        }
        pressAnyKey();
    }
}

void diplomacyMenu(Kingdom *kingdom, MultiplayerManager &mp)
{
    system("cls");
    printHeader("DIPLOMACY");
    kingdom->diplomacy.displayAllies();

    cout << "\n[1] Send Message\n"
         << "[2] Form Alliance\n"
         << "[3] Back\n"
         << "Choice: ";

    char choice = _getch();
    if (choice == '1')
    {
        system("cls");
        printHeader("SEND MESSAGE");
        mp.displayOtherKingdoms();
        cout << "Select kingdom (1-" << mp.getPlayerCount() << "): ";
        int target;
        if (cin >> target && target >= 1 && target <= mp.getPlayerCount() && target != mp.getCurrentPlayerIndex() + 1)
        {
            cin.ignore();
            cout << "Enter message: ";
            string msg;
            getline(cin, msg);
            Kingdom *targetKingdom = mp.getKingdom(target - 1);
            targetKingdom->diplomacy.addMessage(kingdom->getName() + ": " + msg);
            printColored("Message sent!\n", COLOR_GREEN);
        }
        else
        {
            printColored("Invalid target!\n", COLOR_RED);
            cin.clear();
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        pressAnyKey();
    }
    else if (choice == '2')
    {
        system("cls");
        printHeader("FORM ALLIANCE");
        mp.displayOtherKingdoms();
        cout << "Select kingdom (1-" << mp.getPlayerCount() << "): ";
        int target;
        if (cin >> target && target >= 1 && target <= mp.getPlayerCount() && target != mp.getCurrentPlayerIndex() + 1)
        {
            cin.ignore();
            Kingdom *targetKingdom = mp.getKingdom(target - 1);
            kingdom->diplomacy.addAlly(targetKingdom->getName());
            targetKingdom->diplomacy.addAlly(kingdom->getName());
            printColored("Alliance formed with " + targetKingdom->getName() + "!\n", COLOR_GREEN);
        }
        else
        {
            printColored("Invalid target!\n", COLOR_RED);
            cin.clear();
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        pressAnyKey();
    }
}

void tradeMenu(Kingdom *current, MultiplayerManager &mp)
{
    system("cls");
    printHeader("TRADE SYSTEM");
    mp.displayOtherKingdoms();

    cout << "Select kingdom (1-" << mp.getPlayerCount() << "): ";
    int target;
    if (!(cin >> target) || target < 1 || target > mp.getPlayerCount() || target == mp.getCurrentPlayerIndex() + 1)
    {
        printColored("Invalid target!\n", COLOR_RED);
        cin.clear();
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        pressAnyKey();
        return;
    }
    cin.ignore();

    cout << "\nYour Resources:\n";
    for (int i = 0; i < 4; i++)
    {
        cout << "[" << (i + 1) << "] ";
        current->getResource(i).displayStatus();
    }

    cout << "\nEnter resource to trade (1-4): ";
    int res;
    if (!(cin >> res) || res < 1 || res > 4)
    {
        printColored("Invalid resource!\n", COLOR_RED);
        cin.clear();
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        pressAnyKey();
        return;
    }
    cin.ignore();

    cout << "Enter amount: ";
    int amount;
    if (!(cin >> amount) || amount < 0)
    {
        printColored("Invalid amount!\n", COLOR_RED);
        cin.clear();
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        pressAnyKey();
        return;
    }
    cin.ignore();

    cout << "[1] Legal Trade\n[2] Smuggle\nChoice: ";
    char tradeChoice = _getch();
    Kingdom *targetKingdom = mp.getKingdom(target - 1);
    string resourceName = current->getResource(res - 1).getName();

    if (tradeChoice == '1')
    {
        current->trades.legalTrade(*current, *targetKingdom, resourceName, amount);
        printColored("Legal trade completed!\n", COLOR_GREEN);
    }
    else if (tradeChoice == '2')
    {
        current->trades.smuggle(*current, *targetKingdom, resourceName, amount);
        printColored("Smuggling attempted!\n", COLOR_GREEN);
    }
    else
    {
        printColored("Invalid choice!\n", COLOR_RED);
    }
    pressAnyKey();
}