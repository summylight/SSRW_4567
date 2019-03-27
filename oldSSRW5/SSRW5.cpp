#include "sfmt/SFMT.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <set>
#include <map>
#include <fstream>
#include <exception>
#include <iterator>
#include <set>
#include <sstream>
#include <cmath>
#define CLOCKS_PER_SEC ((__clock_t) 1000000)
using namespace std ;
vector<vector<int> > graph;
int graph_degree=0;
vector<vector<int> > readFile(string path)
{
	FILE *fp ;

	fp = fopen(path.c_str(), "r") ;
	if(NULL == fp)
	{
		cout << "Error : read file" << endl ;
		exit(0) ;
	}

	int a, b, edge_count=0 ;

	while(fscanf(fp, "%d%d", &a, &b) == 2)
	{
		cout << a << " "<<b<<endl;
		while(a+1>graph.size()) 
			graph.push_back(vector<int>());
//		cout<< "now graph has " << graph.size()<< endl;
		while(b+1>graph.size()) 
			graph.push_back(vector<int>());
//		cout<< "now graph has " << graph.size()<< endl;
		graph[a].push_back(b) ;
        graph[b].push_back(a) ;
		edge_count+=1 ;
		graph_degree+=2;
	}
	cout  << graph.size ()<< "  vectices 	" << edge_count << "  edges" << endl;
         
	fclose(fp) ;
	return graph ;
}

bool exist_edge(int  point1,int point2)
{
  vector<int>::iterator pos;
  for(pos=graph[point1].begin();pos!=graph[point1].end()&&(*pos)!=point2;pos++);
   return (pos!=graph[point1].end());
}

