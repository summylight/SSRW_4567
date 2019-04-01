#include<igraph.h>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<vector>
#include<sys/time.h>
#include<set>
#include<random>
#include "SFMT/SFMT.h"
#define MAXSUBS 21  //5-subgraph count
//Set for once random walk jump distance
using namespace std;
sfmt_t sfmtSeed;

long int RandStart(igraph_t *graph);
long int RandWalk(igraph_t *graph, long int steps, long int startNode);
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
    /*
    long int  graph_size=igraph_vcount(graph);  //number of vertices of graph
    START_JUMP=graph_size?;
//    printf("here is graph_size : %d\n",graph_size);
    random_device r;
    mt19937_64 prng(r());
    uniform_int_distribution<long int> uniform_dist(0,graph_size-1);
    long int firstNode=sfmt_genrand_uint32(&sfmtSeed);
//    printf("here is first node : %ld\n",firstNode);
    return RandWalk(graph,START_JUMP,firstNode);   //!graph_size*10 set for Stationary process
    */
    long long edge_size = igraph_ecount(graph);
    long long tmp = sfmt_genrand_uint32(&sfmtSeed) % edge_size;
    igraph_integer_t from,to;
    igraph_edge(graph, tmp, &from, &to);
    if(sfmt_genrand_uint32(&sfmtSeed)%2) return from;
    else return to;
}
/**
 * \function RandWalk
 * Perform a randwalk on one given node
 * 
 * \param graph the input graph
 * \param steps the random walk will run
 * \param startNode random walk startNode
 * */
