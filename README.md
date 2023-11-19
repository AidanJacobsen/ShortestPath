# ShortestPath

In this assignment, I implemented Dijkstra's algorithm to find the shortest path from
one node of a graph to another node in the graph.  Each node can be assigned a name and
the program will take an input graph in the below file format.  Using a single graph
description file, the program than then be run to find the shortest path between any two
node names which are provided as the 2nd and third arguments to the program call.  An example
is shown below.

graph.txt:

D 3 E
D 7 C
E 9 C
C 6 A
A 2 B
E 4 B

Program Call:
graph.txt D B

Output:
ShortestPath (Length=7): D->E->B

The graph is shown below:
      ________9________
     |                 |
     C----7----D---3---E
     |                 |
     6                 4
     |                 |
     A---2---B----------
