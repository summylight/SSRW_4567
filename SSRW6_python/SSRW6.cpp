#include<igraph.h>
#include<iostream>
#include<algorithm>
#include<sstream>
#include<vector>
#define MAX 112
using namespace std;
int main(){
    igraph_t graph[MAX];
    igraph_small(&graph[0],6,IGRAPH_UNDIRECTED,0,1,1,2,2,3,3,4,4,5,-1);
    igraph_write_graph_edgelist(&graph[0],stdout);
    return 0;
} 