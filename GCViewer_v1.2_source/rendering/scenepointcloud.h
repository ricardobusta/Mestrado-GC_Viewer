#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include "sceneobject.h"

#include <QVector3D>
#include <QVector>

class ScenePointCloud : public SceneObject
{
public:
  ScenePointCloud(const QString &name, const QString &owner, const double &object_spread, const QString &color);
  ~ScenePointCloud();

  QVector < QVector<QVector3D> > points_;

  void DrawObject(const float &spread, const float &shrink, const bool user_color, const unsigned int current_frame) const;
  void Colorize();
  void Delete();

  void ClearPoints();
};

#endif // POINTCLOUD_H
