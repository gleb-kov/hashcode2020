#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

ifstream fin("tests/f.txt");
ofstream fout("answ/answer_f.txt");

using ll = uint64_t;
size_t books_cnt, libs_cnt, days_cnt;

unordered_map<size_t, size_t> id_book;
vector<ll> book_cost;

struct lib {
    size_t id;
    size_t cnt;
    size_t signup;
    size_t perday;
    ll total_cost;
    vector<size_t> books;

    void sort_books() {
        sort(books.begin(), books.end(), [](size_t lhs, size_t rhs) {
            return book_cost[lhs] > book_cost[rhs];
        });
        /*sort(books.begin(), books.end(), [](size_t lhs, size_t rhs) {
            return ((double) book_cost[lhs] / (double) id_book[lhs]) >
                   ((double) book_cost[rhs] / (double) id_book[rhs]);
        });*/
    }
};

vector<lib> libs;

void sort_libs_by_total(size_t days_used) {
    for (size_t i = 0; i < libs.size(); i++) {
        lib & cur = libs[i];
        cur.sort_books();
        cur.total_cost = 0;

        if (cur.signup + days_used >= days_cnt) {
            continue;
        }
        size_t m = days_cnt - days_used, us = 0;
        m = min(cur.cnt, m * cur.perday);
        for (size_t j = 0; j < cur.books.size() && us < m; j++) {
            size_t tb = cur.books[j];
            if (book_cost[tb] == 0) break;
            cur.total_cost += book_cost[tb];
            us++;
        }
    }

    /*sort(libs.begin(), libs.end(), [](lib const &lhs, lib const &rhs) {
        return lhs.total_cost < rhs.total_cost;
    });*/

    sort(libs.begin(), libs.end(), [](lib const &lhs, lib const &rhs) {
        return ((double) lhs.total_cost / (double) lhs.signup) < ((double) rhs.total_cost / (double) rhs.signup);
    });
}

int main() {
    fin >> books_cnt >> libs_cnt >> days_cnt;

    book_cost.resize(books_cnt);
    libs.resize(libs_cnt);

    for (size_t i = 0; i < books_cnt; i++) {
        fin >> book_cost[i];
    }

    for (size_t i = 0; i < libs_cnt; i++) {
        fin >> libs[i].cnt >> libs[i].signup >> libs[i].perday;
        libs[i].id = i;
        libs[i].books.resize(libs[i].cnt);
        libs[i].total_cost = 0;
        for (size_t j = 0; j < libs[i].cnt; j++) {
            fin >> libs[i].books[j];
            id_book[libs[i].books[j]] += 2;
            // libs_by_book[libs[i].books[j]].push_back(i);
            libs[i].total_cost += book_cost[libs[i].books[j]];
        }
        libs[i].sort_books();
    }

    size_t days_used = 0;

    vector<size_t> ansl;
    vector<vector<size_t>> ansb;

    for (size_t i = 0; i < libs_cnt; i++) {
        cout << i << '/' << libs_cnt << "\n";
        sort_libs_by_total(days_used);
        lib &cur = libs.back();
        if (cur.signup + days_used >= days_cnt) {
            libs.erase(--libs.end());
            continue;
        }
        days_used += cur.signup;
        size_t m = days_cnt - days_used;
        m = min(cur.cnt, m * cur.perday);
        vector<size_t> b;
        for (size_t j = 0; j < cur.books.size() && b.size() < m; j++) {
            size_t tb = cur.books[j];
            if (book_cost[tb] == 0) break;
            b.push_back(tb);
            book_cost[tb] = 0;
        }
        if (!b.empty()) {
            ansl.push_back(cur.id);
            ansb.emplace_back(b);
        }
        libs.erase(--libs.end());
    }

    fout << ansl.size() << "\n";
    for (size_t j = 0; j < ansl.size(); j++) {
        fout << ansl[j] << " " << ansb[j].size() << "\n";
        for (size_t tmp : ansb[j]) {
            fout << tmp << " ";
        }
        fout << "\n";
    }

    return 0;
}
