#include <custom.h>
#include <queue>

void FloodFill(int x, int y, OB_Color fill_color, OB_Color boundary_color, std::vector<GLubyte>& pixels, int width, int height)
{
    if (x < 0 || x >= width || y < 0 || y >= height) return;
    std::queue<std::pair<int, int>> queue;
    queue.push({x, y});
    while (!queue.empty())
    {
        auto [cx, cy] = queue.front(); queue.pop();
        if (cx < 0 || cx >= width || cy < 0 || cy >= height) continue;

        OB_Color ocp = getPixelColor(cx, cy, pixels, width);
        if (Check2Colors(fill_color, ocp) || Check2Colors(boundary_color, ocp)) continue;

        setPixelColor(cx, cy, fill_color, pixels, width);

        queue.push({cx + 1, cy});
        queue.push({cx - 1, cy});
        queue.push({cx, cy + 1});
        queue.push({cx, cy - 1});
    }
}