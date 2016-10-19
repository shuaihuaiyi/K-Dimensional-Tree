#include <iostream>
#include <fstream>
#include "KBTree.h"
//using namespace std;

vector<string> split(string s, string p);
vector<KDDData> readData(const string filename);

int main()
{
	vector<KDDData> result = readData("kddcup.data_10_percent_corrected");
	return 0;
}

vector<string> split(string s, string p)
{ //将s字符串按p分割
	int pos;
	int size = s.size();
	vector<string> result;
	s += p;
	for (int i = 0; i < size; i++)
	{
		pos = s.find(p, i);
		if (pos <= size)
		{
			string temp = s.substr(i, pos - i);
			result.push_back(temp);
			i = pos + p.size() - 1;
		}
	}
	return result;
}

vector<KDDData> readData(const string filename)
{ //从KDD数据文件中读取数据
	vector<KDDData> result;
	KDDData data;
	vector<string> temp;
	string s;
	ifstream in;
	in.open(filename);
	if (in.fail())
	{
		cerr << "打开文件失败" << endl;
		exit(-1);
	}
	while (getline(in, s))
	{
		temp = split(s, ",");
		for (int i = 0; i < 9; i++)
			data.properties[i] = atof(temp[i + 22].data());
		if (temp[41] == "normal")
			data.isNormal = true;
		else if ((temp[41] == "back") || (temp[41] == "land") || (temp[41] == "neptune")
			|| (temp[41] == "pod") || (temp[41] == "teardrop") || (temp[41] == "smurf"))
			data.isDoS = true;
		result.push_back(data);
	}
	in.close();
	return result;
}