#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QVector3D>
#include <QColor>
#include <QVector>

class Face{
public:
  Face(const QVector3D &v0, const QVector3D &v1, const QVector3D &v2);
  Face(const QVector3D &v0, const QVector3D &v1, const QVector3D &v2, const QColor &color_);
  Face(const QVector<QVector3D> &v);
  Face(const QVector<QVector3D> &v, const QColor &color);

  void Draw(const float &spread, const float &shrink, const bool user_color) const;
  void DrawTetraFace(const float &spread, const float &shrink, const bool user_color) const;
  void SetColor(const QColor &color);
private:
  QVector<QVector3D> v_;
  QVector3D n_;
  QVector3D center_;
  QColor color_;

  bool valid_;
};

class Tetrahedron{
public:
  Tetrahedron(const QVector3D &v0, const QVector3D &v1, const QVector3D &v2);
  Tetrahedron(const QVector3D &v0, const QVector3D &v1, const QVector3D &v2, const QVector3D &v3);
  ~Tetrahedron();

  void Draw(const float &spread, const float &shrink, const bool user_color) const;

  void SetColor(const QColor &color);
private:
  int face_count_;

  Face *f[4];
  QVector3D center_;
};

#endif // GEOMETRY_H
