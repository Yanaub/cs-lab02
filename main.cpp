#include "histogram.h"
#include"svg_modul.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <istream>
#include <curl/curl.h>
#include <sstream>
#include <string>
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






void removing_repetitions(Input &input){
    for(int i=0;i<input.numbers.size();i++){
        for(int j=i+1;j<input.numbers.size();j++){
            if(input.numbers[i]==input.numbers[j]){
                input.numbers.erase(input.numbers.begin() + j);
                j--;
            }
        }
    }

}
size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    size_t data_size=item_size*item_count;

    buffer->write(reinterpret_cast<const char*>(items), data_size);

return data_size;
}

Input download(const string& address) {
stringstream buffer;

CURL* curl = curl_easy_init();
double connect = 0;
            if(curl) {

                    CURLcode res;

            curl_easy_setopt(curl, CURLOPT_URL, address.c_str());

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                cerr<<curl_easy_strerror(res);
                res = curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME, &connect);
                cerr << connect << "\n";
                exit(1);
        }




            curl_easy_cleanup(curl);}

            return read_input(buffer, false);
}




int main(int argc, char* argv[]) {

    Input input;
    if (argc > 1) {
            input = download(argv[1]);


    } else {
        input = read_input(cin, true);

}





    removing_repetitions(input);

        double min, max;
    find_minmax(input.numbers, min, max);

    const auto bins = make_histogram(input);
    show_histogram_svg(bins,input.colors );
}
