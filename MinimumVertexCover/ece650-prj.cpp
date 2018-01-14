#include "algorithm.h"
#include "graph.h"
#include <pthread.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <memory>
#include <unistd.h>

using namespace std;
static void *(* algorithm[])(void *) = {APPROX_VC_3, APPROX_VC_1,APPROX_VC_2}; //function pointer
static const char *titles[] = {"CNF-SAT-VC: ", "APPROX-VC-1: ", "APPROX-VC-2: "};

void run_algorithm(Graph &graph)
{
    pthread_t threads[3];
    VertexVec *output[3];
    int ret;
    for(size_t i = 0; i < 3;++i) {
        ret = pthread_create(&threads[i], nullptr, algorithm[i], &graph);
        if (ret) _exit(1); /*error happens here*/
    }

    for(size_t i = 0; i < 3;++i) {
        pthread_join(threads[i],(void **)&output[i]);
        cout<<titles[i];
        if(!output[i]) continue;
        VertexVec &C = *output[i];
        /* print the output */
        for (unsigned j=0; j < C.size(); j++){
            cout<<C[j];
            if(j + 1 != C.size()){
                cout<<',';
            }
        }
        cout << endl;
    }


    for(size_t i = 0; i < 3;++i) {
        delete(output[i]);
    }
}

void *du_iothread(void *){
    Graph &graph = *new Graph(); //why new Graph()? why create a reference? & means reference which is only another name of the object
    char cmd;
    string line;
    unsigned int vertices_num = 0;
    string edge_string;
    char pre_cmd = '0';

    while (getline(cin, line)) {
        istringstream input(line);
        while (input >> cmd) {
            switch (cmd)
            {
                case 'V' :
                    if (pre_cmd == 'V')
                    {
                        cerr << "Error: the first character is repeated.\n";
                        break;
                    }
                    else
                    {
                        input >> vertices_num;
                        graph.init(vertices_num);
                        pre_cmd = 'V';

                        break;
                    }


                case 'E' :
                {
                    unsigned int flagE = 0;
                    if ( pre_cmd == 'E')
                    {
                        cerr << "Error: the first character is repeated.\n ";
                        break;
                    }
                    else
                    {
                        input >> edge_string;
                        istringstream input_edg(edge_string);
                        char edge_char;
                        unsigned int vertice_element = 0;
                        unsigned int v1;
                        unsigned int v2;

                        input_edg >> edge_char;//read '{'

                        while (edge_char != '}') {
                            input_edg >> edge_char;// read '<'
                            if (edge_char == '}')
                            {
                                flagE = 1;
                                break;
                            }
                            else
                            {

                                input_edg >> vertice_element;// read the first vertex
                                v1 = vertice_element;
                                input_edg >> edge_char;// read ','

                                input_edg >> vertice_element;// read the second vertex
                                v2 = vertice_element;

                                input_edg >> edge_char;// read '>'
                                input_edg >> edge_char;// read ',' or '}'

                                graph.add({v1,v2});
                                if (v1 > vertices_num || v2 > vertices_num)
                                {
                                    cerr << "Error: point order out of range.\n";
                                    break;
                                }

                            }

                        }
                        if(flagE == 1)
                        {
                            pre_cmd = 'E';
                            break;
                        }
/*                        for ( int i =0; i < Edges.size(); i++)
                        {
                            cout<<"i:"<<i<<"  "<<Edges[i].v1<<Edges[i].v2<<endl;
                        }*/
                        run_algorithm(graph);
                        pre_cmd = 'E';
                        break;

                    }
                }

            }

        }

    }
    return nullptr;

}

int main(int argc, char **argv)
{
    int ret;
    pthread_t iothread;
    srand(time(nullptr)); // srand() in main functoin to ensure the unique random value of each time
    ret = pthread_create(&iothread, nullptr, du_iothread, nullptr);
    if (ret) return 1;
    ret = pthread_detach(iothread); // this line is used to make that when main thread finish, the iothread won't be blocked
    if (ret) return 1;
    pthread_exit(0);
    return 1;
}















