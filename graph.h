//
// Created by lenovo on 2017/10/14.
//

#ifndef ECE650_A2_GRAPH_H
#define ECE650_A2_GRAPH_H
#include <vector>
using namespace std;


class graph {


#define INF    (~(0x1<<31))
private:
    unsigned int g_ver_num; //the number of vertices
    vector<vector<unsigned int>> g_matrix;
    vector<unsigned> result_path;

public:
    void clear_linkage();
    void set_ver(unsigned int ver_num); //vertices are put in the vector
    void link_vertices(unsigned int v1, unsigned int v2);
    void cal_path(unsigned int vs, unsigned int vd);//get the shortest path
};


#endif //ECE650_A2_GRAPH_H

