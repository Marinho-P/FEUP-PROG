#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"
#include "Image.hpp"

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
                continue;
            }
            if ( command == "add"){
                string filename;
                int r,g,b,x,y;
                input >> filename >> r >> g >> b >> x >> y;;
                add(filename,r,g,b,x,y);
                continue;
            }
            if(command == "crop"){
                int x,y,w,h;
                input >> x >> y >> w >> h;
                crop(x,y,w,h);
                continue;
            }
            if ( command == "rotate_left"){
                rotate_left();
                continue;
            }
            if ( command == "rotate_right"){
                rotate_right();
                continue;
            }
            if ( command == "xpm2_open"){
                xpm2_open();
                continue;
            
            }
            if(command == "median_filter"){
                int ws;
                input >> ws;
                median_filter(ws);
                continue;
            }
            if( command == "xpm2_save"){
                xpm2_save();
                continue;
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
    void Script::xpm2_open(){
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromXPM2(filename);
    }
    void Script :: xpm2_save(){
        string filename;
        input >> filename;
        saveToXPM2(filename,image);
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
        image->invert();
    }
    void Script::to_gray_scale(){
        image->to_gray_scale();
    }
    void Script :: v_mirror(){
        image->v_mirror();
    }
    void Script::h_mirror(){
        image->h_mirror();
    }
    void Script::replace( unsigned char r1,unsigned char g1,unsigned char b1,unsigned char r2,unsigned char g2,unsigned char b2){
        image->replace(r1,g1,b1,r2,g2,b2);
    }
    void Script::fill(int x , int y , int w , int h , unsigned char r , unsigned char g , unsigned char b){
        image->fill(x,y,w,h,r,g,b);
    }
    void Script::add(string filename, unsigned char r , unsigned char g , unsigned char b , int x , int y){
        image-> add(filename,r,g,b,x,y);
    }
    void Script::crop(int x, int y, int w, int h) {
        image->crop(x,y,w,h);
    }
    void Script::rotate_left(){
       image->rotate_left();
    }
    void Script::rotate_right(){
        image->rotate_right();
    }
   void Script:: median_filter(int ws){
        image->median_filter(ws);
    }

}

