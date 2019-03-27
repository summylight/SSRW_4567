from __future__ import division
import random as rdm
import random_walk as rdmW
import igraph as igh
from sys import argv
import string 
import multiprocessing
import sys
import datetime
Graph_list=[]
Graph_list.append(igh.Graph())
Graph_list[0].add_vertices(5)
Graph_list[0].add_edges([(0,4),(1,4),(2,4),(3,4)])

Graph_list.append(igh.Graph())
Graph_list[1].add_vertices(5)
Graph_list[1].add_edges([(0,3),(0,4),(1,4),(2,4)])

Graph_list.append(igh.Graph())
Graph_list[2].add_vertices(5)
Graph_list[2].add_edges([(0,3),(0,4),(1,4),(2,4),(3,4)])

Graph_list.append(igh.Graph())
Graph_list[3].add_vertices(5)
Graph_list[3].add_edges([(0,3),(0,4),(1,3),(1,4),(2,4)])

Graph_list.append(igh.Graph())
Graph_list[4].add_vertices(5)
Graph_list[4].add_edges([(0,3),(0,4),(1,3),(2,4),(3,4)])

Graph_list.append(igh.Graph())
Graph_list[5].add_vertices(5)
Graph_list[5].add_edges([(0,3),(0,4),(1,3),(1,4),(2,4),(3,4)])

Graph_list.append(igh.Graph())
Graph_list[6].add_vertices(5)
Graph_list[6].add_edges([(0,3),(0,4),(1,3),(1,4),(2,3),(2,4)])

Graph_list.append(igh.Graph())
Graph_list[7].add_vertices(5)
Graph_list[7].add_edges([(0,3),(0,4),(1,3),(1,4),(2,3),(2,4),(3,4)])

Graph_list.append(igh.Graph())
Graph_list[8].add_vertices(5)
Graph_list[8].add_edges([(0,2),(0,4),(1,3),(1,4)])

Graph_list.append(igh.Graph())
Graph_list[9].add_vertices(5)
Graph_list[9].add_edges([(0,2),(0,4),(1,3),(1,4),(2,4)])

Graph_list.append(igh.Graph())
Graph_list[10].add_vertices(5)
Graph_list[10].add_edges([(0,2),(0,4),(1,3),(1,4),(2,4),(3,4)])

Graph_list.append(igh.Graph())
Graph_list[11].add_vertices(5)
Graph_list[11].add_edges([(0,2),(0,3),(1,3),(1,4),(2,4)])

Graph_list.append(igh.Graph())
Graph_list[12].add_vertices(5)
Graph_list[12].add_edges([(0,2),(0,3),(0,4),(1,3),(1,4),(2,4)])

Graph_list.append(igh.Graph())
Graph_list[13].add_vertices(5)
Graph_list[13].add_edges([(0,2),(0,3),(0,4),(1,3),(1,4),(2,4),(3,4)])

Graph_list.append(igh.Graph())
Graph_list[14].add_vertices(5)
Graph_list[14].add_edges([(0,2),(0,3),(0,4),(1,4),(2,3),(2,4)])

Graph_list.append(igh.Graph())
Graph_list[15].add_vertices(5)
Graph_list[15].add_edges([(0,2),(0,3),(0,4),(1,4),(2,3),(2,4),(3,4)])

Graph_list.append(igh.Graph())
Graph_list[16].add_vertices(5)
Graph_list[16].add_edges([(0,2),(0,3),(0,4),(1,3),(1,4),(2,3),(2,4),(3,4)])

Graph_list.append(igh.Graph())
Graph_list[17].add_vertices(5)
Graph_list[17].add_edges([(0,2),(0,3),(0,4),(1,2),(1,3),(1,4),(2,4)])

Graph_list.append(igh.Graph())
Graph_list[18].add_vertices(5)
Graph_list[18].add_edges([(0,2),(0,3),(0,4),(1,2),(1,3),(1,4),(2,4),(3,4)])

Graph_list.append(igh.Graph())
Graph_list[19].add_vertices(5)
Graph_list[19].add_edges([(0,2),(0,3),(0,4),(1,2),(1,3),(1,4),(2,3),(2,4),(3,4)])

Graph_list.append(igh.Graph())
Graph_list[20].add_vertices(5)
Graph_list[20].add_edges([(0,1),(0,2),(0,3),(0,4),(1,2),(1,3),(1,4),(2,3),(2,4),(3,4)])


W_constant=[24,8,40,20,18,68,60,156,2,12,64,10,46,124,40,108,244,108,232,432,720]
G = igh.read(argv[1],"ncol").as_undirected()

step_num=int(argv[2])    #number of steps for the random walk
iter_num=1        #number of runs for the experiment
sumccc=[0.0]*21



counter20 = multiprocessing.Value('d', 0.0)
counter19 = multiprocessing.Value('d', 0.0)
counter18 = multiprocessing.Value('d', 0.0)
counter17 = multiprocessing.Value('d', 0.0)
counter16 = multiprocessing.Value('d', 0.0)
counter15 = multiprocessing.Value('d', 0.0)
counter14 = multiprocessing.Value('d', 0.0)
counter13 = multiprocessing.Value('d', 0.0)
counter12 = multiprocessing.Value('d', 0.0)

