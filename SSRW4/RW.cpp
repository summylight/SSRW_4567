#include "sfmt/SFMT.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include<pthread.h>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include<ctime>
#include<set>
#include<cstdio>
#include<map>
#include<thread>
#include <fstream>
#include <exception>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <mutex>
#include <random>
using namespace std ;
vector<vector<int> > graph ;
int test_num=0;
volatile  float  count1(0),count2(0);
mutex mtx;
vector<vector<int> > readFile(string path, int &N)
{
	FILE *fp ;
	

	fp = fopen(path.c_str(), "r") ;
	if(fp == false)
	{
		cout << "Error : read file" << endl ;
		exit(0) ;
	}

	int a, b, count=0 ;
	int n, m ;

	fscanf(fp, "%d%d", &n, &m) ;
	N = n ;

	for(int i=0; i<n; i++)
		graph.push_back(vector<int>()) ;

	while(fscanf(fp, "%d%d", &a, &b) == 2)
	{
		graph[a].push_back(b) ;
		count++ ;
	}
      //  cout<<a<<endl;
	if(count != m)
		cout << "m not equal to the number of edges in file" + path << endl ;
         
	fclose(fp) ;

	return graph ;
}

bool exist_edge(int  point1,int point2)
{
  vector<int>::iterator pos;
  for(pos=graph[point1].begin();pos!=graph[point1].end()&&(*pos)!=point2;pos++);
   return (pos!=graph[point1].end());
}






class graphlet
{
private:
	int *vertices; //!< A private member variable
	int size; //!< A private member variable
	int degree; //!< A private member variable
	bool isprocessed; //!< A private member variable
	map<pair<int,int>,bool> edge_status; //!< A private member variable 
	map<pair<int,int>,bool>::iterator esit; //!< A private member variable
	
public:
	 
	vector<int> degree_sum; //!< A public member variable
	//set<graphlet*> neighbors;
	vector<graphlet*> _neighbors;
	int graphletid; //!< A public member variable
	graphlet(){}//!< Constructor

	/*! \fn graphlet(int X,int Y,int Z)
 		*  \brief A constructor function to create 3 node graphlets.
 		*  \param X an integer
		*  \param Y an integer
		*  \param Z an integer
 		*/
	graphlet(int X,int Y,int Z)
	{
		size=3;
		degree_sum.resize(6);
		for(int i=0;i<6;i++)degree_sum[i]=0;
		
		vertices = new int[3];
		vertices[0] = X;
		vertices[1] = Y;
		vertices[2] = Z;
		edge_status.insert(make_pair(make_pair(X,Y),false));
		edge_status.insert(make_pair(make_pair(Y,Z),false));
		edge_status.insert(make_pair(make_pair(Z,X),false));
		sort(vertices,vertices+3);
	}

	/*! \fn bool get_edge_status(int X, int Y)
 		*  \brief A function to know whether there is any edge between X and Y.
 		*  \param X an integer
		*  \param Y an integer
		*  \return boolean
 		*/
	bool get_edge_status(int X, int Y)
	{
		
		esit = edge_status.find(make_pair(X,Y));
		if(esit != edge_status.end())
		{
			return esit->second;
		}
		esit = edge_status.begin();
		esit = edge_status.find(make_pair(Y,X));
		if(esit !=edge_status.end())
		{
			return esit->second;
			
		}
		else
		{
			cout << "no stat found\n";
		}
		
	}
	/*! \fn void clear_edge_stat()
 		*  \brief A function to clear edge_status vector.
 		*/
	void clear_edge_stat()
	{
		edge_status.clear();
	}
	
	/*! \fn void set_edge_status(int X, int Y)
 		*  \brief A function to set edge status to true between X and Y.
 		*  \param X an integer
		*  \param Y an integer
 		*/
	void set_edge_status(int X, int Y)
	{
		esit = edge_status.find(make_pair(X,Y));
		if(esit != edge_status.end()){
		//cout << "set to "<<X <<"and" <<Y<<endl;
			esit->second = true;
			return;
		}
		esit = edge_status.begin();
		esit = edge_status.find(make_pair(Y,X));
		if(esit != edge_status.end()){
		//cout << "set to "<<X <<"and" <<Y<<endl;
			esit->second = true;
			return;
		}
		else	{cout << "can not be set\n";}
		
	}

