#include <fstream>
#include "graph.hpp"

#define CIN                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

void bench_search(int n)
{
    ofstream file("../graphics/bench_search.txt", ios_base::trunc);
    for (int i = n / 50; i <= n; i += n / 50)
    {
        Graph graph = generate_graph(i);
        auto begin = chrono::steady_clock::now();
        vector<double> ans1 = graph.search(0);
        vector<double> ans2 = graph.search(i / 4);
        vector<double> ans3 = graph.search(i / 2);
        vector<double> ans4 = graph.search(i - 1);
        auto end = chrono::steady_clock::now();
        auto time = chrono::duration_cast<chrono::microseconds>(end - begin);
        cout << i << "\n";
        file << i << " " << time.count() / 4.0 << "\n";
    }
    file.close();
}

void bench_paint(int n)
{
    ofstream file("../graphics/bench_paint.txt", ios_base::trunc);
    for (int i = n / 50; i <= n; i += n / 50)
    {
        Graph graph = generate_graph(i);
        auto begin = chrono::steady_clock::now();
        auto ans = graph.paint();
        auto end = chrono::steady_clock::now();
        auto time = chrono::duration_cast<chrono::microseconds>(end - begin);
        cout << i << "\n";
        file << i << " " << time.count() << "\n";
    }
    file.close();
}

int main()
{
//    CIN;
//    bench_search(30000);
//    bench_paint(10000);

    return 0;
}
