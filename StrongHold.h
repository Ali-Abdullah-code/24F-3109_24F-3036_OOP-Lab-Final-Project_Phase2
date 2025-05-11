#ifndef STRONGHOLD_H
#define STRONGHOLD_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Custom exception class
class GameException
{
private:
    string message;

public:
    GameException(const string &msg) : message(msg) {}
    string what() const 
    {
        return message; 
    }
};

// Forward declarations
class Resource;
class Population;
class SocialClass;
class Military;
class Economy;
class Leadership;
class Bank;
class Event;
class Message;
class Alliance;
class Trade;
class Map;
class Kingdom;
class GameManager;

// Resource class (unchanged)
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
    bool consume(int amount);
    void changeProductionRate(int change);
    void changeConsumptionRate(int change);
    void displayStatus() const;
};

// Population class (unchanged)
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

// SocialClass and derived classes (unchanged)
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

// Military class (extended for battles)
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
    int calculateStrength() const;
    void paySoldiers(int gold);
    void displayStatus() const;
    bool engageInBattle(Military &enemy, bool isBetrayal); // Battle logic
};

// Economy class
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
    void receiveTrade(int gold); // For trade transactions
};

// Leadership class
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

// Bank class
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

// Event class
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

// Message class for communication
class Message
{
private:
    string sender;
    string receiver;
    string content;
    string timestamp;

public:
    Message(string sender, string receiver, string content);
    string getSender() const;
    string getReceiver() const;
    string getContent() const;
    string getTimestamp() const;
    void saveToLog() const;
};

// Alliance class for treaties
class Alliance
{
private:
    string kingdom1;
    string kingdom2;
    string status;
    string timestamp;

public:
    Alliance(string k1, string k2);
    string getKingdom1() const;
    string getKingdom2() const;
    string getStatus() const;
    void breakAlliance();
    void saveToLog() const;
};

// Trade class for market and smuggling
class Trade
{
protected:
    string sender;
    string receiver;
    string resource;
    int amount;
    int gold;
    string timestamp;

public:
    Trade(string sender, string receiver, string resource, int amount, int gold);
    virtual bool execute(Kingdom &senderKingdom, Kingdom &receiverKingdom);
    virtual void saveToLog() const;
};

class Smuggling : public Trade
{
private:
    int risk; // 0-100
public:
    Smuggling(string sender, string receiver, string resource, int amount, int gold, int risk);
    bool execute(Kingdom &senderKingdom, Kingdom &receiverKingdom) override;
    void saveToLog() const override;
};

// Map class for grid-based positioning
class Map
{
private:
    static const int SIZE = 5; 
    char grid[SIZE][SIZE];     
    int kingdomX[4];           
    int kingdomY[4];           
public:
    Map();
    void placeKingdom(int kingdomId, int x, int y);
    void moveKingdom(int kingdomId, int newX, int newY);
    bool isValidPosition(int x, int y) const;
    int getKingdomX(int kingdomId) const;
    int getKingdomY(int kingdomId) const;
    void display() const;
};


template <typename T>
class DataLogger
{
private:
    string filename;

public:
    DataLogger(const string &fname) : filename(fname) {}
    void log(const T &data) const
    {
        ofstream file(filename, ios::app);
        if (!file.is_open())
        {
            throw GameException("Failed to open file: " + filename);
        }
        file << data << endl;
        file.close();
    }
};

// Kingdom class 
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
    int mapX, mapY;
public:
    Kingdom();
    Kingdom(string name);
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
    bool saveGame(const string &filename) const;
    bool loadGame(const string &filename);
    // New methods for Phase 2
    void sendMessage(const string &receiver, const string &content);
    void receiveMessages() const;
    void formAlliance(const string &otherKingdom);
    void breakAlliance(const string &otherKingdom);
    void offerTrade(const string &receiver, const string &resource, int amount, int gold, bool isSmuggling);
    void acceptTrade(const Trade &trade);
    void attackKingdom(Kingdom &target, bool isBetrayal);
    void setMapPosition(int x, int y);
    int getMapX() const;
    int getMapY() const;
};

// GameManager for multiplayer
class GameManager
{
private:
    Kingdom *kingdoms;
    int numKingdoms;
    Map map;
    DataLogger<string> sessionLogger;

public:
    GameManager(int num);
    ~GameManager();
    void initializeKingdoms();
    void runTurn();
    void logSession(const string &entry);
    Kingdom &getKingdom(int index);
};

#endif // STRONGHOLD_H