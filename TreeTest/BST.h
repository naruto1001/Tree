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
	//���캯��
	BinTree() :root(NULL) {}
	//ָ��������־�Ĺ��캯��
	BinTree(T value) : refValue(value), root(NULL) {}
	//��������
	~BinTree() {};

public:
	BinTreeNode<T>* GetRoot() const
	{
		return root;
	}
	//�������������
	void CreateBinTree()
	{
		CreateBinTree(root);
	}
	//����������ݹ飩
	void PerOrder(BinTreeNode<T> *subTree)
	{
		if (subTree != NULL)
		{
			std::cout << subTree->data << " ";
			PerOrder(subTree->leftChild);
			PerOrder(subTree->rightChild);
		}
	}
	//����������ǵݹ飩
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
	//����������ݹ飩
	void InOrder(BinTreeNode<T>* subTree)
	{
		if (subTree != NULL)
		{
			InOrder(subTree->leftChild);
			std::cout << subTree->data << " ";
			InOrder(subTree->rightChild);
		}
	}
	//����������ǵݹ飩
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
	//����������ݹ飩
	void postOrder(BinTreeNode<T> * subTree)
	{
		if (subTree!= NULL)
		{
			postOrder(subTree->leftChild);
			postOrder(subTree->rightChild);
			std::cout << subTree->data << " ";
		}
	}
	//����������ǵݹ飩
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

	//ʹ��ǰ������������������������
	void CreateBindTreeBy_Per_In(BinTreeNode<T>* cur, const char *pre, const char *in, int n)
	{
		if(n <= 0)
		{
			cur = NULL;
			return;
		}
		int k = 0;
		while (pre[0] != in[k])//���������ҵ�pre[0]��ֵ
		{
			k++;
		}
		cur = new BinTreeNode<T>(in[k]);
		CreateBindTreeBy_Per_In(cur->leftChild, pre + 1, in, k);
		CreateBindTreeBy_Per_In(cur->rightChild, pre + k + 1, in + k + 1, n - k - 1);
	}

	//�����������subTreeΪ���Ľڵ����
	int Size(BinTreeNode<T>* subTree) const
	{
		if(subTree == NULL)
		{
			return 0;
		}
		return 1 + Size(subTree->leftChild) + Size(subTree->rightChild);
	}
protected:
	//���ݹ������������
	void CreateBinTree(BinTreeNode<T> *&BT)
	{
		std::stack<BinTreeNode<T>*> s;
		BT = NULL;
		BinTreeNode<T>* p, * t; //p������¼��ǰ�����Ľڵ㣬t������סջ����Ԫ��
		int k;					//k�������������������ı��
		T ch;
		std::cin >> ch;
		while (ch != refValue)
		{
			switch (ch)
			{
			case '('://��(������
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
				if (BT == NULL)				//���ͷ����ǿգ����ø��ڵ�
				{
					BT = p;
				}
				else if (k == 1)				//���kΪ1���ڵ�����t��������
				{
					t = s.top();
					t->leftChild = p;
				}
				else						//���kΪ1���ڵ�����t��������
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
	BinTreeNode<T>* root;		//���ڵ�
	T refValue;					//���������ֹͣ���
};