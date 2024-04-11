// k-nearest neighbor simple. conduciendo un vehiculo motorizado estandar.

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class City
{
private:
    string name;
    unordered_map<City *, double> neighborDistances;

public:
    City(string n) : name(n) {}

    string getName() const
    {
        return name;
    }

    void addNeighbor(City *neighbor, double distance)
    {
        neighborDistances[neighbor] = distance;
    }

    const unordered_map<City *, double> &getNeighborDistances() const
    {
        return neighborDistances;
    }

    double getDistanceTo(City *neighbor) const
    {
        auto it = neighborDistances.find(neighbor);
        return it != neighborDistances.end() ? it->second : -1; // Return -1 if no direct connection
    }
};

class Map
{

public:
    unordered_map<string, City *> cities;

    ~Map()
    {
        for (auto &pair : cities)
        {
            delete pair.second;
        }
    }

    void addCity(const string &cityName)
    {
        if (cities.find(cityName) == cities.end())
        {
            cities[cityName] = new City(cityName);
        }
    }

    void addConnection(const string &city1, const string &city2, double distance)
    {
        if (cities.find(city1) != cities.end() && cities.find(city2) != cities.end())
        {
            cities[city1]->addNeighbor(cities[city2], distance);
            cities[city2]->addNeighbor(cities[city1], distance);
        }
    }

    vector<string> findShortestPath(const string &start, const string &end) const
    {
        queue<pair<City *, vector<string>>> q;
        unordered_map<City *, bool> visited;

        // Initialize start city
        City *startCity = cities.at(start);
        q.push({startCity, {start}});
        visited[startCity] = true;

        while (!q.empty())
        {
            auto [currentCity, path] = q.front();
            q.pop();

            // If the current city is the destination, return the path
            if (currentCity->getName() == end)
            {
                return path;
            }

            // Explore neighbors
            for (auto [neighbor, _] : currentCity->getNeighborDistances())
            {
                if (!visited[neighbor])
                {
                    vector<string> newPath = path;
                    newPath.push_back(neighbor->getName());
                    q.push({neighbor, newPath});
                    visited[neighbor] = true;
                }
            }
        }

        // If no path found
        return {};
    }

    double calculateTotalDistance(const vector<string> &path) const
    {
        double totalDistance = 0.0;
        for (size_t i = 0; i < path.size() - 1; ++i)
        {
            City *currentCity = cities.at(path[i]);
            City *nextCity = cities.at(path[i + 1]);
            double distance = currentCity->getDistanceTo(nextCity);
            if (distance > 0)
            {
                totalDistance += distance;
            }
        }
        return totalDistance;
    }

    void printCities() const
    {
        cout << "Cities in the map:\n";
        for (const auto &pair : cities)
        {
            cout << pair.first << endl;
        }
    }

    void printConnections() const
    {
        cout << "Connections between cities:\n";
        for (const auto &pair : cities)
        {
            City *city = pair.second;
            cout << "City: " << city->getName() << "\nNeighbors:\n";
            for (const auto &neighbor : city->getNeighborDistances())
            {
                cout << neighbor.first->getName() << " : " << neighbor.second << " km\n";
            }
            cout << endl;
        }
    }

    int getCitiesCount() const
    {
        return cities.size();
    }

    int getConnectionsCount() const
    {
        int count = 0;
        for (const auto &pair : cities)
        {
            count += pair.second->getNeighborDistances().size();
        }
        return count / 2; // Divided by 2 as each connection is counted twice
    }
};

int main()
{
    Map chileMap;

    // Add cities
    chileMap.addCity("Arica");
    chileMap.addCity("Iquique");
    chileMap.addCity("Antofagasta");
    chileMap.addCity("Calama");
    chileMap.addCity("Copiapo");
    chileMap.addCity("La Serena");
    chileMap.addCity("Valparaiso");
    chileMap.addCity("Santiago");
    chileMap.addCity("Rancagua");
    chileMap.addCity("Talca");
    chileMap.addCity("Chillan");
    chileMap.addCity("Concepcion");
    chileMap.addCity("Temuco");
    chileMap.addCity("Puerto Montt");
    chileMap.addCity("Osorno");
    chileMap.addCity("Punta Arenas");

    // Add connections with distances in kilometers
    chileMap.addConnection("Arica", "Iquique", 309.4);
    chileMap.addConnection("Iquique", "Antofagasta", 416.1);
    chileMap.addConnection("Iquique", "Calama", 387.8);
    chileMap.addConnection("Antofagasta", "Calama", 217.3);
    chileMap.addConnection("Antofagasta", "Copiapo", 455);
    chileMap.addConnection("Copiapo", "La Serena", 336.5);
    chileMap.addConnection("La Serena", "Valparaiso", 431.5);
    chileMap.addConnection("Valparaiso", "Santiago", 115.6);
    chileMap.addConnection("Santiago", "Rancagua", 86.6);
    chileMap.addConnection("Rancagua", "Talca", 172.3);
    chileMap.addConnection("Talca", "Chillan", 151.3);
    chileMap.addConnection("Chillan", "Concepcion", 98.1);
    chileMap.addConnection("Concepcion", "Temuco", 292.9);
    chileMap.addConnection("Temuco", "Puerto Montt", 353.5);
    chileMap.addConnection("Puerto Montt", "Osorno", 108.0);
    chileMap.addConnection("Puerto Montt", "Chillan", 631.3);
    chileMap.addConnection("Osorno", "Puerto Montt", 107.3);
    chileMap.addConnection("Santiago", "Chillan", 404.6);
    chileMap.addConnection("Chillan", "Concepcion", 98.1);
    chileMap.addConnection("Concepcion", "Temuco", 292.9);
    chileMap.addConnection("Puerto Montt", "Punta Arenas", 2173.4);

    // Additional functionalities
    cout << "Number of cities in the map: " << chileMap.getCitiesCount() << endl;
    cout << "Number of connections in the map: " << chileMap.getConnectionsCount() << endl;

    cout << "\nCities in the map:\n";
    chileMap.printCities();

    cout << "\nConnections between cities:\n";
    chileMap.printConnections();

    // Get user input for cities
    string startCity, endCity;
    cout << "\nEnter the starting city: ";
    getline(cin, startCity);
    cout << "Enter the destination city: ";
    getline(cin, endCity);

    // Find shortest path
    vector<string> shortestPath = chileMap.findShortestPath(startCity, endCity);

    // Print the path with distances
    if (!shortestPath.empty())
    {
        cout << "\nShortest path from " << startCity << " to " << endCity << ":\n";
        double totalDistance = chileMap.calculateTotalDistance(shortestPath);
        for (size_t i = 0; i < shortestPath.size() - 1; ++i)
        {
            string currentCity = shortestPath[i];
            string nextCity = shortestPath[i + 1];
            double distance = chileMap.cities.at(currentCity)->getDistanceTo(chileMap.cities.at(nextCity));
            cout << currentCity << " -> " << nextCity << " : " << distance << " km\n";
        }
        cout << "Total distance: " << totalDistance << " km\n";
    }
    else
    {
        cout << "No path found!" << endl;
    }

    return 0;
}
