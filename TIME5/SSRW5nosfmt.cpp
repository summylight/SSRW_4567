#include<igraph.h>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<vector>
#include<time.h>
#include<random>
#include<set>
#define MAXSUBS 21  //5-subgraph count
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
    long int START_JUMP;
    igraph_integer_t graph_size=igraph_vcount(graph);  //number of vertices of graph
    START_JUMP=graph_size*10;
//    printf("here is graph_size : %d\n",graph_size);
    random_device r;
    mt19937_64 prng(r());
    uniform_int_distribution<long int> uniform_dist(0,graph_size-1);
    long int firstNode=uniform_dist(prng);
//    printf("here is first node : %ld\n",firstNode);
    return RandWalk(graph,START_JUMP,firstNode);   //!graph_size*10 set for Stationary process
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
    random_device r;
    mt19937_64 prng(r());
    for (int i=0;i<steps;++i){
        igraph_neighbors(graph,&v,nextNode,IGRAPH_ALL); 
//        print_vector(&v, stdout);
        uniform_int_distribution<int> unif(0,igraph_vector_size(&v)-1);
        long int next = unif(prng);
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
 * \param argv[1] the input graphfile ,NOTICE that file must like vertice one ,vertice two \
 * \input graph should be an undirected graph , connected and contain no ring 
 * \param argv[2] the times you want to run the randwalk ,the more you run, the rusult may be more accurate
 * */

int main(int argc, char* argv[]){
    double dur;
    clock_t start,end;
 
    if (argc <3){
        printf("The pramament of the procedure is like ./SSRW5C which_file_you_want_to_test times_you_want_to_walk\n");
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
    igraph_small(&graph[0],5,IGRAPH_UNDIRECTED,0,4,1,4,2,4,3,4,-1);
    igraph_small(&graph[1],5,IGRAPH_UNDIRECTED,0,3,0,4,1,4,2,4,-1);
    igraph_small(&graph[2],5,IGRAPH_UNDIRECTED,0,3,0,4,1,4,2,4,3,4,-1);
    igraph_small(&graph[3],5,IGRAPH_UNDIRECTED,0,3,0,4,1,3,1,4,2,4,-1);
    igraph_small(&graph[4],5,IGRAPH_UNDIRECTED,0,3,0,4,1,3,2,4,3,4,-1);
    igraph_small(&graph[5],5,IGRAPH_UNDIRECTED,0,3,0,4,1,3,1,4,2,4,3,4,-1);
    igraph_small(&graph[6],5,IGRAPH_UNDIRECTED,0,3,0,4,1,3,1,4,2,3,2,4,-1);
    igraph_small(&graph[7],5,IGRAPH_UNDIRECTED,0,3,0,4,1,3,1,4,2,3,2,4,3,4,-1);
    igraph_small(&graph[8],5,IGRAPH_UNDIRECTED,0,2,0,4,1,3,1,4,-1);
    igraph_small(&graph[9],5,IGRAPH_UNDIRECTED,0,2,0,4,1,3,1,4,2,4,-1);
    igraph_small(&graph[10],5,IGRAPH_UNDIRECTED,0,2,0,4,1,3,1,4,2,4,3,4,-1);
    igraph_small(&graph[11],5,IGRAPH_UNDIRECTED,0,2,0,3,1,3,1,4,2,4,-1);
    igraph_small(&graph[12],5,IGRAPH_UNDIRECTED,0,2,0,3,0,4,1,3,1,4,2,4,-1);
    igraph_small(&graph[13],5,IGRAPH_UNDIRECTED,0,2,0,3,0,4,1,3,1,4,2,4,3,4,-1);
    igraph_small(&graph[14],5,IGRAPH_UNDIRECTED,0,2,0,3,0,4,1,4,2,3,2,4,-1);
    igraph_small(&graph[15],5,IGRAPH_UNDIRECTED,0,2,0,3,0,4,1,4,2,3,2,4,3,4,-1);
    igraph_small(&graph[16],5,IGRAPH_UNDIRECTED,0,2,0,3,0,4,1,3,1,4,2,3,2,4,3,4,-1);
    igraph_small(&graph[17],5,IGRAPH_UNDIRECTED,0,2,0,3,0,4,1,2,1,3,1,4,2,4,-1);
    igraph_small(&graph[18],5,IGRAPH_UNDIRECTED,0,2,0,3,0,4,1,2,1,3,1,4,2,4,3,4,-1);
    igraph_small(&graph[19],5,IGRAPH_UNDIRECTED,0,2,0,3,0,4,1,2,1,3,1,4,2,3,2,4,3,4,-1);
    igraph_small(&graph[20],5,IGRAPH_UNDIRECTED,0,1,0,2,0,3,0,4,1,2,1,3,1,4,2,3,2,4,3,4,-1);
    //for(int i=0;i<MAXSUBNAME;++i)
    //    igraph_write_graph_edgelist(&graph[i],stdout);
    int W_constant[]={24,8,40,20,18,68,60,156,2,12,64,10,46,124,40,108,244,108,232,432,720};
    for(int i=0;i<MAXSUBS;++i)
        count[i]=0;
    start = clock();
    vector<long int> node(5),user(5);
    igraph_vector_t nodeneigh[4];
    for(int j=0;j<4;j++)
        igraph_vector_init(&nodeneigh[j],0);
    long int countsubs=0;
    random_device r;
    mt19937_64 prng;
    for(;run_times<given_time;++run_times){
//        cout << " count subgraph time  : " << run_times <<endl;
        prng.seed(r());
        uniform_int_distribution<long int> uniform_dist;
        node[0]=startid;

        igraph_neighbors(&G,&nodeneigh[0],node[0],IGRAPH_ALL);
        user[1] = uniform_dist(prng)%igraph_vector_size(&nodeneigh[0]);
        node[1] = VECTOR(nodeneigh[0])[user[1]];
        igraph_neighbors(&G,&nodeneigh[1],node[1],IGRAPH_ALL);
//           print_vector(&nodeneigh[1]);
        user[2] = uniform_dist(prng)%igraph_vector_size(&nodeneigh[1]);
        node[2] = VECTOR(nodeneigh[1])[user[2]];
        igraph_neighbors(&G,&nodeneigh[2],node[2],IGRAPH_ALL);
        igraph_vector_append(&nodeneigh[1],&nodeneigh[2]);
//           print_vector(&nodeneigh[1]);
        user[3] = uniform_dist(prng)%igraph_vector_size(&nodeneigh[1]);
        node[3] = VECTOR(nodeneigh[1])[user[3]];
        igraph_neighbors(&G,&nodeneigh[3],node[3],IGRAPH_ALL);
        igraph_vector_append(&nodeneigh[1],&nodeneigh[3]);
//           print_vector(&nodeneigh[1]);
        user[4] = uniform_dist(prng)%igraph_vector_size(&nodeneigh[1]);
        node[4] = VECTOR(nodeneigh[1])[user[4]];
//        for(int k=0;k<5;k++)
//            print_vector(&nodeneigh[k],stdout);
//        for (int j=0;j<6;j++){
//            cout << node[j] <<endl;
//        }
        set<long int> it(node.begin(),node.end());
        if(it.size()==5) {
            igraph_t subgraph;
            igraph_vs_t vids;
            igraph_vs_vector_small(&vids, node[0],node[1],node[2],node[3],node[4],-1);
            igraph_induced_subgraph(&G,&subgraph,vids,IGRAPH_SUBGRAPH_CREATE_FROM_SCRATCH);
//        cout << "subgraphsize: " <<subgraph_size<<endl;
            igraph_bool_t ios=0;
                for(int i=0;(i<MAXSUBS)&&!ios;++i){
                    igraph_isomorphic(&subgraph,&graph[i],&ios);
    //                cout << "iso result : " << ios <<endl;
                    if(ios){
                        igraph_vector_t degree;
                        igraph_vector_init(&degree,5);
                        igraph_vs_t vids_vs;
                        igraph_vs_vector_small(&vids_vs,node[0],node[1],node[2],node[3],node[4],-1);
                        igraph_degree(&G,&degree,vids_vs,IGRAPH_ALL,0);
                        long int dg_prod=VECTOR(degree)[1]*(VECTOR(degree)[1]+VECTOR(degree)[2])*(VECTOR(degree)[1]+VECTOR(degree)[2]+VECTOR(degree)[3]);
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
                igraph_destroy(&subgraph);
            }
        startid=RandWalk(&G,NEXTJUMP,node[0]);
//        printf("next startnode: %ld",startid);
    }
    end = clock();
    dur = (double)(end - start);
    printf("Use Time:%f\n",(dur/CLOCKS_PER_SEC));  //count time

    int count0=0;
    for(int i=0;i<MAXSUBS;++i)
        if(count[i]==0) {count0++;
//        cout << "No found subgraph : "<<i<<endl;
    }
    cout  << "0Subgraph counts " << count0 << endl;
//  sort occurrence probability of all subgraph and print most frequent subgraph serial number 
    long double ans[MAXSUBS];
    for(int i=0;i<MAXSUBS;++i)
        ans[i]=(count[i]*igraph_ecount(&G)*2/W_constant[i])/given_time;
    long double sorted[MAXSUBS];
    for(int i=0;i<MAXSUBS;++i)
        sorted[i]=ans[i];
    sort(sorted,sorted+MAXSUBS);
    for(int i=MAXSUBS-1;i>=0;--i){
        int exposition;
        bool flag=0;
        for(exposition=0;(exposition<MAXSUBS)&&!flag;exposition++)
            if(sorted[i]==ans[exposition]) flag=1;
        printf("SubGraph[%d] account for %Lf \n",exposition,sorted[i]);
    }

    const char *delim = ".";
	char *fileNosuffix=strtok(filename,delim);
	string s=fileNosuffix;
	s = s + ".ssrw5result";
	ofstream out(s);
    for(int i=0;i<MAXSUBS;++i){
        out << i << " "<<ans[i]<<endl;
    }
    out.close();
    return 0;
} 