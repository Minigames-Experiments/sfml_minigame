#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <list>
#include <memory>
#include <set>
#include <string>

//! Le type de la texture (GRASS=herbe, DIRT=terre, ROCK=roche, ...)
enum class TextureType {
  //! herbe
  GRASS,
  //! terre
  DIRT,
  //! roche
  ROCK,
  //! magma
  MAGMA,
};

//! position possibles de la texture
enum class TextureLocalisation {
  //! Texture de surface (herbe ...)
  SURFACE,
  //! Texture interne
  INNER,
};

/**
 * Contient toutes les informations relative à une texture d'une planète
 */
class PlaneteTextureInfos {
public:
  /**
   * @brief Premier constructeur de PlaneteTextureInfos.
   *
   * @param texture_file le chemin vers le fichier de texture
   * @param texture_type le type de texture (GRASS, ROCK, ...)
   * @param texture_localisations les localisations possible de la texture (en
   * surface, ...)
   */
  PlaneteTextureInfos(
      const std::string &texture_file, const TextureType &texture_type,
      const std::set<TextureLocalisation> &texture_localisations)
      : texture_file_(texture_file), texture_type_(texture_type),
        texture_localisations_(texture_localisations) {
    loadTexture();
  }

  /**
   * @brief Second constructeur qui prend des chaines de characteres pour les
   * descriptions de la texture. Ce constructeur est utilisé principalement pour
   * charger une texture depuis un fichier
   *
   * @param texture_file le chemin vers le fichier de texture
   * @param texture_type le type de texture en string (GRASS, ROCK, ...)
   * @param texture_localisations  les localisations possible de la texture en
   * string (en surface, ...)
   */
  PlaneteTextureInfos(const std::string &texture_file,
                      const std::string &texture_type,
                      const std::list<std::string> &texture_localisations)
      : texture_file_(texture_file) {
    loadTexture();
    texture_type_ = parseTextureType(texture_type);
    for (auto &loc_string : texture_localisations) {
      texture_localisations_.emplace(parseTextureLocalisation(loc_string));
    }
  }

  sf::Texture &texture() { return texture_; };

  std::string &texture_file() { return texture_file_; }

  TextureType &texture_type() { return texture_type_; }

  std::set<TextureLocalisation> &texture_localisations() {
    return texture_localisations_;
  }

private:
  /// variables privées
  //! chemin vers le fichier de texture
  std::string texture_file_;
  //! Le type de la texture (GRASS=herbe, DIRT=terre, ROCK=roche, ...)
  TextureType texture_type_;
  //! position possibles de la texture ()
  std::set<TextureLocalisation> texture_localisations_;

  sf::Texture texture_;

private:
  /// fonctions privées

  void loadTexture() {
    if (!texture_.loadFromFile(texture_file_)) {
      throw std::invalid_argument("Unknown texture file " + texture_file_);
    }
  }

  /**
   * @brief Convertie une chaine de caractere representant un type de structure
   * en enum
   *
   * @param types_string
   * @return TextureType
   */
  TextureType parseTextureType(const std::string &type_string) {
    if (type_string == "DIRT") {
      return TextureType::DIRT;
    } else if (type_string == "GRASS") {
      return TextureType::GRASS;
    } else if (type_string == "MAGMA") {
      return TextureType::MAGMA;
    } else if (type_string == "ROCK") {
      return TextureType::ROCK;
    } else if (type_string == "DIRT") {
      return TextureType::DIRT;
    } else {
      throw std::invalid_argument("Unknown texture type " + type_string);
    };
  }

  TextureLocalisation parseTextureLocalisation(const std::string &loc_string) {
    if (loc_string == "INNER") {
      return TextureLocalisation::INNER;
    } else if (loc_string == "SURFACE") {
      return TextureLocalisation::SURFACE;
    } else {
      throw std::invalid_argument("Unknown texture localisation " + loc_string);
    };
  }
};