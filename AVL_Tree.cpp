/**
    @author Marek Brynda
    AVL Tree
**/
#include <iostream>

using namespace std; 

class Node  {  
public:
    int label;  
    Node *left;  
    Node *right;  
    int height;  
};  

Node* createNode(int x)  {  
    // create new node
    Node* node = new Node(); 
    // assign values
    node->label = x;  
    // left and right NULL - no subtrees
    node->left = NULL;  
    node->right = NULL;  
    // initialize height to 1
    node->height = 1;

    return(node);  
}  

// get the height
int height(Node* n){
	if(n==NULL)
		return 0;
	return n->height;
}

int balanceFactor(Node *n){
    if(n==NULL)
        return 0;
    return height(n->left) - height(n->right);
}

// funtions to roatate
Node *rRotation(Node *n){  
    Node *l = n->left;  
    Node *r = l->right;  
  	
  	// n will becoame new right for this tree
  	// the left child wil became the new root 
  	// (on the left from it nothing will change)
    l->right = n;  
    // now left of previous root will baceme the left of now right
    // it is smaller than old r
    n->left = r;  

    int lh = height(n->left);
    int rh = height(n->right);
    n->height = (lh > rh)? lh : rh + 1; 
    
    lh = height(l->left);
    rh = height(l->right); 
    l->height = (lh > rh)? lh : rh + 1;   
    
    // return new root
    return l;  
}  

Node *lRotation(Node *n){  
    Node *r = n->right;  
    Node *l = r->left;  
    
    // n will becoame new left for this tree
    // the left right will became the new root 
    // (on the right from it nothing will change)
    r->left = n;  
    // now left of previous root will baceme the left of now right
    // it is smaller than old r
    n->right = l;  

    int lh = height(n->left);
    int rh = height(n->right);
    n->height = (lh > rh)? lh : rh + 1; 
    
    lh = height(r->left);
    rh = height(r->right); 
    r->height = (lh > rh)? lh : rh + 1;   
    
    // return new root
    return r;  
}  

Node* insertNode(Node* n, int x)  
{  
    // it no node exists then create a new one 
    if (n == NULL)  
        return(createNode(x));  
    
    if (x < n->label){
        // if x smaller than key of node 
        // insert it into left of node  
        n->left = insertNode(n->left, x);  
    }else{  
        // if x bigger than key of node 
        // insert it into right of node  
        n->right = insertNode(n->right, x);  
    }
  
    // udpate heights of node
    int lh = height(n->left);
    int rh = height(n->right);
    n->height = (lh > rh)? lh : rh + 1;
  
    int b = balanceFactor(n);  
    
    if (b > 1 && x < n->left->label){
        // b > 1 = left bigger 
        // x < label on the left 
        // it means it went on left -> r rotation
        return rRotation(n);  
    }else if (b < -1 && x > n->right->label){  
        // b < -1 = right bigger 
        // x > label on the right 
        // it means it went on right -> l rotation
        return lRotation(n);  
    }else if(b > 1 && x > n->left->label){  
        // b > 1 = left bigger 
        // x > label on the left 
        // it means it went on left and then right
        // there will be need rotation level lower
        // left -> l rotation
        // then r rotation
        n->left = lRotation(n->left);  
        return rRotation(n);  
    }else if (b < -1 && x < n->right->label){ 
        // b < -1 = right bigger 
        // x < label on the right 
        // it means it went on right and then left
        // there will be need rotation level lower
        // right -> r rotation
        // then l rotation 
        n->right = rRotation(n->right);  
        return lRotation(n);  
    }else{}  
  
    return n;  
}  
  
void printTree(Node *n)  
{  
    if(n != NULL)  
    {   
        printTree(n->left); 
        cout << n->label << " "; 
        printTree(n->right);  
    }  
}   

int main(){
    int input_arr[] = {3,5,6,4,1,2};

    int n = sizeof(input_arr)/sizeof(input_arr[0]);
    
    Node *tree = NULL;  

    for( int i = 0; i < n; i++){        
        tree = insertNode(tree, input_arr[i]);
        printTree(tree);
        cout<<endl;
    }

	return 0;
}