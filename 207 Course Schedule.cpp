/*
    Khan's Algorithm, BFS
    
    three representation of graphs
    
    1. edge list: an array of two vertex numbers, add third number for weight
    e.g [ [0,1], [0,6], [0,8], [1,4], [1,6], [1,9], [2,4], [2,6], [3,4], [3,5], [3,8], [4,5], [4,9], [7,8], [7,9] ]
    advantage:
    disadvantage: If the edges appear in the edge list in no particular order, that's a linear search to find if an edge in graph or not
    
    2. adjacency matrix: For a graph with |V| vertices, an adjacency matrix is a |V| X |V| matrix of 0s and 1s, where the entry in row i and column j is 1 if and only if the edge (i,j) is in the graph. If you want to indicate an edge weight, put it in the row i, column j entry, and reserve a special value (perhaps null) to indicate an absent edge.
    
    advantage: find out whether an edge is present in constant time
    disadvantage: 1. take O(V2) space
                  2. if you want to find out which vertices are adjacent to a given vertex i, have to go through V cells in row i
    
    3. adjacency list: combines adjacency matrices with edge lists. For each vertex i ii, store an array of the vertices adjacent to it.
                       If the graph is weighted, then each item in each adjacency list is either a two-item array or an object
    
    advantage: 1.get to each vertex's adjacency list in constant time
               2.To find out whether an edge (i,j) is present in the graph, we go to i's adjacency list in constant time and then look for j in i's adjacency list. How long does that take in the worst case? The answer is O(d), where d is the degree of vertex i, because that's how long i's adjacency list is. The degree of vertex i could be as high as |V|-1 (if i is adjacent to all the other |V|-1 vertices) or as low as 0 (if i ii is isolated, with no incident edges).
    disadvantage:
*/
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> in(numCourses);
        // convert a edge list to adjacency list, also calculte indegree of every node
        // for every list in the adjacency list, index is the "start"(prerequisit), all numbers in a list is the "end"
        for (auto &a : prerequisites) {
            graph[a.second].push_back(a.first);
            ++in[a.first];
        }
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) { // put all node that has 0 indegree into a queue
            if (in[i] == 0) q.push(i);
        }
        while (!q.empty()) {
            int t = q.front();
            q.pop();
            for (auto &a : graph[t]) { // remove the edge, so all "end" node indegree reduce by one, if a vertex has 0 indegree push to queue
                --in[a];
                if (in[a] == 0) q.push(a);
            }
        }
        // if there is still node with indegree greater than 0, then there is cycle, which means live lock
        // which means can not finish all courses
        for (int i = 0; i < numCourses; ++i) {
            if (in[i] != 0) return false;
        }
        return true;
    }
};