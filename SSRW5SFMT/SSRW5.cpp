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
#include<set>
#define MAXSUBS 21  //5-subgraph count
#define NEXTJUMP 0 //Set for once random walk jump distance
using namespace std;
long int RandWalk(igraph_t *graph, long int steps, long int startNode);;
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
inline long int RandStart(igraph_t *graph){
    long int graph_size=igraph_vcount(graph);  //number of vertices of graph
//    printf("here is graph_size : %d\n",graph_size);
    igraph_rng_seed(igraph_rng_default(),clock());
    long int firstNode=igraph_rng_get_integer(igraph_rng_default(), -1, graph_size);
//    printf("here is first node : %ld\n",firstNode);
    return RandWalk(graph,graph_size,firstNode);   //!graph_size*10 set for Stationary process
}

/**
 * \function RandWalk
 * Perform a randwalk on one given node
 * 
 * \param graph the input graph
 * \param steps the random walk will run
 * \param startNode random walk startNode
 * */
inline long int RandWalk(igraph_t *graph, long int steps, long int startNode){
    igraph_vector_t v;
    igraph_vector_init(&v,0);
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
 * \param argv[1] the input graphfile ,NOTICE that file must like vertice one ,vertice two \
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
    long long count[MAXSUBS];    //count times all subgraph may appear
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
    vector<long int> node(5),user(5),degree(3);
    igraph_vector_t nodeneigh[4];
    for(int j=0;j<4;j++)
        igraph_vector_init(&nodeneigh[j],0);
    for(;run_times<given_time;++run_times){
//        cout << " count subgraph time  : " << run_times <<endl;
        node[0]=startid;

        igraph_neighbors(&G,&nodeneigh[0],node[0],IGRAPH_ALL);
 //       print_vector(&nodeneigh[0], stdout);
        user[1] = sfmt_genrand_uint32(&sfmtSeed)%igraph_vector_size(&nodeneigh[0]);
        node[1] = VECTOR(nodeneigh[0])[user[1]];

        igraph_neighbors(&G,&nodeneigh[1],node[1],IGRAPH_ALL);
        degree[0]=igraph_vector_size(&nodeneigh[1]);
        user[2] = sfmt_genrand_uint32(&sfmtSeed)%degree[0];
        node[2] = VECTOR(nodeneigh[1])[user[2]];

        igraph_neighbors(&G,&nodeneigh[2],node[2],IGRAPH_ALL);
        igraph_vector_append(&nodeneigh[1],&nodeneigh[2]);
        degree[1]=igraph_vector_size(&nodeneigh[1]);
        user[3] = sfmt_genrand_uint32(&sfmtSeed)%degree[1];
        node[3] = VECTOR(nodeneigh[1])[user[3]];

        igraph_neighbors(&G,&nodeneigh[3],node[3],IGRAPH_ALL);
        igraph_vector_append(&nodeneigh[1],&nodeneigh[3]);
        degree[2]=igraph_vector_size(&nodeneigh[1]);
        user[4] = sfmt_genrand_uint32(&sfmtSeed)%degree[2];
        node[4] = VECTOR(nodeneigh[1])[user[4]];

//        for(int k=0;k<5;k++)
//            print_vector(&nodeneigh[k],stdout);
//        for (int j=0;j<6;j++){
//            cout << node[j] <<endl;
//        }
        
//        cout << "subgraphsize: " <<subgraph_size<<endl;
        set<long int> it(node.begin(),node.end());
        if(it.size()==5){
            igraph_t subgraph;
            igraph_vs_t vids;
            igraph_vs_vector_small(&vids, node[0],node[1],node[2],node[3],node[4],-1);
            igraph_induced_subgraph(&G,&subgraph,vids,IGRAPH_SUBGRAPH_CREATE_FROM_SCRATCH);
            igraph_bool_t ios=0;
            for(int i=0;(i<MAXSUBS)&&!ios;++i){
                igraph_isomorphic(&subgraph,&graph[i],&ios);
//                cout << "iso result : " << ios <<endl;
                if(ios){
                    long long dg_prod=degree[0]*degree[1]*degree[2];
                    count[i]=count[i]+dg_prod;   //count isomorphic subgraph
//                    cout << "find the subgraph: " << i << endl;
                    break;
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
            igraph_vs_destroy(&vids);
        }
        startid=RandWalk(&G,NEXTJUMP,node[1]);
//        printf("next startnode: %ld",startid);
    }
    end = clock();
    dur = (double)(end - start);
    printf("Use Time:%f\n",(dur/CLOCKS_PER_SEC));  //count time

    
//  sort occurrence probability of all subgraph and print most frequent subgraph serial number 
    long long ans[MAXSUBS];
    for(int i=0;i<MAXSUBS;++i)
        ans[i]=((count[i]/W_constant[i])/given_time)*igraph_ecount(&G)*2;
    int count0=0;
    for(int i=0;i<MAXSUBS;++i)
        if(ans[i]==0) {count0++;
//        cout << "No found subgraph : "<<i<<endl;
    }
    cout  << "0Subgraph counts " << count0 << endl;
    long long  sorted[MAXSUBS];
    for(int i=0;i<MAXSUBS;++i)
        sorted[i]=ans[i];
    sort(sorted,sorted+MAXSUBS);
    for(int i=MAXSUBS-1;i>=0;--i){
        int exposition;
        bool flag=0;
        for(exposition=0;(exposition<MAXSUBS)&&!flag;exposition++)
            if(sorted[i]==ans[exposition]) flag=1;
        printf("SubGraph[%d] account for %Ld \n",exposition,sorted[i]);
    }

    const char *delim = ".";
	char *fileNosuffix=strtok(filename,delim);
	string s=fileNosuffix;
	s = s + ".ssrw5million0";
    cout << "Now writing to " << s <<endl;
	ofstream out(s,std::ios_base::app);
    for(int i=0;i<MAXSUBS;++i){
        out << i << " "<<ans[i]<<endl;
    }
    out << dur<<endl;
    out.close();
    return 0;
} 