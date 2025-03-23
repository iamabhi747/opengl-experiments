#include <custom.h>


void BoundaryFill(int x, int y, OB_Color fill_color, OB_Color boundary_color, std::vector<GLubyte>& pixels, int width, int height)
{
    if (x < 0 || x >= width || y < 0 || y >= height) return;
    OB_Color ocp = getPixelColor(x, y, pixels, width);
    if(Check2Colors(fill_color, ocp) || Check2Colors(boundary_color, ocp)) return;

    setPixelColor(x, y, fill_color, pixels, width);

    BoundaryFill(x + 1, y    , fill_color, boundary_color, pixels, width, height);
    BoundaryFill(x - 1, y    , fill_color, boundary_color, pixels, width, height);
    BoundaryFill(x    , y + 1, fill_color, boundary_color, pixels, width, height);
    BoundaryFill(x    , y - 1, fill_color, boundary_color, pixels, width, height);
}