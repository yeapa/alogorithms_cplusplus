#include <iostream>
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
};

int main() {

    BinaryTree<int , int > binaryTree;
    binaryTree.put(11,11);
    binaryTree.put(10,10);
    binaryTree.put(9,9);
    cout<<binaryTree.root->val;
    cout<<binaryTree.root->left->val<<endl;
    cout<<binaryTree.get(10)<<endl;

    cout<<binaryTree.rank(9)<<endl;

    cout<<binaryTree.max(binaryTree.root)->val<<endl;
    return 0;
}

