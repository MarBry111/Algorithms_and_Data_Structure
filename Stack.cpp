/**
	@author Marek Brynda
**/
#include <iostream>

using namespace std;

struct Node{
	Node *next;
	int data;
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
			cout << n->data << " ";
			n = n->next;
		}
		cout << "]";
		cout << endl;
	}

	void Push(int x){
		try{
			Node *tmp = new Node();
			tmp->data = x;
			tmp->next = top;
			top = tmp;
		} catch(bad_alloc& ex){
			cout << "STACK IS FULL" << endl;
		}

		printStack();
	}

	void Pop(){
		Node *tmp = top;
		if(isEmpty()){
			cout << "STACK IS EMPTY" <<endl;
		}else{
			top = tmp->next;
		}
		// to avoid printing empty stack
		if(top != NULL){
			printStack();
		}

		free(tmp);
	}
};

int main()
{
	Stack st = Stack();
	
	st.Push(6);
	st.Pop();
	st.Pop();
	st.Push(5);
	st.Push(4);
	st.Pop();
	st.Push(5);
	st.Pop();

	return 0;
}