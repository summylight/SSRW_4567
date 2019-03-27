SSRW algorithm is implemented in python, using iGraph routines. The installation of iGraph is required. See http://igraph.org/python/.


The code requires two input files.
1. The graph file
   It describes the graph in a text format. Each line in the file describes an undirected edge with space-separated ids of its incident nodes. The graph must be a connected graph. See so-slashdot_lcc.txt as an example. 

2. The starting node file
   It describes the starting node of the random walk for each trial. Each line in the file describes the id of a node in the graph. See startingnode_slashdot.txt as an example.  

step_num decides the length of the random walk.
iter_num indicates the number of trials. 

The output file will contain the estimates of the counts for 6-node or 7-node motifs.
