#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QVector>
#include <QTextStream>

class SceneObject;

class Scene : public QObject
{
  Q_OBJECT

public:
  Scene(QObject *parent=0);
  ~Scene();

  QVector<SceneObject*> objects_;

  void draw();

  float spread_;
  float shrink_;

  float rot_x_;
  float rot_y_;
  float rot_z_;

  bool wireframe_;

  float zoom_;

  bool user_color_;

  unsigned int current_frame_;
  unsigned int frame_delay_count_;
  unsigned int frame_delay_;

  int ObjectNumber() const;

  void LoadFile(const QString &filename);
  void LoadInput(QTextStream &in, const bool is3d);
  void LoadHull(QTextStream &in, const bool is3d);
  void LoadTetra(QTextStream &in, const bool is3d);

//  void SaveFile(QString filename);
private:

public slots:
  void SetShrink(const int &shrink);
  void SetSpread(const int &spread);
  void SetWireframe(const bool &wireframe);
  void SetUserColor(const bool &user_color);
  void SetFrameDelay(const int &fps);
  void Colorize();

signals:
  void Repaint();
};

#endif // SCENE_H
