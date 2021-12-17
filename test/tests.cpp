#include <cstdlib>
#include "graph.hpp"
#include "gtest/gtest.h"
#include <paint.hpp>
#include <random>

TEST(Graph, paint)
{
    int n = 7;
    vector<vector<bool>> mx = {{1, 1, 1, 0, 0, 0, 1},
                               {1, 1, 1, 1, 0, 0, 0},
                               {1, 1, 1, 1, 0, 1, 1},
                               {0, 1, 1, 1, 1, 0, 1},
                               {0, 0, 0, 1, 1, 1, 0},
                               {0, 0, 1, 0, 1, 1, 0},
                               {1, 0, 1, 1, 0, 0, 1}};

    vector<Vertex> verts(n);
    for (int i = 0; i < n; i++)
        verts[i] = Vertex(rand() % 10, rand() % 10, 0);

    Graph graph(mx, verts);
    auto ans = graph.paint();
    vector<int> true_ans = {1, 2, 3, 1, 3, 1, 2};

    ASSERT_EQ(ans.first, 3);
    ASSERT_TRUE(ans.second == true_ans);
}

TEST(Graph, path)
{
    vector<vector<bool>> mx = {{0, 1, 0, 1, 1, 1},
                               {1, 0, 1, 0, 0, 0},
                               {0, 1, 0, 1, 0, 1},
                               {1, 0, 1, 0, 1, 0},
                               {1, 0, 0, 1, 0, 1},
                               {1, 0, 1, 0, 1, 0}};

    vector<Vertex> verts = {Vertex(0, 2, 0), Vertex(2, 2, 0),
                            Vertex(3, 1, 0), Vertex(2, 0, 0),
                            Vertex(0, 0, 0), Vertex(1, 1, 1)};
    Graph graph(mx, verts);

    auto ans2 = graph.search_path(0, 2);
    vector<int> true_path = {0, 1, 2};
    ASSERT_TRUE(ans2 == true_path);
}

TEST(Graph, search)
{
    vector<vector<bool>> mx = {{0, 1, 0, 1, 1, 1},
                               {1, 0, 1, 0, 0, 0},
                               {0, 1, 0, 1, 0, 1},
                               {1, 0, 1, 0, 1, 0},
                               {1, 0, 0, 1, 0, 1},
                               {1, 0, 1, 0, 1, 0}};

    vector<Vertex> verts = {Vertex(0, 2, 0), Vertex(2, 2, 0), Vertex(3, 1, 0), Vertex(2, 0, 0), Vertex(0, 0, 0), Vertex(1, 1, 1)};
    Graph graph(mx, verts);

    vector<double> ans0 = {0.0, 2.0, 2 + sqrt(2), sqrt(8), 2.0, sqrt(3)};
//    print_distance(graph.search(0));
    ASSERT_TRUE(graph.search(0) == ans0);

    vector<double> ans4 = {2.0, 4.0, 2.0 + sqrt(2), 2.0, 0.0, sqrt(3)};
//    print_distance(graph.search(4));
    ASSERT_TRUE(graph.search(4) == ans4);
}

TEST(Graph, search_path)
{
    vector<vector<bool>> mx = {{0, 1, 0, 1, 1, 1},
                               {1, 0, 1, 0, 0, 0},
                               {0, 1, 0, 1, 0, 1},
                               {1, 0, 1, 0, 1, 0},
                               {1, 0, 0, 1, 0, 1},
                               {1, 0, 1, 0, 1, 0}};

    vector<Vertex> verts = {Vertex(0, 2, 0), Vertex(2, 2, 0), Vertex(3, 1, 0), Vertex(2, 0, 0), Vertex(0, 0, 0), Vertex(1, 1, 1)};
    Graph graph(mx, verts);

    vector<int> ans = {4, 3, 2};
    ASSERT_TRUE(graph.search_path(4, 2) == ans);
    vector<int> ans2 = {5, 2, 1};
    ASSERT_TRUE(ans2 == graph.search_path(5, 1));
//    for (int i: ans2)
//        cout << i << ", ";
}

