#include <algorithm>
#include <iostream>
#include <memory>
#include "algorithm.h" // help us to use some existing algorithms
#include "graph.h"
#include "minisat/core/Solver.h"

void *APPROX_VC_1(void *input)
{
    Graph g = *(const Graph *)input; //static cast; type convertion; pointer is 64 btis; for compiler, it knows that input points to a graph type pbject, which is the only difference between those two pointers.
    VertexVec &C = *new VertexVec(); //after "new", output is a address pointing to VertexVec type object


    while(g.num_edges > 0){
        auto v = std::max_element(
                g.adjacency.begin(),g.adjacency.end(),
                [](VertexList &l1, VertexList &l2)->bool{ return l1.size()<l2.size(); } //?
        );
        unsigned i = (unsigned)(v-g.adjacency.begin()); //get the highest degree vertex
        C.push_back(i);
        g.clear(i);
    }
    std::sort( C.begin(), C.end(), std::less<int>());
    return &C;
}

void *APPROX_VC_2(void *input) // ? random pick can cause the more complicated running time maybe we can add a vector of edges
{
    Graph g = *(const Graph *)input;
     // the value of input is the same as that of gp, but they are different variables
    VertexVec &C = * new VertexVec();// new followed by type name; () means call the constructor function. it is put into the heap.

    while (g.num_edges > 0) {
        unsigned v1_pick = 0, v2_pick;
        {
            size_t m;
            m = rand() % (g.num_edges * 2); // change this part to another easier method.
            while (g.adjacency[v1_pick].size() <= m) {
                m -= g.adjacency[v1_pick].size();
                ++v1_pick;
            }
            v2_pick = g.adjacency[v1_pick].front();
        }

        C.push_back(v1_pick);
        C.push_back(v2_pick);
        g.clear( v1_pick );
        g.clear( v2_pick );
        /*
        Edges.erase(Edges.begin()+m);
        v1_pick = edge_pick.v1;
        v2_pick = edge_pick.v2;

        for (auto it=Edges.begin(); it != Edges.end(); )
        {
            auto &i=*it;
            if ( i.v1 == edge_pick.v1 || i.v1 == edge_pick.v2 )
                Edges.erase(it);
            else if ( i.v2 == edge_pick.v1 || i.v2 == edge_pick.v2 )
                Edges.erase(it);
            else
                it++;
        }
        */

    }
    std::sort( C.begin(), C.end(), std::less<int>());
    return &C;
}

void *APPROX_VC_3(void *gp)
{
    const Graph &input = *(const Graph *)gp;
    VertexVec &C = *new VertexVec();
    // -- allocate on the heap so that we can reset later if needed
    std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
    // k: the number of the vertex-cover vertices
    unsigned int k = 0;
    //if res = ture, then the assignment is the final result of mini_vc
    bool res;

    while (k <= input.adjacency.size() - 1)
    {


//reset the n*k matrix which stores the literals
        std::vector<std::vector<Minisat::Lit>> nk_matrix(input.adjacency.size());
        for (unsigned int i = 0; i < input.adjacency.size(); i++)
            for (unsigned int j = 0; j < k; j++) {
                Minisat::Lit l = Minisat::mkLit(solver->newVar());
                nk_matrix[i].push_back(l);
            }
        // first condition
        for (unsigned int i = 0; i < k; i++) {
            Minisat::vec<Minisat::Lit> save_literal;
            for (unsigned int j = 0; j < input.adjacency.size(); j++) {
                save_literal.push(nk_matrix[j][i]);
            }
            solver->addClause(save_literal);
        }

// second condition
        for (unsigned int m = 0; m < input.adjacency.size(); m++)
            for (unsigned int p = 0; p < k; p++)
                for (unsigned int q = p + 1; q < k; q++) {
                    solver->addClause(~nk_matrix[m][p], ~nk_matrix[m][q]);
                }
//third condition
        for (unsigned int m = 0; m < k; m++)
            for (unsigned int p = 0; p < input.adjacency.size(); p++)
                for (unsigned int q = p + 1; q < input.adjacency.size(); q++) {
                    solver->addClause(~nk_matrix[p][m], ~nk_matrix[q][m]);
                }

//forth condition
        for(unsigned v1 = 0 ; v1 < input.adjacency.size(); ++v1) {
            for (auto v2 : input.adjacency[v1]) {
                if(v2 < v1) continue;
                Minisat::vec<Minisat::Lit> edge_lit;
                for (unsigned int w = 0; w < k; w++) {
                    edge_lit.push(nk_matrix[v1][w]);
                    edge_lit.push(nk_matrix[v2][w]);
                }

                solver->addClause(edge_lit);
            }
        }
        res = solver->solve();
        if (res )
        {
            for ( unsigned int i = 0; i < input.adjacency.size(); i++)
                for ( unsigned int j =0; j < k; j++)
                    if ( Minisat::toInt(solver->modelValue(nk_matrix[i][j])) == 0)
                    {
                        C.push_back(i);
                    }

            break;
        }
        else {
            solver.reset(new Minisat::Solver());
        }
        k++;
    }
    std::sort( C.begin(), C.end(), std::less<int>());
    return &C;
}

