#pragma once

#include "vertex.hpp"
#include <chrono>
#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <random>

using namespace std;

/// ребро графа
struct Edge
{
    int a = 0; // индекс первой вершины
    int b = 0; // индекс второй вершины
    double cost = 0.0; // цена пути между ними

    Edge(int a, int b, double cost) : a(a), b(b), cost(cost)
    {};

    ~Edge() = default;
};

/// неориентированный граф
class Graph
{
public:
    vector<vector<bool>> mx; // матрица смежности, вершина смежна сама с собой
    vector<Vertex> verts; // вершины
    vector<Edge> edges;
    int n = 0; // количество вершин
    int m = 0; // количество рёбер

    Graph(const vector<vector<bool>> &matrix, const vector<Vertex> &verts) : mx(matrix), verts(verts), n(verts.size())
    {
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (mx[i][j])
                    m++;

        edges.reserve(m);
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (mx[i][j])
                    edges.emplace_back(i, j, dist(verts[i], verts[j]));
    };

    void add_vertex(const Vertex &p)
    {
        // проверка на дубликат
        for (auto &v: verts)
            if (equal(v, p, 0.0001))
                return;

        verts.emplace_back(p);
        for (int i = 0; i < n; ++i)
            mx[i].emplace_back(false);
        mx.emplace_back(vector<bool>(n + 1, false));
        n++;
    }

    void add_edge(const int begin, const int end)
    {
        if (begin < 0 || begin >= n || end < 0 || end >= n)
        {
            cerr << "Error in function add_edge(" << begin << ", " << end << ")\n";
            throw out_of_range("Error in function add_edge");
        }

        // проверка на дубликат
        if (mx[begin][end])
            return;

        m++;
        edges.emplace_back(Edge(begin, end, dist(verts[begin], verts[end])));
        mx[begin][end] = true;
        mx[end][begin] = true;
    }

    /// поиск кратчайшего расстояния от начальной вершины до всех
    vector<double> search(int begin) const
    {
        if (begin < 0 || begin >= n)
        {
            cerr << "Error in function search(" << begin << ")\n";
            throw out_of_range("Error in function search");
        }

        vector<double> d(n, 1e9);
        d[begin] = 0;
        while (true)
        {
            bool any = false;
            for (int j = 0; j < m; ++j)
                if (d[edges[j].b] > d[edges[j].a] + edges[j].cost)
                {
                    d[edges[j].b] = d[edges[j].a] + edges[j].cost;
                    any = true;
                } else if (d[edges[j].a] > d[edges[j].b] + edges[j].cost)
                {
                    // так как граф не ориентированный и все рёбра хранятся один раз
                    d[edges[j].a] = d[edges[j].b] + edges[j].cost;
                    any = true;
                }
            if (!any) break;
        }

        for (int i = 0; i < n; i++)
            if (d[i] == 1e9)
                d[i] = -1.0;

        return d;
    }

    /// поиск кратчайшего пути между двумя вершинами
    vector<int> search_path(int begin, int end) const
    {
        if (begin < 0 || begin >= n || end < 0 || end >= n)
        {
            cerr << "Error in function search_path(" << begin << ", " << end << ")\n";
            throw out_of_range("Error in function search_path");
        }

        vector<double> d(n, 1e9);
        d[begin] = 0;
        vector<int> p(n, -1); // храним предпоследнюю вершину в кратчайшем пути, ведущем в неё
        while (true)
        {
            bool any = false;
            for (int j = 0; j < m; ++j)
                if (d[edges[j].b] > d[edges[j].a] + edges[j].cost)
                {
                    d[edges[j].b] = d[edges[j].a] + edges[j].cost;
                    p[edges[j].b] = edges[j].a;
                    any = true;
                } else if (d[edges[j].a] > d[edges[j].b] + edges[j].cost)
                {
                    // так как граф не ориентированный и все рёбра хранятся один раз
                    d[edges[j].a] = d[edges[j].b] + edges[j].cost;
                    p[edges[j].a] = edges[j].b;
                    any = true;
                }
            if (!any) break;
        }

        if (d[end] == 1e9)
            return {begin};

        vector<int> path;
        path.reserve(n / 2);
        for (int cur = end; cur != -1; cur = p[cur])
            path.push_back(cur);
        reverse(path.begin(), path.end());

        return path;
    }

    /// возвращает пару из: числа цветов, и цвета для каждой вершины
    pair<int, vector<int>> paint() const
    {
        vector<vector<bool>> a(mx);
        vector<int> ans(n, 0);
        int k = 1;
        for (int i = 0; i < n; i++)
        {
            if (ans[i])
                continue;

            ans[i] = k;
            while (true)
            {
                int j = -1; // ищем первую вершину не смежную с данной
                for (int t = i + 1; t < n; t++)
                    if (!a[i][t])
                    {
                        j = t;
                        break;
                    }

                if (j == -1)
                    break;

                // сложение i строки с j строкой
                for (int t = 0; t < n; t++)
                    a[i][t] = max(a[i][t], a[j][t]);
                ans[j] = k;
            }
            k += 1;
        }

        return {k - 1, ans};
    }

    ~Graph() = default;
};

// Генерация случайного графа заданного размера
Graph generate_graph(int n)
{
    // n - размер графа (количество вершин)
    vector<vector<bool>> mx(n);
    random_device rd;
    mt19937 mersenne(rd());

    for (int i = 0; i < n; i++)
    {
        mx[i].resize(n, false);
        for (int j = 0; j < n; j++)
            if (mersenne() % (n / 3) == 3)
                mx[i][j] = true;
        mx[i][i] = true;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
            if (mx[j][i])
                mx[i][j] = true;
    }

    vector<Vertex> verts(n);
    for (int i = 0; i < n; i++)
        verts[i] = Vertex(mersenne() % 3 * n, mersenne() % 3 * n, 0);

    Graph graph(mx, verts);
    return graph;
}
