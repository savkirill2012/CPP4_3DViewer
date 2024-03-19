#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <algorithm>
#include <cmath>
#include <vector>

#include "obj_data.h"

namespace s21 {

class Transformation {
 public:
  Transformation() {}
  ~Transformation() {}
  void Rotate(DataObj &model, Transform &transform);
  void Scale(DataObj &model, Transform &transform);
  void Translate(DataObj &model, Transform &transform);

 private:
  static constexpr double kConvertAngle = M_PI / 180;
};

}  // namespace s21

#endif  // TRANSFORMATION_H
