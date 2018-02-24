#ifndef GRAPH_H
#define GRAPH_H

#include<set>
#include<map>
#include<memory>
#include<stdexcept>
#include<list>
using namespace std;

using Index = size_t;
using Path = std::pair<Index,Index>;

class VertexData
{

    VertexData(){}
};



class Vertex
{
public:
    explicit  Vertex()
    {
        _Object = nullptr;
        _Index = -1;
        _Visited = false;
    }
    Vertex(Index index)
    {
        _Index  = index;
        _Object = nullptr;
        _Visited = false;
    }

    Vertex(Index index,VertexData* object)
    {
        _Index  = index;
        _Object = object;
        _Visited = false;
    }
    Vertex(const Vertex& vertex)
    {
        _Object = vertex.getObject();
        _Index = vertex.getIndex();
    }
    ~Vertex()
    {
        if(_Object != nullptr)
             delete _Object;
    }



    Index getIndex() const
    {
        return _Index;
    }

    VertexData* getObject() const
    {
        return _Object;
    }

    void setIndex(const Index &index)
    {
        _Index = index;
    }

    void setObject(VertexData* Object)
    {
        _Object = Object;
    }

    bool operator==(const Vertex& vertex)
    {
        if(_Index == vertex.getIndex())
            return true;
        return false;
    }

    bool operator!=(const Vertex& vertex)
    {
        if(_Index != vertex.getIndex() )
            return true;
        return false;
    }

    Vertex& operator=(const Vertex& vertex)
    {
        _Index = vertex.getIndex();
        _Object = vertex.getObject();
        return *this;
    }

    void addEdge(Vertex* end)
    {
        _Edges.insert(end);
    }

    set<Vertex*> getEdges()
    {
        return _Edges;
    }

    bool isAdjacent(const Vertex& end)
    {
        for(auto vertex:_Edges)
            if(*vertex == end)
                return true;
        return false;
    }

    bool isVisited() const
    {
        return _Visited;
    }

    void setVisited(bool visited)
    {
        _Visited = visited;
    }

private:

    bool   _Visited;
    int    _Weight;
    Index  _Index;
    VertexData* _Object;
    std::set<Vertex*> _Edges;
};


class Graph{

public:
    explicit  Graph(){}

    void addVertex(const Vertex& vertex)
    {
        _AdjMatrix[vertex.getIndex()] = vertex;
    }

    void addEdge(const Vertex& start, const Vertex& end)
    {
        _AdjMatrix[start.getIndex()].addEdge(&_AdjMatrix[end.getIndex()]);
    }

    set<Vertex*> getEdges(const Vertex& start)
    {
        return _AdjMatrix[start.getIndex()].getEdges();
    }

    set<Vertex*> getEdges(const Index& start)
    {
        return _AdjMatrix[start].getEdges();
    }

//    Vertex* operator[](Index& index)
//    {
//        auto iter = _AdjMatrix.find(index);
//        if (iter != _AdjMatrix.end())
//            return &(iter->second);
//        else
//        throw new std::logic_error("Can not find the vertex!!");

//        return nullptr;
//    }

    bool isAdjacent(const Index& start_index, const Index& end_index)
    {
        if(_AdjMatrix[start_index].isAdjacent(end_index))
            return true;
        return false;
    }

    void setVisited(Index index,bool visited)
    {

        Vertex &vertex = _AdjMatrix[index];
        vertex.setVisited(visited);
        _VisitedList.push_back(&vertex);
    }

    bool isVisited(Index index)
    {
         return _AdjMatrix[index].isVisited();
    }

    const std::list<Vertex*>& getVisitedList()
    {
        return _VisitedList;
    }

private:

    std::map<Index,Vertex> _AdjMatrix;
    std::list<Vertex*> _VisitedList;


};


#endif//GRAPH_H


