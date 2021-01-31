/**
    @author Marek Brynda
**/
#include <iostream>

using namespace std; 

int t = 3;

class Node{
public: 
    int *keys; // list of keys
    Node **C;  // lsit of children
    int n;     // numbe of keys inside
    bool leaf; // info if given node is leafv

    // if given node is leaf then true if not then false
    Node(bool leaf1) {
        leaf = leaf1;

        keys = new int[2 * t - 1]; // max number of keys
        C = new Node *[2 * t]; // max numbe of degrees

        n = 0; // init n as 0
    }

    // insert element
    void insert(int k) {
        int i = n - 1; // max iterator for keys
        // if leaf then
        if (leaf == true) {
            // while i is bigger equal zeo and key bigger than k 
            while (i >= 0 && keys[i] > k) {
                // move keys into the right
                // maing place for new key
                keys[i + 1] = keys[i];
                i--;
            }
            // move k into the righ place
            keys[i + 1] = k;
            // updat number of elements
            n = n + 1;
        }else{
            /// if not leaf then find correct place
            while (i >= 0 && keys[i] > k){
                i--;
            }
            // if correct child has max degree then split it
            if (C[i + 1]->n == 2 * t - 1) {
                splitChild(i + 1, C[i + 1]);
            // move i if k is not in the right place
            if (keys[i + 1] < k)
                i++;
            }
            // insert k into the correct child whichhas been splitted
            C[i + 1]->insert(k);
        }
    }

    // split child 
    void splitChild(int i, Node *y) {
        // create new node
        Node *z = new Node(y->leaf);
        // number of keys will be t-1
        z->n = t - 1;

        for (int j = 0; j < t - 1; j++){
            // append keys from right of parent into the child
            z->keys[j] = y->keys[j + t];
        }
        // if parent was not a leaf then
        if (y->leaf == false) {
            // move children of parent inot the new child (right part of them)
            for (int j = 0; j < t; j++){
                z->C[j] = y->C[j + t];
            }
        }
        // now the parent has only t-1 children
        y->n = t - 1;
        // move to the right children to make place for z
        for (int j = n; j >= i + 1; j--){
            C[j + 1] = C[j];
        }
        // place new child in correct place
        C[i + 1] = z;
        // move keys into the right to make place for z
        for (int j = n - 1; j >= i; j--){
            keys[j + 1] = keys[j];
        }
        // move parent key into the right place
        keys[i] = y->keys[t - 1];
        // update number of keys
        n = n + 1;
    }

    void printNode(int x=0, int maxn=(2*t-1)){
        int i;
        for (i = 0; i < n; i++) {
            cout << (char)keys[i] <<",";
        }

        if(x==maxn){
            cout<<endl;
        }else {
            for (i = 0; i < n; i++) {
                cout<< " ";
            }
        }

        for (i = 0; i < n; i++) {
            if (leaf == false)
                C[i]->printNode(i, n);
        }

        if (leaf == false)
            C[i]->printNode(i, n);
    }

};

class BTree{
public:
    Node *root;

    BTree(){
        root = NULL;
    }

    // insert new node
    void insertNode(int k) {
        if (root == NULL) {
            // if no nodes then initialize
            root = new Node(true);
            root->keys[0] = k;
            root->n = 1;
        }else{
            // if some nodes then check degree of root
            // if max capacity then split 
            if (root->n == 2 * t - 1) {
                // new node for sure not leaf
                Node *s = new Node(false);
                // first child root
                s->C[0] = root; 
                // preform split chold on root
                s->splitChild(0, root);

                int i = 0;
                // move i to the correct place for k
                if (s->keys[0] < k)
                    i++;
                // insert k in the correct place
                s->C[i]->insert(k);
                // now s is new root
                root = s;
            }else{
                // if there is place then insert k into the current place
                root->insert(k);
            }
        }
    }

    void printTree() {
        if (root != NULL)
            cout<<"     ";
            root->printNode(root->n, root->n);
    }
};


int main(){
    
    int input_arr[] = {'J', 'I', 'K', 'H', 'A', 'C', 'B', 'F', 'D','G'}; //{'A', 'D', 'F', 'G', 'C', 'B', 'H', 'I','K','L','J'};

    int n = sizeof(input_arr)/sizeof(input_arr[0]);
    
    BTree tree; 

    for( int i = 0; i < n; i++){  
        //int ia = (int)input_arr[i];      
        tree.insertNode(input_arr[i]);
        tree.printTree();
        cout<<endl;
    }

	return 0;
}