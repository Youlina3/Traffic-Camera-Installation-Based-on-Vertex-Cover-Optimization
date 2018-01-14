#include "graph.h"
#include <algorithm>

void Graph::init(unsigned n){
    adjacency.clear();
    num_edges = 0;
    adjacency.resize(n,{});
}

void Graph::add(Edge e) {
    auto &l1 = adjacency[e.v1];
    auto &l2 = adjacency[e.v2];
    l1.push_back(e.v2);
    l2.push_back(e.v1);
    num_edges ++;
}

/*void Graph::remove(Edge e){
    auto &l1 = adjacency[e.v1];
    auto &l2 = adjacency[e.v2];
    auto i1 = std::find(l1.begin(),l1.end(),e.v2);
    if(i1 == l1.end()) return ;
    auto i2 = std::find(l2.begin(),l2.end(),e.v1);
    if(i2 == l2.end()) return ;

    l1.erase(i1);
    l2.erase(i2);
    --num_edges;
}*/

void Graph::clear(unsigned v){
    if(v >= adjacency.size()) return;
    for(auto u : adjacency[v]){
        auto &l2 = adjacency[u];
        auto i2 = std::find(l2.begin(),l2.end(),v);
        if(i2 != l2.end()){
            l2.erase(i2);
            --num_edges;
        }
    }
    adjacency[v].clear();
}


/*
Graph::EdgeIterator &Graph::EdgeIterator::operator++();
bool Graph::EdgeIterator::operator!=(const Graph::EdgeIterator &);
Edge Graph::EdgeIterator::operator*();



Graph::Graph(size_t num_vertex): _num_edges(0), _adjacency(num_vertex) {}

size_t Graph::num_edges() const { return _num_edges; }

void  Graph::add(Edge e) {
    auto r1 = _adjacency[e.v1].insert(e.v2);
    auto r2 = _adjacency[e.v2].insert(e.v1);
    if(r1.second && r2.second ) _num_edges ++;
}

void  Graph::remove(Edge e){
    auto it1 = _adjacency[e.v1].find(e.v2);
    auto it2 = _adjacency[e.v2].find(e.v1);
    if(it1 != _adjacency[e.v1].end() && it2 != _adjacency[e.v2].end())
    {
        _adjacency[e.v1].erase(it1);
        _adjacency[e.v2].erase(it2);
        --_num_edges;
    }
}

Edge Graph::operator[](size_t n){
    if(n>_num_edges) return {};



}

EdgeIterator  Graph::begin(){

}

EdgeIterator  Graph::end(){

}
*/

