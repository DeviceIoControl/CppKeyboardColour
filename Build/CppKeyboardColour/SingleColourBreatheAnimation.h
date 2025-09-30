#pragma once

#include "IAnimation.h"
#include "FrameCollection.h"

// Animation qui crée un effet de "respiration" (breathe) pour une seule couleur.
// La luminosité de la couleur augmente puis diminue.
class SingleColourBreatheAnimation : public IAnimation
{
public:
    // Constructeur : prend la couleur cible pour l'animation.
    SingleColourBreatheAnimation(const Colour& targetColour);

    // Retourne le nom de l'animation.
    std::wstring GetName() const override;

    // Récupère une image de l'animation à un index donné.
    std::optional<Frame> GetFrame(uint32_t idx) override;

    // Indique si l'animation est supportée par un type de clavier donné.
    bool IsSupportedKB(KeyboardType kbType) const override;

    // Retourne le nombre total d'images dans l'animation.
    uint32_t Size() const override;

private:
    // Collection d'images (frames) qui composent l'animation.
    FrameCollection m_frames;

    // Ajoute une image à la collection.
    void AddFrame(const Frame& frame);

    // Génère les images pour l'effet de respiration.
    void GenerateBreathe(const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs);
};