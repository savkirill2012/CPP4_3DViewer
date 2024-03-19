#include "../Model/parser.h"

#include "main.h"

TEST(Parser, Subtest_1) {
  std::string file_path = "Tests/data/cube.txt";

  s21::ReadOne* read = new s21::ReadOne();
  s21::ReadTwo* read2 = new s21::ReadTwo();
  s21::Parser parser(read);
  s21::DataObj data_info;
  s21::Transform transform;
  parser.ReadFile(file_path, &data_info);
  parser.setStrategy(read2);
  parser.ReadFile(file_path, &data_info);

  double point_mass[8][3] = {
      {48.656645, 48.864150, 4.766477},  {58.189599, 48.864150, 4.766477},
      {48.656645, 58.397104, 4.766477},  {58.189599, 58.397104, 4.766477},
      {48.656645, 58.397104, -4.766477}, {58.189599, 58.397104, -4.766477},
      {48.656645, 48.864150, -4.766477}, {58.189599, 48.864150, -4.766477}};

  for (int i = 0; i < 24; i++) {
    ASSERT_NEAR(point_mass[i / 3][i % 3], data_info.vertexes[i], 1e-4);
  }

  int line_mass[24][2] = {{1, 2}, {2, 4}, {4, 3}, {3, 1}, {3, 4}, {4, 6},
                          {6, 5}, {5, 3}, {5, 6}, {6, 8}, {8, 7}, {7, 5},
                          {7, 8}, {8, 2}, {2, 1}, {1, 7}, {2, 8}, {8, 6},
                          {6, 4}, {4, 2}, {7, 1}, {1, 3}, {3, 5}, {5, 7}};

  for (int i = 0, j = 0; i < 24; i += 2, j++) {
    ASSERT_EQ(line_mass[j][0] - 1, data_info.facets[i]);
    ASSERT_EQ(line_mass[j][1] - 1, data_info.facets[i + 1]);
  }

  ASSERT_EQ(data_info.count_edges, 6);
  ASSERT_EQ(data_info.count_facets, 24);
  ASSERT_EQ(data_info.count_vertex, 24);
}
