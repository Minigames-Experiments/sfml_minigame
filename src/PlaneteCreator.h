#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <unordered_map>

#include "PlaneteMap.h"
#include "PlaneteTextureInfos.h"

/**
 * @brief Classe qui permet de créer des cartes de planetes
 *
 */
class PlaneteCreator {
public:
  /**
   * @brief Charge toutes les textures du monde a partir d'un fichier de
   * description.
   *
   * @param world_textures_description_file chemin vers le fichier de
   * description
   */
  void loadSprites(const std::string &world_textures_description_file);

  /**
   * @brief Methode pour créer une planete
   *
   * @param radius_tiles rayon de la planete
   * @return PlaneteMap
   */
  PlaneteMap createPlaneteMap(int radius_tiles);

private:
  // Structure qui stock les textures des planètes par nom de fichier
  std::unordered_map<std::string, PlaneteTextureInfos> textures_map_;
  // Structure qui stock les textures des planètes par type
  std::unordered_map<TextureType, std::vector<PlaneteTextureInfos *>>
      textures_map_by_type_;

private:
  /**
   * @brief Charge toutes les textures depuis un ficher description.txt
   *
   * @param texture_description_file chemin vers le ficjier de description
   */
  void loadTextures(const std::string &texture_description_file);
};
