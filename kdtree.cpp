#include<bits/stdc++.h>
#include "kdtree.h"

using namespace std;
typedef pair<long long int,long long int> PII;
typedef vector<long long int> VI;
typedef vector< PII > VPII;


int main()
{
    VPII vec,rem;
    kdtree *rootaddr = NULL;
    long long int point_id,point_x, point_y;
    ifstream fin;
    fin.open("data.txt");
    long long int count =0 ;
    cout << "Enter alpha value ?" << endl ;
    cin >> alpha ;
    int first ;
    while(fin >> point_id >> point_x >> point_y) {
        vec.push_back(make_pair(point_x, point_y));
    }
    fin.close();
    rootaddr = NULL;
    rootaddr = static_build(rootaddr, vec, 0, 0, (long long int)vec.size() - 1);
     //Visualize(rootaddr, 0, 'a');
    //cout << l[0] << l[1] <<l[2] << l[3] <<endl;
    cout << "Enter the case  PointInside : 1   Visualise : 2  Inside : 3   Test Intersect : 4    Range query: 5 " << endl;
    long long int c ;
    cin >> c ;
    switch(c)
    {
        case 1 : cout << "Enter the point "<< endl;
                  cin >> x_c >> y_c ;
                  cout << "enter the region number "<<endl;
                  cin>>region ;
                  PointInside(rootaddr);
                  if(k==1)
                    cout << "point " << x_c  << " "<<y_c << " is inside the region "<< endl;
                   else
                    cout << "point " << x_c  << " "<<y_c << " is not inside the region "<< endl;
                  break;
                  
        case 2   : cout << " type of traversal you want level order : 0 pre order : 1 " << endl;
                   int m3;
                   cin >> m3;
                   cout << "tree traversal\n";
                   cout << endl;			
                   if (m3==0) 
                    printLevelOrder(rootaddr);
                    else
                      Visualize1(rootaddr,0,'a');
                  break ;
       case 3   :  cout << "Enter the region values "<< endl;
                  cin >> region1 >> region2 ;
                  Inside(rootaddr) ;
                  cout << bx1 <<" "<<  by1 <<" " << tx1 << " "<< ty1 <<" "<< bx2 << " "<< by2 <<" " << tx2 << " "<< ty2 << endl; 
                  break ;
          case 4  :  cout << "Enter the region values "<< endl;
                  cin >> region1 >> region2 ;
                  TestIntersect(rootaddr) ;
                  cout << bx1 <<" "<<  by1 <<" " << tx1 << " "<< ty1 <<" "<< bx2 << " "<< by2 <<" " << tx2 << " "<< ty2 << endl; 
                  break ;
        case 5  : cout << "Enter the xmin,ymin,xmax,ymax ??" << endl ;
                  cin >> xmin >> ymin >> xmax >> ymax ;
                  rangeSearch(rootaddr) ;
                  for(auto  i =regions.begin();i!=regions.end();i++)
                     { 
                     //cout << *i << endl;
                     long long int verse=*i;
                    ifstream fin;
                    fin.open("data.txt");
                   while(fin >> point_id >> point_x >> point_y) {
                       p1=0;k=0;
                    Point_Inside_Region(rootaddr,verse,point_x,point_y) ;
                    }
                    fin.close();
                   }
                 cout << "Points inside the region mentioned are " << endl; 
                 for(auto m=result.begin();m!=result.end();m++)
                    cout << m->first << " " << m->second << endl;
                    ofstream fout ;
                    fout.open("result_program_kdtree.txt");
                 for(auto m=result.begin();m!=result.end();m++)
                    fout << m->first << " " << m->second << endl;
                  break ;
    }
    return 0;
}
