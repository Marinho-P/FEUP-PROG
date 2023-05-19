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
                pixel.invert();
                matrix[x][y] = pixel;
            }
      }
  }
  void Image::to_gray_scale(){
      for ( int x = 0 ; x < width_ ; x++){
            for ( int y = 0 ; y < height_ ; y++){
                Color pixel = matrix[x][y];
                pixel.to_gray_scale();
                matrix[x][y] = pixel;
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
    for(int x = 0; x <width_;x++){
      for ( int y = 0; y < height_;y++){
         matrix[x][y].replace(r1,g1,b1,r2,g2,b2);
      }
    }
  }
  void Image::fill(int x , int y , int w , int h , unsigned char r , unsigned char g , unsigned char b){
    for (int x_pixel = x ; x_pixel < x + w ; x_pixel++){
            for ( int y_pixel = y ; y_pixel < y + h ; y_pixel++){
                matrix [x_pixel][y_pixel].fill(r,g,b);
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
    width_ = w;
    height_ = h;
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
    matrix = temp_matrix;
  }
  void Image :: add(std::string filename, unsigned char r , unsigned char g , unsigned char b , int x , int y){
    int w, h, dummy;
    rgb_value *buffer = stbi_load(filename.c_str(), &w, &h, &dummy, 3);
    rgb_value* p = buffer;
    for (int new_image_y = y; new_image_y < y+h; new_image_y++) {
        for (int new_image_x = x; new_image_x < x+w; new_image_x++) {
            matrix[new_image_x][new_image_y].add(p,r,g,b);
            p += 3;
        }
    }
    stbi_image_free(buffer);
  }
  void Image :: median_filter(int ws){
        rgb_value* redArray = new rgb_value[ws*ws]; 
        rgb_value* greenArray = new rgb_value[ws*ws];
        rgb_value* blueArray = new rgb_value[ws*ws];
        //create new matrix
        Color **filtered = new Color*[width_];
        for ( int i = 0; i < width_ ; i++){
          filtered[i] = new Color[height_];
        }
        
        for(int x = 0; x < width_; x++ ){
            for( int y = 0; y < height_; y++){ // iterate over the pixels in the image
            int i = 0;
                for( int nx = x - ws/2; nx <= x+ ws/2;nx++){
                    for(int ny = y -ws/2;ny <= y + ws/2; ny++){ // iterate over the adjacent pixels
                        if((nx>= 0) && (nx< width_) && (ny>= 0) && (ny<height_)){// test if in bounds
                            redArray[i] = matrix[nx][ny].red();
                            greenArray[i] = matrix[nx][ny].green();
                            blueArray[i] = matrix[nx][ny].blue();
                            i++;
              
                        }
                        
                    }
                } // i = number of elements in each array
                std::sort(redArray,redArray + i ); 
                std::sort(greenArray,greenArray + i );
                std::sort(blueArray,blueArray + i );
                for( int k = 0; k< i;k++){
                }
                if( i % 2 == 0){ // median
                    filtered[x][y].red() = (redArray[i/2] + redArray[(i/2)-1])/2.0;
                    filtered[x][y].green() = (greenArray[(i/2)] + greenArray[(i/2)-1])/2;
                    filtered[x][y].blue() = (blueArray[(i/2)] + blueArray[(i/2)-1])/2;
                }
                else{

                    filtered[x][y].red() = redArray[(i-1)/2];
                    filtered[x][y].green() = greenArray[(i-1)/2];
                    filtered[x][y].blue() = blueArray[(i-1)/2];
                }
                        

            }
        }
        // Release the memory from the original matrix
        for ( int i = 0 ; i < width_ ; i++){
          delete [] matrix[i];
        }
        delete [] matrix;
        
        delete[]redArray;
        delete[] blueArray;
        delete[] greenArray;
        matrix = filtered;
    }
}
