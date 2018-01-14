//
store the graph in a matrix and calculate the shortest path using Dijkstra's algorithm
//

#include "graph.h"
#include "iostream"

//set the vertices vector
void graph::clear_linkage(){

    for (auto &i:g_matrix)
        for(auto &j : i)
            j=INF;
    result_path.clear();
}

void graph::set_ver(unsigned int ver_num)
{
    g_matrix.clear();
    result_path.clear();
    g_ver_num = ver_num;
    g_matrix.resize(g_ver_num);
    for (auto &i:g_matrix)
    {
        i.resize(g_ver_num,INF);
    }
}

//set the matrix
void graph::link_vertices(unsigned int v1, unsigned int v2)
{
    if (v1 >= g_matrix.size()|| v2 >= g_matrix[0].size())
        throw "out of range";
    else
    {
        g_matrix[v1][v2] = 1;
        g_matrix[v2][v1] = 1;
    }
}


//create a vector to store the path

void graph::cal_path(unsigned int ver_src, unsigned int ver_dst) {
    if (ver_src >= g_ver_num || ver_dst >= g_ver_num)
    {
        throw " Input points out of range";
    }

    unsigned int new_dist;
    unsigned int flag[g_ver_num];

    unsigned int dist[g_ver_num];
    result_path.clear();


    for (unsigned int i = 0; i < g_ver_num; i++) {
        flag[i] = 0;

        dist[i] = g_matrix[ver_src][i];
    }


    flag[ver_src] = 1;
    dist[ver_src] = 0;

    for (unsigned int i = 1; i < g_ver_num; i++) {

        unsigned int min = INF;
        unsigned int k = 0;
        for (unsigned int j = 0; j < g_ver_num; j++) {
            if (flag[j] == 0 && dist[j] < min) {
                min = dist[j];
                k = j;
            }
        }

        flag[k] = 1;


        for (unsigned int j = 0; j < g_ver_num; j++) {
            new_dist = (g_matrix[k][j] == INF ? INF : (min + g_matrix[k][j]));
            if (flag[j] == 0 && (new_dist < dist[j])) {
                dist[j] = new_dist;

            }
        }
    }


    if (dist[ver_dst] == INF)
    {
        throw " the path doesn't exist";
    }

    unsigned int vertex = ver_dst;
    while (dist[vertex] > 0) {
        result_path.push_back(vertex);
        for(size_t i = 0; i<g_ver_num; ++i)
        {
            if(g_matrix[vertex][i] < INF &&
               dist[i] + g_matrix[vertex][i] == dist[vertex])
            {
                vertex = i;
                break;
            }
        }
    }
    result_path.push_back(vertex);


    for (auto mk = result_path.rbegin(); mk != result_path.rend(); mk++)
    {
        cout << *mk;
        if (mk != result_path.rend() - 1) {
            cout << "-";
        } else
            cout << endl;
    }
}
