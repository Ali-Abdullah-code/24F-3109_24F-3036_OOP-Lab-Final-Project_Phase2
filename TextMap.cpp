#include "StrongHold.h"

TextMap::TextMap()
{
    addLocation("Castle", "Your royal stronghold");
    addLocation("Forest", "Dense ancient woodland");
    addLocation("Mines", "Abandoned mineral tunnels");
    addLocation("Farmlands", "Vast agricultural fields");
    addLocation("Fast University", "Chiniot - Faisalabad");

    connectLocations("Castle", "Forest");
    connectLocations("Castle", "Farmlands");
    connectLocations("Forest", "Mines");
    connectLocations("Farmlands", "Mines");
    connectLocations("Fast University", "Farmlands");
}
void TextMap::addLocation(string name, string desc)
{
    if (locationCount < MAX_LOCATIONS)
    {
        locations[locationCount].name = name;
        locations[locationCount].description = desc;
        locationCount++;
    }
}

void TextMap::connectLocations(string loc1, string loc2)
{
    for (int i = 0; i < locationCount; i++)
    {
        if (locations[i].name == loc1 && locations[i].connectionCount < MAX_CONNECTIONS)
        {
            locations[i].connections[locations[i].connectionCount++] = loc2;
        }
        if (locations[i].name == loc2 && locations[i].connectionCount < MAX_CONNECTIONS)
        {
            locations[i].connections[locations[i].connectionCount++] = loc1;
        }
    }
}

void TextMap::displayMap(string currentLocation)
{
    cout << "\n=== WORLD MAP ===\n";
    for (int i = 0; i < locationCount; i++)
    {
        cout << "\n"
             << (locations[i].name == currentLocation ? "> " : "  ")
             << locations[i].name << "\n"
             << "   " << locations[i].description << "\n"
             << "   Connected to: ";

        for (int j = 0; j < locations[i].connectionCount; j++)
        {
            cout << locations[i].connections[j];
            if (j != locations[i].connectionCount - 1)
            {
                cout << ", ";
            }
        }
    }
    cout << "\n";
}

bool TextMap::isValidMove(string from, string to)
{
    for (int i = 0; i < locationCount; i++)
    {
        if (locations[i].name == from)
        {
            for (int j = 0; j < locations[i].connectionCount; j++)
            {
                if (locations[i].connections[j] == to)
                {
                    return true;
                }
            }
        }
    }
    return false;
}