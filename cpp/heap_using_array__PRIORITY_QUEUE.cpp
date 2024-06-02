#include<bits/stdc++.h>
using namespace std;

/*
    We are assuming 0 based indexing
    left child = 2*i +1
    right child = 2*i +2

    We are building MAX HEAP
*/
class Heap{
    vector<int> v;
    int size;

public:

    Heap(){
        size = 0;
    }
    /* ** INSERTION IN HEAP
        * We move from end to front

        * First we insert element at the end of array
        * Then we place that element at it's correct position
    */
    void insert(int val){
        cout<<"Inserting...\n";
        size += 1;

        // Inserting val at the end of array
        v.push_back(val);

        int index = size-1;

        // Shifting current element to its correct position
        heapify_up(index);
        print();
    }

    /* ** DELETION IN HEAP (root is removed)
        * We move from root(front) to end

        * First we swap last and root element
        * Then we delete the last element (i.e. Root is deleted)
        * Then we place that new root element at it's correct position
    */
    void remove(){
        if(size == 0){
            cout<<"Heap is empty\n";
            return;
        }

        cout<<"Deleting...\n";

        v[0] = v[size-1];
        size -= 1;
        v.pop_back();
        
        int index = 0;
        heapify_down(v, size, index);
        print();
    }

    /* HEAPIFY UP
        * We move from bottom to top
    */
    void heapify_up(int index){
        int parent = (index-1)/2;
        if(index>0 && v[parent] < v[index]){
            swap(v[parent], v[index]);
            heapify_up(parent);
        }
        
    }

    /*  HEAPIFY DOWN
        * We move from top to bottom while putting element at it's correct position
        * Leaf nodes are always at it's correct position (as it does not have child to compare with)
        * In Complete Binary Tree (CBT) leaf nodes are from (n/2) to (n-1)th element
        * So we will compare from [0,n/2)
        * 
        * 
    */
    
    void heapify_down(vector<int> &v, int size, int index){

        int index_of_max_element = index;

        int leftIndex = 2*index+1;
        int rightIndex = 2*index+2;

        if(leftIndex<size && v[leftIndex] > v[index_of_max_element]){
            index_of_max_element = leftIndex;
        }
        if(rightIndex<size && v[rightIndex] > v[index_of_max_element]){
            index_of_max_element = rightIndex;
        }

        if(index_of_max_element != index){
            swap(v[index_of_max_element], v[index]);
            heapify_down(v,size,index_of_max_element);
        }
        
    }


    /* HEAP SORT
        * Step 0 - Build Heap

        * Step 1 - swap v[0] with v[last_unsorted_element]
        * Step 2 - put root node to it's correct position (heapify_down)
        * 
    */
    void heap_sort(){

        cout<<"Heap sort in action...\n";
        int sz = size;

        while(sz>0){
            swap(v[0], v[sz-1]);
            sz--;
            heapify_down(v,sz,0);
        }

    }

    void print(){
        cout<<"Printing heap...\n";
        for(int val: v){
            cout<<val<<" ";
        }
        cout<<endl;
    }

};

int main(){
    Heap h;
    h.insert(12);
    h.insert(65);
    h.insert(72);
    h.insert(14);
    h.insert(9);
    h.insert(19);

    // h.remove();

    h.heap_sort();
    h.print();

    
    return 0;
}