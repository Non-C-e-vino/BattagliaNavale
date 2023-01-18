/**
 * 
 * @author Callegaro Gabriele
 * 
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include "replayLoops.h"

#define DELAY_MS 1000

int main(int argc, char *argv[])
{

    if(argc == 3 && !std::strcmp(argv[1], "v"))
    {

        std::string fileName = argv[2];
        gameLoops::replay_loop(fileName, DELAY_MS);

    }else if(argc == 4 && !std::strcmp(argv[1], "f"))
    {

        std::string fileName = argv[2];
        std::ofstream ofs(argv[3]);

        if(!ofs.is_open())
        {
            std::cout << "Impossibile aprire file di output." << std::endl;
            return 0;
        }
        std::cout << "Avvio scrittura su file..." << std::endl;
        std::streambuf* coutbuf = std::cout.rdbuf(ofs.rdbuf());

        gameLoops::replay_loop(fileName);

        std::cout.rdbuf(coutbuf);
        std::cout << "scrittura terminata." << std::endl;
        
    }else std::cout << "Fornire degli argomenti validi:\n\t"
        << "argomenti \"v\" [nome_file_log]:\n\t"
        << "  stampa a video il replay del file di log indicato;\n\t"
        << "argomenti \"f\" [nome_file_log] [nome_file_output_replay]:\n\t" 
        << "  scrive su file il replay del file di log indicato.\n" << std::endl;
    return 0;
}