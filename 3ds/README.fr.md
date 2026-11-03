# PokéSurvivor 3DS

[Español](README.md) · [English](README.en.md) · Français

Portage natif pour Nintendo 3DS réalisé par **Dan Franza**, à partir du jeu original de JPTER78 et de ses contributeurs. Jouable en solo ou en coopération.

**À venir :** un launcher-updater pour lancer le jeu et faciliter ses mises à jour.

## Télécharger le jeu

[Télécharger PokéSurvivor 3DS avec ses licences et crédits](distribution/pokesurvivor3ds.zip). Décompressez l’archive, puis copiez le fichier `pokesurvivor3ds.3dsx` dans le dossier `3ds` de la carte SD. Conservez les documents joints avec le jeu lorsque vous le partagez.

**Version CIA expérimentale :** [télécharger le CIA avec les licences et crédits](distribution/pokesurvivor3ds-cia.zip) ou [le fichier CIA seul](distribution/pokesurvivor3ds.cia). Installez-le avec un installateur CIA sur une console compatible. Cette version n’a pas encore été testée sur console.

## Compilation

Prérequis : devkitPro (`3ds-dev`), Node.js et Python avec Pillow.

```sh
cd 3ds
node tools/export_game.js      # données du jeu web → include/gamedata.h
node tools/export_music.js     # partitions → include/music.h
python3 tools/make_sprites.py  # sprites → romfs/gfx/ et include/spritemeta.h
python3 tools/make_tiles.py    # décors → romfs/gfx/ et include/tiles.h
make                           # produit pokesurvivor3ds.3dsx
```

Le répertoire `romfs/gfx/` est généré et n'est pas inclus dans Git. Pour tester le jeu, utiliser Azahar ou envoyer le fichier sur la console avec `3dslink pokesurvivor3ds.3dsx`. Sur console réelle, la musique nécessite `sdmc:/3ds/dspfirm.cdc` (DSP1) ; sans ce fichier, le jeu fonctionne sans son.

## Musique de partie

Depuis le menu principal, ouvre **Options**, passe à la deuxième page et touche **Musique** pour choisir une musique et en écouter un aperçu. Le choix est conservé et s'applique pendant les parties ; « Musique originale » rétablit la musique du jeu. Les morceaux ajoutés sont convertis en audio mono pour la 3DS : Route 101, Surf Theme, New Bark Town et Littleroot Town (Feora VGM / Yume), Pokémon League Night (Feora / Lucas Cooper) et Pallet Town. Les six pistes proviennent de Pixabay et ont leurs propres conditions : voir [leurs crédits, liens et conditions](MUSIC-LICENSE.md). Les versions fournies avec le jeu sont adaptées au format audio de la 3DS.

## Contenu

- Table des 18 types, faiblesses et messages d'efficacité du jeu web.
- 103 attaques réparties entre 23 comportements, chacune avec quatre améliorations. Chaque Pokémon utilise son attaque initiale et les attaques correspondant à ses types. Une attaque au niveau maximal peut évoluer si l'amélioration requise a été choisie, en solo comme en coopération.
- Ennemis aux comportements variés, boss, vagues, Pokémon chromatiques sauvages et décors par biome. Les liquides peuvent blesser ou ralentir ; les grands coffres s'ouvrent après 3,5 secondes à proximité. Une bombe peut apparaître après une élimination et blesser les ennemis proches.
- Progression permanente, collection, gacha des neuf générations avec garantie, choix de l'attaque initiale et exclusions d'attaques. Les améliorations sont propres à chaque Pokémon.
- Sac accessible depuis le menu principal : aromates, pilules et patchs Talent, CT possédées et progression des neuf Charmes Chroma. Deux ou trois lignes par page selon le mode de lisibilité ; les objets et CT s’utilisent depuis la collection.
- Boutique de Kecleon : menthes, capsules de talent et huit CT quotidiennes. Chaque Pokémon possède une nature et un talent. Seul un sous-ensemble des effets des talents est implémenté ; les autres donnent +8 % aux attaques de leur type.
- Musiques et effets sonores synthétisés. Langues : espagnol, anglais, français, italien et portugais brésilien. La traduction française des noms de Pokémon est disponible.
- Événements : Miaouss voleur de pièces, Gromago transportant des tickets, faille avec un légendaire et Pokémon perdu à ramener à la marque verte.
- Écran inférieur : trois pages pour les attaques et les barres, l'objet et les orbes, puis la carte des environs. En solo, les orbes sont affectables à L et R. Le stick ou la croix directionnelle déplace le personnage ; X/Y/B/A sélectionnent l'attaque active ; START met en pause et permet de réorganiser les attaques.
- Après une victoire contre un légendaire dans une faille, le lien permet de fusionner des attaques pour les lancer simultanément.
- Météo : soleil, pluie, tempête de sable, neige et brouillard, avec effets selon les types et les biomes.
- **Marché noir, propre à la version 3DS :** Pokémon épiques à 50 000 pièces, légendaires à 100 000 et Mewtwo ou Mew à 500 000 ; chance de chromatique indiquée dans le jeu. Le vendeur Miaouss réagit à une apparition chromatique.
- Missions quotidiennes et hebdomadaires, trophées et récompenses. Compléter le Pokédex d'une région, légendaires compris, double le taux de chromatiques de sa bannière de 1 % à 2 %.
- Jugement d'Arceus : Arceus peut être touché mais reste invincible ; une plaque aléatoire détermine son type.

