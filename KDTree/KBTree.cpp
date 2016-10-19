#include <iostream>
#include <fstream>
#include "KBTree.h"
using namespace std;

struct KDDData
{
	double duration;		//length (number of seconds) of the connection
	string protocol_type;	//type of the protocol, e.g. tcp, udp, etc.
	string service;			//network service on the destination, e.g., http, telnet,etc.
	double src_bytes;		//number of data bytes from source to destination

};

void readData(const string filename, vector<KDDData> datas)
{  //从KDD数据文件中读取数据
	KDDData datarow;
	datas.push_back(datarow);

}

int main()
{

	return 0;
}