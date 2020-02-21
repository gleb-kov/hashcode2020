#include <iostream>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <string>
#include <bitset>
#include <ctime>
#include <random>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <sstream>
#pragma comment(linker, "/STACK:256000000")
using namespace std;

#define in(s) freopen(s, "r", stdin)
#define out(s) freopen(s, "w", stdout)
#define forn(i, n) for (int i = 0; i < n; i++)
#define endl '\n'
#define mp make_pair

typedef long long ll;
typedef long double ld;

struct lib {
	ll sz, r, g, num;
	vector <int> b;
};

vector < pair<ll, int> > arr;

bool cmp_b(int a, int b) {
	return arr[a].first > arr[b].first;
}

bool cmp_lib(const lib &a, const lib &b) {
	return a.r < b.r;
}

int main()
{
	in("input.txt");
	out("output.txt");
	srand(1373737);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	ll n, m, d;
	cin >> n >> m >> d;

	arr.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i].first;
		arr[i].second = i;
	}

	vector <lib> lb(m);
	for (int i = 0; i < m; i++) {
		lb[i].num = i;
		cin >> lb[i].sz >> lb[i].r >> lb[i].g;
		lb[i].g = max(lb[i].g, lb[i].sz);
		lb[i].b.resize(lb[i].sz);
		for (int j = 0; j < (int)lb[i].b.size(); j++)
			cin >> lb[i].b[j];
		sort(lb[i].b.begin(), lb[i].b.end(), cmp_b);
	}

	sort(lb.begin(), lb.end(), cmp_lib);

	vector <int> ans(m);
	for (int i = 0; i < m; i++)
		ans[i] = lb[i].num;

	vector < vector<int> > ansb(m);
	for (int i = 0; i < m; i++) {
		ansb[i] = lb[i].b;
	}

	cout << (int)ans.size() << endl;
	for (int i = 0; i < (int)ans.size(); i++) {
		cout << ans[i] << ' ' << (int)ansb[i].size() << endl;
		for (int j = 0; j < (int)ansb[i].size(); j++)
			cout << ansb[i][j] << ' ';
		cout << endl;
	}

	return 0;
}