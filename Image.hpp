#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"

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
  };
}
#endif
