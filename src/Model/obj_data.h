#ifndef OBJ_DATA_H
#define OBJ_DATA_H

#include <array>
#include <vector>

namespace s21 {

struct DataObj {
  std::vector<double> vertexes = {};
  std::vector<unsigned int> facets = {};
  unsigned int count_vertex = 0;
  unsigned int count_facets = 0;
  unsigned int count_edges = 0;
};

struct Transform {
  double value = 1;
  double prev_angle_x = 0;
  double prev_angle_y = 0;
  double prev_angle_z = 0;

  std::array<double, 3> prev_coor = {};
};

enum Axis { kX, kY, kZ };

}  // namespace s21

#endif  // OBJ_DATA_H
