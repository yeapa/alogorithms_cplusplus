#include <iostream>
#include <stack>
using namespace std;
void replaceBlank(char * string,int length){
    int blankNum = 0;
    for(int i = 0;i<length;i++){
        if (*(string+i)==' '){
            blankNum++;
        }
    }

    int destIndex = length-1+2*blankNum;
    int sourceIndex = length-1;

    while(sourceIndex>=0&&destIndex!=sourceIndex){
        if (string[sourceIndex]!=' '){
            string[destIndex] = string[sourceIndex];
            sourceIndex--;
            destIndex--;
        }else{
            string[destIndex--]= '0';
            string[destIndex--]= '2';
            string[destIndex--]= '%';
            sourceIndex--;
        }
    }
}


struct ListNode{
    int m_nValue;
    ListNode * m_pNext;
};

void addToTail(ListNode **pHead,int value){
    ListNode * pNew = new ListNode();
    pNew ->m_nValue = value;
    pNew ->m_pNext = NULL;
    if(*pHead==NULL){
        *pHead=pNew;
    } else{
        ListNode * pNode = *pHead;
        while (pNode->m_pNext!=NULL){
            pNode=pNode->m_pNext;
        }
        pNode->m_pNext=pNew;
    }
}

void reverse(ListNode **pHead){
    ListNode * pCurNode=(*pHead)->m_pNext;
    ListNode *pBeforeNode=*pHead;
    pBeforeNode->m_pNext=NULL;
    ListNode *pNextNode=NULL;
    while(pCurNode!=NULL){
        pNextNode=pCurNode->m_pNext;
        pCurNode->m_pNext=pBeforeNode;

        pBeforeNode=pCurNode;
        *pHead=pCurNode;
        pCurNode=pNextNode;
    }
}

void removeNode(ListNode **pHead,int value){
    ListNode * pCurNode = *pHead;
    ListNode * pBeforeNode=*pHead;
    while (pCurNode->m_pNext!=NULL){
        if (pCurNode->m_nValue==value){
            pBeforeNode->m_pNext=pCurNode->m_pNext;
            delete pCurNode;
            pCurNode=pBeforeNode->m_pNext;
        } else{
            pBeforeNode=pCurNode;
            pCurNode=pCurNode->m_pNext;
        }
    }
}



template <class Key,class Value >
class BinaryTree {
private:

    class Node{
    public:
        Key key;
        Value val;
        Node* left=NULL ;
        Node* right=NULL;
        int N;
    public:
        Node(Key key,Value val,int N){
            this->key = key;
            this->val = val;
            this->N = N;
        }
    };


public:
    Node *root=NULL;

    int size(Node *pCurNode){
        if(pCurNode==NULL){
            return  0;
        }
        return pCurNode->N;
    }
    void put(Key key,Value val){
        root = put(root,key, val);
    }
    Node* put(Node* pCurNode,Key key,Value val){
        if(pCurNode==NULL){
            return new Node(key,val,1);
        }
        if(key>pCurNode->key) {
            pCurNode->right = put(pCurNode->right,key,val);
        }
        else if(key<pCurNode->key){
            pCurNode->left = put(pCurNode->left,key,val);
        }else{
            pCurNode->val = val;
        }
        pCurNode->N = size(pCurNode->left)+size(pCurNode->right)+1;
        return pCurNode;
    }

    Node* min(Node* x){
        if (x->left==NULL) return x;
            return min(x->left);
    }

    Node* max(Node* x){
        if (x->right==NULL) return x;
        return min(x->left);
    }


    Key get(Key key){
        return get(root,key);
    }

    Node * floor(Node* x, Key key){
        if(x==NULL){ return NULL;}
        if (key<x->key){
            return floor(x->left,key);
        }
        if(key==x->key) return x;
        Node* t = floor(x->right,key);
        if (t!=NULL){
            return t;
        } else{
            return x;
        }
    }

    Value get(Node* pCurNode,Key key){
        if(pCurNode==NULL) return NULL;
        if (key>pCurNode->key){
            return get(pCurNode->right,key);
        } else if(key<pCurNode->key){
            return get(pCurNode->left,key);
        }else{
            return pCurNode->val;
        }
    }

