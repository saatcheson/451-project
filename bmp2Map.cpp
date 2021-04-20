#include "bmp2Map.h"


bmpMap::bmpMap(std::string& filename)
{
    bitmap_image image(filename);
    img = image;
    height = image.height();
    width = image.width();
    
    //Create map
    for (std::size_t y = 0; y < height; ++y) {
        std::vector<int> newRow;
        map.push_back(newRow);

        for (std::size_t x = 0; x < width; ++x) {
            rgb_t color;
            img.get_pixel(x, y, color);
            
            //if the color is darker than medium grey then its a zero
            if ((color.red < 128) && (color.green < 128) && (color.blue < 128)) {
                map[y].push_back(0);
            } else {
                map[y].push_back(1);
            }
        }
    }
}

bmpMap::bmpMap(const bmpMap& rhs)
:img(rhs.img)
,width(rhs.width)
,height(rhs.height)
{
    //Create map
    for (std::size_t y = 0; y < height; ++y) {
        std::vector<int> newRow;
        map.push_back(newRow);
        map[y] = rhs.map[y];
    }
}

// Assignment operator
bmpMap& bmpMap::operator=(const bmpMap& rhs)
{
    // 1. First check that we're not self-assigning
    if (&rhs != this)
    {
        this->img = rhs.img;
        this->width = rhs.width;
        this->height = rhs.height;
        //Create map
        for (std::size_t y = 0; y < height; ++y) {
            std::vector<int> newRow;
            this->map.push_back(newRow);
            this->map[y] = rhs.map[y];
        }
    }
    return *this;
}

bmpMap::~bmpMap() {}

void bmpMap::printMap() {
    for (std::size_t y = 0; y < height; ++y) {
        for (std::size_t x = 0; x < width; ++x) {
            printf("%d ", map[y][x]);
        }
        printf("\n");
    }
}

bool bmpMap::checkFree(int x, int y) {
    return map[y][x] == 1;
}

unsigned int bmpMap::get_height() {
    return height;
}

unsigned int bmpMap::get_width() {
    return width;
}