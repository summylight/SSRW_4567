from __future__ import division
import random as rdm
import random_walk as rdmW
import igraph as igh
import string 
import multiprocessing
import sys
import datetime
Graph_list=[]
Graph_list.append(igh.Graph())
Graph_list[0].add_vertices(6)
Graph_list[0].add_edges([(0,5),(1,5),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[1].add_vertices(6)
Graph_list[1].add_edges([(0,4),(0,5),(1,5),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[2].add_vertices(6)
Graph_list[2].add_edges([(0,4),(0,5),(1,5),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[3].add_vertices(6)
Graph_list[3].add_edges([(0,4),(0,5),(1,4),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[4].add_vertices(6)
Graph_list[4].add_edges([(0,4),(1,4),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[5].add_vertices(6)
Graph_list[5].add_edges([(0,4),(0,5),(1,4),(1,5),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[6].add_vertices(6)
Graph_list[6].add_edges([(0,4),(0,5),(1,4),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[7].add_vertices(6)
Graph_list[7].add_edges([(0,4),(0,5),(1,4),(1,5),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[8].add_vertices(6)
Graph_list[8].add_edges([(0,4),(0,5),(1,4),(1,5),(2,4),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[9].add_vertices(6)
Graph_list[9].add_edges([(0,4),(0,5),(1,4),(1,5),(2,4),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[10].add_vertices(6)
Graph_list[10].add_edges([(0,4),(0,5),(1,4),(1,5),(2,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[11].add_vertices(6)
Graph_list[11].add_edges([(0,4),(0,5),(1,4),(1,5),(2,4),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[12].add_vertices(6)
Graph_list[12].add_edges([(0,4),(0,5),(1,4),(1,5),(2,4),(2,5),(3,4),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[13].add_vertices(6)
Graph_list[13].add_edges([(0,4),(0,5),(1,4),(1,5),(2,4),(2,5),(3,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[14].add_vertices(6)
Graph_list[14].add_edges([(0,3),(0,5),(1,4),(1,5),(2,5)])
Graph_list.append(igh.Graph())
Graph_list[15].add_vertices(6)
Graph_list[15].add_edges([(0,3),(0,5),(1,4),(1,5),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[16].add_vertices(6)
Graph_list[16].add_edges([(0,3),(0,5),(1,4),(1,5),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[17].add_vertices(6)
Graph_list[17].add_edges([(0,3),(0,4),(0,5),(1,4),(1,5),(2,5)])
Graph_list.append(igh.Graph())
Graph_list[18].add_vertices(6)
Graph_list[18].add_edges([(0,3),(0,4),(1,4),(1,5),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[19].add_vertices(6)
Graph_list[19].add_edges([(0,3),(0,4),(0,5),(1,4),(2,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[20].add_vertices(6)
Graph_list[20].add_edges([(0,3),(0,4),(0,5),(1,4),(1,5),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[21].add_vertices(6)
Graph_list[21].add_edges([(0,3),(0,4),(0,5),(1,4),(1,5),(2,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[22].add_vertices(6)
Graph_list[22].add_edges([(0,3),(0,4),(0,5),(1,4),(1,5),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[23].add_vertices(6)
Graph_list[23].add_edges([(0,3),(0,5),(1,4),(1,5),(2,4)])
Graph_list.append(igh.Graph())
Graph_list[24].add_vertices(6)
Graph_list[24].add_edges([(0,3),(0,5),(1,4),(1,5),(2,4),(2,5)])
Graph_list.append(igh.Graph())
Graph_list[25].add_vertices(6)
Graph_list[25].add_edges([(0,3),(0,5),(1,4),(1,5),(2,4),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[26].add_vertices(6)
Graph_list[26].add_edges([(0,3),(0,5),(1,4),(1,5),(2,4),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[27].add_vertices(6)
Graph_list[27].add_edges([(0,3),(0,5),(1,4),(2,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[28].add_vertices(6)
Graph_list[28].add_edges([(0,3),(0,5),(1,4),(1,5),(2,4),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[29].add_vertices(6)
Graph_list[29].add_edges([(0,3),(0,5),(1,4),(1,5),(2,4),(2,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[30].add_vertices(6)
Graph_list[30].add_edges([(0,3),(0,5),(1,4),(1,5),(2,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[31].add_vertices(6)
Graph_list[31].add_edges([(0,3),(0,5),(1,4),(1,5),(2,4),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[32].add_vertices(6)
Graph_list[32].add_edges([(0,3),(0,4),(0,5),(1,5),(2,5),(3,4),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[33].add_vertices(6)
Graph_list[33].add_edges([(0,3),(0,4),(0,5),(1,5),(2,5),(3,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[34].add_vertices(6)
Graph_list[34].add_edges([(0,3),(0,4),(1,4),(1,5),(2,4),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[35].add_vertices(6)
Graph_list[35].add_edges([(0,3),(0,4),(0,5),(1,4),(1,5),(2,4),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[36].add_vertices(6)
Graph_list[36].add_edges([(0,3),(0,4),(0,5),(1,4),(1,5),(2,4),(2,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[37].add_vertices(6)
Graph_list[37].add_edges([(0,3),(0,4),(0,5),(1,4),(1,5),(2,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[38].add_vertices(6)
Graph_list[38].add_edges([(0,3),(0,4),(1,4),(1,5),(2,4),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[39].add_vertices(6)
Graph_list[39].add_edges([(0,3),(0,4),(0,5),(1,4),(1,5),(2,4),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[40].add_vertices(6)
Graph_list[40].add_edges([(0,3),(0,4),(0,5),(1,4),(1,5),(2,5),(3,4),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[41].add_vertices(6)
Graph_list[41].add_edges([(0,3),(0,4),(0,5),(1,4),(2,5),(3,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[42].add_vertices(6)
Graph_list[42].add_edges([(0,3),(0,4),(0,5),(1,4),(1,5),(2,5),(3,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[43].add_vertices(6)
Graph_list[43].add_edges([(0,3),(0,4),(0,5),(1,4),(1,5),(2,4),(2,5),(3,4),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[44].add_vertices(6)
Graph_list[44].add_edges([(0,3),(0,4),(0,5),(1,4),(1,5),(2,4),(2,5),(3,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[45].add_vertices(6)
Graph_list[45].add_edges([(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,5)])
Graph_list.append(igh.Graph())
Graph_list[46].add_vertices(6)
Graph_list[46].add_edges([(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[47].add_vertices(6)
Graph_list[47].add_edges([(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[48].add_vertices(6)
Graph_list[48].add_edges([(0,3),(0,4),(1,3),(1,5),(2,4),(2,5)])
Graph_list.append(igh.Graph())
Graph_list[49].add_vertices(6)
Graph_list[49].add_edges([(0,3),(0,4),(0,5),(1,3),(1,5),(2,4),(2,5)])
Graph_list.append(igh.Graph())
Graph_list[50].add_vertices(6)
Graph_list[50].add_edges([(0,3),(0,4),(0,5),(1,3),(2,4),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[51].add_vertices(6)
Graph_list[51].add_edges([(0,3),(0,4),(1,3),(1,5),(2,4),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[52].add_vertices(6)
Graph_list[52].add_edges([(0,3),(0,4),(0,5),(1,3),(2,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[53].add_vertices(6)
Graph_list[53].add_edges([(0,3),(0,4),(1,3),(1,5),(2,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[54].add_vertices(6)
Graph_list[54].add_edges([(0,3),(0,4),(0,5),(1,3),(1,5),(2,4),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[55].add_vertices(6)
Graph_list[55].add_edges([(0,3),(0,4),(0,5),(1,3),(1,5),(2,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[56].add_vertices(6)
Graph_list[56].add_edges([(0,3),(0,4),(1,3),(1,5),(2,4),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[57].add_vertices(6)
Graph_list[57].add_edges([(0,3),(0,4),(0,5),(1,3),(1,5),(2,4),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[58].add_vertices(6)
Graph_list[58].add_edges([(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,4),(2,5)])
Graph_list.append(igh.Graph())
Graph_list[59].add_vertices(6)
Graph_list[59].add_edges([(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,4),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[60].add_vertices(6)
Graph_list[60].add_edges([(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,4),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[61].add_vertices(6)
Graph_list[61].add_edges([(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,4),(2,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[62].add_vertices(6)
Graph_list[62].add_edges([(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,4),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[63].add_vertices(6)
Graph_list[63].add_edges([(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,5),(3,4),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[64].add_vertices(6)
Graph_list[64].add_edges([(0,3),(0,4),(0,5),(1,3),(1,4),(2,5),(3,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[65].add_vertices(6)
Graph_list[65].add_edges([(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,5),(3,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[66].add_vertices(6)
Graph_list[66].add_edges([(0,3),(0,4),(0,5),(1,3),(1,5),(2,4),(2,5),(3,4),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[67].add_vertices(6)
Graph_list[67].add_edges([(0,3),(0,4),(1,3),(1,5),(2,4),(2,5),(3,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[68].add_vertices(6)
Graph_list[68].add_edges([(0,3),(0,4),(0,5),(1,3),(1,5),(2,4),(2,5),(3,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[69].add_vertices(6)
Graph_list[69].add_edges([(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,4),(2,5),(3,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[70].add_vertices(6)
Graph_list[70].add_edges([(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,3),(2,4),(2,5)])
Graph_list.append(igh.Graph())
Graph_list[71].add_vertices(6)
Graph_list[71].add_edges([(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,3),(2,4),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[72].add_vertices(6)
Graph_list[72].add_edges([(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,3),(2,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[73].add_vertices(6)
Graph_list[73].add_edges([(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,3),(2,4),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[74].add_vertices(6)
Graph_list[74].add_edges([(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,3),(2,4),(2,5),(3,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[75].add_vertices(6)
Graph_list[75].add_edges([(0,2),(0,4),(0,5),(1,3),(1,5),(2,4),(2,5)])
Graph_list.append(igh.Graph())
Graph_list[76].add_vertices(6)
Graph_list[76].add_edges([(0,2),(0,4),(0,5),(1,3),(1,5),(2,4),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[77].add_vertices(6)
Graph_list[77].add_edges([(0,2),(0,4),(0,5),(1,3),(1,5),(2,4),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[78].add_vertices(6)
Graph_list[78].add_edges([(0,2),(0,4),(0,5),(1,3),(1,5),(2,4),(2,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[79].add_vertices(6)
Graph_list[79].add_edges([(0,2),(0,4),(0,5),(1,3),(1,5),(2,4),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[80].add_vertices(6)
Graph_list[80].add_edges([(0,2),(0,4),(0,5),(1,3),(1,4),(1,5),(2,4),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[81].add_vertices(6)
Graph_list[81].add_edges([(0,2),(0,4),(0,5),(1,3),(1,4),(1,5),(2,4),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[82].add_vertices(6)
Graph_list[82].add_edges([(0,2),(0,4),(0,5),(1,3),(1,4),(1,5),(2,4),(2,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[83].add_vertices(6)
Graph_list[83].add_edges([(0,2),(0,4),(0,5),(1,3),(1,4),(1,5),(2,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[84].add_vertices(6)
Graph_list[84].add_edges([(0,2),(0,4),(0,5),(1,3),(1,4),(2,4),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[85].add_vertices(6)
Graph_list[85].add_edges([(0,2),(0,4),(0,5),(1,3),(1,4),(1,5),(2,4),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[86].add_vertices(6)
Graph_list[86].add_edges([(0,2),(0,4),(0,5),(1,3),(1,4),(1,5),(2,4),(2,5),(3,4),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[87].add_vertices(6)
Graph_list[87].add_edges([(0,2),(0,4),(0,5),(1,3),(1,4),(1,5),(2,4),(2,5),(3,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[88].add_vertices(6)
Graph_list[88].add_edges([(0,2),(0,3),(0,5),(1,3),(1,4),(1,5),(2,4),(2,5)])
Graph_list.append(igh.Graph())
Graph_list[89].add_vertices(6)
Graph_list[89].add_edges([(0,2),(0,3),(0,5),(1,3),(1,4),(1,5),(2,4),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[90].add_vertices(6)
Graph_list[90].add_edges([(0,2),(0,3),(0,5),(1,3),(1,4),(1,5),(2,4),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[91].add_vertices(6)
Graph_list[91].add_edges([(0,2),(0,3),(0,5),(1,3),(1,4),(1,5),(2,4),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[92].add_vertices(6)
Graph_list[92].add_edges([(0,2),(0,3),(0,4),(1,3),(1,4),(1,5),(2,4),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[93].add_vertices(6)
Graph_list[93].add_edges([(0,2),(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,4),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[94].add_vertices(6)
Graph_list[94].add_edges([(0,2),(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[95].add_vertices(6)
Graph_list[95].add_edges([(0,2),(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,4),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[96].add_vertices(6)
Graph_list[96].add_edges([(0,2),(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,4),(2,5),(3,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[97].add_vertices(6)
Graph_list[97].add_edges([(0,2),(0,3),(0,4),(0,5),(1,4),(1,5),(2,3),(2,4),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[98].add_vertices(6)
Graph_list[98].add_edges([(0,2),(0,3),(0,4),(0,5),(1,4),(1,5),(2,3),(2,4),(2,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[99].add_vertices(6)
Graph_list[99].add_edges([(0,2),(0,3),(0,4),(0,5),(1,4),(1,5),(2,3),(2,4),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[100].add_vertices(6)
Graph_list[100].add_edges([(0,2),(0,3),(0,4),(0,5),(1,5),(2,3),(2,4),(2,5),(3,4),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[101].add_vertices(6)
Graph_list[101].add_edges([(0,2),(0,3),(0,4),(0,5),(1,5),(2,3),(2,4),(2,5),(3,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[102].add_vertices(6)
Graph_list[102].add_edges([(0,2),(0,3),(0,4),(0,5),(1,4),(1,5),(2,3),(2,4),(2,5),(3,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[103].add_vertices(6)
Graph_list[103].add_edges([(0,2),(0,3),(0,4),(0,5),(1,3),(1,4),(1,5),(2,3),(2,4),(2,5),(3,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[104].add_vertices(6)
Graph_list[104].add_edges([(0,2),(0,3),(0,4),(0,5),(1,2),(1,3),(1,4),(1,5),(2,4),(2,5),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[105].add_vertices(6)
Graph_list[105].add_edges([(0,2),(0,3),(0,4),(0,5),(1,2),(1,3),(1,4),(1,5),(2,4),(2,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[106].add_vertices(6)
Graph_list[106].add_edges([(0,2),(0,3),(0,4),(0,5),(1,2),(1,3),(1,4),(2,4),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[107].add_vertices(6)
Graph_list[107].add_edges([(0,2),(0,3),(0,4),(0,5),(1,2),(1,3),(1,4),(1,5),(2,4),(2,5),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[108].add_vertices(6)
Graph_list[108].add_edges([(0,2),(0,3),(0,4),(0,5),(1,2),(1,3),(1,4),(1,5),(2,4),(2,5),(3,4),(3,5)])
Graph_list.append(igh.Graph())
Graph_list[109].add_vertices(6)
Graph_list[109].add_edges([(0,2),(0,3),(0,4),(0,5),(1,2),(1,3),(1,4),(1,5),(2,4),(2,5),(3,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[110].add_vertices(6)
Graph_list[110].add_edges([(0,2),(0,3),(0,4),(0,5),(1,2),(1,3),(1,4),(1,5),(2,3),(2,4),(2,5),(3,4),(3,5),(4,5)])
Graph_list.append(igh.Graph())
Graph_list[111].add_vertices(6)
Graph_list[111].add_edges([(0,1),(0,2),(0,3),(0,4),(0,5),(1,2),(1,3),(1,4),(1,5),(2,3),(2,4),(2,5),(3,4),(3,5),(4,5)])


W_constant=[120,42,204,10,32,104,84,340,40,216,188,600,576,1344,12,66,336,58,36,36,186,134,552,2,28,14,24,52,160,104,132,548,188,528,120,412,296,358,420,1024,356,264,892,912,1984,144,320,872,12,120,88,80,68,112,308,230,340,904,352,232,726,704,1656,610,580,1364,756,792,1640,3012,792,1452,1504,2892,5112,52,80,292,156,840,256,672,440,658,608,1520,1440,2928,280,204,596,1500,612,1354,1356,2684,4660,1274,1272,2596,978,2016,4428,7464,2548,2352,2448,4452,4368,7328,11520,17280]
fwrite = open("6_node_WRW_slashdot_5W.txt", "w")
G = igh.read('p2p-Gnutella062.txt').as_undirected()
f = open('startingnode_slashdot.txt', 'r')

step_num=100000    #number of steps for the random walk
iter_num=1        #number of runs for the experiment
sumccc=[0.0]*112

counter111 = multiprocessing.Value('d', 0.0)
counter110 = multiprocessing.Value('d', 0.0)
counter109 = multiprocessing.Value('d', 0.0)
counter108 = multiprocessing.Value('d', 0.0)
counter107 = multiprocessing.Value('d', 0.0)
counter106 = multiprocessing.Value('d', 0.0)
counter105 = multiprocessing.Value('d', 0.0)
counter104 = multiprocessing.Value('d', 0.0)
counter103 = multiprocessing.Value('d', 0.0)
counter102 = multiprocessing.Value('d', 0.0)

counter101 = multiprocessing.Value('d', 0.0)
counter100 = multiprocessing.Value('d', 0.0)
counter99 = multiprocessing.Value('d', 0.0)
counter98 = multiprocessing.Value('d', 0.0)
counter97 = multiprocessing.Value('d', 0.0)
counter96 = multiprocessing.Value('d', 0.0)
counter95 = multiprocessing.Value('d', 0.0)
counter94 = multiprocessing.Value('d', 0.0)
counter93 = multiprocessing.Value('d', 0.0)
counter92 = multiprocessing.Value('d', 0.0)

counter91 = multiprocessing.Value('d', 0.0)
counter90 = multiprocessing.Value('d', 0.0)
counter89 = multiprocessing.Value('d', 0.0)
counter88 = multiprocessing.Value('d', 0.0)
counter87 = multiprocessing.Value('d', 0.0)
counter86 = multiprocessing.Value('d', 0.0)
counter85 = multiprocessing.Value('d', 0.0)
counter84 = multiprocessing.Value('d', 0.0)
counter83 = multiprocessing.Value('d', 0.0)
counter82 = multiprocessing.Value('d', 0.0)

counter81 = multiprocessing.Value('d', 0.0)
counter80 = multiprocessing.Value('d', 0.0)
counter79 = multiprocessing.Value('d', 0.0)
counter78 = multiprocessing.Value('d', 0.0)
counter77 = multiprocessing.Value('d', 0.0)
counter76 = multiprocessing.Value('d', 0.0)
counter75 = multiprocessing.Value('d', 0.0)
counter74 = multiprocessing.Value('d', 0.0)
counter73 = multiprocessing.Value('d', 0.0)
counter72 = multiprocessing.Value('d', 0.0)

counter71 = multiprocessing.Value('d', 0.0)
counter70 = multiprocessing.Value('d', 0.0)
counter69 = multiprocessing.Value('d', 0.0)
counter68 = multiprocessing.Value('d', 0.0)
counter67 = multiprocessing.Value('d', 0.0)
counter66 = multiprocessing.Value('d', 0.0)
counter65 = multiprocessing.Value('d', 0.0)
counter64 = multiprocessing.Value('d', 0.0)
counter63 = multiprocessing.Value('d', 0.0)
counter62 = multiprocessing.Value('d', 0.0)

counter61 = multiprocessing.Value('d', 0.0)
counter60 = multiprocessing.Value('d', 0.0)
counter59 = multiprocessing.Value('d', 0.0)
counter58 = multiprocessing.Value('d', 0.0)
counter57 = multiprocessing.Value('d', 0.0)
counter56 = multiprocessing.Value('d', 0.0)
counter55 = multiprocessing.Value('d', 0.0)
counter54 = multiprocessing.Value('d', 0.0)
counter53 = multiprocessing.Value('d', 0.0)
counter52 = multiprocessing.Value('d', 0.0)

counter61 = multiprocessing.Value('d', 0.0)
counter60 = multiprocessing.Value('d', 0.0)
counter59 = multiprocessing.Value('d', 0.0)
counter58 = multiprocessing.Value('d', 0.0)
counter57 = multiprocessing.Value('d', 0.0)
counter56 = multiprocessing.Value('d', 0.0)
counter55 = multiprocessing.Value('d', 0.0)
counter54 = multiprocessing.Value('d', 0.0)
counter53 = multiprocessing.Value('d', 0.0)
counter52 = multiprocessing.Value('d', 0.0)

counter51 = multiprocessing.Value('d', 0.0)
counter50 = multiprocessing.Value('d', 0.0)
counter49 = multiprocessing.Value('d', 0.0)
counter48 = multiprocessing.Value('d', 0.0)
counter47 = multiprocessing.Value('d', 0.0)
counter46 = multiprocessing.Value('d', 0.0)
counter45 = multiprocessing.Value('d', 0.0)
counter44 = multiprocessing.Value('d', 0.0)
counter43 = multiprocessing.Value('d', 0.0)
counter42 = multiprocessing.Value('d', 0.0)

counter41 = multiprocessing.Value('d', 0.0)
counter40 = multiprocessing.Value('d', 0.0)
counter39 = multiprocessing.Value('d', 0.0)
counter38 = multiprocessing.Value('d', 0.0)
counter37 = multiprocessing.Value('d', 0.0)
counter36 = multiprocessing.Value('d', 0.0)
counter35 = multiprocessing.Value('d', 0.0)
counter34 = multiprocessing.Value('d', 0.0)
counter33 = multiprocessing.Value('d', 0.0)
counter32 = multiprocessing.Value('d', 0.0)

counter31 = multiprocessing.Value('d', 0.0)
counter30 = multiprocessing.Value('d', 0.0)
counter29 = multiprocessing.Value('d', 0.0)
counter28 = multiprocessing.Value('d', 0.0)
counter27 = multiprocessing.Value('d', 0.0)
counter26 = multiprocessing.Value('d', 0.0)
counter25 = multiprocessing.Value('d', 0.0)
counter24 = multiprocessing.Value('d', 0.0)
counter23 = multiprocessing.Value('d', 0.0)
counter22 = multiprocessing.Value('d', 0.0)

counter21 = multiprocessing.Value('d', 0.0)
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
	    lst_motif = [0]*112
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
		    r=rdm.randint(0,G.degree(w[i-1])+G.degree(w[i])+G.degree(node4)+G.degree(node5))
		    if r<G.degree(w[i-1]):
		        node6=rdm.choice(G.neighbors(w[i-1]))
		    elif r<G.degree(w[i-1])+G.degree(w[i]):
		        node6=rdm.choice(G.neighbors(w[i]))
		    elif r<G.degree(w[i-1])+G.degree(w[i])+G.degree(node4)  :
		        node6=rdm.choice(G.neighbors(node4)) 
		    else:
		        node6=rdm.choice(G.neighbors(node5)) 
		    temp=G.subgraph(w[(i-2):i+1]+[node4]+[node5]+[node6])
		    dg_prod=G.degree(w[i-1])*(G.degree(w[i-1])+G.degree(w[i]))*(G.degree(w[i-1])+G.degree(w[i])+G.degree(node4))*(G.degree(w[i-1])+G.degree(w[i])+G.degree(node4)+G.degree(node5))
		    if len(list(set(w[(i-2):i+1]+[node4]+[node5]+[node6])))==6:
		      for graph_in in range(112):  
		        if  temp.isomorphic(Graph_list[graph_in]):
		             lst_motif[graph_in]+=dg_prod
		             break
		i+=1
		    
	      
	    denom=sum([a/b for a,b in zip(lst_motif,W_constant)])
	   

	    x=[31525*2*(a/(b*step_num)) for a,b in zip(lst_motif,W_constant)]
	    
            lock.acquire()
            
                 

            counter111.value+=(x[111])
            counter110.value+=(x[110])
            counter109.value+=(x[109])
            counter108.value+=(x[108])
            counter107.value+=(x[107])
            counter106.value+=(x[106])
            counter105.value+=(x[105])
            counter104.value+=(x[104])
            counter103.value+=(x[103])
            counter102.value+=(x[102])
            counter101.value+=(x[101])
	    counter100.value+=(x[100])
	    counter99.value+=(x[99])
	    counter98.value+=(x[98])
            counter97.value+=(x[97])
	    counter96.value+=(x[96])
	    counter95.value+=(x[95])
	    counter94.value+=(x[94])
	    counter93.value+=(x[93])
	    counter92.value+=(x[92])
	    counter91.value+=(x[91])
            counter90.value+=(x[90])
	    counter89.value+=(x[89])
	    counter88.value+=(x[88])
	    counter87.value+=(x[87])
	    counter86.value+=(x[86])
	    counter85.value+=(x[85])
	    counter84.value+=(x[84])
	    counter83.value+=(x[83])
	    counter82.value+=(x[82])
	    counter81.value+=(x[81])
	    counter80.value+=(x[80])
	    counter79.value+=(x[79])
	    counter78.value+=(x[78])
	    counter77.value+=(x[77])
	    counter76.value+=(x[76])
	    counter75.value+=(x[75])
	    counter74.value+=(x[74])
	    counter73.value+=(x[73])
	    counter72.value+=(x[72])
	    counter71.value+=(x[71])
	    counter70.value+=(x[70])
	    counter69.value+=(x[69])
	    counter68.value+=(x[68])
	    counter67.value+=(x[67])
	    counter66.value+=(x[66])
	    counter65.value+=(x[65])
	    counter64.value+=(x[64])
	    counter63.value+=(x[63])
	    counter62.value+=(x[62])
	    counter61.value+=(x[61])
	    counter60.value+=(x[60])
	    counter59.value+=(x[59])
	    counter58.value+=(x[58])
	    counter57.value+=(x[57])
	    counter56.value+=(x[56])
	    counter55.value+=(x[55])
	    counter54.value+=(x[54])
	    counter53.value+=(x[53])
	    counter52.value+=(x[52])
	    counter51.value+=(x[51])
	    counter50.value+=(x[50])
	    counter49.value+=(x[49])
	    counter48.value+=(x[48])
	    counter47.value+=(x[47])
	    counter46.value+=(x[46])
	    counter45.value+=(x[45])
	    counter44.value+=(x[44])
	    counter43.value+=(x[43])
	    counter42.value+=(x[42])
	    counter41.value+=(x[41])
	    counter40.value+=(x[40])
	    counter39.value+=(x[39])
	    counter38.value+=(x[38])
	    counter37.value+=(x[37])
	    counter36.value+=(x[36])
	    counter35.value+=(x[35])
	    counter34.value+=(x[34])
	    counter33.value+=(x[33])
	    counter32.value+=(x[32])
	    counter31.value+=(x[31])
	    counter30.value+=(x[30])
            counter29.value+=(x[29])
	    counter28.value+=(x[28])
	    counter27.value+=(x[27])
	    counter26.value+=(x[26])
	    counter25.value+=(x[25])
	    counter24.value+=(x[24])
	    counter23.value+=(x[23])
	    counter22.value+=(x[22])
	    counter21.value+=(x[21])
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
            '''
            fwrite.close()
            f.close()
'''
process = multiprocessing.Process(target=calc,args=())
process.start()
process.join()
'''
record = []
starttime = datetime.datetime.now()

lock = multiprocessing.Lock()
numcpus=sys.argv[1]
numcpus2=int(numcpus)
for i in range(numcpus2):
    process = multiprocessing.Process(target=calc,args=('process',lock))
    process.start()
    record.append(process)

for process in record:
    process.join()

endtime = datetime.datetime.now()
temp=[0.0]*112
print numcpus2

temp[111]=counter111.value/(numcpus2)
temp[110]=counter110.value/(numcpus2)
temp[109]=counter109.value/(numcpus2)
temp[108]=counter108.value/(numcpus2)
temp[107]=counter107.value/(numcpus2)
temp[106]=counter106.value/(numcpus2)
temp[105]=counter105.value/(numcpus2)
temp[104]=counter104.value/(numcpus2)
temp[103]=counter103.value/(numcpus2)
temp[102]=counter102.value/(numcpus2)
temp[101]=counter101.value/(numcpus2)
temp[100]=counter100.value/(numcpus2)
temp[99]=counter99.value/(numcpus2)
temp[98]=counter98.value/(numcpus2)
temp[97]=counter97.value/(numcpus2)
temp[96]=counter96.value/(numcpus2)
temp[95]=counter95.value/(numcpus2)
temp[94]=counter94.value/(numcpus2)
temp[93]=counter93.value/(numcpus2)
temp[92]=counter92.value/(numcpus2)
temp[91]=counter91.value/(numcpus2)
temp[90]=counter90.value/(numcpus2)
temp[89]=counter89.value/(numcpus2)
temp[88]=counter88.value/(numcpus2)
temp[87]=counter87.value/(numcpus2)
temp[86]=counter86.value/(numcpus2)
temp[85]=counter85.value/(numcpus2)
temp[84]=counter84.value/(numcpus2)
temp[83]=counter83.value/(numcpus2)
temp[82]=counter82.value/(numcpus2)
temp[81]=counter81.value/(numcpus2)
temp[80]=counter80.value/(numcpus2)
temp[79]=counter79.value/(numcpus2)
temp[78]=counter78.value/(numcpus2)
temp[77]=counter77.value/(numcpus2)
temp[76]=counter76.value/(numcpus2)
temp[75]=counter75.value/(numcpus2)
temp[74]=counter74.value/(numcpus2)
temp[73]=counter73.value/(numcpus2)
temp[72]=counter72.value/(numcpus2)
temp[71]=counter71.value/(numcpus2)
temp[70]=counter70.value/(numcpus2)
temp[69]=counter69.value/(numcpus2)
temp[68]=counter68.value/(numcpus2)
temp[67]=counter67.value/(numcpus2)
temp[66]=counter66.value/(numcpus2)
temp[65]=counter65.value/(numcpus2)
temp[64]=counter64.value/(numcpus2)
temp[63]=counter63.value/(numcpus2)
temp[62]=counter62.value/(numcpus2)
temp[61]=counter61.value/(numcpus2)
temp[60]=counter60.value/(numcpus2)
temp[59]=counter59.value/(numcpus2)
temp[58]=counter58.value/(numcpus2)
temp[57]=counter57.value/(numcpus2)
temp[56]=counter56.value/(numcpus2)
temp[55]=counter55.value/(numcpus2)
temp[54]=counter54.value/(numcpus2)
temp[53]=counter53.value/(numcpus2)
temp[52]=counter52.value/(numcpus2)
temp[51]=counter51.value/(numcpus2)
temp[50]=counter50.value/(numcpus2)
temp[49]=counter49.value/(numcpus2)
temp[48]=counter48.value/(numcpus2)
temp[47]=counter47.value/(numcpus2)
temp[46]=counter46.value/(numcpus2)
temp[45]=counter45.value/(numcpus2)
temp[44]=counter44.value/(numcpus2)
temp[43]=counter43.value/(numcpus2)
temp[42]=counter42.value/(numcpus2)
temp[41]=counter41.value/(numcpus2)
temp[40]=counter40.value/(numcpus2)
temp[39]=counter39.value/(numcpus2)
temp[38]=counter38.value/(numcpus2)
temp[37]=counter37.value/(numcpus2)
temp[36]=counter36.value/(numcpus2)
temp[35]=counter35.value/(numcpus2)
temp[34]=counter34.value/(numcpus2)
temp[33]=counter33.value/(numcpus2)
temp[32]=counter32.value/(numcpus2)
temp[31]=counter31.value/(numcpus2)
temp[30]=counter30.value/(numcpus2)
temp[29]=counter29.value/(numcpus2)
temp[28]=counter28.value/(numcpus2)
temp[27]=counter27.value/(numcpus2)
temp[26]=counter26.value/(numcpus2)
temp[25]=counter25.value/(numcpus2)
temp[24]=counter24.value/(numcpus2)
temp[23]=counter23.value/(numcpus2)
temp[22]=counter22.value/(numcpus2)
temp[21]=counter21.value/(numcpus2)
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
'temp.sort()
i=111
while(i>100):
    print temp[i]
    i=i-1
print (endtime - starttime).seconds


