# PokéSurvivor 3DS (prototipo nativo)

Requisitos: devkitPro (`3ds-dev`) y Pillow.

```
cd 3ds
python3 tools/make_atlas.py   # atlas + include/sprites.h desde ../assets/pokemon
make                           # -> pokesurvivor3ds.3dsx
```

Prueba: Azahar (`azahar pokesurvivor3ds.3dsx`) o `3dslink` a la consola.

Controles: pantalla táctil (joystick flotante, cartas de mejora). Respaldo: Circle Pad/cruceta, A, START sale.
Presupuesto Old 3DS: todo estático (110 enemigos, 48 proyectiles, 160 gemas), atlas 1024×1024 RGBA5551 (2 MB, 3 starters + 24 ennemis en 4 tiers de BST).

Ataques por starter (hoja: perforante, fuego: rápido, agua: normal). Enemigos: tier 2 embiste, tier 3 dispara. Mejor tiempo en `sdmc:/3ds/pokesurvivor3ds.sav`.
