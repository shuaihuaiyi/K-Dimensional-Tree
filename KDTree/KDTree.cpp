#include <iostream>
#include <fstream>
#include <time.h>
#include "KDTree.h"
//using namespace std;

vector<string> split(string& s, const string& p);
list<KDDData> readData(const string& filename, int divider);

int main()
{
	clock_t start, finish;
	string s;
	int i = 0;
	double totaltime;
//	std::ios_base::sync_with_stdio(false);
	start = clock();

	list<KDDData> result = readData("kddcup.data_10_percent_corrected", 500);
	finish = clock();
	totaltime = double(finish - start) / CLOCKS_PER_SEC;
	cout << "此程序的运行时间为" << totaltime << "秒！" << endl;
	return 0;
}

vector<string> split(string& s, const string& p)
{ //将s字符串按p分割
	int pos;
	int size = s.size();
	vector<string> result;
	result.reserve(50);
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

list<KDDData> readData(const string& filename, int divider)
{ //从KDD数据文件中读取1/n的数据
	list<KDDData> result;
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
	temp.reserve(50);
	while (getline(in, s))
	{
		for (int i = 0;i < divider; i++)
		{
			if (!getline(in, s))
			{
				in.close();
				return result;
			}
		}
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