#include <iostream>
#include <vector>
#include <string>
using namespace std;

class CITY
{
    private:

    int rows;
    int cols;
    int totoalnodes;
     vector<vector<pair<int,int>>> adj;

    public:

    CITY(int r,int c)
    {
        rows=r;
        cols=c;
        totoalnodes=r*c;
    }
    void Citygrid()
    {

    }
    void Newroad()
    {

    }
    void Neighbour()
    {

    }
    void Getweight()
    {

    }
    void Updatetraffic()
    {

    }
    int Totalnodes()
    {
      return 0;
    }
};

class NODE
{
    private:

    int x,y;
    bool blocked;
    bool emergency;
    string ememrgencytype;

    public:

    NODE()
    {

    }
   void Setblocked()
    {

    }
    void Setemergency()
    {

    }
    void Reset()
    {

    }
};
class VEHICLES
{
    static int count;
    static int Maxfuel;

    private :

    int id;
    string type;
    int loc;
    int fuel;
    bool available;
    vector<int> currentpath;
    int targetemergency;

    public :

    VEHICLES()
    {
        id=0;
        type="";
        loc=0;
        fuel=0;
    }

    void Setvehicle(int id,string type,int loc)
    {
        this->id=id;
        this->type=type;
        this->loc=loc;
        this->fuel=Maxfuel;
        this->available=true;
        count++;
    }
    static int vehiclecount()
    {
        return count;
    }
    static void Setmaxfuel(int max)
    {
        Maxfuel=max;
    }
    int Getid()
    {
      return id;
    }
    string Gettype()
    {
      return type;
    }
    void Assignemergency()
    {

    }
    void Assignpath()
    {

    }
    void Reducefuel()
    {

    }
    void Refuel()
    {
        fuel=Maxfuel;
    }
    bool Isavailable()
    {
      if(available)
      {
          return true;
      }
      else
      {
          return false;
      }
    }
    int Getlocation()
    {
      return loc;
    }
};
class EMERGENCY
{
    private :

    int id;
    string type;
    int loc;
    int severity;
    int status;
    int deadline;

    public :

    EMERGENCY()
    {

    }
    void Markresolved()
    {

    }
    bool Isactive()
    {
       return false;
    }
    void Getpriority()
    {

    }
    void Getlocation()
    {

    }
};
class PATHFINDER
{
    public :

    vector <int> CalPath(int src,int dest,CITY &city)
    {
        int nodeCount=city.Totalnodes();
        vector<int> dist(nodeCount,INT_MAX);
        vector<bool> visited(nodeCount,false);
        vector<int> parent(nodeCount,-1);
        dist[src]=0;
        for(int i=0;i<nodeCount-1;i++)
        {
            int curr=-1;
            for(int nd=0;nd<nodeCount;nd++)
            {
                if(!visited[nd]&&(curr==-1||dist[nd]<dist[curr]))
                    curr=nd;
            }
            if(curr==-1||dist[curr]==INT_MAX) break;
            visited[curr]=true;
            for(auto &edge : city.adj[curr])
            {
                int node=edge.first;
                int weight=edge.second;
                if(!visited[node]&&dist[curr]!=INT_MAX&&dist[curr]+weight<dist[node])
                {
                    dist[node]=dist[curr]+weight;
                    parent[node]=curr;
                }
            }
        }
        vector<int> path;
        int node=dest;
        while(node!=-1)
        {
            path.insert(path.begin(),node);
            node=parent[node];
        }
        return path;
    }
    void UpdatePath()
    {

    }
    void Getdistance(int dest)
    {

    }
};
class DISPATCHER
{
    public:

    int Findvehicle()
    {
       return 0;
    }
    void Assignvehicle()
    {

    }
    void Computeroute()
    {

    }
};

int VEHICLES::count = 0;
int VEHICLES::Maxfuel = 0;

