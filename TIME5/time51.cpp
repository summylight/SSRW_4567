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
#define MAXSUBS 21  //5-subgraph count
#define NEXTJUMP 0 //Set for once random walk jump distance
#define MAXTIME 100000
using namespace std;

long int RandStart(igraph_t *graph);
long int RandWalk(igraph_t *graph, int steps, long int startNode);
long int START_JUMP=0;

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
    START_JUMP=graph_size*10;
//    printf("here is graph_size : %d\n",graph_size);
    igraph_rng_seed(igraph_rng_default(),clock());
    long int firstNode=igraph_rng_get_integer(igraph_rng_default(), -1, graph_size);
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
 * \param argv[0] ./SSRW5C
 * \param argv[1] the input graphfile ,NOTICE that file must like vertice one ,vertice two
 * \input graph should be an undirected graph , connected and contain no ring 
 * \param argv[2] the times you want to run the randwalk ,the more you run, the rusult may be more accurate
 * */

int main(int argc, char* argv[]){
    double dur1,dur2,dur0;
    clock_t rs0,re0,start1,end1,start2,end2,start0,end0;

    srand((unsigned)time(NULL));
    sfmt_t sfmtSeed ;
	sfmt_init_gen_rand(&sfmtSeed, time(NULL));
    if (argc <3){
        printf("The pramament of the procedure is like ./time5 which_file_you_want_to_test times_you_want_to_walk\n");
        exit(1);
    }

    char* filename = argv[1];
    FILE *instream = fopen(filename,"r");
    
    long int given_time = atol(argv[2]);
    if(!instream){
        string msg="Open file fail!:";
        msg.append(filename);
        throw runtime_error(msg);
    }

    igraph_t G;
    igraph_read_graph_ncol(&G,instream,NULL,0,IGRAPH_ADD_WEIGHTS_NO,IGRAPH_UNDIRECTED);
    rs0=clock();
    long int startid=RandStart(&G);
    re0=clock();
    dur0=re0-rs0;
    printf("Start JUMP %ld Use Time:%fs\n",START_JUMP,(dur0/CLOCKS_PER_SEC));  //count time
//    cout << startid <<endl;
    long int count[MAXSUBS];    //count times all subgraph may appear


    igraph_t graph[MAXSUBS];    //graph array store all unique subgraphs
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
    int W_constant[]={24,8,40,20,18,68,60,156,2,12,64,10,46,124,40,108,244,108,232,432,720};
    for(int i=0;i<MAXSUBS;++i)
        count[i]=0;
    
    vector<igraph_t> subgraphs;  //store all allowed subgraphs
    vector<vector<long int> > nodes;    //store the vertices correspond to subgraph
    vector<long int> node(5),user(5);
    igraph_vector_t nodeneigh[4];
    long int run_times;
    long int repeat=given_time/MAXTIME;
    long int onetimes;
    start0=clock();
    for(int k=0;k<=repeat;k++){
        onetimes=(k==repeat)?given_time%MAXTIME:MAXTIME;    //split store space
        start1 = clock();
        for(run_times=0;run_times<onetimes;++run_times){
            node[0]=startid;
            for(int j=0;j<4;j++)
                igraph_vector_init(&nodeneigh[j],1);

            igraph_neighbors(&G,&nodeneigh[0],node[0],IGRAPH_ALL);
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

//            for(int k=0;k<5;k++)
//                print_vector(&nodeneigh[k],stdout);
//            for (int j=0;j<6;j++){
//                cout << node[j] <<endl;
//            }
            igraph_t subgraph;
            igraph_vs_t vids;
            igraph_vs_vector_small(&vids, node[0],node[1],node[2],node[3],node[4],-1);
            igraph_induced_subgraph(&G,&subgraph,vids,IGRAPH_SUBGRAPH_CREATE_FROM_SCRATCH);
//            cout << "subgraphsize: " <<subgraph_size<<endl;
            if(igraph_vcount(&subgraph)<5) continue;
            else{
                subgraphs.push_back(subgraph);
                nodes.push_back(node);
            }
            startid=RandWalk(&G,NEXTJUMP,node[4]);
//            printf("next startnode: %ld",startid);
        }
        printf("Now we get %ld allowed sample from %ld samples\n",subgraphs.size(),given_time);
        end1 = clock();
        dur1 += (double)(end1 - start1);

        start2 = clock();
        while(!subgraphs.empty()){
            igraph_bool_t ios=0;
            igraph_t subgraph = subgraphs.back();
            vector<long int> node = nodes.back();
            subgraphs.pop_back();
            nodes.pop_back();
            for(int i=0 ; (i<MAXSUBS) && !ios ; ++i ){
                igraph_isomorphic(&subgraph,&graph[i],&ios);
//                   cout << "iso result : " << ios <<endl;
                if(ios){
                    igraph_vector_t degree;
                    igraph_vector_init(&degree,5);
                    igraph_vs_t vids_vs;
                    igraph_vs_vector_small(&vids_vs,node[0],node[1],node[2],node[3],node[4],-1);
                    igraph_degree(&G,&degree,vids_vs,IGRAPH_ALL,0);
                    long int dg_prod=VECTOR(degree)[1]*(VECTOR(degree)[1]+VECTOR(degree)[2])*(VECTOR(degree)[1]+VECTOR(degree)[2]+VECTOR(degree)[3]);
                    count[i]=count[i]+dg_prod;   //count isomorphic subgraph
//                       cout << "find the subgraph: " << i << endl;
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
        }
        end2 = clock();
        dur2 += (double)(end2 - start2);
    }
    end0=clock();
    printf("Random walk Use Time:%fs\n",(dur1/CLOCKS_PER_SEC));  //count time
    printf("Calculate isomorphic Use Time:%fs\n",(dur2/CLOCKS_PER_SEC));  //count time       
    dur1 = (double)(end0 - start0);
    printf("ALL program Use Time:%fs\n",(dur1/CLOCKS_PER_SEC));  //count time   


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
    copy(ans,ans+MAXSUBS,sorted);
    sort(sorted,sorted+MAXSUBS);
    for(int i=MAXSUBS-1;i>MAXSUBS-15;--i){
        int exposition;
        bool flag=0;
        for(exposition=0;(exposition<MAXSUBS)&&!flag;exposition++)
            if(sorted[i]==ans[exposition]) flag=1;
        printf("SubGraph[%d] account for %Lf \n",exposition,sorted[i]);
    }


    const char *delim = ".";
	char *fileNosuffix=strtok(filename,delim);
	string s=fileNosuffix;
	s = s + ".time5result";
	ofstream out(s);
    for(int i=0;i>MAXSUBS;++i){
        out << i << " "<<ans[i]<<endl;
    }
    return 0;
} 