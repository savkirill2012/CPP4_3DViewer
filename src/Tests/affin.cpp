#include "../Model/parser.h"
#include "../Model/transformation.h"
#include "main.h"

TEST(Affin, Subtest_2) {
  std::string file_path = "Tests/data/cube.txt";

  s21::ReadOne* read = new s21::ReadOne();
  s21::ReadTwo* read2 = new s21::ReadTwo();
  s21::Parser parser(read);
  s21::DataObj data_info;
  s21::Transform transform;
  parser.ReadFile(file_path, &data_info);
  parser.setStrategy(read2);
  parser.ReadFile(file_path, &data_info);

  transform.prev_angle_x = 50;
  transform.prev_angle_y = 10;
  s21::Transformation tr;

  tr.Rotate(data_info, transform);

  double point_mass[24] = {
      42.148977, 36.396218, -40.947196, 51.563128, 36.560542, -42.438478,
      40.914513, 42.629802, -48.053228, 50.328664, 42.794126, -49.544511,
      40.061856, 35.419211, -54.230410, 49.476007, 35.583535, -55.721692,
      41.296320, 29.185627, -47.124378, 50.710471, 29.349951, -48.615660};

  for (int i = 0; i < 24; i++) {
    EXPECT_NEAR(data_info.vertexes[i], point_mass[i], 1e-4);
  }
}
