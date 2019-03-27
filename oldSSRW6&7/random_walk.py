'''
Random Walk
@author: Guyue Han
'''
import random as rdm

def random_walk(steps,G,startnode):
    randW_list=[startnode];
    currNode=startnode;
    for indx in range(steps-1):
        currNode=rdm.choice(G.neighbors(currNode));
        randW_list.append(currNode);
    return randW_list