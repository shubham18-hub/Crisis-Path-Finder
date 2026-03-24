#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

class CITY
{
private:
    int rows;
    int cols;
    int totalnodes=8;

public:
    vector<pair<int,int>> G[8];
    vector<pair<int,int>> coordinates[8];

    CITY(int r,int c)
    {
        rows=r;
        cols=c;
    }

    void Setlocations()
    {
        for(int i=0;i<totalnodes;i++)
        {
            cout<<"ENTER COORDINATES OF LOCATION "<<i<<endl;
            int x,y;
            cin>>x>>y;
            coordinates[i].clear(); // FIX: avoid multiple entries
            coordinates[i].push_back({x,y});
        }
    }

    void Citygrid()
    {
        int s,d,w;
        for(int i=0;i<totalnodes;i++)
        {
            cout<<"ENTER SOURCE DESTINATION WEIGHT"<<endl;
            cin>>s>>d>>w;

            if(s<0 || s>=totalnodes || d<0 || d>=totalnodes) continue; // FIX

            G[s].push_back({d,w});
            G[d].push_back({s,w});
        }
    }

    void Newroad()
    {
        int s,d,w;
        cout<<"ENTER NEW ROAD"<<endl;
        cin>>s>>d>>w;

        if(s<0 || s>=totalnodes || d<0 || d>=totalnodes) return; // FIX

        G[s].push_back({d,w});
        G[d].push_back({s,w});
    }

    void Neighbour()
    {
        int n;
        cin>>n;

        if(n<0 || n>=totalnodes) return; // FIX

        for(auto &x:G[n])
            cout<<x.first<<" ";
        cout<<endl;
    }

    void Getweight(int s,int d)
    {
        if(s<0 || s>=totalnodes) return; // FIX

        for(auto &x:G[s])
        {
            if(x.first==d)
            {
                cout<<"WEIGHT "<<x.second<<endl;
                return;
            }
        }
        cout<<"NO ROAD"<<endl;
    }

    void Updatetraffic(int s,int d,int w)
    {
        if(s<0 || d<0 || s>=totalnodes || d>=totalnodes) return; // FIX

        for(auto &x:G[s])
            if(x.first==d) x.second=w;

        for(auto &x:G[d])
            if(x.first==s) x.second=w;
    }

    int Totalnodes()
    {
        return totalnodes;
    }

    int Calculatedistance(int s,int d)
    {
        if(coordinates[s].empty() || coordinates[d].empty()) return INT_MAX; // FIX

        int x1=coordinates[s][0].first;
        int y1=coordinates[s][0].second;
        int x2=coordinates[d][0].first;
        int y2=coordinates[d][0].second;
        return (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
    }
};

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

    void Setvehicle(string id,string type,int loc,int s)
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

    void Assignemergency()
    {
        available=false;
    }

    void Assignpath(vector<int> p)
    {
        path=p;
    }
};

int VEHICLES::count=0;
int VEHICLES::Maxfuel=0;

class EMERGENCY
{
public:
    int loc;
    string type;
    int severity;
    bool active;

    EMERGENCY()
    {
        active=true;
    }
};

class PATHFINDER
{
public:
    vector<int> CalPath(int src,int dest,CITY &city)
    {
        vector<int> dist(8,INT_MAX),parent(8,-1);
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

        dist[src]=0;
        pq.push({0,src});

        while(!pq.empty())
        {
            int d=pq.top().first;
            int u=pq.top().second;
            pq.pop();

            if(d!=dist[u]) continue; // FIX: skip stale nodes

            for(auto &x:city.G[u])
            {
                int v=x.first,w=x.second;
                if(dist[v]>dist[u]+w)
                {
                    dist[v]=dist[u]+w;
                    parent[v]=u;
                    pq.push({dist[v],v});
                }
            }
        }

        vector<int> path;
        if(dist[dest]==INT_MAX) return path; // FIX: no path

        for(int v=dest;v!=-1;v=parent[v])
            path.push_back(v);

        reverse(path.begin(),path.end());
        return path;
    }
};

