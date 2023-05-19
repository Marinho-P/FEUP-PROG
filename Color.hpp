#ifndef __prog_Color_hpp__
#define __prog_Color_hpp__

namespace prog
{
  typedef unsigned char rgb_value;
  class Color
  {
    private:
      rgb_value red_ , green_ , blue_; 
    public:
      Color(); 
      Color(const Color& c); 
      Color(rgb_value r, rgb_value g, rgb_value b);
      rgb_value red() const;
      rgb_value blue() const;
      rgb_value green() const;
      rgb_value& green();
      rgb_value& red();
      rgb_value& blue();
      bool operator==(const Color& Color2);
      void invert();
      void to_gray_scale();
      void replace( unsigned char r1,unsigned char g1,unsigned char b1,unsigned char r2,unsigned char g2,unsigned char b2);
      void fill(unsigned char r,unsigned char g,unsigned char b);
      void add(rgb_value* &p, unsigned char r,unsigned char g,unsigned char b);
  };

}
#endif
