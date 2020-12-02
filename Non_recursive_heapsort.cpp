/**
    @author Marek Brynda
**/
#include <math.h> 
#include <iostream>

using namespace std; 

void heapify(int arr[], int n){
    // startign from 1 beacuse root doen't have parents
    for(int i=n-1; i>0; i--){
        //check if children is bigger than parents
        // subtract 1 beacuse we starting form 0 -> div by 2 to go to previous level
        if(arr[i]>arr[(i-1)/2]){
            int j = i;
            // we have to change order of parent/chlder as long as parent wont be the biggest of all
            while(arr[j]>arr[(j-1)/2]){
                int child = arr[j];
                int parent = arr[(j-1)/2];
                arr[(j-1)/2] = child;
                arr[j] = parent;
                j=(j-1)/2; 
            }
        }
    }
}

void printArray(int arr[], int n, int sortedN=0){
    if(sortedN==0){
        cout<<"[";
        for( int i = 0; i < (n-1); i++ )
            cout << arr[i]<< ",";
        cout<<arr[n-1]<<"]"<<endl;
    }else{
        cout<<"["<<arr[0];
        for( int i = 1; i < (n-sortedN); i++ )
            cout << ","<<arr[i];
        cout<<"|";
        for( int i = (n-sortedN); i < (n-1); i++ )
            cout << arr[i]<< ",";
        cout<<arr[n-1]<<"]"<<endl;
    }
}

void shiftArr(int arr[], int n){
    for (int i = 0; i < n; i++) {
        arr[i] = arr[i + 1];
    }
}
  
// Driver Code to test above 
int main()  
{ 
    int inputArr[] = {2,4,1,3,5,7,6};  
    // size of array
    int n = sizeof(inputArr)/sizeof(*inputArr);

    cout << "Initial array:";
    printArray(inputArr, n);

    cout << "Initial heap:";
    heapify(inputArr, n);
    printArray(inputArr, n);
    for(int iter = 0; iter < n; iter++){
        if(iter == n-1) cout<<"After deletion of "<<inputArr[0]<<" (sorted array – heap is empty) ";
        else cout<<"After deletion of "<<inputArr[0]<<" ";

        int last = inputArr[0];
        shiftArr(inputArr, n-1-iter);
        inputArr[n-1-iter] = last;
        heapify(inputArr, n-1-iter);
        if(iter == n-1) printArray(inputArr, n);
        else printArray(inputArr, n, iter+1);
    }
  
    return 0; 
} 