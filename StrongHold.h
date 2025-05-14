#ifndef STRONGHOLD_H
#define STRONGHOLD_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

#define COLOR_RED 12
#define COLOR_GREEN 10
#define COLOR_YELLOW 14
#define COLOR_CYAN 11
#define COLOR_WHITE 15

const int MAX_PLAYERS = 4;
const int MAX_ALLIES = 3;
const int MAX_MESSAGES = 20;
const int MAX_KINGDOMS = 4;
const int MAX_LOCATIONS = 10;
const int MAX_CONNECTIONS = 5;

void printColored(const string &text, int colorCode);
void pressAnyKey();

// Forward declarations
class Resource;
class Population;
class SocialClass;
class Military;
class Economy;
class Leadership;
class Bank;
class Event;
class Kingdom;
class DiplomacySystem;
class WarSystem;
class TradeSystem;

struct MapLocation
{
    string name;
    string description;
    string connections[MAX_CONNECTIONS];
    int connectionCount = 0;
};

// Resource class to manage different types of resources
class Resource
{
private:
    string name;
    int amount;
    int productionRate;
    int consumptionRate;

public:
    Resource();
    Resource(string name, int amount, int productionRate, int consumptionRate);

    string getName() const;
    int getAmount() const;
    int getProductionRate() const;
    int getConsumptionRate() const;
    void setAmount(int newAmount);
    void produce();
    void consume();
    bool consume(int amountToConsume);
    void changeProductionRate(int change);
    void changeConsumptionRate(int change);
    void displayStatus() const;
};

// Population class to manage kingdom's inhabitants
class Population
{
private:
    int totalPopulation;
    int growthRate;
    int deathRate;
    int happiness;
    int health;

public:
    Population();
    Population(int initialPopulation);

    int getTotal() const;
    void setPopulation(int pop);
    int getGrowthRate() const;
    int getHappiness() const;
    int getHealth() const;

    void setGrowthRate(int rate);
    void setDeathRate(int rate);
    void updatePopulation();
    void changeHappiness(int change);
    void changeHealth(int change);
    bool checkForRevolt() const;
};

// SocialClass represents different groups in society
class SocialClass
{
private:
    string name;
    int population;
    int taxRate;
    int happiness;
    int productivity;

public:
    SocialClass();
    SocialClass(string name, int population, int taxRate);

    string getName() const;
    int getPopulation() const;
    int getTaxRate() const;
    int getHappiness() const;
    int getProductivity() const;

    virtual void update() = 0;
    virtual double contribute() const = 0;
    virtual SocialClass *clone() const = 0;
    virtual int consume(Resource *resource, int amount);

    void setPopulation(int pop);
    void setTaxRate(int rate);
    void changeHappiness(int change);
    void updateProductivity();
    int generateTax() const;

    virtual ~SocialClass();
};

// Derived Social Classes
class Peasant : public SocialClass
{
private:
    double farmingEfficiency;

public:
    Peasant(int pop);
    void update() override;
    double contribute() const override;
    SocialClass *clone() const override;
};

class Merchant : public SocialClass
{
private:
    double tradingEfficiency;

public:
    Merchant(int pop);
    void update() override;
    double contribute() const override;
    SocialClass *clone() const override;
};

class Noble : public SocialClass
{
private:
    double influencePower;

public:
    Noble(int pop);
    void update() override;
    double contribute() const override;
    SocialClass *clone() const override;
};

// Military class to manage army
class Military
{
private:
    int soldiers;
    int training;
    int morale;
    int equipment;
    int cost;

public:
    Military();
    Military(int initialSoldiers);

    int getSoldiers() const;
    int getTraining() const;
    int getMorale() const;
    int getEquipment() const;
    int getCost() const;

    void recruit(int count);
    void setSoldiers(int count);
    void train(int level);
    void changeMorale(int change);
    void equip(int level);
    void attack(Kingdom *attacker, Kingdom *defender);
    int calculateStrength() const;
    void paySoldiers(int gold);
    void displayStatus() const;
};

// Economy class to manage gold and taxes
class Economy
{
private:
    int treasury;
    int taxRate;
    int inflation;
    int servicesCost;

public:
    Economy();
    Economy(int initialTreasury);

    int getTreasury() const;
    int getTaxRate() const;
    int getInflation() const;
    int getServicesCost() const;

    void setTreasury(int amount);
    void setTaxRate(int rate);
    void collectTaxes(int amount);
    bool spendGold(int amount);
    void updateInflation();
    void updateServicesCost();
};

