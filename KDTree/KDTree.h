#pragma once
#include <string>
#include <set>
#include <list>
#include <vector>
//定义测试结果：
#define IS_NORMAL 0
#define IS_DOS 1
#define OTHERS 2
#define	new_max 2
#define new_min 0
#define bucket_size 5

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
	int d = 0;			//分割维
	double spno;		//分割点
//	double max = new_max;		//最大值
//	double min = new_min;		//最小值
	KDTreeNode* lc = nullptr;	//小于等于分割点的分支
	KDTreeNode* gc = nullptr;	//大于分割点的分支
	list<KDDData*> value;	//如果是叶结点，在这里保存数据点的指针
};

class KDTree
{
public:
	KDTree(set<KDDData*>& datas);
	~KDTree();
	void test(set<KDDData*> testDatas);
	int getResult(KDDData testData);

private:
	void buildTree(KDTreeNode* node) const;

	KDTreeNode* root;
	double radios[9];		//用于规格化时的比例，-1表示某维度只有常数值
};

inline KDTree::KDTree(set<KDDData*>& datas)
{
	double maxs[9];		//第N维的最大值
	double mins[9];		//第N维的最小值
	if (datas.empty())
	{
		cerr << "用于建立KD树的数据集是空集" << endl;
		return;
	}
	//else
	//获取数据边界
	for (int i = 0; i < 9; ++i)
		mins[i] = maxs[i] = (*(datas.begin()))->properties[i];
	for (KDDData* data : datas)
	{
		for (int i = 0; i < 9; i++)
		{
			maxs[i] = data->properties[i] > maxs[i] ? data->properties[i] : maxs[i];
			mins[i] = data->properties[i] < mins[i] ? data->properties[i] : mins[i];
		}
	}
	//规格化数据
	for (int i = 0; i < 9; ++i)
	{
		if (maxs[i] - mins[i] == 0)
		{
			radios[i] = -1;
			continue;
		}
		radios[i] = (new_max - new_min) / (maxs[i] - mins[i]);
		for (KDDData* data : datas)
			data->properties[i] = (data->properties[i] - mins[i])*radios[i];//+new_min
	}
	//递归建树
	root = new KDTreeNode;
	for (KDDData* data : datas)
		root->value.push_back(data);
	buildTree(root);
}

inline void KDTree::buildTree(KDTreeNode* node) const
{//递归建树
	double maxs[9];		//第N维的最大值
	double mins[9];		//第N维的最小值
	double maxrange = 0;	//最大延展度
	if (node->value.size() <= bucket_size)
		return;
	//获取数据边界
	for (int i = 0; i < 9; ++i)
		mins[i] = maxs[i] = node->value.front()->properties[i];
	for (KDDData* data : node->value)
	{
		for (int i = 0; i < 9; i++)
		{
			maxs[i] = data->properties[i] > maxs[i] ? data->properties[i] : maxs[i];
			mins[i] = data->properties[i] < mins[i] ? data->properties[i] : mins[i];
		}
	}
	//找出具有最大延展度的维
	for (int i = 0; i < 9; ++i)
	{
		if (maxrange < (maxs[i] - mins[i]))
		{
			maxrange = maxs[i] - mins[i];
			node->d = i;
		}
	}
	if (maxrange == 0)
		return;
	//规定分割点，将点集分割
	node->spno = mins[node->d] + maxrange / 2;
	node->gc = new KDTreeNode;
	node->lc = new KDTreeNode;
	for (KDDData* data : node->value)
	{
		if (data->properties[node->d] > node->spno)
			node->gc->value.push_back(data);
		else
			node->lc->value.push_back(data);
	}
	//递归建树
	buildTree(node->lc);
	buildTree(node->gc);
}

inline KDTree::~KDTree()
{
	//todo 完成析构函数
}

inline void KDTree::test(set<KDDData*> testDatas)
{
	//规格化测试数据

	//todo 
}

inline int KDTree::getResult(KDDData testData)
{

	return OTHERS;
}