TEST(Graph, add)
{
    vector<vector<bool>> mx = {{0, 1, 0, 1, 1, 1},
                               {1, 0, 1, 0, 0, 0},
                               {0, 1, 0, 1, 0, 1},
                               {1, 0, 1, 0, 1, 0},
                               {1, 0, 0, 1, 0, 1},
                               {1, 0, 1, 0, 1, 0}};

    vector<Vertex> verts = {Vertex(0, 2, 0), Vertex(2, 2, 0), Vertex(3, 1, 0), Vertex(2, 0, 0), Vertex(0, 0, 0), Vertex(1, 1, 1)};
    Graph graph(mx, verts);

    graph.add_vertex(Vertex{2, 1, 0});
    graph.add_edge(6, 2);
    graph.add_edge(6, 1);
    graph.add_edge(6, 4);
    graph.add_edge(6, 3);

    vector<double> ans4 = {2.0, sqrt(5) + 1, sqrt(5) + 1, 2.0, 0.0, sqrt(3), sqrt(5)};
    ASSERT_TRUE(graph.search(4) == ans4);

    vector<int> ans = graph.search_path(4, 2);
    vector<Vertex> path(ans.size());
    for (int i = 0; i < ans.size(); i++)
        path[i] = graph.verts[ans[i]];
}

TEST(Graph, visualisation)
{
    vector<vector<bool>> mx = {{0, 1, 0, 1, 1},
                               {1, 0, 1, 0, 0},
                               {0, 1, 0, 1, 0},
                               {1, 0, 1, 0, 1},
                               {1, 0, 0, 1, 0}};

    vector<Vertex> verts = {Vertex(0, 2, 0), Vertex(2, 2, 0), Vertex(3, 1, 0), Vertex(2, 0, 0), Vertex(0, 0, 0)};
    Graph graph(mx, verts);

    visualisation(graph, "graph1.dot");
}

TEST(Graph, visualisation_paint)
{
    int n = 7;
    vector<vector<bool>> mx = {{1, 1, 1, 0, 0, 0, 1},
                               {1, 1, 1, 1, 0, 0, 0},
                               {1, 1, 1, 1, 0, 1, 1},
                               {0, 1, 1, 1, 1, 0, 1},
                               {0, 0, 0, 1, 1, 1, 0},
                               {0, 0, 1, 0, 1, 1, 0},
                               {1, 0, 1, 1, 0, 0, 1}};

    vector<Vertex> verts(n);
    random_device rd;
    mt19937 mersenne(rd());
    for (int i = 0; i < n; i++)
        verts[i] = Vertex(mersenne() % 20, mersenne() % 20, 0);

    Graph graph(mx, verts);
    pair<int, vector<int>> ans = graph.paint();

    // dot -Tpng graph2.dot -ograph2.png
    visualisation_paint(graph, ans, "graph2.dot");
}

TEST(Graph, big_paint)
{
    int n = 30;

    Graph graph = generate_graph(n);
    pair<int, vector<int>> ans = graph.paint();

    // dot -Tpng big_paint_graph.dot -ograph5.png
    visualisation_paint(graph, ans, "big_paint_graph.dot");
}

TEST(Graph, visualisation_path)
{
    vector<vector<bool>> mx = {{0, 1, 0, 1, 1},
                               {1, 0, 1, 0, 0},
                               {0, 1, 0, 1, 0},
                               {1, 0, 1, 0, 1},
                               {1, 0, 0, 1, 0}};

    vector<Vertex> verts = {Vertex(0, 2, 0), Vertex(2, 2, 0), Vertex(3, 1, 0), Vertex(2, 0, 0), Vertex(0, 0, 0)};
    Graph graph(mx, verts);
    vector<int> ans = graph.search_path(0,2);

    // dot -Tpng graph3.dot -ograph3.png
    visualisation_path(graph, ans, "graph3.dot");
}

