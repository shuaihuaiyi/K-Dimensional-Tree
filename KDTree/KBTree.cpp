#include <iostream>
#include <fstream>
#include "KBTree.h"
using namespace std;

struct KDDData
{
<<<<<<< .mine
	//基本属性集
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
	//忽略特征31~40
	string label;			//这个连接的类型												41
=======
	//基本属性集
	double duration;		//length (number of seconds) of the connection
	string protocol_type;	//type of the protocol, e.g. tcp, udp, etc.
	string service;			//network service on the destination, e.g., http, telnet,etc.
	string flag;			//normal or error status of the connection
	double src_bytes;		//number of data bytes from source to destination
	double dst_bytes;		//number of data bytes from destination to source
	bool land;				//1 if connection is from/to the same host/port;0 otherwise
	double wrong_fragment;	//number of ``wrong'' fragments
	double urgent;			//number of urgent packets
	//忽略特征10~22,共13个数据
	//流量属性集
	double count; 			//number of connections to the same host as the current connection in the past two seconds
	double srv_count;		//number of connections to the same service as the current connection in the past two seconds
	double serror_rate;		//% of connections that have ``SYN'' errors
	double srv_serror_rate;	//% of connections that have ``SYN'' errors
	double rerror_rate;		//% of connections that have ``REJ'' errors
	double srv_rerror_rate;	//% of connections that have ``REJ'' errors
	double same_srv_rate;	//% of connections to the same service
	double diff_srv_rate;	//% of connections to different services
	double srv_diff_host_rate;//% of connections to different hosts


>>>>>>> .theirs
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