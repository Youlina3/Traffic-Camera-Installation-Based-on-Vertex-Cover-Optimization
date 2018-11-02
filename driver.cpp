// c++ ece650-a3.cpp -std=c++11 -o ece650-a3
#include <iostream>
#include <unistd.h>
#include <vector>
#include <signal.h>

int procB(void) {
    // Process B writing to C
    while (!std::cin.eof()) {
        // read a line of input until EOL and store in a string
        std::string line;
        std::getline(std::cin, line);
        std::cout << line << std::endl;
    }
    std::cout << "[B] saw EOF" << std::endl;
    return 0;
}


int main (int argc, char **argv) {
    std::vector<pid_t> kids;

    //generate pipe
    int RgtoA[2];
    int A1BtoA2[2];
    pipe(RgtoA);
    pipe(A1BtoA2);
    pid_t child_pid;
    
    child_pid = fork();
    if(child_pid == 0)
    {
        
        dup2(RgtoA[1], STDOUT_FILENO);
        close(RgtoA[0]);
        close(RgtoA[1]);

        int rgen = execv("./rgen",argv);
        return rgen;
    }

    kids.push_back(child_pid);
    
    child_pid = fork();
    if(child_pid == 0)
    {
        dup2(RgtoA[0], STDIN_FILENO);
        close(RgtoA[0]);
        close(RgtoA[1]);

        dup2(A1BtoA2[1], STDOUT_FILENO);
        close(A1BtoA2[0]);
        close(A1BtoA2[1]);

        char *argv1[3];

        argv1[0] = (char *)"python";
        argv1[1] = (char *)"ece650-a1.py";
        argv1[2] = nullptr;

        return execvp("python", argv1);
    }
    kids.push_back(child_pid);

    // conncet a1 to a2
    child_pid = fork();
    if(child_pid == 0)
    {
        dup2(A1BtoA2[0], STDIN_FILENO);
        close(A1BtoA2[0]);
        close(A1BtoA2[1]);

        int a_2 = execv("ece650-a2", argv);
        return a_2;
    }
    kids.push_back(child_pid);
    // keyboard to a_2
    dup2(A1BtoA2[1], STDOUT_FILENO);
    close(A1BtoA2[0]);
    close(A1BtoA2[1]);
    int you = procB();

    for(pid_t k : kids)
    {

        kill(k, SIGTERM);
    }
    return you;
}
