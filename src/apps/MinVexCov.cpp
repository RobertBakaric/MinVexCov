/*
 * MinVexCov.cpp
 * 
 * Copyright 2015 Robert Bakaric <rbakaric@irb.hr>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */




#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <MinVertexCover.hpp>
#include <boost/program_options.hpp>
 
 namespace po = boost::program_options;
 using namespace std;
 using namespace vex;
 
void PrintLogo(){
  
   cout <<"\n\
\n\
  __  __ _   __      __        _____           \n\
 |  \\/  (_)  \\ \\    / /       / ____|          \n\
 | \\  / |_ _ _\\ \\  / /____  _| |     _____   __\n\
 | |\\/| | | '_ \\ \\/ / _ \\ \\/ / |    / _ \\ \\ / /\n\
 | |  | | | | | \\  /  __/>  <| |___| (_) \\ V / \n\
 |_|  |_|_|_| |_|\\/ \\___/_/\\_\\\\_____\\___/ \\_/ \n\
                                           \n\
                            by Robert Bakaric \n\
\n\
_________________________________________________________________v0.01\n\
**********************************************************************\n\
\n\
CONTACT:\n\
   This program has been written and is maintained by Robert Bakaric,\n\
   email: rbakaric@irb.hr , bakaric@evolbio.mpg.de                    \n\
                                                                      \n\
\n\
\n\
LICENSE:\n\
   The program is distributed under the GNU General Public License.   \n\
   You should have received a copy of the licence together  with this \n\
   software. If not, see http://www.gnu.org/licenses/                 \n\
______________________________________________________________________\n\
**********************************************************************\n\
" << endl;

                                                           
}



template <typename INT, typename CHARA>
po::variables_map SetOptions(INT& argc, CHARA& argv){

    try {
        int opt;
        string version = "0.01";
        po::options_description desc("Options");
        desc.add_options()
            ("help,h", "produce help message")
            ("version,v", "print version information")
            ("input-file,i", po::value< string >(), "input file")
            ("output-file,o", po::value< string >(), "output file")
        ;

        po::positional_options_description p;
        p.add("input-file,i", -1);
        
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).
                  options(desc).positional(p).run(), vm);
        po::notify(vm);
    
        if (vm.count("help")) {
            cout << "Usage: ./program [options]\n\n";
            PrintLogo();
            cout << desc;
            exit(0);
        }else if (vm.count("version")) {
            cout << "Program version:  " << version << "\n";
            exit(0);
        }
        if (!vm.count("input-file")){
            cout << "Input file is not defined \n";
            exit(0);
        }

        return vm;    
    }
    catch(std::exception& e)
    {
        cout << e.what() << "\n";
        exit(0);
    }    
}


void ComputeMinVexCov(const string file, const string& out){
  
   fstream fs;
   ofstream os;
   streambuf *backup;
   
   if(out.size()>0){
      backup = cout.rdbuf();
      os.open (out.c_str());
      if ( !os.is_open())
         throw runtime_error ("Cannot open file: " + out );
      cout.rdbuf(os.rdbuf()); 
   }
   
   
   fs.open (file.c_str(), ios::in);
   if ( !fs.is_open())
      throw  runtime_error ("Cannot open file: " + file );
   vector<string> child;
   vector<string> parent;


   int i = 0; 
   while( !fs.eof()) {
      if(child.size() == i){
         child.resize((child.size()+1)*2);
         parent.resize((parent.size()+1)*2);
      }
      fs >> child[i];
      fs >> parent[i++] ;
   }  
 
   parent.resize(i-1);
   child.resize(i-1);
   VexCov<string,int> Vex(parent,child);
   vector<string> results = Vex.GetMinVexCov();
   
   cout << "\nMinimum Vertex Cover has: " <<results.size() << " ("<<results.size()<<"/OPT <= " <<Vex.GetError() << ") vertices\n";
   cout << "\nVertices covering the graph:"<< endl;
   for(auto it = results.begin();it!=results.end();it++)
      cout << *it << endl;
   
   
   fs.close();

   if ( os.is_open()){
      cout.rdbuf(backup);
      os.close();
   }
}



int main (int argc, char** argv){

   po::variables_map arg;
   arg = SetOptions(argc,argv);
   unordered_map<string,string> Arg;
try{

  string output = arg.count("output-file") ? arg["output-file"].as<string>() : "";  

/* Filter Sequences */  
    ComputeMinVexCov(arg["input-file"].as<string>(), output);
    
  }catch(runtime_error& e){
    cerr << e.what() << "\n";
  }
  
  return 0;
}
