#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

using namespace std;

/// main() must be declared with arguments
/// otherwise command line arguments are ignored

unsigned int street_num ( unsigned int k )
{
    // open /dev/urandom to read
    std::ifstream urandom("/dev/urandom");

    // check that it did not fail
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int rand = 3;
    urandom.read((char*)&rand, sizeof(unsigned int));
    rand = rand % (k-2+1) +2;
    urandom.close();
    return (unsigned int) rand;

}

unsigned int line_segment_num (unsigned int k)
{
    // open /dev/urandom to read
    std::ifstream urandom("/dev/urandom");

    // check that it did not fail
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int rand = 3;
    urandom.read((char*)&rand, sizeof(unsigned int));
    rand = rand % (k-1+1) + 1;
    urandom.close();
    return (unsigned int) rand;


}

unsigned int wait_num (unsigned int k)
{
    // open /dev/urandom to read
    std::ifstream urandom("/dev/urandom");

    // check that it did not fail
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int time = 3;
    urandom.read((char*)&time, sizeof(unsigned int)); 
    time = time % (k-5+1) + 5;
    urandom.close();
    return (unsigned int) time;


}

int coordinate_value (unsigned int k)
{
    // open /dev/urandom to read
    std::ifstream urandom("/dev/urandom");

    // check that it did not fail
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int rand = 3;
    urandom.read((char*)&rand, sizeof(int));
    rand = rand % (k+k);
    int out= rand - k ;
    urandom.close();
    return out;


}

void create_street( vector<string> &street , unsigned int street_num)
{
    string name = "a";
    for (unsigned int i=0; i < street_num; i++)
    {
        street.push_back(name);
        name = name +'a';
    }

}

int max_xy( int a1, int a2)
{

    int max1;
    if ( a1 > a2)
    {
        max1 = a1;
        return max1;
    }
    max1 = a2;
    return max1;

}

int min_xy( int a1, int a2)
{

    int min1;
    if ( a1 > a2)
    {
        min1 = a2;
        return min1;
    }

    min1 = a1;
    return min1;

}



bool if_intersect( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    double xnum, xden, xcoor, ynum, yden, ycoor;

    xnum = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4));
    xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));
    xcoor =  xnum / xden;

    ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4);
    yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
    ycoor = ynum / yden;

    int min_x1, min_x2, max_x1, max_x2, min_y1, min_y2, max_y1, max_y2;

    min_x1 = min_xy(x1,x2);
    max_x1 = max_xy(x1,x2);
    min_x2 = min_xy(x3,x4);
    max_x2 = max_xy(x3,x4);
    min_y1 = min_xy(y1,y2);
    max_y1 = max_xy(y1,y2);
    min_y2 = min_xy(y3,y4);
    max_y2 = max_xy(y3,y4);

    if ( min_x1<= xcoor &&  xcoor <= max_x1)
        if ( min_x2 <= xcoor && xcoor <= max_x2)
            if ( min_y1 <= ycoor && ycoor <= max_y1)
                if ( min_y2 <= ycoor && ycoor <= max_y2)
                    return true;
    return false;

}



bool if_add_point ( vector<int> coordinate, int x, int y)
{
    int s = coordinate.size();
    if ( coordinate.empty())
    {

        return true;
    }if ( s == 2)
    {
        if (( x == coordinate[0]) && (y == coordinate[1]) )
        {

            return false;
        }

        return true;
    }
    else
    {
        //check duplicate coordinates
        for (int i = 0; i < coordinate.size(); i = i + 2){
            if (x == coordinate[i] && y == coordinate[i+1]){
                return false;
            }
        }

        double k1, k2;
        //{0,10,0,10,4,4,5,5,6,6,5,7,0,0,7,7}
        if ( x == coordinate[s-2] && x == coordinate[s-4])
            return false;

        //check intersection
        if ( (x == coordinate[s-2]) && (x != coordinate[s-4]))
        {
            if ( s == 4)
                return true;
            else
            {
                for ( int i = s-3; i >=2; i = i-2 )
                {
                    if ( if_intersect(x,y,coordinate[s-2],coordinate[s-1],coordinate[i-1],coordinate[i],coordinate[i-3],coordinate[i-2]))
                        return false;

                }

                return true;
            }
        }

        if ( (coordinate[s-4] == coordinate[s-2]) && (x != coordinate[s-2]))
        {
            if ( s == 4)
                return true;
            else
            {
                for ( int i = s-3; i >=0; i = i-2 )
                {
                    if ( if_intersect(x,y,coordinate[s-2],coordinate[s-1],coordinate[i-1],coordinate[i],coordinate[i-3],coordinate[i-2]))
                        return false;

                }

                return true;
            }
        }

        //check in a line

        k1 = ((y - coordinate[s-1]) / (x-coordinate[s-2]));
        k2 = ((coordinate[s-1]) - coordinate[s-3]) / (coordinate[s-2]-coordinate[s-4]);

        if (k1 == k2)
            return false;

        else
        {

            if ( s == 4)
                return true;
            else
            {
                for ( int i = s-3; i >=0; i = i-2 )
                {
                    if ( if_intersect(x,y,coordinate[s-2],coordinate[s-1],coordinate[i-1],coordinate[i],coordinate[i-3],coordinate[i-2]))
                        return false;

                }

                return true;
            }

        }


    }

}





