#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>

using namespace std;

struct lib {
    int nbooks;
    int signup;
    int per_day;
    vector<int> books;
};

int D, L, B;

vector<int> score;
vector<lib> libs; vector<int> order;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> B >> L >> D;
    score.resize(B);
    order.resize(L);

    for (size_t i = 0; i < B; ++i)
        cin >> score[i];

    mt19937 gen((int)time(nullptr));
    vector<uint64_t> totals(L);

    for (size_t i = 0; i < L; ++i) {
        order[i] = i;
        int b, d, pd;
        cin >> b >> d >> pd;

        vector<int> books(b);

        for (size_t j = 0; j < b; ++j) {
            cin >> books[j];
        }

        libs.push_back({b, d, pd, std::move(books)});
    }

    int Lsq = sqrt(L);
    int day = 0;

    vector<int> freq(B);

    Lsq = 2;

    for (int l = 0; l < L; l += Lsq) {
        for (int& x : freq)
            x = 0;

        for (int i = l; i < L; ++i) {
            lib& lb = libs[order[i]];

            totals[order[i]] = 0;
            int ttl = lb.per_day * (D - day - lb.signup);

            if (day + lb.signup > D) {
                totals[order[i]] = 0;
                continue;
            }

            for (int bk = 0; bk < min(ttl, lb.nbooks); ++bk) {
                totals[order[i]] += score[lb.books[bk]];
                ++freq[lb.books[bk]];
            }
        }

        sort(order.begin() + l, order.end(), [&](int i, int j) {
            return totals[i] * 1ll * libs[j].signup > totals[j] * 1ll * libs[i].signup;
        });

        int r = min(L, l + Lsq);

        shuffle(order.begin() + l, order.begin() + r, gen);

        for (int i = l; i < r; ++i) {
            lib& lb = libs[order[i]];

            sort(lb.books.begin(), lb.books.end(), [&](int i, int j) {
                return score[i] > score[j];
            });

            day += lb.signup;
            int ttl = lb.per_day * (D - day);

            for (int bk = 0; bk < min(ttl, lb.nbooks); ++bk)
                score[lb.books[bk]] = 0;
        }
    }

    // output
    cout << L << '\n';
    for (size_t i = 0; i < L; ++i) {
        lib const& l = libs[order[i]];

        cout << order[i] << ' ' << l.nbooks << '\n';

        for (int book_id : l.books)
            cout << book_id << ' ';

        cout << '\n';
    }
    return 0;
}
