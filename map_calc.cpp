#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
template <typename List>
void split(const string& s, const string& delim, List& result)
{
    result.clear();

    string::size_type pos = 0;

    while(pos != std::string::npos )
    {
        string::size_type p = s.find(delim, pos);

        if(p == std::string::npos)
        {
            result.push_back(s.substr(pos));
            break;
        }
        else {
            result.push_back(s.substr(pos, p - pos));
        }

        pos = p + delim.size();
    }
}

void calc_out(std::string mapfile) {
	string line;
	ifstream ifs(mapfile);
	string csvfile = mapfile.substr(0, mapfile.size()-3) + "csv";
	ofstream ofs(csvfile);
	vector<string> str;
	if (ifs.fail())
	{
		cerr << mapfile << " 読込失敗" << endl;
		return;
	}
	if (ofs.fail())
	{
		cerr << csvfile << " 書込失敗" << endl;
		return;
	}

	bool in_rom = false;
	int rom_size = 0;
	int rom_use_size = 0;
	int rom_addr_sta;
    while (getline(ifs, line))
    {
		split(line, " ", str );
#if 0
		for (vector<string>::const_iterator it = str.begin(), e = str.end(); it != e; ++it) {
			cout << "[" << *it << "]";
		}
		cout << endl;
#endif
		if (str[0] == "rom_end") {
			in_rom = false;
			rom_size =  stoi(str[1], nullptr, 16) - rom_addr_sta;
		}
		if ( in_rom ) {
			rom_use_size +=  stoi(str[2], nullptr, 10);
		}
		if (str[0] == "rom_start") {
			in_rom = true;
			rom_addr_sta = stoi(str[1], nullptr, 16);
		}
	}
	ofs << "ROM確保量=" << rom_size << " ROM使用量=" << rom_use_size << endl;
	ofs.close();
}

int main(int argc, char* arg[]){
	if ( argc > 1 && arg[1][0] == '1' ) cout << "1" << endl;
	calc_out("test.txt");
	printf("終わったのでキーを押して\n");
	getchar();
	return 0;
}
