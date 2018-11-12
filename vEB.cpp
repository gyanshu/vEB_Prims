#include <sys/resource.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>
#include<utility>
#include<set>
#include <random>
#include <chrono>
using namespace std;
typedef long long lld;
typedef unsigned long long llu;
int c = 0;
class vEB
{
    llu u;
    
    llu *m, *M;
    vEB *summary;   // used if u != 2
    vEB **cluster;  // used if u != 2
    
public:
    vEB(llu);
    
    void insert(llu);
    void Delete(llu);
    llu min();
    llu max();
    
    llu extractMin();
};

vEB::vEB(llu u)
{
    this -> u = u;
    this -> m = NULL;
    this -> M = NULL;
    
    if (u == 2)
    {
        this -> summary = NULL;
        this -> cluster = NULL;
    }
    
    else
    {
        llu subSize = (llu)sqrt(u);

        int p = (int)(log(u)/log(2));
        int lo = (int)pow(2,p/2);
        int hi = (int)pow(2,ceil(p/2.0));
        this->summary = new vEB(hi);
        this -> cluster = new vEB*[hi];   
        for(int i = 0;i < hi; i++)
        {
            this->cluster[i] = new vEB(lo);
            c++;
        }
        
    }
}

llu vEB::min()
{
    if (m!=NULL)
        return (*m);
    else
        return -1;
}

llu vEB::max()
{
    if(M!=NULL)
        return (*M);
    else 
        return -1;
}

llu vEB::extractMin()
{
    llu ret = this -> min();
    this -> Delete(ret);
    return ret;
}

void vEB::insert(llu x)
{
    if (u == 2)
    {
        if (x == 0)
        {
            if (m == NULL)
            {
                m = new llu;
                M = new llu;
                (*m) = (*M) = x;
            }
            else (*m) = x;
        }
        else if (x == 1)
        {
            if (M == NULL)
            {
                m = new llu;
                M = new llu;
                (*m) = (*M) = x;
            }
            else (*M) = x;
        }
        return;
    }

    if(m==NULL)
    {
        m = new llu;
        M = new llu;
        *m = *M = x;
        return;
    }
    if(x < *m)
    {
        llu curr = x;
        x = *m;
        *m = curr;
    }

    if(x > *M)
        *M = x;

    llu subSize = (llu)sqrt(u);

    int p = (int)(log(u)/log(2));
    int lower = (int)pow(2,p/2);
    int upper = (int)pow(2,ceil(p/2.0));

    llu hi = x / lower, lo = x % lower;

    if(u > 2)
    {
        if(cluster[hi]->m == NULL)
        {
            summary->insert(hi);
        }
        cluster[hi]->insert(lo);
    }
}

void vEB::Delete(llu x)
{
    if(*m == *M && x==*m)
    {
        m = NULL;
        M = NULL;
        return;
    }
    if(u == 2)
    {
        if (x == 0)
        {
            if ((*M) == 0)
            {
                m = M = NULL;
            }
            else (*m) = 1;
        }
        else if (x == 1)
        {
            if ((*m) == 1)
            {
                m = M = NULL;
            }
            else (*M) = 0;
        }
        return;
    }

    if(x == *m)
    {
        llu subSize = (llu)sqrt(u);
        int p = (int)(log(u)/log(2));
        int lower = (int)pow(2,p/2);
        llu x_ = summary -> min();
        llu y = cluster[x_]->min();
        x = x_*lower + y;
        *m = x;
    }

    llu subSize = (llu)sqrt(u);
    int p = (int)(log(u)/log(2));
    int lower = (int)pow(2,p/2);
    int upper = (int)pow(2,ceil(p/2.0));

    llu hi = x / lower, lo = x % lower;

    cluster[hi]->Delete(lo); 

    if(cluster[hi]->m == NULL)
    {
        summary->Delete(hi);
        if( x == (*M))
        {
            if(summary->M == NULL)
                (*M) == *m;
            else
                *M = summary->max()*lower + cluster[summary->max()]->max();
        }
    }

    else if( x == (*M))
    {
        *M = summary->max()*lower + cluster[summary->max()]->max();
    }
}


int main()
{
    struct rusage r_usage;
    int count = 0;
    int nodes;
    cin>>nodes;
    int e = 19;
    vector<vector<pair<int,int>>> G(nodes);
    vector<pair<int,int>> edge;
    int disc[nodes] = {0};
    vector<int> d(nodes,1000000);
    vector<int> par(nodes,-1);
    /*
    //Small graph
    int u[14] = {0,0,1,1,2,2,2,3,3,4,6,6,6,7};
    int v[14] = {1,7,7,2,8,5,3,5,4,5,5,8,7,8};
    int wt[14] = {4,8,11,8,2,4,7,14,9,10,2,6,1,7};
    for(int i=0;i<1000;i++) 
    {

        G[u[i]].push_back(make_pair(v[i],wt[i]));
        G[v[i]].push_back(make_pair(u[i],wt[i]));
    }
    */

    /*
    //complete graph with random edge weights
    for (int i = 0; i < nodes; ++i)
    {
        for (int j = i+1; j < nodes; ++j)
        {
            int a;
            cin>>a;
            G[i].push_back(make_pair(j,a));
            G[j].push_back(make_pair(i,a));
        }
    }

	*/
    int s,dest,weight;
    s = 0;

    for(int j = 1;j<nodes;j++)
    {
    	int a;
        cin>>a;
        G[0].push_back(make_pair(j,a));
        G[j].push_back(make_pair(0,a));
    }

    while(1)
    {
    	cin>>s;
    	if(s==-10)
    		break;
    	cin>>dest;
    	cin>>weight;
    	G[s].push_back(make_pair(dest,weight));
        G[dest].push_back(make_pair(s,weight));

    }

    cin>>e;
    long long prod = e*nodes;
    e = 0;

    while(prod)
    {
    	prod /= 2;
    	e++;
    }

    vEB *vEB = new class vEB(pow(2, e));
    vEB->insert(0);
    d[0] = 0; 
    par[0] = 0;
    auto start = chrono::high_resolution_clock::now();
    vector<int> w(nodes);
    while(count < nodes)
    {
        int value = vEB->extractMin();
        int v = value%nodes;
        int weight = value/nodes;
        if(disc[v]==1)
           continue;
        disc[v] = 1;

        count++;
        edge.push_back(make_pair(par[v],v));
        int n = G[v].size();
        
        for(int i=0;i<n;i++) 
        {
            if(disc[G[v][i].first]==0)	//The vertex isn't visited only their d[] will change
            {
                int v2=G[v][i].first;
                int cost=G[v][i].second;//weight of edge v,v2
                if(d[v2]>cost) 
                {
                    d[v2]=cost;
                    vEB->insert(cost*nodes + v2);
                    par[v2]=v;			//parent will be updated in this loop
                    w[v2] = cost;
                }
            }
        }
    }
    /*
	//Testing prim's implementation correctness
    long long sum = 0;
    for(int i = 0; i < nodes; i++)
        sum += w[i];
    cout<<sum<<endl;*/

	//Time computation
    auto stop = chrono::high_resolution_clock::now(); 
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start); 
    cout<<duration.count();
    /*
    //Space computation
    getrusage(RUSAGE_SELF,&r_usage);
	cout<<(r_usage.ru_maxrss)/1024;*/
/*
	//Printing output MST
    cout<<"MST edge set is"<<endl; 
    for(int i=0;i<edge.size();i++)
        cout<<edge[i].first<<","<<edge[i].second<<endl;

    cout<<edge.size()<<endl;
*/
    return 0;
}

