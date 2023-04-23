#include <iostream>
#include <fstream>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename) {

    }
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }

    void Script::run() {
        string command;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open") {
                open();
                continue;
            }
            if (command == "blank") {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save") {
                save();
                continue;
            } 
            if (command == "invert"){
                invert();
                continue;
            }
            if(command == "to_gray_scale"){
                to_gray_scale();
                continue;
            }

            if(command == "v_mirror"){
                v_mirror();
                continue;
            }
            if(command == "h_mirror"){
                h_mirror();
                continue;
            }
            if (command == "replace"){
                int r1,g1,b1,r2,g2,b2;
                input >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
                replace(r1,g1,b1,r2,g2,b2);
                continue;
            }
            if ( command == "fill"){
                int x,y,w,h,r,g,b;
                input >> x >> y >> w >> h >> r >> g >> b;
                fill(x,y,w,h,r,g,b);
            }
            if ( command == "add"){
                string filename;
                int r,g,b,x,y;
                input >> filename >> r >> g >> b >> x >> y;;
                add(filename,r,g,b,x,y);
            }

        }
    }
    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }
    void Script::blank() {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }
    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }
    void Script::invert(){
        int width = image->width();
        int height = image->height();
        for ( int x = 0 ; x < width ; x++){
            for ( int y = 0 ; y < height ; y++){
                Color pixel = image->at(x,y);
                pixel.red() = 255 - pixel.red() ;
                pixel.green() = 255-pixel.green() ;
                pixel.blue() = 255-pixel.blue() ;
                image->at(x,y) = pixel;
            }
        }
    }
    void Script :: to_gray_scale(){
        int width = image->width();
        int height = image->height();
        for ( int x = 0 ; x < width ; x++){
            for ( int y = 0 ; y < height ; y++){
                Color pixel = image->at(x,y);
                unsigned int r = pixel.red();
                unsigned int g = pixel.green();
                unsigned int b = pixel.blue();
                pixel.red() = (r+g+b)/3;
                pixel.green() = (r+g+b)/3;
                pixel.blue() = (r+g+b)/3;
                image->at(x,y) = pixel;


            }
        }
    }
    void Script :: v_mirror(){
        int width = image->width();
        int height = image->height();
        for( int x = 0; x<width;x++){
            for(int y= 0; y < height/2;y++){
                Color pixel1 = image->at(x,y);
                Color pixel2 = image->at(x,height -1 -y);
                image->at(x,y) = pixel2;
                image->at(x,height -1 -y) = pixel1;
            }
        }
    }
    void Script :: h_mirror(){
        int width = image->width();
        int height = image->height();
        for( int x = 0; x<width/2;x++){
            for(int y= 0; y < height;y++){
                Color pixel1 = image->at(x,y);
                Color pixel2 = image->at(width -1 -x,y);
                image->at(x,y) = pixel2;
                image->at(width -1- x,y) = pixel1;
            }
        }
    }
    void Script::replace( unsigned char r1,unsigned char g1,unsigned char b1,unsigned char r2,unsigned char g2,unsigned char b2){
        Color pixel_replace = {r2,g2,b2};
        int width = image->width();
        int height = image->height();
        for ( int x = 0 ; x < width ; x++){
            for ( int y = 0 ; y < height ; y++){
                Color pixel = image->at(x,y);
                if ( (pixel.red() == r1) && (pixel.green() == g1) && (pixel.blue() == b1)){
                    image->at(x,y) = pixel_replace;
                }
            }
        }
    }
    void Script::fill(int x , int y , int w , int h , unsigned char r , unsigned char g , unsigned char b){
        Color fill_with = {r,g,b};
        for (int x_ = x ; x_ < x + w ; x_++){
            for ( int y_ = y ; y_ < y + h ; y_++){
                image->at(x_,y_) = fill_with;
            }
        }
    }
    void Script::add(string filename, unsigned char r , unsigned char g , unsigned char b , int x , int y){
        int i = 0 , j = 0; // coordenadas da nova imagem para dar "copypaste"
        Image* image_fill = loadFromPNG(filename);
        int width = image_fill->width();
        int height = image_fill->height();
        for (int x_ = x ; x_ < width + x ; x_++){
            for (int y_ = y ; y_ < height + y ; y_++){
                Color pixel = image_fill->at(i,j);
                if (pixel.red() != r || pixel.green() != g || pixel.blue() != b){
                    image->at(x_,y_) = pixel;
                }
                j++;
            }
            i++;
            j = 0; // dar reset na height da imagem a ser "printed"
        }
        delete image_fill;
    }
}

