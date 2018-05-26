#ifndef SCENETETRAHEDRONS_H
#define SCENETETRAHEDRONS_H

#include "sceneobject.h"
#include "geometry.h"

#include <QVector>

class SceneTetrahedrons : public SceneObject
{
public:
  SceneTetrahedrons(const QString &name, const QString &owner, const double &spread, const QString &color);
  ~SceneTetrahedrons();

  QVector< QVector<Tetrahedron*> > tetrahedrons_;

  void DrawObject(const float &spread, const float &shrink, const bool user_color, const unsigned int current_frame) const;
  void Colorize();
  void Delete();
  void ClearTetrahedrons();
};

#endif // SCENETETRAHEDRONS_H
