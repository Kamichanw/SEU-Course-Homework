#include "iostream"
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;
struct node {
	int v;
	long long weight;
	node * next;
	node(int a, long long b) {
		v = a;
		weight = b;
		next = NULL;
	}
};
struct bnode {
	int u;
	int v;
	long long  dis;
	bool operator <(const bnode &b)const {
		return dis > b.dis;
	}
};
inline long long mymin(long long a, long long b) {
	return a > b ? b : a;
}
struct order {
	int id;
	int start;
	int end;
	vector<int> path;
	int timec;
	int ddl1;
	int ddl2;
	bool operator < (const order &b)const {
		return end < b.end;
	}
};
int path[500000];
vector<node*> head(500000, NULL);
int isdone[500000];
long long dis[500000];
void dijisitra(int s) {
	for (int i = 0; i < 500000; i++) {
		dis[i] = 0x3f3f3f3f3f3f3f3fLL;
		isdone[i] = 0;
		path[i] = 0;
	}

	priority_queue<bnode> pq;
	node *first = head[s];
	dis[s] = 0;
	while (first != NULL) {
		bnode temp;
		temp.u = s;
		temp.v = first->v;
		temp.dis = first->weight;
		dis[temp.v] = first->weight;
		pq.push(temp);
		first = first->next;
	}

	while (!pq.empty()) {
		bnode nownode = pq.top();
		pq.pop();
		if (isdone[nownode.v])continue;
		isdone[nownode.v] = 1;
		node *temp = head[nownode.v];
		while (temp != NULL) {
			if (!isdone[temp->v]) {
				if (dis[temp->v] > dis[nownode.v] + temp->weight) {
					dis[temp->v] = dis[nownode.v] + temp->weight;
					bnode a;
					a.u = nownode.v;
					a.v = temp->v;
					a.dis = dis[temp->v];
					pq.push(a);
					path[temp->v] = nownode.v;
				}
			}
			temp = temp->next;

		}
	}

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	vector<string>ans;
	while (t--) {
		for (int i = 0; i < 500000; i++) {
			head[i] = NULL;

		}
		int n, e, r, x;
		cin >> n >> e >> r >> x;
		vector<pair<int, int>> vpos;
		for (int i = 1; i <= e; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			node *temp = head[u];
			if (temp == NULL) {
				head[u] = new node(v, w);
			} else {
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = new node(v, w);
			}
			temp = head[v];
			if (temp == NULL) {
				head[v] = new node(u, w);
			} else {
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = new node(u, w);
			}
		}
		priority_queue<order> totalorder;
		for (int i = 0; i < r; i++) {
			int start, end, ddl1, ddl2;
			cin >> start >> end >> ddl1 >> ddl2;
			dijisitra(start);
			stack<int> s;
			int t = end;
			while (path[t] != start && t != 0) {
				s.push(t);
				t = path[t];
			}
			s.push(start);
			order temp;
			temp.start = start;
			temp.end = end;
			temp.ddl1 = ddl1;
			temp.ddl2 = ddl2;
			temp.id = i + 1;
			temp.timec = dis[end];
			if(temp.timec>temp.ddl2)continue;
			while (!s.empty()) {
				int nw = s.top();
				s.pop();
				temp.path.push_back(nw);

			}

			totalorder.push(temp);


		}
		string thisans;
		int lastpos;
		int i = 1;
		for (; i <= x && !totalorder.empty(); i++) {
			int time = 0;
			order noworder = totalorder.top();
			if (lastpos == noworder.start || time == 0) {
				if (time + noworder.timec > noworder.ddl2)
					continue;
			} else {
				dijisitra(lastpos);
				if (time + noworder.timec + dis[noworder.start] > noworder.ddl2)
					continue;
			}

			noworder = totalorder.top();
			totalorder.pop();

			thisans += "solution " + to_string(i) ;
			thisans += "\npick " + to_string(noworder.id);

			if (lastpos == noworder.start || time == 0) {
				thisans += "\ngoto " + to_string(noworder.path.size());
				for (auto xx : noworder.path) {
					thisans += " " + to_string(xx);
				}
			} else {
				dijisitra(lastpos);
				time += dis[noworder.start];
				if (time >= 144)break;
				stack<int> s;
				int t = noworder.start;
				while (path[t] != noworder.start && t != 0) {
					s.push(t);
					t = path[t];
				}
				thisans += "\ngoto " + to_string(noworder.path.size() + s.size());
				while (!s.empty()) {
					int sw = s.top();
					s.pop();
					thisans += " " + to_string(sw);

				}
				for (auto xx : noworder.path) {
					thisans += " " + to_string(xx);
				}

			}
			time += noworder.timec;
			if (time < noworder.ddl1)time = noworder.ddl1;
			if (time <= 144) {
				thisans += "\nserve " + to_string(noworder.id);
				thisans += "\n";
				lastpos = noworder.end;
				i--;
			}else{
				lastpos=-1;
			}
			
		}
		ans.push_back(thisans);
	}
	for(auto sss:ans){
		cout<<sss<<endl;
	}
	




	return 0;
}