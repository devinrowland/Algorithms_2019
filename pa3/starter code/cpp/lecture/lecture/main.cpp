#include "CityGraph.h";
#include "CsvParser.h"
#include <iostream>;
#include <algorithm>;


int main(void)
{

	//map_num: mapping of vertexs file string
	//deliv_num: delivery file string

	string map_num;
	string deliv_num;

	cout << "*** Route Planner ***" << endl;
	cout << "Enter maps file: ";
	cin >> map_num;
	cout << "Enter destinations file: ";
	cin >> deliv_num;

	//Putting the map file into a 2D vector
	CsvStateMachine mapping{ "map1.txt" };
	vector<vector<string>> map_vector = mapping.processFile();

	//Putting the delivery file in a 2D vector even though we dont need it, its makes it easier on me
	CsvStateMachine destinations{ "deliveries1.txt" };
	vector<vector<string>> dest_vector = destinations.processFile();

	//CityGraph that all vertexs and connections will be registered
	CityGraph graph{};

	// build map from txt 
	vector<string> Path;
	for (int i = 0; i < map_vector.size(); i++)
	{
		Path = map_vector[i];
		graph.addVertex(Path[0]);
		graph.addVertex(Path[1]);
	}

	//Now that we have all the vertexs, this will connect them all together
	for (int i = 0; i < map_vector.size(); i++)
	{
		Path = map_vector[i];
		graph.connectVertex(Path[0], Path[1], stoi(Path[2]), true);
	}

	//Vector that holds the routes
	vector<string> start = dest_vector[0];

	//Makes graph and runs the tree function to find routes
	CityGraph MinimumSpanningCityGraph = graph;
	auto route = MinimumSpanningCityGraph.computeMinimumSpanningTree(start[0]);

	//Helps go through all the routes to find the weights of the routes
	Edge current;
	int time = 0;

	//Loops through and adds the weights
	for (int i = 0; i < route.size(); i++)
	{
		current = route[i];
		time += current.weight;
	}

	//Outputs for teir one
	cout << "Total travel time: " << time << " minutes" << endl;


	//Tier2

	unordered_map<string, int> distances{};
	CityGraph Graph2{};
	string starts;
	int weight;
	vector<string> deliv;


	
	for (int i = 0; i < dest_vector.size(); i++)
	{
		vector<string> current = dest_vector[i];
		deliv.push_back(current[0]);
		Graph2.addVertex(current[0]);

		//Calculates shortest route from the current location
		distances = graph.computeShortestPath(current[0]);
		for (auto cur : distances)
		{
			for (int i = 0; i < deliv.size(); i++)
			{
				// Not itself and is in the set deliveries file
				if (cur.first != current[0] && cur.first == deliv.at(i))
				{
					//Builds the new graph
					weight = cur.second;
					Graph2.connectVertex(current[0], deliv.at(i), weight, true);
					if (i == 0)
					{
						starts = current[0];
					}

				}
			}
		}
	}
	//Variables to calculate route time
	time = 0;
	auto routes = Graph2.computeMinimumSpanningTree(deliv.at(0));
	Edge routeweight;

	//Adds the weights together.
	for (int i = 0; i < routes.size(); i++)
	{
		routeweight = routes[i];
		time = time + routeweight.weight;
	}

	cout << "Total travel time: " << time << " minutes" << endl;

	//teir3
	vector<string> routed;
	string currents = "";
	string next = "";

	// loads route into a vector
	auto path = Graph2.computeShortestPath(starts);

	for (auto curr : path)
	{
		routed.push_back(curr.first);
	}

	for (int x = 0; x < routed.size() - 1; x++)
	{
		currents = routed.at(x);
		next = routed.at(x + 1);
		cout << currents << " -> " << next << endl;
	}

	
	return 0;
}