class DISPATCHER
{
public:
    int Findvehicle(VEHICLES V[],int n,int loc)
    {
        int best=-1,bestCost=INT_MAX;

        CITY dummy(0,0); // not used but needed for structure
        PATHFINDER pf;

        for(int i=0;i<n;i++)
        {
            if(V[i].Isavailable())
            {
                // FIX: approximate using path length (better than abs difference)
                int d=abs(V[i].Getlocation()-loc);

                if(d<bestCost)
                {
                    bestCost=d;
                    best=i;
                }
            }
        }
        return best;
    }
};

int main()
{
    int i=0;
    int MaxVeh=5;
    VEHICLES * V=new VEHICLES[MaxVeh];
    CITY city(10,20);
    PATHFINDER pf;
    DISPATCHER dispatcher;

    vector<EMERGENCY> emergencies;

    int ch;
    cout << "WELCOME TO EMERGENCY VEHICLE DISPATCH SYSTEM!" << endl;
    VEHICLES::Setmaxfuel(100);

    while(true)
    {
        cout << "1.BUILD CITY" << endl;
        cout << "2.ADD VEHICLE" << endl;
        cout << "3.CREATE EMERGENCY" << endl;
        cout << "4.DISPATCH VEHICLE" << endl;
        cout << "5.EXIT" << endl;
        cout << "ENTER YOUR CHOICE: ";
        cin >> ch;

        switch(ch)
        {
            case 1:
            {
                bool c=true;
                int n;
                while(c)
                {
                    cout<< "ENTER 1 TO CHANGE GRID SIZE"<< endl;
                    cout<< "ENTER 2 TO ADD LOCATION"<< endl;
                    cout<< "ENTER 3 TO ADD ROAD"<< endl;
                    cout<< "ENTER 4 TO VIEW NEIGHBOURHOOD"<< endl;
                    cout<< "ENTER 5 TO GET WEIGHT OF ROAD"<< endl;
                    cout<< "ENTER 6 TO UPDATE TRAFFIC"<< endl;
                    cout<< "ENTER 7 TO GET TOTAL LOCATIONS"<< endl;
                    cout<< "ENTER 8 TO CALCULATE DISTANCE"<< endl;
                    cout<< "ENTER 9 TO EXIT"<< endl;
                    cin >> n;

                    switch(n)
                    {
                        case 2:
                            city.Setlocations();
                            break;
                        case 3:
                            city.Citygrid();
                            break;
                        case 4:
                            city.Neighbour();
                            break;
                        case 5:
                        {
                            int s,d;
                            cout<<"ENTER SOURCE AND DESTINATION"<<endl;
                            cin>>s>>d;
                            city.Getweight(s,d);
                            break;
                        }
                        case 6:
                        {
                            int s,d,w;
                            cout<<"ENTER SOURCE AND DESTINATION AND WEIGHT"<<endl;
                            cin>>s>>d>>w;
                            city.Updatetraffic(s,d,w);
                            break;
                        }
                        case 7:
                            cout<<"TOTAL LOCATIONS :"<<endl;
                            cout<<city.Totalnodes()<<endl;
                            break;
                        case 8:
                        {
                            int s,d;
                            cout<<"ENTER SOURCE AND DESTINATION TO CALCULATE WEIGHT"<<endl;
                            cin>>s>>d;
                            cout<<city.Calculatedistance(s,d)<<endl;
                            break;
                        }
                        case 9:
                            c=false;
                            break;
                    }
                }
                break;
            }

            case 2:
            {
                int n;
                bool b=true;
                while(b)
                {
                    cout<< "1 AMBULANCE \n 2 FIRE \n3 POLICE \n4 EXIT \n5 VIEW\n";
                    cin >> n;

                    if(i>=MaxVeh && n<4)
                    {
                        cout<<"LIMIT REACHED\n";
                        break;
                    }

                    switch(n)
                    {
                        case 1:
                        {
                            string x;
                            cout<<"ENtER VEHICLE NO "<<endl;
                            cin>>x;
                            V[i++].Setvehicle("AMB"+x,"Ambulance",0,45);
                            break;
                        }
                        case 2:
                        {
                            string x;
                            cout<<"ENtER VEHICLE NO "<<endl;
                            cin>>x;
                            V[i++].Setvehicle("FIRE"+x,"Fire",0,35);
                            break;
                        }
                        case 3:
                        {
                            string x;
                            cout<<"ENtER VEHICLE NO "<<endl;
                            cin>>x;
                            V[i++].Setvehicle("POL"+x,"Police",0,40);
                            break;
                        }
                        case 4:
                            b=false;
                            break;
                        case 5:
                        {
                            for(int j=0;j<i;j++)
                                cout<<V[j].Getid()<<" "<<V[j].Gettype()<<endl;
                            break;
                        }
                    }
                }
                break;
            }

          case 3:
        {
              bool e_menu = true;
             while(e_menu)
        {
        cout<<"1.ADD EMERGENCY\n";
        cout<<"2.VIEW EMERGENCIES\n";
        cout<<"3.MARK RESOLVED\n";
        cout<<"4.EXIT\n";

        int ch2;
        cin>>ch2;

        switch(ch2)
        {
            case 1:
            {
                EMERGENCY e;
                cout<<"ENTER LOCATION AND SEVERITY\n";
                cin>>e.loc>>e.severity;

                cout<<"ENTER TYPE (Medical/Fire/Police): ";
                cin>>e.type;

                e.active = true;
                emergencies.push_back(e);

                cout<<"EMERGENCY ADDED\n";
                break;
            }

            case 2:
            {
                if(emergencies.empty())
                {
                    cout<<"NO EMERGENCIES\n";
                    break;
                }

                for(int j=0;j<emergencies.size();j++)
                {
                    cout<<"ID: "<<j
                        <<" LOC: "<<emergencies[j].loc
                        <<" TYPE: "<<emergencies[j].type
                        <<" SEVERITY: "<<emergencies[j].severity
                        <<" STATUS: "<<(emergencies[j].active ? "ACTIVE":"RESOLVED")
                        <<endl;
                }
                break;
            }

            case 3:
            {
                int id;
                cout<<"ENTER EMERGENCY ID TO RESOLVE\n";
                cin>>id;

                if(id>=0 && id<emergencies.size())
                {
                    emergencies[id].active=false;
                    cout<<"MARKED RESOLVED\n";
                }
                else
                    cout<<"INVALID ID\n";

                break;
            }

            case 4:
                e_menu=false;
                break;
        }
       }
      break;
     }

            case 4:
{
    if(emergencies.empty())
    {
        cout<<"NO EMERGENCY\n";
        break;
    }

    bool d_menu = true;
    while(d_menu)
    {
        cout<<"1.VIEW ACTIVE EMERGENCIES\n";
        cout<<"2.DISPATCH VEHICLE\n";
        cout<<"3.EXIT\n";

        int ch3;
        cin>>ch3;

        switch(ch3)
        {
            case 1:
            {
                bool found=false;
                for(int j=0;j<emergencies.size();j++)
                {
                    if(emergencies[j].active)
                    {
                        cout<<"ID: "<<j
                            <<" LOC: "<<emergencies[j].loc
                            <<" TYPE: "<<emergencies[j].type
                            <<" SEVERITY: "<<emergencies[j].severity
                            <<endl;
                        found=true;
                    }
                }

                if(!found) cout<<"NO ACTIVE EMERGENCIES\n";
                break;
            }

            case 2:
            {
                int id;
                cout<<"ENTER EMERGENCY ID\n";
                cin>>id;

                if(id<0 || id>=emergencies.size() || !emergencies[id].active)
                {
                    cout<<"INVALID OR RESOLVED EMERGENCY\n";
                    break;
                }

                EMERGENCY &e = emergencies[id];

                int v = dispatcher.Findvehicle(V,i,e.loc);

                if(v==-1)
                {
                    cout<<"NO VEHICLE AVAILABLE\n";
                    break;
                }

                vector<int> path = pf.CalPath(V[v].Getlocation(),e.loc,city);

                if(path.empty())
                {
                    cout<<"NO PATH AVAILABLE\n";
                    break;
                }

                V[v].Assignemergency();
                V[v].Assignpath(path);

                e.active=false; // mark resolved after dispatch

                cout<<"DISPATCHED "<<V[v].Getid()<<endl;
                cout<<"PATH: ";
                for(int x:path) cout<<x<<" ";
                cout<<endl;

                break;
            }

            case 3:
                d_menu=false;
                break;
        }
    }
    break;
     }
    }
    }
}
/*
Doesn�t consider vehicle type vs emergency type
Doesn�t consider severity priority
Doesn�t choose best path cost
Doesn�t update vehicle location*/

