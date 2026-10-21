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
- Cofres con sprites de la web; los grandes se abren quedándose a su lado 3,5 s. Rocas indestructibles en la grieta.
- Bomba (0,6 % de las bajas): daña a todos los enemigos cercanos. Jefes con ataques de la web (embestida, salto, lluvia, rayos, ráfaga, nova) y furia al 50 % de PS. Pokémon shiny salvajes (1/4096): al derrotarlos se desbloquean. PS en número y clima más visible con indicador.
- Ataques evolucionados (solo + coop): con el ataque al nivel máx. y su mejora requerida ya elegida en la partida, aparece una carta dorada que lo evoluciona (nuevo nombre y estadísticas).
- Progresión permanente: mejoras, gacha de 9 generaciones con garantía, colección de Pokémon, vetos y movimiento inicial.
- Música (aldea, bosque, jefe) y efectos sintetizados por software.
- Idiomas: español, inglés, francés, italiano, portugués (BR) y chino simplificado/tradicional (selección al inicio; el chino usa la fuente del sistema). Textos de `js/lang/*.js` vía `tools/export_lang.js`.
- Tienda de Kecleon (menta, cápsulas de habilidad y 8 MT diarias según la fecha de la consola), naturaleza y habilidad por Pokémon (Pokémon → Detalles: menta, cápsulas y MT), «Segundo movimiento inicial» y cooperativo con espectador del compañero. Habilidades: subconjunto de efectos (`AbTerm` en `gamedata.h`); las demás dan +8 % con su tipo. Sin probar en consola real. Pokédex por regiones, gacha con máquina tragaperras, probabilidades y brillantes (1 %), misiones diarias y semanales.
- Eventos: ladrón de monedas (Meowth; Gholdengo con ticket ×10) grieta con arena de legendario y Pokémon perdido (llévalo a la marca verde; también en cooperativo).
- Pantalla táctil: joystick flotante; sólo dispara el ataque activo (o grupo fusionado) y X/Y/B/A lo cambian (START = pausa/ordenar).
- Vínculo/fusión tras vencer a un legendario en la grieta (fusiona 2 ataques o añade uno a un grupo; se disparan a la vez).
- Clima (sol, lluvia, tormenta de arena, nevada, niebla) con bonos/penalizaciones por tipo y por bioma.
- Estilo de la web: fuente pixel original (Pixelify Sans, con ★ ♥ ◀ ▶ propios), iconos pixel-art en los menús, paneles enmarcados, flechas ◀ ▶ para cambiar de página, contador de tickets en el gacha y ticket violeta (= 10 normales; botón propio ×10 violeta). Mejoras permanentes por Pokémon (sólo afectan al compañero elegido) y objetos traducidos.
- Logros con medallas (colección, supervivencia, combate, grietas, un logro por legendario) con premios automáticos.
- Cooperativo local 3DS↔3DS para 2 jugadores (botón Coop; red inalámbrica local UDS, sin internet ni servidores). Las dos consolas ejecutan la misma simulación y sólo intercambian entradas (lockstep, 30 pasos/s, mismo build en ambas). Sin pausa manual; las mejoras se eligen en la pantalla inferior sin detener el juego; el compañero caído revive al subir de nivel el otro. Grieta: si uno entra, el otro es teletransportado (el legendario tiene más vida). Vínculo/fusión: la partida se pausa hasta que los dos hayan elegido. Sentencia de Arceus adaptada a dos jugadores (Arceus persigue al más cercano; termina cuando caen los dos). No probado en hardware.

## No incluido
Cooperativo online, nube, amigos, títulos/perfil, logros de grupo/objetos/arenas, nombres de Pokémon traducidos. Partida de 15 min (la web: 30); al llegar, empieza la Sentencia de Arceus (versión simplificada, sin cinemática saltable). Objetos equipables: los 11 de la web (cofres 8 %/50 %, jefes siempre; uno por partida).
Guardado en `sdmc:/3ds/pokesurvivor3ds.sav`.
