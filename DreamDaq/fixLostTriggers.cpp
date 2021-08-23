#include <cstdint>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main ( int argc, char** argv )
 {
  if (argc != 2) return -1;
  int runnr = atoi ( argv[1] );
  string ifname = "/home/dreamtest/SPS.2021.08/sps2021data.run"+string(argv[1])+".txt";
  cerr << "fixing run number: " << runnr << " - input file: " << ifname << endl;

  ifstream dataf;
  dataf.open (ifname.c_str(), ifstream::in);

  string line;
  string blankev = "values: 0 0 16 0 1 0 17 0 2 0 18 0 3 0 19 0 4 0 20 0 5 0 21 0 6 0 22 0 7 0 23 0 8 0 24 0 9 0 25 0 10 0 26 0 11 0 27 0 12 0 28 0 13 0 29 0 14 0 30 0 15 0 31 0 32 0 48 0 33 0 49 0 34 0 50 0 35 0 51 0 36 0 52 0 37 0 53 0 38 0 54 0 39 0 55 0 40 0 56 0 41 0 57 0 42 0 58 0 43 0 59 0 44 0 60 0 45 0 61 0 46 0 62 0 47 0 63 0 64 0 80 0 65 0 81 0 66 0 82 0 67 0 83 0 68 0 84 0 69 0 85 0 70 0 86 0 71 0 87 0 72 0 88 0 73 0 89 0 74 0 90 0 75 0 91 0 76 0 92 0 77 0 93 0 78 0 94 0 79 0 95 0 TDC size 0 val.s";
  uint32_t evofs(0);
  while (getline(dataf, line))
   {
    string delimiter = "values:";
    size_t pos = line.find(delimiter);
    string token = line.substr(0, pos);
    string remn = line.substr(pos);
    istringstream iss(token);
    uint32_t evn, cts1, cts2, cts3, tmask;
    std::string dummy[6];
    iss >> dec >> dummy[0] >> dummy[1] >> evn >> dummy[2] >> dummy[3]
	>> cts1 >> cts2 >> cts3 >> dummy[4] >> dummy[5] >> hex >> tmask;

    cout << dec << " ev # " << evn+evofs << " tow cts " << cts1 << " " << cts2
	<< " " << cts3 << " trigger mask " << hex << tmask << " " << remn << endl;

    if (tmask == 0xffff0005)
     {
      evofs ++;
      cout << dec << " ev # " << evn+evofs << " tow cts " << cts1 << " " << cts2
	  << " " << cts3 << " trigger mask " << hex << 0xffffffff << " " << blankev << endl;
     }

   }

  dataf.close();
  return 0;
 }
