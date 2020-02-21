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
	ll sumb;
	bool used;
	vector <int> b;
};

vector < pair<ll, int> > arr;
vector <ll> have;

bool cmp_b(int a, int b) {
	return arr[a].first > arr[b].first;
	//return ((ld)arr[a].first / (ld)have[a]) > ((ld)arr[b].first / (ld)have[b]);
}

bool cmp_lib(const lib &a, const lib &b) {
	if (a.used != b.used)
		return a.used < b.used;
	return ((ld)a.sumb / (ld)a.r) >((ld)b.sumb / (ld)b.r);
}

void recalc(vector <lib> &kek) {
	for (int i = 0; i < (int)kek.size(); i++) {
		kek[i].sumb = 0ll;
		for (int j = 0; j < (int)kek[i].sz; j++)
			kek[i].sumb += arr[kek[i].b[j]].first;
		sort(kek[i].b.begin(), kek[i].b.end(), cmp_b);
	}
}

int main()
{
	in("input.txt");
	out("output.txt");
	srand(1373737);
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ll n, m, d;
	cin >> n >> m >> d;

	arr.resize(n);
	have.resize(n);
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
		lb[i].sumb = 0ll;
		for (int j = 0; j < (int)lb[i].b.size(); j++) {
			cin >> lb[i].b[j];
			lb[i].sumb += arr[lb[i].b[j]].first;
			have[lb[i].b[j]]++;
		}
	}
	for (int i = 0; i < m; i++)
		sort(lb[i].b.begin(), lb[i].b.end(), cmp_b);

	sort(lb.begin(), lb.end(), cmp_lib);

	vector <int> ans(m);
	for (int i = 0; i < m; i++) {
		ans[i] = lb[i].num;
	}

	vector < vector<int> > ansb(m);
	for (int i = 0; i < m; i++) {
		ansb[i] = lb[i].b;
	}

	cout << (int)ans.size() << endl;
	ll day = 0, it = 1;
	for (int i = 0; i < (int)ans.size(); i++) {
		recalc(lb);
		sort(lb.begin() + i, lb.end(), cmp_lib);
		sort(lb[i].b.begin(), lb[i].b.end(), cmp_b);
		day += lb[i].r;
		if (day < d) {
			ll cnt = min((d - day) * lb[i].g, lb[i].sz);
			for (int j = 0; j < cnt; j++) {
				arr[lb[i].b[j]].first = 0;
			}
			for (int j = cnt; j < (int)lb[i].sz; j++)
				have[lb[i].b[j]]--;
		}
		ansb[i] = lb[i].b;
		ans[i] = lb[i].num;
		cout << ans[i] << ' ' << (int)ansb[i].size() << endl;
		for (int j = 0; j < (int)ansb[i].size(); j++) {
			cout << ansb[i][j] << ' ';
		}
		cout << endl;
	}

	return 0;
}