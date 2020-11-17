#pragma once
#include <stack>
#include <iostream>

template<typename T>
struct BinTreeNode
{
	T data;
	BinTreeNode<T> *leftChild, *rightChild;
	BinTreeNode() :leftChild(NULL), rightChild(NULL) {};
	BinTreeNode(T x, BinTreeNode* l = NULL, BinTreeNode* r = NULL) :data(x), leftChild(l), rightChild(r) {};
};

template<typename T>
class BinTree
{
public:
	//构造函数
	BinTree() :root(NULL) {}
	//指定结束标志的构造函数
	BinTree(T value) : refValue(value), root(NULL) {}
	//析构函数
	~BinTree() {};

public:
	BinTreeNode<T>* GetRoot() const
	{
		return root;
	}
	//广义表创建二叉树
	void CreateBinTree()
	{
		CreateBinTree(root);
	}
	//先序遍历（递归）
	void PerOrder(BinTreeNode<T> *subTree)
	{
		if (subTree != NULL)
		{
			std::cout << subTree->data << " ";
			PerOrder(subTree->leftChild);
			PerOrder(subTree->rightChild);
		}
	}
	//先序遍历（非递归）
	void PerOrder_NoRecurvel(BinTreeNode<T> *subTree)
	{
		std::stack<BinTreeNode<T>*> s;
		s.push(NULL);
		while (subTree != NULL)
		{
			std::cout << subTree->data << " ";
			if (subTree->rightChild != NULL)
			{
				s.push(subTree->rightChild);
			}
			if (subTree->leftChild != NULL)
			{
				subTree = subTree->leftChild;
			}
			else
			{
				subTree = s.top();
				s.pop();
			}
		}
	}
	//中序遍历（递归）
	void InOrder(BinTreeNode<T>* subTree)
	{
		if (subTree != NULL)
		{
			InOrder(subTree->leftChild);
			std::cout << subTree->data << " ";
			InOrder(subTree->rightChild);
		}
	}
	//中序遍历（非递归）
	void InOrder_NoRecurvel(BinTreeNode<T>* subTree)
	{
		std::stack<BinTreeNode<T>*> s;
		do 
		{
			while (subTree != NULL)
			{
				s.push(subTree);
				subTree = subTree->leftChild;
			}
			if (!s.empty())
			{
				subTree = s.top();
				s.pop();
				std::cout << subTree->data << " ";
				subTree = subTree->rightChild;
			}
		} while (subTree != NULL || !s.empty());
	}
	//后序遍历（递归）
	void postOrder(BinTreeNode<T> * subTree)
	{
		if (subTree!= NULL)
		{
			postOrder(subTree->leftChild);
			postOrder(subTree->rightChild);
			std::cout << subTree->data << " ";
		}
	}
	//后序遍历（非递归）
	void postOrder_NoRecurve(BinTreeNode<T>* subTree)
	{
		if (root == NULL)
			return;
		std::stack<BinTreeNode<T>*> s;
		s.push(subTree);
		BinTreeNode<T>* lastPop = NULL;
		while (!s.empty())
		{
			while (s.top()->leftChild != NULL)
			{
				s.push(s.top()->leftChild);
			}
			while (!s.empty())
			{
				if(lastPop == s.top()->rightChild || s.top()->rightChild == NULL)
				{
					std::cout << s.top()->data << " ";
					lastPop = s.top();
					s.pop();
				}
				else if(s.top()->rightChild != NULL)
				{
					s.push(s.top()->rightChild);
					break;
				}
			}
		}
	}

	//使用前序遍历和中序遍历创建二叉树
	void CreateBindTreeBy_Per_In(BinTreeNode<T>* cur, const char *pre, const char *in, int n)
	{
		if(n <= 0)
		{
			cur = NULL;
			return;
		}
		int k = 0;
		while (pre[0] != in[k])//在中序中找到pre[0]的值
		{
			k++;
		}
		cur = new BinTreeNode<T>(in[k]);
		CreateBindTreeBy_Per_In(cur->leftChild, pre + 1, in, k);
		CreateBindTreeBy_Per_In(cur->rightChild, pre + k + 1, in + k + 1, n - k - 1);
	}

	//计算二叉树以subTree为根的节点个数
	int Size(BinTreeNode<T>* subTree) const
	{
		if(subTree == NULL)
		{
			return 0;
		}
		return 1 + Size(subTree->leftChild) + Size(subTree->rightChild);
	}
protected:
	//根据广义表创建二叉树
	void CreateBinTree(BinTreeNode<T> *&BT)
	{
		std::stack<BinTreeNode<T>*> s;
		BT = NULL;
		BinTreeNode<T>* p, * t; //p用来记录当前创建的节点，t用来记住栈顶的元素
		int k;					//k是用来处理左右子树的标记
		T ch;
		std::cin >> ch;
		while (ch != refValue)
		{
			switch (ch)
			{
			case '('://对(做处理
				s.push(p);
				k = 1;
				break;
			case ')':
				s.pop();
				break;
			case ',':
				k = 2;
				break;
			default:
				p = new BinTreeNode<T>(ch);
				if (BT == NULL)				//如果头结点是空，设置根节点
				{
					BT = p;
				}
				else if (k == 1)				//如果k为1将节点链入t的左子树
				{
					t = s.top();
					t->leftChild = p;
				}
				else						//如果k为1将节点链入t的右子树
				{
					t = s.top();
					t->rightChild = p;
				}
				break;
			}
			std::cin >> ch;
		}
	}
private:
	BinTreeNode<T>* root;		//根节点
	T refValue;					//数据输入的停止标记
};