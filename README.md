# Real-dataset-shortest-path-sample
Dijkstra's method to find shortest paths on real datasets

Dijkstra's algorithm was coded to find the longest shortest paths from candidate source in real datasets provided on https://www.cs.utah.edu/~lifeifei/SpatialDataset.htm

The five road networks of California, San Francisco, North America, City of San Joaquin County, and City of Oldenburg are not strongly conneceted. So, the nodes with no ingoing arcs are considered as sources for Dijkstra's algorithm. Shortest paths from each candidate sink are found and the longest ones are recorded on the text files \_dijkstras.txt. The format of text file is: The_longest_Shortest_path source ... (path) ... sink 
