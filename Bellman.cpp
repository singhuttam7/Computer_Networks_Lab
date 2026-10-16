//Bellman-Ford Algorithm

#include <iostream>
#include <vector>
using namespace std;

struct Edge {
int source;
int destination;
int cost;
};

void bellmanFord(int vertices, int edges, vector<Edge>& graph, int source){
const int INF = 99999;
//Distance from source to every vertex
vector<int> distance(vertices, INF);

distance[source] = 0;

//Relax all edges v-1 times
for(int i = 1; i <= vertices - 1; i++){
for(int j = 0; j < edges; j++){
int u = graph[j].source;
int v = graph[j].destination;
int cost = graph[j].cost;

if (distance[u] != INF &&
distance[u] + cost < distance[v]){
distance[v] = distance[u] + cost;
}
}
}
//Check for negative weight cycle
for(int j = 0; j< edges; j++){
int u = graph[j].source;
int v = graph[j].destination;
int cost = graph[j].cost;

if (distance[u] != INF &&
distance[u] + cost < distance[v]){
cout<<"Negative weight cycle detected!"<<endl;
return ;

}
}
//Display shortest distances
cout<<"\nShortest distances from source "<<source<<":\n";
for(int i = 0; i < vertices; i++){
cout<<"To node "<<i << "=";
if( distance[i] == INF)
cout<<"INF";
else
cout<< distance[i];
cout<<endl;
}
}

int main(){
int vertices, edges;
cout<<"Enter number of vertices: ";
cin>> vertices;
cout<<"Enter number of edges: ";
cin>> edges;
vector<Edge> graph(edges);

cout<<"\nEnter edges as: \n";
cout<<"Source Destination cost\n";
for(int i = 0; i < edges; i++){
cin>> graph[i].source
>>graph[i].destination
>>graph[i].cost;
}

int source;
cout<<"\nEnter source node: ";
cin>> source;
bellmanFord(vertices, edges, graph, source);
return 0;
}



