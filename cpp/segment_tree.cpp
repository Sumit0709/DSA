#include<bits/stdc++.h>
using namespace std;

class SegmentTree{
    
    public:
    void build(int idx, int low, int high, vector<int> &arr, vector<int> &seg){

        if(low == high){
            seg[idx] = arr[low];
            return;
        }
        int mid = low + (high - low)/2;
        build(2*idx+1,low,mid,arr,seg);
        build(2*idx+2,mid+1,high,arr,seg);

        // Change this based on question's requirement (currently this is for SUM)
        seg[idx] = seg[2*idx+1] + seg[2*idx+2];
    }

    int query(int idx, int low, int high, int my_l, int my_r, vector<int> &seg){

        if(low>=my_l && high<=my_r){
            return seg[idx];
        }
        else if(my_l>high || my_r<low){
            // Change this based on question's requirement (currently this is for SUM)
            return 0;
        }

        int mid = low+(high - low)/2;

        int left = query(2*idx+1, low, mid, my_l, my_r, seg);
        int right = query(2*idx+2, mid+1, high, my_l, my_r, seg);

        return left + right;
    }

    void point_update(int idx, int low, int high, int node, int new_val, vector<int> &seg){
        if(low == high){
            seg[idx] = new_val;
            return;
        }

        int mid = low+(high-low)/2;
        if(node<=mid && node>=low){
            point_update(2*idx+1, low, mid, node, new_val, seg);
        }
        else{
            point_update(2*idx+2, mid+1, high, node, new_val, seg);
        }

        // Change this based on question's requirement (currently this is for SUM)
        seg[idx] = seg[2*idx+1] + seg[2*idx+2];
    }



    // This is for lazy update
    void range_update(int idx, int low, int high, int my_l, int my_r, int val, vector<int> &seg, vector<int> &lazy){

        if(lazy[idx]!=0){
            seg[idx] += (high-low+1)*lazy[idx];
            if(low != high){
                lazy[2*idx+1] += lazy[idx];
                lazy[2*idx+2] += lazy[idx];
            }
            lazy[idx] = 0;
        }

        if(my_l>high || my_r<low || low>high) return;

        else if(low>=my_l && high<=my_r){
            seg[idx] += (high-low+1)*val;
            if(low != high){
                lazy[2*idx+1] += val;
                lazy[2*idx+2] += val;
            }
            return;
        }

        int mid = low + (high - low)/2;
        range_update(2*idx+1, low, mid, my_l, my_r, val, seg, lazy);
        range_update(2*idx+2, mid+1, high, my_l, my_r, val, seg, lazy);

        // Change this based on question's requirement (currently this is for SUM)
        seg[idx] = seg[2*idx+1] + seg[2*idx+2];

    }

    int query_lazy(int idx, int low, int high, int my_l, int my_r, vector<int> &seg, vector<int> &lazy){

        if(lazy[idx]!=0){
            seg[idx] += lazy[idx]*(high-low+1);
            if(low != high){
                lazy[2*idx+1] += lazy[idx];
                lazy[2*idx+2] += lazy[idx];
            }
            lazy[idx] = 0;
        }

        if(my_l>high || my_r<low || low>high) return 0;

        else if(low>=my_l && high<=my_r){
            return seg[idx];
        }

        int mid = low + (high-low)/2;
        return query_lazy(2*idx+1,low,mid,my_l,my_r,seg,lazy) +
                query_lazy(2*idx+2,mid+1,high,my_l,my_r,seg,lazy);
    }

};

int main(){


    int n;
    cin>>n;
    vector<int> arr(n), seg(4*n), lazy(4*n,0);
    SegmentTree sg;

    for(int i=0; i<n; i++)
        cin>>arr[i];

    sg.build(0,0,n-1,arr,seg);

    int q;
    cin>>q;

    for(int i=0; i<q; i++){
        int l,r;
        cin>>l>>r;
        cout<<sg.query(0,0,n-1,l,r,seg);
        cout<<endl;
    }

    // sg.point_update(0,0,n-1,2,8,seg);
    // cout<<sg.query(0,0,n-1,1,3,seg);
    // cout<<endl;
    // sg.range_update(0,0,n-1,3,8,1,seg,lazy);
    // cout<<sg.query_lazy(0,0,n-1,1,3,seg,lazy);
    return 0;
}