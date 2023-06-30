#include "histogram.h"
#include"svg_modul.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

vector<double>input_numbers(size_t &number_count) {
    vector<double> result(number_count);
    for (size_t i = 0; i < number_count; i++) {
            cin >> result[i];
    }
    return result;
}

vector<string>input_colors(size_t &bin_count) {
    vector<string> result(bin_count);
    string color;
    for (size_t i = 0; i < bin_count; i++) {
            cin >> color;
            bool flag=check_color(color);
            if ((color[0]=='#' or color.find(' ')==color.npos) and flag==true){
                result[i]=color;
            }
            else{
                cout<<"input error";
                i--;
            }
    }
    return result;
}



void removing_repetitions(vector<double> &v){
    for(int i=0;i<v.size();i++){
        for(int j=i+1;j<v.size();j++){
            if(v[i]==v[j]){
                v.erase(v.begin() + j);
                j--;
            }
        }
    }
}

vector<size_t> make_histogram(vector<double>&numbers,size_t bin_count){
    double min, max;
    find_minmax(numbers, min, max);
    vector<size_t> bins(bin_count);
    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < numbers.size(); i++) {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
           auto lo = min + j * bin_size;
           auto hi = min + (j + 1) * bin_size;
           if ((lo <= numbers[i]) && (numbers[i] < hi)) {
                bins[j]++;
                found = true;
           }
        }
        if (!found) {
           bins[bin_count - 1]++;
        }
   }
   return bins;
}


void show_histogram_text(const vector<size_t> &bins){
  double max_count=find_max_count(bins);
  size_t height ;
  for(int i=0;i<bins.size();i++){
        if(bins[i]<100){
            cout<<" ";
        }
        if(bins[i]<10){
            cout<<" ";}
        cout <<bins[i]<<"|";
        if(max_count>MAX_ASTERISK){
                height = MAX_ASTERISK * (static_cast<double>(bins[i]) / max_count);
                for(size_t j=0;j<height;j++){
                    cout<<"*";}}
        else{
            for(int j=0;j<bins[i];j++){
                    cout<<"*";}}
        cout<<endl;
    }
}

int main()
{
    size_t number_count, bin_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    cerr << "Enter numbers: ";
    auto numbers = input_numbers(number_count);
    cerr << "Enter bin count: ";
    cin >> bin_count;
    cerr << "Enter colors: ";
    const auto colors = input_colors(bin_count);


    //removing_repetitions(numbers);
    double min, max;
    find_minmax(numbers, min, max);

    const auto bins = make_histogram(numbers, bin_count);
    show_histogram_svg(bins,colors);
}