bool is_connected(int point1,int point2,int point3)
{
bool  p1=exist_edge(point1,point2);
bool  p2=exist_edge(point2,point3);
bool  p3=exist_edge(point1,point3);

return   ((p1&&p2)||(p2&&p3)||(p1&&p3));
// (&&exist_edge(point2,point3)))||((exist_edge(point1,point2)&&exist_edge(point1,point3)))||((exist_edge(point2,point3)&&exist_edge(point1,point3))));

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
			return false;
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
		for(int j=0;j< this->size;j++)
			for(int k=0;k< this->size;k++){
				if(get_edge_status(vertices[j],vertices[k])) cout <<" 1";
				else cout << " 0";
			}
			cout << endl;
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
	{
		int *degree  = new int[t->get_size()];
		vector<int> v;
		t->getVertices(v);
		
		if(t->get_size()==3)
		{
			degree[0] = degree[1] = degree[2] = 0;
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
				degree[1]++;
				degree[2]++;
			}
			sort(degree, degree+3);

			if(degree[0]==1 && degree[1]==1 && degree[2]==2)
			{
				t->graphletid = 1;
			}
			else if(degree[0]==2 && degree[1]==2 && degree[2]==2)
			{
				t->graphletid = 2;
			}
			
		}
		if(t->get_size()==4)
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
		if(t->get_size()==5)
		{
			vector<int> copy_degree;
			copy_degree.resize(t->get_size());
			degree[0] = degree[1] = degree[2] = degree[3] = degree[4] = 0;
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
				degree[0]++;
				degree[4]++;
			}
			if(edgesT[4]==true)
			{
				degree[1]++;
				degree[2]++;
			}
			if(edgesT[5]==true)
			{
				degree[1]++;
				degree[3]++;
			}
			
			if(edgesT[6]==true)
			{
				degree[1]++;
				degree[4]++;
			}
			if(edgesT[7]==true)
			{
				degree[2]++;
				degree[3]++;
			}
			if(edgesT[8]==true)
			{
				degree[2]++;
				degree[4]++;
			}
			if(edgesT[9]==true)
			{
				degree[3]++;
				degree[4]++;
			}

	
			copy_degree[0] = degree[0];copy_degree[1] = degree[1];copy_degree[2] = degree[2];copy_degree[3] = degree[3];copy_degree[4] = degree[4];
			sort(degree, degree+5);
		
			if(degree[0]==1 && degree[1]==1 && degree[2]==2 && degree[3]==2 && degree[4]==2)
			{
				t->graphletid = 9;
			}
			else if(degree[0]==1 && degree[1]==1 && degree[2]==1 && degree[3]==2 && degree[4]==3)
			{
				t->graphletid = 10;
			}
			else if(degree[0]==1 && degree[1]==1 && degree[2]==1 && degree[3]==1 && degree[4]==4)
			{
				t->graphletid = 11;
			}
			else if(degree[0]==1 && degree[1]==1 && degree[2]==2 && degree[3]==3 && degree[4]==3)
			{
				t->graphletid = 12;
			}

			else if(degree[0]==1 && degree[1]==2 && degree[2]==2 && degree[3]==2 && degree[4]==3)
			{
				int index;
				for(int i=0; i<copy_degree.size();i++)
				{
					if(copy_degree[i]==1)
					{
						index = i;
						break;
					}
				}
				for(int j=0; j<copy_degree.size();j++)
				{
					if(index==j)continue;
					if(t->get_edge_status(v[index],v[j]))
					{
						index = j;
						break;
					}
				}
				if(copy_degree[index]==2)
					t->graphletid = 13;
				else
					t->graphletid = 16;
			}
			else if(degree[0]==1 && degree[1]==1 && degree[2]==2 && degree[3]==2 && degree[4]==4)
			{
				t->graphletid = 14;
			}

			if(degree[0]==2 && degree[1]==2 && degree[2]==2 && degree[3]==2 && degree[4]==2)
			{
				t->graphletid = 15;
			}
			else if(degree[0]==1 && degree[1]==2 && degree[2]==2 && degree[3]==3 && degree[4]==4)
			{
				t->graphletid = 17;
			}
			else if(degree[0]==2 && degree[1]==2 && degree[2]==2 && degree[3]==2 && degree[4]==4)
			{
				t->graphletid = 18;
			}
			else if(degree[0]==1 && degree[1]==2 && degree[2]==3 && degree[3]==3 && degree[4]==3)
			{
				t->graphletid = 19;
			}

			else if(degree[0]==2 && degree[1]==2 && degree[2]==2 && degree[3]==3 && degree[4]==3)
			{
				int index;
				vector<int> _index;
				for(int i=0; i<copy_degree.size();i++)
				{
					if(copy_degree[i]==3)
					{
						index = i;
						break;
					}
				}
				for(int j=0; j<copy_degree.size();j++)
				{
					if(index==j)continue;
					if(t->get_edge_status(v[index],v[j]))
					{
						_index.push_back(j);
						//break;
					}
				}
				if(copy_degree[_index[0]]==2 && copy_degree[_index[1]]==2 && copy_degree[_index[2]]==2)
					t->graphletid = 20;
				else
					t->graphletid = 21;
			
			}
			else if(degree[0]==2 && degree[1]==2 && degree[2]==2 && degree[3]==4 && degree[4]==4)
			{
				t->graphletid = 22;
			}

			if(degree[0]==1 && degree[1]==3 && degree[2]==3 && degree[3]==3 && degree[4]==4)
			{
				t->graphletid = 23;
			}
			else if(degree[0]==2 && degree[1]==2 && degree[2]==3 && degree[3]==3 && degree[4]==4)
			{
				t->graphletid = 24;
			}
			else if(degree[0]==2 && degree[1]==3 && degree[2]==3 && degree[3]==3 && degree[4]==3)
			{
				t->graphletid = 25;
			}
			else if(degree[0]==2 && degree[1]==3 && degree[2]==3 && degree[3]==4 && degree[4]==4)
			{
				t->graphletid = 26;
			}

			else if(degree[0]==3 && degree[1]==3 && degree[2]==3 && degree[3]==3 && degree[4]==4)
			{
				t->graphletid = 27;
			}
			else if(degree[0]==3 && degree[1]==3 && degree[2]==4 && degree[3]==4 && degree[4]==4)
			{
				t->graphletid = 28;
			}
			else if(degree[0]==4 && degree[1]==4 && degree[2]==4 && degree[3]==4 && degree[4]==4)
			{
				t->graphletid = 29;
			}
			return;
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
		        
			if(t->get_size()==3)
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
			if(t->get_size()==4)
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
                      
			if(t->get_size()==5)
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
//			for (int i=0;i<v.size();i++){
//				for (int j=i+1;j<v.size();j++){
//					if(t->get_edge_status(v[i],v[j])) cout<<" 1";
//					else cout<< " 0";
//				}
//				cout<<endl;
//			}
				
				find_which_graplet(t,edgesT);
			}
	}




