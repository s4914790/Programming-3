#include <QApplication>
#include <QSurfaceFormat>

#include "scene.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QSurfaceFormat format;
  format.setSamples(4);
#if defined(__APPLE__)
  format.setMajorVersion(4);
  format.setMinorVersion(1);
#else
  // with luck we have the latest GL version so set to that
  format.setMajorVersion(4);
  format.setMinorVersion(5);
#endif
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setDepthBufferSize(24);
  QSurfaceFormat::setDefaultFormat(format);

  Scene scene;
  scene.resize(1024, 720);
  scene.show();

  return a.exec();
}
