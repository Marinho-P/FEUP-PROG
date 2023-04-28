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
}
