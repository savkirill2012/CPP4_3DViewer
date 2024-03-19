#include "viewer.h"

#include "./ui_viewer.h"

Viewer::Viewer(QWidget *parent) : QMainWindow(parent), ui(new Ui::Viewer) {
  ui->setupUi(this);
  glWidget = ui->widget;
  settings = new QSettings(this);
  load_settings();

  // connects
  connect(ui->vertices_color_btn, SIGNAL(clicked()), ui->widget,
          SLOT(change_vertices_color()));
  connect(ui->edges_color_btn, SIGNAL(clicked()), ui->widget,
          SLOT(change_edges_color()));
  connect(ui->background_color_btn, SIGNAL(clicked()), ui->widget,
          SLOT(change_background_color()));

  connect(ui->edges_type_combobox, SIGNAL(currentIndexChanged(int)), ui->widget,
          SLOT(set_edges_type(int)));
  connect(ui->projection_type_combobox, SIGNAL(currentIndexChanged(int)),
          ui->widget, SLOT(set_projection_type(int)));
  connect(ui->vertices_display_method_combobox,
          SIGNAL(currentIndexChanged(int)), ui->widget,
          SLOT(set_vertices_method(int)));  // add

  connect(ui->edges_thikness_slider, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(set_line_width(int)));
  connect(ui->vertices_size_slider, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(set_vertices_size(int)));

  connect(ui->rotation_x_spinbox, SIGNAL(valueChanged(double)), ui->widget,
          SLOT(on_rotation_x_spinbox_valueChanged(double)));
  connect(ui->rotation_y_spinbox, SIGNAL(valueChanged(double)), ui->widget,
          SLOT(on_rotation_y_spinbox_valueChanged(double)));
  connect(ui->rotation_z_spinbox, SIGNAL(valueChanged(double)), ui->widget,
          SLOT(on_rotation_z_spinbox_valueChanged(double)));

  connect(ui->position_x_spinbox, SIGNAL(valueChanged(double)), ui->widget,
          SLOT(on_position_x_spinbox_valueChanged(double)));
  connect(ui->position_y_spinbox, SIGNAL(valueChanged(double)), ui->widget,
          SLOT(on_position_y_spinbox_valueChanged(double)));
  connect(ui->position_z_spinbox, SIGNAL(valueChanged(double)), ui->widget,
          SLOT(on_position_z_spinbox_valueChanged(double)));

  connect(ui->model_scale_slider, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(on_model_scale_slider_valueChanged(int)));
  connect(ui->reset_model_settings_btn, SIGNAL(clicked()), this,
          SLOT(reset_settings()));
}

Viewer::~Viewer() {
  save_settings();
  delete ui;
}

void Viewer::on_load_from_file_btn_clicked() {
  QString path =
      QFileDialog::getOpenFileName(this, "Load a file", QDir::currentPath());
  if (!path.isEmpty()) {
    QFileInfo fileInfo(path);
    if (fileInfo.suffix() != "obj") {
      QMessageBox::warning(this, "Warning!",
                           "Invalid file extension. Expected '.obj'");
    } else {
      ui->widget->modelPath = path;
      QString filename = fileInfo.fileName();
      ui->Filename_Label->setText(filename);
      ui->widget->initialize_model();

      ui->edges_count_label->setText(
          QString::number(ui->widget->model->GetData().count_edges));
      ui->vertices_count_label->setText(
          QString::number(ui->widget->model->GetData().count_vertex));
    }
  }
}

void Viewer::save_settings() {
  settings->setValue("background", global_settings.GetBackgroundColor());
  settings->setValue("width", global_settings.GetHigthSize());
  settings->setValue("edges_t", global_settings.GetEdgesType());
  settings->setValue("edges_color", global_settings.GetEdgeColor());
  settings->setValue("vetr_method", global_settings.GetVerticesDisplayMethod());
  settings->setValue("vertices_size", global_settings.GetHigthSize());
  settings->setValue("vertices_color", global_settings.GetHigthColor());
  settings->setValue("projection_type", global_settings.GetProjectionType());
}

