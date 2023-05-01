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
  void Image::invert(){
        for ( int x = 0 ; x < width_ ; x++){
            for ( int y = 0 ; y < height_ ; y++){
                Color pixel = matrix[x][y];
                Color inverted_pixel = Color(255- pixel.red(), 255 -pixel.green(),255 - pixel.blue());
                matrix[x][y] = inverted_pixel;
            }
      }
  }
  void Image::to_gray_scale(){
      for ( int x = 0 ; x < width_ ; x++){
            for ( int y = 0 ; y < height_ ; y++){
                Color pixel = matrix[x][y];
                unsigned char to_gray_scale = (pixel.red()+pixel.green()+pixel.blue())/3;
                Color pixel_to_gray_scale = Color(to_gray_scale,to_gray_scale,to_gray_scale);
                matrix[x][y] = pixel_to_gray_scale;
          }
      }
  }
  void Image::v_mirror(){
    for ( int x = 0; x<width_;x++){
      for ( int y = 0; y < height_/2;y++){
        Color pixel1 = matrix[x][y];
        Color pixel2 = matrix[x][height_-1-y];
        matrix[x][y] = pixel2;
        matrix[x][height_-1-y] = pixel1;
      }
    }
  }
  void Image::h_mirror(){
    for ( int x = 0; x < width_/2 ; x++){
      for ( int y = 0;y < height_ ; y++){
        Color pixel1 = matrix[x][y];
        Color pixel2 = matrix[width_-1-x][y];
        matrix[x][y] = pixel2;
        matrix[width_-1-x][y] = pixel1;
      }
    } 
  }
  void Image::replace(unsigned char r1,unsigned char g1,unsigned char b1,unsigned char r2,unsigned char g2,unsigned char b2){
    Color pixel_to_change = {r1,g1,b1};
    Color pixel_replace = {r2,g2,b2};
    for(int x = 0; x <width_;x++){
      for ( int y = 0; y < height_;y++){
        Color pixel = matrix[x][y];
        if (pixel == pixel_to_change){
          matrix[x][y] = pixel_replace;
        }
      }
    }
  }
  void Image::fill(int x , int y , int w , int h , unsigned char r , unsigned char g , unsigned char b){
    Color fill_with = {r,g,b};
    for (int x_pixel = x ; x_pixel < x + w ; x_pixel++){
            for ( int y_pixel = y ; y_pixel < y + h ; y_pixel++){
                matrix [x_pixel][y_pixel] = fill_with;
            }
        }
  }
  void Image::crop(int x, int y, int w, int h){
    Color **temp_matrix = new Color*[w];
    for ( int i = 0; i < w ; i++){
      temp_matrix[i] = new Color[h];
    }
    for ( int x_pixel = 0 ; x_pixel < w ; x_pixel++){
      for ( int y_pixel = 0; y_pixel < h ; y_pixel++){
        temp_matrix[x_pixel][y_pixel] = matrix[x+x_pixel][y+y_pixel];
      }
    }
    // Release the memory from the original matrix
    for ( int i = 0 ; i < width_ ; i++){
      delete [] matrix[i];
    }
    delete [] matrix;
    // updated size
    width_ = w;
    height_ = h;
    // Copy the values of the temp_matrix to matrix
    matrix = temp_matrix;
}
  void Image::rotate_left(){
    Color **temp_matrix = new Color*[height_];
    for ( int i = 0; i < height_ ; i++){
      temp_matrix[i] = new Color[width_];
    }
    for ( int x = 0; x < height_ ; x++){
        for (int y = 0 ;  y < width_; y++){
            temp_matrix[x][y] = matrix[width_ - y -1][x];
        }
  }
  // Release the memory from the original matrix
    for ( int i = 0 ; i < width_ ; i++){
      delete [] matrix[i];
    }
    delete [] matrix;
    // updated size
    int update_width = height_;
    int update_height = width_;
    width_ = update_width;
    height_ = update_height;
    // Copy the values of the temp_matrix to matrix
    matrix = temp_matrix;
  }
  void Image::rotate_right(){
    Color **temp_matrix = new Color*[height_];
    for ( int i = 0; i < height_ ; i++){
      temp_matrix[i] = new Color[width_];
    }
    for ( int x = 0; x < height_ ; x++){
        for (int y = 0 ;  y < width_; y++){
            temp_matrix[x][y] = matrix[y][height_ -x -1];
        }
    }
    // Release the memory from the original matrix
    for ( int i = 0 ; i < width_ ; i++){
      delete [] matrix[i];
    }
    delete [] matrix;
    // updated size
    int update_width = height_;
    int update_height = width_;
    width_ = update_width;
    height_ = update_height;
    // Copy the values of the temp_matrix to matrix
    matrix = temp_matrix;
  }

}