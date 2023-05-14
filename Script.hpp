#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__
#include "Image.hpp"

namespace prog
{
  class Script
  {
  public: 
    Script(const std::string &filename);
    ~Script();
    void run();
  private:
    // Current image.
    Image *image;
    // Input stream for reading script commands.
    std::ifstream input;
  private:
    // Private functions
    void clear_image_if_any();
    void open();
    void blank();
    void save();
    void invert();
    void to_gray_scale();
    void v_mirror();
    void h_mirror();
    void replace(unsigned char r1,unsigned char g1,unsigned char b1,unsigned char r2,unsigned char g2,unsigned char b2);
    void fill(int x , int y , int w , int h , unsigned char r , unsigned char g , unsigned char b);
    void add(std::string filename, unsigned char r , unsigned char g , unsigned char b , int x , int y);
    void crop(int x,int y,int w,int h);
    void rotate_left();
    void rotate_right();
    void median_filter(int ws);
    void xpm2_open();
    void xpm2_save();
  };
}
#endif
