# Sous Menu Énigme (SDL2, C)

Projet éducatif et modulaire en C montrant un sous-menu Énigme (800x600) avec transitions vers un écran Quiz. Code compact et séparé en fonctions d'affichage, de gestion d'événements et de boutons pour faciliter l'apprentissage.

## Structure
- `src/main.c` : logique complète (états, rendu, événements, audio).
- `assets/` : ressources à fournir par l'étudiant (voir ci-dessous).

## Dépendances
- SDL2
- SDL2_ttf
- SDL2_mixer

## Ressources attendues (`assets/`)
- `background4.bmp` : image de fond (800x600 ou plus).
- `hover-button.mp3` : son bref pour le survol (fallback possible `hover.wav`).
- `sonican-quiz-background.mp3` : musique de suspense (battement de tambour).
- `Roboto-Regular.ttf` : police TTF (modifiable dans le code si besoin).

## Compilation (exemple MinGW)
```
gcc src/main.c -I<SDL2_include> -I<SDL2_ttf_include> -I<SDL2_mixer_include> -L<SDL2_lib> -lSDL2 -lSDL2_ttf -lSDL2_mixer -o enigme.exe
```
Placez les DLL SDL2/SDL2_ttf/SDL2_mixer à côté de l'exécutable ou dans le `PATH`.

## Utilisation
- Lancer `enigme.exe` : fenêtre 800x600 avec boutons QUIZ/PUZZLE.
- Survol : effet visuel + son bref.
- Clic QUIZ : passe à l'écran Quiz, démarre la musique, boutons A/B/C survolables/cliquables.
- Échap ou fermeture fenêtre : sortie propre (musique arrêtée).

## Points pédagogiques
- **Modularité** : fonctions dédiées (rendu du menu/quiz, gestion des événements, dessin des boutons, chargement/cleanup des assets).
- **État clair** : enum `Screen` pour piloter les écrans, variables booléennes pour la musique, struct `Assets` et `Button` pour regrouper les données.
- **Gestion des ressources** : init/quit SDL2, TTF, mixer, libération systématique des textures/sons/polices.
- **Interactions** : survol souris (visuel + son), clics détectés, sortie clavier (ESC).

## Extensions suggérées (exercices)
1. Implémenter la logique PUZZLE (nouvel écran ou pop-up).
2. Charger les questions/réponses depuis un fichier texte ou JSON.
3. Afficher un feedback correct/incorrect et un score.
4. Ajouter un timer visuel (barre ou compteur).
5. Adapter les couleurs/typo pour un thème pédagogique.

Le code est volontairement simple et académique pour un projet étudiant.