    int rank(Key key){
        return rank(root,key);
    }

    int rank(Node* pCurNode,Key key){
        if(pCurNode==NULL){
            return -1;
        }  if (key == pCurNode->key){
            return size(pCurNode->left);
        }
        if (key == pCurNode->key){
            return size(pCurNode->left);
        }
        else if(key < pCurNode->key){
            return rank(pCurNode->left,key);
        }else{
            return size(pCurNode->left)+1+rank(pCurNode->right,key);
        }
    }

    Key select(int k){
        return select(root,k)->key;
    }
    Node* select(Node* pCurNode,int k){
        if(pCurNode==NULL) return NULL;
        if (k==size(pCurNode->left)){
            return pCurNode;
        }
        else if(k<size(pCurNode->left)){
            return select(pCurNode->left,k);
        } else{
            return select(pCurNode->right,k-size(pCurNode->left)-1);
        }
    }

    void deleteMin(){
        root=deleteMin(root);
    }

    Node*  deleteMin(Node* pCurNode){
        if(pCurNode->left==NULL)
            return pCurNode->right;
        pCurNode->left = deleteMin(pCurNode->left);
        pCurNode->N=size(pCurNode->left)+size(pCurNode->right)+1;
        return pCurNode;

    }

    void del(Key key){
        root = del(root,key);
    }
    Node* del(Node * pCurNode,Key key){
        if(pCurNode=NULL) {
            return NULL;
        }
        if (key<pCurNode->val){
            pCurNode->left=del(pCurNode->left,key);
        }
        else if(key>pCurNode->val){
            pCurNode->right=del(pCurNode->right,key);
        }else{
            if(pCurNode->right==NULL){
                return pCurNode->left;
            }
            if (pCurNode->left==NULL){
                return pCurNode->right;
            }
            Node* temp=pCurNode;
            pCurNode=min(pCurNode->right);
            pCurNode->left=temp->left;
        }

        return pCurNode;
    }
    void preOrder(Node * pCurNode){
        if(pCurNode==NULL){
            return;
        }
        if(pCurNode->left!=NULL){
            preOrder(pCurNode->left);
        }

        cout<<pCurNode->key<<"  ";

        if(pCurNode->right!=NULL){
            preOrder(pCurNode->right);
        }

    }

};
struct BinaryTreeNode{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};


BinaryTreeNode* constructCore(int* startPreorder,int * endPreorder,int* startInorder,int* endInorder){
    int rootValue = startPreorder[0];
    BinaryTreeNode* root = new BinaryTreeNode();
    root->m_nValue=rootValue;
    root->m_pLeft=root->m_pRight=NULL;
    if(startPreorder == endPreorder){
        if(startInorder == endInorder && *startInorder==*startPreorder){
            return root;
        } else{
            perror("input invalid");
            exit(EXIT_FAILURE);
        }
    }

    int* rootInorder = startInorder;
    while (rootInorder<=endInorder && *rootInorder!=rootValue){
        ++rootInorder;
    }

    if(rootInorder==endInorder && *rootInorder!=rootValue) {
        perror("input invalid");
        exit(EXIT_FAILURE);
    }
    int leftLength = rootInorder-startInorder;
    int *leftPreorderEnd = startPreorder+leftLength;
    if(leftLength>0){
        root->m_pLeft = constructCore(startPreorder+1,leftPreorderEnd,startInorder,rootInorder-1);
    }
    if(leftLength<endPreorder-startPreorder){
        root->m_pRight = constructCore(leftPreorderEnd+1,endPreorder,rootInorder+1,endInorder);
    }
    return root;
}

BinaryTreeNode* construct(int* preorder,int* inorder,int length){
    if(preorder==NULL||inorder==NULL||length<=0){
        return NULL;
    }
    return constructCore(preorder,preorder+length-1,inorder,inorder+length-1);

}




template <class T>
class CQueue{
public:
    CQueue(){}
    ~CQueue(){}

    void appendTail(T t){
        while(!stack2.empty()){
            stack1.push(stack2.top());
            stack2.pop();
        }
        stack1.push(t);

        while (!stack1.empty()){
            stack2.push(stack1.top());
            stack1.pop();
        }

    }

