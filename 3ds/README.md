# PokéSurvivor 3DS (prototipo nativo)

Requisitos: devkitPro (`3ds-dev`) y Pillow.

```
cd 3ds
python3 tools/make_atlas.py   # atlas + include/sprites.h desde ../assets/pokemon
make                           # -> pokesurvivor3ds.3dsx
```

Prueba: Azahar (`azahar pokesurvivor3ds.3dsx`) o `3dslink` a la consola.

Controles: joystick flotante táctil (o Circle Pad/cruceta). X/Y/B/A lanzan los ataques asignados;
START abre la pantalla de ataques (tocar un botón y luego un ataque; también X/Y/B/A para elegir botón).
"Auto" dispara solo lo que esté listo. Cada nivel: mejora general o +30% a un ataque equipado.
Jefe cada 2 min; victoria a los 10 min. Mejor tiempo en `sdmc:/3ds/pokesurvivor3ds.sav`.
Presupuesto Old 3DS: todo estático (110 enemigos, 64 proyectiles, 160 gemas), atlas 1024×1024 RGBA5551 (2 MB).
