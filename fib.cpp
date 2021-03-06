#include "Fheap.hpp"
#include <chrono> 
#include <random>
#include <vector>
#include <iostream>
#include <sys/resource.h>
using namespace std;
#define INF 999999

void addEdge(vector <pair<int, int> > adj[], int u, 
    int v, int wt) { 
    adj[u].push_back(make_pair(v, wt)); 
    adj[v].push_back(make_pair(u, wt)); 
} 

void primMST(vector<pair<int,int> > adj[], int V) 
{ 
    FibonacciHeap<int> fibHeap;
    
    vector<int> key(V, INF); 
    vector<int> parent(V, -1); 
    vector<bool> inMST(V, false); 

    fibHeap.insert(0, 0);
    key[0] = 0; 

    while (!fibHeap.isEmpty()) 
    {       
        int u = fibHeap.removeMinimum();
        inMST[u] = true;
        for (auto x : adj[u]) { 
            int v = x.first; 
            int weight = x.second; 
            if (inMST[v] == false && key[v] > weight) { 
                key[v] = weight; 
                fibHeap.insert(v, key[v]);
                parent[v] = u;
                //w[v] = weight;
            } 
        } 
    } 
    
} 


int main(int argc, char* argv[]) 
{
	struct rusage r_usage;
    int V;
    cin>>V;
    //vector<int> w(V);
    //int V = 9;
    int prev = 0;
    vector<pair<int, int> > graph[V];
    /*
	//Generating completely random graph
    for(int i = 0; i < V*V; i++) {
        int status;
        cin>>status;
        if(status == -1)
            continue;
        int v;
        v = status;
        int weight;
        cin>>weight;
        addEdge(graph, prev, v, weight);
        prev = v;
    }*/

    int s,d,weight;
    s = 0;

    for(int j = 1;j<V;j++)
    {
    	int a;
        cin>>a;
        addEdge(graph, 0, j, a);
    }

    while(1)
    {
    	cin>>s;
    	if(s==-10)
    		break;
    	cin>>d;
    	cin>>weight;
    	addEdge(graph,s,d,weight);

    }
/*
	//Complete graph with random edge weights
    for (int i = 0; i < V; ++i)
    {
        for (int j = i+1; j < V; ++j)
        {
            int a;
            cin>>a;
            addEdge(graph, i, j, a);
        }
    }
*/
    int edges;
    cin>>edges;
    
    
	//Time computation
    auto start = std::chrono::high_resolution_clock::now(); 
    primMST(graph, V); 
    auto stop = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    cout<<duration.count(); 
    /*
	//Testing prim's implementation correctness
    long long sum = 0;
    for (int i = 1; i < V; ++i) {
        //printf("%d - %d\n", parent[i], i);
        sum += w[i];
    }
    cout<<sum<<endl;*/
    /*
    Space computation
    primMST(graph, V); 
    getrusage(RUSAGE_SELF,&r_usage);
  	cout<<(r_usage.ru_maxrss)/1024;
  	*/
    return 0; 
}
