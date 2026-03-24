#include <iostream>
#include <vector>
#include <string>
#include <queue>   
#include <climits> 

using namespace std;

class CITY
{
public:
    int totalnodes = 8;
    vector<pair<int, int>> G[8];
    vector<pair<int, int>> coordinates[8];

private:
    int rows;
    int cols;

public:
    CITY(int r, int c)
    {
        rows = r;
        cols = c;
    }
    void Setlocations()
    {
        for (int i = 0; i < totalnodes; i++)
        {
            cout << "ENTER COORDINATES OF LOCATION NO  " << i + 1 << endl;
            int x1, y1;
            cin >> x1 >> y1;
            coordinates[i].push_back({x1, y1});
        }
    }
    void Citygrid()
    {
        int s, d, w;
        for (int i = 0; i < totalnodes; i++)
        {
            cout << "ENTER SOURCE, DESTINATION AND WEIGHT OF ROAD: " << endl;
            cin >> s >> d >> w;
            G[s].push_back({d, w});
            G[d].push_back({s, w});
        }
    }
    void Newroad()
    {
        cout << "ENTER SOURCE, DESTINATION AND WEIGHT OF NEW ROAD: " << endl;
        int s, d, w;
        cin >> s >> d >> w;
        G[s].push_back({d, w});
        G[d].push_back({s, w});
    }
    void Neighbour()
    {
        int n;
        cout << "ENTER NEIGHBOURHOOD " << endl;
        cin >> n;
        cout << "NEIGHBOURING AREAS ARE : " << endl;
        for (int i = 0; i < G[n].size(); i++)
            cout << G[n][i].first << endl;
    }
    void Getweight(int src, int des)
    {
        for (int i = 0; i < G[src].size(); i++)
        {
            if (G[src][i].first == des)
            {
                cout << "WEIGHT OF ROAD IS : " << G[src][i].second << endl;
                return;
            }
        }
        cout << "NO DIRECT ROAD EXISTS BETWEEN THE LOCATIONS!" << endl;
    }
    void Updatetraffic(int src, int des, int w)
    {
        for (int i = 0; i < G[src].size(); i++)
        {
            if (G[src][i].first == des)
            {
                G[src][i].second = w;
                break;
            }
        }
        for (int i = 0; i < G[des].size(); i++)
        {
            if (G[des][i].first == src)
            {
                G[des][i].second = w;
                break;
            }
        }
    }
    int Totalnodes()
    {
        return totalnodes;
    }
    int Calculatedistance(int src, int dest)
    {
        int x1 = coordinates[src][0].first;
        int y1 = coordinates[src][0].second;
        int x2 = coordinates[dest][0].first;
        int y2 = coordinates[dest][0].second;
        return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    }
};

class NODE
{
private:
    int x, y;
    bool blocked;
    bool emergency;
    string emergencytype;

public:
    NODE() {}
    void Setblocked() {}
    void Setemergency() {}
    void Reset() {}
};

class VEHICLES
{
    static int count;
    static int Maxfuel;

private:
    string id;
    int speed;
    string type;
    int loc;
    int fuel;
    bool available;
    vector<int> currentpath;
    int targetemergency;

public:
    VEHICLES()
    {
        id = "";
        type = "";
        loc = 0;
        fuel = 0;
        speed = 30;
        available = false;
    }

    void Setvehicle(string id, string type, int loc, int s)
    {
        this->id = id;
        this->type = type;
        this->loc = loc;
        this->fuel = Maxfuel;
        this->speed = s;
        this->available = true;
        count++;
    }
    static int vehiclecount()
    {
        return count;
    }
    static void Setmaxfuel(int max)
    {
        Maxfuel = max;
    }
    string Getid()
    {
        return id;
    }
    string Gettype()
    {
        return type;
    }
    int Getspeed()
    {
        return speed;
    }
    bool Isavailable()
    {
        return available;
    }
    int Getlocation()
    {
        return loc;
    }
};

class PATHFINDER
{
public:
    int CalPath(int src, int dest, CITY &city)
    {
        int n = city.Totalnodes();
        vector<int> dist(n, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty())
        {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u])
                continue;

            for (auto &neighbor : city.G[u])
            {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist[dest];
    }
};

class DISPATCHER
{
public:
    int Findvehicle(int emergencyLoc, string type, VEHICLES *V, int totalVehicles, CITY &city)
    {
        PATHFINDER pf;
        int bestIdx = -1;
        int minTime = INT_MAX;

        for (int i = 0; i < totalVehicles; i++)
        {
            if (V[i].Isavailable() && V[i].Gettype() == type)
            {
                int distance = pf.CalPath(V[i].Getlocation(), emergencyLoc, city);

                if (distance != INT_MAX)
                {
                    int travelTime = distance / V[i].Getspeed();
                    if (travelTime < minTime)
                    {
                        minTime = travelTime;
                        bestIdx = i;
                    }
                }
            }
        }
        return bestIdx;
    }
};

int VEHICLES::count = 0;
int VEHICLES::Maxfuel = 0;

int main()
{
    int vCount = 0;
    int MaxVeh = 5;
    VEHICLES *V = new VEHICLES[MaxVeh];
    CITY city(10, 20);
    DISPATCHER dispatcher;
    int ch;

    cout << "WELCOME TO THE URBAN LIFELINE SYSTEM!" << endl;
    VEHICLES::Setmaxfuel(100);

    while (true)
    {
        cout << "\n1.BUILD CITY\n2.ADD RESPONDER\n3.DISPATCH TO CRISIS\n4.EXIT\nCHOICE: ";
        cin >> ch;

        if (ch == 4)
            break;

        switch (ch)
        {
        case 1:
            city.Citygrid();
            city.Setlocations();
            break;
        case 2:
            if (vCount < MaxVeh)
            {
                string id, type;
                int loc, speed;
                cout << "Enter ID, Type (Medical/Fire), Location, Speed: ";
                cin >> id >> type >> loc >> speed;
                V[vCount++].Setvehicle(id, type, loc, speed);
            }
            break;
        case 3:
            int target;
            string type;
            cout << "Enter Crisis Location (0-7) and Type required: ";
            cin >> target >> type;
            int best = dispatcher.Findvehicle(target, type, V, vCount, city);
            if (best != -1)
                cout << "\n[SUCCESS] Dispatching Responder: " << V[best].Getid() << endl;
            else
                cout << "\n[ALERT] No specialized responders found!" << endl;
            break;
        }
    }
    delete[] V;
    return 0;
}
