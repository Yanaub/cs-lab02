#include"svg_modul.h"

bool check_color(string color){
    if (color=="red"){
        return false;
    }
    else{
        return true;
    }
}

bool color_flag(string color){
    if ((color[0]=='#' or color.find(' ')==color.npos) ){
                return true;
            }
            else
                return false;
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
string s;
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
void svg_rect(double x, double y, double width, double height,string stroke, string fill ){

    cout<<"<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />";

}
void heading(double width, double height, int count_bins, double &x,double &y){
    x=width/2;
    y=(height/(count_bins+1))-((height/(count_bins+1))/2);
    cout << "<text x='" << x << "' text-anchor='middle' y='"<<y<<"'>"<<"Histogram"<<"</text>";

}

void show_histogram_svg(const vector<size_t>& bins,const vector<string>& colors) {
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
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
    double top = 0;
    double x,y;
    heading(IMAGE_WIDTH, IMAGE_HEIGHT, bins.size(),x,y);
    top += (IMAGE_HEIGHT/(bins.size()+1));
    double max_count=find_max_count(bins);
    size_t width ;

    for (size_t i=0;i<bins.size();i++) {

            const double bin_width = BLOCK_WIDTH * bins[i];
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bins[i]));
            if(max_count>MAX_ASTERISK){
                width = MAX_ASTERISK * (static_cast<double>(bins[i]) / max_count);
                svg_rect(TEXT_WIDTH, top, width, BIN_HEIGHT, STROKE,colors[i]);}
            else{
                svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, STROKE,colors[i]);}
            top += BIN_HEIGHT;
}
svg_end();

}
