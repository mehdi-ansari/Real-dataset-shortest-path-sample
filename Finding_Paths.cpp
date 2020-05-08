#include "Finding_Paths.h"

//Reads inputs including Nodes, Coordinates, Edges, and Distances:
vector <vector <double>> Read_dataSets(string myNdataset_name, string myEdataset_name) {
	// Nodes coordinates:
	string lineN;
	vector <double> Node_cooridante;
	vector <vector <double>> Nodes;

	ifstream Nodefile(myNdataset_name);
	if (Nodefile.is_open())
	{
		while (getline(Nodefile, lineN))
		{
			istringstream in(lineN);
			copy(istream_iterator<double>(in), istream_iterator<double>(), back_inserter(Node_cooridante));
			Nodes.push_back(Node_cooridante);
			Node_cooridante.clear();
		}
	}
	else
	{
		cout << myNdataset_name << " is not open!!" << endl;
	}

	// Edges and their lengths:
	string lineE;
	vector <double> Edge_cooridante;
	vector <vector <double>> Edges;

	ifstream Edgefile(myEdataset_name);
	if (Edgefile.is_open())
	{
		while (getline(Edgefile, lineE))
		{
			istringstream in(lineE);
			copy(istream_iterator<double>(in), istream_iterator<double>(), back_inserter(Edge_cooridante));
			Edges.push_back(Edge_cooridante);
			Edge_cooridante.clear();
		}
	}
	else
	{
		cout << myEdataset_name << " is not open!!" << endl;
	}

	//Find the middle of edges and adding to Edges matrix:
	vector <vector <double>> Edges_DATA(1 + Edges.size());
	Edges_DATA[0].push_back(Nodes.size());
	Edges_DATA[0].push_back(Edges.size());

	for (size_t i = 0; i < Edges.size(); i++)
	{
		Edges_DATA[i + 1] = Edges[i];
		Edges_DATA[i + 1].push_back((Nodes[Edges[i][1]][1] + Nodes[Edges[i][2]][1]) / 2);
		Edges_DATA[i + 1].push_back((Nodes[Edges[i][1]][2] + Nodes[Edges[i][2]][2]) / 2);
	}
	return Edges_DATA;
}

vector <vector <double>> Dijkstras_Alg(vector <vector <double>> Adjacency_list, vector <vector <double>> Adjacency_cost, int source, double inft) {
	int v = Adjacency_list.size();

	vector <double> dist(v);
	vector <int> Temp_set(v);
	vector <double> pred(v);
	vector <int> already_labaled(v);
	for (size_t i = 0; i < v; i++)
	{
		dist[i] = inft;
		Temp_set[i] = i;
		pred[i] = -9;
		already_labaled[i] = 0;
	}
	dist[source] = 0;
	pred[source] = -1;
	already_labaled[source] = 1;

	int stop = 0;

	while ((Temp_set.size() != 0) && (stop == 0))
	{
		int u = -1;
		double min_dist = inft;
		int index_min;

		bool final_loop = false;

		for (size_t i = 0; i < Temp_set.size(); i++)		// Erase the labaled vertex from the exploring list
		{
			if (dist[Temp_set[i]] < min_dist)
			{
				min_dist = dist[Temp_set[i]];
				u = Temp_set[i];				//Choose vertex with minimum distance from source
				index_min = i;
				final_loop = true;
			}
		}


		if (final_loop == true)
		{
			already_labaled[u] = 1;
			Temp_set.erase(Temp_set.begin() + index_min);
		}


		if (min_dist < inft)				//To prevent algorithm checking not connected vertices
		{
			for (size_t i = 0; i < Adjacency_list[u].size(); i++)
			{
				int ui = Adjacency_list[u][i];
				double cost_ui = Adjacency_cost[u][i];

				if (already_labaled[ui] == 0)
				{
					if (dist[ui] > dist[u] + cost_ui)
					{
						dist[ui] = dist[u] + cost_ui;
						pred[ui] = u;
					}
				}
			}
		}
		else
		{
			stop = 1;
		}
	}

	vector <vector <double>> distPredc;
	distPredc.push_back(dist);
	distPredc.push_back(pred);

	dist.clear();
	Temp_set.clear();
	pred.clear();
	already_labaled.clear();

	return distPredc;
}