TEST(Graph, vis_paint1)
{
    int n = 15;

    Graph graph = generate_graph(n);
    pair<int, vector<int>> ans = graph.paint();

    // dot -Tpng graph4.dot -ograph4.png
    visualisation_paint(graph, ans, "graph4.dot");
}

TEST(Graph, vis_path1)
{
    vector<vector<bool>> mx = {{0, 1, 0, 1, 1, 1},
                               {1, 0, 1, 0, 0, 0},
                               {0, 1, 0, 1, 0, 1},
                               {1, 0, 1, 0, 1, 1},
                               {1, 0, 0, 1, 0, 1},
                               {1, 0, 1, 1, 1, 0}};


    vector<Vertex> verts = {Vertex(0, 2, 0), Vertex(2, 2, 0), Vertex(3, 1, 0), Vertex(2, 0, 0), Vertex(0, 0, 0), Vertex(4, 3, 0)};
    Graph graph(mx, verts);
    vector<int> ans = graph.search_path(1,5);

    // dot -Tpng graph_path1.dot -ograph6.png
    visualisation_path(graph, ans, "graph_path1.dot");
}

TEST(Graph, vis_path2)
{
    vector<vector<bool>> mx = {{1, 1, 0, 1, 1},
                               {1, 1, 1, 0, 0},
                               {0, 1, 1, 1, 0},
                               {1, 0, 1, 1, 1},
                               {1, 0, 0, 1, 1}};

    vector<Vertex> verts = {Vertex(0, 2, 0), Vertex(2, 2, 0), Vertex(3, 1, 0), Vertex(2, 0, 0), Vertex(0, 0, 0)};
    Graph graph(mx, verts);
    vector<int> ans = graph.search_path(0,3);
    

    // dot -Tpng graph_path2.dot -ograph7.png
    visualisation_path(graph, ans, "graph_path2.dot");
}

TEST(Graph, vis_path3)
{
    vector<vector<bool>> mx = {{0, 1, 0, 1, 1, 1, 1, 1, 1},
                               {1, 0, 1, 0, 0, 0, 0, 1, 0},
                               {0, 1, 0, 1, 0, 1, 1, 1, 0},
                               {1, 0, 1, 0, 1, 1, 1, 0, 0},
                               {1, 0, 0, 1, 0, 1, 0, 1, 0},
                               {1, 0, 1, 1, 1, 0, 1, 1, 1},
                               {1, 0, 1, 1, 0, 1, 0, 1, 0},
                               {1, 1, 1, 0, 1, 1, 1, 0, 0},
                               {1, 0, 0, 0, 0, 1, 0, 0, 0}};


    vector<Vertex> verts = {Vertex(0, 2, 0), Vertex(2, 2, 0), Vertex(3, 1, 0), Vertex(2, 0, 0), Vertex(0, 0, 0), Vertex(4, 3, 0), Vertex(2, 3, 0), Vertex(4, 0, 0), Vertex(1, 3, 0)};
    Graph graph(mx, verts);
    vector<int> ans = graph.search_path(1,8);

    // dot -Tpng graph_path3.dot -ograph8.png
    visualisation_path(graph, ans, "graph_path3.dot");
}
TEST(Graph, vis_path4)
{
    vector<vector<bool>> mx = {{1, 1, 0, 1, 1},
                               {1, 1, 1, 0, 0},
                               {0, 1, 1, 1, 0},
                               {1, 0, 1, 1, 1},
                               {1, 0, 0, 1, 1}};

    vector<Vertex> verts = {Vertex(0, 2, 0), Vertex(2, 2, 0), Vertex(3, 1, 0), Vertex(2, 0, 0), Vertex(0, 0, 0)};
    Graph graph(mx, verts);
    vector<int> ans = graph.search_path(1,4);


    // dot -Tpng graph_path4.dot -ograph9.png
    visualisation_path(graph, ans, "graph_path4.dot");
}