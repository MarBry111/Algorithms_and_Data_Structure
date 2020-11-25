/**
	@author Marek Brynda
**/
#include <iostream>
#include <list>

using namespace std;

void task6(list<int> list1, list<int> list2, int N){

	cout << "First List: ";
	for (list<int>::iterator l1 = list1.begin(); l1 != list1.end();){
	    cout << *l1;
	    if (++l1 != list1.end()) cout << "->";
	}
	cout << endl;

	cout << "Second List: ";
	for (list<int>::iterator l2 = list2.begin(); l2 != list2.end();){
	    cout << *l2;
	    if (++l2 != list2.end()) cout << "->";
	}
	cout << endl;

	int numOfPairs = 0;
	for (list<int>::iterator l1 = list1.begin(); l1 != list1.end(); ++l1){
	    for (list<int>::iterator l2 = list2.begin(); l2 != list2.end(); ++l2){
			if(*l1 - *l2 == N){
				if(numOfPairs>0) cout<<",";
				cout << "("<<(*l1)<<","<<(*l2)<<")";
				numOfPairs++;
			}
		}
	}
	if(numOfPairs==0) cout << "There is no such a pair!!!"<<endl;
	cout << endl;
}

int main()
{	

	list<int> firstList = {9, 6, 7, 8};
	list<int> secondList = {4, 5, 6};

	task6(firstList, secondList, 4);

	return 0;
}
