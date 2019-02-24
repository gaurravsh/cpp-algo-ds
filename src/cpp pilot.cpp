//============================================================================
// Name        : cpp.cpp
// Author      : Gaurav
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

 int *a;
int sizeOfArr;

typedef struct node{
	int sum;
	struct node* left;
	struct node* right;
	int lowerIndex;
	int upperIndex;
}node;
node *root;

node *buildTree(int i,int j);
int sumAt(node *p);
void traverse(node *p);

int main(){
	cout<<"Enter size of array and then numbers :"<<endl;
	cin >> sizeOfArr;
	a=new int[sizeOfArr];
	for(int i=0;i<sizeOfArr;i++)
		cin>>a[i];
    root=buildTree(0, sizeOfArr-1);
    traverse(root);
    return 0;
}

node *buildTree(int i,int j){
	if(i<0 || j>=sizeOfArr)
		return NULL;
	int m=(i+j)/2;

	node*p=new node;

	if(i==j){
		p->sum=a[i];
		p->left=NULL;
		p->right=NULL;
	}
	else{
		p->left=buildTree(i, m);
		p->right=buildTree(m+1, j);
		p->sum=sumAt(p);
	}
	p->lowerIndex=i;
	p->upperIndex=j;
	return p;
}

int sumAt(node *p){
	int sumL=p->left==NULL?0:p->left->sum;
	int sumR=p->right==NULL?0:p->right->sum;
	return sumL+sumR;
}

void traverse(node*p){
	if(p==NULL)	return;
	cout<<"Root : "<<p->sum<<endl;
	cout<<"Left : "; traverse(p->left); cout<<endl;
	cout<<"Right : "; traverse(p->right); cout<<endl;
}

void update(node *p,int index, int value){
	if(index<p->lowerIndex || index>p->upperIndex)	return;
	p->sum=p->sum+value;
	if(p->lowerIndex==index && p->upperIndex==index)	return;
	//if(index>p->lowerIndex)
		update(p->left, index, value);
	//if (index<p->upperIndex)
		update(p->right, index, value);

}
