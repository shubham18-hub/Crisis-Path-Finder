
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <climits>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>
#include <atomic>
#include <optional>  
using namespace std;

int SafeInput(const string &p = "")
{
    int val;
    while(true)
    {
        if(!p.empty()) 
        cout << p;
        cin >> val;
        if(cin.good())
        return val;
        cout<<"INVALID INPUT. PLEASE ENTER AN INTEGER.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
}

string SafeStringInput(const string &p = "")
{
    string val;
    if(!p.empty()) 
    cout << p;
    cin >> val;
    return val;
}


//CLASS — CITY 

class CITY
{
private:
    int rows;
    int cols;
    int totalnodes = 8;

public:
    vector<pair<int,int>> G[8];
    pair<int,int> coordinates[8];
    CITY(int r, int c)
    {
        rows =r;
        cols= c;
        for(int i=0; i<8;i++) 
        coordinates[i] ={-1, -1};
    }
    void Setlocations()
    {
        for(int i = 0; i < totalnodes; i++)
        {
            int x, y;
            while(true)
            {
                cout << "ENTER COORDINATES OF LOCATION "<< i << "(x: 0-" << rows-1 << ", y: 0-" << cols-1 << "):";
                x = SafeInput();
                y = SafeInput();
                if(x>=0&&x<rows&&y>=0 && y<cols)
                    break;
                cout <<"INVALID COORDINATES! x must be in [0," << rows-1<<"] and y must be in [0," << cols-1 << "]. TRY AGAIN.\n";
            }
            for(int j=0;j<i;j++)
            {
                if(coordinates[j].first==x && coordinates[j].second==y)
                {
                    cout<<"WARNING: LOCATION " <<j<< " ALREADY HAS THE SAME COORDINATES (" << x << "," << y << ").\n";
                    cout<<"CONTINUING ANYWAY...\n";
                }
            }
            coordinates[i]={x, y};
        }
    }
    bool RoadExists(int s, int d)
    {
        for(auto &x : G[s])
            if(x.first == d) 
            return true;
        return false;
    }
    void Citygrid()
    {
        int numRoads;
        while(true)
        {
            cout << "ENTER NUMBER OF ROADS TO ADD (1-20): ";
            numRoads = SafeInput();
            if(numRoads>=1 && numRoads<=20) 
            break;
            cout<<"INVALID NUMBER. MUST BE BETWEEN 1 AND 20.\n";
        }
        int s, d;
        for(int i=0;i<numRoads;i++)
        {
            cout <<"ENTER SOURCE DESTINATION (road"<< i+1 << "/"<<numRoads<<"): ";
            s = SafeInput();
            d = SafeInput();
            if(s<0 || s>=totalnodes || d<0 || d>=totalnodes)
            {
                cout << "INVALID NODE INDEX. SKIPPING.\n";
                continue;
            }
            if(RoadExists(s, d))
            {
                cout <<"ROAD BETWEEN" <<s<<" AND "<<d<<" ALREADY EXISTS. SKIPPING.\n";
                continue;
            }
            if(coordinates[s].first==-1 || coordinates[d].first==-1)
            {
                cout <<"SET LOCATIONS BEFORE ADDING ROADS (OPTION 2 IN BUILD CITY MENU).\n";
                continue;
            }
            int dist=Calculatedistance(s, d);
            int w =max(1,dist)+ rand()%5;
            G[s].push_back({d, w});
            G[d].push_back({s, w});
            cout << "ROAD ADDED: "<<s <<" <-> "<< d<<"  WEIGHT (DIST + TRAFFIC): "<< w <<"\n";
        }
    }
    void Newroad()
    {
        cout << "ENTER NEW ROAD (SOURCE DESTINATION):";
        int s =SafeInput();
        int d =SafeInput();
        if(s<0 || s>=totalnodes || d<0 || d>=totalnodes)
        {
            cout<< "INVALID NODE INDEX. ROAD NOT ADDED.\n";
            return;
        }
        if(RoadExists(s, d))
        {
            cout<<"ROAD ALREADY EXISTS BETWEEN " <<s<<" AND "<< d << ".\n";
            return;
        }
        if(coordinates[s].first==-1 || coordinates[d].first==-1)
        {
            cout<<"SET LOCATIONS BEFORE ADDING ROADS (OPTION 2 IN BUILD CITY MENU).\n";
            return;
        }
        int dist=Calculatedistance(s, d);
        int w= max(1, dist)+rand()%5;
        G[s].push_back({d, w});
        G[d].push_back({s, w});
        cout <<"ROAD ADDED: "<< s<< "<-> "<< d<< " WEIGHT (DIST + TRAFFIC): "<<w << "\n";
    }
    void Neighbour()
    {
        int n = SafeInput("ENTER NODE: ");
        if(n < 0||n>=totalnodes)
        {
            cout <<"INVALID NODE. MUST BE IN [0,"<<totalnodes-1 << "].\n";
            return;
        }
        if(G[n].empty())
        {
            cout <<"NODE"<<n<<"HAS NO NEIGHBOURS.\n";
            return;
        }
        cout <<"NEIGHBOURS OF "<< n<<": ";
        for(auto &x:G[n]) cout << x.first<< " ";
        cout << endl;
    }

    void Getweight(int s, int d)
    {
        if(s<0||s >=totalnodes || d<0 || d>=totalnodes)
        {
            cout << "INVALID NODE INDEX.\n";
            return;
        }

        for(auto &x:G[s])
        {
            if(x.first==d)
            {
                cout <<" WEIGHT "<<x.second<< endl;
                return;
            }
        }
        cout<<"NO ROAD BETWEEN "<<s<< " AND "<<d<<".\n";
    }

    void Updatetraffic(int s, int d, int w)
    {
        if(s<0 || d<0 || s>=totalnodes || d>=totalnodes)
        {
            cout<<"INVALID NODE INDEX.\n";
            return;
        }
        bool updated=false;
        for(auto &x:G[s])
            if(x.first==d)
            {
                 x.second=w; 
                 updated = true;
            }
        for(auto &x:G[d])
            if(x.first==s)
             {
                  x.second=w;
            }
        if(!updated)
            cout <<"NO ROAD FOUND BETWEEN "<<s<<" AND "<<d<<" TO UPDATE.\n";
        else
            cout<<"TRAFFIC WEIGHT UPDATED.\n";
    }
    int Totalnodes()
    {
        return totalnodes;
    }

    int Calculatedistance(int s, int d)
    {
        if(coordinates[s].first==-1 || coordinates[d].first==-1)
        {
            cout<<"COORDINATES NOT SET FOR ONE OR BOTH NODES.\n";
            return INT_MAX;
        }
        int x1=coordinates[s].first,y1 =coordinates[s].second;
        int x2=coordinates[d].first,y2 =coordinates[d].second;
        return (int)sqrt((double)(x2-x1)*(x2-x1)+(double)(y2-y1)*(y2-y1));
    }

    bool Hasroads()
    {
        for(int i=0;i<8;i++)
            if(!G[i].empty()) return true;
        return false;
    }

    bool Validnode(int n)
    {
        return (n>=0 && n<totalnodes);
    }
};

// CLASS — VEHICLES  

class VEHICLES
{
    static int count;
    static int Maxfuel;
    string id;
    int speed;
    string type;
    int loc;
    int fuel;
    bool available;
    vector<int> path;
public:
    VEHICLES()
    {
        id="";
        type="";
        loc=0;
        fuel=0;
        speed=30;
        available=true;
    }
    void Setvehicle(string id, string type, int loc, int s)
    {
        this->id=id;
        this->type=type;
        this->loc=loc;
        this->fuel=Maxfuel;
        this->speed=s;
        this->available=true;
        count++;
    }

    static int vehiclecount()  
    { 
        return count; 
    }
    static void Setmaxfuel(int x) 
    { 
        Maxfuel=x; 
    }
    static int Getmaxfuel()    
    { 
        return Maxfuel;
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
    int Getlocation() 
    { 
        return loc; 
    }
    bool Isavailable() 
    { 
        return available; 
    }
    int Getfuel()     
    { 
         return fuel; 
    }
    void Assignemergency()        
    {  
        available=false; 
    }
    void Assignpath(vector<int> p)
    { 
         path=p;
     }
    void Updatelocation(int newloc)
    { 
         loc=newloc; 
    }

    void Consumefuel(int cost)
    {
        fuel-=cost;
         if(fuel<0) 
        fuel = 0;
     }
    void Completemission()
    {
        available=true;
     cout<<"VEHICLE "<<id <<" IS NOW AVAILABLE AGAIN\n";
    }
    void Refuel()
    {
        fuel=Maxfuel;
         cout<<"VEHICLE " << id << " REFUELLED TO "<<Maxfuel <<"\n";
    }
    void Checkandrefuel()
    {
        if(fuel==0)
        {
             fuel=Maxfuel;
             cout<<"VEHICLE "<<id<<" AUTO-REFUELLED (WAS EMPTY)\n";
        }
    }
    double CalculateTime(int distance)
    {
         if(speed<=0) 
        return 0.0;
         return (double)distance/speed;
    }
};

int  VEHICLES::count=0;
int VEHICLES::Maxfuel=0;

//  CLASS — EMERGENCY  
class EMERGENCY
{
public:
     int loc;
     string type;
    int severity;
    bool active;
     EMERGENCY() 
    { 
        active = true; 
    }
};

// CLASS — PATHFINDER 

class PATHFINDER
{
public:
    void Dijkstra(int src,CITY &city,vector<int> &dist,vector<int> &parent)
    {
         int n=city.Totalnodes();
         dist.assign(n, INT_MAX);
         parent.assign(n, -1);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        dist[src]=0;
         pq.push({0,src});
 
        while(!pq.empty())
        {
            int d=pq.top().first;
            int u=pq.top().second;
            pq.pop();
             if(d != dist[u])
             continue;
            for(auto &x:city.G[u])
            {
                int v=x.first,w= x.second;
                  if(dist[v]>dist[u] + w)
                {
                    dist[v]=dist[u] + w;
                    parent[v]=u;
                     pq.push({dist[v], v});
                }
            }
         }
    }

    vector<int> CalPath(int src,int dest,CITY &city)
    {
         vector<int>dist,parent;
        Dijkstra(src,city,dist,parent);
        vector<int> path;
         if(dist[dest]==INT_MAX) 
        return path;
        for(int v=dest;v!=-1;v=parent[v])
            path.push_back(v);
        reverse(path.begin(), path.end());
         return path;
    }
    int CalCost(int src,int dest,CITY &city)
    {
         vector<int> dist,parent;
        Dijkstra(src,city,dist,parent);
        return dist[dest];
     }
     vector<int> CalPathandCost(int src,int dest,CITY &city,int &cost)
    {
        vector<int> dist,parent;
         Dijkstra(src,city,dist,parent);
        cost=dist[dest];
        vector<int> path;
        if(cost==INT_MAX) 
         return path;
         for(int v=dest;v!=-1;v=parent[v])
            path.push_back(v);
        reverse(path.begin(),path.end());
        return path;
     }
};

// CLASS — DISPATCHER

class DISPATCHER
{
public:
     int Findvehicle(VEHICLES V[],int n,int loc,string etype,CITY &city,PATHFINDER &pf)
    {
        int best=-1;
        int bestCost=INT_MAX;
         string requiredType="";
        if(etype=="Medical")     
        requiredType="Ambulance";
         else if(etype=="Fire")  
         requiredType="Fire";
        else if(etype=="Police")
          requiredType="Police";
        int notAvailable=0,wrongType=0,noPath=0,noFuel=0;
         for(int i=0;i<n;i++)
        {
            if(!V[i].Isavailable()) 
             { 
                 notAvailable++; 
                 continue; 
             }
            if(!requiredType.empty() && V[i].Gettype()!=requiredType) 
            {
                 wrongType++; 
                 continue; 
             }
 
             int cost=pf.CalCost(V[i].Getlocation(),loc,city);
            if(cost==INT_MAX) 
             { 
                noPath++; 
                continue; 
            }
             if(V[i].Getfuel()<cost) 
            { 
                noFuel++; 
                continue; 
             }

            if(cost<bestCost) 
             { 
                bestCost=cost; 
                best=i; 
             }
        }

        if(best==-1 && !requiredType.empty())
        {
            cout<<"NO "<<requiredType<<" AVAILABLE.";
            if(notAvailable>0) 
            { 
                  cout <<" ("<<notAvailable<<" BUSY)"; 
            }
            if(noFuel>0)       
            { 
                cout<<" (" << noFuel<< " LOW FUEL)"; 
             }
             if(noPath>0)       
            { 
                cout<<" (" << noPath<< " NO PATH)"; 
            }
            cout<<"\nCHECKING OTHER VEHICLE TYPES...\n";

            noPath=0;noFuel=0;
             for(int i=0;i<n;i++)
            {
                if(!V[i].Isavailable()) 
                continue;
                int cost=pf.CalCost(V[i].Getlocation(),loc,city);
                 if(cost==INT_MAX) 
                { 
                    noPath++; 
                    continue; 
                }
                if(V[i].Getfuel()<cost) 
                { 
                    noFuel++; 
                     continue; 
                }

                if(cost<bestCost) 
                { 
                     bestCost=cost; 
                    best=i; 
                }
            }
            if(best==-1)
            {
                if(noFuel > 0) 
                cout<<"SOME VEHICLES HAVE INSUFFICIENT FUEL. USE REFUEL OPTION.\n";
                 if(noPath>0)
                cout << "NO REACHABLE VEHICLE EXISTS. CHECK ROAD NETWORK.\n";
            }
        }
         return best;
    }

    int FindBestEmergency(vector<EMERGENCY> &emergencies,VEHICLES V[],int vn,CITY &city,PATHFINDER &pf)
    {
        int bestEmergency=-1;
         double bestScore=-1.0;
        for(int j=0;j<(int)emergencies.size();j++)
        {
            if(!emergencies[j].active) 
            continue;
             int minCost=INT_MAX;
            for(int k=0;k<vn;k++)
            {
                if(!V[k].Isavailable()) 
                continue;
                int cost=pf.CalCost(V[k].Getlocation(),emergencies[j].loc,city);
                 if(cost<minCost) 
                minCost=cost;
            }
            if(minCost==INT_MAX) 
            continue;

            double score=(double)emergencies[j].severity/(minCost + 1);
            if(score>bestScore)
            {
                bestScore=score;
                 bestEmergency=j;
            }
        }
        return bestEmergency;
    }
};
struct VehicleSnapshot
{
    string id;
     string type;
    int loc;
     int fuel;
    bool available;
    vector<int> path;
};

struct EmergencySnapshot
{
    int loc;
    string type;
     int severity;
    bool active;
};
struct SharedState
{
    vector<pair<int,int>>nodeCoords; 
    vector<pair<int,int>>edges;    
     vector<pair<float,float>>nodePos;
    vector<int> edgeWeights; 
     vector<VehicleSnapshot> vehicles;
    vector<EmergencySnapshot>emergencies;
     mutable mutex mtx;
    atomic<bool> running{true};
};



//  SFMLSimulation 
class SFMLSimulation
{
    static constexpr unsigned WIN_W  = 1100u;
    static constexpr unsigned WIN_H  = 750u;
    static constexpr float NODE_R = 20.f;
    static constexpr float MARGIN = 80.f;

    SharedState &state;
    sf::Font font;
    bool fontLoaded = false;

    // ---- colour helpers ----
    sf::Color vehicleColor(const string &type) const
    {
        if(type == "Ambulance") 
        return sf::Color(50,  220, 120);
        if(type == "Fire")      
        return sf::Color(230, 80,  50);
        if(type == "Police")    
        return sf::Color(80,  140, 230);
        return sf::Color(200, 200, 200);
    }

    sf::Color emergencyColor(const string &type, bool active) const
    {
        if(!active) return sf::Color(80, 80, 80);
        if(type == "Medical") 
        return sf::Color(255, 100, 100, 200); // Red for medical
        if(type == "Fire")   
         return sf::Color(255, 165, 0, 200);   // Orange for fire
        if(type == "Police")  
        return sf::Color(0, 0, 255, 200);     // Blue for police
        return sf::Color(255, 255, 0, 200); // Yellow default
    }

    // ---- draw a thick line between two points ----
    // SFML 3: setPosition({x,y}), setSize({w,h}), setRotation(sf::degrees(a))
    void drawLine(sf::RenderWindow &win,
                  sf::Vector2f a, sf::Vector2f b,
                  sf::Color col, float thickness = 2.f)
    {
        sf::Vector2f dir = b - a;
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if(len < 0.001f) return;

        sf::RectangleShape line({len, thickness});      // SFML 3: brace-init vector
        line.setPosition(a);                            // SFML 3: vector overload
        line.setFillColor(col);
        float angleDeg = std::atan2(dir.y, dir.x) * 180.f / 3.14159265f;
        line.setRotation(sf::degrees(angleDeg));        // SFML 3: sf::degrees()
        win.draw(line);
    }

    // ---- draw centred label (only when font loaded) ----
    // SFML 3: sf::Text(font, string, charSize)  — constructor-based
    void drawText(sf::RenderWindow &win, const string &str,float x, float y, unsigned size, sf::Color col, int align = 0)
    {
        if(!fontLoaded) return;
        sf::Text t(font, str, size);                    // SFML 3: unified constructor
        t.setFillColor(col);
        sf::FloatRect b = t.getLocalBounds();
        float px = x;
        if(align == 0) // center
            px = x - b.size.x / 2.f;
        else if(align == 1) // left
            px = x;
        else if(align == 2) // right
            px = x - b.size.x;
        t.setPosition({px, y - b.size.y / 2.f - b.position.y});
        win.draw(t);
    }

    // ---- smooth interpolation along a multi-node path ----
    sf::Vector2f interpolatePath(const vector<int> &path, float t,const vector<pair<float,float>> &nodePos)
    {
        if(path.empty()) return {0.f, 0.f};
        if(path.size() == 1)
            return {nodePos[path[0]].first, nodePos[path[0]].second};

        float totalSegs = float(path.size() - 1);
        float scaled=t * totalSegs;
        int seg=min(int(scaled), int(totalSegs) - 1);
        float frac=scaled - float(seg);
        sf::Vector2f a = {nodePos[path[seg  ]].first, nodePos[path[seg  ]].second};
        sf::Vector2f b = {nodePos[path[seg+1]].first, nodePos[path[seg+1]].second};
        return a + frac * (b - a);
    }

public:
    explicit SFMLSimulation(SharedState &s) : state(s)
    {
        // Try to load a system font; rendering continues without labels if unavailable
        bool loaded = font.openFromFile("C:/Windows/Fonts/arial.ttf");
        if(!loaded)
            loaded = font.openFromFile("C:/Windows/Fonts/calibri.ttf");
        if(!loaded)
            loaded = font.openFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf");
        if(!loaded)
            loaded = font.openFromFile("/System/Library/Fonts/Helvetica.ttc"); // macOS fallback
        fontLoaded = loaded && !font.getInfo().family.empty();
    }

    // Runs inside a background thread — owns its own sf::RenderWindow
    void run()
    {
        // SFML 3: VideoMode takes sf::Vector2u {w,h} — brace-init
        sf::RenderWindow window(
            sf::VideoMode({WIN_W, WIN_H}),
            "Emergency Dispatch — City Visualizer",
            sf::Style::Titlebar | sf::Style::Close);   // sf::Style still valid for non-fullscreen
        window.setFramerateLimit(60u);
        vector<float> animT; // per-vehicle animation progress [0..1]
        while(window.isOpen() && state.running.load())
        {
            // ---- SFML 3 event loop: pollEvent() -> std::optional<sf::Event> ----
            while(const std::optional event = window.pollEvent())
            {
                // SFML 3: event->is<T>() instead of event.type == sf::Event::Closed
                if(event->is<sf::Event::Closed>())
                {
                    window.close();
                    state.running = false;
                }
            }

            // ---- snapshot under lock ----
            vector<pair<float,float>> nodePos;
            vector<pair<int,int>> nodeCoords;
            vector<pair<int,int>> edges;
            vector<int>edgeWeights;
            vector<VehicleSnapshot> vehicles;
            vector<EmergencySnapshot> emergencies;
            {
                lock_guard<mutex> lk(state.mtx);
                nodePos = state.nodePos;
                nodeCoords= state.nodeCoords;
                edges = state.edges;
                edgeWeights= state.edgeWeights;
                vehicles = state.vehicles;
                emergencies = state.emergencies;
            }

            // Grow animation table to match vehicle count
            while(animT.size() < vehicles.size()) animT.push_back(0.f);

            // Advance animation for dispatched vehicles
            for(int i = 0; i < (int)vehicles.size(); i++)
            {
                if(!vehicles[i].path.empty() && !vehicles[i].available)
                {
                    animT[i] += 0.0005f; // Slower animation for full movement // Slower animation
                    if(animT[i] > 1.f) animT[i] = 1.f;
                }
                else
                {
                    animT[i] = 0.f;
                }
            }

            // ---- render ----
            window.clear(sf::Color(18, 20, 30));
            // ---- legend panel (right strip) ----
            sf::RectangleShape legend({200.f, float(WIN_H)});   // SFML 3: brace-init
            legend.setPosition({float(WIN_W) - 200.f, 0.f});
            legend.setFillColor(sf::Color(28, 30, 45));
            window.draw(legend);
            drawText(window, "LEGEND",
                     float(WIN_W) - 190.f, 30.f, 16, sf::Color(200,200,255), 1);
            auto drawLegendDot = [&](float y, sf::Color col, const string &label)
            {
                sf::CircleShape dot(8.f);
                dot.setFillColor(col);
                dot.setPosition({float(WIN_W) - 118.f, y});   // SFML 3: {x,y}
                window.draw(dot);
                drawText(window, label, float(WIN_W) - 100.f, y + 4.f, 14, col, 1);
            };

            drawLegendDot(62.f,sf::Color(100,160,255),"Node");
            drawLegendDot(94.f,sf::Color(50, 220,120),"Ambulance");
            drawLegendDot(126.f,sf::Color(230,80,50),"Fire Truck");
            drawLegendDot(158.f,sf::Color(80, 140,230),"Police Car");
            drawLegendDot(190.f,sf::Color(255,100,100), "Medical Emergency");
            drawLegendDot(222.f,sf::Color(255,165,0), "Fire Emergency");
            drawLegendDot(254.f,sf::Color(0, 0,255), "Police Emergency");
            drawLegendDot(286.f,sf::Color(80,80, 80),"Resolved");
            // ---- vehicle status list ----
            drawText(window,"VEHICLES",float(WIN_W) -190.f,330.f, 16,sf::Color(200,200,255),1);
            for(int i=0;i<(int)vehicles.size();i++)
            {
                string status =vehicles[i].available?"FREE":"BUSY";
                string line1=vehicles[i].id+"  "+status;
                string line2="Fuel:"+ to_string(vehicles[i].fuel)+"  @" + to_string(vehicles[i].loc);
                float yBase=350.f + i * 50.f;
                sf::Color vc=vehicleColor(vehicles[i].type);
                drawText(window,line1,float(WIN_W)-190.f,yBase,14,vc,1);
                drawText(window, line2,float(WIN_W)-190.f,yBase+15.f,13,sf::Color(180,180,180), 1);
            }

            // ---- placeholder when city not yet set up ----
            if(nodePos.empty())
            {
                drawText(window, "Set city locations in console",
                         float(WIN_W - 200) / 2.f, float(WIN_H) / 2.f,
                         18, sf::Color(130,130,150));
                window.display();
                continue;
            }
            // ---- road edges ----
            for(size_t idx = 0; idx < edges.size(); ++idx)
            {
                auto &e = edges[idx];
                if(e.first  >= (int)nodePos.size()) continue;
                if(e.second >= (int)nodePos.size()) continue;
                sf::Vector2f A = {nodePos[e.first ].first, nodePos[e.first ].second};
                sf::Vector2f B = {nodePos[e.second].first, nodePos[e.second].second};
                drawLine(window, A, B, sf::Color(60, 70, 100), 2.f);

                // Draw weight in the middle
                if(idx < edgeWeights.size())
                {
                    sf::Vector2f mid = (A + B) / 2.f;
                    drawText(window, to_string(edgeWeights[idx]), mid.x, mid.y, 12, sf::Color(150,150,150));
                }
            }

            // ---- highlighted dispatch paths ----
            for(int i = 0; i < (int)vehicles.size(); i++)
            {
                const auto &vh = vehicles[i];
                if(vh.path.size() < 2) continue;
                sf::Color pc = vehicleColor(vh.type);
                pc.a = 130;
                for(int j = 0; j + 1 < (int)vh.path.size(); j++)
                {
                    int na = vh.path[j], nb = vh.path[j+1];
                    if(na >= (int)nodePos.size() || nb >= (int)nodePos.size()) continue;
                    sf::Vector2f A = {nodePos[na].first, nodePos[na].second};
                    sf::Vector2f B = {nodePos[nb].first, nodePos[nb].second};
                    drawLine(window, A, B, pc, 4.f);
                }
            }

            // ---- city nodes ----
            for(int i = 0; i < (int)nodePos.size(); i++)
            {
                float cx = nodePos[i].first;
                float cy = nodePos[i].second;
                // Glow ring
                sf::CircleShape ring(NODE_R + 4.f);
                ring.setOrigin({NODE_R + 4.f, NODE_R + 4.f});          // SFML 3: {x,y}
                ring.setPosition({cx, cy});
                ring.setFillColor(sf::Color::Transparent);
                ring.setOutlineThickness(2.f);
                ring.setOutlineColor(sf::Color(60, 90, 160, 160));
                window.draw(ring);

                // Node circle
                sf::CircleShape node(NODE_R);
                node.setOrigin({NODE_R, NODE_R});
                node.setPosition({cx, cy});
                node.setFillColor(sf::Color(40, 80, 160));
                node.setOutlineThickness(2.f);
                node.setOutlineColor(sf::Color(100, 160, 255));
                window.draw(node);

                drawText(window, to_string(i), cx, cy, 15, sf::Color(230,240,255));
                if(i < (int)nodeCoords.size() && nodeCoords[i].first != -1)
                {
                    string coordStr = "(" + to_string(nodeCoords[i].first) + "," + to_string(nodeCoords[i].second) + ")";
                    drawText(window, coordStr, cx, cy + 20.f, 12, sf::Color(200,200,200));
                }
            }

            // ---- emergencies ----
            for(auto &em : emergencies)
            {
                if(em.loc < 0 || em.loc >= (int)nodePos.size()) continue;
                float cx = nodePos[em.loc].first;
                float cy = nodePos[em.loc].second;
                float radius = 10.f + em.severity * 1.8f;
                sf::CircleShape emark(radius);
                emark.setOrigin({radius, radius});
                emark.setPosition({cx, cy - NODE_R - radius - 4.f});
                emark.setFillColor(emergencyColor(em.type, em.active));
                emark.setOutlineThickness(1.5f);
                emark.setOutlineColor(
                    sf::Color(255, 220, 0, em.active ? 255u : 80u));
                window.draw(emark);
                if(em.active)
                    drawText(window, "!",
                             cx, cy - NODE_R - radius - 4.f,
                             16, sf::Color::White);
            }

            // ---- vehicles ----
            for(int i=0;i<(int)vehicles.size();i++)
            {
                const auto &vh = vehicles[i];
                sf::Vector2f vpos;

                if(!vh.path.empty() && !vh.available)
                    vpos = interpolatePath(vh.path, animT[i], nodePos);
                else
                {
                    if(vh.loc < 0 || vh.loc >= (int)nodePos.size()) continue;
                    vpos = {nodePos[vh.loc].first, nodePos[vh.loc].second};
                }

                sf::Color vc = vehicleColor(vh.type);
                float offsetX = float(i) * 5.f;   // slight spread so vehicles don't overlap

                // Diamond (rotated square)
                sf::RectangleShape vbody({14.f, 14.f});
                vbody.setOrigin({7.f, 7.f});
                vbody.setPosition({vpos.x + offsetX, vpos.y - 6.f});
                vbody.setRotation(sf::degrees(45.f));        // SFML 3: sf::degrees()
                vbody.setFillColor(vc);
                vbody.setOutlineThickness(1.5f);
                vbody.setOutlineColor(sf::Color(255,255,255,180));
                window.draw(vbody);

                // Vehicle ID label
                string shortId = vh.id.size() > 5 ? vh.id.substr(0, 5) : vh.id;
                drawText(window, shortId,
                         vpos.x + offsetX, vpos.y + 16.f, 12, vc);

                // Fuel bar
                float maxF     = float(VEHICLES::Getmaxfuel());
                float fuelRatio = (maxF > 0.f) ? float(vh.fuel) / maxF : 0.f;
                float barW     = 30.f, barH = 4.f;
                float barX     = vpos.x + offsetX - barW / 2.f;
                float barY     = vpos.y + 26.f;

                sf::RectangleShape barBg({barW, barH});
                barBg.setPosition({barX, barY});
                barBg.setFillColor(sf::Color(60, 60, 60));
                window.draw(barBg);

                sf::RectangleShape barFg({barW * fuelRatio, barH});
                barFg.setPosition({barX, barY});
                barFg.setFillColor(fuelRatio > 0.4f
                                   ? sf::Color(80,  220, 80)
                                   : sf::Color(220, 80,  80));
                window.draw(barFg);
            }

            // ---- title ----
            drawText(window, "VEHICLE EMERGENCY DISPATCH SYSTEM",
                     float(WIN_W - 200) / 2.f, 20.f, 20,
                     sf::Color(255, 100, 100));

            window.display();
        }
    }
};

// ---------------------------------------------------------------
//  Helper functions — push snapshots into SharedState
//  Called from the console (main) thread after each state change.
// ---------------------------------------------------------------

static void SyncCityToState(CITY &city, SharedState &state)
{
    lock_guard<mutex> lk(state.mtx);

    const int n = city.Totalnodes(); // 8

    constexpr float DRAW_W = float(1100u - 200u);   // exclude legend
    constexpr float DRAW_H = float(750u);
    constexpr float MG     = 80.f;

    // Find coordinate extents for normalisation
    int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
    for(int i = 0; i < n; i++)
    {
        if(city.coordinates[i].first == -1) continue;
        minX = min(minX, city.coordinates[i].first);
        maxX = max(maxX, city.coordinates[i].first);
        minY = min(minY, city.coordinates[i].second);
        maxY = max(maxY, city.coordinates[i].second);
    }

    float rangeX = float(max(1, maxX - minX));
    float rangeY = float(max(1, maxY - minY));

    state.nodePos.resize(n);
    state.nodeCoords.resize(n);
    for(int i = 0; i < n; i++)
    {
        state.nodeCoords[i] = city.coordinates[i];
        if(city.coordinates[i].first == -1)
        {
            state.nodePos[i] = {-200.f, -200.f}; // off-screen placeholder
            continue;
        }
        float px = MG + (float(city.coordinates[i].first  - minX) / rangeX) * (DRAW_W - 2.f*MG);
        float py = MG + (float(city.coordinates[i].second - minY) / rangeY) * (DRAW_H - 2.f*MG);
        state.nodePos[i] = {px, py};
    }

    // Collect unique undirected edges with weights
    state.edges.clear();
    state.edgeWeights.clear();
    for(int u = 0; u < n; u++)
        for(auto &nb : city.G[u])
            if(nb.first > u)
            {
                state.edges.push_back({u, nb.first});
                state.edgeWeights.push_back(nb.second);
            }
}

static void SyncVehiclesToState(VEHICLES V[], int vehicleIdx, SharedState &state)
{
    lock_guard<mutex> lk(state.mtx);
    state.vehicles.resize(vehicleIdx);
    for(int i=0;i<vehicleIdx;i++)
    {
        state.vehicles[i].id= V[i].Getid();
        state.vehicles[i].type=V[i].Gettype();
        state.vehicles[i].loc=V[i].Getlocation();
        state.vehicles[i].fuel=V[i].Getfuel();
        state.vehicles[i].available=V[i].Isavailable();
    }
}
static void SyncEmergenciesToState(vector<EMERGENCY> &emergencies, SharedState &state)
{
    lock_guard<mutex> lk(state.mtx);
    state.emergencies.resize(emergencies.size());
    for(int i = 0; i < (int)emergencies.size(); i++)
    {
        state.emergencies[i].loc      = emergencies[i].loc;
        state.emergencies[i].type     = emergencies[i].type;
        state.emergencies[i].severity = emergencies[i].severity;
        state.emergencies[i].active   = emergencies[i].active;
    }
}

static void SyncDispatchToState(int vIdx, const vector<int> &path,
                                VEHICLES V[], int totalVehicles, SharedState &state)
{
    lock_guard<mutex> lk(state.mtx);
    state.vehicles.resize(totalVehicles);
    for(int i = 0; i < totalVehicles; i++)
    {
        state.vehicles[i].id        = V[i].Getid();
        state.vehicles[i].type      = V[i].Gettype();
        state.vehicles[i].loc       = V[i].Getlocation();
        state.vehicles[i].fuel      = V[i].Getfuel();
        state.vehicles[i].available = V[i].Isavailable();
    }
    if(vIdx >= 0 && vIdx < (int)state.vehicles.size())
        state.vehicles[vIdx].path = path;
}

//  ORIGINAL main()


int main()
{
    srand((unsigned)time(0));
    int vehicleIdx = 0;
    int MaxVeh = 5;
    VEHICLES *V = new VEHICLES[MaxVeh];
    CITY city(15, 15);
    PATHFINDER pf;
    DISPATCHER dispatcher;

    vector<EMERGENCY> emergencies;

    int ch;
    cout << "WELCOME TO EMERGENCY VEHICLE DISPATCH SYSTEM!\n";
    VEHICLES::Setmaxfuel(100);

    // --------- ADDED SFML CODE START (launch renderer thread) ---------
    SharedState sfmlState;
    SFMLSimulation sfmlSim(sfmlState);

    thread sfmlThread([&]() {
        sfmlSim.run();
    });
    // --------- ADDED SFML CODE END (launch renderer thread) ---------

    while(true)
    {
        cout << "\n1.BUILD CITY\n2.ADD VEHICLE\n3.CREATE EMERGENCY\n4.DISPATCH VEHICLE\n5.EXIT\n";
        cout << "ENTER YOUR CHOICE: ";
        ch = SafeInput();

        switch(ch)
        {
            case 1:
            {
                bool c = true;
                while(c)
                {
                    cout << "\n1.CHANGE GRID SIZE\n2.ADD LOCATION\n3.ADD ROAD\n"
                         << "4.VIEW NEIGHBOURHOOD\n5.GET ROAD WEIGHT\n6.UPDATE TRAFFIC\n"
                         << "7.TOTAL LOCATIONS\n8.CALCULATE DISTANCE\n9.EXIT\n";
                    int n = SafeInput();

                    switch(n)
                    {
                        case 1:
                            cout << "NOTE: Changing grid size does not affect totalnodes (fixed at 8).\n";
                            break;
                        case 2:
                            city.Setlocations();
                            // --------- ADDED SFML CODE START ---------
                            SyncCityToState(city, sfmlState);
                            // --------- ADDED SFML CODE END ---------
                            break;
                        case 3:
                            city.Citygrid();
                            // --------- ADDED SFML CODE START ---------
                            SyncCityToState(city, sfmlState);
                            // --------- ADDED SFML CODE END ---------
                            break;
                        case 4:
                            city.Neighbour();
                            break;
                        case 5:
                        {
                            cout << "ENTER SOURCE AND DESTINATION: ";
                            int s = SafeInput();
                            int d = SafeInput();
                            if(!city.Validnode(s) || !city.Validnode(d))
                                cout << "INVALID NODE INDEX.\n";
                            else
                                city.Getweight(s, d);
                            break;
                        }
                        case 6:
                        {
                            cout << "ENTER SOURCE DESTINATION WEIGHT: ";
                            int s = SafeInput();
                            int d = SafeInput();
                            int w = SafeInput();
                            city.Updatetraffic(s, d, w);
                            // --------- ADDED SFML CODE START ---------
                            SyncCityToState(city, sfmlState);
                            // --------- ADDED SFML CODE END ---------
                            break;
                        }
                        case 7:
                            cout << "TOTAL LOCATIONS: " << city.Totalnodes() << endl;
                            break;
                        case 8:
                        {
                            cout << "ENTER SOURCE AND DESTINATION: ";
                            int s = SafeInput();
                            int d = SafeInput();
                            if(!city.Validnode(s) || !city.Validnode(d))
                                cout << "INVALID NODE INDEX.\n";
                            else
                            {
                                int dist = city.Calculatedistance(s, d);
                                if(dist != INT_MAX)
                                    cout << "EUCLIDEAN DISTANCE: " << dist << endl;
                            }
                            break;
                        }
                        case 9:
                            c = false;
                            break;
                        default:
                            cout << "INVALID OPTION.\n";
                    }
                }
                break;
            }

            case 2:
            {
                bool b = true;
                while(b)
                {
                    cout << "\n1 AMBULANCE\n2 FIRE\n3 POLICE\n4 EXIT\n5 VIEW\n"
                         << "6 REFUEL VEHICLE\n7 MARK VEHICLE AVAILABLE\n";
                    int n = SafeInput();

                    if(vehicleIdx >= MaxVeh && n < 4)
                    {
                        cout << "VEHICLE LIMIT REACHED (" << MaxVeh << ").\n";
                        break;
                    }

                    switch(n)
                    {
                        case 1:
                        case 2:
                        case 3:
                        {
                            string vnum = SafeStringInput("ENTER VEHICLE NO: ");

                            int startLoc;
                            while(true)
                            {
                                startLoc = SafeInput("ENTER STARTING LOCATION (0-" +
                                                     to_string(city.Totalnodes()-1) + "): ");
                                if(city.Validnode(startLoc)) break;
                                cout << "INVALID LOCATION. MUST BE IN [0,"
                                     << city.Totalnodes()-1 << "].\n";
                            }

                            if(n == 1)      V[vehicleIdx].Setvehicle("AMB"  + vnum, "Ambulance", startLoc, 45);
                            else if(n == 2) V[vehicleIdx].Setvehicle("FIRE" + vnum, "Fire",      startLoc, 35);
                            else            V[vehicleIdx].Setvehicle("POL"  + vnum, "Police",    startLoc, 40);

                            cout << "VEHICLE ADDED AT LOCATION " << startLoc << ".\n";
                            vehicleIdx++;
                            // --------- ADDED SFML CODE START ---------
                            SyncVehiclesToState(V, vehicleIdx, sfmlState);
                            // --------- ADDED SFML CODE END ---------
                            break;
                        }
                        case 4:
                            b = false;
                            break;
                        case 5:
                        {
                            if(vehicleIdx == 0) { cout << "NO VEHICLES ADDED YET\n"; break; }
                            for(int j = 0; j < vehicleIdx; j++)
                                cout << V[j].Getid()
                                     << "  TYPE:"   << V[j].Gettype()
                                     << "  FUEL:"   << V[j].Getfuel()
                                     << "  LOC:"    << V[j].Getlocation()
                                     << "  STATUS:" << (V[j].Isavailable() ? "AVAILABLE" : "BUSY")
                                     << endl;
                            break;
                        }
                        case 6:
                        {
                            if(vehicleIdx == 0) { cout << "NO VEHICLES ADDED\n"; break; }
                            int idx = SafeInput("ENTER VEHICLE INDEX (0 TO " +
                                                to_string(vehicleIdx-1) + "): ");
                            if(idx < 0 || idx >= vehicleIdx)
                                cout << "INVALID INDEX.\n";
                            else
                            {
                                V[idx].Refuel();
                                // --------- ADDED SFML CODE START ---------
                                SyncVehiclesToState(V, vehicleIdx, sfmlState);
                                // --------- ADDED SFML CODE END ---------
                            }
                            break;
                        }
                        case 7:
                        {
                            if(vehicleIdx == 0) { cout << "NO VEHICLES ADDED\n"; break; }
                            int idx = SafeInput("ENTER VEHICLE INDEX (0 TO " +
                                                to_string(vehicleIdx-1) + "): ");
                            if(idx < 0 || idx >= vehicleIdx)
                                cout << "INVALID INDEX.\n";
                            else
                            {
                                V[idx].Completemission();
                                // --------- ADDED SFML CODE START ---------
                                SyncVehiclesToState(V, vehicleIdx, sfmlState);
                                // --------- ADDED SFML CODE END ---------
                            }
                            break;
                        }
                        default:
                            cout << "INVALID OPTION.\n";
                    }
                }
                break;
            }

            case 3:
            {
                bool e_menu = true;
                while(e_menu)
                {
                    cout << "\n1.ADD EMERGENCY\n2.VIEW EMERGENCIES\n3.MARK RESOLVED\n4.EXIT\n";
                    int ch2 = SafeInput();

                    switch(ch2)
                    {
                        case 1:
                        {
                            EMERGENCY e;
                            cout << "ENTER LOCATION (0-" << city.Totalnodes()-1 << "): ";
                            e.loc = SafeInput();

                            if(!city.Validnode(e.loc))
                            {
                                cout << "INVALID LOCATION. MUST BE BETWEEN 0 AND "
                                     << city.Totalnodes()-1 << ".\n";
                                break;
                            }

                            e.severity = SafeInput("ENTER SEVERITY (1-10): ");

                            while(true)
                            {
                                e.type = SafeStringInput("ENTER TYPE (Medical/Fire/Police): ");
                                if(e.type == "Medical" || e.type == "Fire" || e.type == "Police")
                                    break;
                                cout << "INVALID TYPE. USE Medical / Fire / Police.\n";
                            }

                            e.active = true;
                            emergencies.push_back(e);
                            cout << "EMERGENCY ADDED.\n";
                            // --------- ADDED SFML CODE START ---------
                            SyncEmergenciesToState(emergencies, sfmlState);
                            // --------- ADDED SFML CODE END ---------
                            break;
                        }
                        case 2:
                        {
                            if(emergencies.empty()) { cout << "NO EMERGENCIES\n"; break; }
                            for(int j = 0; j < (int)emergencies.size(); j++)
                                cout << "ID: "       << j
                                     << "  LOC: "    << emergencies[j].loc
                                     << "  TYPE: "   << emergencies[j].type
                                     << "  SEV: "    << emergencies[j].severity
                                     << "  STATUS: " << (emergencies[j].active ? "ACTIVE" : "RESOLVED")
                                     << endl;
                            break;
                        }
                        case 3:
                        {
                            int id = SafeInput("ENTER EMERGENCY ID TO RESOLVE: ");
                            if(id >= 0 && id < (int)emergencies.size())
                            {
                                emergencies[id].active = false;
                                cout << "MARKED RESOLVED.\n";
                                // --------- ADDED SFML CODE START ---------
                                SyncEmergenciesToState(emergencies, sfmlState);
                                // --------- ADDED SFML CODE END ---------
                            }
                            else
                                cout << "INVALID ID.\n";
                            break;
                        }
                        case 4:
                            e_menu = false;
                            break;
                        default:
                            cout << "INVALID OPTION.\n";
                    }
                }
                break;
            }

            case 4:
            {
                if(emergencies.empty()) { cout << "NO EMERGENCIES REGISTERED.\n"; break; }

                if(!city.Hasroads())
                {
                    cout << "NO ROADS IN CITY. BUILD CITY ROADS FIRST (OPTION 1 > 3).\n";
                    break;
                }

                bool d_menu = true;
                while(d_menu)
                {
                    cout << "\n1.VIEW ACTIVE EMERGENCIES\n2.DISPATCH VEHICLE\n3.EXIT\n";
                    int ch3 = SafeInput();

                    switch(ch3)
                    {
                        case 1:
                        {
                            bool found = false;
                            for(int j = 0; j < (int)emergencies.size(); j++)
                            {
                                if(emergencies[j].active)
                                {
                                    cout << "ID: "     << j
                                         << "  LOC: "  << emergencies[j].loc
                                         << "  TYPE: " << emergencies[j].type
                                         << "  SEV: "  << emergencies[j].severity
                                         << endl;
                                    found = true;
                                }
                            }
                            if(!found) cout << "NO ACTIVE EMERGENCIES.\n";
                            break;
                        }

                        case 2:
                        {
                            int bestEmergency = dispatcher.FindBestEmergency(
                                                    emergencies, V, vehicleIdx, city, pf);

                            if(bestEmergency == -1)
                            {
                                cout << "NO ACTIVE EMERGENCIES TO DISPATCH.\n";
                                break;
                            }

                            cout << "RECOMMENDED EMERGENCY (SCORE-BASED): ID " << bestEmergency
                                 << "  (SEV: " << emergencies[bestEmergency].severity
                                 << ", TYPE: " << emergencies[bestEmergency].type << ")\n";
                            cout << "ENTER EMERGENCY ID TO DISPATCH (OR -1 TO USE RECOMMENDED): ";

                            int id = SafeInput();
                            if(id == -1) id = bestEmergency;

                            if(id < 0 || id >= (int)emergencies.size() || !emergencies[id].active)
                            {
                                cout << "INVALID OR RESOLVED EMERGENCY.\n";
                                break;
                            }

                            EMERGENCY &e = emergencies[id];

                            if(!city.Validnode(e.loc))
                            {
                                cout << "EMERGENCY LOCATION IS INVALID. CANNOT DISPATCH.\n";
                                break;
                            }

                            for(int k = 0; k < vehicleIdx; k++)
                                V[k].Checkandrefuel();

                            int v = dispatcher.Findvehicle(V, vehicleIdx, e.loc, e.type, city, pf);

                            if(v == -1)
                            {
                                cout << "NO SUITABLE VEHICLE AVAILABLE FOR THIS EMERGENCY.\n";
                                break;
                            }

                            int pathCost = 0;
                            vector<int> path = pf.CalPathandCost(
                                                   V[v].Getlocation(), e.loc, city, pathCost);

                            if(path.empty())
                            {
                                cout << "NO PATH AVAILABLE TO EMERGENCY LOCATION."
                                     << " CHECK ROAD NETWORK CONNECTIVITY.\n";
                                break;
                            }

                            V[v].Assignemergency();
                            V[v].Assignpath(path);
                            V[v].Updatelocation(e.loc);
                            V[v].Consumefuel(pathCost);

                            e.active = false;

                            double travelTime = V[v].CalculateTime(pathCost);

                            cout << "DISPATCHED " << V[v].Getid()
                                 << "  (TYPE: " << V[v].Gettype() << ")\n";
                            cout << "PATH: ";
                            for(int x : path) cout << x << " ";
                            cout << "\n";
                            cout << "ESTIMATED TRAVEL COST: " << pathCost << "\n";
                            cout << "ESTIMATED TRAVEL TIME: " << travelTime << " MIN\n";
                            cout << "FUEL REMAINING: " << V[v].Getfuel() << "\n";

                            // --------- ADDED SFML CODE START ---------
                            SyncDispatchToState(v, path, V, vehicleIdx, sfmlState);
                            SyncEmergenciesToState(emergencies, sfmlState);
                            // --------- ADDED SFML CODE END ---------

                            // Simulate travel time
                            cout << "Simulating travel...\n";
                            std::this_thread::sleep_for(std::chrono::seconds(10));

                            V[v].Completemission();

                            // --------- ADDED SFML CODE START ---------
                            SyncVehiclesToState(V, vehicleIdx, sfmlState);
                            // --------- ADDED SFML CODE END ---------
                            break;
                        }

                        case 3:
                            d_menu = false;
                            break;
                        default:
                            cout << "INVALID OPTION.\n";
                    }
                }
                break;
            }

            case 5:
                // --------- ADDED SFML CODE START ---------
                sfmlState.running = false;
                if(sfmlThread.joinable()) sfmlThread.join();
                // --------- ADDED SFML CODE END ---------
                delete[] V;
                cout << "GOODBYE!\n";
                return 0;

            default:
                cout << "INVALID CHOICE. PLEASE ENTER 1-5.\n";
        }
    }
}
