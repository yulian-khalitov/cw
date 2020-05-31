#include "Graph.h"

Graph::Graph(std::vector<std::string> rows)
{
	std::map<char, int> vertex_map;
	for (auto row : rows) vertex_map[row[0]] = vertex_map[row[2]] = 0;
	vertex_map['T'] = vertex_map.size() - 1;
	int i = 1;
	for (auto& vert : vertex_map)
	{
		if (vert.first != 'S' && vert.first != 'T') vert.second = i++;
		vertexes.push_back(Vertex(0, 0));
	}
	for (auto row : rows)
	{
		std::stringstream capacity_stream(row.substr(4, row.length() - 1));
		int capacity = 0;
		capacity_stream >> capacity;
		edges.push_back(Edge(0, capacity, vertex_map[row[0]], vertex_map[row[2]]));
	}
}


void Graph::preflow()
{
	vertexes[0].h = vertexes.size();
	for (int i = 0; i < edges.size(); ++i)
	{
		if (edges[i].u == 0)
		{
			edges[i].flow = edges[i].capacity;
			vertexes[edges[i].v].excess_flow += edges[i].flow;
			edges.push_back(Edge(-edges[i].flow, 0, edges[i].v, 0));
		}
	}
}


int Graph::overflow_vertex()
{
	for (int i = 1; i < vertexes.size() - 1; ++i)
		if (vertexes[i].excess_flow > 0) return i;
	return -1;
}


void Graph::update_reverse_edge(int i, int flow)
{
	int u = edges[i].v;
	int v = edges[i].u;

	for (int j = 0; j < edges.size(); ++j)
	{
		if (edges[j].v == v && edges[j].u == u)
		{
			edges[j].flow -= flow;
			return;
		}
	}
	edges.push_back(Edge(0, flow, u, v));
}


bool Graph::push(int u)
{
	for (int i = 0; i < edges.size(); ++i)
	{
		if (edges[i].u == u)
		{
			if (edges[i].flow == edges[i].capacity) continue;
			if (vertexes[u].h > vertexes[edges[i].v].h)
			{
				int flow = std::min(edges[i].capacity - edges[i].flow, vertexes[u].excess_flow);
				edges[i].flow += flow;
				vertexes[u].excess_flow -= flow;
				vertexes[edges[i].v].excess_flow += flow;
				update_reverse_edge(i, flow);
				return true;
			}
		}
	}
	return false;
}


void Graph::relabel(int u)
{
	int min_h = INT_MAX;
	for (int i = 0; i < edges.size(); ++i)
	{
		if (edges[i].u == u)
		{
			if (edges[i].flow == edges[i].capacity)
				continue;
			if (vertexes[edges[i].v].h < min_h)
			{
				min_h = vertexes[edges[i].v].h;
				vertexes[u].h = min_h + 1;
			}
		}
	}
}

int Graph::max_flow()
{
	preflow();
	while (overflow_vertex() != -1)
	{
		int u = overflow_vertex();
		if (!push(u))
			relabel(u);
	}
	return vertexes.back().excess_flow;
}