vector <vector <double>> impl_Dijkstras_Alg(vector <vector <double>> input, string Ndataset_name, string Edataset_name) {
	int number_nodes = input[0][0];
	int number_edges = input[0][1];

	//Adjacency List:
	vector <vector <double>> Adj_list(number_nodes);
	vector <vector <double>> Adj_cost(number_nodes);
	double infnty = 0;

	//Dijkstra's Algorithm will run to find largest shortest path between outgoing nodes and all other connected nodes:
	vector <bool> outgoing_labales(number_nodes);
	for (size_t i = 0; i < number_nodes; i++)
	{
		outgoing_labales[i] = true;
	}

	for (size_t i = 0; i < number_edges; i++)
	{
		Adj_list[input[i + 1][1]].push_back(input[i + 1][2]);
		Adj_cost[input[i + 1][1]].push_back(input[i + 1][3]);
		infnty += input[i + 1][3];

		outgoing_labales[input[i + 1][2]] = false;
	}

	vector <vector <double>> Path;

	clock_t begin_Dijkstras_Alg = clock();
	int iteration_dijkstra = 0;

	for (size_t v = 0; v < number_nodes; v++)
	{
		if (outgoing_labales[v] == true)
		{
			int source_s = v;
			vector <vector <double>> Output_Path_s = Dijkstras_Alg(Adj_list, Adj_cost, source_s, infnty);

			vector <double> Record_output;
			double longest_path = 0;
			int longest_path_index = source_s;

			for (size_t i = 0; i < Output_Path_s[0].size(); i++)
			{
				if (Output_Path_s[0][i] < infnty)
				{
					if (Output_Path_s[0][i] > longest_path)
					{
						longest_path = Output_Path_s[0][i];
						longest_path_index = i;
					}
				}
			}

			Record_output.push_back(longest_path);
			Record_output.push_back(longest_path_index);
			double pr = longest_path_index;
			while (Output_Path_s[1][pr] != -1)
			{
				Record_output.push_back(Output_Path_s[1][pr]);
				pr = Output_Path_s[1][pr];
			}
			Path.push_back(Record_output);
			Record_output.clear();

			iteration_dijkstra++;
		}
	}

	clock_t end_Dijkstras_Alg = clock();
	double Tot_Dijkstra = double(end_Dijkstras_Alg - begin_Dijkstras_Alg) / CLOCKS_PER_SEC;

	//+++++++++++++++++++++++++++++++++++++++++ Save results:
	ofstream MyExcelFile;
	MyExcelFile.open("ZZZ_results.txt");

	MyExcelFile << "Nodes dataset name: " << Ndataset_name << endl;
	MyExcelFile << "Edges dataset name: " << Edataset_name << endl;
	MyExcelFile << iteration_dijkstra << " paths are found by Dijkstra's algorithm in total time: " << Tot_Dijkstra << "sec.  " << endl;
	MyExcelFile << "Longest_Shortest_path    PATH" << endl;

	for (size_t i = 0; i < Path.size(); i++)
	{
		MyExcelFile << Path[i][0] << " ";
		for (size_t j = 1; j < Path[i].size(); j++)
		{
			MyExcelFile << Path[i][Path[i].size() - j] << " ";
		}
		MyExcelFile << endl;
	}

	cout << endl << "Results were saved on ZZZ_results.txt!" << endl;
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//Following vector is the same with "Path" but only sorted from source to sink:
	vector <vector <double>> Outputs_paths(Path.size());
	for (size_t i = 0; i < Path.size(); i++)
	{
		Outputs_paths[i].push_back(Path[i][0]);
		for (size_t j = 1; j < Path[i].size(); j++)
		{
			Outputs_paths[i].push_back(Path[i][Path[i].size() - j]);
		}
	}

	return Outputs_paths;
}
