# PokéSurvivor 3DS

[Español](README.md) · English · [Français](README.fr.md)

A native Nintendo 3DS port by **Dan Franza**, based on the original game by JPTER78 and its contributors. Playable solo or in co-op.

**Coming soon:** a launcher-updater to start the game and make updates easier.

## Build

Requirements: devkitPro (`3ds-dev`), Node.js, and Python with Pillow.

```sh
cd 3ds
node tools/export_game.js      # web game data → include/gamedata.h
node tools/export_music.js     # scores → include/music.h
python3 tools/make_sprites.py  # sprites → romfs/gfx/ and include/spritemeta.h
python3 tools/make_tiles.py    # terrain → romfs/gfx/ and include/tiles.h
make                           # produces pokesurvivor3ds.3dsx
```

`romfs/gfx/` is generated and is not stored in Git. Test using Azahar or send the file to a console with `3dslink pokesurvivor3ds.3dsx`. On real hardware, music requires `sdmc:/3ds/dspfirm.cdc` (DSP1); without it, the game runs without sound.

## Features

- All 18 types, weaknesses, and effectiveness messages from the web game.
- 103 moves across 23 behavior types, each with four upgrades. Pokémon use their starting move and moves matching their types. A max-level move can evolve after its required upgrade has been selected, in solo or co-op.
- Enemies with varied behaviors, bosses, waves, wild shiny Pokémon, and biome-based maps. Liquids can damage or slow; large chests open after standing nearby for 3.5 seconds. A bomb may drop after a defeat and damage nearby enemies.
- Permanent progression, Pokémon collection, nine-generation gacha with a guarantee, starting move selection and move bans. Upgrades are specific to each Pokémon.
- Kecleon's shop offers mints, ability capsules, and eight daily TMs. Each Pokémon has a nature and ability. Only some ability effects are implemented; the others give +8% damage to moves of the Pokémon's type.
- Software-synthesized music and sound effects. Languages: Spanish, English, French, Italian, and Brazilian Portuguese. French Pokémon names are available.
- Events: coin-stealing Meowth, ticket-carrying Gholdengo, legendary rifts, and lost Pokémon to escort to a green marker.
- Three lower-screen pages show moves and status bars, held item and orbs, and a local map. In solo, orbs can be assigned to L and R. Move with the Circle Pad or D-pad; X/Y/B/A select the active move; START pauses and lets you reorder moves.
- After defeating a legendary in a rift, bonds can fuse moves so they fire together.
- Sun, rain, sandstorms, snow, and fog affect types and biomes.
- **Black market, exclusive to the 3DS version:** epic Pokémon cost 50,000 coins, legendary Pokémon 100,000, and Mewtwo and Mew 500,000; the game displays the shiny chance. Meowth reacts to a shiny.
- Daily and weekly missions, trophies and rewards. Completing a region's Pokédex, including legendaries, doubles that banner's shiny rate from 1% to 2%.
- Arceus's Judgment: Arceus can be hit but is invincible; a random Plate determines its type.

## Co-op and community server

Local co-op connects two nearby consoles wirelessly without a server. Both must run the same game version. They run the same simulation and exchange inputs at 30 steps per second. Upgrade cards can be selected without stopping play; bond choices pause the game. A fallen partner revives when the other levels up. Entering a rift brings both players into it.

**Co-op → Community servers** accepts a nickname, `host:port` address, and up to six favorites. Servers offer leaderboards and two-player online co-op: create a private room with a six-character code, join using a code, or search publicly for a compatible game version.

To host the server, from `3ds/`:

```sh
node server/server.js [port]
```

The default TCP port is `25570` and must be reachable by players. The server saves leaderboards in `server/ranking.json` and relays game data. Co-op still needs testing on real consoles.

## Limitations and save file

Cloud saves, friends, titles and profiles, and group/item/arena achievements are not included. A run lasts 15 minutes before the simplified Arceus's Judgment; the web game lasts 30 minutes. All eleven held items from the web game are present, with one held item per run.

The save file is `sdmc:/3ds/pokesurvivor3ds.sav`.

## Effects, options, and animations

- Projectiles and orbits use the web game's shapes and palettes. After changing `js/entities/vfx.js` or moves, run `tools/make_vfx.py` to regenerate `romfs/gfx/vfx.t3x` and `include/vfxmeta.h`.
- The **Options** menu offers language selection and an enhanced readability mode, which shows two larger items per page in the relevant menus.
- Attack animations use Attack, Shoot, or Charge according to the move. `tools/make_acts.py` generates `romfs/gfx/pNNNN{a,h,c}[s].t3x` and `include/actmeta.h`. If an animation is missing, the game uses Walk.

## Initial quiz and Halloween

Without a save file, a personality quiz suggests a starting Pokémon. From October 30 through November 2, based on the console clock, Halloween adds night maps, pumpkins, ghosts, candy, themed music, and a Ghost Pokémon banner. A solo run started during the event keeps it until the run ends; it is disabled in co-op.

Witch Gengar replaces Arceus at the end of a run. Kecleon sells three costumes — Gengar, Pikachu, and Umbreon — for 300 candies each; purchased costumes remain available. Their resources are generated by `tools/make_sprites.py`; costumed attacks use the walking animation.
