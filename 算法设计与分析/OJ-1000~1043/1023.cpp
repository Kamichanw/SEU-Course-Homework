#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct Node {

	int v = 0, cost = 0, len = 0, jump = 0;
	bool operator<(const Node& n)const{
		return this->len > n.len;
	}
	Node(int v, int cost, int len, int jump) {
		this->v = v;
		this->cost = cost;
		this->len = len;
		this->jump = jump;
	}
};

int c[501];
int map[501][501];
int best[501][101];

int main() {
	int t;
	cin >> t;
	while (t--) {
		priority_queue<Node> q;
		int n, e, s, t, m;
		cin >> n >> e >> s >> t >> m;
		for (int i = 1;i <= n;i++) {
			cin >> c[i];
			for (int j = 1;j <= n;j++) map[i][j] = 0;
			for (int j = 0;j <= m;j++) best[i][j] = 0;//从起点到第i个点花费为j的最短路径
		}
		for (int i = 0;i < e;i++) {
			int u, v, w;
			cin >> u >> v >> w;
			if (map[u][v] == 0) {
				map[u][v] = w;
				map[v][u] = w;
			}
			else {//消除重边
				map[u][v] = map[u][v] > w ? w : map[u][v];
				map[v][u] = map[v][u] > w ? w : map[v][u];
			}
		}
		for (int i = 1;i <= n;i++) if ((map[s][i] != 0) && c[i] <= m) { 
			q.push(Node(i, c[i], map[s][i], 1));
			best[i][c[i]] = map[s][i];
		}
		int flag=1;
		while (!q.empty()&&flag) {//这边就是Dijkstra算法的变种
			Node cur = q.top(); 
			if (cur.v == t) {
				cout << cur.len << endl;
				flag=0;
			}
			if (cur.jump<n-1)
				for (int i = 1;i <= n;i++) {
					if (map[cur.v][i] != 0 && cur.cost + c[i] <= m && i != s)
						if (best[i][cur.cost + c[i]] == 0 || cur.len + map[cur.v][i] < best[i][cur.cost + c[i]]) {
							q.push(Node(i, cur.cost + c[i], cur.len + map[cur.v][i], cur.jump + 1));
							best[i][cur.cost + c[i]] = cur.len + map[cur.v][i];
						}
				}
			q.pop();
		}
		if(flag)
		cout << -1 << endl;
	}
	return 0;
}