// Leadership class to manage kingdom rulers
class Leadership
{
private:
    string currentRuler;
    int popularity;
    int leadershipAbility;
    int corruptionLevel;

public:
    Leadership();
    Leadership(string initialRuler);

    string getCurrentRuler() const;
    int getPopularity() const;
    int getLeadershipAbility() const;
    int getCorruptionLevel() const;

    void setRuler(string ruler);
    void changePopularity(int change);
    void changeLeadershipAbility(int change);
    void changeCorruptionLevel(int change);
    bool checkForCoup() const;
    void handleElection();
};

// Bank class to manage loans and banking operations
class Bank
{
private:
    int reserves;
    float interestRate;
    int loans;
    int corruption;

public:
    Bank();
    Bank(int initialReserves);

    int getReserves() const;
    float getInterestRate() const;
    int getLoans() const;
    int getCorruption() const;

    void setReserves(int amount);
    void setInterestRate(float rate);
    int provideLoan(int amount);
    void collectLoanPayment(int amount);
    void updateInterest();
    void conductAudit();
};



// Event class to manage random kingdom events
class Event
{
private:
    string name;
    string description;
    int impact;
    string targetSystem;

public:
    Event();
    Event(string name, string description, int impact, string targetSystem);

    string getName() const;
    string getDescription() const;
    int getImpact() const;
    string getTargetSystem() const;
    
    void triggerEvent(Kingdom &kingdom) const;
};

class DiplomacySystem
{
private:
    string allies[MAX_ALLIES];
    int numAllies = 0;
    string messages[MAX_MESSAGES];
    int messageCount = 0;

public:
    void addAlly(const string &kingdom);
    void addMessage(const string &msg);
    void displayAllies() const;
    void displayMessages() const;
};

class WarSystem
{
private:
    string warStatus[MAX_KINGDOMS];

public:
    void declareWar(const string &attacker, const string &defender);
    void resolveBattle(Kingdom &attacker, Kingdom &defender);
    void logEvent(const string &message);
};

class TradeSystem
{
private:
    const float SMUGGLE_RISK = 0.5;

public:
    void legalTrade(Kingdom &from, Kingdom &to, string resource, int amount);
    void smuggle(Kingdom &from, Kingdom &to, string resource, int amount);
    void logTrade(const string &from, const string &to, const string &res, int amt, bool isSmuggle);
};

class TextMap
{
private:
    MapLocation locations[MAX_LOCATIONS];
    int locationCount = 0;

public:
    TextMap();
    void addLocation(string name, string desc);
    void connectLocations(string loc1, string loc2);
    void displayMap(string currentLocation);
    bool isValidMove(string from, string to);
};

class Kingdom
{
private:
    string name;
    Population population;
    SocialClass **socialClasses;
    int numSocialClasses;
    Military military;
    Economy economy;
    Leadership leadership;
    Bank bank;
    Resource *resources;
    int numResources;
    string currentLocation;

public:
    DiplomacySystem diplomacy;
    WarSystem wars;
    TradeSystem trades;

    Kingdom();
    Kingdom(string name);
    Kingdom(const Kingdom &other); // Copy constructor
    Kingdom &operator=(const Kingdom &other); // Assignment operator
    ~Kingdom();

    string getName() const;
    Population &getPopulation();
    Military &getMilitary();
    Economy &getEconomy();
    Leadership &getLeadership();
    Bank &getBank();
    int getNumSocialClasses() const;
    SocialClass &getSocialClass(int index);

    void addSocialClass(const SocialClass &newClass);
    void addResource(const Resource &newResource);

    Resource &getResource(int index);
    Resource &getResource(const string &name);

    void advanceTurn();
    void handleEvent(const Event &event);
    void displayStatus() const;

    string getLocation() const;
    void setLocation(string newLoc);

    bool saveGame(const string &filename) const;
    bool loadGame(const string &filename);
};

class MultiplayerManager
{
private:
    Kingdom kingdoms[MAX_PLAYERS];
    int playerCount = 0;
    int currentPlayer = 0;
    int totalTurns = 0;

public:
    void setupPlayers();
    void nextTurn();
    Kingdom *getCurrentKingdom();
    Kingdom *getKingdom(int index);
    void displayOtherKingdoms();
    void processGlobalEvents();
    void saveGameState();
    int getPlayerCount();
    int getCurrentPlayerIndex();
};

#endif // STRONGHOLD_H