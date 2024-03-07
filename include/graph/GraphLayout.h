#pragma once

namespace graph
{

class Graph;

class GraphLayout
{
public:
	static void StressMinimization(const Graph& graph);
	static void GEM(const Graph& graph);
	static void NodeRespecter(const Graph& graph);
	static void FMMM(const Graph& graph);
	static void Multilevel(const Graph& graph);

	static void OptimalHierarchy(const Graph& graph);

}; // GraphLayout


}