#ifndef FileProcess_H
#define FileProcess_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std ;

vector<vector<int> > readFile(string path, int &N)
{
	FILE *fp ;
	vector<vector<int> > graph ;

	fp = fopen(path.c_str(), "r") ;
	if(fp == false)
	{
		cout << "Error : read file" << endl ;
		exit(0) ;
	}

	int a, b, count=0 ;
	int n, m ;

	fscanf(fp, "%d%d", &n, &m) ;
        cout<<n;
	N = n ;

	for(int i=0; i<n; i++)
		graph.push_back(vector<int>()) ;

	while(fscanf(fp, "%d%d", &a, &b) == 2)
	{
		graph[a].push_back(b) ;
		count++ ;
	}

	if(count != m)
		cout << "m not equal to the number of edges in file" + path << endl ;

	fclose(fp) ;

	return graph ;
}

#endif
