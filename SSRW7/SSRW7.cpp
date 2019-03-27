#include<igraph.h>
#include "sfmt/SFMT.h"
#include<iostream>
#include<algorithm>
#include<cstring>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<vector>
#include<time.h>
#define MAXSUBS 853  //7-subgraph count
#define NEXTJUMP 50 //Set for once random walk jump distance
using namespace std;
long int RandStart(igraph_t *graph);
long int RandWalk(igraph_t *graph, int steps, long int startNode);

/**
 * \function print_vector
 * Print elements in an igraph vector  
 * 
 * \param vector pointer
 * \param outfile FILE pointer (using stdout can print to the screen)
 * 
 * */
void print_vector(igraph_vector_t *v, FILE *f) {
  long int i;
  for (i=0; i<igraph_vector_size(v); i++) {
    fprintf(f, " %li", (long int) VECTOR(*v)[i]);
  }
  fprintf(f, "\n");
}

/**
 * \function RandStart
 * Create a startnode that  random walk could start from while obeying Stationary process 
 * 
 * \param graph the input graph
 * \return a startnode id
 * */
long int RandStart(igraph_t *graph){
    igraph_integer_t RANDSTARTNUM=igraph_vcount(graph)*100;
    igraph_integer_t graph_size=igraph_vcount(graph);  //number of vertices of graph
//    printf("here is graph_size : %d\n",graph_size);
    igraph_rng_seed(igraph_rng_default(),clock());
    long int firstNode=igraph_rng_get_integer(igraph_rng_default(), -1, graph_size);
//    printf("here is first node : %ld\n",firstNode);
    return RandWalk(graph,RANDSTARTNUM,firstNode);
}

/**
 * \function RandWalk
 * Perform a randwalk on one given node
 * 
 * \param graph the input graph
 * \param steps the random walk will run
 * \param startNode random walk startNode
 * */
long int RandWalk(igraph_t *graph, int steps, long int startNode){
    igraph_vector_t v;
    igraph_vector_init(&v,10);
    long int nextNode = startNode;
    sfmt_t sfmtSeed ;
	sfmt_init_gen_rand(&sfmtSeed, time(NULL));
    for (int i=0;i<steps;++i){
        igraph_neighbors(graph,&v,nextNode,IGRAPH_ALL); 
//        print_vector(&v, stdout);
        long int next = sfmt_genrand_uint32(&sfmtSeed)%igraph_vector_size(&v);
//        printf("step: %d size : %ld choose :%ld \t",i,igraph_vector_size(&v),next);
        nextNode=VECTOR(v)[next];
//        cout <<nextNode <<"randwalk" <<endl;
    }  
//    cout <<nextNode <<"END" <<endl;
    return nextNode;

}

/**
 * \function main
 * 
 * Based on SSRW(Yang.C) algrithem
 * 
 * \param argv[0] ./SSRW6C
 * \param argv[1] the input graphfile ,NOTICE that file must like vertice one ,vertice two
 * \input graph should be an undirected graph , connected and contain no ring 
 * \param argv[2] the times you want to run the randwalk ,the more you run, the rusult may be more accurate
 * */

