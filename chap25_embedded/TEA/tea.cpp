#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <fstream>

#include "TEA.hpp"

using namespace tea_ppp;

//------------------------------------------------------------------------------

const std::string option_encipher {"encipher"};
const std::string option_decipher {"decipher"};

//------------------------------------------------------------------------------

void encipher_file(std::ifstream& inf, std::ofstream& outf, const Ulong * const k, const int& nchar){
    Ulong outptr[2];
    char inbuf[nchar];
    Ulong* inptr = reinterpret_cast<Ulong*>(inbuf);
    int counter = 0;
    while(inf.get(inbuf[counter])){
        outf << std::hex; //use hexadecimal output
        if(++counter == nchar){
            encipher(inptr, outptr, k);
            //pad with leading zeros;
            outf << std::setw(8) << std::setfill('0') << outptr[0] << ' ' 
                << std::setw(8) << std::setfill('0') << outptr[1] << ' ';
            counter = 0;
        }
    }
    if(counter){ //pad
        while(counter != nchar) inbuf[counter++] = '0';
        encipher(inptr, outptr, k);
    outf << outptr[0] << ' ' << outptr[1] << ' ';
    }
}

void decipher_file(std::ifstream& inf, std::ofstream& outf, const Ulong * const k, const int& nchar){
    Ulong inptr[2];
    char outbuf[nchar+1];
    outbuf[nchar]=0; //terminator
    Ulong* outptr = reinterpret_cast<Ulong*>(outbuf);
    inf.setf(std::ios_base::hex, std::ios_base::basefield); // use hexadecimal input

    while(inf >> inptr[0] >> inptr[1]){
        decipher(inptr, outptr, k);
        outf << outbuf;
    }
}

int main(int argc, char* argv[]){
    try {

        // PARSE ARGUMENTS //TODO use some CLI package, e.g. Lyra
        if (argc < 2 ) throw std::runtime_error {"argument not given (1 required)"};
        if( argc > 2 ) throw std::runtime_error {"too many arguments (1 required)"};
        std::string option{argv[1]};
        if (option != option_encipher && option != option_decipher) 
            throw std::runtime_error {"wrong argument, specify \"encipher\" or \"decipher\""};

        // PREPARE
        const int nchar = 2*sizeof(Ulong);   //64 bits
        const int kchar = 2*nchar;          //128 bits
        std::string op;
        std::string key;
        std::string infile;
        std::string outfile;
        if (option == option_encipher)
            std::cout << "please enter input file name to encrypt, output file name, and key:\n";
        else if (option == option_decipher)
            std::cout << "please enter file name of encrypted file, output file name, and key:\n";
        std::cin >> infile >> outfile >> key;

        while(key.size()<kchar) key += '0';     // pad key

        std::ifstream inf{infile};
        std::ofstream outf{outfile};
        if(!inf || !outf) throw std::runtime_error{"bad filename"};
        const Ulong* k = reinterpret_cast<const Ulong*>(key.data()); 

        // DO STUFF
        if ( option == option_encipher )
            encipher_file(inf, outf, k, nchar);
        else if (option == option_decipher)
            decipher_file(inf, outf, k, nchar);
        
        return 0;
    }
    catch(std::exception& e){
        std::cerr << e.what() << "\n";
        return 1;
    }
    catch(...){
        std::cerr << "something went wrong\n";
        return 2;
    }
}

