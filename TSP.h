#pragma once
#ifndef TSP_h
#define TSP_h

#include <vector>
#include <cmath>
#include <utility>

using namespace std;

struct s_point
{
    pair <int, int> realc;
    pair <int, int> absc;
};

struct v_point
{
    s_point s_point;
    float val;
};


class TSP {
private:
    vector<v_point> edges;
    float res;
public:
    TSP(vector<vector<float>>& mx);
    vector<v_point> re_cols(vector<vector<float>>& mx);
    vector<v_point> re_lines(vector<vector<float>>& mx);
    float SumCol_n_Lines(const vector<v_point>& cols, const vector<v_point>& lines);
    float re_mx(vector<vector<float>>& mx);
    vector<s_point> line_one(const vector<vector<float>>& mx);
    vector<float> d_i(const vector<vector<float>>& mx, const vector<s_point>& s);
    vector<float> d_j(const vector<vector<float>>& mx, const vector<s_point>& s);
    v_point maxing(const vector<float>& di, const vector<float>& dj, const vector<s_point>& s);
    vector<vector<float>> modificator(const vector<vector<float>>& mx, s_point kl);
    pair<bool, float> NGFC(float old_H, int new_H, v_point kl);
    float recurs(vector<vector<float>>& mx, float sum);
    float get_res();
    vector<v_point> get_res_path();
    void print_matrix(const vector<vector<float>>& mx);
};

#endif
