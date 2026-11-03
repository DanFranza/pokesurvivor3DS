# PokéSurvivor · Donjon Mystère

## PokéSurvivor 3DS

Portage Nintendo 3DS réalisé par **Dan Franza**, à partir du jeu original de JPTER78 et de ses contributeurs. Un launcher-updater arrive bientôt. [Documentation française du portage](3ds/README.fr.md) · [English documentation](3ds/README.en.md) · [Documentación en español](3ds/README.md).

**Téléchargement 3DS :** [jeu, licences et crédits (ZIP)](3ds/distribution/pokesurvivor3ds.zip). Décompressez l’archive et copiez le fichier `.3dsx` dans le dossier `3ds` de la carte SD.

**Version CIA expérimentale :** [jeu, licences et crédits (ZIP)](3ds/distribution/pokesurvivor3ds-cia.zip) · [CIA seul](3ds/distribution/pokesurvivor3ds.cia). Installation sur console compatible ; test sur console encore nécessaire.

[Version espagnole et anglaise d'origine de ce README](README.es.md) · [Traduction française de la licence](LICENSE.fr.md)

Jeu de survie de type bullet heaven avec des Pokémon, dans le style de Survivor.io et de Megabonk, avec des sprites de *Pokémon Donjon Mystère*, une dimension roguelike, **966 Pokémon des neuf générations**, des chromatiques et un gacha par région. La musique et les effets ont été composés pour le jeu.

HTML, CSS et JavaScript sans framework sur Canvas 2D. Sans compilation, sans dépendance et **entièrement local** : aucune connexion Internet n'est nécessaire pour jouer.

> **Auteur**
>
> Le code et la musique originale de PokéSurvivor ont été écrits par **Jonathan Piera Torregrosa**, propriétaire du compte JPTER78 et de pokesurvivor.com. Il indique avoir déposé auprès de Google la demande de retrait pour atteinte au droit d'auteur **4-2352000042234** concernant pokesurvivor.co.

> **Avertissement concernant les cryptomonnaies**
>
> PokéSurvivor ne possède **aucune cryptomonnaie, aucun jeton ni NFT officiel**, et l'auteur n'en a créé aucun. Tout jeton utilisant le nom du jeu a été créé par des tiers. L'auteur décline toute responsabilité concernant les achats, ventes ou investissements effectués dans ceux-ci. Rien ici ne constitue un conseil en investissement. Le jeu est gratuit et le restera.

## Jouer

Double-cliquez sur `index.html`. Créez un compte ou entrez en tant qu'invité, effectuez le test de personnalité et partez dans le donjon.

| Touche | Action |
|---|---|
| `W` `A` `S` `D` / flèches | Se déplacer |
| `1` `2` `3` `4` | Choisir l'attaque active |
| `Q` / `E` | Parcourir les attaques |
| `Échap` / `P` | Pause |

**Sur mobile ou tablette**, en mode paysage : posez le doigt n'importe où et faites-le glisser pour vous déplacer ; le joystick apparaît au point de contact. Touchez une attaque en bas pour la sélectionner et le bouton en haut à droite pour mettre en pause. Le jeu peut être installé comme application (« Ajouter à l'écran d'accueil »). Les **paramètres** permettent de régler le son, la qualité graphique et son mode automatique, les chiffres de dégâts, les secousses, les FPS et le compte.

Le Pokémon attaque automatiquement avec l'attaque active, ou avec toutes les attaques d'un **lien** : chaque légendaire vaincu permet de fusionner jusqu'à quatre attaques pour les lancer ensemble depuis un seul emplacement. Rochers, coffres et hautes herbes peuvent être détruits ; murs et arbres bloquent les projectiles ennemis. L'eau ralentit et la lave brûle, y compris les ennemis.

La carte contient des **autels de pouvoir**, des **sources de soin**, des **coffres verrouillés** — restez quelques secondes à proximité — et des **pièges** qui blessent aussi les ennemis. Une **faille** s'ouvre parfois : entrez-y pour combattre un **légendaire** dans une arène séparée.

Une **table des types** s'applique : par exemple, Écume inflige davantage de dégâts à Salamèche. Des effets **météo** apparaissent parfois — soleil, pluie, sable, neige et brouillard — et renforcent ou affaiblissent certains types.

Des **missions** quotidiennes et hebdomadaires rapportent tickets et pièces. Les **succès** donnent médailles et titres ; votre **profil** affiche vos trois Pokémon favoris, vos records et vos médailles. Pendant une partie, vous trouvez des **objets** comme les Restes et le Bandeau Choix ; vos attaques **évoluent** à leur niveau maximal. Les ennemis ont des comportements différents : ils soignent, créent des boucliers, appellent leur groupe ou préviennent leurs attaques par une marque au sol.

Les **améliorations** sont propres à chaque Pokémon. Le **gacha** utilise des **tickets** gagnés en jouant : tickets ×1 auprès de certains Pokémon et tickets ×10 auprès des boss et légendaires. Les tirages se font sur une machine à sous en pixel art.

Chaque ennemi a une chance sur 4 096 d'être **chromatique** : il brille, une flèche au bord de l'écran indique sa position et, si vous le battez, vous l'obtenez. Dans le gacha, un tirage sur 100 est chromatique. Dans la collection, choisissez votre partenaire normal ou chromatique.

La musique commence après le premier clic, les navigateurs empêchant sa lecture avant une interaction. Le volume et la coupure du son sont accessibles par le bouton du haut à droite ou dans le menu pause.

La sauvegarde est stockée dans le `localStorage` du navigateur : elle est perdue si les données du site sont effacées.

Le dossier `videos/` contient des enregistrements avec leur musique : combat contre un boss, capture d'un chromatique sauvage et obtention d'un chromatique au gacha.

## Sauvegarde dans le cloud et publication

- **Base de données Firebase :** les comptes avec nom et mot de passe ou Google permettent de retrouver sa partie sur plusieurs ordinateurs. Sans configuration, la sauvegarde reste uniquement dans le navigateur.
- **Jouer avec des amis, jusqu'à quatre, et classement :** avec un compte cloud, le menu **Amis** permet d'ajouter un joueur par son pseudo et de l'inviter ; le menu **Classement** présente les temps de survie en solo ou en groupe, par période, entre amis et par Pokémon.
- **Publication gratuite sur GitHub Pages :** [docs/PUBLICAR.md](docs/PUBLICAR.md).
- Si vous jouez sur deux ordinateurs simultanément ou hors ligne, les sauvegardes sont **fusionnées** : les collections sont réunies sans perdre de Pokémon ou de chromatique, les améliorations et statistiques gardent la valeur maximale, tandis que les pièces et le partenaire utilisent la version la plus récente. Les modifications de l'autre ordinateur arrivent en direct.

## Licence

Les six musiques ajoutées au port 3DS proviennent de Pixabay et ont leurs propres conditions : voir [crédits et licence des musiques](3ds/MUSIC-LICENSE.md).

Le code est soumis à la [licence PolyForm Noncommercial 1.0.0](LICENSE-NONCOMMERCIAL.md) depuis le 14 octobre 2026 : il peut être utilisé, étudié et modifié, mais **pas à des fins commerciales**, notamment pour vendre le jeu ou faire payer son contenu. Les versions jusqu'au commit `b297089` ont été publiées sous licence MIT. Les sprites, sous CC BY-NC 4.0, la police, sous OFL, et les marques Pokémon ont leurs propres conditions : voir [LICENSE](LICENSE), sa [traduction française](LICENSE.fr.md), la [traduction de la licence PolyForm](LICENSE-NONCOMMERCIAL.fr.md) et [CREDITS.md](CREDITS.md). Il s'agit d'un projet de fan sans but lucratif.

**Le seul site officiel est [pokesurvivor.com](https://pokesurvivor.com).** Le jeu est et restera gratuit ; si quelqu'un vous demande de payer, il ne s'agit pas de l'auteur.

## Structure

```text
index.html              écrans et ordre de chargement
css/style.css           interface de style Donjon Mystère
assets/pokemon/{dex}/   feuilles de sprites PMD (Idle, Walk, Attack, Shoot, Charge, Hurt, Faint)
assets/pokemon/{dex}/s/ les mêmes en version chromatique
assets/fonts/           Pixelify Sans (OFL) et sa version aux chiffres redessinés
js/
  net/      fonctions sociales, réseau, coopération et classement
  core/     utilitaires, sauvegarde, son, commandes, sprites et caméra
  data/     pokedex*, sprites-meta*, attaques, starters, ennemis,
            améliorations et partitions musicales
  world/    tuiles en pixel art, terrain, objets et collisions
  entities/ joueur, ennemis, projectiles, objets à ramasser et effets
  systems/  combat, apparition, montée de niveau et gacha
  ui/       icônes, interface, HUD, connexion, test, menus et classement
  game.js   déroulement et boucle principale
tools/      scripts régénérant les fichiers marqués d'un *
```

`*` indique un fichier généré. Pour les recréer, Python 3, Pillow et une connexion Internet sont nécessaires lors de l'opération :

```sh
python tools/fetch_sprites.py    # sprites normaux et chromatiques + js/data/sprites-meta.js
                                 # ~20 min ; reprise possible grâce à tools/cache/
python tools/fetch_pokedex.py    # js/data/pokedex.js
python tools/fetch_credits.py    # CREDITS.md
```

## Notes d'implémentation

- **Sprites PMD.** Les colonnes représentent les images d'animation et les lignes les huit directions : bas, bas-droite, droite, haut-droite, haut, haut-gauche, gauche et bas-gauche, vérifiées avec les fichiers `-Offsets.png`. Chaque animation ayant ses propres dimensions, elles sont alignées selon le **point d'ancrage au sol** extrait de `-Shadow.png`, afin d'éviter les sauts lors des attaques.
- **Coordonnées.** `(x, y)` correspond aux **pieds** de l'entité. Les collisions ont lieu au sol ; les projectiles se déplacent sur ce plan mais sont dessinés en hauteur, avec leur ombre en dessous.
- **Monde.** Les données de terrain et d'objets des blocs de 16 × 16 tuiles sont peu coûteuses et toujours générées. Leur image est produite en écrivant dans un `ImageData`, à la résolution du pixel art, uniquement pour les blocs visibles : environ 4 ms par bloc dans Chrome.
- **Performances.** Une grille spatiale des ennemis est reconstruite à chaque image. Avec 420 ennemis, simulation et rendu complet prennent environ 3 ms par image dans Chrome.
- **Métadonnées.** Elles sont en `.js` et non en `.json`, car `fetch()` est bloqué avec `file://`.
- **Chromatiques.** Ceux de SpriteCollab utilisent le même dessin avec une autre palette ; ils sont dans `s/`. Seuls 30 ont une géométrie différente, indiquée par le champ `sa`. Les feuilles PNG utilisent une palette exacte : même image, poids divisé par deux.
- **Audio.** Le synthétiseur Web Audio programme les notes 150 ms à l'avance et applique une réverbération par convolution. Les partitions sont dans `js/data/music.js`, dans un format texte propre au jeu. Les effets ont un intervalle minimal et un nombre de voix limité pour éviter la saturation lorsque 400 ennemis sont touchés simultanément.
- **Icônes.** Des matrices de caractères sont converties en canvas et en URL de données, toujours à des multiples entiers de leur taille afin de garder des pixels nets.

## Crédits et licence

Sprites de [SpriteCollab](https://github.com/PMDCollab/SpriteCollab), sous **CC BY-NC 4.0** : usage **non commercial** avec attribution. La liste des artistes figure dans [CREDITS.md](CREDITS.md). Pokémon appartient à Nintendo, Creatures Inc. et GAME FREAK. Ce projet de fan est sans but lucratif.
