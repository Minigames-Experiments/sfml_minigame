#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "PlaneteCreator.h"

/**
 * @brief Classe principale qui gere le jeu
 *
 */
class GameController {
public:
  /**
   * @brief Methode qui lance le jeu. Cet appel est bloquant
   *
   */
  void startGame() {

    //! Etape 1: Charger les textures
    loadTextures();

    //! Etape 2: Creer la fenêtre de jeu
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Minigame!");

    //! Etape 3 Generer une planete
    int map_radius_tiles = 6; // rayon de la planete (peut être modifié)
    PlaneteMap planete_map =
        planete_creator_.createPlaneteMap(map_radius_tiles);
    planete_map.setPosition(432, 400 + map_radius_tiles * 64);

    //! Event loop
    while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {

        switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        default:
          break;
        }
      }

      //! On efface le contenu de la fenetre
      window.clear();

      //! On dessine le monde
      // planete_map.setRotation(25);
      // planete_map.rotate(25);
      // planete_map.setPosition(432, 60);
      planete_map.drawOn(window);

      //! on affiche la fenetre
      window.display();
    }
  }

  /**
   * @brief Methode qui charge toutes les textures
   */
  void loadTextures() {
    // chargement des textures du monde
    planete_creator_.loadSprites("textures/worlds/description.txt");

    // chargement des textures des personnages
    // TODO
  }

private:
  //! Classe qui permet de creer des planetes à une position donnée
  PlaneteCreator planete_creator_;
};