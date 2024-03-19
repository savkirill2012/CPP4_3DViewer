// #ifndef MODEL_H_
// #define MODEL_H_

#include <QColor>
#include <QSettings>
#include <list>
#include <string>

#include "obj_data.h"
#include "transformation.h"

namespace s21 {

class Subject;

class Observer {
 public:
  virtual ~Observer(){};
  virtual void SetSubject(Subject* subject) { _subject = subject; };
  virtual void RemoveSubject() { _subject = nullptr; };
  virtual Subject* GetSubject() { return _subject; };
  virtual void Update() = 0;
  // protected:
  //     Observer();
 private:
  Subject* _subject;
};

class Subject {
 public:
  virtual ~Subject(){};
  virtual void Attach(Observer* add_o) {
    _observers.push_back(add_o);
    add_o->SetSubject(this);
  };
  virtual void Detach(Observer* rem_o) {
    _observers.remove(rem_o);
    rem_o->RemoveSubject();
  };
  virtual void Notify() {
    for (std::list<Observer*>::iterator st = _observers.begin(),
                                        end = _observers.end();
         st != end; ++st) {
      (*st)->Update();
    }
  };
  // protected:
  //     Subject();
 private:
  std::list<Observer*> _observers;
};

class PositionModelSettings : public Subject {
 public:
  PositionModelSettings()
      : _x_val(0),
        _y_val(0),
        _z_val(0),
        _x_angle(0),
        _y_angle(0),
        _z_angle(0),
        _scale(1){};

  double GetAngleX() { return _x_angle; };
  double GetAngleY() { return _y_angle; };
  double GetAngleZ() { return _z_angle; };

  double GetPosX() { return _x_val; };
  double GetPosY() { return _y_val; };
  double GetPosZ() { return _z_val; };

  double GetScale() { return _scale; };

  void SetAngleX(double x) {
    _x_angle = x;
    Notify();
  };

  void SetAngleY(double y) {
    _y_angle = y;
    Notify();
  };

  void SetAngleZ(double z) {
    _z_angle = z;
    Notify();
  };

  void SetPosX(double x) {
    _x_val = x;
    Notify();
  };

  void SetPosY(double y) {
    _y_val = y;
    Notify();
  };

  void SetPosZ(double z) {
    _z_val = z;
    Notify();
  };

  void SetScale(double zoom) {
    _scale = zoom;
    Notify();
  };

 private:
  double _x_val;
  double _y_val;
  double _z_val;

  double _x_angle;
  double _y_angle;
  double _z_angle;

  double _scale;
};

class Model : public Observer {
 public:
  Model(){};
  Model(s21::DataObj data, s21::Transform transform)
      : _data(data), _transform(transform){};

  void ChangeMoveVals(PositionModelSettings* settings) {
    _transform.prev_angle_x = settings->GetAngleX();
    _transform.prev_angle_y = settings->GetAngleY();
    _transform.prev_angle_z = settings->GetAngleZ();

    _transform.prev_coor[0] = settings->GetPosX();
    _transform.prev_coor[1] = settings->GetPosY();
    _transform.prev_coor[2] = settings->GetPosZ();

    _transform.value = settings->GetScale();
  }

  void Update() override {
    ChangeMoveVals(dynamic_cast<PositionModelSettings*>(GetSubject()));
  };

  s21::DataObj GetData() {
    s21::DataObj ret_data = _data;
    s21::Transformation t;
    t.Scale(ret_data, _transform);
    t.Rotate(ret_data, _transform);
    t.Translate(ret_data, _transform);

    return ret_data;
  };

 private:
  s21::DataObj _data;
  s21::Transform _transform;
};

class GlobalViewSettings {
 public:
  static GlobalViewSettings& Instance() {
    static GlobalViewSettings _instance;
    return _instance;
  };

  enum VerticesDisplayMethod { SQUARE, CIRCLE, BLANK };
  enum EdgesType { SOLID, DASHED };
  enum ProjectionType { PARALLEL, CENTRAL };
  QSettings* settings;

  void SetProectionType(int type) {
    _type_of_proection = ProjectionType(type);
  };
  void SetHigthColor(QColor color) { _higth_color = color; };
  void SetEdgeColor(QColor color) { _edge_color = color; };
  void SetBackgroundColor(QColor color) { _back_colour = color; };
  void SetEdgesType(int type) { _edge_style = EdgesType(type); };
  void SetHigthSize(double size) { _higth_size = size; };
  void SetEdgesSize(double size) { _edge_size = size; };
  void SetVerticesDisplayMethod(int type) {
    _higth_style = VerticesDisplayMethod(type);
  };

  QColor GetHigthColor() { return _higth_color; };
  QColor GetEdgeColor() { return _edge_color; };
  QColor GetBackgroundColor() { return _back_colour; };
  EdgesType GetEdgesType() { return _edge_style; };
  ProjectionType GetProjectionType() { return _type_of_proection; };
  VerticesDisplayMethod GetVerticesDisplayMethod() { return _higth_style; };
  float GetHigthSize() { return _higth_size; };
  float GetEdgesSize() { return _edge_size; };

 private:
  GlobalViewSettings() {
    settings = new QSettings();
    QVariant bg = settings->value("background");
    QVariant width = settings->value("width");
    QVariant edges_t = settings->value("edges_t");
    QVariant edges_color = settings->value("edges_color");
    QVariant vetr_method = settings->value("vetr_method");
    QVariant vertices_size = settings->value("vertices_size");
    QVariant vertices_color = settings->value("vertices_color");
    QVariant projection_type = settings->value("projection_type");

    if (bg.isValid()) {
      SetBackgroundColor(bg.value<QColor>());
    }
    if (width.isValid()) {
      SetHigthSize(width.value<float>());
    }
    if (edges_t.isValid()) {
      SetEdgesType(edges_t.value<int>());
    }
    if (edges_color.isValid()) {
      SetEdgeColor(edges_color.value<QColor>());
    }
    if (vetr_method.isValid()) {
      SetVerticesDisplayMethod(vetr_method.value<int>());
    }
    if (vertices_size.isValid()) {
      SetHigthSize(vertices_size.value<float>());
    }
    if (vertices_color.isValid()) {
      SetHigthColor(vertices_color.value<QColor>());
    }
    if (projection_type.isValid()) {
      SetProectionType(projection_type.value<int>());
    }
  };

  ~GlobalViewSettings() {
    settings->setValue("background", GetBackgroundColor());
    settings->setValue("width", GetHigthSize());
    settings->setValue("edges_t", GetEdgesType());
    settings->setValue("edges_color", GetEdgeColor());
    settings->setValue("vetr_method", GetVerticesDisplayMethod());
    settings->setValue("vertices_size", GetHigthSize());
    settings->setValue("vertices_color", GetHigthColor());
    settings->setValue("projection_type", GetProjectionType());
  };

  ProjectionType _type_of_proection;
  QColor _higth_color;
  float _higth_size;
  VerticesDisplayMethod _higth_style;
  QColor _edge_color;
  float _edge_size;
  EdgesType _edge_style;
  QColor _back_colour;
};

}  // namespace s21

// #endif
