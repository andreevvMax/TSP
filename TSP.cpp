#include "TSP.h"
#include <iostream>

using namespace std;

TSP::TSP(vector<vector<float> >& mx)
{
    float sum = re_mx(mx);
    res = recurs(mx, sum);
}

float TSP::recurs(vector<vector<float> >& mx, float sum)
{
    if (mx.size() > 3)
    {
        vector<s_point> s = line_one(mx);
        vector<float> di = d_i(mx, s);
        vector<float> dj = d_j(mx, s);
        v_point arg_max = maxing(di, dj, s);
        vector<vector<float>> resize_mx = modificator(mx, arg_max.s_point);
        mx.clear();
        float new_sum = re_mx(resize_mx);
        auto par = NGFC(sum, new_sum, arg_max);
        if (par.first)
        {
            v_point edg;
            edg.val = par.second;
            edg.s_point = arg_max.s_point;
            edges.push_back(edg);
        }
        else
        {
            v_point edg;
            edg.val = par.second;
            edg.s_point.absc.first = arg_max.s_point.absc.second;
            edg.s_point.absc.second = arg_max.s_point.absc.first;
            edges.push_back(edg);
        }
        s.clear();
        di.clear();
        dj.clear();
        return recurs(resize_mx, sum + new_sum);
    }
    else
    {
        for (int i = 1; i <= 2; i++)
            for (int j = 1; j <= 2; j++)
                if (mx[i][j] < FLT_MAX)
                {
                    v_point edg;
                    edg.val = sum;
                    edg.s_point.absc.first = mx[i][0];
                    edg.s_point.absc.second = mx[0][j];
                    edges.push_back(edg);
                }
        mx.clear();
        return edges.back().val;
    }

}

pair<bool, float> TSP::NGFC(float old_H, int new_H, v_point kl)
{
    float neg = old_H + kl.val;
    float pos = old_H + new_H;
    if (pos <= neg)
    {
        auto p = make_pair(true, pos);
        return p;
    }
    else
    {
        auto p = make_pair(false, neg);
        return p;
    }
}

float TSP::SumCol_n_Lines(const vector<v_point>& cols, const vector<v_point>& lines)
{
    float sum = 0;
    for (auto c : cols)
        sum += c.val;
    for (auto r : lines)
        sum += r.val;
    return sum;
}

float TSP::re_mx(vector<vector<float> >& mx)
{
    vector<v_point> min_cols = re_cols(mx);
    vector<v_point> min_lines = re_lines(mx);
    return SumCol_n_Lines(min_cols, min_lines);
}

vector<v_point> TSP::re_cols(vector<vector<float> >& mx)
{
    int v_size = mx.size();
    vector<v_point> cols_val;
    pair <int, int> min_pair;
    for (int i = 1; i < v_size; i++)
    {
        float min = FLT_MAX;
        for (int j = 1; j < v_size; j++)
            if (mx[i][j] < min)
            {
                min = mx[i][j];
                min_pair.first = i;
                min_pair.second = j;
            }
        v_point point;
        point.s_point.realc = min_pair;
        point.val = min;
        cols_val.push_back(point);
    }

    for (auto k : cols_val)
        for (int j = 1; j <= cols_val.size(); j++)
            mx[k.s_point.realc.first][j] -= k.val;
    return cols_val;
}

vector<v_point> TSP::re_lines(vector<vector<float> >& mx)
{
    int v_size = mx.size();
    vector<v_point> line_val;
    pair <int, int> min_pair;
    for (int j = 1; j < v_size; j++)
    {
        float  min = FLT_MAX;
        for (int i = 1; i < v_size; i++)
            if (mx[i][j] < min)
            {
                min = mx[i][j];
                min_pair.first = i;
                min_pair.second = j;
            }
        v_point point;
        point.s_point.realc = min_pair;
        point.val = min;
        line_val.push_back(point);
    }
    for (auto k : line_val)
        for (int i = 1; i <= line_val.size(); i++)
            mx[i][k.s_point.realc.second] -= k.val;
    return line_val;
}

vector<float> TSP::d_i(const vector<vector<float> >& mx, const vector<s_point>& s)
{
    int v_size = mx.size();
    vector<float> result;
    for (auto s_p : s)
    {
        float min = FLT_MAX;
        for (int j = 1; j < v_size; j++)
            if (mx[s_p.realc.first][j] < min && j != s_p.realc.second)
                min = mx[s_p.realc.first][j];
        result.push_back(min);
    }
    return result;
}
vector<float> TSP::d_j(const vector<vector<float> >& mx, const vector<s_point>& s)
{
    int v_size = mx.size();
    vector<float> result;
    for (auto s_p : s)
    {
        float min = FLT_MAX;
        for (int i = 1; i < v_size; i++)
            if (mx[i][s_p.realc.second] < min && i != s_p.realc.first)
                min = mx[i][s_p.realc.second];
        result.push_back(min);
    }
    return result;
}

vector<s_point> TSP::line_one(const vector<vector<float> >& mx)
{
    int v_size = mx.size();
    vector<s_point> first_line;
    for (int i = 1; i < v_size; i++)
        for (int j = 1; j < v_size; j++)
            if (mx[i][j] == 0)
            {
                s_point s_p;
                s_p.realc = make_pair(i, j);
                s_p.absc = make_pair(mx[i][0], mx[0][j]);
                first_line.push_back(s_p);
            }
    return first_line;
}

v_point TSP::maxing(const vector<float>& di, const vector<float>& dj, const vector<s_point>& s)
{
    v_point p;
    float max = -1;
    for (int i = 0; i < di.size(); i++)
    {
        float temp = di[i] + dj[i];
        if (temp > max)
        {
            max = temp;
            p.val = max;
            p.s_point.absc = s[i].absc;
            p.s_point.realc = s[i].realc;
        }
    }
    return p;
}

vector<vector<float>> TSP::modificator(const vector<vector<float> >& mx, s_point kl)
{
    vector<vector<float>> resize_mx;
    int size = mx.size();
    float a_first;
    float a_second;
    float first;
    float second;
    second = kl.realc.second;

    for (int i = 1; i < size; i++)
        if (mx[i][second] == FLT_MAX)
        {
            a_second = mx[i][0];
            break;
        }

    first = kl.realc.first;

    for (int j = 1; j < size; j++)
        if (mx[first][j] == FLT_MAX)
        {
            a_first = mx[0][j];
            break;
        }

    for (int i = 0; i < size; i++)
        if (mx[i][0] != kl.absc.first)
        {
            vector<float> resize_row;
            for (int j = 0; j < size; j++)
                if (mx[0][j] != kl.absc.second)
                    resize_row.push_back(mx[i][j]);
            resize_mx.push_back(resize_row);
        }

    size--;
    for (int i = 1; i < size; i++)
        if (resize_mx[i][0] == a_second)
        {
            first = i;
            break;
        }

    for (int j = 1; j < size; j++)
        if (resize_mx[0][j] == a_first)
        {
            second = j;
            break;
        }


    resize_mx[first][second] = FLT_MAX;
    return resize_mx;

}

void TSP::print_matrix(const vector<vector<float> >& mx)
{
    cout << endl;
    auto v_size = mx.size();
    for (auto i = 0; i < v_size; i++)
    {
        for (auto j = 0; j < v_size; j++)
            if (mx[i][j] == FLT_MAX)
                cout << "nf" << " ";
            else
                cout << mx[i][j] << " ";
        cout << endl;
    }

}

float TSP::get_res()
{
    return res;
}

vector<v_point> TSP::get_res_path()
{
    return edges;
}