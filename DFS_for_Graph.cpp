/**
	@author Marek Brynda
**/
#include <iostream>
#include <limits>


using namespace std;


struct Node{
	Node *next;
	Node *edge;
	int label;
	bool visited;
};

class Stack{
	private:
		Node *top;
	public:
		Stack(){
			top = NULL;
		}

		bool isEmpty(){
			return(top == NULL);
		}

		void printStack(){
			Node *n = top;
			cout << "[ ";
			while(n != NULL){
				cout << n->label << " ";
				n = n->next;
			}
			cout << "]";
			cout << endl;
		}

		void Push(int x){
			try{
				Node *tmp = new Node();
				tmp->label = x;
				tmp->next = top;
				top = tmp;
			} catch(bad_alloc& ex){
				cout << "STACK IS FULL" << endl;
			}

			//printStack();
		}

		Node *Pop(){
			Node *tmp = top;
			if(isEmpty()){
				cout << "STACK IS EMPTY" <<endl;
			}else{
				top = tmp->next;
			}
			// to avoid printing empty stack
			//if(top != NULL){
			//	printStack();
			//}

			return tmp;
		}
};


class Graph{
	private:
		Node *top;
	public:
		Graph(){
			top = NULL;
		}

		void printGraph(){
			Node *n = top;
			while(n != NULL){
				cout << n->label;

				Node *m = n->edge;
				while(m != NULL){
					cout << "->" << m->label;
					m = m->next;
				}
				n = n->next;
				cout << endl;
			}
			cout << endl;
		}

		Node* findNode(int x){
			Node *n = top;
			while(n != NULL){
				if(n->label==x) return(n);
				n = n->next;
			}
			return(NULL);
		}

		void addVertex(int x){
			Node* nodeX = findNode(x);
			// there not exists this kind of node
			if(nodeX==NULL){
				Node *tmp = new Node();
				tmp->label = x;
				tmp->next = top;
				tmp->edge = NULL;
				tmp->visited = false;
				top = tmp;
			}else{
				cout<<"GIVEN VERTEX "<< x <<" ALREADY EXISTS!"<<endl;
			}
			//printGraph();
		}

		bool existsEdge(Node* nodeX, int y){
			Node *m = nodeX->edge;
			while(m != NULL){
				if(m->label==y) return(true);
				m = m->next;
			}
			return(false);
		}

		void addEdge(int x, int y){
			Node* nodeX = findNode(x);
			Node* nodeY = findNode(y);
			if((nodeX!=NULL)&&(nodeY!=NULL)){
				if(!existsEdge(nodeX,y)){
					Node *tmp = new Node();
					tmp->label = y;
					tmp->next = nodeX->edge;
					nodeX->edge = tmp;
				}else{
					cout<<"GIVEN EDGE "<< x <<"->"<< y <<" ALREADY EXISTS!"<<endl;
				}
			}else{
				cout<<"ONE OF VERTICES "<< x <<" , "<< y <<" DOES NOT EXIST!"<<endl;
			}
			//printGraph();
		}

		void removeEdge(int x, int y){
			Node* nodeX = findNode(x);
			Node* nodeY = findNode(y);
			// if both nodes exists then check if edge exists
			if((nodeX!=NULL)&&(nodeY!=NULL)){
				// if edge exists then add new adge as the first element of linked list
				if(existsEdge(nodeX,y)){
					Node *m = nodeX->edge;
					if(m->label==y){
						nodeX->edge=m->next;
					}else{
						Node *mm = m->next;
						while(mm->label!=y){
							m = m->next;
							mm = m->next;
						}
						m->next = mm->next;
						free(mm);
					}
				}else{
					cout<<"GIVEN EDGE "<< x <<"->"<< y <<" DOES NOT EXIST!"<<endl;
				}
			}else{
				cout<<"GIVEN EDGE "<< x <<"->"<< y <<" DOES NOT EXIST!"<<endl;
			}
			//printGraph();
		}

