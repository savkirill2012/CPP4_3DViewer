#include "transformation.h"

namespace s21 {

void Transformation::Scale(DataObj &model, Transform &transform) {
  size_t size = model.vertexes.size();
  for (size_t i = 0; i < size; i += 3) {
    model.vertexes[i] *= transform.value;
    model.vertexes[i + 1] *= transform.value;
    model.vertexes[i + 2] *= transform.value;
  }
}

void Transformation::Translate(DataObj &model, Transform &transform) {
  size_t size = model.vertexes.size();
  for (size_t i = 0; i < size; i += 3) {
    model.vertexes[i] += transform.prev_coor[0];
    model.vertexes[i + 1] += transform.prev_coor[1];
    model.vertexes[i + 2] += transform.prev_coor[2];
  }
}

void Transformation::Rotate(DataObj &model, Transform &transform) {
  size_t size = model.vertexes.size();
  for (size_t i = 0; i < size; i += 3) {
    double temp_y = model.vertexes[i + 1];
    double temp_z = model.vertexes[i + 2];
    model.vertexes[i + 1] =
        cos(kConvertAngle - kConvertAngle * transform.prev_angle_x) * temp_y -
        sin(kConvertAngle - kConvertAngle * transform.prev_angle_x) * temp_z;
    model.vertexes[i + 2] =
        sin(kConvertAngle - kConvertAngle * transform.prev_angle_x) * temp_y +
        cos(kConvertAngle - kConvertAngle * transform.prev_angle_x) * temp_z;
    double temp_x = model.vertexes[i];
    temp_z = model.vertexes[i + 2];
    model.vertexes[i] =
        cos(kConvertAngle - kConvertAngle * transform.prev_angle_y) * temp_x -
        sin(kConvertAngle - kConvertAngle * transform.prev_angle_y) * temp_z;
    model.vertexes[i + 2] =
        sin(kConvertAngle - kConvertAngle * transform.prev_angle_y) * temp_x +
        cos(kConvertAngle - kConvertAngle * transform.prev_angle_y) * temp_z;
    temp_x = model.vertexes[i];
    temp_y = model.vertexes[i + 1];
    model.vertexes[i] =
        cos(kConvertAngle - kConvertAngle * transform.prev_angle_z) * temp_x -
        sin(kConvertAngle - kConvertAngle * transform.prev_angle_z) * temp_y;
    model.vertexes[i + 1] =
        sin(kConvertAngle - kConvertAngle * transform.prev_angle_z) * temp_x +
        cos(kConvertAngle - kConvertAngle * transform.prev_angle_z) * temp_y;
  }
}
}  // namespace s21
