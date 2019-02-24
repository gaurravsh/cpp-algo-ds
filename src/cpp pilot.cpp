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


node *buildTree(int ,int);
int sumAt(node *);
void traverse(node *);
void update(node *,int , int );
int query(node*,int, int);

int main(){
	cout<<"Enter size of array and then numbers :"<<endl;
	cin >> sizeOfArr;
	char flag;
	a=new int[sizeOfArr];
	for(int i=0;i<sizeOfArr;i++)
		cin>>a[i];
	node *root=buildTree(0, sizeOfArr-1);

    int index,value;
    int index1, index2;
    while(1){
    	cout <<"Enter Choice (u:update,e:exit,q:query) : ";
    	cin >>flag;
    	if(flag=='e' || flag=='E')
    		break;
    	else if(flag=='u' || flag=='U'){
    		cout<<endl<<"Enter index and value : ";
    		cin>>index>>value;
    		update(root, index, value);
    		traverse(root);
    	}
    	else if(flag=='q'||flag=='Q'){
    		cout<<endl<<"Enter lower and upper index : ";
    		cin>>index1>>index2;
    		cout<<endl<<"query result : "
    				<<query(root,index1,index2)<<endl;
    	}
    	else cout<<"bad input"<<endl;
    }
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
	update(p->left, index, value);
	update(p->right, index, value);
}

int query(node* p,int i, int j){
	if(i<p->lowerIndex && j>p->upperIndex)	return 0;
	if(i==p->lowerIndex && j==p->upperIndex) return p->sum;
	if(p->left->lowerIndex<=i && j<=p->left->upperIndex)
		return query(p->left,i,j);
	else if(p->right->lowerIndex<=i && j<=p->right->upperIndex)
		return query(p->right,i,j);
	else if(p->left->lowerIndex<=i && i<=p->left->upperIndex
			&& p->right->lowerIndex<=j && j<=p->right->upperIndex)
		return query(p->left,i,p->left->upperIndex)
				+ query(p->right,p->right->lowerIndex,j);
	else return 0;
}