    T deleteHead(){
        T temp= stack2.top();
        stack2.pop();
        return temp;
    }

private:
    stack<T> stack1;
    stack<T> stack2;

};

class Sort{
    static int partition(int a[],int lo,int hi ){
//        if(hi<=lo) { return lo;}
        int i = lo;
        int j = hi+1;
        int v = a[lo];

        while(true){
            while (a[++i]<v)  {
                if(i>hi) break;
            }
            while(a[--j]>v)   {
                if (j<lo) break;
            }
            if(i>=j) break;

            int tempa= a[i];
            a[i]=a[j];
            a[j]=tempa;
        }

        int temp = a[lo];
        a[j]=a[lo];
        a[lo]=temp;
        return j;
    }

    static void sort(int* a,int lo,int hi){
        if (hi<=lo){
            return;
        }
        int i = partition(a,lo,hi);
        sort(a,lo,i-1);
        sort(a,i+1,hi);
    }

};

int fibonacci(int n){

    if(n<0) { return -1;}
    int d[n+1];
    d[0]=0;
    d[1]=1;
    for(int i=2;i<1+n;i++){
        d[i]=d[i-1]+d[i-2];
    }
    cout<<d[n]<<endl;

}

int count1(int n){
    int count =0;
    while (n!=0){
        if(n&1){
            count++;
        }
        n=n>>1;
    }
    return count;
}

class Sales_datas{
public:
    Sales_datas(const Sales_datas& orig){
        bookNo=orig.bookNo;
        units_sold=orig.units_sold;
        revenue=orig.revenue;
    }

    Sales_datas& operator=(const Sales_datas& orig){
        bookNo=orig.bookNo;
        units_sold=orig.units_sold;
        revenue=orig.revenue;
        return *this;
    }

private:
    string bookNo;
    int units_sold=0;
    double revenue = 0.0;

};

class Sales_data{

public:
    Sales_data()= default;
    Sales_data(const Sales_datas&)= default;
    Sales_data& operator=(const Sales_data&)= default;
    ~Sales_data()= default;

};

class HasPtr{
public:
    HasPtr(const string &s = string()):ps(new string(s)),i(0)
    {    }

    HasPtr(const HasPtr &p):ps(new string(*p.ps)),i(p.i)
    {

    }

    HasPtr& operator=(const HasPtr& p){
        string* temp = new string(*p.ps);
        delete(ps);
        ps=temp;
        i=p.i;
        return *this;
    }

    ~HasPtr(){delete ps;}
private:
    string *ps;
    int i;
};

class Hasptr1{
public:
    Hasptr1(const string& s = string()):ps(new string(s)),i(0),use(new size_t(1)){

    }
    Hasptr1(const Hasptr1& origin){
        ps = origin.ps;
        i=origin.i;
        use =origin.use;
        (*use)++;
    }

    Hasptr1& operator=(const Hasptr1& origin){
        ps = origin.ps;
        i=origin.i;
        use = origin.use;
        (*origin.use)++;
        if(--*use==0){
            delete(use);
            delete(ps);
        }
        return *this;
    }
    ~Hasptr1(){
        if(--*use==0){
            delete(use);
            delete(ps);
        }
    }

private:
    string* ps;
    int i;
    size_t* use;

};
int main() {
    BinaryTree<int , int > binaryTree;
    binaryTree.put(10,10);
    binaryTree.put(6,6);
    binaryTree.put(14,14);
    binaryTree.put(4,4);
    binaryTree.put(8,8);
    binaryTree.put(12,12);
    binaryTree.put(16,16);
    cout<<binaryTree.root->val<<endl;
    cout<<binaryTree.root->left->val<<endl;
//    cout<<binaryTree.get(10)<<endl;
    cout<<binaryTree.rank(9)<<endl;
    cout<<binaryTree.min(binaryTree.root)->val<<endl;

    binaryTree.preOrder(binaryTree.root);

    CQueue<int> queue;
    queue.appendTail(1);
    queue.appendTail(2);
    cout<< queue.deleteHead() <<endl;

    fibonacci(4);
    cout<<count1(9)<<endl;


    return 0;
}