void Viewer::load_settings() {
  QVariant bg = settings->value("background");
  QVariant width = settings->value("width");
  QVariant edges_t = settings->value("edges_t");
  QVariant edges_color = settings->value("edges_color");
  QVariant vetr_method = settings->value("vetr_method");
  QVariant vertices_size = settings->value("vertices_size");
  QVariant vertices_color = settings->value("vertices_color");
  QVariant projection_type = settings->value("projection_type");

  if (bg.isValid()) {
    global_settings.SetBackgroundColor(bg.value<QColor>());
  }
  if (width.isValid()) {
    glWidget->set_line_width(width.value<float>());
    ui->edges_thikness_slider->setValue(width.value<float>());
  }
  if (edges_t.isValid()) {
    glWidget->set_edges_type(edges_t.value<int>());
    ui->edges_type_combobox->setCurrentIndex(edges_t.value<int>());
  }
  if (edges_color.isValid()) {
    global_settings.SetEdgeColor(edges_color.value<QColor>());
  }
  if (vetr_method.isValid()) {
    glWidget->set_vertices_method(vetr_method.value<int>());
    ui->vertices_display_method_combobox->setCurrentIndex(
        vetr_method.value<int>());
  }
  if (vertices_size.isValid()) {
    glWidget->set_vertices_size(vertices_size.value<float>());
    ui->vertices_size_slider->setValue(vertices_size.value<float>());
  }
  if (vertices_color.isValid()) {
    global_settings.SetHigthColor(vertices_color.value<QColor>());
  }
  if (projection_type.isValid()) {
    glWidget->set_projection_type(projection_type.value<int>());
    ui->projection_type_combobox->setCurrentIndex(projection_type.value<int>());
  }
  update();
}

void Viewer::reset_settings() {
  global_settings.SetBackgroundColor(QColor(Qt::black));
  global_settings.SetEdgesType(0);
  global_settings.SetEdgesSize(1);
  global_settings.SetProectionType(0);
  global_settings.SetVerticesDisplayMethod(0);
  global_settings.SetHigthSize(1);
  global_settings.SetEdgeColor(QColor(Qt::white));
  global_settings.SetHigthColor(QColor(Qt::white));
  glWidget->update();
}

void Viewer::on_screenshot_btn_clicked() {
  QString filename =
      QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
  QString filter = "JPEG Files (*.jpg);;BMP Files (*.bmp);;All Files (*)";
  QString filepath = QFileDialog::getSaveFileName(
      this, "Enter the name of screenshot", filename, filter);
  if (!filepath.isEmpty()) {
    QString extension = "jpg";
    extension = QFileInfo(filepath).suffix().toLower();
    extension = extension.isEmpty() ? "jpg" : extension;
    if (!(extension == "jpeg" || extension == "jpg" || extension == "bmp")) {
      QMessageBox::warning(this, "Warning!",
                           "Invalid file extension. Expected JPG or BMP");
    }
    QImage image = glWidget->grab().toImage();
    image.save(filepath, extension.toUtf8().constData());
  }
}

void Viewer::on_record_btn_clicked() {
  if (!glWidget->modelPath.isEmpty()) {
    timer = new QTimer(this);
    gif = new QGifImage();
    counter = 0;
    timer->start(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(create_gif()));
    ui->record_btn->setText("Recording in progress");
  } else {
    QMessageBox::warning(this, "Warning!", "File not uploaded");
  }
}

void Viewer::create_gif() {
  gif->setDefaultDelay(50);
  QImage image = glWidget->grabFramebuffer();
  QImage resized_image =
      image.scaled(1920, 1080, Qt::KeepAspectRatio, Qt::SmoothTransformation);
  gif->addFrame(resized_image);
  counter++;
  if (counter == 50) {
    timer->stop();
    QString filename =
        QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
    gif->save(filename);
    QMessageBox::information(this, "Success!", "Gif saved successfully");
    delete gif;
    ui->record_btn->setText("Start recording");
  }
}