int main (int argc, char **argv) {

    std::string svalue, nvalue, lvalue, cvalue;
    unsigned int sint_value = 10, nint_value = 5, lint_value = 5, cint_value = 20;
    int c;
    int k;
    int s_num, l_num, x_cord, y_cord;
    unsigned int w_sed;

    vector<string> street; //steet names
    vector<int> street_line_num;//segments
    vector<int> coordinate;//x_cord y_cord

    opterr = 0;

    // parse
    while ((c = getopt(argc, argv, "s:n:l:c:")) != -1) {
        switch (c) {
            case 's':
                svalue = optarg;
                sint_value = std::atoi(svalue.c_str());
                if (sint_value < 2)
                {
                    cerr << "Error: the number is too small (after s)"<<endl;
                    exit(1);
                }

                break;
            case 'n':
                nvalue = optarg;
                nint_value = std::atoi(nvalue.c_str());
                if (nint_value < 1)
                {
                    cerr << "Error: the number is too small (after n)"<<endl;
                    exit(1);
                }

                break;
            case 'l':
                lvalue = optarg;
                lint_value = std::atoi(lvalue.c_str());
                if (lint_value < 5)
                {
                    cerr << "Error: the number is too small (after l)"<<endl;
                    exit(1);
                }

                break;
            case 'c':
                cvalue = optarg;
                cint_value = std::atoi(cvalue.c_str());
                if (cint_value < 1)
                {
                    cerr << "Error: the number is too small (after c)"<<endl;
                    exit(1);
                }

                break;

            case '?':
                if (optopt == 's') {
                    std::cerr << "Error: option -" << optopt
                              << " requires an argument." << std::endl;
                    break;
                }
                else if (optopt == 'n') {
                    std::cerr << "Error: option -" << optopt
                              << " requires an argument." << std::endl;
                    break;
                }
                else if (optopt == 'l') {
                    std::cerr << "Error: option -" << optopt
                              << " requires an argument." << std::endl;
                    break;
                }
                else if (optopt == 'c') {
                    std::cerr << "Error: option -" << optopt
                              << " requires an argument." << std::endl;
                    break;
                }

                else
                    std::cerr << "Error: unknown option: " << optopt << std::endl;
                    break;

        }


    }

    while (true)
    {



//remove all existing streets through a1
        if ( !street.empty())
        {
            for(auto i = street.begin(); i != street.end(); i++)
            {
                cout<<"r "<<'"'<<*i<<'"'<<endl;

            }

            street.clear();//clear street name
            street_line_num.clear();//clear line-segment

        }

//generate the number of streets
        s_num = street_num(sint_value);
//generate streets'names
        create_street(street, s_num);

//generate steets' line_segments
        for (int j = 0; j < s_num; j++)
        {
            l_num = line_segment_num(nint_value);
            street_line_num.push_back(l_num);

        }

        int index = 0;

        for (int mk = 0; mk < street_line_num.size(); mk++)
        {
            coordinate.clear();     //save coordinates of each street
            int times = 0;
            int error = 0;
            while ( times < street_line_num[mk]+1 )
            {
                x_cord = coordinate_value(cint_value);
                y_cord = coordinate_value(cint_value);
                if (if_add_point(coordinate, x_cord, y_cord))
                {
                    coordinate.push_back(x_cord);
                    coordinate.push_back(y_cord);
                    times++;
                    error = 0;
                }

                else
                {

                    if ( error == 25)
                    {
                        cerr<<"Error: failed to generate valid input for 25 simultaneous attempts"<<endl;
                        exit(1);   // ? how to exit
                    }

                    error++;
                }


            }


            // a command output
            string a_output;
            a_output = string("a \"") + street[index] + "\" ";

//how to output a command line
            for (int mk = 0; mk < coordinate.size(); mk = mk+2)
            {
                string a,b;
                if (coordinate[mk]<0){
                  a = "-"+to_string(coordinate[mk]*(-1));
                } else {
                  a = to_string(coordinate[mk]);
                }
                if (coordinate[mk+1]<0){
                  b = "-"+to_string(coordinate[mk+1]*(-1));
                } else {
                  b = to_string(coordinate[mk+1]);
                }
                a_output = a_output + '('+ a + ','+ b +')';
            }

            cout<<a_output<<endl;

            index++;
        }

        // g command
            cout<<'g'<<endl;
            w_sed = wait_num(lint_value);
            sleep(w_sed);

        }


}










