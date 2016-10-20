#pragma once
#include <vector>
#include <string>
//定义测试结果：
#define IS_NORMAL 0
#define IS_DOS 1
#define OTHERS 2

using namespace std;

struct KDDData
{
	/*
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
	*/
	double properties[9];	//流量属性集，对应源数据中的第22-30项
	bool isNormal = false;	//这个连接的类型，normal表示正常流量										41
	bool isDoS = false;		//这个连接的类型，back，land，neptune，pod，teardrop，smurf表示DoS攻击		41
};
struct KDTreeNode
{
	int d;			//分割维
	double v;		//分割点
	double max;		//最大值
	double min;		//最小值
	KDTreeNode* lc = NULL;	//小于等于分割点的分支
	KDTreeNode* gc = NULL;	//大于分割点的分支
	vector<KDDData> value;	//如果是叶结点，在这里保存数据点
};

class KDTree
{
public:
	KDTree(vector<KDDData> datas);
	~KDTree();
	void test(vector<KDDData> testDatas);
	int getResult(KDDData testData);

private:
	KDTreeNode * buildTree();
	KDTreeNode * root;
};

KDTree::KDTree(vector<KDDData> datas)
{
	double new_max = 2;
	double new_min = 0;
	double maxs[9];
	double mins[9];
	if (datas.empty())
	{
		cerr << "用于建立KD树的数据集是空集" << endl;
		return;
	}
	for (vector<KDDData>::iterator data = datas.begin();data != datas.end();++data)
	{
		for (int i = 0; i < 9; i++)
		{
			maxs[i] = data->properties[i];
			mins[i] = data->properties[i];
		}
	}
	//TODO:规格化
	
	//todo 递归建树
}

KDTreeNode * KDTree::buildTree()
{//递归建树

	return NULL;
}

KDTree::~KDTree()
{

}

inline void KDTree::test(vector<KDDData> testDatas)
{

}

inline int KDTree::getResult(KDDData testData)
{

	return OTHERS;
}
