#include "PlaneteCreator.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <stdexcept>
#include <string>

#include "PlaneteTextureInfos.h"

#include <cmath>

void PlaneteCreator::loadSprites(
    const std::string &world_textures_description_file) {
  loadTextures(world_textures_description_file);
}

void PlaneteCreator::loadTextures(const std::string &texture_description_file) {

  std::ifstream infile(texture_description_file);

  // Parse the file line by line
  std::string line;
  int line_counter = 0;
  while (std::getline(infile, line)) {
    std::istringstream iss(line);

    std::list<std::string> tokens{std::istream_iterator<std::string>{iss},
                                  std::istream_iterator<std::string>{}};

    // Si la ligne est vide, on l'ignore
    if (tokens.empty()) {
      continue;
    }

    // Si la ligne n'a pas au moins un nom, un type et une localisation, lancer
    // une exception
    if (tokens.size() < 3) {
      throw std::invalid_argument("Ligne " + std::to_string(line_counter) +
                                  " invalide!");
    }

    // on récupère le chemin de la texture
    std::string texture_file = tokens.front();
    tokens.pop_front();

    // on récupère le type de la texture
    std::string texture_type = tokens.front();
    tokens.pop_front();

    // on stock les informations de la texture dans une hash map (appelee
    // unordered_map en c++11)
    textures_map_.emplace(
        texture_file, PlaneteTextureInfos(texture_file, texture_type, tokens));

    auto &texture = textures_map_.at(texture_file);

    if (textures_map_by_type_.count(texture.texture_type()) == 0) {
      textures_map_by_type_.emplace(
          texture.texture_type(), std::vector<PlaneteTextureInfos *>{&texture});
    } else {
      textures_map_by_type_[texture.texture_type()].push_back(&texture);
    }

    std::cout << "Texture added: " << texture_file << std::endl;
    line_counter++;
  }

  if (line_counter == 0) {
    throw std::invalid_argument("No textures has been loaded from " +
                                texture_description_file + "!!!");
  }
}

std::vector<PlaneteTextureInfos *> filterTextureLocalisation(
    const std::vector<PlaneteTextureInfos *> &textures_infos,
    TextureLocalisation loc) {
  std::vector<PlaneteTextureInfos *> filtred;
  std::copy_if(textures_infos.begin(), textures_infos.end(),
               std::back_inserter(filtred),
               [loc](PlaneteTextureInfos *texture) {
                 return texture->texture_localisations().count(loc) != 0;
               });
  return filtred;
}

PlaneteMap PlaneteCreator::createPlaneteMap(int radius_tiles) {
  double center = radius_tiles - 0.5;
  PlaneteMap map(radius_tiles * 2, radius_tiles * 2, 64);

  int surface = radius_tiles;     // altitude de la surface
  int inner_radius = surface - 1; // altitude maximum sous la surface
  float core_radius =
      (double)radius_tiles / 2; // altitude du noyau de la planete

  // On construit la planète en fonction de la distance au centre de chaque
  // sprite
  for (int x = 0; x < 2 * radius_tiles; x++) {
    for (int y = 0; y < 2 * radius_tiles; y++) {

      // distance de la tile courante par rapport au centre de la planète
      float radius =
          std::sqrt(std::pow(x - center, 2) + std::pow(y - center, 2));
      auto &sprite = map.getSpriteAt(x, y);

      // On met à jour la coordonnée pixelique du sprite
      sprite.setOrigin(map.spriteSize() / 2, map.spriteSize() / 2);
      float tile_view_pose_x = (x - radius_tiles) * map.spriteSize();
      float tile_view_pose_y = (y - radius_tiles) * map.spriteSize();
      sprite.setPosition(tile_view_pose_x, tile_view_pose_y);

      // On oriente la texture en fonction de sa position par rapport au centre
      // de la planete
      if ((x > y && x <= center) || (x > center && (2 * center - x) > y)) {
        // Top side
        sprite.rotate(0);
      } else if ((y <= center && (2 * center - x) <= y) ||
                 (y > center && (2 * center - x) < (2 * center - y))) {
        // Right side
        sprite.rotate(90);
      } else if ((x >= center && (2 * center - x) >= (2 * center - y)) ||
                 (x > (2 * center - y))) {
        // Bottom side
        sprite.rotate(180);
      } else {
        // Left side
        sprite.rotate(270);
      }

      // On applique la texture appropriée
      if (core_radius > 0 && radius <= core_radius) {
        sprite.setTexture(
            filterTextureLocalisation(textures_map_by_type_[TextureType::MAGMA],
                                      TextureLocalisation::INNER)
                .front()
                ->texture());
      } else if (radius < inner_radius) {
        sprite.setTexture(
            filterTextureLocalisation(textures_map_by_type_[TextureType::DIRT],
                                      TextureLocalisation::INNER)
                .front()
                ->texture());
      } else if (radius <= surface) {
        sprite.setTexture(
            filterTextureLocalisation(textures_map_by_type_[TextureType::DIRT],
                                      TextureLocalisation::SURFACE)
                .front()
                ->texture());
      }
    }
  }
  return std::move(map);
}