	/*! \fn graphlet(int X,int Y,int Z,int W)
 		*  \brief A constructor function to create 4 node graphlets.
 		*  \param X an integer
		*  \param Y an integer
		*  \param Z an integer
		*  \param W an integer
 		*/
	graphlet(int X,int Y,int Z,int W)
	{
		size=4;
		degree_sum.resize(6);
		for(int i=0;i<6;i++)degree_sum[i]=0;
		vertices = new int[4];
		vertices[0] = X;
		vertices[1] = Y;
		vertices[2] = Z;
		vertices[3] = W;
		edge_status.insert(make_pair(make_pair(X,Y),false));
		edge_status.insert(make_pair(make_pair(X,Z),false));
		edge_status.insert(make_pair(make_pair(X,W),false));
		edge_status.insert(make_pair(make_pair(Y,Z),false));
		edge_status.insert(make_pair(make_pair(Y,W),false));
		edge_status.insert(make_pair(make_pair(Z,W),false));
		
		sort(vertices,vertices+4);
	}

	/*! \fn graphlet(int V,int W,int X,int Y,int Z)
 		*  \brief A constructor function to create 4 node graphlets.
 		*  \param V an integer
		*  \param W an integer
		*  \param X an integer
		*  \param Y an integer
		*  \param Z an integer
 		*/
	graphlet(int V,int W,int X,int Y,int Z)
	{
		size=5;
		vertices = new int[5];
		degree_sum.resize(6);
		for(int i=0;i<6;i++)degree_sum[i]=0;
		vertices[0] = V;
		vertices[1] = W;
		vertices[2] = X;
		vertices[3] = Y;
		vertices[4] = Z;
		edge_status.insert(make_pair(make_pair(V,W),false));
		edge_status.insert(make_pair(make_pair(V,X),false));
		edge_status.insert(make_pair(make_pair(V,Y),false));
		edge_status.insert(make_pair(make_pair(V,Z),false));
		edge_status.insert(make_pair(make_pair(W,X),false));
		edge_status.insert(make_pair(make_pair(W,Y),false));
		edge_status.insert(make_pair(make_pair(W,Z),false));
		edge_status.insert(make_pair(make_pair(X,Y),false));
		edge_status.insert(make_pair(make_pair(X,Z),false));
		edge_status.insert(make_pair(make_pair(Y,Z),false));
		sort(vertices,vertices+5);
	}
	//!< Destructor
	~graphlet(){
		//_neighbors.clear();
		delete vertices;
		//cout<<"graphlet destructor\n";
	}

	/*! \fn void set_degree(int _degree)
 		*  \brief A function to set degree of current graphlet.
 		*  \param degree an integer
 		*/
	void set_degree(int _degree){
		degree = _degree;
	}

	/*! \fn int get_size()
 		*  \brief A function to know the size of the current graphlet.
		*  \return an integer
 		*/
	int get_size()
	{
		return size;
	}

	
	/*! \fn int get_size()
 		*  \brief A function to know the degree of the current graphlet.
		*  \return an integer
 		*/
	int get_degree()
	{
		return degree;
	}

	/*! \fn void getVertices(vector<int> & t)
 		*  \brief A function to get vertices of the current graphlet.
 		*  \param t address of vector<int>
 		*/
	void getVertices(vector<int> & t)
	{
		for(int i=0; i< this->size; i++)
			 t.push_back(vertices[i]);
	}

	/*! \fn void set_isprocessed(bool t)
 		*  \brief A function to set isprocessed flag of the current graphlet.
 		*  \param t a boolean
		*/
	void set_isprocessed(bool t)
	{
		isprocessed = t;
	}

	/*! \fn void set_isprocessed(bool t)
 		*  \brief A function to get isprocessed flag of the current graphlet.
 		*  \return boolean 
		*/
	bool get_isprocessed()
	{
		return isprocessed;
	}

	/*! \fn void print_edge_stat()
 		*  \brief A function print edge status of a graphlet.
		*/
	void print_edge_stat(){
		cout<<"edgestat:(";		
		for(esit=edge_status.begin(); esit!= edge_status.end(); esit++)
			 cout << (esit->first).first << ","<<(esit->first).second <<" stat = "<<esit->second<<endl;;
		cout <<")"<<endl;
	}

	/*! \fn void print_graphlet()
 		*  \brief A function print a graphlet.
		*/
	void print_graphlet(){
		cout<<"graphlet:(";		
		for(int i=0; i< this->size; i++)
			 cout << vertices[i] << ",";
		cout <<")"<<endl;
	}
	
