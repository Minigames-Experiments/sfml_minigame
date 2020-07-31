#pragma once

#include <functional>
#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>
/**
 * @brief Class qui stocke tout les sprites d'une planète
 *
 */
class PlaneteMap {
public:
  /**
   * @brief Constructeur de PlaneteMap
   *
   * @param width largeur de la planete en sprites
   * @param height hauteur de la planete en sprites
   * @param sprite_size dimension d'un sprite en pixels
   */
  PlaneteMap(int width, int height, int sprite_size = 64)
      : width_(width), height_(height), sprite_size_(sprite_size),
        position_(0, 0), orientation_(0) {
    sprites_.resize(width * height);
    
  }

  /**
   * @brief Recupere le sprite à la position donnée
   *
   * @param x sprite index selon x
   * @param y sprite index selon y
   * @return sf::Sprite& reference sur le sprite
   */
  sf::Sprite &getSpriteAt(int x, int y) { return sprites_[y * width_ + x]; }

  void drawOn(sf::RenderTarget &target) {
    sf::Transform transform;
    transform.translate(position_);
    transform.rotate(orientation_);  

    for (auto &sprite : sprites_) {
        target.draw(sprite,transform);
    }
  }

  /**
   * @brief Set the planete position
   *
   * @param x
   * @param y
   */
  void setPosition(float x, float y) {
    position_ = sf::Vector2f(x, y); 
  }

/**
   * @brief Move the planete position
   *
   * @param x
   * @param y
   */
  void move(float x, float y) {
    position_ += sf::Vector2f(x, y); 
  }

  /**
   * @brief Set the planete orientation
   *
   * @param x
   * @param y
   */
  void setRotation(float yaw) {
    orientation_ = yaw;
  }

/**
   * @brief Rotate the planete orientation
   *
   * @param yaw
   */
  void rotate(float yaw) {
    orientation_+= yaw;
  }

  /**
   * @brief Retourne la dimension d'un sprite
   *
   * @return int
   */
  int spriteSize() { return sprite_size_; }

  /**
   * @brief Retourne la liste des sprites
   *
   * @return std::vector<sf::Sprite>&
   */
  std::vector<sf::Sprite> &sprites() { return sprites_; }

private:
  //! enssemble des sprites de la planete
  std::vector<sf::Sprite> sprites_;
  int width_;
  int height_;
  int sprite_size_;
  sf::Vector2f position_;
  float orientation_;
};