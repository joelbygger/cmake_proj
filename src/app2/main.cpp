//
// This program will generate a random graph and then calculates path lengths
// between nodes using Djikstras algorithm.
//

#include "graph.hpp"
#include "path.hpp"
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <vector>

namespace CreateGraph
{
    // To group min an max distance range, to avoid mixups.
    struct DistanceRange
    {
        const int min;
        const int max;
    };

    void generateRandom(Graph& graph, const int noVertices, const double edgeDensity, const DistanceRange distRange);
    void createAndEvaluate(const int noVertices, const double edgeDensity, const DistanceRange distRange);

    // Function creates a graph, makes sure it's sorted so that Djukstras
    // algorithm can be applied to it.
    void generateRandom(Graph& graph, const int noVertices, const double edgeDensity, const DistanceRange distRange)
    {
        // I use std::uniform_int_distribution instead of rand, easier when dealing with ranges, from
        // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
        std::random_device rd;                                // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd());                               // Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> densityDistr(1, 100); // [%]
        std::uniform_int_distribution<> edgeLenDistr(distRange.min, distRange.max);

        // Loop through nodes and create connections based on density.
        // We make sure we only calculate a edge density once. We do not create connections for:
        // - nodes connected to themselves
        // - nodes we have already connected.
        //   0 1 2 3
        // 0 x n n n
        // 1 x x n n
        // 2 x x x n
        // 3 x x x x
        // Algorithm acc. to (at 8:30) https://www.coursera.org/learn/c-plus-plus-a/lecture/p8Kyz/3-4-using-dijkstras-algorithm
        // Underlying layer might also make sure that we don't overwrite already
        // created edges, but we can't rely on that here...
        for (int from = 0; from < noVertices; from++)
        {
            for (int to = from; to < noVertices; to++)
            {
                if (to != from && edgeDensity >= densityDistr(gen))
                {
                    graph.addEdgeIfNew(from, to, edgeLenDistr(gen));
                }
            }
        }

        graph.sort();
    }

    // Creates a graph, then chekcs paths and prints results.
    // edgeDensity as percent, i.e. 10 == 0%.
    void createAndEvaluate(const int noVertices, const double edgeDensity, const DistanceRange distRange)
    {
        std::cout << "Generating graph of " << noVertices << " vertices, with density " << edgeDensity << std::endl;

        Graph graph(noVertices);
        generateRandom(graph, noVertices, edgeDensity, distRange);
        Dijkstra path(graph, 0);
        // graph.printGraph();

        std::vector<int> lens;
        auto allOk = true;
        for (int i = 1; i < noVertices; i++)
        {
            auto len = path.getLen(i);
            if (len == std::numeric_limits<int>::max())
            {
                allOk = false;
                break;
            }
            lens.push_back(len);

            // This is debug prints, not sure if interesting...
            std::cout << "Calculating to id: " << i << ", ";
            std::cout << "calculated length: " << lens.back();
            std::vector<int> route = path.getPath(i);
            std::cout << ", route: ";
            for (auto const& node : route)
            {
                std::cout << node << " ";
            }
            std::cout << " end" << std::endl;
        }

        if (allOk)
        {
            // Use STL function to sum the path lengths.
            auto avg = std::accumulate(lens.begin(), lens.end(), 0) / static_cast<int>(lens.size());
            std::cout << "Average path len: " << avg << std::endl;
        }
        else
        {
            std::cout << "Some path was incomplete, aborting this run." << std::endl << std::endl;
        }
    }
} // namespace CreateGraph

int main()
{
    // We are allowed to use discrete/ floating disatances as we like:
    // https://www.coursera.org/learn/c-plus-plus-a/peer/1WzYR/homework-2-implement-dijkstras-algorithm/discussions/threads/ZM1sPhR2Eee0thK6z3XwTA
    const CreateGraph::DistanceRange distRange = { 1, 10 };
    const int noVertices = 50;
    double density = 20; // [%]

    CreateGraph::createAndEvaluate(noVertices, density, distRange);
    density = 40; // [%]
    CreateGraph::createAndEvaluate(noVertices, density, distRange);
}
