#include "CampusGraph.h";
#include "CsvParser.h";
#include <iostream>;
#include <cstdlib>;

int main(void)
{
	//start: starting position in finding shortest path
	//end: end point in finding shortest path

	string start;
	string end;

	cout << "** HSU Transit Time Calculator **" << endl;
	cout << "Enter Starting Location: ";
	cin >> start;
	cout << "Enter Destinantion: ";
	cin >> end;

	//Example of how to parse a CSV file for graph building

	CsvStateMachine csm{ "distances.csv" };
	vector<vector<string>> data = csm.processFile();

	CampusGraph graph{};
	int i = 1;
	int j = 1;

	//sets first vertex into graph
	graph.addVertex(data[0][0]);

	//while loop thats adds all vertexs into the graph
	while (i <= 231)
	{
		if (data[i][0] != data[i - 1][0])
		{
			graph.addVertex(data[i][0]);
		}
		i++;
	}

	// Makes all connections between vertexs
	i = 0;
	while (i <= 231)
	{
		int num = 0;
		string character;
		character = data[i][2];
		num = stoi(character);
		graph.connectVertex(data[i][0], data[i][1], num);
		i++;
	}

	//Finds shortest paths between all vertexs
	auto distances = graph.computeShortestPath(start);
	int distance_traveled = distances[end];

	cout << "Estimated Time Traveled: " << distance_traveled;

	return 0;
}