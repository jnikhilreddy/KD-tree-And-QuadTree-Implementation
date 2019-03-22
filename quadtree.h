#include<bits/stdc++.h>

using namespace std;

typedef float LL;
typedef pair<float,float> PII;
typedef vector<float> VI;
typedef vector< PII > VPII;

float xmin,xmax,ymin,ymax ;
long long int val=0,k=0,p=0;
long long int node_num1=0 ;
long long int alpha ;
float x_c,y_c,region ;
long long int region1,region2 ;
float bx1,tx1,by1,ty1,bx2,by2,tx2,ty2 ;
long long int reg1=0,reg2=0 ;
float thresold_x,thresold_y;
VI l ;
float p1=0;
VI regions ;
set<pair<float ,float> > result;

struct quadtree {
    quadtree *nw,*ne ,*se,*sw;
    float x,y;
    bool splitDimension;
    bool alphaSatisfied;
    long long int name;
    long long int node_num ;
};
long long int Visualize1(quadtree *nodeaddr, long long int depth, char c) {
    if(nodeaddr == NULL)
        return depth;
    Visualize1(nodeaddr->ne, depth + 1, '1');
    Visualize1(nodeaddr->nw, depth + 1, '2');
    Visualize1(nodeaddr->sw, depth + 1, '3');
    Visualize1(nodeaddr->se, depth + 1, '4');
}

void printGivenLevel(quadtree *nodeaddr, long long int level,long long int direction) 
{ 
    if (nodeaddr == NULL) 
        return; 
    if (level == 1) 
        {
     cout << " x : " << nodeaddr->x << " y :  " << nodeaddr->y  << " "  << "  region : "<< nodeaddr->node_num ;
     if(direction==0)
       cout <<"   ROOT "<< endl;   
     if(direction==1)
       cout <<"   NORTH EAST "<< endl;
       if(direction==2)
       cout <<"   NORTH WEST " <<endl;
       if(direction==3)
       cout <<"   SOUTH WEST "<< endl; 
       if(direction==4)
       cout <<"   SOUTH EAST "<< endl ; 
     cout <<  endl;
        } 
    else if (level > 1) 
    { 
        printGivenLevel(nodeaddr->ne, level-1,1); 
        printGivenLevel(nodeaddr->nw, level-1,2); 
        printGivenLevel(nodeaddr->sw, level-1,3);
        printGivenLevel(nodeaddr->se, level-1,4); 
    } 
} 

void printLevelOrder(quadtree *nodeaddr) 
{ 
    long long int h = Visualize1(nodeaddr,0,'a'); 
    long long int i; 
    for (i=1; i<=h; i++) 
    { 
        cout << "level : " << i << endl;
        cout << endl;
        printGivenLevel(nodeaddr, i,0); 
        printf("\n"); 
}
}  
/** This function prints the quadtree (preorder traversal) */
void Visualize(quadtree *nodeaddr, float depth, char c) {
    if(nodeaddr == NULL)
        return;
    cout << "x : " << nodeaddr->x << " y :  " << nodeaddr->y << "   " <<"depth : " << depth  << "    region :  "<<  nodeaddr->node_num << "     " << " is Leaf(0 -> leaf) : " << nodeaddr->alphaSatisfied << "   " ;
    if(c=='a')
      cout << "  ROOT " << endl;
    if(c=='1')
      cout <<  "   NORTH EAST" << endl;
    if(c=='2')
      cout << "   NORTH WEST" << endl;
    if(c=='3')
      cout << "    SOUTH WEST" << endl;
    if(c=='4')
      cout <<  "   SOUTH EAST" << endl;
    cout << endl;
    Visualize(nodeaddr->ne, depth + 1, '1');
    Visualize(nodeaddr->nw, depth + 1, '2');
    Visualize(nodeaddr->sw, depth + 1, '3');
    Visualize(nodeaddr->se, depth + 1, '4');
}


/** Sorting comparison function */
float cmp(const PII &a, const PII &b) {
    return ((a.second < b.second) || ((a.second == b.second) && (a.first < b.first)));
}
void checkTestIntersect()
{
    if((bx1<=bx2 || tx1<=tx2 || by1<=by2 || ty1 <=ty2)  || (bx2<=bx1 || tx2<=tx1 || by2<=by1 || ty2 <=ty1))
                    cout << "Regions are overlapping "<< endl;
                  else
                     cout << "Region are not overlapping "<< endl ;
    return ;
}

