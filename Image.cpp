#include "Image.hpp"

namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
    width_ = w;
    height_ = h;
    matrix = new Color*[width_];
    for ( int i = 0; i < width_ ; i++){
      matrix[i] = new Color[height_];
    }
    for ( int i = 0 ; i < width_ ; i++){
      for ( int j = 0; j < height_ ; j++){
        matrix[i][j] = fill;
      }
    }
  }
  Image::~Image()
  {
    for ( int i = 0 ; i < width_ ; i++){
      delete [] matrix[i];
    }
    delete [] matrix;
  }
  int Image::width() const
  {
    return width_;
  }
  int Image::height() const
  {
    return height_;
  }

  Color& Image::at(int x, int y)
  {
    
    return matrix[x][y];
  }

  const Color& Image::at(int x, int y) const
  {
    return matrix[x][y];
  }
}
