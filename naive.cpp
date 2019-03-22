#include<bits/stdc++.h>

using namespace std ;
typedef pair<long long int,long long int> PII;
typedef vector<long long int> VI;
typedef vector< PII > VPII;
long long int xmin,xmax,ymin,ymax ;
long long int x,y ;
VPII res;
int main()
{
    VPII vec;
    long long int point_x, point_y,point_id;
    ifstream fin;
    fin.open("data.txt");
    ofstream fout;
    fout.open("result_naive.txt");
    cout << "Enter the xmin,ymin,xmax,ymax ??" << endl ;
    cin >> xmin >> ymin >> xmax >> ymax ;
    long long int count =0 ;
    while(fin >> point_id >> point_x >> point_y) {
        vec.push_back(make_pair(point_x, point_y));
    }
    for(auto i = vec.begin();i!=vec.end();i++)
    {
       x = i->first ;
       y = i->second ;
       if(x >= xmin && y >= ymin )
       {
           if( x <= xmax && y <= ymax)
               res.push_back(make_pair(x,y));         
       }
    }
    sort(res.begin(),res.end());
    for(auto i = res.begin();i!=res.end();i++)
    {
        x = i->first ;
        y = i->second ;
        fout << x << " " << y << endl;
    }
    return 0;
}
