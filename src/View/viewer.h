#ifndef VIEWER_H
#define VIEWER_H

#include <QColorDialog>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QString>
#include <QTimer>
#include <QVector>

#include "../third_party/QtGifImage/include/gifimage/qgifimage.h"
// #include <QColor>

#include <QMainWindow>

#include "glwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Viewer;
}
QT_END_NAMESPACE

class Viewer : public QMainWindow {
  Q_OBJECT

 public:
  Viewer(QWidget *parent = nullptr);
  ~Viewer();

 private slots:
  void on_load_from_file_btn_clicked();
  // void change_vertices_color();

 private:
  s21::GlobalViewSettings &global_settings =
      s21::GlobalViewSettings::Instance();
  Ui::Viewer *ui;
  QSettings *settings;
  GLWidget *glWidget;

  QTimer *timer;
  QGifImage *gif;
  int counter;

 public slots:
  void load_settings();
  void save_settings();
  void reset_settings();
  void on_screenshot_btn_clicked();
  void on_record_btn_clicked();
  void create_gif();
};
#endif  // VIEWER_H
