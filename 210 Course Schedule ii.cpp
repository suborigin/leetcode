/*
    bfs solution, same as course schedule 1 problem
*/
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses), res;
        for (auto &a : prerequisites) {
            graph[a.second].push_back(a.first);
            ++indegree[a.first];
        }
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
                res.push_back(i);
            }
        }
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (auto &a : graph[cur]) {
                --indegree[a];
                if(indegree[a] == 0) {
                    q.push(a);
                    res.push_back(a);
                }
            }
        }
        return res.size() == numCourses ? res : vector<int> {};
    }
};