#include <iostream>
#include <fstream>
#include <vector>

#pragma pack(1)

struct FileHeader
{
    char type[2];
    long size;
    short reserved1;
    short reserved2;
    long offset_bits;
};

struct InfoHeader
{
    long size;
    long width;
    long height;
    short planes;
    short bit_count;
    long compression;
    long size_image;
    long x_pels_per_meter;
    long y_pels_per_meter;
    long color_used;
    long colors_important;
};

struct Color
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};



int main()
{
    char ipath[] = "C:\\Users\\student\\Desktop\\boss.bmp";
    std::ifstream ifstream(ipath);

    FileHeader file_header;
    ifstream.read((char*)&file_header, sizeof(FileHeader));

    InfoHeader info_header;
    ifstream.read((char*)&info_header, sizeof(InfoHeader));

    unsigned char** initial_color_buffer = new unsigned char*[info_header.height];

    for (long line = 0; line < info_header.height; line++)
    {
        initial_color_buffer[line] = new unsigned char[info_header.width * 3];
        ifstream.read((char*)initial_color_buffer[line], info_header.width * 3);
    }

    Color** initial_colors = new Color* [info_header.height];

    for (long y = 0; y < info_header.height; y++)
    {
        initial_colors[y] = new Color[info_header.width];
        for (long x = 0; x < info_header.width - 3; x++)
        {
            Color* color = new Color
            {
                initial_color_buffer[y][x * 3],
                initial_color_buffer[y][x * 3 + 1],
                initial_color_buffer[y][x * 3 + 2]
            };
            initial_colors[y][x] = *color;
        }
    }

    Color** blurred_colors = new Color* [info_header.height];

    for (long y = 0; y < info_header.height; y++)
    {
        blurred_colors[y] = new Color[info_header.width];
        for (long x = 0; x < info_header.width; x++)
        {
            std::vector<Color*> colors;
            colors.push_back(&initial_colors[y][x]);
            if (x > 1) colors.push_back(&initial_colors[y][x - 1]);
            if (x < info_header.width - 1) colors.push_back(&initial_colors[y][x + 1]);
            if (y > 1) colors.push_back(&initial_colors[y - 1][x]);
            if (y < info_header.height - 1) colors.push_back(&initial_colors[y + 1][x]);

            Color* blurred_color = new Color { 0, 0, 0 };

            for (Color* color : colors)
            {
                blurred_color->blue += color->blue / colors.size();
                blurred_color->green += color->green / colors.size();
                blurred_color->red += color->red / colors.size();
            }

            blurred_colors[y][x] = *blurred_color;
        }
    }

    char opath[] = "C:\\Users\\student\\Desktop\\reversed_boss.bmp";
    std::ofstream ofstream(opath);
    ofstream.write((char*)&file_header, sizeof(FileHeader));
    ofstream.write((char*)&info_header, sizeof(InfoHeader));

    for (long line = 0; line < info_header.height; line++)
    {
        ofstream.write((char*)initial_colors[line], info_header.width * 3);
    }

    ofstream.close();
}