#pragma once
#include <vector>
#include <string>
//定义测试结果：
#define IS_NORMAL 0
#define IS_DOS 1
#define OTHERS 2

using namespace std;


struct KDTreeNode
{
	int d;			//分割维
	double v;		//分割点
	double max;		//最大值
	double min;		//最小值
	KDTreeNode* lc = nullptr;	//小于等于分割点的分支
	KDTreeNode* gc = nullptr;	//大于分割点的分支
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

	return nullptr;
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
