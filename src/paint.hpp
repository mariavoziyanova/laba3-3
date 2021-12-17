#pragma once

#include <graph.hpp>
#include <fstream>

// dot -Tpng graph1.dot -ograph1.png
void visualisation(const Graph &graph, const string &filename)
{
    ofstream file("../graphs/" + filename, std::ios_base::trunc);
    file << "graph " << filename.substr(0, filename.size() - 4) << "{\n";
    file << "\trankdir =LR;\n";
    file << "\tranksep = 0.8;\n";
    file << "\tnodesep = 0.8;\n";

    for (auto &edge: graph.edges)
    {
        file << "\t" << 1 + edge.a << "--" << 1 + edge.b << fixed
             << setprecision(2) << " [label=\"" << edge.cost << "\"];\n";
    }
    file << "}";
    file.close();
}

void visualisation_paint(const Graph &graph, const pair<int, const vector<int>> &a, const string &filename)
{
    vector<string> colours(a.first);
    ifstream in("../graphs/colours.txt", std::ios_base::in);
    int size = 0; // считываем цвета из файла
    while (size < a.first && !in.eof())
    {
        in >> colours[size];
        while (colours[size].empty() && !in.eof())
            in >> colours[size];
        size++;
    }
    in.close();

    ofstream file("../graphs/" + filename, std::ios_base::trunc);
    file << "graph " << filename.substr(0, filename.size() - 4) << "{\n";
    file << "\trankdir = LR;\n";
    file << "\tranksep = 0.8;\n";
    file << "\tnodesep = 0.8;\n";

    for (auto &edge: graph.edges)
    {
        file << "\t" << 1 + edge.a << "--" << 1 + edge.b << ";\n";
    }

    for (int i = 0; i < a.second.size(); i++)
    {
        file << "\t" << 1 + i << " [color=\"" << colours[a.second[i] - 1] << "\",style=filled];\n";
    }

    file << "}";
    file.close();
}

void visualisation_path(const Graph &graph, const vector<int> &a, const string &filename)
{
    ofstream file("../graphs/" + filename, std::ios_base::trunc);
    file << "graph " << filename.substr(0, filename.size() - 4) << "{\n";
    file << "\trankdir =LR;\n";
    file << "\tranksep = 0.8;\n";
    file << "\tnodesep = 0.8;\n";

    for (auto &edge: graph.edges)
    {
        file << "\t" << 1 + edge.a << "--" << 1 + edge.b << fixed
             << setprecision(2) << " [label=\"" << edge.cost << "\"];\n";
    }

    for (int i = 0; i < a.size(); i++)
    {
        file << "\t" << 1 + a[i] << " [color=\"red\",style=filled];\n";
    }

    file << "}";
    file.close();
}

/*
digraph G {
        size ="4,4";
        main [shape=box];
        main -> parse [weight=8];
        parse -> execute;
        main -> init [style=dotted];
        main -> cleanup;
        execute -> { make_string; printf}
        init -> make_string;
        edge [color=red]; // so is this
        main -> printf [style=bold,label="100 times"];
        make_string [label="make a\nstring"];
        node [shape=box,style=filled,color=".7 .3 1.0"];
        execute -> compare;
}
*/