#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"
#include <string>
#include <fstream>
#include <iostream>

namespace prog
{
  class Image
  {
  private:
    Color **matrix; // criar um double pointer para a matrix 
    int width_ , height_;
  public:
    // constructor
    Image(int w, int h, const Color &fill = {255, 255, 255});
    // deconstructor
    ~Image();
    // getters
    int width() const;
    int height() const;
    // pixel acessors / mutator
    Color &at(int x, int y);
    const Color &at(int x, int y) const;
    void invert();
    void to_gray_scale();
    void v_mirror();
    void h_mirror();
    void replace(unsigned char r1,unsigned char g1,unsigned char b1,unsigned char r2,unsigned char g2,unsigned char b2);
    void fill(int x , int y , int w , int h , unsigned char r , unsigned char g , unsigned char b);
    void crop(int x, int y, int w, int h);
    void rotate_left();
    void rotate_right();
    void median_filter(int ws);
  };
}
#endif