int main()
{
    int i=0;
    int MaxVeh=5;
    VEHICLES * V=new VEHICLES[MaxVeh];
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
                 cout<< "ENTER 8 TO EXIT"<< endl;
                 cout<< "ENTER YOUR CHOICE: ";
                 cin >> n;
                 switch(n)
                 {
                     case 1:
                     {
                         // code to change grid size
                         break;
                     }
                     case 2:
                     {
                         // code to add location
                         break;
                     }
                     case 3:
                     {
                         // code to add road
                         break;
                     }
                     case 4:
                     {
                         // code to view neighbourhood
                         break;
                     }
                     case 5:
                     {
                         // code to get weight of road
                         break;
                     }
                     case 6:
                     {
                         // code to update traffic
                         break;
                     }
                     case 7:
                     {
                         // code to get total locations
                         break;
                     }
                     case 8:
                     {
                         cout << "EXITING BUILD CITY MODULE!" << endl;
                         c=false;
                         break;
                     }
                     default:
                     {
                         cout << "INVALID CHOICE! PLEASE TRY AGAIN." << endl;
                         break;
                     }
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
                    cout<< "ENTER 1 TO ADD AMBULANCE"<< endl;
                    cout<< "ENTER 2 TO ADD FIRE TRUCK"<< endl;
                    cout<< "ENTER 3 TO ADD POLICE CAR"<< endl;
                    cout<< "ENTER 4 TO EXIT"<< endl;
                    cout<< "ENTER 5 TO VIEW ALL VEHICLES"<< endl;
                    cout<< "ENTER YOUR CHOICE: ";
                    cin >> n;
                    if(i>=MaxVeh&&n<4)
                        {
                            cout << "MAXIMUM VEHICLE LIMIT REACHED! CANNOT ADD MORE VEHICLES." << endl;
                            break;
                        }
                    switch(n)
                    {
                        case 1:
                        {
                            V[i++].Setvehicle(0001,"Ambulance",0);
                            break;
                        }
                        case 2:
                        {
                            V[i++].Setvehicle(1001,"Fire Truck",0);
                            break;
                        }
                        case 3:
                        {
                            V[i++].Setvehicle(2001,"Police Car",0);
                            break;
                        }
                        case 4:
                        {
                            cout << "EXITING ADD VEHICLE MODULE!" << endl;
                            b=false;
                            break;
                        }
                        case 5:
                        {
                            cout << "CURRENT VEHICLES IN THE SYSTEM:" << endl;
                            cout<<VEHICLES::vehiclecount()<<endl;
                             for(int j=0;j<i;j++)
                             {
                                 cout << "ID: " << V[j].Getid() << " TYPE: " << V[j].Gettype() << endl;
                             }
                            break;
                        }
                        default:
                        {
                            cout << "INVALID CHOICE! PLEASE TRY AGAIN." << endl;
                            break;
                        }
                    }
                }
               break;
           }
           case 3:
           {
               int n;
               bool b=true;
                while(b)
                {
                    cout<< "ENTER 1 TO CREATE MEDICAL EMERGENCY"<< endl;
                    cout<< "ENTER 2 TO CREATE FIRE EMERGENCY"<< endl;
                    cout<< "ENTER 3 TO CREATE CRIME EMERGENCY"<< endl;
                    cout<< "ENTER 4 TO EXIT"<< endl;
                    cout<< "ENTER YOUR CHOICE: ";
                    cin >> n;
                    switch(n)
                    {
                        case 1:
                        {

                            break;
                        }
                        case 2:
                        {
                            // code to create fire emergency
                            break;
                        }
                        case 3:
                        {
                            // code to create crime emergency
                            break;
                        }
                        case 4:
                        {
                            cout << "EXITING CREATE EMERGENCY MODULE!" << endl;
                            b=false;
                            break;
                        }
                        default:
                        {
                            cout << "INVALID CHOICE! PLEASE TRY AGAIN." << endl;
                            break;
                        }
                    }
                }
               break;
           }
           case 4:
           {
               // code to dispatch vehicle
               break;
           }
           case 5:
           {
               cout << "THANK YOU FOR USING THE SYSTEM!" << endl;
               return 0;
           }
           default:
           {
               cout << "INVALID CHOICE! PLEASE TRY AGAIN." << endl;
               break;
           }
       }
    }
    return 0;
}
