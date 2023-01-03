#include <iostream>
#include <string>
#include <fstream>
#include "gameLoops.h"

int main(int argc, char *argv[]){
    std::ofstream ofs("output.txt");
    std::streambuf* coutbuf = std::cout.rdbuf(ofs.rdbuf());
    std::string fileName = "log.txt";
    gameLoops::replay_loop(fileName);
    return 0;
}