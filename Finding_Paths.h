#include <iostream>
#include <string>
#include <cmath>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <vector>
#include <math.h>       /* fmod */
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>

using namespace std; 

vector <vector <double>> Read_dataSets(string myNdataset_name, string myEdataset_name);

vector <vector <double>> Dijkstras_Alg(vector <vector <double>> Adjacency_list, vector <vector <double>> Adjacency_cost, int source, double inft);

vector <vector <double>> impl_Dijkstras_Alg(vector <vector <double>> input, string Ndataset_name, string Edataset_name);