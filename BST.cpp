/**
    @author Marek Brynda
    Binary Search Tree
**/
#include <iostream>
#include <list>
#include <vector>

using namespace std; 

// node of BST
struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent;
};

Node* newNode(int data){
    Node* tmpNode = new Node();
    tmpNode->data = data;
    tmpNode->left = tmpNode->right = NULL;
    return tmpNode;
}

Node* insertNode(Node* root, int data){
    //create first node of BST
    if (root == NULL) {
        root = newNode(data);
        return root;
    }
    // if root data smaller than insert data then
    if(root->data < data)  { 
        // right node <- right node after inserting new node
        root->right = insertNode(root->right, data); 
    }else{ 
        root->left = insertNode(root->left, data);
    } 
    // return root after finishing inserting data
    return root;
}

void printTree(Node* root){
    // if null then print nothing
    if (root == NULL)
        return;
    // print left - smaller
    printTree(root->left);
    // then print greaters - right but smaller than neighbour node
    printTree(root->right); 
    //if notking on the left then print nothing, then pront current
    cout << root->data << ',';
}

Node* search(Node* root, int n){
    // if root then root
    if (root == NULL || root->data == n) 
       return root; 
    if (root->data < n) 
       return search(root->right, n); 
  
    return search(root->left, n); 
}

Node* search_p(Node* root, int n){
    // if root then root
    if (root->left->data == n || root->right->data == n) 
       return root; 
    if (root->data < n) 
       return search_p(root->right, n); 
  
    return search(root->left, n); 
}

Node* minValue(struct Node* root){
    Node* current = root; 
    // only working for left
    while (current->left != NULL) { 
        current = current->left; 
    } 
    return current; 
} 

void successor(Node* root, int n){ 
    // if there exist anything bigger in siccessors then find min value in right
    Node* s = search(root, n);
    if (s->right != NULL){
        // find smallest value on roght side
        s = minValue(root->right);
        cout << "Successor of "<<n <<" : "<<s->data<<endl;
    }else{
        cout << "For node "<<n<<" there not exists successor"<<endl;
    };
} 

int main()
{
    int input_arr[] = {5,1,3,2,4,7,6};
    // insert procedure BST
    //BST* tree = new BST(input_arr[0]);

    Node* tree = newNode(input_arr[0]);
    printTree(tree);
    cout<<endl;

    int n = sizeof(input_arr)/sizeof(input_arr[0]);
    
    for( int i = 1; i < n; i++){        
        tree = insertNode(tree, input_arr[i]);
        printTree(tree);
        cout<<endl;
    }

    successor(tree, 3);
    //tree = tree->insert(tree, 7);
    //tree->printTree(tree);
    // successors of given elements
	return 0;
}