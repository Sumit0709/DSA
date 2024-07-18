#include<bits/stdc++.h>
using namespace std;

class SCC{
private:
    

    void dfs1(int node, vector<int> adj[], vector<int> &visited, stack<int> &st){
        visited[node] = 1;

        for(int nxt: adj[node]){
            if(!visited[nxt]){
                dfs1(nxt,adj,visited,st);
            }
        }

        st.push(node);
    }

    void reverse_graph(int V, vector<int> adj[], vector<int> reversed_adj[]){

        // start i with 0 if it's 0 based or else start with 1
        for(int i=0; i<V; i++){
            for(int nxt: adj[i]){
                reversed_adj[nxt].push_back(i);
            }
        }

    }

    void dfs2(int node, vector<int> adj[], vector<int> &visited, vector<int> &scc){
        visited[node] = 1;
        scc.push_back(node);

        for(int nxt: adj[node]){
            if(!visited[nxt]){
                dfs2(nxt,adj,visited,scc);
            }
        }
    }


public:

    void count_scc(int V, vector<int> adj[]){

        stack<int> st; // store finishing sequence of vertices
        vector<int> visited(V,0); 

        for(int i=0; i<V; i++){
            if(!visited[i]){
                dfs1(i,adj,visited,st);
            }
        }

        vector<int> reversed_adj[V];
        reverse_graph(V,adj,reversed_adj);

        visited.assign(V,0);
        int count = 0;

        while(!st.empty()){
            if(!visited[st.top()]){
                vector<int> scc;
                dfs2(st.top(),reversed_adj,visited,scc);
                count++;
            }
            st.pop();
        }

        cout<<"Total number of SCC = "<<count<<endl;

    }
};



int main(){


    int V,E;
    cin>>V>>E;

    vector<int> adj[V];
    for(int i=0; i<E; i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
    }

    SCC obj;
    obj.count_scc(V,adj);
    


    return 0;
}