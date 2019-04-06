#include <iostream> 
#include <dirent.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void split_string(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while(std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2-pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if(pos1 != s.length())
		v.push_back(s.substr(pos1));
}

string readFileToJson(string fileName) {
	int pos = fileName.find('_');
	string name = fileName.substr(0, pos);
	int pos2 = fileName.find('_', pos + 1);
	string row = fileName.substr(pos + 1, pos2 - pos -1);
	pos = pos2;
	pos2 = fileName.find('.');
	string col = fileName.substr(pos + 1, pos2 - pos - 1);
	
	string json = "{\"title\":\"" + name + "\",\"row\":\"" + row + "\",\"col\":\"" + col + "\",\"config\":{";
	
	ifstream fin("/Users/liyi/Desktop/database/" + fileName);
	string s;
	getline(fin, s);
	if(s[s.length() - 1] == '\r') {
		s = s.substr(2, s.length() - 3);
	} else {
		s = s.substr(2);
	}
	vector<string> cols;
	split_string(s, cols, " ");
	
	string rowdata = "\"rowdata\":[";
	string coldata = "\"coldata\":[";
	
	bool first = true;
	bool first_r = true;
	while(getline(fin, s)) {
		if(s[s.length() - 1] == '\r') {
			s = s.substr(0, s.length() - 1);
		} else {
			s = s.substr(0);
		}
		vector<string> row;
		split_string(s, row, " ");
		
		if (first) {
			first = false;
		} else {
			json += ",";
		}
		for (int i = 1; i < row.size(); i++) {
			if (i != 1) {
				json += ", ";
			}
			json += "\"" + row[0] + "_" + cols[i - 1] + "\":" + row[i];
		}
		
		if (first_r) {
			rowdata += row[0];
			first_r = false;
		} else {
			rowdata += "," + row[0];
		}
	}
	
	coldata += cols[1];
	for (int i = 2; i < cols.size(); i++) {
		coldata += "," + cols[i];
	}
	coldata += "]";
	rowdata += "]";
	
	json += "}," + rowdata + "," + coldata + "}";
	return "\"" + name + "\":" + json;
}

int main()  
{  
	DIR* dir = opendir("./database");
	dirent* p = NULL;
	ofstream fou("./data.txt");
        fou << "{";
	
	bool first = true;
	while((p = readdir(dir)) != NULL)
	{  	
		if(p->d_name[0] != '.') 
		{  
			string name = string(p->d_name); 
			string json = readFileToJson(name); 
			
			if (first) {
				first = false;
			} else {
				fou << ",";
			}
			
                        fou << json;;
		}  
	}  
        fou << "}";
	closedir(dir);
}
