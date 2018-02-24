#ifndef DFS_H
#define DFS_H
#include<graph.h>
#include<vector>

class DFS
{
public:
    DFS(Graph* graph)
    {
        _Graph = graph;
    }

    bool search(Index start_index)
    {
        auto adjacents = _Graph->getEdges(start_index);
        _Graph->setVisited(start_index,true);

        for(auto adj:adjacents)
        {
            if(adj->getIndex() == start_index)
                continue;

            if(_Graph->isAdjacent(start_index,adj->getIndex()))
            {
                _visited.push_back(std::make_pair(start_index,adj->getIndex()));
            }
            if(!_Graph->isVisited(adj->getIndex()))
                search(adj->getIndex());
          }

        return true;
    }

    std::vector<Path> getVisited() const
    {
        return _visited;
    }

private:
    Graph* _Graph;
    std::vector<Path> _visited;
};
#endif // DFS_H


