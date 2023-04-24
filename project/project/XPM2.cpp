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
        return;
    }
}
