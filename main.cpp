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

void find_minmax(vector<double>&numbers, double &min, double &max) {
    min = numbers[0];
    for (double x : numbers) {
       if (x < min) {
           min = x;
       }
       else if (x > max) {
           max = x;
       }
  }

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

double find_max_count(const vector<size_t> &bins){
  double max_count=0;
  for (int i=0;i<bins.size();i++){
        if(max_count<bins[i]){
            max_count=bins[i];
        }
  }
  return max_count;
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


void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void svg_end() {
    cout << "</svg>\n";
}
void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='"<<baseline<<"'>"<<text<<"</text>";
}
void svg_rect(double x, double y, double width, double height,string stroke = "black", string fill = "black"){

    cout<<"<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />";
}
void show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const auto STROKE="blue";
    const auto FILL="#B0C4DE";
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double max_count=find_max_count(bins);
    size_t width ;
    double top = 0;
    for (size_t bin : bins) {

            const double bin_width = BLOCK_WIDTH * bin;
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            if(max_count>MAX_ASTERISK){
                width = MAX_ASTERISK * (static_cast<double>(bin) / max_count);
                svg_rect(TEXT_WIDTH, top, width, BIN_HEIGHT, STROKE,FILL);}
            else{
                svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, STROKE,FILL);}
            top += BIN_HEIGHT;
}
svg_end();

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

    //removing_repetitions(numbers);
    double min, max;
    find_minmax(numbers, min, max);

    const auto bins = make_histogram(numbers, bin_count);
    show_histogram_svg(bins);
}
