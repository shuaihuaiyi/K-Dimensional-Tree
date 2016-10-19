#include <iostream>
#include <fstream>
#include "KBTree.h"
using namespace std;

struct KDDData
{
	/*//基本属性集
	double duration;		//length (number of seconds) of the connection					0
	string protocol_type;	//type of the protocol, e.g. tcp, udp, etc.						1
	string service;			//network service on the destination, e.g., http, telnet,etc.	2
	string flag;			//normal or error status of the connection						3
	double src_bytes;		//number of data bytes from source to destination				4
	double dst_bytes;		//number of data bytes from destination to source				5
	bool land;				//1 if connection is from/to the same host/port;0 otherwise		6
	double wrong_fragment;	//number of ``wrong'' fragments									7
	double urgent;			//number of urgent packets										8
	//忽略特征9~21
	//流量属性集
	double count; 			//number of connections to the same host as the current connection in the past two seconds		22
	double srv_count;		//number of connections to the same service as the current connection in the past two seconds	23
	double serror_rate;		//% of connections that have ``SYN'' errors						24
	double srv_serror_rate;	//% of connections that have ``SYN'' errors						25
	double rerror_rate;		//% of connections that have ``REJ'' errors						26
	double srv_rerror_rate;	//% of connections that have ``REJ'' errors						27
	double same_srv_rate;	//% of connections to the same service							28
	double diff_srv_rate;	//% of connections to different services						29
	double srv_diff_host_rate;//% of connections to different hosts							30
	//忽略特征31~40*/
	double properties[9];	//所有的流量属性，对应源数据中的第22-30项
	string label;			//这个连接的类型，back，land，neptune，pod，teardrop，smurf表示DoS攻击			41
};

vector<string> split(string s, string p)
{	//将s字符串按p分割
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
{	//从KDD数据文件中读取数据
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
		data.label = temp[41];
		result.push_back(data);
	}
	in.close();
	return result;
}

int main()
{
	KDDData b;
	vector<KDDData> a;
	a.push_back(b);
	b.count = 0;
	a.push_back(b);
	return 0;
}