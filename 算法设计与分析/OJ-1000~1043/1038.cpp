
#include <iostream>
#include <algorithm>
#include <queue>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <functional>

#define mset(a,b) memset(a,b,sizeof(a))
using namespace std;
const int maxn = 105; //顶点数量>a+b
const int inf = 0x3f3f3f3f;
int weight[56][56];
struct edge {
	int to, cap, cost, rev;
	edge() {}
	edge(int to, int cap, int cost, int rev) {
		this->to = to, this->cap = cap, this->cost = cost, this->rev = rev;
	}
};

vector<edge> adja[maxn];
int dis[maxn], prevv[maxn], preve[maxn], top;
bool inque[maxn];
void init(int n) {
	for (int i = 0; i < n; ++i)    adja[i].clear();
	top = n;
}
void addEdge(int u, int v, int f, int cost) {
	adja[u].push_back(edge(v, f, cost, adja[v].size()));
	adja[v].push_back(edge(u, 0, -1 * cost, adja[u].size() - 1));
}
bool spfa(int s, int t) {
	queue<int> mp;
	mset(dis, inf);
	mset(prevv, -1);
	mset(inque, 0);
	mp.push(s), prevv[s] = s, dis[s] = 0, inque[s] = true;
	while (!mp.empty()) {
		int u = mp.front();
		mp.pop();
		inque[u] = false;
		for (int i = 0; i < adja[u].size(); ++i) {
			edge& e = adja[u][i];
			if (e.cap > 0 && dis[e.to] > dis[u] + e.cost) {//松弛操作，与普通spfa不同的地方
				dis[e.to] = dis[u] + e.cost;
				prevv[e.to] = u;
				preve[e.to] = i;
				if (!inque[e.to]) {
					inque[e.to] = true;
					mp.push(e.to);
				}
			}
		}
	}
	if (prevv[t] != -1) return true;
	return false;
}
int minCostMaxFlow(int s, int t, int &cost) {
	cost = 0;
	int flow = 0;
	while (spfa(s, t)) {
		int minn = inf;
		for (int v = t; v != prevv[v]; v = prevv[v]) {
			minn = min(adja[prevv[v]][preve[v]].cap, minn);//判断路径上的最小流量，这边这个路径回溯和Dijkstra一样的
		}
		flow += minn;

		for (int v = t; v != prevv[v]; v = prevv[v]) {
			edge& e = adja[prevv[v]][preve[v]];
			cost += minn * e.cost;
			e.cap -= minn;
			adja[v][e.rev].cap += minn;
		}
	}
	return flow;
}


int main() {
	int x;
	cin >> x;
	while (x--) {
		int a, b;
		cin >> a >> b;
		int n = a + b + 2;
		init(n);

		for (int i = 1; i <= b; i++) {
			for (int j = 1; j <= a; j++) {
				cin >> weight[j][i];
			}
		}
		for (int i = 1; i <= a; i++) {
			int k;
			cin >> k;
			while (k--) {
				int v;
				cin >> v;
				addEdge(i, a + v, 1, weight[i][v]);
			}
		}
		for (int i = 1; i <= a; i++) {
			addEdge(0, i, 1, 0);
		}
		for (int i = 1; i <= b; i++) {
			addEdge(a + i, n - 1, 1, 0);
		}
		int cost;
		int flow = minCostMaxFlow(0, n - 1, cost);

		cout << flow << " " << cost << endl;
	}

	return 0;
}
