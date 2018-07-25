#ifndef TEXTUREPACK_H
#define TEXTUREPACK_H

#include <unordered_map>
#include <string>
#include <vector>
#include <ngl/Types.h>
#include <ngl/Singleton.h>

class TexturePack
{
  public :
    TexturePack() = default;
    TexturePack(const TexturePack &)=delete;
    ~TexturePack() = default;
    static bool loadJSON(const std::string &_filename);
    static bool activateTexturePack(const std::string &_tname);
  private :

    struct Texture
    {
      GLuint id;
      std::string name;
      GLint location;
      Texture(GLint _location, const std::string &_name, const std::string &_path);
    };
    struct Textures
    {
      std::vector<Texture> pack;
    };

    static std::unordered_map<std::string,Textures> s_textures;
};

#endif // TEXTUREPACK_H