float ans[30]={0};
int N ;	//the nodes of graph 
int realcount;
int sum[30];
int sumB[30];
float fsumA[30];
float fsumB[30];
float fsumC[30];
int fsumCnum[30];
float total[30];
float sumC=0;
void estimate_5(int num)
{

	for(int i=0;i<30;i++){
		fsumC[i]=0;
		fsumCnum[i]=0;
  	}
	time_t start,end;
	
	sfmt_t sfmtSeed ;
	

	sfmt_init_gen_rand(&sfmtSeed, time(NULL)) ;
	int iteration = 200000;
	//x.push_back((double)graph[startUser].size()) ;
	int tmpUser = 50;
        
    int tmpID = sfmt_genrand_uint32(&sfmtSeed) % graph[tmpUser].size() ;
    tmpUser = graph[tmpUser][tmpID] ;        
    int sum2=0; 
    graphlet *g1;
    int iter1=4,iter2=5,iter3=6,iter_past,iter_extra;
      
    float co1[31]={0};
    float co2[31]={0};
    float co3[31]={0};
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
    co3[9]=2.0;
    co3[10]=8.0;
    co3[11]=24.0;
    co3[12]=18.0;
    co3[13]=12.0;
    co3[14]=40.0;
    co3[15]=10.0;
    co3[16]=20.0;
    co3[17]=68.0;
    co3[18]=64.0;
    co3[19]=40.0;
    co3[20]=60.0;
    co3[21]=46.0;
    co3[22]=156.0;
    co3[23]=108.0;
    co3[24]=124.0;
    co3[25]=108.0;
    co3[26]=244.0;
    co3[27]=232.0;
    co3[28]=432.0;
    co3[29]=720.0;

    for(int ii=0;ii<1000;ii++){
     int tmpID = sfmt_genrand_uint32(&sfmtSeed) % graph[tmpUser].size() ;
      tmpUser = graph[tmpUser][tmpID] ;  
    }
      
    for(int ii=0;ii<num;ii++){
      int tmpID = sfmt_genrand_uint32(&sfmtSeed) % graph[tmpUser].size() ;
      tmpUser = graph[tmpUser][tmpID] ;  
       int tmpID1 = sfmt_genrand_uint32(&sfmtSeed) % graph[tmpUser].size() ;
       int tmpUser1=graph[tmpUser][tmpID1];
       int tmpID2 = sfmt_genrand_uint32(&sfmtSeed) % graph[tmpUser1].size() ;
       int tmpUser2=graph[tmpUser1][tmpID2];
       int id;
       
       int tmpID3=sfmt_genrand_uint32(&sfmtSeed) %(graph[tmpUser1].size()+graph[tmpUser2].size());
       int tmpUser3;
           // cout<<tmpID3<<endl;
       if(tmpID3<graph[tmpUser1].size())
            tmpUser3=graph[tmpUser1][tmpID3];
        else
            tmpUser3=graph[tmpUser2][tmpID3-graph[tmpUser1].size()];
       
       int tmpID4=sfmt_genrand_uint32(&sfmtSeed) %(graph[tmpUser1].size()+graph[tmpUser2].size()+graph[tmpUser3].size());
       int tmpUser4;
       if(tmpID4<graph[tmpUser1].size())
            tmpUser4=graph[tmpUser1][tmpID4];
        else if(tmpID4<graph[tmpUser1].size()+graph[tmpUser2].size())
            tmpUser4=graph[tmpUser2][tmpID4-graph[tmpUser1].size()];
        else
            tmpUser4=graph[tmpUser3][tmpID4-graph[tmpUser1].size()-graph[tmpUser2].size()];
	
          // cout<<tmpUser4<<endl;
          set<int>my_set;
          my_set.insert(tmpUser);
          my_set.insert(tmpUser1);
          my_set.insert(tmpUser2);
          my_set.insert(tmpUser3);
          my_set.insert(tmpUser4);
          if(my_set.size()==5){
          graphlet *GRC=new graphlet(tmpUser,tmpUser1,tmpUser2,tmpUser3,tmpUser4);
          get_graphletid(GRC);
         id=GRC->graphletid;
//	 GRC->print_graphlet();
         delete GRC;
	 fsumCnum[id]+=1;
        //  cout<<id<<endl;
         if(id>8&&id<30)
         fsumC[id]+=(float)graph[tmpUser1].size()*(graph[tmpUser1].size()+graph[tmpUser2].size())*(graph[tmpUser1].size()+graph[tmpUser2].size()+graph[tmpUser3].size())/(co3[id]);

       }
       }
          
   


  for(int ii=9;ii<30;ii++)
    sumC+=fsumC[ii];
  for(int ii=9;ii<30;ii++)
    ans[ii]=fsumC[ii];
for(int ii=9;ii<30;ii++)
{
//	cout << "graph "<<ii-8<< " count "<<fsumCnum[ii]<<endl;
    cout<<"graph "<<ii-8<<" occupy "<<fsumC[ii]/sumC<<endl;
}

}


float ppp[30]={0};

/**
 * /function main
 * 
 * Read graph file and iteration number, print frequency on screen and outputfile
 * 
 * /param graph file
 * /param <int> interation number, huger the iteration number is, more accurate result is 
 * /return print frequency on screen and outputfile in format "graphname.ssrw5"
 * */
int main(int argc,char **argv)
{      
	graph = readFile(argv[1]);
	char* file= argv[1];
	const char *delim = ".";
	char *filename=strtok(file,delim);
	string s=filename;
	s = s + ".ssrw5result";
	ofstream outfile(s);
//	cout << "here"<<endl;
    clock_t start=clock();
    estimate_5(atoi(argv[2]));
    cout<<"random walk " << atoi(argv[2]) << " times cost "
	<<(double)(clock()-start)/CLOCKS_PER_SEC<<" seconds"<<endl;
	cout << "Writing to output file : " << s << endl;
	if(!outfile) 
		cerr << "Oops! Writing to output file FAIL!!!: " <<s<<endl; 
	for(int i=0;i<21;++i){
		outfile << i+1<<"		"<<(fsumC[i]/sumC)<<endl;
	}
	return 0 ;
}
