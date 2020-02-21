#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct lib {
    int nbooks;
    int signup;
    int per_day;
    vector<int> books;
};

vector<lib> libs;
int B, L, D;
int RL;
vector<int> score;
vector<int> order;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cout.tie(nullptr);

    {
        cin >> B >> L >> D;
        score.resize(B);
        order.resize(L);

        for (size_t i = 0; i < B; ++i)
            cin >> score[i];

        for (size_t i = 0; i < L; ++i) {
            order[i] = i;
            int b, d, pd;
            cin >> b >> d >> pd;

            vector<int> books(b);

            for (size_t j = 0; j < b; ++j)
                cin >> books[j];

            libs.push_back({b, d, pd, books});
        }
    }

    cin >> RL;
    unordered_set<int> ok_books;

    int day_signup = 0;
    vector<int> books(B);

    for (size_t i = 0; i < RL; ++i) {
        int nbooks, id;
        cin >> id >> nbooks;

        for (size_t j = 0; j < nbooks; ++j)
            cin >> books[j];

        lib& l = libs[id];
        if (day_signup + l.signup > D) {
            // ignore
            continue;
        }

        day_signup += l.signup;

        int can = (D - day_signup) * l.per_day;
        for (int b = 0; b < min(can, l.nbooks); ++b)
            ok_books.insert(books[b]);
    }

    uint64_t sc = 0;
    for (auto i : ok_books)
        sc += score[i];
    cout << sc << '\n';
    return 0;
}