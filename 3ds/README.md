# PokéSurvivor 3DS (reescritura nativa, en solitario)

Requisitos: devkitPro (`3ds-dev`), Node y Python con Pillow.

```
cd 3ds
node tools/export_game.js      # datos del juego web -> include/gamedata.h (movimientos, Pokémon, tipos, mejoras)
node tools/export_music.js     # partituras -> include/music.h
python3 tools/make_sprites.py  # romfs/gfx/pNNNN.t3x + include/spritemeta.h (966 Pokémon)
python3 tools/make_tiles.py    # romfs/gfx/tilesNN.t3x + include/tiles.h (21 biomas)
make                           # -> pokesurvivor3ds.3dsx
```

`romfs/gfx/` se genera (no está en git). Prueba: Azahar o `3dslink pokesurvivor3ds.3dsx` a la consola.
Para oír la música en consola real hace falta `sdmc:/3ds/dspfirm.cdc` (DSP1); sin él el juego va en silencio.

## Qué incluye
- Tabla de tipos y debilidades (18 tipos, multiplicadores del juego web, avisos «¡Eficaz!/Poco/Inmune»).
- 103 movimientos de 23 tipos de comportamiento, con 4 mejoras cada uno; cada Pokémon usa su movimiento inicial y los de sus tipos.
- Enemigos con comportamientos (perseguidor, embestida, a distancia, tanque, curandero, escudo, invocador, bombardero, rayo, zonas, abanico, saltador, corredor), jefes y mareas.
- Mapas por bioma con suelo, líquidos que dañan o frenan, árboles, rocas y cofres.
- Progresión permanente: mejoras, gacha de 9 generaciones con garantía, colección de Pokémon, vetos y movimiento inicial.
- Música (aldea, bosque, jefe) y efectos sintetizados por software.
- Pantalla táctil: joystick flotante, X/Y/B/A para lanzar y ordenar ataques (START = pausa/ordenar).

## No incluido
Cooperativo, nube, amigos, brillantes, clima, grietas/arenas, objetos equipables. Partida de 15 min (la web: 30).
Guardado en `sdmc:/3ds/pokesurvivor3ds.sav`.