counter11 = multiprocessing.Value('d', 0.0)
counter10 = multiprocessing.Value('d', 0.0)
counter9 = multiprocessing.Value('d', 0.0)
counter8 = multiprocessing.Value('d', 0.0)
counter7 = multiprocessing.Value('d', 0.0)
counter6 = multiprocessing.Value('d', 0.0)
counter5 = multiprocessing.Value('d', 0.0)
counter4 = multiprocessing.Value('d', 0.0)
counter3 = multiprocessing.Value('d', 0.0)
counter2 = multiprocessing.Value('d', 0.0)
counter1 = multiprocessing.Value('d', 0.0)
counter0 = multiprocessing.Value('d', 0.0)


def calc(sign, lock ):
	for indx in range(iter_num):
		lst_motif = [0]*21
		w=rdmW.random_walk(step_num+1000, G, 50)
		i=1000

		while i<step_num+1000:
			if len(list(set(w[(i-2):i+1])))==3: 
				m=rdm.randint(0,G.degree(w[i-1])+G.degree(w[i]))
				if m<G.degree(w[i-1]):
					node4=rdm.choice(G.neighbors(w[i-1]))
				else:
					node4=rdm.choice(G.neighbors(w[i]))
				n=rdm.randint(0,G.degree(w[i-1])+G.degree(w[i])+G.degree(node4))
				if n<G.degree(w[i-1]):
					node5=rdm.choice(G.neighbors(w[i-1]))
				elif n<G.degree(w[i-1])+G.degree(w[i]):
					node5=rdm.choice(G.neighbors(w[i]))
				else:
					node5=rdm.choice(G.neighbors(node4))
				temp=G.subgraph(w[(i-2):i+1]+[node4]+[node5])
				dg_prod=G.degree(w[i-1])*(G.degree(w[i-1])+G.degree(w[i]))*(G.degree(w[i-1])+G.degree(w[i])+G.degree(node4))
				if len(list(set(w[(i-2):i+1]+[node4]+[node5])))==5:
					for graph_in in range(21):
						if  temp.isomorphic(Graph_list[graph_in]):
							lst_motif[graph_in]+=dg_prod
							break
			i+=1

		x=[G.ecount()*2*(a/(b*step_num)) for a,b in zip(lst_motif,W_constant)]
	    
		lock.acquire()
            
                 


		counter20.value+=(x[20])
		counter19.value+=(x[19])
		counter18.value+=(x[18])
		counter17.value+=(x[17])
		counter16.value+=(x[16])
		counter15.value+=(x[15])
		counter14.value+=(x[14])
		counter13.value+=(x[13])
		counter12.value+=(x[12])
		counter11.value+=(x[11])
		counter10.value+=(x[10])
		counter9.value+=(x[9])
		counter8.value+=(x[8])
		counter7.value+=(x[7])
		counter6.value+=(x[6])
		counter5.value+=(x[5])
		counter4.value+=(x[4])
		counter3.value+=(x[3])
		counter2.value+=(x[2])
		counter1.value+=(x[1])
		counter0.value+=(x[0])

            
		lock.release()
'''
	    for item in x:
               print item
            
		fwrite.close()
		f.close()
process = multiprocessing.Process(target=calc,args=())
process.start()
process.join()
'''

record = []
starttime = datetime.datetime.now()

lock = multiprocessing.Lock()
numcpus=1
numcpus2=int(numcpus)
for i in range(numcpus2):
    process = multiprocessing.Process(target=calc,args=('process',lock))
    process.start()
    record.append(process)

for process in record:
    process.join()

endtime = datetime.datetime.now()
temp=[0.0]*21


temp[20]=counter20.value/(numcpus2)
temp[19]=counter19.value/(numcpus2)
temp[18]=counter18.value/(numcpus2)
temp[17]=counter17.value/(numcpus2)
temp[16]=counter16.value/(numcpus2)
temp[15]=counter15.value/(numcpus2)
temp[14]=counter14.value/(numcpus2)
temp[13]=counter13.value/(numcpus2)
temp[12]=counter12.value/(numcpus2)
temp[11]=counter11.value/(numcpus2)
temp[10]=counter10.value/(numcpus2)
temp[9]=counter9.value/(numcpus2)
temp[8]=counter8.value/(numcpus2)
temp[7]=counter7.value/(numcpus2)
temp[6]=counter6.value/(numcpus2)
temp[5]=counter5.value/(numcpus2)
temp[4]=counter4.value/(numcpus2)
temp[3]=counter3.value/(numcpus2)
temp[2]=counter2.value/(numcpus2)
temp[1]=counter1.value/(numcpus2)
temp[0]=counter0.value/(numcpus2)
temp.sort()
count0=0
j=0
while(j<21):
    if temp[j]==0:
        count0=count0+1
    j=j+1
print ("0Subgraph count %d"%count0)
i=20
while(i>=0):
    print(temp[i])
    i=i-1
print (endtime - starttime).total_seconds()