## Coopération et serveur communautaire

La coopération locale relie deux consoles proches par communication sans fil, sans serveur. Les deux consoles doivent utiliser la même version. Elles exécutent la même simulation et échangent leurs commandes à 30 étapes par seconde. Les cartes d'amélioration sont choisies sans interrompre la partie ; les liens mettent la partie en pause pendant le choix. Un partenaire à terre revient lors de la montée de niveau de l'autre. L'entrée dans une faille transporte les deux joueurs.

Le menu **Coop → Serveurs communautaires** accepte un pseudo, une adresse `hôte:port` et jusqu'à six favoris. Il propose des classements et la coopération en ligne à deux : création d'une salle privée avec code à six caractères, entrée par code ou recherche publique par version compatible.

Pour héberger le serveur, depuis `3ds/` :

```sh
node server/server.js [port]
```

Le port TCP par défaut est `25570`. Il faut le rendre accessible aux joueurs. Le serveur conserve les classements dans `server/ranking.json` et relaie les données de la partie. La coopération doit encore être vérifiée sur consoles réelles.

## Limitations et sauvegarde

Le cloud, les amis, les titres et profils ainsi que les succès de groupe, d'objets et d'arènes ne sont pas inclus. Une partie dure 15 minutes avant le Jugement d'Arceus simplifié ; la version web dure 30 minutes. Les onze objets équipables du jeu web sont présents, à raison d'un objet tenu par partie.

La sauvegarde se trouve dans `sdmc:/3ds/pokesurvivor3ds.sav`.

## Effets, options et animations

- Les projectiles et les orbites utilisent les formes et palettes de la version web. Après modification de `js/entities/vfx.js` ou des attaques, `tools/make_vfx.py` régénère `romfs/gfx/vfx.t3x` et `include/vfxmeta.h`.
- Le menu **Options** propose la langue sur la première page, puis les modes « Normal » et « Lisibilité améliorée » ainsi que le choix de la musique sur la deuxième page. La lisibilité améliorée affiche deux éléments par page avec des caractères plus grands dans les menus concernés.
- Les animations d'attaque utilisent Attack, Shoot ou Charge selon l'attaque. `tools/make_acts.py` génère les fichiers `romfs/gfx/pNNNN{a,h,c}[s].t3x` et `include/actmeta.h`. En l'absence d'animation, le jeu utilise Walk.

## Test initial et Halloween

Sans sauvegarde, un test de personnalité propose le Pokémon initial. Du 30 octobre au 2 novembre selon l'horloge de la console, l'événement Halloween ajoute des cartes nocturnes, des citrouilles, des fantômes, des bonbons, une musique adaptée et une bannière de Pokémon Spectre. L'événement commencé en solo dure jusqu'à la fin de la partie et est désactivé en coopération.

Gengar sorcière remplace Arceus en fin de partie. Kecleon vend trois costumes — Gengar, Pikachu et Noctali — pour 300 bonbons chacun ; ils restent disponibles après achat. Les ressources correspondantes sont générées par `tools/make_sprites.py` ; les attaques costumées utilisent l'animation de marche.

## Réclamations relatives aux droits d’auteur

Pour toute réclamation DMCA concernant le port 3DS, contactez Dan Franza à [danfranza@proton.me](mailto:danfranza@proton.me).
