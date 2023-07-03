#include "histogram.h"
#include"svg_modul.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <istream>

using namespace std;

struct Input {
vector<double> numbers;
size_t bin_count;
vector<string>colors;
};

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

vector<double>input_numbers(istream& in,size_t &number_count) {
    vector<double> result(number_count);
    for (size_t i = 0; i < number_count; i++) {
            in >> result[i];
    }
    return result;
}

vector<string>input_colors(istream& in,size_t &bin_count) {
    vector<string> result(bin_count);
    string color;
    for (size_t i = 0; i < bin_count; i++) {
            in >> color;
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

Input read_input(istream& in) {
    Input data;
    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;
    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);
    cerr << "Enter bin count: ";
    in >> data.bin_count;
    cerr << "Enter colors: ";
    data.colors = input_colors(in,data.bin_count);
    return data;
}






void removing_repetitions(Input input){
    for(int i=0;i<input.numbers.size();i++){
        for(int j=i+1;j<input.numbers.size();j++){
            if(input.numbers[i]==input.numbers[j]){
                input.numbers.erase(input.numbers.begin() + j);
                j--;
            }
        }
    }
}

vector<size_t> make_histogram(Input input){
    double min, max;
    find_minmax(input.numbers, min, max);
    vector<size_t> bins(input.bin_count);
    double bin_size = (max - min) / input.bin_count;
    for (size_t i = 0; i < input.numbers.size(); i++) {
        bool found = false;
        for (size_t j = 0; (j < input.bin_count - 1) && !found; j++) {
           auto lo = min + j * bin_size;
           auto hi = min + (j + 1) * bin_size;
           if ((lo <= input.numbers[i]) && (input.numbers[i] < hi)) {
                bins[j]++;
                found = true;
           }
        }
        if (!found) {
           bins[input.bin_count - 1]++;
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
    const auto input = read_input(cin);


    removing_repetitions(input);
    double min, max;
    find_minmax(input.numbers, min, max);

    const auto bins = make_histogram(input);
    show_histogram_svg(bins,input.colors );
}
