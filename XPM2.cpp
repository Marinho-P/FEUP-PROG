#include "XPM2.hpp"

namespace prog {
    Image* loadFromXPM2(const std::string& file) {
        // extract the first line so as to ignore it 
        std::string line; 
        std::ifstream input(file);
        getline(input,line);
        // read the second line
        getline(input,line);
        std::istringstream header(line);
        int width , height , number_colors , c;
        header >> width >> height >> number_colors >> c;
        std::unordered_map<char,Color> char_color;
        char key , burner_char;
        unsigned char r , g , b;
        std::string value; // char for each Color
        for ( int i = 0 ; i < number_colors; i++){
            getline(input,line);
            std::istringstream stream(line);
            stream >> key >> burner_char >> value; // burner_char é o c
            r =  std::stoi(value.substr(1,2),nullptr,16); // stoi(str,posição,base) passa parte da string de hexa para decimal na base 16
            g = std::stoi(value.substr(3,2),nullptr,16);
            b = std::stoi(value.substr(5,2),nullptr,16);
            Color pixel = {r,g,b};
            char_color[key] = pixel;
        }
        Image* image = new Image(width,height);
        for ( int y = 0; y < height ; y++){
            getline(input,line);
            std::istringstream stream(line);
            for ( int x = 0 ; x < width ; x++){
                image->at(x,y) = char_color[stream.get()]; // stream.get() lê um char de cada vez
            }
        }
        return image;
    }

   void saveToXPM2(const std::string& file, const Image* image) {
        std:: ofstream output(file); // stream for header and values,later stitched with colors and bitmap to become complete
        std:: stringstream colors; // stream for colors
        std:: stringstream bitmap; // stream for bitmap
        output << "! XPM2" << std::endl; // header
        int width = image->width();
        int height = image->height();
        std:: vector<Color> char_colors;
        for(int y = 0; y< height;y++){
            for(int x = 0;x < width ;x++ ){
                Color pixel = image->at(x,y);
                if(std::find(char_colors.begin(),char_colors.end(),pixel) != char_colors.end()){ // if in vector
                    bitmap << (char) (std::distance(char_colors.begin(),std::find(char_colors.begin(),char_colors.end(),pixel)) + 33); // add char to bitmap based on index of vector
                }
                else{
                    char_colors.push_back(pixel); // add new color to vector
                    colors << (char)(char_colors.size() - 1 + 33)  << " c #" << std::setw(2) << std::setfill('0')<< std:: hex << (int)pixel.red() << std:: hex <<std::setw(2) << std::setfill('0')<< (int)pixel.green() << std:: hex <<std::setw(2) << std::setfill('0')<< (int)pixel.blue() << std::endl; //color
                    bitmap << (char)(char_colors.size() - 1 + 33); // add char to bitmap, guaranteed to be last in vector
                }
            }
            bitmap << std::endl;
        }
        output << width << " " << height << " " << char_colors.size() << " 1" << std::endl; //values
        output << colors.str();//stitch colors to output
        output << bitmap.str();// stitch bitmap to output
        output << std:: flush;
        
    }
}
