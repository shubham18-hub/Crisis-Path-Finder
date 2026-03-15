#include <iostream>
#include <vector>
#include <string>
using namespace std;

class CITY
{
    private:

    int rows;
    int cols;
    int totalnodes=8;
    vector<pair<int,int>> G[8];
    vector<pair<int,int>> coordinates[8];
    public:

    CITY(int r,int c)
    {
        rows=r;
        cols=c;
    }
    void Setlocations()
    {
           for(int i=0;i<totalnodes;i++)
           {
           cout<< "ENTER COORDINATES OF LOCATION NO  "<<i+1<<endl;
           int x1,y1;
           cin>>x1>>y1;
           coordinates[i].push_back({x1,y1});
           }
    }
    void Citygrid()
    {
        int s,d,w;
        for(int i=0;i<totalnodes;i++)
        {
           cout<< "ENTER SOURCE, DESTINATION AND WEIGHT OF ROAD: "<<endl;
           cin>>s>>d>>w;
           G[s].push_back({d,w});
           G[d].push_back({s,w});
        }
    }
    void Newroad()
    {
      cout<< "ENTER SOURCE, DESTINATION AND WEIGHT OF NEW ROAD: "<<endl;
      int s,d,w;
      cin>>s>>d>>w;
      G[s].push_back({d,w});
      G[d].push_back({s,w});

    }
    void Neighbour()
    {
        int n;
        cout<<"ENTER NEIGHBOURHOOD "<<endl;
        cin>>n;
        cout<<"NEIGHBOURING AREAS ARE : "<<endl;
        for(int i=0;i<G[n].size();i++)
        cout<<G[n][i].first<<endl;
    }
    void Getweight(int src,int des)
    {
        for(int i=0;i<G[src].size();i++)
        {
            if(G[src][i].first==des)
            {
                cout<<"WEIGHT OF ROAD IS : "<<G[src][i].second<<endl;
                return;
            }
        }
        cout<<"NO DIRECT ROAD EXISTS BETWEEN THE LOCATIONS!"<<endl;

    }
    void Updatetraffic(int src,int des,int w)
    {
        for(int i=0;i<G[src].size();i++)
        {
            if(G[src][i].first==des)
            {
                G[src][i].second=w;
                break;
            }
        }
        for(int i=0;i<G[des].size();i++)
        {
            if(G[des][i].first==src)
            {
                G[des][i].second=w;
                break;
            }
        }
    }
    int Totalnodes()
    {
      return 0;
    }
    int Calculatedistance(int src, int dest)
    {
        int x1=coordinates[src][0].first;
        int y1=coordinates[src][0].second;
        int x2=coordinates[dest][0].first;
        int y2=coordinates[dest][0].second;
        return (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
    }
};

class NODE
{
    private:

    int x,y;
    bool blocked;
    bool emergency;
    string emergencytype;

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

    string id;
    int speed;
    string type;
    int loc;
    int fuel;
    bool available;
    vector<int> currentpath;
    int targetemergency;

    public :

    VEHICLES()
    {
        id="";
        type="";
        loc=0;
        fuel=0;
        speed=30;
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
    static void Setmaxfuel(int max)
    {
        Maxfuel=max;
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

    EMERGENCY( )
    {
        id=0;
        type="";
        loc=0;
        severity=0;
        status=0;
        deadline=0;
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
        return vector<int>();
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
    CITY city(10,20);
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
                 cout<< "ENTER 8 TO CALCULATE DISTANCE BETWEEN TWO LOCATIONS"<< endl;
                 cout<< "ENTER 9 TO EXIT"<< endl;
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
                         city.Citygrid();// code to add location
                         break;
                     }
                     case 3:
                     {
                         city.Newroad();
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
                            
                            break;
                     }
                     case 9:
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
                    cout<<endl;
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
                            string n;
                            cout<<endl;
                            cout<< "ENTER VEHICLE NO. OF AMBULANCE"<<endl;
                            cin>>n;
                            V[i++].Setvehicle("AMB" +n,"Ambulance",0,45);
                            cout<<"---------ADDED SUCCESSFULLY ------"<<endl;
                            break;
                        }
                        case 2:
                        {
                            string n;
                            cout<<endl;
                            cout<< "ENTER VEHICLE NO. OF FIRE TRUCK"<<endl;
                            cin>>n;
                            V[i++].Setvehicle("FIRE" +n,"Fire Truck",0,35);
                              cout<<"---------ADDED SUCCESSFULLY ------"<<endl;
                            break;
                        }
                        case 3:
                        {
                            string n;
                            cout<<endl;
                            cout<< "ENTER VEHICLE NO. OF POLICE CAR"<<endl;
                            cin>>n;
                            V[i++].Setvehicle("POL" + n,"Police Car",0,40);
                            cout<<"---------ADDED SUCCESSFULLY ------"<<endl;
                            break;
                        }
                        case 4:
                        {
                            cout<<endl;
                            cout << "EXITING ADD VEHICLE MODULE!" << endl;
                            b=false;
                            break;
                        }
                        case 5:
                        {
                            cout<<endl;
                            cout << "CURRENT VEHICLES IN THE SYSTEM:" << endl;
                            cout<<VEHICLES::vehiclecount()<<endl;
                             for(int j=0;j<i;j++)
                             {
                                 cout<<endl;
                                 cout << "ID: " << V[j].Getid() << " TYPE: " << V[j].Gettype() << " SPEED:"  << V[j].Getspeed()<<endl;
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
                    cout<<endl;
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
