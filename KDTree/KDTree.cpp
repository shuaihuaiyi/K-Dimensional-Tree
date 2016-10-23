#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include "KDTree.h"
//using namespace std;

vector<string> split(string& s, const string& p);
vector<KDDData>* readData(const string& filename);
vector<KDDData>* readTestData(const string& filename);

int main()
{
	cout << "╔════════════════════════════════════════════╗" << endl;
	cout << "║                                  基于KD树的DoS异常检测                                 ║" << endl;
	cout << "║                                                                                        ║" << endl;
	cout << "║                                                                           作者：率怀一 ║" << endl;
	cout << "║                                                                         2016年10月23日 ║" << endl;
	cout << "╚════════════════════════════════════════════╝" << endl;
	cout << "\n************************************** 读取训练数据 ***************************************" << endl;
	vector<KDDData>* result = readData("kddcup.data_10_percent_corrected");
	cout << "\n**************************************** 建立KD树 *****************************************" << endl;
	KDTree kdt(result);
	cout << "\n************************************** 读取测试数据 ***************************************" << endl;
	vector<KDDData>* test = readTestData("corrected");
	cout << "\n**************************************** 执行测试 *****************************************" << endl;
	kdt.test(test);
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

vector<KDDData>* readTestData(const string& filename)
{
	unordered_set<KDDData> result;
	vector<KDDData>* r;
	KDDData data;
	vector<string> temp;
	string s;
	ifstream in;
	clock_t start, finish;
	double totaltime;
	cout << "正在读取文件 " << filename << " ...";
	int cEntry = 0;
	start = clock();
	in.open(filename);
	if (in.fail())
	{
		cerr << "打开文件失败！" << endl;
		exit(-1);
	}
	temp.reserve(50);
	while (getline(in, s))
	{
		++cEntry;
		temp = split(s, ",");
		for (int i = 0; i < 9; i++)
			data.properties[i] = atof(temp[i + 22].data());
		if ("normal." == temp[41])
			data.label = IS_NORMAL;
		else if (("back." == temp[41]) || ("land." == temp[41]) || ("neptune." == temp[41])
			|| ("pod." == temp[41]) || ("teardrop." == temp[41]) || ("smurf." == temp[41]))
			data.label = IS_DOS;
		result.insert(data);
	}
	in.close();
	r = new vector<KDDData>();
	r->reserve(result.size());
	for (KDDData d : result)
		r->push_back(d);
	finish = clock();
	totaltime = double(finish - start) / CLOCKS_PER_SEC;
	cout << "完成！\n\t已处理流量" << cEntry << "条。去除重复无效条目，用于测试KD树的数据集大小为" << r->size() << endl;
	cout << "\t大致耗时" << totaltime << "秒" << endl;
	return r;
}

vector<KDDData>* readData(const string& filename)
{ //从KDD数据文件中读取数据
	unordered_set<KDDData> result;
	vector<KDDData>* r;
	KDDData data;
	vector<string> temp;
	string s;
	ifstream in;
	clock_t start, finish;
	double totaltime;
	cout << "正在读取文件 " << filename << " ...";
	int cEntry = 0, cNormal = 0, cDoS = 0;
	start = clock();
	in.open(filename);
	if (in.fail())
	{
		cerr << "打开文件失败！" << endl;
		exit(-1);
	}
	temp.reserve(50);
	while (getline(in, s))
	{
		++cEntry;
		temp = split(s, ",");
		if ("normal." == temp[41])
		{
			data.label = IS_NORMAL;
			++cNormal;
			for (int i = 0; i < 9; i++)
				data.properties[i] = atof(temp[i + 22].data());
			result.insert(data);
		}
		else if (("back." == temp[41]) || ("land." == temp[41]) || "neptune." == temp[41]
			|| ("pod." == temp[41]) || ("teardrop." == temp[41]) || ("smurf." == temp[41]))
		{
			++cDoS;
			data.label = IS_DOS;
			for (int i = 0; i < 9; i++)
				data.properties[i] = atof(temp[i + 22].data());
			result.insert(data);
		}
	}
	in.close();
	r = new vector<KDDData>();
	r->reserve(result.size());
	for (KDDData d : result)
		r->push_back(d);
	finish = clock();
	totaltime = double(finish - start) / CLOCKS_PER_SEC;
	cout << "完成！\n\t已处理流量" << cEntry << "条。其中，正常流量" << cNormal << "条；DoS攻击" << cDoS << "条。" << endl;
	cout << "\t去除重复无效条目，用于建立KD树的数据集大小为" << r->size() << endl;
	cout << "\t大致耗时" << totaltime << "秒" << endl;
	return r;
}
