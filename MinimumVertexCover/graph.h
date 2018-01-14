#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <set>
#include <list>

//.h file is used to declare functions and class = struct = type. the advantage is to avoid coping the same declarations
struct Edge{
    unsigned v1,v2;
};

//typedef std::vector<Edge> EdgeVec;
typedef std::vector<unsigned> VertexVec;
typedef std::list<unsigned > VertexList;
typedef std::vector<VertexList> AdjList;

struct Graph{
    std::size_t num_edges;
    AdjList adjacency;

    void init(unsigned num_vertices);
    void add(Edge e);
    //void remove(Edge e);
    void clear(unsigned v);
};

/*
class Graph{
    size_t _num_edges;
    AdjList _adjacency;

public:
    friend class EdgeIterator{
        Graph &g;
        Edge e;
    public:
        EdgeIterator &operator++();
        bool operator!=(const EdgeIterator &);
        Edge operator*();
    };


    Graph(size_t num_vertex);
    size_t num_edges() const;
    void add(Edge e);
    void remove(Edge e);
    Edge operator[](size_t);

    EdgeIterator begin();
    EdgeIterator end();
};
*/
#endif
