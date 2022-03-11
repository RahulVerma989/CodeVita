#include<bits/stdc++.h>
using namespace std;

struct nameRoute
{
    string name;
    int *route;
};

bool uniqueInsertArray(vector<pair <nameRoute,nameRoute> >& arr, string element)
{
    for(int i = 0; i < arr.size(); i++)
    {
        if(arr[i].first.name == element)
        {
            //if element is found            
            return false;
        }
    }

    //if element is not inside array
    nameRoute pasName,point;
    pasName.name = element;
    point.route = NULL;
    arr.push_back({pasName,point});
    return true;
}

int findPosi(vector<pair <nameRoute,nameRoute>>& arr, string element)
{
    for(int i = 0; i < arr.size(); i++)
    {
        if(arr[i].first.name == element)
        {
            return i;
        }
    }
    return -1;
}

bool alphaSorting(string a, string b)
{
    return a<b;
}

int main()
{
    int n = 0,t = 0;

    //stops and ticket
    cin>>n;

    vector<pair <nameRoute,nameRoute> > passengers; // pasengers list
    vector<pair <int, int> > psd; // person source, destination and pointer to passenger
    string standStatus = "";

    for(int j = 1; j <= n; j++)
    {
        cin>>standStatus;
        string name = "";
        bool boarding = true;
        bool nobody = false;
        for(int i = 0; i < standStatus.length(); i++)
        {
            if(!nobody)
            {
                if(standStatus[i] != ' ' && name.length() == 0)
                {
                    continue;
                }
                else
                if(standStatus[i] != '-' && standStatus[i] != '|')
                {
                    //if passenger name 
                    name+=standStatus[i];
                }
                else
                if(name.length())
                {
                    //push the pasenger name
                    if(uniqueInsertArray(passengers,name))
                    {
                        //if passenger is boarding first time

                        //push the pasenger source stop   
                        if(boarding)
                        {
                            //passenger is boarding
                            // psd.push_back(make_pair(j,-1));
                            int pesengerSource = findPosi(passengers,name);
                            if(pesengerSource > -1)
                            {  
                                psd[pesengerSource].first = j;
                                psd[pesengerSource].second = -1;
                                // int *p = &(*(psd.begin() + pesengerSource);
                                passengers[pesengerSource].second.route = &psd[pesengerSource]; // pointer to passenger route
                            }
                        }       
                    }
                    else
                    if(!boarding)
                    {
                        //passenger is present in the bus and is deboarding
                        int pesengerSource = findPosi(passengers,name);
                        if(pesengerSource > -1)
                        {
                            psd[pesengerSource].second = j;
                        }
                    }

                    name = "";

                }
            }
            else
            if(standStatus[i] == '|')
            {
                boarding = false;
                nobody = false;
            }
            else
            if(standStatus[j] == '-')
            {
                nobody = true;
            }
        }

        
        n--;
    }

    cin>>t;

    vector<pair <int, int> > tsd; // ticket source and destination
    vector<string> status; //UT or OT

    for(int i = 0; i < t; i++)
    {
        int source = 0, destination = 0;
        cin>>source>>destination;
        tsd.push_back(make_pair(source,destination));
    }

    int length = passengers.size();

    for(int i = 0; i < length; i++)
    {
        if( (psd[i].first == tsd[i].first) && (psd[i].second == tsd[i].second))
        {
            // passenger is good therefore remove this passenger from this list
            i = passengers.erase(passengers.begin() + i) - passengers.begin();
            psd.erase(psd.begin() + i);
            tsd.erase(tsd.begin() + i);
        }
        else
        if( (psd[i].first == tsd[i].first) && (psd[i].second < tsd[i].second) )
        {
            //source is same but under traveled
            status.push_back("UT");
        }
        else
        if( (psd[i].first == tsd[i].first) && (psd[i].second > tsd[i].second) )
        {
            //source is same but over traveled
            status.push_back("OT");
        }
    }

    sort(passengers.begin(),passengers.end(),alphaSorting);

    length = passengers.size();
    
    for(int i = 0; i < length; i++)
    {
        cout<<passengers[i].first.name<<" ";
        cout<<psd[i].first<<" "<<psd[i].second<<" ";
        cout<<status[i];
    }
    return 0;
}