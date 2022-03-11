#include<bits/stdc++.h>
using namespace std;

//function to detect collision
// bool collisionDetection(int r1, int r2, int s1, int s2, int time, int cd)
// {
//     int radiSum = r1 + r2, radiDif = abs(r1 - r2);
//     if(d > radiSum)
//     {

//     }
// }


int main()
{
    int r1,r2,s1,s2,t,d;
    string noCrash = "no crash";

    cin>>r1>>r2>>s1>>s2>>t>>d;

    int radiSum = r1 + r2, radiDif = abs(r1 - r2);

    if(d > radiSum || d == 0)
    {
        cout<<noCrash;
        return 0;
    }

    //crash may happen
    //  d = radiDif, d = radiSum, radiDif <= d <= radiSum

    //horizontal offset distance from center of circle
    float x = (r1*r1 - r2*r2 + d*d)/(2d); 

    //vertical offset distance from horizontal
    float p = sqrt(r1*r1 - x*x);

    

    return 0;
}