int main(int argc, char* argv[]){
    double dur;
    clock_t start,end;
    start = clock();
    srand((unsigned)time(NULL));
    
    sfmt_t sfmtSeed ;
	sfmt_init_gen_rand(&sfmtSeed, time(NULL));
    if (argc <3){
        printf("The pramament of the procedure is like ./SSRW6C which_file_you_want_to_test times_you_want_to_walk\n");
        exit(1);
    }
    char* filename = argv[1];
    FILE *instream = fopen(filename,"r");
    if(!instream){
        string msg="Open file fail!:";
        msg.append(filename);
        throw runtime_error(msg);
    }
    
    const char *delim = ".";
	char *fileNosuffix=strtok(filename,delim);
	string s=fileNosuffix;
	s = s + ".ssrw7result";
	ofstream out(s);
    if(!out){
        string msg="Open file fail!:";
        msg.append(s);
        throw runtime_error(msg);
    }
    long int given_time = atol(argv[2]);
    
    igraph_t G;
    igraph_read_graph_ncol(&G,instream,NULL,0,IGRAPH_ADD_WEIGHTS_NO,IGRAPH_UNDIRECTED);
    long int startid=RandStart(&G);
//    cout << startid <<endl;
    long int count[MAXSUBS];    //count times all subgraph may appear
    long int run_times=0;
    igraph_t graph[MAXSUBS];
    igraph_small(&graph[0],7,IGRAPH_UNDIRECTED,0,6,1,6,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[1],7,IGRAPH_UNDIRECTED,0,5,0,6,1,6,2,6,3,6,4,6,-1);
    igraph_small(&graph[2],7,IGRAPH_UNDIRECTED,0,5,0,6,1,6,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[3],7,IGRAPH_UNDIRECTED,0,5,0,6,1,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[4],7,IGRAPH_UNDIRECTED,0,5,1,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[5],7,IGRAPH_UNDIRECTED,0,5,0,6,1,5,1,6,2,6,3,6,4,6,-1);
    igraph_small(&graph[6],7,IGRAPH_UNDIRECTED,0,5,0,6,1,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[7],7,IGRAPH_UNDIRECTED,0,5,0,6,1,5,1,6,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[8],7,IGRAPH_UNDIRECTED,0,5,0,6,1,5,2,5,3,6,4,6,-1);
    igraph_small(&graph[9],7,IGRAPH_UNDIRECTED,0,5,0,6,1,5,1,6,2,5,3,6,4,6,-1);
    igraph_small(&graph[10],7,IGRAPH_UNDIRECTED,0,5,0,6,1,5,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[11],7,IGRAPH_UNDIRECTED,0,5,0,6,1,5,1,6,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[12],7,IGRAPH_UNDIRECTED,0,5,0,6,1,5,1,6,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[13],7,IGRAPH_UNDIRECTED,0,5,0,6,1,5,1,6,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[14],7,IGRAPH_UNDIRECTED,0,5,0,6,1,5,1,6,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[15],7,IGRAPH_UNDIRECTED,0,5,0,6,1,5,1,6,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[16],7,IGRAPH_UNDIRECTED,0,5,0,6,1,5,1,6,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[17],7,IGRAPH_UNDIRECTED,0,5,0,6,1,5,1,6,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[18],7,IGRAPH_UNDIRECTED,0,5,0,6,1,5,1,6,2,5,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[19],7,IGRAPH_UNDIRECTED,0,5,0,6,1,5,1,6,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[20],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,6,3,6,-1);
    igraph_small(&graph[21],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,6,3,6,4,6,-1);
    igraph_small(&graph[22],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[23],7,IGRAPH_UNDIRECTED,0,4,0,5,1,5,1,6,2,6,3,6,-1);
    igraph_small(&graph[24],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,6,3,6,-1);
    igraph_small(&graph[25],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[26],7,IGRAPH_UNDIRECTED,0,4,0,5,1,5,1,6,2,6,3,6,4,6,-1);
    igraph_small(&graph[27],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,2,6,3,6,5,6,-1);
    igraph_small(&graph[28],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,6,3,6,4,6,-1);
    igraph_small(&graph[29],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,6,3,6,5,6,-1);
    igraph_small(&graph[30],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[31],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,5,3,6,-1);
    igraph_small(&graph[32],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,2,5,3,6,5,6,-1);
    igraph_small(&graph[33],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,5,2,6,3,6,-1);
    igraph_small(&graph[34],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,5,3,6,4,6,-1);
    igraph_small(&graph[35],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,5,3,6,5,6,-1);
    igraph_small(&graph[36],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[37],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[38],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,5,2,6,3,6,5,6,-1);
    igraph_small(&graph[39],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[40],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[41],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,6,2,6,3,6,4,5,-1);
    igraph_small(&graph[42],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,6,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[43],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,6,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[44],7,IGRAPH_UNDIRECTED,0,4,0,5,1,5,1,6,2,5,3,6,4,6,-1);
    igraph_small(&graph[45],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,6,-1);
    igraph_small(&graph[46],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,3,6,4,6,-1);
    igraph_small(&graph[47],7,IGRAPH_UNDIRECTED,0,4,0,5,1,5,1,6,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[48],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,3,6,5,6,-1);
    igraph_small(&graph[49],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[50],7,IGRAPH_UNDIRECTED,0,4,0,5,1,5,1,6,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[51],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[52],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,6,5,6,-1);
    igraph_small(&graph[53],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[54],7,IGRAPH_UNDIRECTED,0,4,0,5,1,5,1,6,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[55],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[56],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,5,2,6,3,5,-1);
    igraph_small(&graph[57],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,5,3,5,4,6,-1);
    igraph_small(&graph[58],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,5,2,6,3,5,3,6,-1);
    igraph_small(&graph[59],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[60],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,5,2,6,3,5,5,6,-1);
    igraph_small(&graph[61],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,5,3,5,4,6,5,6,-1);
    igraph_small(&graph[62],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[63],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[64],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[65],7,IGRAPH_UNDIRECTED,0,4,0,6,1,5,1,6,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[66],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,6,3,6,4,5,-1);
    igraph_small(&graph[67],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[68],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[69],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,6,3,6,4,5,5,6,-1);
    igraph_small(&graph[70],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[71],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[72],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,5,3,6,-1);
    igraph_small(&graph[73],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[74],7,IGRAPH_UNDIRECTED,0,4,0,5,1,5,1,6,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[75],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[76],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[77],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[78],7,IGRAPH_UNDIRECTED,0,4,0,5,1,5,1,6,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[79],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[80],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[81],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[82],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[83],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[84],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[85],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[86],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,6,-1);
    igraph_small(&graph[87],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[88],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,6,4,6,-1);
    igraph_small(&graph[89],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[90],7,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,6,2,5,2,6,3,6,-1);
    igraph_small(&graph[91],7,IGRAPH_UNDIRECTED,0,4,0,5,1,4,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[92],7,IGRAPH_UNDIRECTED,0,4,0,5,1,4,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[93],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,6,-1);
    igraph_small(&graph[94],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,3,6,4,6,-1);
    igraph_small(&graph[95],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[96],7,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,6,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[97],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[98],7,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,6,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[99],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[100],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[101],7,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,6,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[102],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[103],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,1,6,2,5,2,6,3,5,-1);
    igraph_small(&graph[104],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[105],7,IGRAPH_UNDIRECTED,0,4,1,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[106],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,2,5,3,5,4,6,5,6,-1);
    igraph_small(&graph[107],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,1,6,2,5,2,6,3,5,3,6,-1);
    igraph_small(&graph[108],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,1,6,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[109],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[110],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,1,6,2,5,3,5,4,6,5,6,-1);
    igraph_small(&graph[111],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[112],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,1,6,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[113],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,1,6,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[114],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,1,6,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[115],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,3,6,-1);
    igraph_small(&graph[116],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,-1);
    igraph_small(&graph[117],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,3,6,4,6,-1);
    igraph_small(&graph[118],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[119],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,3,6,5,6,-1);
    igraph_small(&graph[120],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[121],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,5,6,-1);
    igraph_small(&graph[122],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[123],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[124],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[125],7,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,6,2,5,2,6,3,5,3,6,-1);
    igraph_small(&graph[126],7,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,6,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[127],7,IGRAPH_UNDIRECTED,0,4,0,5,1,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[128],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,5,3,6,-1);
    igraph_small(&graph[129],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[130],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[131],7,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,6,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[132],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,5,5,6,-1);
    igraph_small(&graph[133],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[134],7,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,6,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[135],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,3,5,4,6,5,6,-1);
    igraph_small(&graph[136],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[137],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[138],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[139],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[140],7,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,6,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[141],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[142],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,6,4,5,-1);
    igraph_small(&graph[143],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[144],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[145],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[146],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,6,4,5,-1);
    igraph_small(&graph[147],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[148],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,2,5,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[149],7,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,6,2,5,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[150],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,2,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[151],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[152],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[153],7,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,6,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[154],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[155],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,1,6,2,5,2,6,3,5,3,6,4,5,-1);
    igraph_small(&graph[156],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,1,6,2,5,2,6,3,5,4,5,4,6,-1);
    igraph_small(&graph[157],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,2,5,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[158],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,1,6,2,5,3,5,4,5,4,6,5,6,-1);
    igraph_small(&graph[159],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,2,5,2,6,3,5,4,5,4,6,5,6,-1);
    igraph_small(&graph[160],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,1,6,2,5,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[161],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,1,6,2,5,2,6,3,5,4,5,4,6,5,6,-1);
    igraph_small(&graph[162],7,IGRAPH_UNDIRECTED,0,4,0,6,1,4,1,6,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[163],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,-1);
    igraph_small(&graph[164],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[165],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[166],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[167],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,4,5,-1);
    igraph_small(&graph[168],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[169],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,4,5,5,6,-1);
    igraph_small(&graph[170],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[171],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[172],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,5,3,6,4,5,-1);
    igraph_small(&graph[173],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[174],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,5,3,6,4,5,5,6,-1);
    igraph_small(&graph[175],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,5,4,5,4,6,5,6,-1);
    igraph_small(&graph[176],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[177],7,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,6,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[178],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[179],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[180],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[181],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,-1);
    igraph_small(&graph[182],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,2,4,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[183],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[184],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[185],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[186],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,3,6,-1);
    igraph_small(&graph[187],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,4,6,-1);
    igraph_small(&graph[188],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[189],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,2,4,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[190],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,3,5,4,6,5,6,-1);
    igraph_small(&graph[191],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,2,4,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[192],7,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,5,2,4,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[193],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[194],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[195],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,2,4,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[196],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[197],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,-1);
    igraph_small(&graph[198],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[199],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,3,5,3,6,4,6,-1);
    igraph_small(&graph[200],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[201],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[202],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[203],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[204],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[205],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[206],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[207],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,2,4,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[208],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[209],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[210],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,-1);
    igraph_small(&graph[211],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[212],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,4,6,5,6,-1);
    igraph_small(&graph[213],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[214],7,IGRAPH_UNDIRECTED,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[215],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,6,2,5,2,6,-1);
    igraph_small(&graph[216],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,6,2,5,2,6,3,6,-1);
    igraph_small(&graph[217],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,6,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[218],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,6,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[219],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,6,2,5,2,6,-1);
    igraph_small(&graph[220],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,2,6,-1);
    igraph_small(&graph[221],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,3,6,-1);
    igraph_small(&graph[222],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,6,2,5,2,6,3,6,-1);
    igraph_small(&graph[223],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,4,6,-1);
    igraph_small(&graph[224],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,6,2,5,2,6,4,6,-1);
    igraph_small(&graph[225],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,5,6,-1);
    igraph_small(&graph[226],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,2,6,3,6,-1);
    igraph_small(&graph[227],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,2,6,4,6,-1);
    igraph_small(&graph[228],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,3,6,4,6,-1);
    igraph_small(&graph[229],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,6,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[230],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,2,6,5,6,-1);
    igraph_small(&graph[231],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,4,6,5,6,-1);
    igraph_small(&graph[232],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[233],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,2,6,3,6,5,6,-1);
    igraph_small(&graph[234],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,2,6,4,6,5,6,-1);
    igraph_small(&graph[235],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[236],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,6,3,5,3,6,-1);
    igraph_small(&graph[237],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,6,3,5,4,6,-1);
    igraph_small(&graph[238],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[239],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[240],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[241],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[242],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,-1);
    igraph_small(&graph[243],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,5,3,6,4,6,-1);
    igraph_small(&graph[244],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[245],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,5,2,6,5,6,-1);
    igraph_small(&graph[246],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,5,3,6,5,6,-1);
    igraph_small(&graph[247],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,5,2,6,3,6,5,6,-1);
    igraph_small(&graph[248],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,1,6,2,5,2,6,3,6,5,6,-1);
    igraph_small(&graph[249],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[250],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[251],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[252],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,5,6,-1);
    igraph_small(&graph[253],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[254],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[255],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[256],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,6,3,5,-1);
    igraph_small(&graph[257],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,6,3,5,3,6,-1);
    igraph_small(&graph[258],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,6,3,5,4,6,-1);
    igraph_small(&graph[259],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[260],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[261],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[262],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[263],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[264],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[265],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,6,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[266],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,2,6,3,5,3,6,-1);
    igraph_small(&graph[267],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[268],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,3,5,3,6,4,6,-1);
    igraph_small(&graph[269],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,3,5,3,6,5,6,-1);
    igraph_small(&graph[270],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,3,5,4,6,5,6,-1);
    igraph_small(&graph[271],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,6,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[272],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[273],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[274],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[275],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[276],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[277],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,-1);
    igraph_small(&graph[278],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[279],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,5,3,5,3,6,4,6,-1);
    igraph_small(&graph[280],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[281],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[282],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[283],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[284],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,5,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[285],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[286],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[287],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[288],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[289],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[290],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[291],7,IGRAPH_UNDIRECTED,0,3,0,4,1,4,1,5,2,5,2,6,3,6,-1);
    igraph_small(&graph[292],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,2,6,-1);
    igraph_small(&graph[293],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,3,6,-1);
    igraph_small(&graph[294],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,2,5,2,6,3,6,-1);
    igraph_small(&graph[295],7,IGRAPH_UNDIRECTED,0,3,0,4,1,4,1,5,1,6,2,5,2,6,3,6,-1);
    igraph_small(&graph[296],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,4,6,-1);
    igraph_small(&graph[297],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,2,5,2,6,4,6,-1);
    igraph_small(&graph[298],7,IGRAPH_UNDIRECTED,0,3,0,4,1,4,1,5,1,6,2,5,2,6,4,6,-1);
    igraph_small(&graph[299],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,5,6,-1);
    igraph_small(&graph[300],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,2,5,2,6,5,6,-1);
    igraph_small(&graph[301],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,2,6,3,6,-1);
    igraph_small(&graph[302],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,2,6,4,6,-1);
    igraph_small(&graph[303],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,3,6,4,6,-1);
    igraph_small(&graph[304],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[305],7,IGRAPH_UNDIRECTED,0,3,0,4,1,4,1,5,1,6,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[306],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,2,6,5,6,-1);
    igraph_small(&graph[307],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,3,6,5,6,-1);
    igraph_small(&graph[308],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,2,5,2,6,3,6,5,6,-1);
    igraph_small(&graph[309],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,4,6,5,6,-1);
    igraph_small(&graph[310],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[311],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,2,6,3,6,5,6,-1);
    igraph_small(&graph[312],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,2,6,4,6,5,6,-1);
    igraph_small(&graph[313],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[314],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,6,3,5,-1);
    igraph_small(&graph[315],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,6,3,5,3,6,-1);
    igraph_small(&graph[316],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,6,3,5,4,6,-1);
    igraph_small(&graph[317],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[318],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[319],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,-1);
    igraph_small(&graph[320],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,4,6,-1);
    igraph_small(&graph[321],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,3,6,4,6,-1);
    igraph_small(&graph[322],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[323],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[324],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,4,6,5,6,-1);
    igraph_small(&graph[325],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[326],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,5,6,-1);
    igraph_small(&graph[327],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,4,6,5,6,-1);
    igraph_small(&graph[328],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[329],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[330],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,5,5,6,-1);
    igraph_small(&graph[331],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[332],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[333],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[334],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[335],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,2,6,3,5,-1);
    igraph_small(&graph[336],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[337],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,-1);
    igraph_small(&graph[338],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[339],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,3,5,3,6,4,6,-1);
    igraph_small(&graph[340],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,3,5,3,6,5,6,-1);
    igraph_small(&graph[341],7,IGRAPH_UNDIRECTED,0,3,0,4,1,4,1,5,1,6,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[342],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[343],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[344],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[345],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[346],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[347],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[348],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,2,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[349],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[350],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[351],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[352],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[353],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[354],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[355],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,6,4,5,-1);
    igraph_small(&graph[356],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[357],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,6,2,5,2,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[358],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[359],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[360],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[361],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[362],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[363],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[364],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[365],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[366],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,4,5,5,6,-1);
    igraph_small(&graph[367],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[368],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[369],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[370],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[371],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[372],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[373],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[374],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[375],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[376],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,5,1,6,2,4,2,5,2,6,-1);
    igraph_small(&graph[377],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,5,1,6,2,4,2,5,3,6,-1);
    igraph_small(&graph[378],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,-1);
    igraph_small(&graph[379],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,5,1,6,2,4,2,5,2,6,4,6,-1);
    igraph_small(&graph[380],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,5,1,6,2,4,2,5,3,6,4,6,-1);
    igraph_small(&graph[381],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[382],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,5,1,6,2,4,2,5,2,6,4,6,5,6,-1);
    igraph_small(&graph[383],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[384],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,-1);
    igraph_small(&graph[385],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,1,6,2,4,2,5,2,6,3,6,-1);
    igraph_small(&graph[386],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,4,6,-1);
    igraph_small(&graph[387],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,1,6,2,4,2,5,2,6,4,6,-1);
    igraph_small(&graph[388],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,4,2,5,3,6,4,6,-1);
    igraph_small(&graph[389],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,-1);
    igraph_small(&graph[390],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,4,6,-1);
    igraph_small(&graph[391],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,3,6,4,6,-1);
    igraph_small(&graph[392],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[393],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,5,6,-1);
    igraph_small(&graph[394],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,3,6,5,6,-1);
    igraph_small(&graph[395],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,1,6,2,4,2,5,2,6,3,6,5,6,-1);
    igraph_small(&graph[396],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[397],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,5,6,-1);
    igraph_small(&graph[398],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,4,6,5,6,-1);
    igraph_small(&graph[399],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[400],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[401],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[402],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,-1);
    igraph_small(&graph[403],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,3,5,4,6,-1);
    igraph_small(&graph[404],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,4,2,6,3,5,4,6,-1);
    igraph_small(&graph[405],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[406],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,3,6,-1);
    igraph_small(&graph[407],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,4,6,-1);
    igraph_small(&graph[408],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[409],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,4,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[410],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,3,5,3,6,5,6,-1);
    igraph_small(&graph[411],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,4,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[412],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[413],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[414],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[415],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[416],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,4,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[417],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[418],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,6,4,5,-1);
    igraph_small(&graph[419],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,3,6,4,5,4,6,-1);
    igraph_small(&graph[420],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,4,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[421],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,1,6,2,4,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[422],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,6,4,5,5,6,-1);
    igraph_small(&graph[423],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,3,6,4,5,5,6,-1);
    igraph_small(&graph[424],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,4,2,6,3,6,4,5,5,6,-1);
    igraph_small(&graph[425],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,1,6,2,4,2,6,3,6,4,5,5,6,-1);
    igraph_small(&graph[426],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,4,5,4,6,5,6,-1);
    igraph_small(&graph[427],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,4,2,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[428],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,4,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[429],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,1,6,2,4,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[430],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,2,4,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[431],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[432],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,6,4,5,5,6,-1);
    igraph_small(&graph[433],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[434],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[435],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,4,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[436],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,1,6,2,4,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[437],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[438],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,-1);
    igraph_small(&graph[439],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,5,1,6,2,4,2,5,2,6,4,5,4,6,-1);
    igraph_small(&graph[440],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,5,1,6,2,4,2,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[441],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,5,1,6,2,4,2,5,4,5,4,6,5,6,-1);
    igraph_small(&graph[442],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,5,2,4,2,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[443],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[444],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,5,1,6,2,4,2,5,2,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[445],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,5,1,6,2,4,2,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[446],7,IGRAPH_UNDIRECTED,0,3,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[447],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,4,2,6,3,5,3,6,4,5,-1);
    igraph_small(&graph[448],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,4,2,6,3,5,4,5,4,6,-1);
    igraph_small(&graph[449],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,4,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[450],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,4,2,6,3,5,4,5,5,6,-1);
    igraph_small(&graph[451],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,4,3,5,3,6,4,5,5,6,-1);
    igraph_small(&graph[452],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,2,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[453],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,4,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[454],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,4,2,6,3,5,3,6,4,5,5,6,-1);
    igraph_small(&graph[455],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,4,2,6,3,5,4,5,4,6,5,6,-1);
    igraph_small(&graph[456],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[457],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,6,2,4,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[458],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,-1);
    igraph_small(&graph[459],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[460],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[461],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[462],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,-1);
    igraph_small(&graph[463],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[464],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,5,6,-1);
    igraph_small(&graph[465],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[466],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[467],7,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[468],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[469],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,5,-1);
    igraph_small(&graph[470],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[471],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,5,5,6,-1);
    igraph_small(&graph[472],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[473],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,2,4,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[474],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[475],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[476],7,IGRAPH_UNDIRECTED,0,3,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[477],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,5,1,6,2,5,3,4,3,6,-1);
    igraph_small(&graph[478],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,5,1,6,2,5,3,4,5,6,-1);
    igraph_small(&graph[479],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,5,2,5,3,4,3,6,5,6,-1);
    igraph_small(&graph[480],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,5,1,6,2,5,2,6,3,4,3,6,-1);
    igraph_small(&graph[481],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,5,1,6,2,5,3,4,3,6,4,6,-1);
    igraph_small(&graph[482],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,5,1,6,2,5,2,6,3,4,5,6,-1);
    igraph_small(&graph[483],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,5,1,6,2,5,3,4,3,6,5,6,-1);
    igraph_small(&graph[484],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,5,2,5,3,4,3,6,4,6,5,6,-1);
    igraph_small(&graph[485],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,5,1,6,2,5,2,6,3,4,3,6,4,6,-1);
    igraph_small(&graph[486],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,5,1,6,2,5,2,6,3,4,3,6,5,6,-1);
    igraph_small(&graph[487],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,5,1,6,2,5,3,4,3,6,4,6,5,6,-1);
    igraph_small(&graph[488],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,5,1,6,2,5,2,6,3,4,3,6,4,6,5,6,-1);
    igraph_small(&graph[489],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,6,2,6,3,4,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[490],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,6,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[491],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[492],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,4,3,5,3,6,5,6,-1);
    igraph_small(&graph[493],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,4,3,5,4,6,5,6,-1);
    igraph_small(&graph[494],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,5,1,6,2,5,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[495],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[496],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,5,1,6,2,6,3,4,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[497],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[498],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,5,1,6,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[499],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,4,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[500],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,5,1,6,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[501],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,-1);
    igraph_small(&graph[502],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,4,6,-1);
    igraph_small(&graph[503],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[504],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,4,6,5,6,-1);
    igraph_small(&graph[505],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,4,2,5,2,6,4,6,5,6,-1);
    igraph_small(&graph[506],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,2,4,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[507],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,4,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[508],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[509],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,4,6,5,6,-1);
    igraph_small(&graph[510],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[511],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[512],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[513],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,-1);
    igraph_small(&graph[514],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,-1);
    igraph_small(&graph[515],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[516],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,4,2,5,3,5,4,6,5,6,-1);
    igraph_small(&graph[517],7,IGRAPH_UNDIRECTED,0,3,0,4,1,4,1,5,1,6,2,4,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[518],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,2,4,2,5,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[519],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[520],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[521],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,4,2,5,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[522],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[523],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[524],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[525],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[526],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[527],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[528],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[529],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[530],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[531],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[532],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[533],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[534],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,5,5,6,-1);
    igraph_small(&graph[535],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[536],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,2,4,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[537],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[538],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,4,2,5,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[539],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[540],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[541],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,4,4,6,-1);
    igraph_small(&graph[542],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,3,4,3,6,4,6,-1);
    igraph_small(&graph[543],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,2,5,2,6,3,4,3,6,4,6,-1);
    igraph_small(&graph[544],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,5,2,6,3,4,3,6,4,6,-1);
    igraph_small(&graph[545],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,4,5,6,-1);
    igraph_small(&graph[546],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,3,4,3,6,5,6,-1);
    igraph_small(&graph[547],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,2,5,2,6,3,4,3,6,5,6,-1);
    igraph_small(&graph[548],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,5,2,6,3,4,3,6,5,6,-1);
    igraph_small(&graph[549],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,2,5,2,6,3,4,4,6,5,6,-1);
    igraph_small(&graph[550],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,5,2,6,3,4,4,6,5,6,-1);
    igraph_small(&graph[551],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,2,5,3,4,3,6,4,6,5,6,-1);
    igraph_small(&graph[552],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,5,3,4,3,6,4,6,5,6,-1);
    igraph_small(&graph[553],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,2,5,2,6,3,4,3,6,4,6,5,6,-1);
    igraph_small(&graph[554],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,4,3,6,4,6,-1);
    igraph_small(&graph[555],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,4,3,6,5,6,-1);
    igraph_small(&graph[556],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,4,4,6,5,6,-1);
    igraph_small(&graph[557],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,3,4,3,6,4,6,5,6,-1);
    igraph_small(&graph[558],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,2,5,2,6,3,4,3,6,4,6,5,6,-1);
    igraph_small(&graph[559],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,5,2,6,3,4,3,6,4,6,5,6,-1);
    igraph_small(&graph[560],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,4,3,6,4,6,5,6,-1);
    igraph_small(&graph[561],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,1,6,2,6,3,4,3,5,4,6,5,6,-1);
    igraph_small(&graph[562],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[563],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,4,3,5,4,6,5,6,-1);
    igraph_small(&graph[564],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,2,6,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[565],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[566],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,2,5,2,6,3,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[567],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,6,2,5,3,4,3,5,4,6,5,6,-1);
    igraph_small(&graph[568],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,6,2,5,2,6,3,4,3,5,4,6,5,6,-1);
    igraph_small(&graph[569],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,2,5,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[570],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[571],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,4,3,5,4,6,5,6,-1);
    igraph_small(&graph[572],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,6,2,5,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[573],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[574],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[575],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,4,3,5,3,6,5,6,-1);
    igraph_small(&graph[576],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,2,5,2,6,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[577],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[578],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,4,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[579],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[580],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[581],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,6,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[582],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[583],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[584],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,4,6,5,6,-1);
    igraph_small(&graph[585],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[586],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[587],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[588],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[589],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[590],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[591],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,5,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[592],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[593],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[594],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[595],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[596],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[597],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[598],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,2,6,-1);
    igraph_small(&graph[599],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,3,6,-1);
    igraph_small(&graph[600],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,2,4,2,5,2,6,3,6,-1);
    igraph_small(&graph[601],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,6,-1);
    igraph_small(&graph[602],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,3,6,4,6,-1);
    igraph_small(&graph[603],7,IGRAPH_UNDIRECTED,0,3,0,4,1,3,1,5,1,6,2,4,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[604],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[605],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[606],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,6,-1);
    igraph_small(&graph[607],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,3,6,4,6,-1);
    igraph_small(&graph[608],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,5,1,6,2,4,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[609],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,5,6,-1);
    igraph_small(&graph[610],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,3,6,5,6,-1);
    igraph_small(&graph[611],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,2,4,2,5,2,6,3,6,5,6,-1);
    igraph_small(&graph[612],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[613],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,6,5,6,-1);
    igraph_small(&graph[614],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[615],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,6,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[616],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,2,4,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[617],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,6,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[618],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,6,2,4,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[619],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,6,2,4,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[620],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[621],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,6,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[622],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,-1);
    igraph_small(&graph[623],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,3,5,4,6,-1);
    igraph_small(&graph[624],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[625],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,3,5,3,6,4,6,-1);
    igraph_small(&graph[626],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[627],7,IGRAPH_UNDIRECTED,0,3,0,4,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[628],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,2,4,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[629],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[630],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[631],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[632],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[633],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[634],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[635],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[636],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[637],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[638],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[639],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[640],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[641],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[642],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[643],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,2,4,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[644],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[645],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[646],7,IGRAPH_UNDIRECTED,0,3,0,4,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[647],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[648],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[649],7,IGRAPH_UNDIRECTED,0,3,0,4,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[650],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[651],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[652],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[653],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,6,-1);
    igraph_small(&graph[654],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,4,6,-1);
    igraph_small(&graph[655],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,4,6,5,6,-1);
    igraph_small(&graph[656],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[657],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,4,6,5,6,-1);
    igraph_small(&graph[658],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[659],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,6,3,5,3,6,-1);
    igraph_small(&graph[660],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,6,3,5,4,6,-1);
    igraph_small(&graph[661],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[662],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,3,5,3,6,5,6,-1);
    igraph_small(&graph[663],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,2,4,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[664],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,2,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[665],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,4,1,5,2,4,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[666],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[667],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[668],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[669],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,2,4,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[670],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[671],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[672],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[673],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[674],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[675],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[676],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[677],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[678],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[679],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,5,2,6,3,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[680],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,5,2,6,3,4,3,5,3,6,5,6,-1);
    igraph_small(&graph[681],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,5,2,6,3,4,3,5,4,6,5,6,-1);
    igraph_small(&graph[682],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,5,2,6,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[683],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,6,3,4,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[684],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[685],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[686],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,6,2,5,2,6,3,4,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[687],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,6,2,5,2,6,3,4,3,5,3,6,4,5,5,6,-1);
    igraph_small(&graph[688],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[689],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,6,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[690],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[691],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,4,3,6,-1);
    igraph_small(&graph[692],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,5,1,6,2,4,2,5,2,6,3,4,3,6,4,6,-1);
    igraph_small(&graph[693],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,2,4,2,5,2,6,3,4,3,6,5,6,-1);
    igraph_small(&graph[694],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,5,1,6,2,4,2,5,2,6,3,4,3,6,5,6,-1);
    igraph_small(&graph[695],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,2,4,2,5,3,4,3,6,4,6,5,6,-1);
    igraph_small(&graph[696],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,5,1,6,2,4,2,5,3,4,3,6,4,6,5,6,-1);
    igraph_small(&graph[697],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,4,3,6,4,6,-1);
    igraph_small(&graph[698],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,4,3,6,5,6,-1);
    igraph_small(&graph[699],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,3,4,3,6,4,6,5,6,-1);
    igraph_small(&graph[700],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,5,1,6,2,4,2,5,2,6,3,4,3,6,4,6,5,6,-1);
    igraph_small(&graph[701],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,4,3,6,4,6,5,6,-1);
    igraph_small(&graph[702],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[703],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,5,6,-1);
    igraph_small(&graph[704],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,4,3,5,4,6,5,6,-1);
    igraph_small(&graph[705],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[706],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[707],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[708],7,IGRAPH_UNDIRECTED,0,3,0,4,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[709],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[710],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[711],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,4,6,5,6,-1);
    igraph_small(&graph[712],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[713],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,2,4,2,5,2,6,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[714],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[715],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[716],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,6,-1);
    igraph_small(&graph[717],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,3,2,4,2,5,3,6,4,6,-1);
    igraph_small(&graph[718],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[719],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[720],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[721],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[722],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[723],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[724],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[725],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[726],7,IGRAPH_UNDIRECTED,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[727],7,IGRAPH_UNDIRECTED,0,2,0,4,0,6,1,3,1,5,1,6,2,4,2,6,3,5,-1);
    igraph_small(&graph[728],7,IGRAPH_UNDIRECTED,0,2,0,4,0,6,1,3,1,5,1,6,2,4,2,6,3,5,3,6,-1);
    igraph_small(&graph[729],7,IGRAPH_UNDIRECTED,0,2,0,4,0,6,1,3,1,5,1,6,2,4,2,6,3,5,4,6,-1);
    igraph_small(&graph[730],7,IGRAPH_UNDIRECTED,0,2,0,4,0,6,1,3,1,5,1,6,2,4,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[731],7,IGRAPH_UNDIRECTED,0,2,0,4,0,6,1,3,1,5,1,6,2,4,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[732],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,2,4,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[733],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,5,6,-1);
    igraph_small(&graph[734],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,2,4,2,5,2,6,3,6,5,6,-1);
    igraph_small(&graph[735],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,6,4,6,-1);
    igraph_small(&graph[736],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,6,5,6,-1);
    igraph_small(&graph[737],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,4,6,5,6,-1);
    igraph_small(&graph[738],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[739],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,2,4,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[740],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,6,4,6,5,6,-1);
    igraph_small(&graph[741],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,1,3,1,5,1,6,2,4,2,6,3,5,3,6,-1);
    igraph_small(&graph[742],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,6,3,5,3,6,-1);
    igraph_small(&graph[743],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,6,3,5,4,6,-1);
    igraph_small(&graph[744],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,1,3,1,5,1,6,2,4,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[745],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,6,3,5,5,6,-1);
    igraph_small(&graph[746],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,3,5,3,6,5,6,-1);
    igraph_small(&graph[747],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[748],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[749],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[750],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,6,2,4,2,5,2,6,4,5,4,6,-1);
    igraph_small(&graph[751],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,6,2,4,2,5,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[752],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,6,2,4,2,5,2,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[753],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,6,2,4,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[754],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[755],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[756],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[757],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[758],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[759],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[760],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[761],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,2,4,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[762],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[763],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[764],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[765],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,6,3,5,3,6,-1);
    igraph_small(&graph[766],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,6,3,5,4,6,-1);
    igraph_small(&graph[767],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[768],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,2,4,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[769],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,3,5,4,6,5,6,-1);
    igraph_small(&graph[770],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[771],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[772],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[773],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,6,2,4,2,5,2,6,3,5,3,6,-1);
    igraph_small(&graph[774],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,6,2,4,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[775],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,6,2,4,2,5,3,5,3,6,4,6,-1);
    igraph_small(&graph[776],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,6,2,4,2,5,3,5,4,6,5,6,-1);
    igraph_small(&graph[777],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,2,4,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[778],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,1,3,1,4,1,6,2,4,2,5,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[779],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,6,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[780],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,6,2,4,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[781],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,6,2,4,2,5,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[782],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,6,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[783],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[784],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,3,5,3,6,4,6,-1);
    igraph_small(&graph[785],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[786],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[787],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[788],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[789],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[790],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[791],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,2,4,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[792],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[793],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[794],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[795],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[796],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,6,2,4,2,5,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[797],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[798],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[799],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[800],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,4,6,5,6,-1);
    igraph_small(&graph[801],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[802],7,IGRAPH_UNDIRECTED,0,2,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[803],7,IGRAPH_UNDIRECTED,0,2,0,3,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,-1);
    igraph_small(&graph[804],7,IGRAPH_UNDIRECTED,0,2,0,3,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[805],7,IGRAPH_UNDIRECTED,0,2,0,3,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[806],7,IGRAPH_UNDIRECTED,0,2,0,3,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[807],7,IGRAPH_UNDIRECTED,0,2,0,3,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[808],7,IGRAPH_UNDIRECTED,0,2,0,3,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[809],7,IGRAPH_UNDIRECTED,0,2,0,3,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[810],7,IGRAPH_UNDIRECTED,0,2,0,3,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[811],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,-1);
    igraph_small(&graph[812],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,4,6,-1);
    igraph_small(&graph[813],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,6,1,3,1,4,1,5,1,6,2,4,2,5,3,5,3,6,4,6,-1);
    igraph_small(&graph[814],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[815],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[816],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[817],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[818],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[819],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[820],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[821],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[822],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[823],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[824],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[825],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,4,6,5,6,-1);
    igraph_small(&graph[826],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[827],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[828],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,5,3,6,4,6,-1);
    igraph_small(&graph[829],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,5,3,6,5,6,-1);
    igraph_small(&graph[830],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,5,4,6,5,6,-1);
    igraph_small(&graph[831],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[832],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[833],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[834],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,5,1,6,2,3,2,4,2,5,2,6,3,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[835],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,5,1,6,2,3,2,4,2,5,2,6,3,4,3,5,3,6,5,6,-1);
    igraph_small(&graph[836],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,5,1,6,2,3,2,4,2,5,2,6,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[837],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,6,2,3,2,4,2,5,2,6,3,4,3,5,3,6,4,5,4,6,-1);
    igraph_small(&graph[838],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,6,2,3,2,4,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[839],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,5,1,6,2,3,2,4,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[840],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[841],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,3,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[842],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,2,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,4,6,-1);
    igraph_small(&graph[843],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,2,1,3,1,4,1,5,1,6,2,4,2,5,2,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[844],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,2,1,3,1,4,1,5,2,4,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[845],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,2,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[846],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,2,1,3,1,4,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[847],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,2,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[848],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,2,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,6,-1);
    igraph_small(&graph[849],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,2,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,6,5,6,-1);
    igraph_small(&graph[850],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,2,1,3,1,4,1,5,1,6,2,4,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[851],7,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,0,6,1,2,1,3,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    igraph_small(&graph[852],7,IGRAPH_UNDIRECTED,0,1,0,2,0,3,0,4,0,5,0,6,1,2,1,3,1,4,1,5,1,6,2,3,2,4,2,5,2,6,3,4,3,5,3,6,4,5,4,6,5,6,-1);
    //for(int i=0;i<MAXSUBNAME;++i)
    //    igraph_write_graph_edgelist(&graph[i],stdout);
    int W_constant[]={720,264,1248,66,180,660,510,2088,40,212,400,1308,1016,3540,636,2592,2244,6432,6480,14160,84,432,2112,12,334,136,240,200,1156,806,3404,17,58,202,100,159,296,1064,692,828,3472,312,1152,3240,98,614,403,574,434,670,742,2226,1370,1633,2134,5704,58,64,390,328,324,672,2088,1146,1664,5832,636,352,2132,2036,1440,5308,1488,1410,1620,4674,3000,4040,4740,10782,984,4024,3160,9376,9864,20568,808,496,1908,5312,62,152,150,662,207,430,440,286,561,1819,1270,1990,5480,38,31,140,110,480,150,380,476,300,1684,1318,5632,340,1446,668,1084,976,3570,3182,2450,3449,8756,220,224,368,1298,699,890,1066,1010,452,976,1182,3572,3146,2700,2206,3718,9234,1280,3472,3176,7968,1250,698,1175,1326,720,3699,2379,3600,8652,1416,1082,1592,1480,1210,4292,3132,9912,3488,7672,6960,16832,2528,6272,6502,4452,13696,3092,7604,7906,6085,5196,7908,16232,15096,29944,2772,2788,5868,5696,13560,2852,1460,2104,2388,1524,2410,3360,6276,4434,6538,14824,6624,4464,5852,12726,12816,26280,10326,9700,20784,13188,13308,25648,45276,13248,23760,24360,44400,75168,18,120,672,3456,2,95,36,56,92,16,52,334,524,208,352,231,304,1824,1062,1268,5528,352,496,1856,1044,5328,272,1087,820,1070,612,791,610,934,1298,1472,3806,2251,2700,3464,9176,336,952,1109,940,3576,1980,3224,3056,8472,96,618,984,544,432,1084,1088,3368,1646,3256,2304,8600,2244,2830,2172,2500,7166,4300,7060,5712,6732,15602,6208,13616,14912,29728,14,319,174,134,272,96,170,128,222,283,1120,648,343,674,936,894,739,810,466,2845,3114,2002,8714,378,1190,766,3020,8500,3236,2531,1798,2510,2524,1878,6805,6356,4732,15046,2202,2350,5848,5090,5380,13144,982,666,2436,1948,1392,1853,1656,5964,5383,5865,4344,14396,2259,1548,2568,5961,3518,5200,5692,12884,2712,6696,4276,14400,5572,12273,11076,9696,12864,25050,11784,12397,7626,8701,11334,11836,23642,9722,19940,22968,43404,228,216,1264,538,752,2984,1600,8512,804,880,736,352,840,2562,1782,2049,1794,1424,1830,2136,6126,5228,3500,5678,5294,14092,720,510,574,596,2024,1829,1404,1734,652,1332,5700,4530,5215,3208,5298,13578,2261,2116,2448,1878,1590,1295,2290,2432,1118,1624,2160,1650,2524,6334,6008,3431,3995,5928,5192,13956,1984,1008,1868,940,2384,5488,2416,5056,12800,2284,2492,2488,2776,1558,2232,6812,6204,5968,4618,14680,5264,11708,9976,24304,4898,11120,11246,6268,10683,9672,22768,4766,11654,11288,7564,11344,23548,22776,43256,66,172,244,836,216,776,662,720,2520,2936,1980,8568,5328,11520,12100,11352,13144,9676,24788,9336,6120,19392,22176,42288,6200,4604,5004,4346,3452,6088,5958,11590,7880,10968,11480,23772,2264,5232,3968,5166,3928,5740,10558,9826,10534,23204,10492,20684,20264,21520,39536,20098,12600,18906,19420,36836,21021,20227,15008,20026,38186,21238,39868,66476,5094,2866,4200,4410,4620,3964,4518,4888,5254,4778,4180,4215,5660,10323,10806,10092,7293,10262,11228,22804,4256,9074,9434,8056,19568,3276,3766,5188,2256,9868,10790,6384,21500,19436,19748,19056,37896,15042,13260,29032,35648,63036,35640,37720,35056,63440,104256,19434,17452,20564,14402,19832,37072,14888,28816,34640,62496,858,360,625,1948,1320,1832,4858,13572,5307,4251,4580,4892,4062,4744,10962,9817,23032,4884,2722,10837,9170,10324,6802,22168,1956,1500,4068,3570,4162,4545,4060,10090,8366,8946,9542,21916,19190,16388,19582,17331,18083,19454,36724,18426,11402,16548,34722,9410,10208,19744,18732,17760,37564,35180,63268,11316,10808,10032,19774,18204,37840,9408,9288,6898,5112,7908,7076,10152,17942,16604,11516,17916,34520,18348,32942,31636,58850,33586,28812,58432,96412,30544,31248,32576,55906,22464,21852,41304,30914,32153,28720,55388,89416,9850,8730,9612,9345,9120,10044,17668,18341,16804,19030,36036,33459,33052,34326,59608,34964,32648,60516,96032,55004,57328,51736,57012,92792,147324,20856,18904,33960,60480,32736,55536,52560,91752,91008,144840,219744,376,1456,1152,4392,12960,3044,2436,3568,9832,8716,5250,9859,7828,20884,1360,4346,3584,3680,3884,3536,9824,8730,21600,1560,8448,3456,18432,18500,16504,16820,18924,35956,16536,8904,13560,32280,33456,61152,9608,8032,9042,8370,8344,17633,16090,35120,8936,6544,8170,8294,5904,8860,16682,14408,17442,33900,15824,17050,31576,31264,57248,29332,17784,28904,27028,51680,32283,56978,31318,32066,55744,92892,53520,54464,90976,145104,16596,31352,26848,31100,30052,55648,54380,92720,18054,16364,16100,30410,56004,30716,53354,53169,89230,54486,48972,89140,139916,85468,87004,136856,209700,51782,50280,52980,87378,87288,137764,46050,47316,80310,32592,57600,124416,204372,303648,85216,74400,81852,132456,134800,205432,133616,203664,301152,432000,604800};
    for(int i=0;i<MAXSUBS;++i)
        count[i]=0;
    igraph_vector_t vtmp=IGRAPH_VECTOR_NULL;
    start = clock();
    for(;run_times<given_time;++run_times){
//        cout << " count subgraph time  : " << run_times <<endl;
        long int node[7],user[7];
        node[0]=startid;
        igraph_vector_t nodeneigh[6];
        for(int j=0;j<6;j++)
            igraph_vector_init(&nodeneigh[j],10);

        igraph_neighbors(&G,&nodeneigh[0],node[0],IGRAPH_ALL);
 //       print_vector(&nodeneigh[0], stdout);
        user[1] = sfmt_genrand_uint32(&sfmtSeed)%igraph_vector_size(&nodeneigh[0]);
        node[1] = VECTOR(nodeneigh[0])[user[1]];

        igraph_neighbors(&G,&nodeneigh[1],node[1],IGRAPH_ALL);
        user[2] = sfmt_genrand_uint32(&sfmtSeed)%igraph_vector_size(&nodeneigh[1]);
        node[2] = VECTOR(nodeneigh[1])[user[2]];

        igraph_neighbors(&G,&nodeneigh[2],node[2],IGRAPH_ALL);
        igraph_vector_append(&nodeneigh[1],&nodeneigh[2]);
        user[3] = sfmt_genrand_uint32(&sfmtSeed)%igraph_vector_size(&nodeneigh[1]);
        node[3] = VECTOR(nodeneigh[1])[user[3]];

        igraph_neighbors(&G,&nodeneigh[3],node[3],IGRAPH_ALL);
        igraph_vector_append(&nodeneigh[1],&nodeneigh[3]);
        user[4] = sfmt_genrand_uint32(&sfmtSeed)%igraph_vector_size(&nodeneigh[1]);
        node[4] = VECTOR(nodeneigh[1])[user[4]];

        igraph_neighbors(&G,&nodeneigh[4],node[4],IGRAPH_ALL);
        igraph_vector_append(&nodeneigh[1],&nodeneigh[4]);
        user[5] = sfmt_genrand_uint32(&sfmtSeed)%igraph_vector_size(&nodeneigh[1]);
        node[5] = VECTOR(nodeneigh[1])[user[5]];

        igraph_neighbors(&G,&nodeneigh[5],node[5],IGRAPH_ALL);
        igraph_vector_append(&nodeneigh[1],&nodeneigh[5]);
        user[6] = sfmt_genrand_uint32(&sfmtSeed)%igraph_vector_size(&nodeneigh[1]);
        node[6] = VECTOR(nodeneigh[1])[user[6]];
//        for(int k=0;k<5;k++)
//            print_vector(&nodeneigh[k],stdout);
//        for (int j=0;j<6;j++){
//            cout << node[j] <<endl;
//        }
        igraph_t subgraph;
        igraph_vs_t vids;
        igraph_vs_vector_small(&vids, node[0],node[1],node[2],node[3],node[4],node[5],node[6],-1);
        igraph_induced_subgraph(&G,&subgraph,vids,IGRAPH_SUBGRAPH_CREATE_FROM_SCRATCH);
        igraph_integer_t subgraph_size;  //number of vertices of graph
        igraph_vs_all(&vids);
        igraph_vs_size(&subgraph,&vids,&subgraph_size);
//        cout << "subgraphsize: " <<subgraph_size<<endl;
        if(subgraph_size<7) continue;
        else{
            igraph_bool_t ios=0;
            for(int i=0;(i<MAXSUBS)&&!ios;++i){
                igraph_isomorphic(&subgraph,&graph[i],&ios);
//                cout << "iso result : " << ios <<endl;
                if(ios){
                    igraph_vector_t degree;
                    igraph_vector_init(&degree,7);
                    igraph_vs_t vids_vs;
                    igraph_vs_vector_small(&vids_vs,node[0],node[1],node[2],node[3],node[4],node[5],node[6],-1);
                    igraph_degree(&G,&degree,vids_vs,IGRAPH_ALL,0);
                    long int dg_prod=VECTOR(degree)[1]*(VECTOR(degree)[1]+VECTOR(degree)[2])*(VECTOR(degree)[1]+VECTOR(degree)[2]+VECTOR(degree)[3])*(VECTOR(degree)[1]+VECTOR(degree)[2]+VECTOR(degree)[3]+VECTOR(degree)[4])*(VECTOR(degree)[1]+VECTOR(degree)[2]+VECTOR(degree)[3]+VECTOR(degree)[4]+VECTOR(degree)[5]);
                    count[i]=count[i]+dg_prod;   //count isomorphic subgraph
//                    cout << "find the subgraph: " << i << endl;
                } 
            }
            if(!ios) {     //test if find isomorphic fail
                cout << "FIND SUBGRAPH ISO FAIL!!"<<endl;
                cout << "Now print the graph edge:"<<endl;
                igraph_integer_t from,to;
                for(int k=0;k<igraph_ecount(&subgraph);k++){
                    igraph_edge(&subgraph, k,&from, &to);
                    printf(" Num %d edge : from %d to %d\n",k,from,to);
                }
                exit(1);
            }
        }
        startid=RandWalk(&G,NEXTJUMP,node[5]);
        igraph_destroy(&subgraph);
//        printf("next startnode: %ld",startid);
    }
    end = clock();
    dur = (double)(end - start);
    printf("Use Time:%f\n",(dur/CLOCKS_PER_SEC));  //count time

    long double denom[MAXSUBS];
    long double sum=0;
    for(int i=0;i<MAXSUBS;++i){
//        cout << count[i]<<endl;
        denom[i]=count[i]/W_constant[i];
    }
    int count0=0;
    for(int i=0;i<MAXSUBS;++i)
        if(denom[i]==0) {count0++;
//        cout << "No found subgraph : "<<i<<endl;
    }
    cout  << "0Subgraph counts " << count0 << endl;
//  sort occurrence probability of all subgraph and print most frequent subgraph serial number 
    for(int i=0;i<MAXSUBS;++i)
        sum+=denom[i];
    long double ans[MAXSUBS];
    for(int i=0;i<MAXSUBS;++i)
        ans[i]=denom[i]/sum;
    long double sorted[MAXSUBS];
    for(int i=0;i<MAXSUBS;++i)
        sorted[i]=ans[i];
    sort(sorted,sorted+MAXSUBS);
    for(int i=MAXSUBS-1;i>MAXSUBS-15;--i){
        int exposition;
        bool flag=0;
        for(exposition=0;(exposition<MAXSUBS)&&!flag;exposition++)
            if(sorted[i]==ans[exposition]) flag=1;
        printf("SubGraph[%d] account for %Lf \n",exposition,sorted[i]);
    }
    for(int i=0;i>MAXSUBS;++i){
        out << i << " "<<ans[i]<<endl;
    }
    return 0;
} 