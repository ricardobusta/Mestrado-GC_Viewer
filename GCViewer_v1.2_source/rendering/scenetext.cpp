//#include "scenetext.h"

//SceneText::SceneText(const QString &name, const QString &owner, const QString &color)
//  : character_size_(0.10f),
//    char_max_line_(0),
//    char_max_space_(0),
//    SceneObject(name,owner,color)
//{
//}

//void SceneText::DrawObject(const float &spread, const float &shrink, const bool user_color) const
//{
//  glPushMatrix();
//  float scale = 1*character_size_;
//  glScalef(scale,scale,scale);
//  glPushAttrib(GL_ALL_ATTRIB_BITS);
//  glEnable(GL_TEXTURE_2D);
//  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
//  glEnable(GL_BLEND);
//  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//  glBegin(GL_TRIANGLES);
//  glColor4f(1,1,1,1);

//  float char_w = 1.0f/16.0f;
//  float char_h = 1.0f/16.0f;

//  int char_space_ = 0;
//  int char_line_ = 0;
//  for(int i=0;i<transformed_text_.size();i++){
//    if(text_[i]=='\n'){
//      char_space_ = 0;
//      char_line_ -= 2;
//      continue;
//    }
//    int xi = transformed_text_[i]%16;
//    float x = float(transformed_text_[i]%16)*char_w;
//    float y = float(transformed_text_[i]/16)*char_h;

//    glNormal3f(0,0,1);
//    glTexCoord2f(x+0,1-(y+char_h));
//    glVertex3f(-1+char_space_,-1+char_line_,0);
//    glTexCoord2f(x+char_w,1-(y+char_h));
//    glVertex3f( 1+char_space_,-1+char_line_,0);
//    glTexCoord2f(x+char_w,1-(y));
//    glVertex3f( 1+char_space_, 1+char_line_,0);

//    glTexCoord2f(x+0,1-(y+char_h));
//    glVertex3f(-1+char_space_,-1+char_line_,0);
//    glTexCoord2f(x+char_w,1-(y));
//    glVertex3f( 1+char_space_, 1+char_line_,0);
//    glTexCoord2f(x+0,1-(y));
//    glVertex3f(-1+char_space_, 1+char_line_,0);

//    glNormal3f(0,0,-1);
//    glTexCoord2f(x+0,1-(y+char_h));
//    glVertex3f(-1+char_space_,-1+char_line_,0);
//    glTexCoord2f(x+char_w,1-(y));
//    glVertex3f( 1+char_space_, 1+char_line_,0);
//    glTexCoord2f(x+char_w,1-(y+char_h));
//    glVertex3f( 1+char_space_,-1+char_line_,0);

//    glTexCoord2f(x+0,1-(y+char_h));
//    glVertex3f(-1+char_space_,-1+char_line_,0);
//    glTexCoord2f(x+0,1-(y));
//    glVertex3f(-1+char_space_, 1+char_line_,0);
//    glTexCoord2f(x+char_w,1-(y));
//    glVertex3f( 1+char_space_, 1+char_line_,0);
//    char_space_ += 2;
//  }

//  glEnd();
//  glPopAttrib();
//  glPopMatrix();
//}

//void SceneText::CreateDefaultObject(const QColor &color)
//{

//}

//void SceneText::Colorize()
//{

//}

//void SceneText::SetText(const QString &text)
//{
//  QString pattern_text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.:,/+-*$@!?\"'_\\ºª~^´`%0123456789[](){} ";

//  text_ = text;
//  transformed_text_.resize(text_.size());
//  for(int i=0;i<text_.size();i++){
//    for(int j=0;j<pattern_text.size();j++){
//      if(text_[i].toUpper() == pattern_text[j]){
//        transformed_text_[i] = j;
//        continue;
//      }
//    }
//  }

//  qDebug() << text_;
//  qDebug() << transformed_text_;
//}
