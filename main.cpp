#include "histogram.h"
#include"svg_modul.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <istream>

using namespace std;





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

Input read_input(istream& in,bool prompt) {
    Input data;
    if(prompt==true)
    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;
    if(prompt==true)
    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);
    if(prompt==true)
    cerr << "Enter bin count: ";
    in >> data.bin_count;
    if(prompt==true)
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





int main()
{
    const auto input = read_input(cin,true);


    removing_repetitions(input);
    double min, max;
    find_minmax(input.numbers, min, max);

    const auto bins = make_histogram(input);
    show_histogram_svg(bins,input.colors );
}