	/*! \fn bool operator==( graphlet &g1)
 		*  \brief == operator overloading function for graphlets
		*/
	bool operator==( graphlet &g1)
	{
		if(vertices[0] == g1.vertices[0] && vertices[1] == g1.vertices[1] && vertices[2] == g1.vertices[2] 
			&& vertices[3] == g1.vertices[3] && vertices[4] == g1.vertices[4])
		{
			//this->print_graphlet();
			//g1.print_graphlet();
			return true;
		}
		else
		{
			return false;
		}
	}
	/*! \fn graphlet* clone() const
 		*  \brief clone function for graphlet object
		*  \return graphlet type pointer
		*/
	graphlet* clone() const {

   //   	cout << "In clone:\n";
		if(size==3)
		{
			graphlet* clone = new graphlet(vertices[0],vertices[1],vertices[2]);
			clone->size= size;
			clone->edge_status = edge_status;
			clone->_neighbors.assign(_neighbors.begin(), _neighbors.end());
			clone->graphletid = graphletid;
			clone->degree_sum.assign(degree_sum.begin(),degree_sum.end());
			clone->degree = degree;
			return clone;
		}
		if(size==4)
		{
			graphlet* clone = new graphlet(vertices[0],vertices[1],vertices[2],vertices[3]);
			clone->size= size;
			clone->edge_status = edge_status;
			clone->_neighbors.assign(_neighbors.begin(), _neighbors.end());
			clone->graphletid = graphletid;
			clone->degree_sum.assign(degree_sum.begin(),degree_sum.end());
			clone->degree = degree;
			return clone;
		}
		if(size==5)
		{
			graphlet* clone = new graphlet(vertices[0],vertices[1],vertices[2],vertices[3],vertices[4]);
			clone->size= size;
			clone->edge_status = edge_status;
			clone->_neighbors.assign(_neighbors.begin(), _neighbors.end());
			clone->graphletid = graphletid;
			clone->degree_sum.assign(degree_sum.begin(),degree_sum.end());
			clone->degree = degree;
			return clone;
		}
    }

	/*! \fn std::string canonical_code() const
 		*  \brief A function to get unique code for a graphlet
		*  \return string
		*/
	std::string canonical_code() const { 
      
	  	vector<int> data;
		for(int i=0; i< this->size; i++)
			 data.push_back(vertices[i]);
	  	
      stringstream ss;
      std::copy(data.begin(), data.end(), ostream_iterator<int>(ss, "_"));
      //cout << "canonical code: "<< ss.str()<<endl;
		data.clear();
      return ss.str();
    } 
	//vector<int> degree_sum (6);
};




void find_which_graplet(graphlet *&t, vector<bool>& edgesT)
	{       test_num++;
		int *degree  = new int[t->get_size()];
		vector<int> v;
		t->getVertices(v);
		
		{
			degree[0] = degree[1] = degree[2] = degree[3]=0;
			if(edgesT[0]==true)
			{
				degree[0]++;
				degree[1]++;
			}
			if(edgesT[1]==true)
			{
				degree[0]++;
				degree[2]++;
			}
			if(edgesT[2]==true)
			{
				degree[0]++;
				degree[3]++;
			}
			if(edgesT[3]==true)
			{
				degree[1]++;
				degree[2]++;
			}
			if(edgesT[4]==true)
			{
				degree[1]++;
				degree[3]++;
			}
			if(edgesT[5]==true)
			{
				degree[2]++;
				degree[3]++;
			}

	//		cout <<"degree"<< degree[0] <<", "<< degree[1]<<", "<<degree[2] <<", "<< degree[3]<<endl;
			sort(degree, degree+4);

	//		cout <<"degree"<< degree[0] <<", "<< degree[1]<<", "<<degree[2] <<", "<< degree[3]<<endl;
			if(degree[0]==1 && degree[1]==1 && degree[2]==2 && degree[3]==2)
			{
				t->graphletid = 3;
			}
			else if(degree[0]==1 && degree[1]==1 && degree[2]==1 && degree[3]==3)
			{
				t->graphletid = 4;
			}
			else if(degree[0]==2 && degree[1]==2 && degree[2]==2 && degree[3]==2)
			{
				t->graphletid = 5;
			}
			else if(degree[0]==1 && degree[1]==2 && degree[2]==2 && degree[3]==3)
			{
				t->graphletid = 6;
			}

			else if(degree[0]==2 && degree[1]==2 && degree[2]==3 && degree[3]==3)
			{
				t->graphletid = 7;
			}
			else if(degree[0]==3 && degree[1]==3 && degree[2]==3 && degree[3]==3)
			{
				t->graphletid = 8;
			}
		} 
            return;
	}




