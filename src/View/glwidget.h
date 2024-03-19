#ifndef GLWIDGET_H
#define GLWIDGET_H

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <QColorDialog>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>
#include <QString>
#include <QTimer>
#include <QVector>

#include "../Controller/contrl.cpp"
#include "../Model/parser.h"

class GLWidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  using EdgesType = s21::GlobalSettingsContrl::EdgesType;
  using VerticesDisplayMethod =
      s21::GlobalSettingsContrl::VerticesDisplayMethod;
  using ProjectionType = s21::GlobalSettingsContrl::ProjectionType;

  GLWidget(QWidget* parent = nullptr);
  ~GLWidget();

  QString modelPath;

  s21::PosSettingsContrl* pos_settings = new s21::PosSettingsContrl;
  s21::ModelContrl* model = new s21::ModelContrl;
  s21::GlobalSettingsContrl global_settings = s21::GlobalSettingsContrl();
  void initialize_model();

 private:
  void set_proection_view();
  void set_point_view();
  void set_line_view();

 protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);

 public slots:
  void change_vertices_color();
  void change_edges_color();
  void change_background_color();
  void set_edges_type(int type);
  void set_line_width(int size);
  void set_vertices_method(int type);
  void set_vertices_size(int size);
  void set_projection_type(int type);
  void on_rotation_x_spinbox_valueChanged(double arg1);
  void on_rotation_y_spinbox_valueChanged(double arg1);
  void on_rotation_z_spinbox_valueChanged(double arg1);

  void on_position_x_spinbox_valueChanged(double arg1);
  void on_position_y_spinbox_valueChanged(double arg1);
  void on_position_z_spinbox_valueChanged(double arg1);
  void on_model_scale_slider_valueChanged(int arg1);
};
#endif  // GLWIDGET_H
