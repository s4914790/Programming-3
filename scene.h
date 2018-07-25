#ifndef SCENE_H
#define SCENE_H

#include "glinclude.h"
#include <QOpenGLWindow>
#include <QElapsedTimer>
#include <ngl/Transformation.h>

#include "texturepack.h"
#include "character.h"



struct InputAxis
{
  float forward = 0.0f;
  float right = 0.0f;
};

struct Light
{
  ngl::Vec3 position = ngl::Vec3();
  ngl::Vec3 colour = {250.0f, 250.0f, 250.0f};
};

//----------------------------------------------------------------------------------------------------------------------
/// @file scene.h
/// @brief this class inherits from the Qt OpenGLWindow and allows us to use NGL to draw OpenGL
/// @class NGLScene
/// @brief our main glwindow widget for NGL applications all drawing elements are put in this file
//----------------------------------------------------------------------------------------------------------------------
class Scene : public QOpenGLWindow
{
  Q_OBJECT

public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for our NGL drawing class
  /// @param [in] parent the parent window to the class
  //----------------------------------------------------------------------------------------------------------------------
  Scene();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor must close down ngl and release OpenGL resources
  //----------------------------------------------------------------------------------------------------------------------
  ~Scene() override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the initialize class is called once when the window is created and we have a valid GL context
  /// use this to setup any default GL stuff
  //----------------------------------------------------------------------------------------------------------------------
  void initializeGL() override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this is called everytime we want to draw the scene
  //----------------------------------------------------------------------------------------------------------------------
  void paintGL() override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this is called everytime we want to draw the scene
  //----------------------------------------------------------------------------------------------------------------------
  void resizeGL(int _w, int _h) override;

  const std::vector<std::unique_ptr<Actor> > &actors() const;

  const Character &player() const;

private:
  /// @brief timing for camera update
  //----------------------------------------------------------------------------------------------------------------------
  float m_deltaTime = 0.0f;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief frame time for camera update
  //----------------------------------------------------------------------------------------------------------------------
  float m_lastFrame = 0.0f;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief timer for measurment
  /// -----------------------------------------------------------------------------
  QElapsedTimer m_timer;

  InputAxis m_inputAxis;
  ngl::Vec3 m_gravity;
  Character m_player;

  std::vector<Light> m_lights;
  std::unique_ptr<TexturedMesh> m_skybox;
  std::vector<std::unique_ptr<Actor>> m_actors;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Qt Event called when a key is pressed
  /// @param [in] _event the Qt event to query for size etc
  //----------------------------------------------------------------------------------------------------------------------
  void keyPressEvent(QKeyEvent *_event) override;
  void keyReleaseEvent(QKeyEvent *_event) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called every time a mouse is moved
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mouseMoveEvent(QMouseEvent *_event) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse button is pressed
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mousePressEvent(QMouseEvent *_event) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse button is released
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mouseReleaseEvent(QMouseEvent *_event) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse wheel is moved
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void wheelEvent(QWheelEvent *_event) override;

  /// Initialise a single side of the environment map, used in initEnvironment
  void initEnvironmentSide(GLenum target, const char* filename);
  /// Initialise the entire environment map
  void initEnvironment();
  /// Initialise shader for meshes
  void initEnvironmentShader();
  void initCamera();
  void initLight();
  void initLightShader();
  void initMeshActors();

  void paintSkyBox();
};

#endif // SCENE_H
