#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>

struct Vertex
{
	int h, excess_flow;
	Vertex(int h, int excess_flow) : h{ h }, excess_flow{ excess_flow } {}
};

struct Edge
{
	int flow, capacity, u, v;
	Edge(int flow, int capacity, int u, int v) : flow{ flow }, capacity{ capacity }, u{ u }, v{ v } {}
};

class Graph
{
	std::vector<Vertex> vertexes;
	std::vector<Edge> edges;
	bool push(int u);
	void relabel(int u);
	void preflow();
	int overflow_vertex();
	void update_reverse_edge(int i, int flow);
public:
	Graph(std::vector<std::string>);
	int max_flow();
};