long int RandWalk(igraph_t *graph,long int steps, long int startNode){
    igraph_vector_t v;
    igraph_vector_init(&v,0);
    long int nextNode = startNode;
    for (int i=0;i<steps;++i){
        igraph_neighbors(graph,&v,nextNode,IGRAPH_ALL); 
//        print_vector(&v, stdout);
        long int pos = sfmt_genrand_uint32(&sfmtSeed) % igraph_vector_size(&v);
//        printf("step: %d size : %ld choose :%ld \t",i,igraph_vector_size(&v),next);
        nextNode=VECTOR(v)[pos];
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
    struct timeval start,end;
    if (argc <3){
        printf("The pramament of the procedure is like ./SSRW5C filename given_time NEXTJUMP repeat_time\n");
        exit(1);
    }

    char* filename = argv[1];
    long int given_time = atol(argv[2]);
    long int walk_per_jump = atol(argv[3]);
    long int NEXTJUMP = atol(argv[4]);
    int repeat_time =atoi(argv[5]);
    FILE *instream = fopen(filename,"r");
    if(!instream){
        string msg="Open file fail!:";
        msg.append(filename);
        throw runtime_error(msg);
    }
    igraph_t G;
    igraph_read_graph_ncol(&G,instream,NULL,0,IGRAPH_ADD_WEIGHTS_NO,IGRAPH_UNDIRECTED);
    sfmt_init_gen_rand(&sfmtSeed, time(NULL));
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
    for(int iii=0;iii<repeat_time;iii++){
        long long samples_total=0;
        long int startid=RandStart(&G);
//        cout << startid <<endl;
        long double count[MAXSUBS];    //count times all subgraph may appear
        int walk = 0;

        for(int i=0;i<MAXSUBS;++i)
            count[i]=0;
        gettimeofday(&start, NULL);
        vector<long int> node(5),user(5),degree(3);
        igraph_vector_t nodeneigh[4];
        for(int j=0;j<4;j++)
            igraph_vector_init(&nodeneigh[j],0);

        int run_times = 0;
        while(run_times<given_time){
//            cout << " count subgraph time  : " << run_times <<endl;
            node[0]=startid;
            igraph_vector_t neigh1;
            igraph_vector_init(&neigh1,0);
            igraph_neighbors(&G,&nodeneigh[0],node[0],IGRAPH_ALL);
 //           print_vector(&nodeneigh[0], stdout);
            user[1] = sfmt_genrand_uint32(&sfmtSeed)%igraph_vector_size(&nodeneigh[0]);
            node[1] = VECTOR(nodeneigh[0])[user[1]];

            igraph_neighbors(&G,&nodeneigh[1],node[1],IGRAPH_ALL);
            igraph_neighbors(&G,&neigh1,node[1],IGRAPH_ALL);
            degree[0]=igraph_vector_size(&neigh1);
            user[2] = sfmt_genrand_uint32(&sfmtSeed)%degree[0];
            node[2] = VECTOR(neigh1)[user[2]];

            igraph_neighbors(&G,&nodeneigh[2],node[2],IGRAPH_ALL);
            igraph_vector_append(&neigh1,&nodeneigh[2]);
            degree[1]=igraph_vector_size(&neigh1);
            user[3] = sfmt_genrand_uint32(&sfmtSeed)%degree[1];
            node[3] = VECTOR(neigh1)[user[3]];

            igraph_neighbors(&G,&nodeneigh[3],node[3],IGRAPH_ALL);
            igraph_vector_append(&neigh1,&nodeneigh[3]);
            degree[2]=igraph_vector_size(&neigh1);

//            for(int k=0;k<5;k++)
//                print_vector(&nodeneigh[k],stdout);
//            for (int j=0;j<6;j++){
//                cout << node[j] <<endl;
//            }

//            cout << "subgraphsize: " <<subgraph_size<<endl;
            set<long int> it{node[0],node[1],node[2],node[3]};
            long int dg_prod=degree[0]*degree[1];
            if(it.size()==4){
                long int sample_count=0;
                igraph_vector_t vc;
                igraph_vector_init(&vc,0);
                for(int i = 0; i < 3; ++i){
                    //generate 0-3 4-nodes connection
//                    cout << nodes [i] <<" ";
//                    cout << igraph_vector_size(&neighs[i]) << " : ";
 //                   print_vector(&neighs[i],stdout);
                    for(int j = i+1; j < 4; ++j){
                        if(igraph_vector_contains(&nodeneigh[i], node[j])){
                        igraph_vector_push_back(&vc,i);
                        igraph_vector_push_back(&vc,j);                    
//                        cout <<"find !!"<<nodes[i] <<' '<<nodes[j]<<endl;
                        }
                    }   
                }
                while(sample_count< degree[2]){
                    user[4] = sample_count++;
                    node[4] = VECTOR(neigh1)[user[4]];

                    if(node[4]==node[0] || node[4]==node[1] || node[4]==node[2] || node[4]==node[3])
                        continue;

                    igraph_t subgraph;
                    igraph_vector_t vctmp;
                    igraph_vector_copy(&vctmp,&vc);
                    for(int i = 0; i < 4; ++i){
//                    cout << nodes [i] <<" ";
//                    cout << igraph_vector_size(&neighs[i]) << " : ";
 //                   print_vector(&neighs[i],stdout);
                        if(igraph_vector_contains(&nodeneigh[i], node[4])){
                        igraph_vector_push_back(&vctmp,4);
                        igraph_vector_push_back(&vctmp,4);                    
//                        cout <<"find !!"<<nodes[i] <<' '<<nodes[j]<<endl;
                        }
                    }
//                cout << endl;
//                print_vector(&vc,stdout);
                igraph_create(&subgraph,&vctmp,0,IGRAPH_UNDIRECTED);
                    igraph_bool_t ios=0;
                    for(int i=0;(i<MAXSUBS)&&!ios;++i){
                        igraph_isomorphic(&subgraph,&graph[i],&ios);
//                        cout << "iso result : " << ios <<endl;
                        if(ios){
                            count[i]=count[i]+dg_prod;   //count isomorphic subgraph
//                            cout << "find the subgraph: " << i << endl;
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
                    igraph_vector_destroy(&vctmp);
                }
                igraph_vector_destroy(&vc);
            }
            walk ++;
            if(walk == walk_per_jump ){
                walk = 0;
                startid=RandWalk(&G,NEXTJUMP,node[1]);
            }
            else startid = node[1];
            samples_total+=degree[2];
            run_times++;
//            printf("next startnode: %ld",startid);
        }
        gettimeofday(&end,NULL);
        dur = (end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec)/1000000.0;
        printf("Use Time:%f\n",dur);  //count time


//      sort occurrence probability of all subgraph and print most frequent subgraph serial number 
        long double ans[MAXSUBS];
        for(int i=0;i<MAXSUBS;++i)
            ans[i]=((count[i]/W_constant[i])/run_times)*igraph_ecount(&G)*2;

        cout << "Get " << samples_total <<" Samples" <<endl;

        int count0=0;
        for(int i=0;i<MAXSUBS;++i)
            if(ans[i]==0) count0++;
//            cout << "No found subgraph : "<<i<<endl;
        cout  << "0_count_Subgraph counts " << count0 << endl;
        vector<pair<long double,int > > sorted;
        for(int i=0;i<MAXSUBS;++i)
            sorted.push_back(make_pair(ans[i],i));
        sort(sorted.rbegin(),sorted.rend());
        for(int i=0;i<MAXSUBS;++i)
            printf("SubGraph[%d] account for %Lf \n",sorted[i].second,sorted[i].first);

        const char *delim = ".";
	    char *fileNosuffix=strtok(filename,delim);
	    string s=fileNosuffix;
	    s = s + ".ssrw5";
        cout << "Now writing to " << s <<endl;
	    ofstream out(s,std::ios_base::app);
        out.precision(15);
        for(int i=0;i<MAXSUBS;++i)
            out << i << " "<<ans[i]<<endl;
        out << dur<<endl;
        out.close();
        samples_total = 0;
    }
    return 0;
} 

