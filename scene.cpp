#include "scene.h"

#include <ngl/Camera.h>
#include <ngl/NGLInit.h>
#include <ngl/NGLStream.h>
#include <ngl/Random.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Texture.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/VAOFactory.h>
#include <ngl/MultiBufferVAO.h>
#include <QGuiApplication>
#include <QMouseEvent>
#include <QDebug>

#include "boxcollider.h"

// Original base code by Jon Macey NGL Demos. Shader base code by Jon Macey and Richard

constexpr auto shaderProgram = "PBR";
constexpr auto vertexShader  = "PBRVertex";
constexpr auto fragShader    = "PBRFragment";

Scene::Scene():
  m_gravity(0.0f, -2.0f, 0.0f),
  m_player(this, {0.0f, 5.0f, 5.0f})
{
  setTitle("Game");
  m_timer.start();
}

Scene::~Scene()
{
  qDebug() << "Shutting down NGL, removing VAO's and Shaders";
}

void Scene::initializeGL()
{
  // we must call that first before any other GL commands to load and link the
  // gl commands from the lib, if that is not done program will crash
  ngl::NGLInit::instance();

  // Set background colour
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);

  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);

  glClearColor( 0.4f, 0.4f, 0.4f, 1.0f ); // Grey Background
  // enable depth testing for drawing
  glEnable( GL_DEPTH_TEST );
  // enable multisampling for smoother drawing
#ifndef USINGIOS_
  glEnable( GL_MULTISAMPLE );
#endif

  TexturePack::loadJSON("textures/textures.json");
  initEnvironment();
  initLight();
  initMeshActors();
}

void Scene::paintGL()
{
  float currentFrame = m_timer.elapsed()*0.001f;
  m_deltaTime = currentFrame - m_lastFrame;
  m_lastFrame = currentFrame;
  auto size = this->size();
  glViewport( 0, 0, size.width(), size.height() );
  // clear the screen and depth buffer
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  m_player.move(m_gravity, m_deltaTime);
  if (m_inputAxis.forward != 0.0f || m_inputAxis.right != 0.0f)
    {
      m_player.move(m_inputAxis.forward, m_inputAxis.right, m_deltaTime);
    }
  // grab an instance of the shader manager
  ngl::ShaderLib* shader = ngl::ShaderLib::instance();
  ( *shader )[ "PBR" ]->use();
  shader->setUniform("roughnessScale",0.0f);
  for (auto& mesh : m_actors)
    {
      mesh->paintGL();
    }

  paintSkyBox();
  update();
}

void Scene::resizeGL(int _w, int _h)
{
  m_player.setCameraProjection( 45.0f, static_cast<float>( _w ) / _h, 0.05f, 350.0f );
}

const std::vector<std::unique_ptr<Actor> > &Scene::actors() const
{
  return m_actors;
}

const Character &Scene::player() const
{
  return m_player;
}

void Scene::keyPressEvent(QKeyEvent *_event)
{
  switch ( _event->key() )
    {
    // escape key to quit
    case Qt::Key_Escape:
      QGuiApplication::exit( EXIT_SUCCESS );
      break;
    case Qt::Key_F:
      showFullScreen();
      break;
    case Qt::Key_W :
      m_inputAxis.forward +=1.0f;
      break;
    case Qt::Key_S :
      m_inputAxis.forward -=1.0f;
      break;
    case Qt::Key_D :
      m_inputAxis.right += 1.0f;
      break;
    case Qt::Key_A :
      m_inputAxis.right -= 1.0f;
      break;
    }
}

void Scene::keyReleaseEvent(QKeyEvent *_event)
{
  switch ( _event->key() )
    {
    case Qt::Key_W :
      m_inputAxis.forward -=1.0f;
      break;
    case Qt::Key_S :
      m_inputAxis.forward +=1.0f;
      break;
    case Qt::Key_D :
      m_inputAxis.right -= 1.0f;
      break;
    case Qt::Key_A :
      m_inputAxis.right += 1.0f;
      break;
    }
}

void Scene::mouseMoveEvent(QMouseEvent *_event)
{
  auto center = QPoint(width()/2,height()/2);
  auto delta = _event->pos() - center;
  m_player.rotate(delta.x(), -delta.y());
  auto glob = mapToGlobal(center);
  QCursor::setPos(glob);
  QOpenGLWindow::mouseMoveEvent(_event);
}

void Scene::mousePressEvent(QMouseEvent *_event)
{

}

void Scene::mouseReleaseEvent(QMouseEvent *_event)
{

}

void Scene::wheelEvent(QWheelEvent *_event)
{

}

void Scene::initEnvironmentSide(GLenum target, const char *filename)
{
  // Load up the image using NGL routine
  ngl::Image img(filename);

  // Transfer image data onto the GPU using the teximage2D call
  glTexImage2D (
        target,           // The target (in this case, which side of the cube)
        0,                // Level of mipmap to load
        img.format(),     // Internal format (number of colour components)
        img.width(),      // Width in pixels
        img.height(),     // Height in pixels
        0,                // Border
        GL_RGBA,          // Format of the pixel data
        GL_UNSIGNED_BYTE, // Data type of pixel data
        img.getPixels()   // Pointer to image data in memory
        );
}

