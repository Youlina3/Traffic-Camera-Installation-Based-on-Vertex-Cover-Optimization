// Compile with c++ ece650-a2.cpp graph.cpp -std=c++11 -o ece650-a2
#include <iostream>
#include <sstream>
#include "graph.h"

using namespace std;


int main(int argc, char **argv) {

    char cmd;
    unsigned int ver_num;
    unsigned int ver_src;
    unsigned int ver_dst;
    string edg_str;
    char pre_cmd = '0';
    graph graph1;
    string line;
    // read from stdin until EOF
    while (getline(cin, line)) {
        istringstream input(line);

        while (input >> cmd) {

            try {
                switch (cmd)
                {
                    case 'V' :
                        if (pre_cmd == 'V')
                        {
                            throw "the first character is repeated ";
                        }
                        else
                        {
                            input >> ver_num;
                            graph1.set_ver(ver_num);
                            //output Vertices' in graph
                            cout<<'V'<<' '<<ver_num<<endl;
                            pre_cmd = 'V';
                            break;
                        }


                    case 'E' :
                    {
                        if ( pre_cmd == 'E')
                        {
                            throw "the first character is repeated ";
                        }
                        else
                        {
                            graph1.clear_linkage();
                            input >> edg_str;
                            istringstream input_edg(edg_str);
                            //output Edge's in graph
                            cout<<"E "<<edg_str<<endl;
                            char edg_char;
                            unsigned int v1;
                            unsigned int v2;
                            unsigned int ver_elem;

                            input_edg >> edg_char;
                            while (edg_char != '}') {
                                input_edg >> edg_char;// read '<'
                                if (edg_char == '}')  break;

                                input_edg >> ver_elem;// read the first vertex

                                v1 = ver_elem;
                                input_edg >> edg_char;// read ','

                                input_edg >> ver_elem;// read the second vertex

                                v2 = ver_elem;
                                graph1.link_vertices(v1, v2);//call to create a matrix
                                input_edg >> edg_char;// read '>'

                                input_edg >> edg_char;// read ',' or '}'
                            }

                            pre_cmd = 'E';
                            break;
                        }
                    }

                    case 's': {
                        input >> ver_src;
                        input >> ver_dst;
                        graph1.cal_path(ver_src, ver_dst);

                        break;
                    }
//
                }
            }

            catch (const char* m) {
                cerr << "Error:" << m << endl;
            }
            // catch (...) {
            //     cerr << "Error:other types of error" << endl;
            // }

        }
    }
    return 0;
}
/*
V 15
E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}
s 2 10

V 5
E {<0,2>,<2,1>,<2,3>,<3,4>,<4,1>}
s 4 0
 */