void get_graphletid(graphlet *& t) //the delected code should be rewrite later.
	{
		vector<int>v;
		t->getVertices(v);
		set<graphlet*> graphlets;
		int flag=0;
		
		vector<bool>edgesT;
		edgesT.resize((v.size()*(v.size()-1))/2);
		      
			{
				
				int k=0;
				for(int i=0; i<v.size();i++)
				{
					for(int j=i+1; j<v.size();j++)
					{
						edgesT[k] = t->get_edge_status(v[i],v[j]);
				
						if(edgesT[k]==false)
						{
							edgesT[k] = exist_edge(v[i],v[j]);	
							if(edgesT[k]==true)
							{
								t->set_edge_status(v[i],v[j]);
							}
						}
				
						k++;
					}

				}
		
				find_which_graplet(t,edgesT);
			}
                     
	}

//int sum[30];
//int sumB[30];
//float fsumA[30];
//float fsumB[30];
//float total[30];



time_t start,end;
//vector<vector<int> > graph ;

int N ;	//the nodes of graph 



int iteration = 200000;


float co1[31]={0};
float co2[31]={0};
float co3[31]={0};
      


int iter_num;
int   t_rand=0,t_rand_2=1001;
float estimate()
{
 float fsumC[30]={0.0};

 
    
 sfmt_t sfmtSeed ;

 sfmt_init_gen_rand(&sfmtSeed, time(NULL)) ;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 100000000);
	int startUser = rd() % N ;
	//x.push_back((double)graph[startUser].size()) ;
	int tmpUser = startUser ;
        
        int tmpID = sfmt_genrand_uint32(&sfmtSeed) % graph[tmpUser].size() ;
        tmpUser = graph[tmpUser][tmpID] ;        
        int sum2=0;

        // cout<<"-----"<<tmpUser<<endl;
         //graphlet  GRA(1,2,3);





        graphlet *g1;
       // graphlet *GRA=new graphlet(4,5,6);
        int iter1=4,iter2=5,iter3=6,iter_past,iter_extra;
       
       
      for(int cc=0;cc<1000;cc++)
       {
          int tmpID0=rd() % graph[tmpUser].size() ;
             tmpUser=graph[tmpUser][tmpID0];
       }


       for(int ii=0;ii<iter_num;ii++){

            int tmpID0=rd() % graph[tmpUser].size() ;
             tmpUser=graph[tmpUser][tmpID0];
          //  tmpUser = sfmt_genrand_uint32(&sfmtSeed) %N ;
         
        // for(int jj=0;jj< graph[tmpUser].size();jj++){
           int tmpID1 = sfmt_genrand_uint32(&sfmtSeed) % graph[tmpUser].size() ;
           int tmpUser1=graph[tmpUser][tmpID1];
           int tmpID2 =rd() % graph[tmpUser1].size() ;
           int tmpUser2=graph[tmpUser1][tmpID2];
          
           int id;
           int tmpID5=rd() %(graph[tmpUser1].size()+graph[tmpUser2].size());
           int tmpUser5;
           if(tmpID5<graph[tmpUser1].size())
                tmpUser5=graph[tmpUser1][tmpID5];
            else
                tmpUser5=graph[tmpUser2][tmpID5-graph[tmpUser1].size()];
           
          
        if(tmpUser!=tmpUser2&&tmpUser!=tmpUser5&&tmpUser1!=tmpUser5&&tmpUser2!=tmpUser5){
            graphlet *GRC=new graphlet(tmpUser,tmpUser1,tmpUser2,tmpUser5);
            
             get_graphletid(GRC);
          
             id=GRC->graphletid;
             delete GRC;
               fsumC[id]+=(float)graph[tmpUser1].size()*(graph[tmpUser1].size()+graph[tmpUser2].size())/co3[id];
             
            }
      //    }
           }
       
        
    // for(int id=3;id<9;id++)
    //   {
    //      cout<<"id"<<id<<":"<<sum[id]<<endl;
    //   }  
    // for(int id=3;id<9;id++)
    //   {
    //      cout<<"idB"<<id<<":"<<sumB[id]<<endl;
    //   }    

    // float sum_A=0,sum_B=0; 
    // for(int id=3;id<9;id++)
    //   {
         // cout<<"fid"<<id<<":"<<fsumA[id]<<endl;
    //      sum_A+=fsumA[id];
    //   }  
    // for(int id=3;id<9;id++)
    //   {
         // cout<<"fidB"<<id<<":"<<fsumB[id]<<endl;
    //      sum_B+=fsumB[id];
    //   }  
    // for(int id=3;id<9;id++)
    //   {
    //      cout<<"fid"<<id<<":"<<fsumA[id]/sum_A<<endl;
          
    //   }  
   

