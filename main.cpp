#include <iostream>
#include <fstream>
#include <filesystem>
#include "TSP.h"

using namespace std;

struct Point
{
    float x;
    float y;
};

float dist(Point T1, Point T2)
{
    float dist = sqrt((T1.x - T2.x) * (T1.x - T2.x) + (T1.y - T2.y) * (T1.y - T2.y));
    return dist;
}

void readInput(vector<vector<float> >& mx, const int& n, const vector<Point> points)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i == j) mx[i][j] = FLT_MAX;
            else mx[i][j] = dist(points[i], points[j]);
    for (int i = 0; i < n; i++)
    {
        mx[i][0] = i;
        mx[0][i] = i;
    }
}

int main() {
    string path = "C:/Users/Максим/Desktop/TSP/data";
    auto it = filesystem::directory_iterator(path);
    vector<filesystem::path> array_path;
    copy_if(filesystem::begin(it), filesystem::end(it), std::back_inserter(array_path), [](const auto& entry) {
        return filesystem::is_regular_file(entry);
        });
    for (auto& p : array_path)
    {
        ifstream fin;
        fin.open(p.string());
        cout << p.string() << endl;
        int N;
        fin >> N;
        vector<Point> points(N);
        for (int i = 0; i < N; i++)
        {
            Point p;
            fin >> p.x >> p.y;
            points[i] = p;
        }
        N++;
        vector<vector<float>> mx(N, vector<float>(N));
        readInput(mx, N, points);
        TSP tsp(mx);
        float result = tsp.get_res();
        cout << result << endl;
    }
    return 0;
}