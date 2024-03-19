#include "../Model/model.cpp"

namespace s21 {

class GlobalSettingsContrl {
 public:
  using EdgesType = GlobalViewSettings::EdgesType;
  using VerticesDisplayMethod = GlobalViewSettings::VerticesDisplayMethod;
  using ProjectionType = GlobalViewSettings::ProjectionType;

  GlobalSettingsContrl() : _global_settings(GlobalViewSettings::Instance()){};

  // Getters
  QColor GetBGColor() { return _global_settings.GetBackgroundColor(); };
  QColor GetLineColor() { return _global_settings.GetEdgeColor(); };
  QColor GetHigthColor() { return _global_settings.GetHigthColor(); };

  VerticesDisplayMethod GetDisplayMethod() {
    return _global_settings.GetVerticesDisplayMethod();
  };
  EdgesType GetEdgesType() { return _global_settings.GetEdgesType(); };
  ProjectionType GetProjectionType() {
    return _global_settings.GetProjectionType();
  };

  float GetHigthSize() { return _global_settings.GetHigthSize(); };
  float GetEdgesSize() { return _global_settings.GetEdgesSize(); };

  // Setters
  void SetHigthColor(QColor color) { _global_settings.SetHigthColor(color); };
  void SetEdgeColor(QColor color) { _global_settings.SetEdgeColor(color); };
  void SetBackgroundColor(QColor color) {
    _global_settings.SetBackgroundColor(color);
  };

  void SetEdgesType(int type) { _global_settings.SetEdgesType(type); };
  void SetVerticesDisplayMethod(int type) {
    _global_settings.SetVerticesDisplayMethod(type);
  };
  void SetProectionType(int type) { _global_settings.SetProectionType(type); };

  void SetHigthSize(double size) { _global_settings.SetHigthSize(size); };
  void SetEdgesSize(double size) { _global_settings.SetEdgesSize(size); };

 private:
  s21::GlobalViewSettings& _global_settings =
      s21::GlobalViewSettings::Instance();
};

class ModelContrl {
 public:
  ModelContrl() : _model(new Model){};
  ModelContrl(DataObj data, Transform transform)
      : _model(new Model(data, transform)){};

  ~ModelContrl() { delete _model; };

  DataObj GetData() { return _model->GetData(); };

  Model* GetModel() { return _model; }

 private:
  Model* _model;
};

class PosSettingsContrl {
 public:
  PosSettingsContrl() : _pos_settings(PositionModelSettings()){};

  double GetAngleX() { return _pos_settings.GetAngleX(); };
  double GetAngleY() { return _pos_settings.GetAngleY(); };
  double GetAngleZ() { return _pos_settings.GetAngleZ(); };

  double GetPosX() { return _pos_settings.GetPosX(); };
  double GetPosY() { return _pos_settings.GetPosY(); };
  double GetPosZ() { return _pos_settings.GetPosZ(); };

  double GetScale() { return _pos_settings.GetScale(); };

  void SetAngleX(double x) { _pos_settings.SetAngleX(x); };
  void SetAngleY(double y) { _pos_settings.SetAngleY(y); };
  void SetAngleZ(double z) { _pos_settings.SetAngleZ(z); };

  void SetPosX(double x) { _pos_settings.SetPosX(x); };
  void SetPosY(double y) { _pos_settings.SetPosY(y); };
  void SetPosZ(double z) { _pos_settings.SetPosZ(z); };

  void SetScale(double zoom) { _pos_settings.SetScale(zoom); };

  void Attach(Observer* pos) { _pos_settings.Attach(pos); };

 private:
  PositionModelSettings _pos_settings;
};

}  // namespace s21