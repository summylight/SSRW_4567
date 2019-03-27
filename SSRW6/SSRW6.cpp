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
#define MAXSUBS 112  //6-subgraph count
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
    igraph_integer_t graph_size=igraph_vcount(graph);  //number of vertices of graph
//    printf("here is graph_size : %d\n",graph_size);
    igraph_rng_seed(igraph_rng_default(),clock());
    long int firstNode=igraph_rng_get_integer(igraph_rng_default(), -1, graph_size);
//    printf("here is first node : %ld\n",firstNode);
    return RandWalk(graph,graph_size*10,firstNode);   //set for Stationary process
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
 
    srand((unsigned)time(NULL));
    
    sfmt_t sfmtSeed ;
	sfmt_init_gen_rand(&sfmtSeed, time(NULL));
    if (argc <3){
        printf("The pramament of the procedure is like ./SSRW6C which_file_you_want_to_test times_you_want_to_walk\n");
        exit(1);
    }
    
    char* filename = argv[1];
    long int given_time = atol(argv[2]);
    FILE *instream = fopen(filename,"r");
    if(!instream){
        string msg="Open file fail!:";
        msg.append(filename);
        throw runtime_error(msg);
    }
    igraph_t G;
    igraph_read_graph_ncol(&G,instream,NULL,0,IGRAPH_ADD_WEIGHTS_NO,IGRAPH_UNDIRECTED);
    long int startid=RandStart(&G);
