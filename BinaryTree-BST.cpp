#include <iostream>
#include <limits.h>
#include<queue>
using std::cout;
using std::endl;
using std::queue;
using std::max;

struct NODE{
	int key;
	NODE* left;
	NODE* right;
};

NODE* createNode(int data){
	NODE* newNode = new NODE;
	newNode->key = data;
	newNode->left = nullptr;
	newNode->right = nullptr;
	return newNode;
}

void Insert(NODE* &pRoot, int x){
	if (!pRoot){
		pRoot = createNode(x);
		return;
	}
	
	if (pRoot->key > x){
		Insert(pRoot->left, x);
	}else{
		Insert(pRoot->right, x);
	}
}

void InsertIteratively(NODE* &pRoot, int x){
	NODE* prev = nullptr;
	NODE* cur = pRoot;
	while (cur){
		prev = cur;
		if (cur->key > x){
			cur = cur->left;
		}
		else cur = cur->right;
	}
	if (!prev) {
		pRoot = createNode(x);
		return;
	}
	
	if (prev->key > x){
		prev->left = createNode(x);
	}else{
		prev->right = createNode(x);
	}
}

void LNR(NODE* pRoot){
	if (pRoot->left) LNR(pRoot->left);
	cout << pRoot->key << ' ';
	if (pRoot->right) LNR(pRoot->right);
}

void NLR(NODE* pRoot){
	cout << pRoot->key << ' ';
	if (pRoot->left) NLR(pRoot->left);
	if (pRoot->right) NLR(pRoot->right);
}

void LRN(NODE* pRoot){
	if (pRoot->left) LRN(pRoot->left);
	if (pRoot->right) LRN(pRoot->right);
	cout << pRoot->key << ' ';
}

void LevelOrder(NODE* pRoot){
	queue<NODE*> q;
	q.push(pRoot);
	while(!q.empty()){
		NODE* tmp = q.front();
		q.pop();
		cout << tmp->key << ' ';
		if (tmp->left) q.push(tmp->left);
		if (tmp->right) q.push(tmp->right);
	}
	cout << endl;
}

int Height(NODE* pRoot){
	if (!pRoot) return 0;
	int h1 = Height(pRoot->left) + 1;
	int h2 = Height(pRoot->right) + 1;
	return max(h1, h2);
}

int countNode(NODE* pRoot){
	if (!pRoot) return 0;
	
	return countNode(pRoot->left) + countNode(pRoot->right) + 1;
}

int sumNode(NODE* pRoot){
	if (!pRoot) return 0;
	return sumNode(pRoot->left) + sumNode(pRoot->right) + pRoot->key;
}

NODE* Search(NODE* pRoot, int x){
	if (!pRoot) return nullptr;
	if (pRoot->key == x) return pRoot;
	if (pRoot->key > x){
		return Search(pRoot->left, x);
	}else{
		return Search(pRoot->right, x);
	}
}

NODE* getMinNode(NODE* pRoot){
	if (pRoot->left){
		return getMinNode(pRoot->left);
	}
	return pRoot;
}

void Remove(NODE* &pRoot, int x){
	if (!pRoot){
		return;
	}
	
	if (pRoot->key > x)Remove(pRoot->left, x);
	else if (pRoot->key < x) Remove(pRoot->right, x);
	else {
		if (!pRoot->left && !pRoot->right){
			delete pRoot;
			pRoot = nullptr;
			return;
		}
		if (!pRoot->left){
			delete pRoot;
			pRoot = pRoot->right;
			return;
		}
		if (!pRoot->right){
			delete pRoot;
			pRoot = pRoot->left;
			return;
		}
		NODE* minNode = getMinNode(pRoot->right);
		pRoot->key = minNode->key;
		Remove(pRoot->right, minNode->key);
	}
}

NODE* createTree(int a[], int n){
	NODE* BST = nullptr;
	for (int i = 0; i < n; i++){
		Insert(BST, a[i]);
	}
	return BST;
}

void removeTree(NODE* &pRoot){
	queue<NODE*> q;
	q.push(pRoot);
	while (!q.empty()){
		NODE* tmp = q.front();
		q.pop();
		if (tmp->left) q.push(tmp->left);
		if (tmp->right) q.push(tmp->right);
		delete tmp;
	}
	pRoot = nullptr;
}

int heightNode(NODE* pRoot, int value){
	if (!pRoot) return -1;
	if (pRoot->key == value) return Height(pRoot);
	if (pRoot->key > value) return heightNode(pRoot->left, value);
	return heightNode(pRoot->right, value);
}

