#include <limits>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
 
using row_t = std::vector<int>;
using map_t = std::vector<row_t>;
struct area
{
  int x;
  int y;
  int dist = 1;
};
 
map_t LoadInput(const char *fileName);
int GetLongestRoute(const map_t &maps, int x, int y, int &last);
 
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " [filename]" << std::endl;
    return -1;
  }
  map_t maps = LoadInput(argv[1]);
 
  // Find highest skiing route
  int longestLength = 0, maxHeight = 0;
  
  for (size_t y = 0; y < maps.size(); ++y)
  {
    for (size_t x = 0; x < maps[y].size(); ++x)
    {
      auto last = std::numeric_limits<int>::max();
      int currentLongest = GetLongestRoute(maps, x, y, last);
      int currentHeight = maps[y][x] - last;
 
      /* std::cout << "Current height: " << currentHeight << std::endl; */
      if (currentLongest > longestLength) 
      {
        longestLength = currentLongest;
        maxHeight = currentHeight;
      }
      else if (currentLongest == longestLength)
        maxHeight = std::max(maxHeight, currentHeight);
    }
  }
 
  std::cout << "Length: " << longestLength << std::endl << "Drop: " << maxHeight << std::endl;
  //std::cout << "email: " << longestLength << maxHeight << "@redmart.com" << std::endl;
 
  /* for (const auto &row : maps) */
  /* { */
  /*   for (const auto &col : row) */
  /*   { */
  /*     std::cout << col << " "; */
  /*   } */
  /*   std::cout << std::endl; */
  /* } */
  return 0;
}
 
map_t LoadInput(const char *fileName)
{
  map_t maps;
  std::ifstream ifs(fileName);
  if (ifs.bad())
  {
    std::cout << "Error loading " << fileName << std::endl;
    return maps;
  }
 
  int w, h;
  ifs >> w >> h;
 
  /*
     Since reading the file line by line, I will put
     the vector as line by line instead for easier loading
   */
 
  // std::cout << w << " " << h << std::endl;
  maps.resize(h);
 
  for (auto &row : maps)
  {
    for (int i = 0; i < w; ++i)
    {
      int id;
      ifs >> id;
      row.push_back(id);
    }
  }
 
  return maps;
}
 
bool CanReach(int from, int to)
{
  return from > to;
}
 
int GetLongestRoute(const map_t &maps, int x, int y, int &last)
{
  // Need some backtracking algorithm here
  std::queue<area> areas;
  areas.push(area{x, y});
  int maxDist = -1;
 
  while (!areas.empty())
  {
    auto current = areas.front();
    areas.pop();
 
    /* std::cout << "Current node: x:" << current.x << " y:" << current.y << */
    /*   " dist:" << current.dist << */
    /*   " val:" << maps[current.y][current.x] << std::endl; */
 
    if (current.dist > maxDist)
    {
      maxDist = current.dist;
      last = maps[current.y][current.x];
    }
    else if (current.dist == maxDist)
      last = std::min(maps[current.y][current.x], last);
 
    // Visit neighbours of current node
    int cx = current.x;
 
    // North
    int cy = current.y - 1;
    if (cy >= 0)
      if (CanReach(maps[current.y][cx], maps[cy][cx]))
        areas.push(area{cx, cy, current.dist + 1});
 
    // South
    cy = current.y + 1;
    if (cy < static_cast<int>(maps.size()))
      if (CanReach(maps[current.y][cx], maps[cy][cx]))
        areas.push(area{cx, cy, current.dist + 1});
 
    cy = current.y;
 
    // East
    cx = current.x + 1;
    if (cx < static_cast<int>(maps[cy].size()))
      if (CanReach(maps[cy][current.x], maps[cy][cx]))
        areas.push(area{cx, cy, current.dist + 1});
 
    // West
    cx = current.x - 1;
    if (cx >= 0)
      if (CanReach(maps[cy][current.x], maps[cy][cx]))
        areas.push(area{cx, cy, current.dist + 1});
  }
 
  /* std::cout << "Max dist: " << maxDist << std::endl; */
  /* std::cout << "Last: " << last << std::endl; */
  return maxDist;
}