void Scene::initEnvironment()
{
  // Enable seamless cube mapping
  glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

  // Placing our environment map texture in texture unit 0
  glActiveTexture (GL_TEXTURE0);

  // Now load up the sides of the cube
  initEnvironmentSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, "textures/skybox/sky_zneg.png");
  initEnvironmentSide(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, "textures/skybox/sky_zpos.png");
  initEnvironmentSide(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, "textures/skybox/sky_ypos.png");
  initEnvironmentSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, "textures/skybox/sky_yneg.png");
  initEnvironmentSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, "textures/skybox/sky_xneg.png");
  initEnvironmentSide(GL_TEXTURE_CUBE_MAP_POSITIVE_X, "textures/skybox/sky_xpos.png");

  // Generate mipmap levels
  glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

  // Set the texture parameters for the cube map
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP, GL_TRUE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  GLfloat anisotropy;
  glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisotropy);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);

  m_skybox.reset(new TexturedMesh("models/skybox2.obj", "sky"));
  initEnvironmentShader();
}

void Scene::initEnvironmentShader()
{
  // Create and compile the vertex and fragment shader
  auto shader=ngl::ShaderLib::instance();

  // create the shader program
  shader->createShaderProgram( shaderProgram );
  // now we are going to create empty shaders for Frag and Vert
  shader->attachShader( vertexShader, ngl::ShaderType::VERTEX );
  shader->attachShader( fragShader, ngl::ShaderType::FRAGMENT );
  // attach the source
  shader->loadShaderSource( vertexShader, "shaders/PBRVertex.glsl" );
  shader->loadShaderSource( fragShader, "shaders/PBRFragment.glsl" );
  // compile the shaders
  shader->compileShader( vertexShader );
  shader->compileShader( fragShader );
  // add them to the program
  shader->attachShaderToProgram( shaderProgram, vertexShader );
  shader->attachShaderToProgram( shaderProgram, fragShader );
  // now we have associated that data we can link the shader
  shader->linkProgramObject( shaderProgram );
  // and make it active ready to load values
  shader->loadShader("SkyProgram",
                     "shaders/test_vert.glsl",
                     "shaders/test_frag.glsl");

  // Set our cube map texture to on the shader so we can use it
  shader->use("SkyProgram");
  shader->setUniform("envMap", 10);
}

void Scene::initLight()
{
  // Create lights at custom positions with default colour
  m_lights = {{ngl::Vec3(-5.0f,  4.0f, -5.0f)},
              {ngl::Vec3( 5.0f,  4.0f, -5.0f)},
              {ngl::Vec3(-5.0f,  4.0f, 5.0f)},
              {ngl::Vec3( 5.0f,  4.0f, 5.0f)}
             };
  initLightShader();
}

void Scene::initLightShader()
{
  auto shader=ngl::ShaderLib::instance();
  ( *shader )[ shaderProgram ]->use();
  shader->setUniform("camPos",m_player.position());
  shader->setUniform("albedoMap", 0);
  shader->setUniform("normalMap", 1);
  shader->setUniform("metallicMap", 2);
  shader->setUniform("roughnessMap", 3);
  shader->setUniform("aoMap", 4);

  for(size_t i=0; i<m_lights.size(); ++i)
    {
      shader->setUniform(("lightPositions[" + std::to_string(i) + "]").c_str(),m_lights[i].position);
      shader->setUniform(("lightColors[" + std::to_string(i) + "]").c_str(),m_lights[i].colour);
    }

  ( *shader )[ ngl::nglColourShader ]->use();
  shader->setUniform("Colour",1.0f,1.0f,1.0f,1.0f);

  (*shader)[ ngl::nglDiffuseShader]->use();
  shader->setUniform("Colour",1.0f,1.0f,0.0f,1.0f);
  shader->setUniform("lightPos",1.0f,1.0f,1.0f);
  shader->setUniform("lightDiffuse",1.0f,1.0f,1.0f,1.0f);
}

void Scene::initMeshActors()
{
  auto floorActor = std::make_unique<Actor>(this,
                                            new TexturedMesh("models/level.obj", "level"),
                                            new BoxCollider({15.0f,6.0f,12.0f}));
  m_actors.push_back(std::move(floorActor));

  auto flor2Actor = std::make_unique<Actor>(this,
                                            new TexturedMesh("models/level.obj", "level"),
                                            new BoxCollider({15.0f,6.0f,12.0f}),
                                            ngl::Vec3(3.0f, -1.0f, 6.0f));
  m_actors.push_back(std::move(flor2Actor));

  auto wallActor = std::make_unique<Actor>(this,
                                           new TexturedMesh("models/level.obj", "level"),
                                           new BoxCollider({15.0f,6.0f,12.0f}),
                                           ngl::Vec3(14.0f, 4.0f, 11.0f));
  m_actors.push_back(std::move(wallActor));

}

void Scene::paintSkyBox()
{
  ( *ngl::ShaderLib::instance() )[ "SkyProgram" ]->use();
  m_skybox->paintGL(m_player.camera());
}
