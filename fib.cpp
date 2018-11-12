#include "Fheap.hpp"
#include <chrono> 
#include <random>
#include <vector>
#include <iostream>
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
    int V;
    cin>>V;
    //vector<int> w(V);
    //int V = 9;
    int prev = 0;
    vector<pair<int, int> > graph[V];
    /*for(int i = 0; i < V*V; i++) {
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
    for (int i = 0; i < V; ++i)
    {
        for (int j = i+1; j < V; ++j)
        {
            int a;
            cin>>a;
            addEdge(graph, i, j, a);
        }
    }
    int edges;
    cin>>edges;
    auto start = std::chrono::high_resolution_clock::now(); 
    primMST(graph, V); 
    auto stop = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start); 
    /*long long sum = 0;
    for (int i = 1; i < V; ++i) {
        //printf("%d - %d\n", parent[i], i);
        sum += w[i];
    }
    cout<<sum<<endl;*/
    cout<<duration.count();   
    
    return 0; 
}