float sumC=0;
for(int ii=3;ii<9;ii++)
    sumC+=fsumC[ii];

 //   cout<<"estimated"<<"\t"<<"accurate"<<endl;
   //  for(int ii=3;ii<9;ii++)
   //   {     
   //     cout<<fsumC[ii]/sumC<<endl;
   //   }
        
       cout<<fsumC[4]/sumC<<endl;
       mtx.lock();
       //cout<<sumC<<endl;
       count1+=fsumC[4];
       count2+=sumC; 
       mtx.unlock();       
       //cout<<":::::"<<sumC<<'\t';   

   return fsumC[4]/sumC;
}




int main(int argc,char **argv)
{
	//vector<double> x ;

       co1[3]=2.0;
       co1[5]=8.0;
       co1[6]=4.0;
       co1[7]=12.0;
       co1[8]=24.0;
       co2[4]=6.0;
       co2[6]=6.0;
       co2[7]=12.0;
       co2[8]=24.0;
       co3[3]=2.0;
       co3[4]=6.0;
       co3[5]=8.0;
       co3[6]=10.0;
       co3[7]=24.0;
       co3[8]=48.0;


     //for(int ii=3;ii<9;ii++)
//    cout<<fsumC[ii]/sumC<<endl;

//float sum_pp=sums;
//epinions.txt
float ppp[30]={0};
/*
ppp[8] = 1314440;
ppp[7] = 10104542;
ppp[6] = 72280939;
ppp[5] = 3684251;
ppp[4] = 174306227;
ppp[3] = 182564998;*/
//email-enron.txt
ppp[8]= 2027045;
ppp[7] = 18386889;
ppp[6] = 232387128;
ppp[5] = 5977655;
ppp[4] = 1197170807;
ppp[3] = 819288358;

//Email-Eron.txt
ppp[8] = 2341639;
ppp[7] = 22478442;
ppp[6] = 375691411;
ppp[5] = 6758870;
ppp[4] = 4479591993;
ppp[3] = 1371828020;

//epinions.txt connected

ppp[8] = 1314440;
ppp[7] = 10104540;
ppp[6] = 72280936;
ppp[5] = 3684251;
ppp[4] = 174306226;
ppp[3] = 182564989;

//Epinions1.txt
ppp[3]=8356457115;	 ppp[4]=15854747802;	 ppp[5]=71536862;	 ppp[6]=1404367889;	 ppp[7]=77688760;	 ppp[8]=5803397;

//Slashdot0.txt	
ppp[3]= 6354537442;	 ppp[4]=14854175885;	 ppp[5]=27160530;	 ppp[6]=402930550;	 ppp[7]= 16834749;	 ppp[8]=1989958;
//out.txt
ppp[3]=1371827500;ppp[4]=4479590637;ppp[5]=6758865;ppp[6]=375689616;ppp[7]=22477983;ppp[8]=2340740;	

    int num=5;
    start=clock();
    int sum_test=0;
    float sums=0;
    for(int ii=3;ii<9;ii++)
      {     
        sums+=ppp[ii];
      }
     float acc=ppp[4]/sums; 
     cout<<"acc:"<<acc<<endl;  
     graph = readFile("out.txt", N) ;
     iter_num=atoi(argv[1]); 
    
     thread  th[10];

      for(int i=0;i<5;i++)  {
       th[i]=thread(estimate);

       cpu_set_t cpuset;

      CPU_ZERO(&cpuset);

      CPU_SET(i,&cpuset);

      int rc =pthread_setaffinity_np(th[i].native_handle(),sizeof(cpu_set_t), &cpuset);

    if (rc != 0) {

     // std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";

    }

      }
      for(int i=0;i<5;i++){
         th[i].join();
       }
    
    // t.join();     }
     //thread  t1(estimate);
     //thread  t2(estimate);
     //thread  t3(estimate);
     //t1.join();
     //t2.join();
     //t3.join();
    // float sum=0;
     //for(int ii=0;ii<1000;ii++){
     //    float ans=estimate(nums); 
     //    sum+=(ans-acc)*(ans-acc);
    
   //  }
    // cout<<nums<<'\t'<<sqrt(sum/10)/(10*acc)<<endl;
       cout<<"parallel all: "<<count1/count2<<endl;
      // cout<<count2<<endl;

     cout<<(double)(clock()-start)/CLOCKS_PER_SEC<<endl;
     return 0 ;
}
