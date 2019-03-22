#include<bits/stdc++.h>

using namespace std;

typedef long long int LL;
typedef pair<long long int,long long int> PII;
typedef vector<long long int> VI;
typedef vector< PII > VPII;

long long int xmin,xmax,ymin,ymax ;
long long int val=0,k=0,p=0;
long long int node_num1=0 ;
long long int alpha ;
long long int x_c,y_c,region ;
long long int region1,region2 ;
long long int bx1,tx1,by1,ty1,bx2,by2,tx2,ty2 ;
long long int reg1=0,reg2=0 ;
long long int bx,by,tx,ty ;
long long int height=0;
VI l ;
long long int p1=0;
VI regions ;
set<pair<long long int ,long long int> > result;

struct kdtree {
    kdtree *left,*right;
    long long int x,y;
    bool splitDimension;
    bool alphaSatisfied;
    long long int name;
    long long int node_num ;
};


/** This function prints the kdtree (preorder traversal) */
long long int Visualize(kdtree *nodeaddr, long long int depth, char c) {
    if(nodeaddr == NULL)
        return depth;
        /**
    cout << " x : " << nodeaddr->x << " y :  " << nodeaddr->y << "   depth : " << depth << " " << " split( 0->X , 1->Y ) : " <<   nodeaddr->splitDimension << "  region : "<< nodeaddr->node_num;
    if(c=='a')
      cout << "   root" << endl;
    if(c=='l')
     cout << "   left" << endl;
    if(c=='r')
      cout << "   right" << endl; 
    cout << endl ;
    **/
    Visualize(nodeaddr->left, depth + 1, 'l');
    Visualize(nodeaddr->right, depth + 1, 'r');
}

void Visualize1(kdtree *nodeaddr, long long int depth, char c) {
    if(nodeaddr == NULL)
        return ;
    cout << " x : " << nodeaddr->x << " y :  " << nodeaddr->y << "   depth : " << depth << " " << " split( 0->X , 1->Y ) : " <<   nodeaddr->splitDimension << "  region : "<< nodeaddr->node_num;
    if(c=='a')
      cout << "   root" << endl;
    if(c=='l')
     cout << "   left" << endl;
    if(c=='r')
      cout << "   right" << endl; 
    cout << endl ;
    Visualize1(nodeaddr->left, depth + 1, 'l');
    Visualize1(nodeaddr->right, depth + 1, 'r');
}

void printGivenLevel(kdtree *nodeaddr, long long int level) 
{ 
    if (nodeaddr == NULL) 
        return; 
    if (level == 1) 
        {
     cout << " x : " << nodeaddr->x << " y :  " << nodeaddr->y  << " " << " split( 0->X , 1->Y ) : " <<   nodeaddr->splitDimension << "  region : "<< nodeaddr->node_num 
       << "     isleaf (0-> leaf)    " << nodeaddr->alphaSatisfied;      
     cout << endl; 
        } 
    else if (level > 1) 
    { 
        printGivenLevel(nodeaddr->left, level-1); 
        printGivenLevel(nodeaddr->right, level-1); 
    } 
} 

void printLevelOrder(kdtree *nodeaddr) 
{ 
    long long int h = Visualize(nodeaddr,0,'a'); 
    long long int i; 
    for (i=0; i<=h; i++) 
    { 
        printGivenLevel(nodeaddr, i); 
        printf("\n"); 
    } 
} 


