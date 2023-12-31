#ifndef SVG_MODUL_H_INCLUDED
#define SVG_MODUL_H_INCLUDED
#include <vector>
#include <iostream>

using namespace std;
bool check_color(string color);
bool color_flag(string color);
double find_max_count(const vector<size_t> &bins);
void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height,string stroke = "black", string fill = "black" );
void heading(double width, double height, int count_bins, double &x,double &y);
void show_histogram_svg(const vector<size_t>& bins,const vector<string>& colors);



#endif // SVG_MODUL_H_INCLUDED