int Level(NODE* pRoot, NODE* p){
	queue<NODE*> q;
	q.push(pRoot);
	int cur_level = 0;
	while (!q.empty()){
		int size = q.size();
		cur_level++;
		while (size > 0){
			NODE* tmp = q.front();
			q.pop();
			size--;
			if (tmp == p){
				return cur_level;
			}
			if (tmp->left) q.push(tmp->left);
			if (tmp->right) q.push(tmp->right);
		}
	}
	return -1;
}

int countLeaf(NODE* pRoot){
	if (!pRoot) return 0;
	if (!pRoot->left && !pRoot->right) return 1;
	return countLeaf(pRoot->left) + countLeaf(pRoot->right);
}

int countLess(NODE* pRoot, int x){
	if (!pRoot) return 0;		
	if (pRoot->key >= x){
		return countLess(pRoot->left, x);
	}
	return countLess(pRoot->left, x) + countLess(pRoot->right, x)+ 1;
}

int countGreater(NODE* pRoot, int x){
	if (!pRoot) return 0;		
	if (pRoot->key <= x){
		return countGreater(pRoot->right, x);
	}
	return countGreater(pRoot->left, x) + countGreater(pRoot->right, x) + 1;
}

bool isBST(NODE* pRoot, int min, int max){
	if (!pRoot) return true;
	if (pRoot->key <= min || pRoot->key >= max) return false;
	return isBST(pRoot->left, min, pRoot->key) && isBST(pRoot->right, pRoot->key ,max);
}

bool isFullBT(NODE* pRoot){
	if (!pRoot) return true;
	if (!pRoot->left && !pRoot->right) return true;
	if (pRoot->left && pRoot->right) return isFullBT(pRoot->left) && isFullBT(pRoot->right);
	return false;
}

int main(){
	NODE* BST = nullptr;
	NODE* BST1 = nullptr;
	Insert(BST, 9);
	Insert(BST, 8);
	Insert(BST, 6);
	Insert(BST, 10);
	Insert(BST, 11);
	Insert(BST, 3);
	Insert(BST, 5);
	Insert(BST, 4);
	Insert(BST, 1);
	Insert(BST, 7);
	LNR(BST);
	cout << endl;
	InsertIteratively(BST1, 9);
	InsertIteratively(BST1, 8);
	InsertIteratively(BST1, 6);
	InsertIteratively(BST1, 10);
	InsertIteratively(BST1, 11);
	InsertIteratively(BST1, 3);
	InsertIteratively(BST1, 5);
	InsertIteratively(BST1, 4);
	InsertIteratively(BST1, 1);
	InsertIteratively(BST1, 7);
	LNR(BST1);
	
	cout << endl;
	NLR(BST);
	cout << endl;
	LRN(BST);
	cout << endl; 
	LevelOrder(BST);
	cout << endl; 
	cout << Height(BST);
	cout << endl;
	cout << countNode(BST);
	cout << endl;
	cout << sumNode(BST);
	cout << endl;
	NLR(Search(BST, 6));
	cout << endl;
	cout << endl;
	//Remove(BST, 3);
	LNR(BST);
	cout << endl;
	NLR(BST);
	cout << endl;
	LRN(BST);
	cout << endl; 
	cout << endl;
	int a[10] = {1,4,2,3,7,6,9,5,10,8};
	NODE* BST2 = createTree(a, 10);
	LNR(BST2);
	cout << endl;
	NLR(BST2);
	cout << endl;
	LRN(BST2);
	// cout << endl; 
	// cout << endl; 
	// removeTree(BST2);
	cout << endl; 
	cout << endl; 
	cout << heightNode(BST, 12);
	cout << endl; 
	cout << endl; 
	cout << Level(BST, Search(BST, 3));
	cout << endl;
	cout << endl;
	cout << countLeaf(BST);
	cout << endl;
	cout << endl;
	cout << countLess(BST, 9);
	cout << endl;
	cout << endl;
	cout << countGreater(BST,6);
	cout << endl;
	cout << endl;
	if (!isBST(BST, INT_MIN, INT_MAX)) cout << "false"; else cout <<"true" << endl;
	
	NODE* tmp = new NODE{1,nullptr, nullptr};
	tmp->right = new NODE{3,nullptr, nullptr};
	tmp->right->left = new NODE{2,nullptr, nullptr};
	tmp->left = new NODE{0,nullptr, nullptr};
	tmp->right->right = new NODE{4,nullptr, nullptr};
	if (!isBST(tmp, INT_MIN, INT_MAX)) cout << "false"; else cout <<"true" << endl;
	cout << endl;
	cout << (isFullBT(tmp) && isBST(tmp, INT_MIN, INT_MAX));
}