void checkInside()
{
     if((bx1<=bx2 && tx1<=tx2 && by1<=by2 && ty1 <= ty2)  || (bx2<=bx1 && tx2<=tx1 && by2<=by1 && ty2 <=ty1))
                    cout << "Region is completely inside "<< endl;
    else
        cout << "Region is not completely inside "<< endl ;
    
}
/** Computes squared distance between two points */
float distance(float x1,float y1,float x2,float y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

/** This function is for building the quadtree from scratch 
 *  sort all the nodes from s to e in the dimsension "depth"
 *  assign the median of elements from s to e as the current node
 *  for the nw half make a recursive call to nw subtree with depth increased by one
 *  for the ne half make a recursive call to ne subtree with depth increased by one
 */
 
quadtree* static_build(quadtree *rootaddr, VPII &vec,long long int depth,long long int s,long long int e) {
    if(e <  s)
        return NULL;
    node_num1++;
    val++;
    if(((e-s)) < alpha) {
        float bx,by,tx,ty ;
        rootaddr = (quadtree*)(malloc(sizeof(quadtree)));
        rootaddr->x = (vec[s].first + vec[e].first)/2.0 ;  
        rootaddr->y = (vec[s].second + vec[e].second) / 2.0 ;
        rootaddr->alphaSatisfied=0;
        rootaddr->name = val ;
        string s1 = std :: to_string(val)+".txt";
        //cout << s1 << endl;
        ofstream fout ;
        fout.open(s1);
        long long int count1=0;
        for( auto m=s;m!=e+1;m++)
        {
          fout << vec[m].first << " " <<vec[m].second <<endl;
          count1++;
        }
        //cout << count1 << endl;
        fout.close();
        rootaddr->splitDimension = 0;
        rootaddr->node_num = node_num1 ;
        sort(vec.begin() + s, vec.begin() + e  + 1 ) ;
        l.push_back(vec[0].first);  l.push_back(vec[vec.size()-1].first); 
        sort(vec.begin() + s, vec.begin() + e + 1 ,cmp) ;
        l.push_back(vec[0].second);
        l.push_back(vec[vec.size()-1].second);
        rootaddr->nw = NULL;
        rootaddr->ne = NULL;
        rootaddr->sw = NULL;
        rootaddr->se = NULL;
    }
    else {
        //cout << s <<" "<< e << endl;
        VPII vec_nw,vec_ne,vec_sw,vec_se ;
        long long int k;
        sort(vec.begin() + s, vec.begin() + e  + 1 ) ;
        thresold_x =  (vec[s].first + vec[e].first)/ 2.0 ;  
        //cout << countx << endl;
        l.push_back(vec[0].first);  l.push_back(vec[vec.size()-1].first); 
        sort(vec.begin() + s, vec.begin() + e+1 ,cmp) ;
        thresold_y  = (vec[s].second + vec[e].second) / 2.0 ;
        l.push_back(vec[0].second);
        l.push_back(vec[vec.size()-1].second);
         for(auto i = vec.begin() ; i!=vec.end();i++)
        {
            if(i->second < thresold_y && i->first > thresold_x)
              vec_se.push_back(make_pair(i->first,i->second)) ;
             if(i->second >= thresold_y && i->first > thresold_x)
              vec_ne.push_back(make_pair(i->first,i->second)) ;
              if(i->second >= thresold_y && i->first <= thresold_x)
              vec_nw.push_back(make_pair(i->first,i->second)) ;
             if(i->second < thresold_y && i->first <= thresold_x)
              vec_sw.push_back(make_pair(i->first,i->second)) ;
                
        }
        rootaddr = (quadtree*)(malloc(sizeof(quadtree)));
        rootaddr->x = thresold_x ; 
        rootaddr->y = thresold_y ;
        rootaddr->splitDimension = k;
        rootaddr->name = 0 ;
        rootaddr->alphaSatisfied =1 ;
        rootaddr->node_num = node_num1 ;
        rootaddr->ne = static_build(rootaddr->ne, vec_ne, depth + 1, 0 , (long long int)vec_ne.size() - 1 );
        rootaddr->nw = static_build(rootaddr->nw, vec_nw, depth + 1, 0 , (long long int)vec_nw.size() - 1 );
        rootaddr->sw = static_build(rootaddr->sw, vec_sw, depth + 1, 0 , (long long int)vec_sw.size() - 1 );
        rootaddr->se = static_build(rootaddr->se, vec_se, depth + 1, 0 , (long long int)vec_se.size() - 1 );
    }
    regions.push_back(1) ;
    return rootaddr;
}

void PointInside(quadtree *nodeaddr ){
    if(nodeaddr->node_num ==region || p1==1 && k!=1)
        {
            p1=1;
            region1=region-1;
             bx1 = l[4*region1] ;bx2 = l[4*region1+1] ;by1 = l[4*region1+2] ;by2 = l[4*region1+3] ;
            float  w_x = nodeaddr->x ;
            float  w_y = nodeaddr->y ;
            float x,y;
            if(bx2<bx1)
              swap(bx1,bx2);
            if(by2<by1)
               swap(by1,by2);
            if(x_c >= bx1 && x_c <= bx2 && y_c >= by1 && y_c <= by2)
               {
                   k=1;
                   return ;
               }
             if(!nodeaddr->alphaSatisfied)
            {
                string m = std::to_string(nodeaddr->name)+".txt" ;
                ifstream fin;
                fin.open(m);
                cout << m << endl ;
                while(fin >> x >> y)
                 {
                     cout << x << y << endl;
                     if(x_c==x && y_c == y)
                        {  k=0 ;break; return ;}   
                 }
                 fin.close();
            }
            else 
                k=0;
        }
     if(nodeaddr->nw!=NULL  && nodeaddr->ne!=NULL &&  nodeaddr->sw!=NULL && nodeaddr->se!=NULL  && p1!=1 &&k!=1){ 
     PointInside(nodeaddr->nw);
     PointInside(nodeaddr->ne);
     PointInside(nodeaddr->sw);
     PointInside(nodeaddr->se);
     }
}

void TestIntersect(quadtree *nodeaddr ){
    if(nodeaddr->node_num ==region1 && p1==1 && k!=1)
        {
            p1=1;
            float  w_x = nodeaddr->x ;
            float  w_y = nodeaddr->y ;
            float x,y;
            if(!nodeaddr->alphaSatisfied)
            {
                string m = std::to_string(nodeaddr->name)+".txt" ;
                ifstream fin;
                fin.open(m);
                //cout << m << endl ;
                while(fin >> x >> y)
                 {
                    // cout << x << y << endl;
                     if(x_c==x && y_c == y)
                        {  k=1 ;break; return ;}   
                 }
                 fin.close();
            }
            else 
                k=0;
       if(nodeaddr->nw!=NULL && nodeaddr->ne!=NULL && k!=1 && p1==1)           
      {
       TestIntersect(nodeaddr->nw);
       TestIntersect(nodeaddr->ne);
     TestIntersect(nodeaddr->sw);
       TestIntersect(nodeaddr->se);
      }
        }
     region1=region1-1;
      bx1 = l[4*region1] ;tx1 = l[4*region1+1] ;by1 = l[4*region1+2] ;ty1 = l[4*region1+3] ;
     region2=region2-1;
     bx2 = l[4*region2] ;tx2  = l[4*region2+1] ;by2 = l[4*region2+2] ;ty2 = l[4*region2+3] ;
     if(tx1<bx1) swap(bx1,tx1);
       if(ty1<by1) swap(ty1,by1);
       if(tx2<bx2) swap(bx2,tx2);
       if(ty2<by2) swap(ty2,by2);
    checkTestIntersect();return ;
    if(nodeaddr->nw!=NULL && nodeaddr->ne!=NULL && k!=1 && p1==1)           
       {
     TestIntersect(nodeaddr->nw);
     TestIntersect(nodeaddr->ne);
     TestIntersect(nodeaddr->sw);
     TestIntersect(nodeaddr->se);
        }
}

void Inside(quadtree *nodeaddr ){
    if(nodeaddr->node_num ==region1 && p1==1 && k!=1)
        {
            p1=1;
            float  w_x = nodeaddr->x ;
            float  w_y = nodeaddr->y ;
            float x,y;
            if(!nodeaddr->alphaSatisfied)
            {
                string m = std::to_string(nodeaddr->name)+".txt" ;
                ifstream fin;
                fin.open(m);
                //cout << m << endl ;
                while(fin >> x >> y)
                 {
                     //cout << x << y << endl;
                     if(x_c==x && y_c == y)
                        {  k=1 ;break; return ;}   
                 }
                 fin.close();
            }
            else 
                k=0;
       if(nodeaddr->nw!=NULL && nodeaddr->ne!=NULL && k!=1 && p1==1)           
      {
       Inside(nodeaddr->nw);
       Inside(nodeaddr->ne);
       Inside(nodeaddr->se);
       Inside(nodeaddr->sw);
      }
        }
    region1=region1-1;
     bx1 = l[4*region1] ;tx1 = l[4*region1+1] ;by1 = l[4*region1+2] ;ty1 = l[4*region1+3] ;
    if(nodeaddr->nw!=NULL && nodeaddr->ne!=NULL && k!=1 && p1==1)           
       {
       Inside(nodeaddr->nw);
       Inside(nodeaddr->ne);
       Inside(nodeaddr->se);
       Inside(nodeaddr->sw);
        }
    region2=region2-1;
     bx2 = l[4*region2] ; tx2 = l[4*region2+1] ;by2 = l[4*region2+2] ;ty2 = l[4*region2+3] ;
      if(tx1<bx1) swap(bx1,tx1);
       if(ty1<by1) swap(ty1,by1);
       if(tx2<bx2) swap(bx2,tx2);
       if(ty2<by2) swap(ty2,by2);
    checkInside();return ;
}

void rangeSearch(quadtree *nodeaddr)
{
    if(nodeaddr==NULL)
       return ;
     float current_x = nodeaddr->x ;
     float current_y =nodeaddr->y ;
     long long int t_reg = nodeaddr -> node_num ;
     if(xmin < current_x && xmax < current_x && ymin < current_y && ymax < current_y )
             rangeSearch(nodeaddr->sw) ;
      else if(xmin > current_x && xmax > current_x && ymin <current_y && ymax < current_y  )
             rangeSearch(nodeaddr->se) ;
      else if(xmin<current_x && xmax <= current_x && ymin >= current_y && ymax > current_y  )
             rangeSearch(nodeaddr->nw) ;
      else if(xmin > current_x && xmax > current_x && ymin > current_y && ymax > current_y  )
             rangeSearch(nodeaddr->ne) ;
       else
         regions.push_back(nodeaddr->node_num);
}

bool pointInrectangle(float a,float b)
{
    if(a>=xmin && a<=xmax && b>=ymin && b<=ymax)
     return 1 ;
    else 
     return 0;
}

bool Point_Inside_Region(quadtree *nodeaddr,long long int reg,long long int x_res,long long int y_res ){
    if(nodeaddr->node_num == reg || p1==1 && k!=1)
        {
            p1=1;
            float  w_x = nodeaddr->x ;
            float  w_y = nodeaddr->y ;
            float x,y;
            region1=reg-1;
            bx1 = l[4*region1] ;bx2 = l[4*region1+1] ;by1 = l[4*region1+2] ;by2 = l[4*region1+3] ;
             if(bx2<bx1)
              swap(bx1,bx2);
            if(by2<by1)
               swap(by1,by2);
            if(x_res >= bx1 && x_res <= bx2 && y_res >= by1 && y_res <= by2)
               { 
                   k=1 ;
                  //cout << x_res << " "<< y_res << endl;
                  if(pointInrectangle(x_res,y_res))
                  result.insert(make_pair(x_res,y_res));
               }
            else if(!nodeaddr->alphaSatisfied)
            {
                string m = std::to_string(nodeaddr->name)+".txt" ;
                ifstream fin;
                fin.open(m);
                //cout << m << endl ;
                while(fin >> x >> y)
                 {
                    // cout << x << y << endl;
                     if(x_res== x && y_res == y)
                        {
                         if(pointInrectangle(x_res,y_res))
                          result.insert(make_pair(x_res,y_res));
                        k=1 ; return 1 ;}   
                 }
                 fin.close();
            }
            else 
                k=0;
        }
      if(nodeaddr->nw!=NULL  && nodeaddr->ne!=NULL &&  nodeaddr->sw!=NULL && nodeaddr->se!=NULL  && p1!=1 &&k!=1){ 
      Point_Inside_Region(nodeaddr->nw,reg,x_res,y_res);
      Point_Inside_Region(nodeaddr->ne,reg,x_res,y_res);
     Point_Inside_Region(nodeaddr->sw,reg,x_res,y_res);
      Point_Inside_Region(nodeaddr->se,reg,x_res,y_res);
     }
     return 0;
}