//    cout << startid <<endl;
    long int count[MAXSUBS];    //count times all subgraph may appear
    long int run_times=0;
    igraph_t graph[MAXSUBS];
    igraph_small(&graph[0],6,IGRAPH_UNDIRECTED,0,5,1,5,2,5,3,5,4,5,-1);
    igraph_small(&graph[1],6,IGRAPH_UNDIRECTED,0,4,0,5,1,5,2,5,3,5,-1);
    igraph_small(&graph[2],6,IGRAPH_UNDIRECTED,0,4,0,5,1,5,2,5,3,5,4,5,-1);
    igraph_small(&graph[3],6,IGRAPH_UNDIRECTED,0,4,0,5,1,4,2,5,3,5,-1);
    igraph_small(&graph[4],6,IGRAPH_UNDIRECTED,0,4,1,4,2,5,3,5,4,5,-1);
    igraph_small(&graph[5],6,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,5,2,5,3,5,-1);
    igraph_small(&graph[6],6,IGRAPH_UNDIRECTED,0,4,0,5,1,4,2,5,3,5,4,5,-1);
    igraph_small(&graph[7],6,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,5,2,5,3,5,4,5,-1);
    igraph_small(&graph[8],6,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,5,2,4,3,5,-1);
    igraph_small(&graph[9],6,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,5,2,4,2,5,3,5,-1);
    igraph_small(&graph[10],6,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,5,2,4,3,5,4,5,-1);
    igraph_small(&graph[11],6,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,5,2,4,2,5,3,5,4,5,-1);
    igraph_small(&graph[12],6,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,5,2,4,2,5,3,4,3,5,-1);
    igraph_small(&graph[13],6,IGRAPH_UNDIRECTED,0,4,0,5,1,4,1,5,2,4,2,5,3,4,3,5,4,5,-1);
    igraph_small(&graph[14],6,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,2,5,-1);
    igraph_small(&graph[15],6,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,2,5,3,5,-1);
    igraph_small(&graph[16],6,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,2,5,3,5,4,5,-1);
    igraph_small(&graph[17],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,2,5,-1);
    igraph_small(&graph[18],6,IGRAPH_UNDIRECTED,0,3,0,4,1,4,1,5,2,5,3,5,-1);
    igraph_small(&graph[19],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,2,5,4,5,-1);
    igraph_small(&graph[20],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,2,5,3,5,-1);
    igraph_small(&graph[21],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,2,5,4,5,-1);
    igraph_small(&graph[22],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,2,5,3,5,4,5,-1);
    igraph_small(&graph[23],6,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,2,4,-1);
    igraph_small(&graph[24],6,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,2,4,2,5,-1);
    igraph_small(&graph[25],6,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,2,4,3,5,-1);
    igraph_small(&graph[26],6,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,2,4,4,5,-1);
    igraph_small(&graph[27],6,IGRAPH_UNDIRECTED,0,3,0,5,1,4,2,4,3,5,4,5,-1);
    igraph_small(&graph[28],6,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,2,4,2,5,3,5,-1);
    igraph_small(&graph[29],6,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,2,4,2,5,4,5,-1);
    igraph_small(&graph[30],6,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,2,4,3,5,4,5,-1);
    igraph_small(&graph[31],6,IGRAPH_UNDIRECTED,0,3,0,5,1,4,1,5,2,4,2,5,3,5,4,5,-1);
    igraph_small(&graph[32],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,5,2,5,3,4,3,5,-1);
    igraph_small(&graph[33],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,5,2,5,3,4,3,5,4,5,-1);
    igraph_small(&graph[34],6,IGRAPH_UNDIRECTED,0,3,0,4,1,4,1,5,2,4,2,5,3,5,-1);
    igraph_small(&graph[35],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,2,4,2,5,3,5,-1);
    igraph_small(&graph[36],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,2,4,2,5,4,5,-1);
    igraph_small(&graph[37],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,2,4,3,5,4,5,-1);
    igraph_small(&graph[38],6,IGRAPH_UNDIRECTED,0,3,0,4,1,4,1,5,2,4,2,5,3,5,4,5,-1);
    igraph_small(&graph[39],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,2,4,2,5,3,5,4,5,-1);
    igraph_small(&graph[40],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,2,5,3,4,3,5,-1);
    igraph_small(&graph[41],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,2,5,3,4,3,5,4,5,-1);
    igraph_small(&graph[42],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,2,5,3,4,3,5,4,5,-1);
    igraph_small(&graph[43],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,2,4,2,5,3,4,3,5,-1);
    igraph_small(&graph[44],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,4,1,5,2,4,2,5,3,4,3,5,4,5,-1);
    igraph_small(&graph[45],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,4,1,5,2,5,-1);
    igraph_small(&graph[46],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,4,1,5,2,5,3,5,-1);
    igraph_small(&graph[47],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,4,1,5,2,5,3,5,4,5,-1);
    igraph_small(&graph[48],6,IGRAPH_UNDIRECTED,0,3,0,4,1,3,1,5,2,4,2,5,-1);
    igraph_small(&graph[49],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,5,2,4,2,5,-1);
    igraph_small(&graph[50],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,2,4,2,5,3,5,-1);
    igraph_small(&graph[51],6,IGRAPH_UNDIRECTED,0,3,0,4,1,3,1,5,2,4,2,5,3,5,-1);
    igraph_small(&graph[52],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,2,4,3,5,4,5,-1);
    igraph_small(&graph[53],6,IGRAPH_UNDIRECTED,0,3,0,4,1,3,1,5,2,4,3,5,4,5,-1);
    igraph_small(&graph[54],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,5,2,4,2,5,3,5,-1);
    igraph_small(&graph[55],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,5,2,4,3,5,4,5,-1);
    igraph_small(&graph[56],6,IGRAPH_UNDIRECTED,0,3,0,4,1,3,1,5,2,4,2,5,3,5,4,5,-1);
    igraph_small(&graph[57],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,5,2,4,2,5,3,5,4,5,-1);
    igraph_small(&graph[58],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,4,1,5,2,4,2,5,-1);
    igraph_small(&graph[59],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,4,1,5,2,4,3,5,-1);
    igraph_small(&graph[60],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,4,1,5,2,4,2,5,3,5,-1);
    igraph_small(&graph[61],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,4,1,5,2,4,2,5,4,5,-1);
    igraph_small(&graph[62],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,4,1,5,2,4,2,5,3,5,4,5,-1);
    igraph_small(&graph[63],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,4,1,5,2,5,3,4,3,5,-1);
    igraph_small(&graph[64],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,4,2,5,3,4,3,5,4,5,-1);
    igraph_small(&graph[65],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,4,1,5,2,5,3,4,3,5,4,5,-1);
    igraph_small(&graph[66],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,5,2,4,2,5,3,4,3,5,-1);
    igraph_small(&graph[67],6,IGRAPH_UNDIRECTED,0,3,0,4,1,3,1,5,2,4,2,5,3,4,3,5,4,5,-1);
    igraph_small(&graph[68],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,5,2,4,2,5,3,4,3,5,4,5,-1);
    igraph_small(&graph[69],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,4,1,5,2,4,2,5,3,4,3,5,4,5,-1);
    igraph_small(&graph[70],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,4,1,5,2,3,2,4,2,5,-1);
    igraph_small(&graph[71],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,4,1,5,2,3,2,4,2,5,3,5,-1);
    igraph_small(&graph[72],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,4,1,5,2,3,2,4,3,5,4,5,-1);
    igraph_small(&graph[73],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,4,1,5,2,3,2,4,2,5,3,5,4,5,-1);
    igraph_small(&graph[74],6,IGRAPH_UNDIRECTED,0,3,0,4,0,5,1,3,1,4,1,5,2,3,2,4,2,5,3,4,3,5,4,5,-1);
    igraph_small(&graph[75],6,IGRAPH_UNDIRECTED,0,2,0,4,0,5,1,3,1,5,2,4,2,5,-1);
    igraph_small(&graph[76],6,IGRAPH_UNDIRECTED,0,2,0,4,0,5,1,3,1,5,2,4,3,5,-1);
    igraph_small(&graph[77],6,IGRAPH_UNDIRECTED,0,2,0,4,0,5,1,3,1,5,2,4,2,5,3,5,-1);
    igraph_small(&graph[78],6,IGRAPH_UNDIRECTED,0,2,0,4,0,5,1,3,1,5,2,4,2,5,4,5,-1);
    igraph_small(&graph[79],6,IGRAPH_UNDIRECTED,0,2,0,4,0,5,1,3,1,5,2,4,2,5,3,5,4,5,-1);
    igraph_small(&graph[80],6,IGRAPH_UNDIRECTED,0,2,0,4,0,5,1,3,1,4,1,5,2,4,3,5,-1);
    igraph_small(&graph[81],6,IGRAPH_UNDIRECTED,0,2,0,4,0,5,1,3,1,4,1,5,2,4,2,5,3,5,-1);
    igraph_small(&graph[82],6,IGRAPH_UNDIRECTED,0,2,0,4,0,5,1,3,1,4,1,5,2,4,2,5,4,5,-1);
    igraph_small(&graph[83],6,IGRAPH_UNDIRECTED,0,2,0,4,0,5,1,3,1,4,1,5,2,4,3,5,4,5,-1);
    igraph_small(&graph[84],6,IGRAPH_UNDIRECTED,0,2,0,4,0,5,1,3,1,4,2,4,2,5,3,5,4,5,-1);
    igraph_small(&graph[85],6,IGRAPH_UNDIRECTED,0,2,0,4,0,5,1,3,1,4,1,5,2,4,2,5,3,5,4,5,-1);
    igraph_small(&graph[86],6,IGRAPH_UNDIRECTED,0,2,0,4,0,5,1,3,1,4,1,5,2,4,2,5,3,4,3,5,-1);
    igraph_small(&graph[87],6,IGRAPH_UNDIRECTED,0,2,0,4,0,5,1,3,1,4,1,5,2,4,2,5,3,4,3,5,4,5,-1);
    igraph_small(&graph[88],6,IGRAPH_UNDIRECTED,0,2,0,3,0,5,1,3,1,4,1,5,2,4,2,5,-1);
    igraph_small(&graph[89],6,IGRAPH_UNDIRECTED,0,2,0,3,0,5,1,3,1,4,1,5,2,4,3,5,-1);
    igraph_small(&graph[90],6,IGRAPH_UNDIRECTED,0,2,0,3,0,5,1,3,1,4,1,5,2,4,2,5,3,5,-1);
    igraph_small(&graph[91],6,IGRAPH_UNDIRECTED,0,2,0,3,0,5,1,3,1,4,1,5,2,4,2,5,3,5,4,5,-1);
    igraph_small(&graph[92],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,1,3,1,4,1,5,2,4,2,5,3,5,-1);
    igraph_small(&graph[93],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,3,1,4,1,5,2,4,2,5,3,5,-1);
    igraph_small(&graph[94],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,3,1,4,1,5,2,4,3,5,4,5,-1);
    igraph_small(&graph[95],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,3,1,4,1,5,2,4,2,5,3,5,4,5,-1);
    igraph_small(&graph[96],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,3,1,4,1,5,2,4,2,5,3,4,3,5,4,5,-1);
    igraph_small(&graph[97],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,4,1,5,2,3,2,4,2,5,3,5,-1);
    igraph_small(&graph[98],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,4,1,5,2,3,2,4,2,5,4,5,-1);
    igraph_small(&graph[99],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,4,1,5,2,3,2,4,2,5,3,5,4,5,-1);
    igraph_small(&graph[100],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,5,2,3,2,4,2,5,3,4,3,5,-1);
    igraph_small(&graph[101],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,5,2,3,2,4,2,5,3,4,3,5,4,5,-1);
    igraph_small(&graph[102],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,4,1,5,2,3,2,4,2,5,3,4,3,5,4,5,-1);
    igraph_small(&graph[103],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,3,1,4,1,5,2,3,2,4,2,5,3,4,3,5,4,5,-1);
    igraph_small(&graph[104],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,2,1,3,1,4,1,5,2,4,2,5,3,5,-1);
    igraph_small(&graph[105],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,2,1,3,1,4,1,5,2,4,2,5,4,5,-1);
    igraph_small(&graph[106],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,2,1,3,1,4,2,4,2,5,3,5,4,5,-1);
    igraph_small(&graph[107],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,2,1,3,1,4,1,5,2,4,2,5,3,5,4,5,-1);
    igraph_small(&graph[108],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,2,1,3,1,4,1,5,2,4,2,5,3,4,3,5,-1);
    igraph_small(&graph[109],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,2,1,3,1,4,1,5,2,4,2,5,3,4,3,5,4,5,-1);
    igraph_small(&graph[110],6,IGRAPH_UNDIRECTED,0,2,0,3,0,4,0,5,1,2,1,3,1,4,1,5,2,3,2,4,2,5,3,4,3,5,4,5,-1);
    igraph_small(&graph[111],6,IGRAPH_UNDIRECTED,0,1,0,2,0,3,0,4,0,5,1,2,1,3,1,4,1,5,2,3,2,4,2,5,3,4,3,5,4,5,-1);
    //for(int i=0;i<MAXSUBNAME;++i)
    //    igraph_write_graph_edgelist(&graph[i],stdout);
    int W_constant[]={120,42,204,10,32,104,84,340,40,216,188,600,576,1344,12,66,336,58,36,36,186,134,552,2,28,14,24,52,160,104,132,548,188,528,120,412,296,358,420,1024,356,264,892,912,1984,144,320,872,12,120,88,80,68,112,308,230,340,904,352,232,726,704,1656,610,580,1364,756,792,1640,3012,792,1452,1504,2892,5112,52,80,292,156,840,256,672,440,658,608,1520,1440,2928,280,204,596,1500,612,1354,1356,2684,4660,1274,1272,2596,978,2016,4428,7464,2548,2352,2448,4452,4368,7328,11520,17280};
    for(int i=0;i<MAXSUBS;++i)
        count[i]=0;
    igraph_vector_t vtmp=IGRAPH_VECTOR_NULL;
    start = clock();
    for(;run_times<given_time;++run_times){
//        cout << " count subgraph time  : " << run_times <<endl;
        long int node[6],user[6];
        node[0]=startid;
        igraph_vector_t nodeneigh[5];
        for(int j=0;j<5;j++)
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
//        for(int k=0;k<5;k++)
//            print_vector(&nodeneigh[k],stdout);
//        for (int j=0;j<6;j++){
//            cout << node[j] <<endl;
//        }
        igraph_t subgraph;
        igraph_vs_t vids;
        igraph_vs_vector_small(&vids, node[0],node[1],node[2],node[3],node[4],node[5],-1);
        igraph_induced_subgraph(&G,&subgraph,vids,IGRAPH_SUBGRAPH_CREATE_FROM_SCRATCH);
        igraph_integer_t subgraph_size;  //number of vertices of graph
        igraph_vs_all(&vids);
        igraph_vs_size(&subgraph,&vids,&subgraph_size);
//        cout << "subgraphsize: " <<subgraph_size<<endl;
        if(subgraph_size<6) continue;
        else{
            igraph_bool_t ios=0;
            for(int i=0;(i<MAXSUBS)&&!ios;++i){
                igraph_isomorphic(&subgraph,&graph[i],&ios);
//                cout << "iso result : " << ios <<endl;
                if(ios){
                    igraph_vector_t degree;
                    igraph_vector_init(&degree,6);
                    igraph_vs_t vids_vs;
                    igraph_vs_vector_small(&vids_vs,node[0],node[1],node[2],node[3],node[4],node[5],-1);
                    igraph_degree(&G,&degree,vids_vs,IGRAPH_ALL,0);
                    long int dg_prod=VECTOR(degree)[1]*(VECTOR(degree)[1]+VECTOR(degree)[2])*(VECTOR(degree)[1]+VECTOR(degree)[2]+VECTOR(degree)[3])*(VECTOR(degree)[1]+VECTOR(degree)[2]+VECTOR(degree)[3]+VECTOR(degree)[4]);
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

    
    char* filename = argv[1];
    const char *delim = ".";
	char *fileNosuffix=strtok(filename,delim);
	string s=fileNosuffix;
	s = s + ".ssrw6result";
	ofstream out(s);
    for(int i=0;i>MAXSUBS;++i){
        out << i << " "<<ans[i]<<endl;
    }
    return 0;
} 