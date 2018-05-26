#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>

class Scene;

class GLWidget : public QGLWidget
{
  Q_OBJECT
public:
  explicit GLWidget(QWidget *parent = 0);

  void SetScene(Scene *scene);
  void UpdateBGColor();
protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

  void ApplyRot();
  void DrawOneAxis();
  void DrawAxis();

  Scene *scene_;

  QPoint last_click_;
  QPoint delta_;
  QPoint auto_delta_;

  QTimer auto_paint_timer_;

  QImage text_font_;
signals:

public slots:
  void AutoPaint();
  void TryRepaint();
};

#endif // GLWIDGET_H