		void removeVertex(int x){
			// Node has to exists
			Node* nodeX = findNode(x);
			if(nodeX!=NULL){
				// if node is thop then set top as the next node
				if(nodeX==top){
					top=nodeX->next;
				}else{
					Node *n = top;
					Node *nn = n->next;
					while(nn->label!=x){
						cout << n->label <<endl;
						n = n->next;
						nn = n->next;
					}
					n->next=nodeX->next;
				}
				free(nodeX);
			}else{
				cout<<"GIVEN VERTEX "<< x <<" DOES NOT EXIST!"<<endl;
			}
			//printGraph();
		}

	// for looking for smallest not visited Node
	Node* findSmallestNode(){
		Node* top_n = top;
		Node* lowest = top_n;
		//find lowest label in graph
		//if exist more than one node
		if(top_n->next!=NULL){
			while(top_n!=NULL){
				if(lowest->visited && top_n->visited){
					top_n=top_n->next;
					lowest = top_n;
				}else{
					if((top_n->label < lowest->label) && !(top_n->visited)){
						lowest=top_n;
					}
					top_n=top_n->next;
				}
			}
		// only one and hasn't been visited
		}else if(!lowest->visited){
			lowest = top_n;
		// only one and has been visited
		}else{
			return NULL;
		}

		if(lowest==NULL){
			return NULL;
		}		
		return lowest;
	}

	// for looking for smallest not visited neighbour of node
	// n is the node->edge so boefore using this function there is a checkgin if it is not null
	Node* findSmallestEdge(Node* n){
		Node* top_n = n;
		Node* lowest = top_n;
		//find lowest label in graph
		//if exist more than one node
		Node* l_node = findNode(lowest->label);
		if(top_n->next!=NULL){
			while(top_n!=NULL){
				Node* l_node = findNode(lowest->label);
				Node* top_nn = findNode(top_n->label); 
				if(l_node->visited && top_nn->visited){
					top_n=top_n->next;
					lowest = top_n;
				}else{
					if((top_n->label < lowest->label) && !(top_nn->visited)){
						lowest=top_n;
					}
					top_n=top_n->next;
				}
			}
		// only one and hasn't been visited
		}else if(!l_node->visited){
			lowest = top_n;
		// only one and has been visited
		}else{
			return NULL;
		}
		return lowest;
	}

	Stack* DFShelper(Node* n, Stack* s){
		// mark given Node as visite
		n->visited=true;
		// ad label to stack
		(*s).Push(n->label);
		// if there are some edges then
		if(n->edge!=NULL){
			// find smalles edge
			Node* e = findSmallestEdge(n->edge);
			Node* ne = e;
			// while there are some edges whic haven't been visited
			while(e!=NULL){
				ne = findNode(e->label);
				if(!ne->visited) s = DFShelper(ne, s);
				e = findSmallestEdge(n->edge);
			}
		}
		return s;
	}

	Stack* DFS(){
		Stack* s = new Stack();
		Node* n = new Node();
		n = findSmallestNode();		
		while(n!=NULL){
			s = DFShelper(n, s);
			n = findSmallestNode();
		}
		return s;
	}

};


void graphTest1(){
	cout << endl<< "Test 1"<<endl;
	Graph grph = Graph();
	grph.addVertex(1);
	grph.addVertex(2);
	grph.addVertex(3);
	grph.addVertex(4);
	
	grph.addEdge(1,4);
	grph.addEdge(1,3);
	grph.addEdge(3,4);
	grph.addEdge(3,2);
	grph.addEdge(2,2);

	grph.printGraph();

	Stack* s = grph.DFS();
	(*s).printStack(); 
}

void graphTest2(){
	cout << endl<< "Test 2"<<endl;
	Graph grph = Graph();
	grph.addVertex(1);
	grph.addVertex(2);
	grph.addVertex(3);
	grph.addVertex(4);
	grph.addVertex(5);
	
	grph.addEdge(1,4);
	grph.addEdge(1,3);
	grph.addEdge(4,3);
	grph.addEdge(3,2);
	grph.addEdge(2,3);

	grph.printGraph();

	Stack* s = grph.DFS();
	(*s).printStack(); 
}

int main()
{
	graphTest1();

	graphTest2();

	return 0;
}
