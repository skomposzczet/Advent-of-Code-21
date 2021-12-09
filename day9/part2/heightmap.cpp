#include "heightmap.hpp"

void Hmap::analyze()
{
    for (unsigned i = 0 ; i < rows.size() ; ++i)
        for (unsigned j = 0 ; j < rows.at(i).size() ; ++j)
            if (is_lowest(Point(j,i)))
                add_basin(detect_basin(Point(j,i)));
}

bool Hmap::is_lowest(Point p) const
{
    std::vector<Point> neighbour_vectors{Point(0,-1), Point(-1, 0), Point(1,0), Point(0,1)};

    unsigned bigger = std::count_if(neighbour_vectors.begin(), neighbour_vectors.end(), [this, &p](Point & vec)
    {
        if (iir(p+vec))
            return (get_char(p+vec) > get_char(p));
        else
            return true;
    }
    );

    return (bigger == neighbour_vectors.size());
}

int Hmap::detect_basin(Point p, std::vector<Point> & coords)
{
    if (std::find(coords.begin(), coords.end(), p) == coords.end())
        coords.push_back(p);
    else
        return 0;

    std::vector<Point> neighbour_vectors{Point(0,-1), Point(-1, 0), Point(1,0), Point(0,1)};

    for (auto & vec : neighbour_vectors)
        if (iir(p+vec))
            if (get_char(p+vec) != '9')
                detect_basin(p+vec, coords);

    return coords.size();
}

int Hmap::result() const
{
    return std::accumulate(basins.begin(), basins.end(), 1, std::multiplies<int>());
}

void Hmap::add_basin(const int b)
{
    basins.push_back(b);
    std::sort(basins.begin(), basins.end(), std::greater<>());

    if(basins.size() > 3)
        basins.pop_back();
}

bool Hmap::iir(const int x, const int y) const 
{
    return (y >= 0 && y < static_cast<int>(rows.size()) && x >= 0 && x < static_cast<int>(rows.at(y).size()));
}