/** Sorting comparison function */
long long int cmp(const PII &a, const PII &b) {
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
     if((bx1<=bx2 && tx1<=tx2 && by1<=by2 && ty1 <=ty2)  || (bx2<=bx1 && tx2<=tx1 && by2<=by1 && ty2 <=ty1))
                    cout << "Region is completely inside "<< endl;
                  else
                     cout << "Region is not completely inside "<< endl ;
    
}
/** Computes squared distance between two points */
long long int distance(long long int x1,long long int y1,long long int x2,long long int y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

/** This function is for building the kdtree from scratch 
 *  sort all the nodes from s to e in the dimsension "depth"
 *  assign the median of elements from s to e as the current node
 *  for the left half make a recursive call to left subtree with depth increased by one
 *  for the right half make a recursive call to right subtree with depth increased by one
 */
 
kdtree* static_build(kdtree *rootaddr, VPII &vec,long long int depth,long long int s,long long int e) {
    if(e < s)
        return NULL;
    if(((e-s))< alpha) {
        node_num1++;
        val++;
        long long int bx,by,tx,ty ;
        rootaddr = (kdtree*)(malloc(sizeof(kdtree)));
        rootaddr->x = vec[s].first;
        rootaddr->y = vec[s].second;
        rootaddr->alphaSatisfied=0;
        rootaddr->name = val ;
        string s1 = std :: to_string(val)+".txt";
        ofstream fout ;
        fout.open(s1);
        long long int count=e-s ;
        long long int count1=0;
        for( auto m=s;m!=e+1;m++)
        {
          fout << vec[m].first << " " <<vec[m].second <<endl;
          count1++;
        }
        fout.close();
        bx= vec[s].first; 
        tx =vec[e].first;
        by= vec[s].second;
        ty= vec[e].second ;
        rootaddr->splitDimension = 0;
        rootaddr->node_num = node_num1 ;
        l.push_back(bx) ;
        l.push_back(by);
        l.push_back(tx) ;
        l.push_back(ty);
        rootaddr->left = NULL;
        rootaddr->right = NULL;
    }
    else {
        node_num1++;
        val++;
        long long int k;
        long long int bx,by,tx,ty ;
        sort(vec.begin() + s, vec.begin() + e+1 ) ;
        long long int p2 = vec[s].first;
        long long int r = vec[e].first ;
        long long int res = r-p2;
        sort(vec.begin() + s, vec.begin() + e+1 ,cmp) ;
        long long int p1 = vec[s].second;
        long long int r1 = vec[e].second ;
        long long int res1 = r1-p1;
        if(abs(res)>=abs(res1)) {
            sort(vec.begin() + s, vec.begin() + e + 1);
            k=0 ;
            bx= vec[s].first; 
            tx =vec[e].first;
            by= vec[s].second;
            ty= vec[e].second ;
            if(bx>tx)
                 {
                     swap(bx,tx);
                     swap(by,ty);
                 }
        }
        else
            {
                sort(vec.begin() + s, vec.begin() + e + 1, cmp);
                 k=1 ;
                 bx= vec[s].first; 
                 tx =vec[e].first;
                 by= vec[s].second;
                 ty= vec[e].second ;
                 if(bx>tx)
                 {
                     swap(bx,tx);
                     swap(by,ty);
                 }
            }
        rootaddr = (kdtree*)(malloc(sizeof(kdtree)));
        rootaddr->x = vec[(s + e) / 2].first;
        rootaddr->y = vec[(s + e) / 2].second;
        rootaddr->splitDimension = k;
        rootaddr->name = 0 ;
        rootaddr->alphaSatisfied =1 ;
        rootaddr->node_num = node_num1 ;
        l.push_back(bx) ;
        l.push_back(by);
        l.push_back(tx) ;
        l.push_back(ty);
        rootaddr->left = static_build(rootaddr->left, vec, depth + 1, s, (s + e) / 2);
        rootaddr->right = static_build(rootaddr->right, vec, depth + 1, (s + e) / 2 + 1, e);
    }
    return rootaddr;
}

void PointInside(kdtree *nodeaddr ){
    if(nodeaddr->node_num ==region || p1==1 && k!=1)
        {
            p1=1;
            long long int  w_x = nodeaddr->x ;
            long long int  w_y = nodeaddr->y ;
            long long int x,y;
            if(x_c==w_x && y_c == w_y)
               { 
                   k=1 ;
                  return  ;
               }
            else if(!nodeaddr->alphaSatisfied)
            {
                string m = std::to_string(nodeaddr->name)+".txt" ;
                ifstream fin;
                fin.open(m);
                cout << m << endl ;
                while(fin >> x >> y)
                 {
                     cout << x << y << endl;
                     if(x_c==x && y_c == y)
                        {  k=1 ;break; return ;}   
                 }
                 fin.close();
            }
            else 
                k=0;
       if(nodeaddr->left!=NULL && nodeaddr->right!=NULL && k!=1)           
      {
       PointInside(nodeaddr->left);
       PointInside(nodeaddr->right);}
        }
     if(nodeaddr->left!=NULL  && nodeaddr->right!=NULL && p1!=1 &&k!=1){ 
     if(x_c <= nodeaddr->x && y_c <=nodeaddr->y )
     PointInside(nodeaddr->left);
     else
     PointInside(nodeaddr->right);
     }
}

void TestIntersect(kdtree *nodeaddr ){
    if(nodeaddr->node_num ==region1 && p1==1 && k!=1)
        {
            p1=1;
            long long int  w_x = nodeaddr->x ;
            long long int  w_y = nodeaddr->y ;
            long long int x,y;
            if(!nodeaddr->alphaSatisfied)
            {
                string m = std::to_string(nodeaddr->name)+".txt" ;
                ifstream fin;
                fin.open(m);
                //cout << m << endl ;
                while(fin >> x >> y)
                 {
                     cout << x << y << endl;
                     if(x_c==x && y_c == y)
                        {  k=1 ;break; return ;}   
                 }
                 fin.close();
            }
            else 
                k=0;
       if(nodeaddr->left!=NULL && nodeaddr->right!=NULL && k!=1 && p1==1)           
      {
       TestIntersect(nodeaddr->left);
       TestIntersect(nodeaddr->right);}
        }
    region1=region1-1;
    bx1 = l[4*region1] ;by1 = l[4*region1+1] ;tx1 = l[4*region1+2] ;ty1 = l[4*region1+3] ;
    if(nodeaddr->left!=NULL && nodeaddr->right!=NULL && k!=1 && p1==1)           
       {
       TestIntersect(nodeaddr->left);
       TestIntersect(nodeaddr->right);
        }
    region2=region2-1;
    bx2 = l[4*region2] ; by2 = l[4*region2+1] ;tx2 = l[4*region2+2] ;ty2 = l[4*region2+3] ;
    checkTestIntersect();return ;
}

void Inside(kdtree *nodeaddr ){
    if(nodeaddr->node_num ==region1 && p1==1 && k!=1)
        {
            p1=1;
            long long int  w_x = nodeaddr->x ;
            long long int  w_y = nodeaddr->y ;
            long long int x,y;
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
       if(nodeaddr->left!=NULL && nodeaddr->right!=NULL && k!=1 && p1==1)           
      {
       Inside(nodeaddr->left);
       Inside(nodeaddr->right);}
        }
    region1=region1-1;
     bx1 = l[4*region1] ;by1 = l[4*region1+1] ;tx1 = l[4*region1+2] ;ty1 = l[4*region1+3] ;
    if(nodeaddr->left!=NULL && nodeaddr->right!=NULL && k!=1 && p1==1)           
       {
       Inside(nodeaddr->left);
       Inside(nodeaddr->right);
        }
    region2=region2-1;
     bx2 = l[4*region2] ; by2 = l[4*region2+1] ;tx2 = l[4*region2+2] ;ty2 = l[4*region2+3] ;
    checkInside();return ;
}

void rangeSearch(kdtree *nodeaddr)
{
    if(nodeaddr==NULL)
       return ;
     long long int current_x = nodeaddr->x ;
     long long int current_y =nodeaddr->y ;
    switch(nodeaddr->splitDimension)
     {
       case 0 : if(xmin<current_x && xmax <= current_x )
                    rangeSearch(nodeaddr->left) ;
                else if(xmin>current_x && xmax > current_x )
                    rangeSearch(nodeaddr->right) ;
                else
                  regions.push_back(nodeaddr->node_num);
                   
        case 1 : if(ymin<current_y && ymax <= current_y )
                    rangeSearch(nodeaddr->left) ;
                else if(ymin>current_x && ymax > current_y )
                    rangeSearch(nodeaddr->right) ;
                else
                    regions.push_back(nodeaddr->node_num);
     }
}

bool pointInrectangle(long long int a,long long int b)
{
    if(a>=xmin && a<=xmax && b>=ymin && b<=ymax)
     return 1 ;
    else 
     return 0;
}

bool Point_Inside_Region(kdtree *nodeaddr,long long int reg,long long int x_res,long long int y_res ){
    if(nodeaddr->node_num == reg || p1==1 && k!=1)
        {
            p1=1;
            long long int  w_x = nodeaddr->x ;
            long long int  w_y = nodeaddr->y ;
            long long int x,y;
            if(x_res == w_x && y_res == w_y)
               { 
                   k=1 ;
                  //cout << x_res << " "<< y_res << endl;
                  if(pointInrectangle(x_res,y_res))
                  result.insert(make_pair(x_res,y_res));
                  return 1 ;
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
       if(nodeaddr->left!=NULL && nodeaddr->right!=NULL && k!=1)           
      {
       Point_Inside_Region(nodeaddr->left,reg,x_res,y_res);
       Point_Inside_Region(nodeaddr->right,reg,x_res,y_res);}
        }
     if(nodeaddr->left!=NULL  && nodeaddr->right!=NULL && p1!=1 &&k!=1){ 
     if(x_c <= nodeaddr->x && y_c <=nodeaddr->y )
     Point_Inside_Region(nodeaddr->left,reg,x_res,y_res);
     else
     Point_Inside_Region(nodeaddr->right,reg,x_res,y_res);
     }
     return 0;
}

