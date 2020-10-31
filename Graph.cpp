/**
	@author Marek Brynda
**/
#include <iostream>

using namespace std;

struct Edge{
	Edge *next;
	int name;
};

struct Node{
	Node *next;
	Edge *edge;
	int name;
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
			cout << n->name;

			Edge *m = n->edge;
			while(m != NULL){
				cout << "->" << m->name;
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
			if(n->name==x) return(n);
			n = n->next;
		}
		return(NULL);
	}

	void addVertex(int x){
		Node* nodeX = findNode(x); 
		// there not exists this kind of node
		if(nodeX==NULL){
			Node *tmp = new Node();
			tmp->name = x;
			tmp->next = top;
			tmp->edge = NULL;
			top = tmp;
		}else{
			cout<<"GIVEN VERTEX "<< x <<" ALREADY EXISTS!"<<endl;
		}
		printGraph();
	}

	bool existsEdge(Node* nodeX, int y){
		bool exists = false;
		Edge *m = nodeX->edge;
		while(m != NULL){
			if(m->name==y) return(true);
			m = m->next;
		}
		return(false);
	}

	void addEdge(int x, int y){
		Node* nodeX = findNode(x); 
		Node* nodeY = findNode(y); 
		if((nodeX!=NULL)&&(nodeY!=NULL)){
			if(!existsEdge(nodeX,y)){
				Edge *tmp = new Edge();
				tmp->name = y;
				tmp->next = nodeX->edge;
				nodeX->edge = tmp;
			}else{
				cout<<"GIVEN EDGE "<< x <<"->"<< y <<" ALREADY EXISTS!"<<endl;
			}
		}else{
			cout<<"ONE OF VERTICES "<< x <<" , "<< y <<" DOES NOT EXIST!"<<endl;
		}
		printGraph();
	}

	void removeEdge(int x, int y){
		Node* nodeX = findNode(x); 
		Node* nodeY = findNode(y); 
		// if both nodes exists then check if edge exists
		if((nodeX!=NULL)&&(nodeY!=NULL)){
			// if edge exists then add new adge as the first element of linked list
			if(existsEdge(nodeX,y)){
				Edge *m = nodeX->edge;
				if(m->name==y){
					nodeX->edge=m->next;
				}else{
					Edge *mm = m->next;
					while(mm->name!=y){
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
		printGraph();
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
				while(nn->name!=x){
					cout << n->name <<endl;
					n = n->next;
					nn = n->next;
				}
				n->next=nodeX->next;
			}
			free(nodeX);
		}else{
			cout<<"GIVEN VERTEX "<< x <<" DOES NOT EXIST!"<<endl;
		}
		printGraph();
	}
	

	
};


int main()
{
	Graph grph = Graph();
	grph.addVertex(1);
	grph.addVertex(5);
	grph.addVertex(3);
	grph.addEdge(1,3);
	grph.removeEdge(1,5);
	grph.addEdge(5,5);
	grph.addVertex(1);
	grph.addEdge(1,5);
	grph.removeVertex(2);
	grph.removeEdge(1,3);
	grph.removeVertex(3);
	return 0;
}