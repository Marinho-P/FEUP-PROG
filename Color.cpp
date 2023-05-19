#include "Color.hpp"

namespace prog {
    Color::Color() {
        red_ = 0;
        green_ = 0;
        blue_ = 0;
    }
    Color::Color(const Color& other) {
        red_= other.red();
        green_ = other.green();
        blue_ = other.blue();
    }
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) {
        red_ = red;
        blue_ = blue;
        green_ = green;
    }
    rgb_value Color::red() const {
        return red_;
    }
    rgb_value Color::green() const {
        return green_;
    }
    rgb_value Color::blue() const {
        return blue_;
    } 

    rgb_value& Color::red()  {
        return red_;
    }
    rgb_value& Color::green()  {
      return green_;
    }
    rgb_value& Color::blue()  {
      return blue_;
    }
    bool Color :: operator==(const Color& Color2){
        return (red_==Color2.red()) && (green_==Color2.green()) && (blue_==Color2.blue());
    }
    void Color :: invert(){
        this->red_ = 255 - red_;
        this->blue_ = 255 - blue_;
        this->green_ = 255 - green_;
    }
    void Color :: to_gray_scale(){
        rgb_value average = (red_+blue_+ green_)/3;
        red_ = average;
        blue_ = average;
        green_ = average;
    }
    void Color:: replace(unsigned char r1,unsigned char g1,unsigned char b1,unsigned char r2,unsigned char g2,unsigned char b2){
        Color pixel_to_change = {r1,g1,b1};
        Color pixel_replace = {r2,g2,b2};
        if(pixel_to_change == *this){
            *this = pixel_replace; 
        }
    }
    void Color:: fill(unsigned char r,unsigned char g,unsigned char b){
        red_ = r;
        blue_ = b;
        green_ = g;
    }
    void Color:: add(rgb_value* &p, unsigned char r,unsigned char g,unsigned char b){
        Color neutral_pixel = {r,g,b};
        Color pixel_to_add = {p[0],p[1],p[2]};
            if(!( pixel_to_add == neutral_pixel)){
            *this = pixel_to_add;
            } 
    }
}
