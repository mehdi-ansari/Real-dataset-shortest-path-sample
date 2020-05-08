# Real-dataset-shortest-path-sample
Dijkstra's method to find shortest paths on real datasets

Dijkstra's algorithm was coded to find the longest shortest paths from candidate sources in the real datasets provided on https://www.cs.utah.edu/~lifeifei/SpatialDataset.htm

Five road networks of California, San Francisco, North America, City of San Joaquin County, and City of Oldenburg are not strongly conneceted. So, the nodes with no ingoing arcs are considered as sources for Dijkstra's algorithm. The shortest paths from each candidate source are found and the longest shortest path are recorded on the text files \_dijkstras.txt. The format of text file is: The_longest_Shortest_path source ... (path) ... sink 

The cost of moving through an arc is assumed to be the Euclidean distance between the nodes are incident with the arc.
