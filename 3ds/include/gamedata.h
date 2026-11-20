// GENERADO por tools/export_game.js — no editar a mano
#pragma once

#define NTYPES 18
static const char* TYPE_NAMES[NTYPES] = {"normal","fire","water","electric","grass","ice","fighting","poison","ground","flying","psychic","bug","rock","ghost","dragon","dark","steel","fairy"};
static const unsigned TYPE_RGB[NTYPES] = {0xb0a99f,0xff7b3d,0x4b9bff,0xffd33d,0x5fcb6a,0x7fe0e0,0xe0533d,0xb45ec4,0xd6b25c,0x9bb8ff,0xff5f9e,0xa3c43d,0xbfa96b,0x7a6bc4,0x6b58ff,0x6b5c52,0xa8b8c4,0xff9ed8};
static const float TYPE_CHART[NTYPES][NTYPES] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,0.6,0.3,1,1,0.6,1},
  {1,0.6,0.6,1,1.6,1.6,1,1,1,1,1,1.6,0.6,1,0.6,1,1.6,1},
  {1,1.6,0.6,1,0.6,1,1,1,1.6,1,1,1,1.6,1,0.6,1,1,1},
  {1,1,1.6,0.6,0.6,1,1,1,0.3,1.6,1,1,1,1,0.6,1,1,1},
  {1,0.6,1.6,1,0.6,1,1,0.6,1.6,0.6,1,0.6,1.6,1,0.6,1,0.6,1},
  {1,0.6,0.6,1,1.6,0.6,1,1,1.6,1.6,1,1,1,1,1.6,1,0.6,1},
  {1.6,1,1,1,1,1.6,1,0.6,1,0.6,0.6,0.6,1.6,0.3,1,1.6,1.6,0.6},
  {1,1,1,1,1.6,1,1,0.6,0.6,1,1,1,0.6,0.6,1,1,0.3,1.6},
  {1,1.6,1,1.6,0.6,1,1,1.6,1,0.3,1,0.6,1.6,1,1,1,1.6,1},
  {1,1,1,0.6,1.6,1,1.6,1,1,1,1,1.6,0.6,1,1,1,0.6,1},
  {1,1,1,1,1,1,1.6,1.6,1,1,0.6,1,1,1,1,0.3,0.6,1},
  {1,0.6,1,1,1.6,1,0.6,0.6,1,0.6,1.6,1,1,0.6,1,1.6,0.6,0.6},
  {1,1.6,1,1,1,1.6,0.6,1,0.6,1.6,1,1.6,1,1,1,1,0.6,1},
  {0.3,1,1,1,1,1,1,1,1,1,1.6,1,1,1.6,1,0.6,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1.6,1,0.6,0.3},
  {1,1,1,1,1,1,0.6,1,1,1,1.6,1,1,1.6,1,0.6,1,0.6},
  {1,0.6,0.6,0.6,1,1.6,1,1,1,1,1,1,1.6,1,1,1,0.6,1.6},
  {1,0.6,1,1,1,1,1.6,0.6,1,1,1,1,1,1,1.6,1.6,0.6,1},
};

enum { NK_ = 39 };
enum { K_CD=0,K_DMG=1,K_SPEED=2,K_COUNT=3,K_SPREAD=4,K_PIERCE=5,K_LIFE=6,K_SIZE=7,K_RADIUS=8,K_ARC=9,K_KNOCK=10,K_WIDTH=11,K_DUR=12,K_RATE=13,K_RANGE=14,K_AMOUNT=15,K_STACKS=16,K_CHARGE=17,K_PULL=18,K_BOUNCE=19,K_SLOW=20,K_STUN=21,K_HOMING=22,K_BURN=23,K_POISON=24,K_HEX=25,K_DRAIN=26,K_ZAP=27,K_SHRED=28,K_NOITEM=29,K_PUDDLE=30,K_PR=31,K_SPLASH=32,K_BOOST=33,K_CRITUP=34,K_MINCD=35,K_COST=36,K_WX=37,K_SHIELD=38 };
enum { MK_PROJECTILE=0,MK_MELEE=1,MK_BEAM=2,MK_ORBIT=3,MK_NOVA=4,MK_AURA=5,MK_BUFF=6,MK_BOOMERANG=7,MK_CHAIN=8,MK_MINE=9,MK_METEOR=10,MK_TURRET=11,MK_DASH=12,MK_TRAIL=13,MK_CONE=14,MK_HOMING=15,MK_BOUNCE=16,MK_CHARGE=17,MK_SPIN=18,MK_QUAKE=19,MK_VORTEX=20,MK_SHOVE=21,MK_STUN=22,MK_TREMOR=23,MK_WAVE=24,MK_CROSS=25,MK_STORM=26,MK_PUNCH=27,MK_SCISSOR=28,MK_BLITZ=29,MK_LEAP=30,MK_GUARD=31,MK_REST=32,MK_SCREEN=33,MK_DECOY=34,MK_BOOM=35,MK_WEATHER=36 };
enum { ST_ATK=0,ST_PATK=1,ST_SATK=2,ST_SPD=3,ST_DEF=4,ST_REGEN=5 };
struct UpMod { unsigned char key, op; float v; };   // op 0 ×, 1 +, 2 =
struct MoveUp { UpMod m[4]; unsigned char n; const char* text; };
struct MoveDef { const char* name; const char* desc; unsigned char type, kind, cat, stat; float v[NK_]; MoveUp ups[4]; };
#define NMOVES 176
static const MoveDef MOVES[NMOVES] = {
  {"Placaje","Embiste en arco a todo lo que tengas delante.",0,1,0,0,{0.5,16,0,0,0,0,0,0,60,2.13,90,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // tackle
  {"Ataque Rápido","Cruzas como un rayo hacia el enemigo y golpeas todo el camino.",0,12,0,0,{0.75,20,0,0,0,0,0,0,110,0,40,34,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% distancia"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.6},{11,0,1.4}},2,"+60% daño y más ancho"}}},  // quick-attack
  {"Danza Espada","No hace daño: acumula ATAQUE (físico) mientras esté activo.",0,6,2,1,{0.85,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0.13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{16,1,1}},1,"+1 acumulación máxima"},{{{15,0,1.4}},1,"+40% potencia"},{{{12,0,1.5}},1,"+50% duración"},{{{16,1,1},{15,0,1.4}},2,"+1 acumulación y +40% potencia"}}},  // swords-dance
  {"Maquinación","No hace daño: acumula ATAQUE ESPECIAL mientras esté activo.",0,6,2,2,{0.85,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0.13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{16,1,1}},1,"+1 acumulación máxima"},{{{15,0,1.4}},1,"+40% potencia"},{{{12,0,1.5}},1,"+50% duración"},{{{16,1,1},{15,0,1.4}},2,"+1 acumulación y +40% potencia"}}},  // nasty-plot
  {"Agilidad","No hace daño: acumula VELOCIDAD mientras esté activo.",0,6,2,3,{0.85,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0.1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{16,1,1}},1,"+1 acumulación máxima"},{{{15,0,1.4}},1,"+40% potencia"},{{{12,0,1.5}},1,"+50% duración"},{{{16,1,1},{15,0,1.4}},2,"+1 acumulación y +40% potencia"}}},  // agility
  {"Fortaleza","No hace daño: acumula DEFENSA mientras esté activo.",0,6,2,4,{0.85,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0.07,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{16,1,1}},1,"+1 acumulación máxima"},{{{15,0,1.4}},1,"+40% potencia"},{{{12,0,1.5}},1,"+50% duración"},{{{16,1,1},{15,0,1.4}},2,"+1 acumulación y +40% potencia"}}},  // harden
  {"Ascuas","Bola de fuego al enemigo más cercano.",1,0,1,0,{0.52,18,310,1,0.12,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // ember
  {"Lanzallamas","Chorro de llamas en abanico corto que quema.",1,14,1,0,{0.7,7,380,7,0,1,0.42,6,0,0.9,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,3}},1,"+3 disparos"},{{{1,0,1.4}},1,"+40% daño"},{{{6,0,1.3}},1,"+30% alcance"},{{{3,1,3},{5,1,1}},2,"+3 disparos y +1 perforación"}}},  // flamethrower
  {"Giro Fuego","Llamas que giran a tu alrededor. Defensa constante.",1,3,1,0,{0.3,14,2.4,3,0,0,0,9,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 orbe"},{{{1,0,1.55}},1,"+55% daño"},{{{8,0,1.25},{2,0,1.35}},2,"+25% radio y gira más rápido"},{{{3,1,1},{1,0,1.55}},2,"+1 orbe y +55% daño"}}},  // fire-spin
  {"Onda Ígnea","Explota en llamas en todas las direcciones.",1,4,1,0,{1.25,13,250,10,0,1,1.1,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,4}},1,"+4 proyectiles"},{{{1,0,1.4}},1,"+40% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,4},{5,1,1}},2,"+4 proyectiles y +1 perforación"}}},  // heat-wave
  {"Pistola Agua","Chorro perforante. Fiable a cualquier distancia.",2,0,1,0,{0.44,14,350,1,0.1,1,1.5,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // water-gun
  {"Burbuja","Burbujas en abanico que ralentizan a quien tocan.",2,4,1,0,{1,9,210,8,0,0,1.3,8,0,0,0,0,0,0,0,0,0,0,0,0,0.45,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,4}},1,"+4 proyectiles"},{{{1,0,1.4}},1,"+40% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,4},{5,1,1}},2,"+4 proyectiles y +1 perforación"}}},  // bubble
  {"Hidrobomba","Cañonazo de agua lento pero devastador.",2,2,1,0,{1.5,29,0,0,0,0,0,0,250,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // hydro-pump
  {"Acua Aro","No hace daño: acumula REGENERACIÓN de vida.",2,6,2,5,{0.9,0,0,0,0,0,0,0,0,0,0,0,8,0,0,1.6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{16,1,1}},1,"+1 acumulación máxima"},{{{15,0,1.4}},1,"+40% potencia"},{{{12,0,1.5}},1,"+50% duración"},{{{16,1,1},{15,0,1.4}},2,"+1 acumulación y +40% potencia"}}},  // aqua-ring
  {"Látigo Cepa","Látigos de largo alcance en arco amplio.",4,1,0,0,{0.62,19,0,0,0,0,0,0,85,1.63,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // vine-whip
  {"Hoja Afilada","Dos hojas que van y vuelven cortando a la ida y a la vuelta.",4,7,0,0,{0.9,10,330,2,0.5,0,0,6,210,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 bumerán"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% alcance"},{{{3,1,1},{1,0,1.4}},2,"+1 bumerán y +40% daño"}}},  // razor-leaf
  {"Tormenta Floral","Un ciclón de hojas gira amplio a tu alrededor.",4,3,1,0,{0.26,14,2.6,4,0,0,0,8,74,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 orbe"},{{{1,0,1.55}},1,"+55% daño"},{{{8,0,1.25},{2,0,1.35}},2,"+25% radio y gira más rápido"},{{{3,1,1},{1,0,1.55}},2,"+1 orbe y +55% daño"}}},  // leaf-storm
  {"Hierba Lazo","Raíces que atrapan y machacan todo lo que tienes cerca.",4,5,1,0,{0.55,9,0,0,0,0,0,0,76,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{8,0,1.3}},1,"+30% radio"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.7}},1,"Golpea un 40% más a menudo"},{{{8,0,1.3},{1,0,1.5}},2,"+30% radio y +50% daño"}}},  // giga-drain
  {"Impactrueno","Descarga rapidísima que atraviesa varios enemigos.",3,0,1,0,{0.4,13,480,1,0.08,2,1.1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // thunder-shock
  {"Chispazo","Campo eléctrico permanente alrededor de ti.",3,5,1,0,{0.45,8,0,0,0,0,0,0,70,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{8,0,1.3}},1,"+30% radio"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.7}},1,"Golpea un 40% más a menudo"},{{{8,0,1.3},{1,0,1.5}},2,"+30% radio y +50% daño"}}},  // discharge
  {"Rayo","Un rayo que salta de un enemigo a otro.",3,8,1,0,{0.95,21,0,4,0,0,0,0,140,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,2}},1,"+2 saltos"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,2},{1,0,1.4}},2,"+2 saltos y +40% daño"}}},  // thunderbolt
  {"Confusión","Onda que persigue sola a su objetivo.",10,0,1,0,{0.58,13,280,1,0.1,0,2.2,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // confusion
  {"Psicorrayo","Rayo psíquico ancho y contundente.",10,2,1,0,{1.15,17,0,0,0,0,0,0,215,0,0,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // psybeam
  {"Psíquico","Estallido mental radial que busca enemigos.",10,4,1,0,{1.35,10,230,12,0,1,1.6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,4}},1,"+4 proyectiles"},{{{1,0,1.4}},1,"+40% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,4},{5,1,1}},2,"+4 proyectiles y +1 perforación"}}},  // psychic
  {"Residuos","Lodo tóxico que envenena al impactar.",7,0,1,0,{0.6,17,290,1,0.12,0,1.5,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // sludge
  {"Disparo Lodo","Salpica lodo alrededor y ralentiza.",8,4,1,0,{1.1,11,200,7,0,0,1,9,0,0,0,0,0,0,0,0,0,0,0,0,0.4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,4}},1,"+4 proyectiles"},{{{1,0,1.4}},1,"+40% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,4},{5,1,1}},2,"+4 proyectiles y +1 perforación"}}},  // mud-shot
  {"Tornado","Remolinos de viento que te escoltan.",9,3,1,0,{0.26,13,2.8,3,0,0,0,8,72,0,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 orbe"},{{{1,0,1.55}},1,"+55% daño"},{{{8,0,1.25},{2,0,1.35}},2,"+25% radio y gira más rápido"},{{{3,1,1},{1,0,1.55}},2,"+1 orbe y +55% daño"}}},  // gust
  {"Ataque Ala","Barrido de alas amplio que empuja.",9,1,0,0,{0.55,17,0,0,0,0,0,0,73,2.38,70,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // wing-attack
  {"Golpe Cuerpo","Placaje con todo el peso: lento, corto y brutal.",0,1,0,0,{0.95,36,0,0,0,0,0,0,58,2.75,140,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // body-slam
  {"Vozarrón","Onda sonora que sale en todas direcciones.",0,4,1,0,{1.15,12,260,9,0,1,0.9,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,4}},1,"+4 proyectiles"},{{{1,0,1.4}},1,"+40% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,4},{5,1,1}},2,"+4 proyectiles y +1 perforación"}}},  // hyper-voice
  {"Picotazo Veneno","Aguijón rápido que envenena.",7,0,0,0,{0.34,8,420,1,0.08,0,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // poison-sting
  {"Tóxico","Vas dejando charcos de veneno que intoxican a quien los pisa.",7,13,1,0,{0.3,6,0,0,0,0,0,0,26,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{12,0,1.4}},1,"+40% duración"},{{{8,0,1.3}},1,"Charcos un 30% más grandes"},{{{1,0,1.5},{8,0,1.3}},2,"+50% daño y +30% radio"}}},  // toxic
  {"Terratemblor","Sacude el suelo: daña y frena a lo cercano.",8,5,0,0,{0.7,11,0,0,0,0,0,0,80,0,0,0,0,0,0,0,0,0,0,0,0.35,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{8,0,1.3}},1,"+30% radio"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.7}},1,"Golpea un 40% más a menudo"},{{{8,0,1.3},{1,0,1.5}},2,"+30% radio y +50% daño"}}},  // bulldoze
  {"Picadura","Mordisco rápido en arco corto.",11,1,0,0,{0.42,13,0,0,0,0,0,0,55,2,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // bug-bite
  {"Disparo Demora","Deja telarañas en el suelo que atrapan y frenan mucho al que las pisa.",11,9,0,0,{1.1,14,0,2,0,0,0,0,56,0,0,0,7,0,0,0,0,0,0,0,0.6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 mina"},{{{1,0,1.5}},1,"+50% daño"},{{{8,0,1.3}},1,"+30% radio de explosión"},{{{3,1,1},{0,0,0.75}},2,"+1 mina y -25% recarga"}}},  // string-shot
  {"Zumbido","Vibración constante que machaca lo cercano.",11,5,1,0,{0.45,8,0,0,0,0,0,0,66,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{8,0,1.3}},1,"+30% radio"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.7}},1,"Golpea un 40% más a menudo"},{{{8,0,1.3},{1,0,1.5}},2,"+30% radio y +50% daño"}}},  // bug-buzz
  {"Lanzarrocas","Pedrusco pesado que empuja al enemigo.",12,0,0,0,{0.7,24,260,1,0.12,0,1.4,9,0,0,90,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // rock-throw
  {"Avalancha","Caen rocas del cielo sobre los enemigos cercanos.",12,10,0,0,{1.3,21,0,3,0,0,0,0,46,0,50,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 meteoro"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{3,1,2},{0,0,0.8}},2,"+2 meteoros y -20% recarga"}}},  // rock-slide
  {"Rayo Hielo","Rayo helado que congela casi del todo.",5,2,1,0,{1.1,20,0,0,0,0,0,0,220,0,0,30,0,0,0,0,0,0,0,0,0.7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // ice-beam
  {"Nieve Polvo","Ventisca a tu alrededor que ralentiza.",5,5,1,0,{0.55,8,0,0,0,0,0,0,76,0,0,0,0,0,0,0,0,0,0,0,0.45,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{8,0,1.3}},1,"+30% radio"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.7}},1,"Golpea un 40% más a menudo"},{{{8,0,1.3},{1,0,1.5}},2,"+30% radio y +50% daño"}}},  // powder-snow
  {"Golpe Kárate","Golpe seco y potente al frente.",6,1,0,0,{0.5,22,0,0,0,0,0,0,63,1.5,110,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // karate-chop
  {"Esfera Aural","Esfera de energía que nunca falla.",6,0,1,0,{0.62,17,300,1,0.1,0,2,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // aura-sphere
  {"Lengüetazo","Lametazo espectral que paraliza un poco.",13,1,0,0,{0.48,14,0,0,0,0,0,0,60,2.25,0,0,0,0,0,0,0,0,0,0,0.4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // lick
  {"Bola Sombra","Esfera oscura que atraviesa a varios.",13,0,1,0,{0.66,19,280,1,0.1,2,1.6,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // shadow-ball
  {"Furia Dragón","Llamarada dracónica en línea recta.",14,2,1,0,{1,24,0,0,0,0,0,0,230,0,0,34,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // dragon-rage
  {"Danza Dragón","No hace daño: acumula ATAQUE (físico) más rápido que Danza Espada.",14,6,2,1,{0.7,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0.11,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{16,1,1}},1,"+1 acumulación máxima"},{{{15,0,1.4}},1,"+40% potencia"},{{{12,0,1.5}},1,"+50% duración"},{{{16,1,1},{15,0,1.4}},2,"+1 acumulación y +40% potencia"}}},  // dragon-dance
  {"Viento Feérico","Brisa mágica en todas direcciones.",17,4,1,0,{1,11,230,10,0,0,1.2,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,4}},1,"+4 proyectiles"},{{{1,0,1.4}},1,"+40% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,4},{5,1,1}},2,"+4 proyectiles y +1 perforación"}}},  // fairy-wind
  {"Brillo Mágico","Destello a tu alrededor.",17,5,1,0,{0.5,9,0,0,0,0,0,0,72,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{8,0,1.3}},1,"+30% radio"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.7}},1,"Golpea un 40% más a menudo"},{{{8,0,1.3},{1,0,1.5}},2,"+30% radio y +50% daño"}}},  // dazzling-gleam
  {"Garra Metal","Zarpazo de acero en arco.",16,1,0,0,{0.5,18,0,0,0,0,0,0,63,2,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // metal-claw
  {"Foco Resplandor","Rayo de luz metálica que perfora.",16,2,1,0,{1.05,23,0,0,0,0,0,0,220,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // flash-cannon
  {"Mordisco","Dentellada rápida que hace retroceder.",15,1,0,0,{0.45,17,0,0,0,0,0,0,58,1.88,70,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // bite
  {"Pulso Umbrío","Onda de energía oscura en todas direcciones.",15,4,1,0,{1.15,14,240,10,0,1,1.1,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,4}},1,"+4 proyectiles"},{{{1,0,1.4}},1,"+40% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,4},{5,1,1}},2,"+4 proyectiles y +1 perforación"}}},  // dark-pulse
  {"Tinieblas","Una sombra te rodea y consume lo cercano.",15,5,1,0,{0.5,9,0,0,0,0,0,0,72,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{8,0,1.3}},1,"+30% radio"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.7}},1,"Golpea un 40% más a menudo"},{{{8,0,1.3},{1,0,1.5}},2,"+30% radio y +50% daño"}}},  // night-shade
  {"Huesomerang","Un hueso que va y vuelve golpeando fuerte.",8,7,0,0,{0.95,16,300,1,0,0,0,8,230,0,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 bumerán"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% alcance"},{{{3,1,1},{1,0,1.4}},2,"+1 bumerán y +40% daño"}}},  // bonemerang
  {"Psicocorte","Cuchillas psíquicas que vuelven a ti.",10,7,0,0,{0.8,9,360,2,0.6,0,0,7,200,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 bumerán"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% alcance"},{{{3,1,1},{1,0,1.4}},2,"+1 bumerán y +40% daño"}}},  // psycho-cut
  {"Púas","Siembra púas que estallan al pisarlas.",8,9,0,0,{1.2,18,0,2,0,0,0,0,60,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 mina"},{{{1,0,1.5}},1,"+50% daño"},{{{8,0,1.3}},1,"+30% radio de explosión"},{{{3,1,1},{0,0,0.75}},2,"+1 mina y -25% recarga"}}},  // spikes
  {"Púas Tóxicas","Púas venenosas que envenenan mucho al estallar.",7,9,0,0,{1.1,11,0,2,0,0,0,0,56,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 mina"},{{{1,0,1.5}},1,"+50% daño"},{{{8,0,1.3}},1,"+30% radio de explosión"},{{{3,1,1},{0,0,0.75}},2,"+1 mina y -25% recarga"}}},  // toxic-spikes
  {"Granizo","Bolas de hielo caen sobre los enemigos y los frenan.",5,10,1,0,{1.2,18,0,4,0,0,0,0,40,0,0,0,0,0,0,0,0,0,0,0,0.4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 meteoro"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{3,1,2},{0,0,0.8}},2,"+2 meteoros y -20% recarga"}}},  // hail
  {"Puño Meteoro","Dos meteoros de acero que aplastan donde caen.",16,10,0,0,{1.4,24,0,2,0,0,0,0,48,0,70,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 meteoro"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{3,1,2},{0,0,0.8}},2,"+2 meteoros y -20% recarga"}}},  // meteor-mash
  {"Fuego Fatuo","Deja una llama flotante que dispara sola y quema.",1,11,1,0,{3.5,15,300,1,0,0,0,7,0,0,0,0,6,0.55,300,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.5}},1,"+50% daño"},{{{13,0,0.74}},1,"Dispara un 35% más rápido"},{{{3,1,1}},1,"+1 a la vez"},{{{12,0,1.5},{1,0,1.4}},2,"+50% duración y +40% daño"}}},  // will-o-wisp
  {"Sustituto","Un muñeco que se queda disparando por ti.",0,11,0,0,{4,14,320,1,0,0,0,6,0,0,0,0,6,0.4,280,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.5}},1,"+50% daño"},{{{13,0,0.74}},1,"Dispara un 35% más rápido"},{{{3,1,1}},1,"+1 a la vez"},{{{12,0,1.5},{1,0,1.4}},2,"+50% duración y +40% daño"}}},  // substitute
  {"Golpe Aéreo","Te lanzas en picado y cortas todo lo que cruzas.",9,12,0,0,{0.75,18,0,0,0,0,0,0,120,0,60,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% distancia"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.6},{11,0,1.4}},2,"+60% daño y más ancho"}}},  // aerial-ace
  {"Rueda Fuego","Corres envuelto en fuego y dejas un rastro de llamas.",1,13,0,0,{0.28,10,0,0,0,0,0,0,28,0,0,0,2.6,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{12,0,1.4}},1,"+40% duración"},{{{8,0,1.3}},1,"Charcos un 30% más grandes"},{{{1,0,1.5},{8,0,1.3}},2,"+50% daño y +30% radio"}}},  // flame-wheel
  {"Rayo Burbuja","Chorro de burbujas en abanico corto que frena.",2,14,1,0,{0.65,6,340,7,0,0,0.45,6,0,1,0,0,0,0,0,0,0,0,0,0,0.3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,3}},1,"+3 disparos"},{{{1,0,1.4}},1,"+40% daño"},{{{6,0,1.3}},1,"+30% alcance"},{{{3,1,3},{5,1,1}},2,"+3 disparos y +1 perforación"}}},  // bubble-beam
  {"Infortunio","Maldición que salta entre enemigos. Mucho más daño si están quemados, envenenados o frenados.",13,8,1,0,{0.9,17,0,4,0,0,0,0,150,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1.7,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,2}},1,"+2 saltos"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,2},{1,0,1.4}},2,"+2 saltos y +40% daño"}}},  // hex
  {"Hiperrayo","Se carga un momento y suelta un rayo enorme que lo atraviesa todo.",0,17,1,0,{2.2,58,0,0,0,0,0,0,300,0,0,44,0,0,0,0,0,0.75,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{17,0,0.7},{0,0,0.8}},2,"Carga más rápido y -20% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // hyper-beam
  {"Giro Rápido","Giras sobre ti mismo golpeando todo lo que te rodea varias veces.",0,18,0,0,{1,9,0,3,0,0,0,0,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{3,1,1}},1,"+1 vuelta"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // rapid-spin
  {"Nitrocarga","Te lanzas envuelto en llamas y quemas todo el camino.",1,12,0,0,{0.8,19,0,0,0,0,0,0,115,0,0,36,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% distancia"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.6},{11,0,1.4}},2,"+60% daño y más ancho"}}},  // flame-charge
  {"Torbellino","Un remolino que arrastra a los enemigos a su centro y los va dañando.",2,20,1,0,{3,8,0,0,0,0,0,0,72,0,0,0,2.6,0,0,0,0,0,150,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{12,0,1.5}},1,"+50% duración"},{{{18,0,1.4},{1,0,1.4}},2,"Atrae más fuerte y +40% daño"}}},  // whirlpool
  {"Bomba Germen","Una semilla que rebota de enemigo en enemigo.",4,16,0,0,{0.6,10,320,1,0.12,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // seed-bomb
  {"Energibola","Una bola de energía que persigue al enemigo.",4,15,1,0,{0.62,19,280,1,0.12,0,2,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // energy-ball
  {"Rayo Solar","Absorbe luz un momento y la suelta en un rayo enorme.",4,17,1,0,{2.3,62,0,0,0,0,0,0,290,0,0,40,0,0,0,0,0,0.85,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{17,0,0.7},{0,0,0.8}},2,"Carga más rápido y -20% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // solar-beam
  {"Onda Trueno","Una descarga que avisa en el suelo y deja paralizados a los que pilla.",3,22,1,0,{1.6,22,0,0,0,0,0,0,58,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{21,0,1.5}},1,"+50% aturdimiento"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // thunder-wave
  {"Bola Voltio","Una bola eléctrica que salta de enemigo en enemigo.",3,16,1,0,{0.62,10,340,1,0.12,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // electro-ball
  {"Paranormal","Una onda mental que daña y aparta a todos los que tienes cerca.",10,21,1,0,{1.2,16,0,0,0,0,0,0,92,0,320,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{0,0,0.75}},1,"-25% recarga"},{{{10,0,1.5},{1,0,1.4}},2,"+50% empuje y +40% daño"}}},  // extrasensory
  {"Bola Neblina","Una bola de bruma que persigue al enemigo y le frena.",10,15,1,0,{0.55,13,270,1,0.12,0,2,8,0,0,0,0,0,0,0,0,0,0,0,0,0.3,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // mist-ball
  {"Bomba Ácida","Un chorro ácido que salta entre enemigos y los envenena.",7,16,1,0,{0.66,8,310,1,0.12,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // acid-spray
  {"Bucle Arena","Un remolino de arena que atrapa y arrastra a los enemigos.",8,20,0,0,{3,9,0,0,0,0,0,0,70,0,0,0,2.6,0,0,0,0,0,140,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{12,0,1.5}},1,"+50% duración"},{{{18,0,1.4},{1,0,1.4}},2,"Atrae más fuerte y +40% daño"}}},  // sand-tomb
  {"Magnitud","El suelo revienta en línea delante de ti, onda tras onda.",8,19,0,0,{1.15,18,0,6,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,2}},1,"+2 ondas"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.25}},1,"+25% tamaño"},{{{0,0,0.75},{3,1,2}},2,"-25% recarga y +2 ondas"}}},  // magnitude
  {"Remolino","Un golpe de viento que barre a todos los que tienes cerca.",9,21,1,0,{1.1,14,0,0,0,0,0,0,96,0,360,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{0,0,0.75}},1,"-25% recarga"},{{{10,0,1.5},{1,0,1.4}},2,"+50% empuje y +40% daño"}}},  // whirlwind
  {"Tajo Aéreo","Dos cuchillas de aire que buscan al enemigo.",9,15,1,0,{0.55,9,330,2,0.35,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // air-slash
  {"Rayo Señal","Un destello que rebota entre los enemigos.",11,16,1,0,{0.6,10,340,1,0.12,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // signal-beam
  {"Ida y Vuelta","Cruzas entre los enemigos golpeando a todos los del camino.",11,12,0,0,{0.7,17,0,0,0,0,0,0,120,0,0,34,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% distancia"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.6},{11,0,1.4}},2,"+60% daño y más ancho"}}},  // u-turn
  {"Tumba Rocas","Caen rocas donde avisa el suelo y dejan atrapados a los que pilla.",12,22,0,0,{1.7,31,0,0,0,0,0,0,56,0,0,0,0,0,0,0,0,0,0,0,0,0.9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{21,0,1.5}},1,"+50% aturdimiento"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // rock-tomb
  {"Poder Pasado","Rocas antiguas que giran a tu alrededor.",12,3,1,0,{0.28,13,2.6,3,0,0,0,9,70,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 orbe"},{{{1,0,1.55}},1,"+55% daño"},{{{8,0,1.25},{2,0,1.35}},2,"+25% radio y gira más rápido"},{{{3,1,1},{1,0,1.55}},2,"+1 orbe y +55% daño"}}},  // ancient-power
  {"Joya de Luz","Un destello de gema que rebota de enemigo en enemigo.",12,16,1,0,{0.66,11,320,1,0.12,0,1.6,8,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // power-gem
  {"Canto Helado","Esquirlas rapidísimas que persiguen al enemigo.",5,15,0,0,{0.32,9,380,1,0.12,0,1.5,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // ice-shard
  {"Liofilización","Un frío repentino que avisa en el suelo y deja congelados a los que pilla.",5,22,1,0,{1.6,24,0,0,0,0,0,0,60,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{21,0,1.5}},1,"+50% aturdimiento"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // freeze-dry
  {"Patada Giro","Patadas en giro que golpean todo lo que tienes alrededor.",6,18,0,0,{0.95,11,0,3,0,0,0,0,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{3,1,1}},1,"+1 vuelta"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // rolling-kick
  {"Onda Vacío","Un puñetazo al aire que lanza una onda y aparta a los enemigos.",6,21,1,0,{1.1,17,0,0,0,0,0,0,88,0,330,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{0,0,0.75}},1,"-25% recarga"},{{{10,0,1.5},{1,0,1.4}},2,"+50% empuje y +40% daño"}}},  // vacuum-wave
  {"Puño Dinámico","Un puñetazo tremendo donde avisa el suelo: deja aturdidos a los que pilla.",6,22,0,0,{1.7,33,0,0,0,0,0,0,54,0,0,0,0,0,0,0,0,0,0,0,0,0.9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{21,0,1.5}},1,"+50% aturdimiento"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // dynamic-punch
  {"Sombra Vil","Una sombra que se escurre por el suelo hasta el enemigo.",13,15,0,0,{0.45,14,300,1,0.12,0,1.8,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // shadow-sneak
  {"Viento Aciago","Un viento maldito que arremolina a los enemigos y los va dañando.",13,20,1,0,{3,9,0,0,0,0,0,0,74,0,0,0,2.6,0,0,0,0,0,140,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{12,0,1.5}},1,"+50% duración"},{{{18,0,1.4},{1,0,1.4}},2,"Atrae más fuerte y +40% daño"}}},  // ominous-wind
  {"Dragoaliento","Un aliento de dragón en abanico corto que frena.",14,14,1,0,{0.7,7,330,7,0,0,0.5,7,0,0.95,0,0,0,0,0,0,0,0,0,0,0.25,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,3}},1,"+3 disparos"},{{{1,0,1.4}},1,"+40% daño"},{{{6,0,1.3}},1,"+30% alcance"},{{{3,1,3},{5,1,1}},2,"+3 disparos y +1 perforación"}}},  // dragon-breath
  {"Garra Dragón","Un zarpazo de dragón en arco.",14,1,0,0,{0.52,23,0,0,0,0,0,0,65,2.5,70,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // dragon-claw
  {"Enfado","Una furia de golpes en giro que no deja a nadie en pie.",14,18,0,0,{1.1,12,0,4,0,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{3,1,1}},1,"+1 vuelta"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // outrage
  {"Beso Drenaje","Un beso que persigue al enemigo y te cura un poco al darle.",17,15,1,0,{0.55,13,280,1,0.12,0,2,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // draining-kiss
  {"Carantoña","Un ataque juguetón pero muy fuerte en arco.",17,1,0,0,{0.6,26,0,0,0,0,0,0,63,2.5,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // play-rough
  {"Voz Cautivadora","Un grito encantador que daña y aparta a los que tienes cerca.",17,21,1,0,{1.15,15,0,0,0,0,0,0,94,0,300,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{0,0,0.75}},1,"-25% recarga"},{{{10,0,1.5},{1,0,1.4}},2,"+50% empuje y +40% daño"}}},  // disarming-voice
  {"Disparo Espejo","Un destello metálico que rebota entre los enemigos.",16,16,1,0,{0.64,10,340,1,0.12,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // mirror-shot
  {"Giro Bola","Giras como una bola de acero golpeando todo alrededor.",16,18,0,0,{1.05,12,0,3,0,0,0,0,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{3,1,1}},1,"+1 vuelta"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // gyro-ball
  {"Golpe Bajo","Un golpe a traición que busca al enemigo.",15,15,0,0,{0.7,22,330,1,0.12,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // sucker-punch
  {"Tajo Umbrío","Cortes en giro que alcanzan a todo lo que te rodea.",15,18,0,0,{1,11,0,3,0,0,0,0,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{3,1,1}},1,"+1 vuelta"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // night-slash
  {"Ventisca","Un abanico de nieve ancho que deja a los enemigos casi quietos.",5,14,1,0,{0.9,15.74,300,9,0,1,0.55,7,0,1.3,0,0,0,0,0,0,0,0,0,0,0.55,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,3}},1,"+3 disparos"},{{{1,0,1.4}},1,"+40% daño"},{{{6,0,1.3}},1,"+30% alcance"},{{{3,1,3},{5,1,1}},2,"+3 disparos y +1 perforación"}}},  // blizzard
  {"Megacuerno","Una embestida larguísima con el cuerno que atraviesa todo.",11,12,0,0,{1.8,41.68,0,0,0,0,0,0,220,0,120,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% distancia"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.6},{11,0,1.4}},2,"+60% daño y más ancho"}}},  // megahorn
  {"Pulso Dragón","Una onda de dragón enorme y lenta que atraviesa a todos los que pilla.",14,0,1,0,{0.9,18.17,270,1,0.12,99,1.7,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // dragon-pulse
  {"Escaldar","Agua hirviendo que atraviesa a uno y quema.",2,0,1,0,{0.55,22.9,360,1,0.12,1,1.3,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // scald
  {"Vendaval","Un remolino de viento que atraviesa y aparta de un soplido a todos.",9,0,1,0,{1,57.68,330,1,0.12,99,1.2,13,0,0,240,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // hurricane
  {"Psicocarga","Una onda psíquica que rebota entre cuatro enemigos.",10,16,1,0,{0.7,26.17,360,1,0.12,0,1.6,8,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // psyshock
  {"Ascenso Draco","Bajas del cielo a toda velocidad y arrasas todo lo que hay en tu camino.",9,12,0,0,{0.9,17.61,0,0,0,0,0,0,175,0,100,50,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% distancia"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.6},{11,0,1.4}},2,"+60% daño y más ancho"}}},  // dragon-ascent
  {"Onda Mental","Una onda de poder mental sale en todas direcciones y atraviesa a varios enemigos.",10,4,1,0,{1.2,12.26,300,16,0,3,1.4,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1.2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,4}},1,"+4 proyectiles"},{{{1,0,1.4}},1,"+40% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,4},{5,1,1}},2,"+4 proyectiles y +1 perforación"}}},  // psystrike
  {"Fuego Sagrado","Llamas sagradas caen sobre los enemigos cercanos y los queman.",1,10,0,0,{1.3,4.49,0,4,0,0,0,0,58,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1.5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 meteoro"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{3,1,2},{0,0,0.8}},2,"+2 meteoros y -20% recarga"}}},  // sacred-fire
  {"Pulso Primigenio","Rayos de agua salen de ti en todas direcciones y empujan a los enemigos.",2,4,1,0,{1.3,21.56,320,10,0,4,1.3,11,0,0,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,4}},1,"+4 proyectiles"},{{{1,0,1.4}},1,"+40% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,4},{5,1,1}},2,"+4 proyectiles y +1 perforación"}}},  // origin-pulse
  {"Filo del Abismo","Hojas de piedra brotan del suelo en línea, una detrás de otra.",8,19,0,0,{1.25,12.87,0,8,0,0,0,0,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,2}},1,"+2 ondas"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.25}},1,"+25% tamaño"},{{{0,0,0.75},{3,1,2}},2,"-25% recarga y +2 ondas"}}},  // precipice-blades
  {"Placaje Eléctrico","Te lanzas envuelto en electricidad y arrollas todo a tu paso.",3,12,0,0,{0.9,22.14,0,0,0,0,0,0,150,0,120,44,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% distancia"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.6},{11,0,1.4}},2,"+60% daño y más ancho"}}},  // volt-tackle
  {"Tormenta de Diamantes","Una lluvia de diamantes cae sobre los enemigos cercanos.",12,10,0,0,{1.25,8.87,0,5,0,0,0,0,50,0,50,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 meteoro"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{3,1,2},{0,0,0.8}},2,"+2 meteoros y -20% recarga"}}},  // diamond-storm
  {"Sable Místico","Dos tajos de energía salen hacia el enemigo y vuelven a ti.",6,7,1,0,{0.85,11.7,360,2,0.5,0,0,9,240,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 bumerán"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% alcance"},{{{3,1,1},{1,0,1.4}},2,"+1 bumerán y +40% daño"}}},  // secret-sword
  {"Deseo Oculto","Un rayo de luz cae al rato sobre un enemigo y explosiona con mucha fuerza.",16,10,1,0,{2.4,22.14,0,1,0,0,0,0,95,0,120,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 meteoro"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{3,1,2},{0,0,0.8}},2,"+2 meteoros y -20% recarga"}}},  // doom-desire
  {"Geocontrol","No hace daño: acumula mucho ATAQUE ESPECIAL mientras esté activo.",17,6,2,2,{0.85,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0.18,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{16,1,1}},1,"+1 acumulación máxima"},{{{15,0,1.4}},1,"+40% potencia"},{{{12,0,1.5}},1,"+50% duración"},{{{16,1,1},{15,0,1.4}},2,"+1 acumulación y +40% potencia"}}},  // geomancy
  {"Giro Mortífero","Giras golpeando todo lo que tienes alrededor y lo envenenas.",7,18,0,0,{1,8.82,0,4,0,0,0,0,72,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1.5,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{3,1,1}},1,"+1 vuelta"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // mortal-spin
  {"Al Ataque","Un enjambre de bichos persigue a los enemigos.",11,15,0,0,{0.75,22.69,300,4,0.6,0,2,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // attack-order
  {"Canto Arcaico","Un canto antiguo que daña y aparta con fuerza a todos los que tienes cerca.",0,21,1,0,{1.1,84.58,0,0,0,0,0,0,110,0,360,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{0,0,0.75}},1,"-25% recarga"},{{{10,0,1.5},{1,0,1.4}},2,"+50% empuje y +40% daño"}}},  // relic-song
  {"Llama Azul","Una llamarada azul en línea recta que quema todo lo que atraviesa.",1,2,1,0,{1.6,16.81,0,0,0,0,0,0,300,0,0,40,0,0,0,0,0,0,0,0,0,0,0,1.5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // blue-flare
  {"Balón Ígneo","Un balón de fuego que atraviesa a varios enemigos y los quema.",1,0,0,0,{0.7,18.56,320,1,0.1,3,1.5,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // pyro-ball
  {"Lanza Glacial","Lanzas de hielo caen sobre los enemigos cercanos y los frenan.",5,10,0,0,{1.4,5.69,0,4,0,0,0,0,60,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 meteoro"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{3,1,2},{0,0,0.8}},2,"+2 meteoros y -20% recarga"}}},  // glacial-lance
  {"Mil Flechas","Una lluvia de flechas de tierra cae sobre muchos enemigos.",8,10,0,0,{1.3,4.84,0,7,0,0,0,0,44,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 meteoro"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{3,1,2},{0,0,0.8}},2,"+2 meteoros y -20% recarga"}}},  // thousand-arrows
  {"Aerochorro","Un chorro de aire cortante en línea recta que atraviesa todo lo que pilla.",9,2,1,0,{1.3,33.08,0,0,0,0,0,0,320,0,0,36,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // aeroblast
  {"Rayo Umbrío","Un rayo de luz de luna que atraviesa todo lo que pilla.",13,2,1,0,{1.5,34.4,0,0,0,0,0,0,300,0,0,44,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // moongeist-beam
  {"Puntada Sombría","Una flecha sombría que atraviesa a varios enemigos y los deja frenados.",13,0,0,0,{0.75,24.41,400,1,0.08,3,1.4,8,0,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // spirit-shackle
  {"Fragor Escamas","El estruendo de tus escamas daña y aparta a todos los que tienes cerca.",14,21,1,0,{1.1,85.8,0,0,0,0,0,0,100,0,300,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{0,0,0.75}},1,"-25% recarga"},{{{10,0,1.5},{1,0,1.4}},2,"+50% empuje y +40% daño"}}},  // clanging-scales
  {"Lariat Oscuro","Giras con los brazos abiertos golpeando todo lo que tienes alrededor.",15,18,0,0,{1,9.72,0,4,0,0,0,0,78,0,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{3,1,1}},1,"+1 vuelta"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // darkest-lariat
  {"Meteoimpacto","Te lanzas envuelto en el poder del sol y arrollas todo a tu paso.",16,12,0,0,{1,20.33,0,0,0,0,0,0,170,0,120,52,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% distancia"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.6},{11,0,1.4}},2,"+60% daño y más ancho"}}},  // sunsteel-strike
  {"Tajo Supremo","Un tajo enorme con la espada que golpea en un arco amplio.",16,1,0,0,{0.9,24.82,0,0,0,0,0,0,88,3,120,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // behemoth-blade
  {"Aria Burbuja","Burbujas cantarinas salen en todas direcciones y atraviesan a varios enemigos.",2,4,1,0,{1.2,15.32,280,14,0,2,1.4,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,4}},1,"+4 proyectiles"},{{{1,0,1.4}},1,"+40% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,4},{5,1,1}},2,"+4 proyectiles y +1 perforación"}}},  // sparkling-aria
  {"Cascada","Una columna de agua cae sobre el enemigo y lo deja aturdido.",2,22,0,0,{1.4,23.01,0,0,0,0,0,0,46,0,0,0,0,0,0,0,0,0,0,0,0,0.8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{21,0,1.5}},1,"+50% aturdimiento"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // waterfall
  {"Hidropulso","Un anillo de agua que deja aturdido un momento al que toca.",2,0,1,0,{0.7,44.11,360,1,0.12,0,1.4,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0.45,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // water-pulse
  {"Distorsión","Cargas un momento y sale un rayo enorme que distorsiona el tiempo.",14,17,1,0,{2.4,37.64,0,0,0,0,0,0,330,0,0,58,0,0,0,0,0,0.8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{17,0,0.7},{0,0,0.8}},2,"Carga más rápido y -20% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // roar-of-time
  {"Brecha Negra","Una brecha oscura deja aturdidos un buen rato a todos los que pilla.",15,22,1,0,{2,25.3,0,0,0,0,0,0,110,0,0,0,0,0,0,0,0,0,0,0,0,1.8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{21,0,1.5}},1,"+50% aturdimiento"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // dark-void
  {"Géiser Fotónico","Reúnes luz un momento y sale un géiser de fotones enorme hacia delante.",10,17,1,0,{2.3,37.21,0,0,0,0,0,0,320,0,0,60,0,0,0,0,0,0.7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{17,0,0.7},{0,0,0.8}},2,"Carga más rápido y -20% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // photon-geyser
  {"Cañón Dinamax","Cargas energía un momento y disparas un cañonazo rojo enorme.",14,17,1,0,{2.4,35.28,0,0,0,0,0,0,340,0,0,62,0,0,0,0,0,0.8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{17,0,0.7},{0,0,0.8}},2,"Carga más rápido y -20% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // dynamax-cannon
  {"Terremoto","Un temblor sale de ti en anillo y golpea a todo lo que alcanza.",8,23,0,0,{1.6,25.5,0,0,0,0,0,0,170,0,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5},{8,0,1.2}},2,"+50% daño y +20% radio"}}},  // earthquake
  {"Surf","Una ola enorme cruza la pantalla y arrastra a los enemigos.",2,24,1,0,{2.2,215.46,560,0,0,0,0,0,560,0,160,190,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{11,0,1.3}},1,"Ola un 30% más ancha"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5},{10,0,1.4}},2,"+50% daño y arrastra más"}}},  // surf
  {"Llamarada","Una explosión de fuego en cruz sobre el enemigo que quema.",1,25,1,0,{1.6,15.9,0,0,0,0,0,0,90,0,0,26,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"Brazos un 30% más largos"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5},{11,0,1.4}},2,"+50% daño y brazos más anchos"}}},  // fire-blast
  {"Trueno","Caen rayos sobre enemigos al azar de la pantalla.",3,26,1,0,{1.5,4.29,0,5,0,0,0,0,34,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,2}},1,"+2 rayos"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,2},{8,0,1.3}},2,"+2 rayos y +30% radio"}}},  // thunder
  {"Día Soleado","No hace daño: sale el sol (Fuego ×1,5, Agua ×0,5) un rato aunque cambies de ataque.",1,36,2,0,{4,0,0,0,0,0,0,0,0,0,0,0,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{12,0,1.35}},1,"+35% duración"},{{{12,0,1.35}},1,"+35% duración"},{{{12,0,1.35}},1,"+35% duración"},{{{12,0,1.5}},1,"+50% duración"}}},  // sunny-day
  {"Danza Lluvia","No hace daño: llueve (Agua ×1,5, Eléctrico ×1,2, Fuego ×0,5) un rato aunque cambies de ataque.",2,36,2,0,{4,0,0,0,0,0,0,0,0,0,0,0,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},{{{{12,0,1.35}},1,"+35% duración"},{{{12,0,1.35}},1,"+35% duración"},{{{12,0,1.35}},1,"+35% duración"},{{{12,0,1.5}},1,"+50% duración"}}},  // rain-dance
  {"Tormenta Arena","No hace daño: tormenta de arena (Roca, Tierra y Acero ×1,3; los demás sufren, también tú) un rato.",12,36,2,0,{4,0,0,0,0,0,0,0,0,0,0,0,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0},{{{{12,0,1.35}},1,"+35% duración"},{{{12,0,1.35}},1,"+35% duración"},{{{12,0,1.35}},1,"+35% duración"},{{{12,0,1.5}},1,"+50% duración"}}},  // sandstorm
  {"Puño Fuego","Tres directos de fuego seguidos que queman.",1,27,0,0,{0.85,10.37,0,3,0,0,0,0,60,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{3,1,1}},1,"+1 directo"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5},{8,0,1.2}},2,"+50% daño y +20% alcance"}}},  // fire-punch
  {"Puño Hielo","Tres directos helados: frenan y el último deja congelado un momento.",5,27,0,0,{0.85,15.69,0,3,0,0,0,0,60,1,0,0,0,0,0,0,0,0,0,0,0.4,0.35,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{3,1,1}},1,"+1 directo"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5},{8,0,1.2}},2,"+50% daño y +20% alcance"}}},  // ice-punch
  {"Puño Trueno","Tres directos eléctricos: el último salta a dos enemigos cercanos.",3,27,0,0,{0.85,11.98,0,3,0,0,0,0,60,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{3,1,1}},1,"+1 directo"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5},{8,0,1.2}},2,"+50% daño y +20% alcance"}}},  // thunder-punch
  {"Puño Drenaje","Tres directos que te curan con cada golpe.",6,27,0,0,{0.9,17.12,0,3,0,0,0,0,60,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1.5,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{3,1,1}},1,"+1 directo"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5},{8,0,1.2}},2,"+50% daño y +20% alcance"}}},  // drain-punch
  {"Tijera X","Dos tajos cruzados en X: lo que pilles en el centro recibe los dos.",11,28,0,0,{0.75,16.59,0,0,0,0,0,0,70,1.3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5},{9,0,1.3}},2,"+50% daño y tajos más abiertos"}}},  // x-scissor
  {"Triturar","Un mordisco brutal que deja al enemigo débil a tus golpes (+25 % durante 4 s).",15,1,0,0,{1,16.74,0,0,0,0,0,0,63,1.38,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // crunch
  {"Velocidad Extrema","Saltas de enemigo en enemigo tan rápido que no te tocan.",0,29,0,0,{1.3,74.86,0,3,0,0,0,0,220,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 salto"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,2},{1,0,1.3}},2,"+2 saltos y +30% daño"}}},  // extreme-speed
  {"Acróbata","Un salto acrobático sobre el enemigo con onda al caer; sin objeto equipado, pega ×1,5.",9,30,0,0,{1.3,13.3,0,0,0,0,0,0,70,0,0,0,0,0,220,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1.5,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"Onda un 30% más grande"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5},{14,0,1.3}},2,"+50% daño y salta más lejos"}}},  // acrobatics
  {"Bomba Lodo","Una bomba de lodo que envenena y deja un charco tóxico al estallar.",7,0,1,0,{0.75,3.82,300,1,0.12,0,1.4,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,3,32,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // sludge-bomb
  {"Fuerza Lunar","La luz de la luna persigue al enemigo y estalla alrededor.",17,15,1,0,{0.8,7.61,280,1,0.12,0,2,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,56,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // moonblast
  {"Ola-Lava","Lava en todas las direcciones que quema y deja charcos ardiendo.",1,4,1,0,{1.4,7.09,220,8,0,1,0.7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,2.5,24,0,0,0,0,0,0,0},{{{{3,1,4}},1,"+4 proyectiles"},{{{1,0,1.4}},1,"+40% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,4},{5,1,1}},2,"+4 proyectiles y +1 perforación"}}},  // lava-plume
  {"Viento Plata","Un abanico de escamas de plata; a veces te sube el Ataque y la Velocidad.",11,14,1,0,{0.75,10.6,320,8,0,1,0.5,6,0,1.1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.15,0,0,0,0,0},{{{{3,1,3}},1,"+3 disparos"},{{{1,0,1.4}},1,"+40% daño"},{{{6,0,1.3}},1,"+30% alcance"},{{{3,1,3},{5,1,1}},2,"+3 disparos y +1 perforación"}}},  // silver-wind
  {"Roca Afilada","Una roca afiladísima que atraviesa a uno y hace críticos muy a menudo.",12,0,0,0,{0.85,42.72,420,1,0.12,1,1.2,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.3,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // stone-edge
  {"Protección","No hace daño: un escudo te hace intocable 1,5 s. Se recarga en 7 s y, por mucha reducción de recarga que lleves, nunca en menos de 5 s.",0,31,2,0,{7,0,0,0,0,0,0,0,0,0,0,0,1.5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0},{{{{12,0,1.25}},1,"+25% duración"},{{{0,0,0.85}},1,"-15% recarga"},{{{12,0,1.25}},1,"+25% duración"},{{{0,0,0.8},{12,0,1.2}},2,"-20% recarga y +20% duración"}}},  // protect
  {"Descanso","No hace daño: te cura mucho, pero te quedas dormido un rato sin moverte ni atacar.",10,32,2,0,{18,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0.6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{15,0,1.15}},1,"Cura un 15% más"},{{{12,0,0.85}},1,"Duermes un 15% menos"},{{{0,0,0.85}},1,"-15% recarga"},{{{15,0,1.2},{12,0,0.85}},2,"Cura un 20% más y duermes menos"}}},  // rest
  {"Reflejo","No hace daño: una pared de luz te quita un 35 % del daño físico un rato.",10,33,2,0,{10,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0.35,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{12,0,1.3}},1,"+30% duración"},{{{15,0,1.15}},1,"Protege un 15% más"},{{{0,0,0.85}},1,"-15% recarga"},{{{12,0,1.3}},1,"+30% duración"}}},  // reflect
  {"Pantalla Luz","No hace daño: una pared de luz te quita un 35 % del daño especial un rato.",10,33,2,0,{10,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0.35,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},{{{{12,0,1.3}},1,"+30% duración"},{{{15,0,1.15}},1,"Protege un 15% más"},{{{0,0,0.85}},1,"-15% recarga"},{{{12,0,1.3}},1,"+30% duración"}}},  // light-screen
  {"Doble Equipo","No hace daño: dejas una copia tuya que atrae a los enemigos cercanos.",0,34,2,0,{8,0,0,1,0,0,0,0,260,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{12,0,1.3}},1,"+30% duración"},{{{3,1,1}},1,"+1 copia"},{{{0,0,0.85}},1,"-15% recarga"},{{{8,0,1.3}},1,"Atrae desde un 30% más lejos"}}},  // double-team
  {"Explosión","Una explosión enorme a tu alrededor; te cuesta un cuarto de la vida que te queda (nunca te deja KO).",0,35,0,0,{2.5,38.57,0,0,0,0,0,0,150,0,220,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.25,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // explosion
  {"Golpe Umbrío","Desapareces y caes sobre el enemigo con una onda de sombra.",13,30,0,0,{1.3,18.48,0,0,0,0,0,0,90,0,0,0,0,0,260,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"Onda un 30% más grande"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5},{14,0,1.3}},2,"+50% daño y salta más lejos"}}},  // shadow-force
  {"Sentencia","Caen rayos de luz sobre muchos enemigos de la pantalla.",0,26,1,0,{1.4,2.85,0,8,0,0,0,0,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,2}},1,"+2 rayos"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,2},{8,0,1.3}},2,"+2 rayos y +30% radio"}}},  // judgment
  {"Mundo Gélido","Un anillo de hielo sale de ti, golpea a todos los que alcanza y los frena.",5,23,1,0,{1.5,24,0,0,0,0,0,0,190,0,0,0,0,0,0,0,0,0,0,0,0.6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5},{8,0,1.2}},2,"+50% daño y +20% radio"}}},  // glaciate
  {"Fulgor Semilla","Una explosión de semillas en cruz sobre un enemigo.",4,25,1,0,{1.4,23.2,0,0,0,0,0,0,110,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"Brazos un 30% más largos"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5},{11,0,1.4}},2,"+50% daño y brazos más anchos"}}},  // seed-flare
  {"Disparo Certero","Un disparo de agua rapidísimo que atraviesa a todos y hace más golpes críticos.",2,0,1,0,{0.6,10.71,520,1,0.05,99,1.2,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.3,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // snipe-shot
  {"Puños Plasma","Tres puñetazos de plasma; el último electrocuta a los enemigos cercanos.",3,27,0,0,{0.8,10.19,0,3,0,0,0,0,64,1.1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{3,1,1}},1,"+1 directo"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5},{8,0,1.2}},2,"+50% daño y +20% alcance"}}},  // plasma-fists
  {"Truco Floral","Flores que persiguen a los enemigos y hacen muchos más golpes críticos.",4,15,0,0,{0.8,22.54,300,4,0.6,0,2,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // flower-trick
  {"Asalto Estelar","Cargas con el puerro por delante y arrollas todo lo que hay en tu camino.",6,12,0,0,{1.1,32.74,0,0,0,0,0,0,180,0,140,50,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% distancia"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.6},{11,0,1.4}},2,"+60% daño y más ancho"}}},  // meteor-assault
  {"Cadena Virulenta","Una cadena tóxica salta de un enemigo a otro y los envenena.",7,8,1,0,{1,34.3,0,6,0,0,0,0,150,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,2}},1,"+2 saltos"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,2},{1,0,1.4}},2,"+2 saltos y +40% daño"}}},  // malignant-chain
  {"Hachazo Pétreo","Dos hachazos de piedra cruzados: lo que pilles en el centro recibe los dos.",12,28,0,0,{0.8,18.55,0,0,0,0,0,0,78,1.3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5},{9,0,1.3}},2,"+50% daño y tajos más abiertos"}}},  // stone-axe
};

static const short MOVE_ONLY[NMOVES][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{384,0,0},{150,0,0},{244,250,0},{382,0,0},{383,0,0},{172,25,26},{719,0,0},{647,0,0},{385,0,0},{716,0,0},{970,0,0},{416,0,0},{648,0,0},{643,0,0},{815,0,0},{898,0,0},{718,0,0},{249,0,0},{792,0,0},{724,0,0},{784,0,0},{727,0,0},{791,0,0},{888,0,0},{730,0,0},{0,0,0},{0,0,0},{483,0,0},{491,0,0},{800,0,0},{890,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{487,0,0},{493,0,0},{646,0,0},{492,0,0},{818,0,0},{807,0,0},{908,0,0},{865,0,0},{1025,0,0},{900,0,0}};
static const short EVO_NEED[NMOVES] = {0,2,-1,-1,-1,-1,1,3,5,0,1,2,1,-1,1,3,5,0,1,4,3,3,1,6,1,1,2,1,1,3,2,5,1,1,3,5,1,3,1,2,1,3,1,3,1,-1,1,5,1,4,1,2,5,1,3,1,5,3,1,3,4,2,2,1,6,1,2,2,5,1,5,3,1,2,4,3,5,0,1,2,3,1,5,0,4,1,3,1,2,4,1,3,6,1,1,0,5,1,4,1,4,1,2,3,1,1,1,2,1,1,1,1,1,1,1,1,1,1,-1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,2,1,3,-1,-1,-1,1,2,3,5,3,1,2,2,5,3,5,4,2,-1,-1,-1,-1,-1,0,1,1,1,1,1,1,1,1,1,1};
static const char* EVO_NAME[NMOVES] = {"Placaje +","Ataque Rápido +","","","","","Ascuas +","Lanzallamas +","Giro Fuego +","Onda Ígnea +","Pistola Agua +","Burbuja +","Hidrobomba +","","Látigo Cepa +","Hoja Afilada +","Tormenta Floral +","Hierba Lazo +","Impactrueno +","Chispazo +","Rayo +","Confusión +","Psicorrayo +","Psíquico +","Residuos +","Disparo Lodo +","Tornado +","Ataque Ala +","Golpe Cuerpo +","Vozarrón +","Picotazo Veneno +","Tóxico +","Terratemblor +","Picadura +","Disparo Demora +","Zumbido +","Lanzarrocas +","Avalancha +","Rayo Hielo +","Nieve Polvo +","Golpe Kárate +","Esfera Aural +","Lengüetazo +","Bola Sombra +","Furia Dragón +","","Viento Feérico +","Brillo Mágico +","Garra Metal +","Foco Resplandor +","Mordisco +","Pulso Umbrío +","Tinieblas +","Huesomerang +","Psicocorte +","Púas +","Púas Tóxicas +","Granizo +","Puño Meteoro +","Fuego Fatuo +","Sustituto +","Golpe Aéreo +","Rueda Fuego +","Rayo Burbuja +","Infortunio +","Hiperrayo +","Giro Rápido +","Nitrocarga +","Torbellino +","Bomba Germen +","Energibola +","Rayo Solar +","Onda Trueno +","Bola Voltio +","Paranormal +","Bola Neblina +","Bomba Ácida +","Bucle Arena +","Magnitud +","Remolino +","Tajo Aéreo +","Rayo Señal +","Ida y Vuelta +","Tumba Rocas +","Poder Pasado +","Joya de Luz +","Canto Helado +","Liofilización +","Patada Giro +","Onda Vacío +","Puño Dinámico +","Sombra Vil +","Viento Aciago +","Dragoaliento +","Garra Dragón +","Enfado +","Beso Drenaje +","Carantoña +","Voz Cautivadora +","Disparo Espejo +","Giro Bola +","Golpe Bajo +","Tajo Umbrío +","Ventisca +","Megacuerno +","Pulso Dragón +","Escaldar +","Vendaval +","Psicocarga +","Ascenso Draco +","Onda Mental +","Fuego Sagrado +","Pulso Primigenio +","Filo del Abismo +","Placaje Eléctrico +","Tormenta de Diamantes +","Sable Místico +","Deseo Oculto +","","Giro Mortífero +","Al Ataque +","Canto Arcaico +","Llama Azul +","Balón Ígneo +","Lanza Glacial +","Mil Flechas +","Aerochorro +","Rayo Umbrío +","Puntada Sombría +","Fragor Escamas +","Lariat Oscuro +","Meteoimpacto +","Tajo Supremo +","Aria Burbuja +","Cascada +","Hidropulso +","Distorsión +","Brecha Negra +","Géiser Fotónico +","Cañón Dinamax +","Terremoto +","Surf +","Llamarada +","Trueno +","","","","Puño Fuego +","Puño Hielo +","Puño Trueno +","Puño Drenaje +","Tijera X +","Triturar +","Velocidad Extrema +","Acróbata +","Bomba Lodo +","Fuerza Lunar +","Ola-Lava +","Viento Plata +","Roca Afilada +","","","","","","Explosión +","Golpe Umbrío +","Sentencia +","Mundo Gélido +","Fulgor Semilla +","Disparo Certero +","Puños Plasma +","Truco Floral +","Asalto Estelar +","Cadena Virulenta +","Hachazo Pétreo +"};
struct EvoMod { UpMod m[6]; unsigned char n; const char* text; };
static const EvoMod EVO_MODS[37] = {
  {{{1,0,1.8},{3,1,2},{5,1,2},{7,0,1.3},{4,0,1.1}},5,"×1,8 daño, +2 proyectiles, +2 perforación y más grandes"},  // projectile
  {{{1,0,1.9},{8,0,1.3},{9,0,9}},3,"×1,9 daño, más alcance y golpea en 360°"},  // melee
  {{{1,0,1.8},{11,0,1.5},{8,0,1.2},{0,0,0.85}},4,"×1,8 daño, rayo un 50% más grueso y más largo"},  // beam
  {{{3,1,2},{1,0,1.7},{8,0,1.15}},3,"+2 orbes, ×1,7 daño y más radio"},  // orbit
  {{{3,1,6},{1,0,1.6},{5,1,1}},3,"+6 proyectiles, ×1,6 daño y +1 perforación"},  // nova
  {{{1,0,1.8},{8,0,1.35}},2,"×1,8 daño y un 35% más de radio"},  // aura
  {{},0,""},  // buff
  {{{1,0,1.8},{3,1,1},{8,0,1.2},{7,0,1.2}},4,"×1,8 daño, +1 bumerán y más alcance"},  // boomerang
  {{{1,0,1.7},{3,1,3},{8,0,1.2}},3,"×1,7 daño y +3 saltos"},  // chain
  {{{1,0,1.8},{3,1,2},{8,0,1.25}},3,"×1,8 daño, +2 minas y explosión más grande"},  // mine
  {{{1,0,1.7},{3,1,2},{8,0,1.2}},3,"×1,7 daño, +2 meteoros y más radio"},  // meteor
  {{{1,0,1.8},{3,1,1},{13,0,0.8}},3,"×1,8 daño, +1 a la vez y dispara más rápido"},  // turret
  {{{1,0,1.9},{8,0,1.25},{0,0,0.8}},3,"×1,9 daño, más distancia y menos recarga"},  // dash
  {{{1,0,1.8},{8,0,1.25},{12,0,1.3}},3,"×1,8 daño, charcos más grandes y duraderos"},  // trail
  {{{1,0,1.7},{3,1,4},{5,1,1}},3,"×1,7 daño, +4 disparos y +1 perforación"},  // cone
  {{{1,0,1.8},{3,1,2},{7,0,1.3},{4,0,1.2}},4,"×1,8 daño, +2 proyectiles y más grandes"},  // homing
  {{{1,0,1.8},{19,1,2},{3,1,1},{4,0,1.3}},4,"×1,8 daño, +2 rebotes y +1 proyectil"},  // bounce
  {{{1,0,1.8},{11,0,1.5},{17,0,0.7}},3,"×1,8 daño, rayo un 50% más grueso y carga más rápido"},  // charge
  {{{1,0,1.8},{3,1,1},{8,0,1.2}},3,"×1,8 daño, +1 vuelta y más radio"},  // spin
  {{{1,0,1.8},{3,1,3},{8,0,1.25}},3,"×1,8 daño, +3 ondas y ondas más grandes"},  // quake
  {{{1,0,1.8},{8,0,1.3},{18,0,1.4}},3,"×1,8 daño, más radio y atrae más fuerte"},  // vortex
  {{{1,0,1.8},{8,0,1.25},{10,0,1.4}},3,"×1,8 daño, más radio y empuja más"},  // shove
  {{{1,0,1.8},{8,0,1.3},{21,0,1.4}},3,"×1,8 daño, más radio y aturde más rato"},  // stun
  {{{1,0,1.8},{8,0,1.3}},2,"×1,8 daño y un 30% más de radio"},  // tremor
  {{{1,0,1.8},{11,0,1.3},{10,0,1.3}},3,"×1,8 daño, ola más ancha y arrastra más"},  // wave
  {{{1,0,1.8},{8,0,1.3},{11,0,1.3}},3,"×1,8 daño y brazos más largos y anchos"},  // cross
  {{{1,0,1.7},{3,1,3},{8,0,1.2}},3,"×1,7 daño, +3 rayos y más radio"},  // storm
  {{{1,0,1.8},{3,1,2}},2,"×1,8 daño y +2 directos"},  // punch
  {{{1,0,1.8},{8,0,1.25}},2,"×1,8 daño y tajos más largos"},  // scissor
  {{{1,0,1.7},{3,1,3}},2,"×1,7 daño y +3 saltos"},  // blitz
  {{{1,0,1.8},{8,0,1.3}},2,"×1,8 daño y onda más grande"},  // leap
  {{},0,""},  // guard
  {{},0,""},  // rest
  {{},0,""},  // screen
  {{},0,""},  // decoy
  {{{1,0,1.8},{8,0,1.3}},2,"×1,8 daño y un 30% más de radio"},  // boom
  {{},0,""},  // weather
};

static const short POOL_ALL[] = {0,1,2,3,4,5,28,29,60,65,66,153,160,164,165,6,7,8,9,59,62,67,142,144,147,157,10,11,12,13,63,68,106,134,135,141,145,18,19,20,72,73,143,149,14,15,16,17,69,70,71,38,39,57,86,87,103,148,40,41,88,89,90,150,24,30,31,56,76,155,25,32,53,55,77,78,140,26,27,61,79,80,107,154,21,22,23,54,74,75,108,161,162,163,33,34,35,81,82,104,151,158,36,37,83,84,85,146,159,42,43,64,91,92,44,45,93,94,95,105,50,51,52,101,102,152,48,49,58,99,100,46,47,96,97,98,156};
struct PoolRef { short off, n; };
static const PoolRef POOL_BY_TYPE[NTYPES] = {{0,15},{15,11},{26,11},{37,7},{44,7},{51,7},{58,6},{64,6},{70,7},{77,7},{84,10},{94,8},{102,7},{109,5},{114,6},{120,6},{126,5},{131,6}};

enum { B_CHASE=0,B_CHARGER=1,B_RANGED=2,B_TANK=3,B_HEALER=4,B_SHIELDER=5,B_SUMMONER=6,B_BOMBER=7,B_BEAMER=8,B_ZONER=9,B_FAN=10,B_JUMPER=11,B_RUNNER=12 };
struct DexE { const char* name; unsigned char t1, t2, rarity, gen, leg, beh, start; short minion; unsigned short hp, spd, bst; float atk, pa, sa; unsigned char df, sd; };
#define DEX_N 1082
static const DexE DEX[DEX_N] = {
  {"Bulbasaur",4,7,1,1,0,0,14,0,90,97,318,1.06,0.97,1.06,49,65},  // #1
  {"Ivysaur",4,7,2,1,0,0,14,0,97,103,405,1.14,1.04,1.14,63,80},  // #2
  {"Venusaur",4,7,4,1,0,0,14,0,106,112,525,1.25,1.15,1.25,83,100},  // #3
  {"Charmander",1,255,1,1,0,0,6,0,88,105,309,1.03,0.99,1.03,43,50},  // #4
  {"Charmeleon",1,255,2,1,0,0,6,0,96,112,405,1.14,1.05,1.14,58,65},  // #5
  {"Charizard",1,9,4,1,0,0,6,0,105,120,534,1.3,1.16,1.3,78,85},  // #6
  {"Squirtle",2,255,1,1,0,0,10,0,90,96,314,0.97,0.96,0.97,65,64},  // #7
  {"Wartortle",2,255,2,1,0,0,10,0,97,102,405,1.06,1.05,1.06,80,80},  // #8
  {"Blastoise",2,255,4,1,0,0,10,0,106,111,530,1.17,1.16,1.17,100,105},  // #9
  {"Caterpie",11,255,1,1,0,6,33,0,90,97,195,0.86,0.86,0.81,35,20},  // #10
  {"Metapod",11,255,1,1,0,6,33,0,92,91,205,0.84,0.81,0.84,55,25},  // #11
  {"Butterfree",11,9,2,1,0,0,33,0,97,107,395,1.2,0.95,1.2,50,80},  // #12
  {"Weedle",11,7,1,1,0,0,33,0,88,99,195,0.89,0.89,0.81,30,20},  // #13
  {"Kakuna",11,7,1,1,0,0,33,0,90,93,205,0.84,0.84,0.84,50,25},  // #14
  {"Beedrill",11,7,2,1,0,6,33,13,99,110,395,1.2,1.2,0.95,40,80},  // #15
  {"Pidgey",0,9,1,1,0,0,0,0,88,102,251,0.95,0.95,0.89,40,35},  // #16
  {"Pidgeotto",0,9,2,1,0,1,0,0,98,108,349,1.03,1.03,0.97,55,50},  // #17
  {"Pidgeot",0,9,3,1,0,6,0,16,107,120,479,1.14,1.14,1.08,75,70},  // #18
  {"Rattata",0,255,1,1,0,0,0,0,84,108,253,1.01,1.01,0.84,35,35},  // #19
  {"Raticate",0,255,3,1,0,0,0,0,95,119,413,1.15,1.15,0.97,60,70},  // #20
  {"Spearow",0,9,1,1,0,0,0,0,88,107,262,1.03,1.03,0.87,30,31},  // #21
  {"Fearow",0,9,3,1,0,0,0,0,99,120,442,1.2,1.2,1.04,65,61},  // #22
  {"Ekans",7,255,1,1,0,0,24,0,86,101,288,1.03,1.03,0.92,44,54},  // #23
  {"Arbok",7,255,3,1,0,6,24,23,97,112,448,1.22,1.22,1.06,69,79},  // #24
  {"Pikachu",3,255,2,1,0,2,18,0,86,116,320,1,1,0.97,40,50},  // #25
  {"Raichu",3,255,3,1,0,0,18,0,97,124,485,1.2,1.2,1.2,55,80},  // #26
  {"Sandshrew",8,255,1,1,0,1,25,0,92,95,300,1.11,1.11,0.81,85,30},  // #27
  {"Sandslash",8,255,3,1,0,6,25,27,104,105,450,1.25,1.25,0.95,110,55},  // #28
  {"Nidoran♀",7,255,1,1,0,0,24,0,95,95,275,0.96,0.96,0.92,52,40},  // #29
  {"Nidorina",7,255,2,1,0,0,24,0,102,102,365,1.04,1.04,1,67,55},  // #30
  {"Nidoqueen",7,8,4,1,0,6,24,29,110,110,505,1.21,1.21,1.11,87,85},  // #31
  {"Nidoran♂",7,255,1,1,0,9,24,0,91,99,273,1.01,1.01,0.92,40,40},  // #32
  {"Nidorino",7,255,2,1,0,0,24,0,97,105,365,1.1,1.1,1,57,55},  // #33
  {"Nidoking",7,8,4,1,0,6,24,32,106,114,505,1.26,1.26,1.17,77,75},  // #34
  {"Clefairy",17,255,2,1,0,4,46,0,102,93,323,1.03,0.95,1.03,48,65},  // #35
  {"Clefable",17,255,3,1,0,4,46,0,113,103,483,1.22,1.08,1.22,73,90},  // #36
  {"Vulpix",1,255,1,1,0,0,6,0,87,105,299,0.97,0.93,0.97,40,65},  // #37
  {"Ninetales",1,255,4,1,0,2,6,0,103,120,505,1.15,1.12,1.15,75,100},  // #38
  {"Jigglypuff",0,17,1,1,0,11,0,0,122,86,270,0.95,0.95,0.95,20,25},  // #39
  {"Wigglytuff",0,17,3,1,0,3,0,0,133,97,435,1.17,1.08,1.17,45,50},  // #40
  {"Zubat",7,9,1,1,0,0,24,0,88,101,245,0.95,0.95,0.86,35,40},  // #41
  {"Golbat",7,9,3,1,0,6,24,41,104,116,455,1.14,1.14,1.06,70,75},  // #42
  {"Oddish",4,7,2,1,0,10,14,0,90,91,320,1.11,0.97,1.11,55,65},  // #43
  {"Gloom",4,7,2,1,0,9,14,0,97,95,395,1.17,1.06,1.17,70,75},  // #44
  {"Vileplume",4,7,3,1,0,0,14,0,104,99,490,1.31,1.14,1.31,85,90},  // #45
  {"Paras",11,4,1,1,0,0,33,0,86,88,285,1.08,1.08,0.95,55,55},  // #46
  {"Parasect",11,4,2,1,0,10,33,0,97,91,405,1.22,1.22,1.03,80,80},  // #47
  {"Venonat",11,7,1,1,0,0,33,0,97,97,305,1,1,0.92,50,55},  // #48
  {"Venomoth",11,7,3,1,0,0,33,0,102,116,450,1.2,1.06,1.2,60,75},  // #49
  {"Diglett",8,255,1,1,0,0,25,0,74,118,265,1,1,0.89,25,45},  // #50
  {"Dugtrio",8,255,3,1,0,6,25,50,86,128,425,1.25,1.25,0.97,50,70},  // #51
  {"Meowth",0,255,1,1,0,11,0,0,88,116,290,0.95,0.95,0.92,35,40},  // #52
  {"Persian",0,255,3,1,0,6,0,52,99,126,440,1.08,1.08,1.06,60,65},  // #53
  {"Psyduck",2,255,2,1,0,0,21,0,92,101,320,1.06,0.99,1.06,48,50},  // #54
  {"Golduck",2,255,4,1,0,0,10,0,106,114,500,1.22,1.15,1.22,78,80},  // #55
  {"Mankey",6,255,1,1,0,1,40,0,88,107,305,1.14,1.14,0.89,35,45},  // #56
  {"Primeape",6,255,3,1,0,6,40,56,99,118,455,1.28,1.28,1.03,60,70},  // #57
  {"Growlithe",1,255,2,1,0,2,6,0,95,103,350,1.08,1.08,1.08,45,50},  // #58
  {"Arcanine",1,255,4,1,0,6,6,58,110,118,555,1.31,1.31,1.25,80,80},  // #59
  {"Poliwag",2,255,1,1,0,0,10,0,88,116,300,0.97,0.97,0.92,40,40},  // #60
  {"Poliwhirl",2,255,2,1,0,0,10,0,99,116,385,1.06,1.06,0.97,65,50},  // #61
  {"Poliwrath",2,6,4,1,0,6,10,60,110,107,510,1.22,1.22,1.08,95,90},  // #62
  {"Abra",10,255,1,1,0,8,21,0,81,116,310,1.28,0.81,1.28,15,55},  // #63
  {"Kadabra",10,255,2,1,0,2,21,0,88,122,400,1.36,0.89,1.36,30,70},  // #64
  {"Alakazam",10,255,4,1,0,0,21,0,95,128,500,1.44,0.97,1.44,45,95},  // #65
  {"Machop",6,255,1,1,0,0,40,0,102,93,305,1.14,1.14,0.89,50,35},  // #66
  {"Machoke",6,255,2,1,0,0,40,0,106,97,405,1.25,1.25,0.97,70,60},  // #67
  {"Machamp",6,255,4,1,0,6,40,66,110,101,505,1.42,1.42,1.06,80,85},  // #68
  {"Bellsprout",4,7,1,1,0,0,14,0,92,95,300,1.11,1.11,1.08,35,30},  // #69
  {"Weepinbell",4,7,2,1,0,0,14,0,99,101,390,1.2,1.2,1.17,50,45},  // #70
  {"Victreebel",4,7,3,1,0,0,14,0,106,107,490,1.28,1.28,1.25,65,70},  // #71
  {"Tentacool",2,7,2,1,0,10,10,0,88,107,335,0.97,0.92,0.97,35,100},  // #72
  {"Tentacruel",2,7,4,1,0,6,10,72,106,120,515,1.14,1.08,1.14,65,120},  // #73
  {"Geodude",12,8,1,1,0,7,36,0,88,86,300,1.14,1.14,0.86,100,30},  // #74
  {"Graveler",12,8,2,1,0,7,36,0,95,93,390,1.22,1.22,0.95,115,45},  // #75
  {"Golem",12,8,4,1,0,7,36,0,106,97,495,1.36,1.36,1,130,65},  // #76
  {"Ponyta",1,255,3,1,0,9,6,0,92,116,410,1.17,1.17,1.06,55,65},  // #77
  {"Rapidash",1,255,4,1,0,6,6,77,99,122,500,1.25,1.25,1.14,70,80},  // #78
  {"Slowpoke",2,10,1,1,0,2,21,0,110,84,315,1.06,1.06,0.92,65,40},  // #79
  {"Slowbro",2,10,3,1,0,10,10,0,113,91,490,1.25,1.11,1.25,110,80},  // #80
  {"Magnemite",3,16,2,1,0,2,18,0,81,97,325,1.22,0.89,1.22,70,55},  // #81
  {"Magneton",3,16,3,1,0,6,18,81,92,107,465,1.36,1.03,1.36,95,70},  // #82
  {"Farfetch’d",0,9,2,1,0,1,0,0,93,103,377,1.2,1.2,1.02,55,62},  // #83
  {"Doduo",0,9,1,1,0,1,0,0,86,110,310,1.17,1.17,0.89,45,35},  // #84
  {"Dodrio",0,9,3,1,0,6,0,84,97,124,470,1.31,1.31,1.03,70,60},  // #85
  {"Seel",2,255,2,1,0,0,10,0,99,97,325,0.95,0.95,0.95,55,70},  // #86
  {"Dewgong",2,5,3,1,0,0,10,0,110,107,475,1.08,1.08,1.08,80,95},  // #87
  {"Grimer",7,255,2,1,0,0,24,0,106,88,325,1.14,1.14,0.92,50,50},  // #88
  {"Muk",7,255,4,1,0,0,24,0,117,99,500,1.28,1.28,1.06,75,100},  // #89
  {"Shellder",2,255,1,1,0,0,10,0,84,95,305,1.06,1.06,0.95,100,25},  // #90
  {"Cloyster",2,5,4,1,0,6,10,90,92,107,525,1.22,1.22,1.17,180,45},  // #91
  {"Gastly",13,7,1,1,0,0,43,0,84,112,310,1.25,0.89,1.25,30,35},  // #92
  {"Haunter",13,7,2,1,0,0,43,0,90,118,405,1.33,0.97,1.33,45,55},  // #93
  {"Gengar",13,7,4,1,0,2,43,0,97,124,500,1.42,1.06,1.42,60,75},  // #94
  {"Onix",12,8,2,1,0,5,36,0,86,107,385,0.95,0.95,0.86,160,45},  // #95
  {"Drowzee",10,255,2,1,0,2,21,0,97,96,328,0.96,0.96,0.94,45,90},  // #96
  {"Hypno",10,255,3,1,0,0,21,0,108,106,483,1.1,1.1,1.1,70,115},  // #97
  {"Krabby",2,255,2,1,0,0,10,0,84,99,325,1.28,1.28,0.84,90,25},  // #98
  {"Kingler",2,255,3,1,0,0,10,0,95,110,475,1.42,1.42,0.97,115,50},  // #99
  {"Voltorb",3,255,2,1,0,7,18,0,88,120,330,1,0.86,1,50,55},  // #100
  {"Electrode",3,255,3,1,0,7,18,0,97,141,490,1.14,0.97,1.14,70,80},  // #101
  {"Exeggcute",4,10,2,1,0,7,14,0,97,95,325,1.03,0.92,1.03,80,45},  // #102
  {"Exeggutor",4,10,4,1,0,0,14,0,113,101,530,1.39,1.22,1.39,85,75},  // #103
  {"Cubone",8,255,2,1,0,0,25,0,92,93,320,0.97,0.97,0.92,95,50},  // #104
  {"Marowak",8,255,3,1,0,11,25,0,97,97,425,1.14,1.14,0.97,110,80},  // #105
  {"Hitmonlee",6,255,3,1,0,0,40,0,92,115,455,1.36,1.36,0.89,53,110},  // #106
  {"Hitmonchan",6,255,3,1,0,1,40,0,92,110,455,1.28,1.28,0.89,79,110},  // #107
  {"Lickitung",0,255,2,1,0,1,0,0,110,91,385,1.03,1,1.03,75,75},  // #108
  {"Koffing",7,255,2,1,0,7,24,0,88,93,340,1.06,1.06,1.03,95,45},  // #109
  {"Weezing",7,255,3,1,0,7,24,0,99,103,490,1.2,1.2,1.17,120,70},  // #110
  {"Rhyhorn",8,12,2,1,0,1,25,0,106,88,345,1.17,1.17,0.86,95,30},  // #111
  {"Rhydon",8,12,3,1,0,9,25,0,117,95,485,1.42,1.42,0.95,120,45},  // #112
  {"Chansey",0,255,3,1,0,4,0,0,182,99,450,0.89,0.73,0.89,5,105},  // #113
  {"Tangela",4,255,3,1,0,0,14,0,99,103,435,1.25,1,1.25,115,40},  // #114
  {"Kangaskhan",0,255,3,1,0,11,0,0,117,116,490,1.22,1.22,0.92,80,80},  // #115
  {"Horsea",2,255,1,1,0,0,10,0,84,103,295,1.08,0.92,1.08,70,25},  // #116
  {"Seadra",2,255,3,1,0,6,10,116,95,114,440,1.22,1.06,1.22,95,45},  // #117
  {"Goldeen",2,255,2,1,0,10,10,0,90,104,320,1.07,1.07,0.89,60,50},  // #118
  {"Seaking",2,255,3,1,0,10,10,0,106,107,450,1.21,1.21,1.06,65,80},  // #119
  {"Staryu",2,255,2,1,0,0,10,0,84,114,340,1.08,0.95,1.08,55,55},  // #120
  {"Starmie",2,10,4,1,0,8,10,0,97,126,520,1.25,1.11,1.25,85,85},  // #121
  {"Mr. Mime",10,17,3,1,0,5,21,0,88,116,460,1.25,0.95,1.25,65,120},  // #122
  {"Scyther",11,9,4,1,0,6,33,0,102,122,500,1.31,1.31,1,80,80},  // #123
  {"Jynx",5,10,3,1,0,2,38,0,99,118,455,1.33,0.97,1.33,35,95},  // #124
  {"Electabuzz",3,255,3,1,0,0,18,0,99,122,490,1.22,1.16,1.22,57,85},  // #125
  {"Magmar",1,255,4,1,0,0,6,0,99,117,495,1.25,1.22,1.25,57,85},  // #126
  {"Pinsir",11,255,4,1,0,10,33,0,99,114,500,1.39,1.39,1,100,70},  // #127
  {"Tauros",0,255,3,1,0,11,0,0,104,124,490,1.25,1.25,0.92,95,70},  // #128
  {"Magikarp",2,255,1,1,0,10,10,0,79,112,200,0.78,0.76,0.78,55,20},  // #129
  {"Gyarados",2,9,4,1,0,6,10,129,113,112,540,1.39,1.39,1.03,79,100},  // #130
  {"Lapras",2,5,4,1,0,0,10,0,128,103,535,1.17,1.17,1.17,80,95},  // #131
  {"Ditto",0,255,1,1,0,0,0,0,92,98,288,0.96,0.96,0.96,48,48},  // #132
  {"Eevee",0,255,2,1,0,1,0,0,95,101,325,1,1,0.95,50,65},  // #133
  {"Vaporeon",2,255,4,1,0,2,10,0,128,105,525,1.31,1.06,1.31,60,95},  // #134
  {"Jolteon",3,255,4,1,0,2,18,0,99,133,525,1.31,1.06,1.31,60,95},  // #135
  {"Flareon",1,255,4,1,0,0,6,0,99,105,525,1.42,1.42,1.22,60,110},  // #136
  {"Porygon",0,255,2,1,0,11,0,0,99,95,395,1.17,1.03,1.17,70,75},  // #137
  {"Omanyte",12,2,2,1,0,2,36,0,86,93,355,1.2,0.92,1.2,100,55},  // #138
  {"Omastar",12,2,4,1,0,0,36,0,102,101,495,1.33,1.03,1.33,125,70},  // #139
  {"Kabuto",12,2,2,1,0,0,36,0,84,101,355,1.14,1.14,1,90,45},  // #140
  {"Kabutops",12,2,4,1,0,11,36,0,97,112,495,1.33,1.33,1.06,105,70},  // #141
  {"Aerodactyl",12,9,4,1,0,1,36,0,106,133,515,1.28,1.28,1.03,65,75},  // #142
  {"Snorlax",0,255,4,1,0,1,0,0,142,91,540,1.31,1.31,1.06,65,110},  // #143
  {"Articuno",5,9,5,1,1,0,38,0,110,114,580,1.22,1.17,1.22,100,125},  // #144
  {"Zapdos",3,9,5,1,1,0,18,0,110,120,580,1.39,1.2,1.39,85,90},  // #145
  {"Moltres",1,9,5,1,1,0,6,0,110,116,580,1.39,1.25,1.39,90,85},  // #146
  {"Dratini",14,255,1,1,0,0,44,0,88,99,300,1.05,1.05,0.97,45,50},  // #147
  {"Dragonair",14,255,3,1,0,0,44,0,97,107,420,1.16,1.16,1.08,65,70},  // #148
  {"Dragonite",14,9,4,1,0,0,44,0,111,112,600,1.44,1.44,1.25,95,100},  // #149
  {"Mewtwo",10,255,5,1,1,8,21,0,118,133,680,1.55,1.31,1.55,90,90},  // #150
  {"Mew",10,255,5,1,1,0,21,0,115,120,600,1.25,1.25,1.25,100,100},  // #151
  {"Chikorita",4,255,1,2,0,0,14,0,90,97,318,0.97,0.97,0.97,65,65},  // #152
  {"Bayleef",4,255,2,2,0,0,14,0,97,103,405,1.05,1.04,1.05,80,80},  // #153
  {"Meganium",4,255,4,2,0,0,14,0,106,112,525,1.16,1.15,1.16,100,100},  // #154
  {"Cyndaquil",1,255,1,2,0,0,6,0,88,105,309,1.03,0.99,1.03,43,50},  // #155
  {"Quilava",1,255,2,2,0,0,6,0,96,112,405,1.14,1.05,1.14,58,65},  // #156
  {"Typhlosion",1,255,4,2,0,0,6,0,105,120,534,1.3,1.16,1.3,78,85},  // #157
  {"Totodile",2,255,1,2,0,0,10,0,92,96,314,1.06,1.06,0.94,64,48},  // #158
  {"Croconaw",2,255,2,2,0,0,10,0,99,102,405,1.14,1.14,1.02,80,63},  // #159
  {"Feraligatr",2,255,4,2,0,0,10,0,108,111,530,1.28,1.28,1.13,100,83},  // #160
  {"Sentret",0,255,1,2,0,0,0,0,86,86,215,0.95,0.95,0.89,34,45},  // #161
  {"Furret",0,255,3,2,0,0,0,0,108,116,415,1.12,1.12,0.95,64,55},  // #162
  {"Hoothoot",0,9,1,2,0,1,0,0,97,99,262,0.9,0.86,0.9,30,56},  // #163
  {"Noctowl",0,9,3,2,0,0,0,0,115,107,452,1.17,0.97,1.17,50,96},  // #164
  {"Ledyba",11,9,1,2,0,6,33,0,88,101,265,0.92,0.81,0.92,30,80},  // #165
  {"Ledian",11,9,2,2,0,0,33,0,95,114,390,1,0.89,1,50,110},  // #166
  {"Spinarak",11,7,1,2,0,10,33,0,88,91,250,1.03,1.03,0.92,40,40},  // #167
  {"Ariados",11,7,2,2,0,6,33,167,102,95,400,1.2,1.2,1.03,70,70},  // #168
  {"Crobat",7,9,4,2,0,6,24,41,108,133,535,1.2,1.2,1.08,80,80},  // #169
  {"Chinchou",2,3,2,2,0,8,10,0,104,106,330,1.01,0.91,1.01,38,56},  // #170
  {"Lanturn",2,3,3,2,0,0,10,0,126,106,460,1.12,1.02,1.12,58,76},  // #171
  {"Pichu",3,255,1,2,0,2,18,0,79,103,205,0.92,0.92,0.89,15,35},  // #172
  {"Cleffa",17,255,1,2,0,4,46,0,92,84,218,0.95,0.84,0.95,28,55},  // #173
  {"Igglybuff",0,17,1,2,0,0,0,0,110,84,210,0.92,0.86,0.92,15,20},  // #174
  {"Togepi",17,255,1,2,0,2,46,0,86,86,245,0.92,0.81,0.92,65,65},  // #175
  {"Togetic",17,9,2,2,0,10,46,0,95,95,405,1.14,0.92,1.14,85,105},  // #176
  {"Natu",10,9,2,2,0,8,21,0,88,107,320,1.08,0.97,1.08,45,45},  // #177
  {"Xatu",10,9,3,2,0,0,21,0,99,118,470,1.22,1.11,1.22,70,70},  // #178
  {"Mareep",3,255,1,2,0,0,18,0,95,93,280,1.06,0.92,1.06,40,45},  // #179
  {"Flaaffy",3,255,2,2,0,0,18,0,102,97,365,1.14,1,1.14,55,60},  // #180
  {"Ampharos",3,255,4,2,0,0,18,0,110,101,510,1.33,1.11,1.33,85,90},  // #181
  {"Bellossom",4,255,3,2,0,0,14,0,104,99,490,1.2,1.14,1.2,95,100},  // #182
  {"Marill",2,17,1,2,0,4,10,0,102,95,250,0.81,0.81,0.81,50,50},  // #183
  {"Azumarill",2,17,3,2,0,4,10,0,115,99,420,1.03,0.97,1.03,80,80},  // #184
  {"Sudowoodo",12,255,3,2,0,1,36,0,102,91,410,1.25,1.25,0.86,115,65},  // #185
  {"Politoed",2,255,4,2,0,10,10,0,110,107,500,1.2,1.11,1.2,75,100},  // #186
  {"Hoppip",4,9,1,2,0,0,14,0,86,99,250,0.89,0.89,0.89,40,55},  // #187
  {"Skiploom",4,9,2,2,0,0,14,0,95,112,340,0.95,0.95,0.95,50,65},  // #188
  {"Jumpluff",4,9,3,2,0,0,14,0,104,124,460,1,1,1,70,95},  // #189
  {"Aipom",0,255,2,2,0,1,0,0,95,114,360,1.08,1.08,0.92,55,55},  // #190
  {"Sunkern",4,255,1,2,0,0,14,0,84,91,180,0.86,0.86,0.86,30,30},  // #191
  {"Sunflora",4,255,3,2,0,0,14,0,104,91,425,1.28,1.11,1.28,55,85},  // #192
  {"Yanma",11,9,2,2,0,6,33,0,99,118,390,1.11,1.06,1.11,45,45},  // #193
  {"Wooper",2,8,1,2,0,0,10,0,95,84,210,0.95,0.95,0.84,45,25},  // #194
  {"Quagsire",2,8,3,2,0,3,10,0,113,93,430,1.17,1.17,1.06,85,65},  // #195
  {"Espeon",10,255,4,2,0,0,21,0,99,124,525,1.42,1.06,1.42,60,95},  // #196
  {"Umbreon",15,255,4,2,0,0,50,0,113,105,525,1.06,1.06,1.03,110,130},  // #197
  {"Murkrow",15,9,2,2,0,0,50,0,97,116,405,1.17,1.17,1.17,42,42},  // #198
  {"Slowking",2,10,3,2,0,6,10,79,113,91,490,1.25,1.11,1.25,80,110},  // #199
  {"Misdreavus",13,255,3,2,0,2,43,0,97,114,435,1.17,1.03,1.17,60,85},  // #200
  {"Unown",10,255,2,2,0,0,21,0,92,98,336,1.1,1.1,1.1,48,48},  // #201
  {"Wobbuffet",10,255,2,2,0,3,21,0,156,92,405,0.88,0.88,0.88,58,58},  // #202
  {"Girafarig",0,10,3,2,0,0,0,0,102,114,455,1.2,1.14,1.2,65,65},  // #203
  {"Pineco",11,255,1,2,0,0,33,0,92,84,290,1.06,1.06,0.89,90,35},  // #204
  {"Forretress",11,16,3,2,0,10,33,0,104,95,465,1.2,1.2,1.03,140,60},  // #205
  {"Dunsparce",0,255,3,2,0,3,0,0,115,97,415,1.08,1.08,1.06,70,65},  // #206
  {"Gligar",8,9,3,2,0,1,25,0,99,114,430,1.11,1.11,0.89,105,65},  // #207
  {"Steelix",16,8,4,2,0,5,48,0,104,91,510,1.17,1.17,1,200,65},  // #208
  {"Snubbull",17,255,1,2,0,0,46,0,97,91,300,1.14,1.14,0.92,50,40},  // #209
  {"Granbull",17,255,3,2,0,10,46,0,110,97,450,1.36,1.36,1.03,75,60},  // #210
  {"Qwilfish",2,7,3,2,0,10,10,0,99,114,440,1.22,1.22,1,85,55},  // #211
  {"Scizor",11,16,4,2,0,0,33,0,102,105,500,1.42,1.42,1,100,80},  // #212
  {"Shuckle",11,12,4,2,0,5,33,0,79,80,505,0.76,0.76,0.76,230,230},  // #213
  {"Heracross",11,6,4,2,0,6,33,0,106,114,500,1.39,1.39,0.92,75,95},  // #214
  {"Sneasel",15,5,3,2,0,1,50,0,95,126,430,1.22,1.22,0.89,55,75},  // #215
  {"Teddiursa",0,255,2,2,0,1,0,0,97,95,330,1.14,1.14,0.97,50,50},  // #216
  {"Ursaring",0,255,4,2,0,0,0,0,110,101,500,1.42,1.42,1.11,75,75},  // #217
  {"Slugma",1,255,1,2,0,9,6,0,88,86,250,1.08,0.92,1.08,40,40},  // #218
  {"Magcargo",1,12,3,2,0,11,6,0,97,91,430,1.2,0.97,1.2,120,80},  // #219
  {"Swinub",5,8,1,2,0,8,38,0,92,99,250,0.97,0.97,0.86,40,30},  // #220
  {"Piloswine",5,8,3,2,0,1,38,0,115,99,450,1.25,1.25,1.03,80,60},  // #221
  {"Corsola",2,12,3,2,0,0,10,0,99,93,410,1.06,1,1.06,95,95},  // #222
  {"Remoraid",2,255,1,2,0,0,10,0,86,105,300,1.06,1.06,1.06,35,35},  // #223
  {"Octillery",2,255,3,2,0,0,10,0,104,97,480,1.28,1.28,1.28,75,75},  // #224
  {"Delibird",5,9,2,2,0,2,38,0,90,110,330,1.06,1,1.06,45,45},  // #225
  {"Mantine",2,9,3,2,0,2,10,0,108,107,485,1.14,0.92,1.14,70,140},  // #226
  {"Skarmory",16,9,3,2,0,5,48,0,99,107,465,1.14,1.14,0.92,140,70},  // #227
  {"Houndour",15,1,2,2,0,9,50,0,90,105,330,1.14,1.03,1.14,30,50},  // #228
  {"Houndoom",15,1,4,2,0,9,50,0,104,118,500,1.31,1.2,1.31,50,80},  // #229
  {"Kingdra",2,14,4,2,0,6,10,116,104,114,540,1.22,1.22,1.22,95,95},  // #230
  {"Phanpy",8,255,2,2,0,11,25,0,110,95,330,1.03,1.03,0.92,60,40},  // #231
  {"Donphan",8,255,4,2,0,11,25,0,110,99,500,1.36,1.36,1.03,120,60},  // #232
  {"Porygon2",0,255,4,2,0,1,0,0,108,103,515,1.28,1.14,1.28,90,95},  // #233
  {"Stantler",0,255,3,2,0,0,0,0,103,114,465,1.22,1.22,1.17,62,65},  // #234
  {"Smeargle",0,255,1,2,0,0,0,0,95,110,250,0.81,0.81,0.81,35,45},  // #235
  {"Tyrogue",6,255,1,2,0,0,40,0,86,93,210,0.89,0.89,0.89,35,35},  // #236
  {"Hitmontop",6,255,3,2,0,1,40,0,92,107,455,1.22,1.22,0.89,95,110},  // #237
  {"Smoochum",5,10,1,2,0,0,38,0,90,105,305,1.17,0.86,1.17,15,65},  // #238
  {"Elekid",3,255,2,2,0,0,18,0,90,118,360,1.06,1.05,1.06,37,55},  // #239
  {"Magby",1,255,2,2,0,0,6,0,90,113,365,1.11,1.11,1.08,37,55},  // #240
  {"Miltank",0,255,3,2,0,1,0,0,113,120,490,1.14,1.14,0.92,105,70},  // #241
  {"Blissey",0,255,4,2,0,4,0,0,185,101,540,1.11,0.76,1.11,10,135},  // #242
  {"Raikou",3,255,5,2,1,8,18,0,110,126,580,1.33,1.17,1.33,75,100},  // #243
  {"Entei",1,255,5,2,1,0,6,0,122,120,580,1.33,1.33,1.2,85,75},  // #244
  {"Suicune",2,255,5,2,1,0,10,0,115,114,580,1.2,1.11,1.2,115,115},  // #245
  {"Larvitar",12,8,1,2,0,1,36,0,92,95,300,1.05,1.05,0.95,50,50},  // #246
  {"Pupitar",12,8,3,2,0,0,36,0,102,99,410,1.16,1.16,1.06,70,70},  // #247
  {"Tyranitar",12,15,4,2,0,0,36,0,115,104,600,1.44,1.44,1.22,110,100},  // #248
  {"Lugia",10,9,5,2,1,0,21,0,118,124,680,1.2,1.2,1.2,130,154},  // #249
  {"Ho-Oh",1,9,5,2,1,9,6,0,118,116,680,1.42,1.42,1.31,90,154},  // #250
  {"Celebi",10,4,5,2,1,8,21,0,115,120,600,1.25,1.25,1.25,100,100},  // #251
  {"Treecko",4,255,1,3,0,0,15,0,88,107,310,1.06,0.95,1.06,35,55},  // #252
  {"Grovyle",4,255,2,3,0,0,14,0,92,118,405,1.17,1.06,1.17,45,65},  // #253
  {"Sceptile",4,255,4,3,0,0,14,0,102,128,530,1.28,1.17,1.28,65,85},  // #254
  {"Torchic",1,255,1,3,0,0,6,0,90,97,310,1.08,1.03,1.08,40,50},  // #255
  {"Combusken",1,6,2,3,0,0,6,0,97,101,405,1.17,1.17,1.17,60,60},  // #256
  {"Blaziken",1,6,4,3,0,9,6,0,106,112,530,1.36,1.36,1.31,70,70},  // #257
  {"Mudkip",2,255,1,3,0,0,10,0,92,95,310,1.08,1.08,0.97,50,50},  // #258
  {"Marshtomp",2,8,2,3,0,11,10,0,102,99,405,1.17,1.17,1.03,70,70},  // #259
  {"Swampert",2,8,4,3,0,11,10,0,115,103,535,1.31,1.31,1.17,90,90},  // #260
  {"Poochyena",15,255,1,3,0,1,50,0,86,93,220,1,1,0.86,35,30},  // #261
  {"Mightyena",15,255,3,3,0,6,50,261,102,107,420,1.2,1.2,1.03,70,60},  // #262
  {"Zigzagoon",0,255,1,3,0,1,0,0,87,103,240,0.86,0.86,0.86,41,41},  // #263
  {"Linoone",0,255,3,3,0,1,0,0,105,120,420,1.08,1.08,0.97,61,61},  // #264
  {"Wurmple",11,255,1,3,0,10,33,0,90,86,195,0.95,0.95,0.81,35,30},  // #265
  {"Silcoon",11,255,1,3,0,6,33,0,92,84,205,0.89,0.89,0.84,55,25},  // #266
  {"Beautifly",11,9,2,3,0,0,33,0,97,105,395,1.25,1.08,1.25,50,50},  // #267
  {"Cascoon",11,255,1,3,0,0,33,0,92,84,205,0.89,0.89,0.84,55,25},  // #268
  {"Dustox",11,7,2,3,0,6,33,0,97,105,385,0.97,0.97,0.97,70,90},  // #269
  {"Lotad",2,4,1,3,0,0,10,0,88,91,220,0.92,0.86,0.92,30,50},  // #270
  {"Lombre",2,4,2,3,0,2,10,0,97,99,340,1.03,0.97,1.03,50,70},  // #271
  {"Ludicolo",2,4,3,3,0,2,10,0,106,107,480,1.2,1.08,1.2,70,100},  // #272
  {"Seedot",4,255,1,3,0,10,14,0,88,91,220,0.92,0.92,0.86,50,30},  // #273
  {"Nuzleaf",4,15,2,3,0,10,14,0,102,103,340,1.08,1.08,1.03,40,40},  // #274
  {"Shiftry",4,15,3,3,0,0,14,0,110,112,480,1.25,1.25,1.2,60,60},  // #275
  {"Taillow",0,9,1,3,0,0,0,0,88,114,270,1,1,0.86,30,30},  // #276
  {"Swellow",0,9,3,3,0,1,0,0,97,130,455,1.17,1.17,1.11,60,50},  // #277
  {"Wingull",2,9,1,3,0,0,10,0,88,114,270,1,0.86,1,30,30},  // #278
  {"Pelipper",2,9,3,3,0,0,10,0,97,105,440,1.22,0.97,1.22,100,70},  // #279
  {"Ralts",10,17,1,3,0,0,21,0,83,95,198,0.95,0.84,0.95,25,35},  // #280
  {"Kirlia",10,17,1,3,0,0,21,0,87,99,278,1.06,0.89,1.06,35,55},  // #281
  {"Gardevoir",10,17,4,3,0,0,21,0,101,112,518,1.39,1.06,1.39,65,115},  // #282
  {"Surskit",11,2,1,3,0,6,33,0,88,105,269,0.97,0.86,0.97,32,52},  // #283
  {"Masquerain",11,9,3,3,0,0,33,0,102,112,454,1.25,1.03,1.25,62,82},  // #284
  {"Shroomish",4,255,1,3,0,0,14,0,97,93,295,0.92,0.92,0.92,60,60},  // #285
  {"Breloom",4,6,3,3,0,1,14,0,97,107,460,1.42,1.42,1.03,80,60},  // #286
  {"Slakoth",0,255,1,3,0,0,0,0,97,91,280,1.03,1.03,0.89,60,35},  // #287
  {"Vigoroth",0,255,3,3,0,0,0,0,106,116,440,1.14,1.14,1,80,55},  // #288
  {"Slaking",0,255,4,3,0,1,0,0,138,120,670,1.58,1.58,1.22,100,65},  // #289
  {"Nincada",11,8,1,3,0,9,33,0,84,95,266,0.95,0.95,0.86,90,30},  // #290
  {"Ninjask",11,9,3,3,0,10,33,0,97,145,456,1.2,1.2,0.97,45,50},  // #291
  {"Shedinja",11,13,1,3,0,0,33,0,70,95,236,1.2,1.2,0.86,45,30},  // #292
  {"Whismur",0,255,1,3,0,1,0,0,99,90,240,0.98,0.98,0.98,23,23},  // #293
  {"Loudred",0,255,2,3,0,1,0,0,108,98,360,1.09,1.09,1.09,43,43},  // #294
  {"Exploud",0,255,3,3,0,0,0,0,117,107,490,1.2,1.2,1.2,63,73},  // #295
  {"Makuhita",6,255,1,3,0,1,40,0,102,88,237,1.03,1.03,0.81,30,30},  // #296
  {"Hariyama",6,255,3,3,0,0,40,0,135,99,474,1.36,1.36,0.92,60,60},  // #297
  {"Azurill",0,17,1,3,0,2,0,0,92,86,190,0.81,0.81,0.81,40,40},  // #298
  {"Nosepass",12,255,2,3,0,1,36,0,84,91,375,0.95,0.95,0.95,135,90},  // #299
  {"Skitty",0,255,1,3,0,1,0,0,92,99,260,0.95,0.95,0.89,45,35},  // #300
  {"Delcatty",0,255,2,3,0,4,0,0,102,116,400,1.06,1.06,1,65,55},  // #301
  {"Sableye",15,13,2,3,0,2,50,0,92,99,380,1.11,1.11,1.06,75,65},  // #302
  {"Mawile",16,17,2,3,0,0,48,0,92,99,380,1.17,1.17,1,85,55},  // #303
  {"Aron",16,12,2,3,0,11,48,0,92,91,330,1.08,1.08,0.92,100,40},  // #304
  {"Lairon",16,12,3,3,0,1,48,0,97,95,430,1.2,1.2,0.97,140,50},  // #305
  {"Aggron",16,12,4,3,0,5,48,0,102,99,530,1.31,1.31,1.03,180,60},  // #306
  {"Meditite",6,10,1,3,0,8,40,0,84,103,280,0.92,0.92,0.92,55,55},  // #307
  {"Medicham",6,10,3,3,0,2,40,0,97,112,410,1.03,1.03,1.03,75,75},  // #308
  {"Electrike",3,255,1,3,0,0,18,0,88,105,295,1.06,0.95,1.06,40,40},  // #309
  {"Manectric",3,255,3,3,0,0,18,0,102,122,475,1.28,1.11,1.28,60,60},  // #310
  {"Plusle",3,255,2,3,0,0,18,0,97,118,405,1.17,0.97,1.17,40,75},  // #311
  {"Minun",3,255,2,3,0,8,18,0,97,118,405,1.11,0.92,1.11,50,85},  // #312
  {"Volbeat",11,255,3,3,0,0,33,0,99,114,430,1.1,1.1,0.96,75,85},  // #313
  {"Illumise",11,255,3,3,0,6,33,0,99,114,430,1.1,0.96,1.1,75,85},  // #314
  {"Roselia",4,7,2,3,0,0,14,0,92,105,400,1.25,1.03,1.25,45,80},  // #315
  {"Gulpin",7,255,1,3,0,0,24,0,102,95,302,0.94,0.94,0.94,53,53},  // #316
  {"Swalot",7,255,3,3,0,9,24,0,115,101,467,1.1,1.1,1.1,83,83},  // #317
  {"Carvanha",2,15,1,3,0,0,10,0,90,105,305,1.2,1.2,1.06,20,20},  // #318
  {"Sharpedo",2,15,3,3,0,0,10,0,102,118,460,1.36,1.36,1.22,40,40},  // #319
  {"Wailmer",2,255,2,3,0,0,10,0,128,103,400,1.08,1.08,1.08,35,35},  // #320
  {"Wailord",2,255,4,3,0,0,10,0,146,103,500,1.2,1.2,1.2,45,45},  // #321
  {"Numel",1,8,1,3,0,0,6,0,97,93,305,1.06,1.03,1.06,40,45},  // #322
  {"Camerupt",1,8,3,3,0,11,6,0,102,95,460,1.28,1.25,1.28,70,75},  // #323
  {"Torkoal",1,255,3,3,0,0,6,0,102,86,470,1.17,1.17,1.17,140,70},  // #324
  {"Spoink",10,255,2,3,0,0,21,0,97,103,330,1.08,0.84,1.08,35,80},  // #325
  {"Grumpig",10,255,3,3,0,0,21,0,106,112,470,1.2,0.95,1.2,65,110},  // #326
  {"Spinda",0,255,2,3,0,0,0,0,97,103,360,1.03,1.03,1.03,60,60},  // #327
  {"Trapinch",8,255,1,3,0,0,25,0,90,82,290,1.25,1.25,0.95,45,45},  // #328
  {"Vibrava",8,14,2,3,0,0,25,0,92,107,340,1.08,1.08,0.97,50,50},  // #329
  {"Flygon",8,14,4,3,0,11,25,0,106,120,520,1.25,1.25,1.14,80,80},  // #330
  {"Cacnea",4,255,2,3,0,0,14,0,92,93,335,1.17,1.17,1.17,40,40},  // #331
  {"Cacturne",4,15,3,3,0,1,14,0,102,101,475,1.33,1.33,1.33,60,60},  // #332
  {"Swablu",0,9,1,3,0,0,0,0,90,99,310,0.92,0.92,0.92,60,75},  // #333
  {"Altaria",14,9,3,3,0,6,44,333,104,112,490,1.08,1.08,1.08,90,105},  // #334
  {"Zangoose",0,255,3,3,0,11,0,0,103,116,458,1.33,1.33,1.03,60,60},  // #335
  {"Seviper",7,255,3,3,0,0,24,0,103,105,458,1.25,1.25,1.25,60,60},  // #336
  {"Lunatone",12,10,3,3,0,7,36,0,110,107,460,1.22,1,1.22,65,85},  // #337
  {"Solrock",12,10,3,3,0,7,36,0,110,107,460,1.22,1.22,1,85,65},  // #338
  {"Barboach",2,8,1,3,0,1,10,0,92,103,288,0.96,0.96,0.95,43,41},  // #339
  {"Whiscash",2,8,3,3,0,9,10,0,120,103,468,1.13,1.13,1.12,73,71},  // #340
  {"Corphish",2,255,1,3,0,0,10,0,89,93,308,1.14,1.14,0.97,65,35},  // #341
  {"Crawdaunt",2,15,3,3,0,0,10,0,98,101,468,1.36,1.36,1.2,85,55},  // #342
  {"Baltoy",8,10,1,3,0,7,25,0,88,101,300,0.92,0.92,0.92,55,70},  // #343
  {"Claydol",8,10,4,3,0,7,25,0,97,110,500,1.08,1.08,1.08,105,120},  // #344
  {"Lileep",12,4,2,3,0,10,36,0,100,88,355,1.04,0.93,1.04,77,87},  // #345
  {"Cradily",12,4,4,3,0,11,36,0,109,96,495,1.15,1.15,1.15,97,107},  // #346
  {"Anorith",12,11,2,3,0,0,36,0,90,110,355,1.22,1.22,0.92,50,50},  // #347
  {"Armaldo",12,11,4,3,0,1,36,0,104,97,495,1.39,1.39,1.08,100,80},  // #348
  {"Feebas",2,255,1,3,0,0,10,0,79,112,200,0.78,0.78,0.76,20,55},  // #349
  {"Milotic",2,255,4,3,0,0,10,0,113,112,540,1.25,1.03,1.25,79,125},  // #350
  {"Castform",0,255,3,3,0,1,0,0,102,107,420,1.08,1.08,1.08,70,70},  // #351
  {"Kecleon",0,255,3,3,0,1,0,0,97,95,440,1.2,1.2,1.03,70,120},  // #352
  {"Shuppet",13,255,1,3,0,0,43,0,90,97,295,1.11,1.11,1.05,35,33},  // #353
  {"Banette",13,255,3,3,0,2,43,0,99,105,455,1.33,1.33,1.16,65,63},  // #354
  {"Duskull",13,255,1,3,0,0,43,0,79,88,295,0.92,0.92,0.86,90,90},  // #355
  {"Dusclops",13,255,3,3,0,2,43,0,88,88,455,1.08,1.08,1.03,130,130},  // #356
  {"Tropius",4,9,3,3,0,0,14,0,115,99,460,1.1,1.07,1.1,83,87},  // #357
  {"Chimecho",10,255,3,3,0,0,21,0,104,105,455,1.22,0.97,1.22,80,90},  // #358
  {"Absol",15,255,3,3,0,1,50,0,99,110,465,1.42,1.42,1.11,60,60},  // #359
  {"Wynaut",10,255,1,3,0,3,21,0,113,88,260,0.83,0.83,0.83,48,48},  // #360
  {"Snorunt",5,255,1,3,0,0,38,0,92,99,300,0.97,0.97,0.97,50,50},  // #361
  {"Glalie",5,255,3,3,0,0,38,0,106,112,480,1.14,1.14,1.14,80,80},  // #362
  {"Spheal",5,2,1,3,0,0,38,0,102,88,290,1,0.92,1,50,50},  // #363
  {"Sealeo",5,2,3,3,0,0,38,0,110,97,410,1.11,1.03,1.11,70,70},  // #364
  {"Walrein",5,2,4,3,0,0,38,0,120,105,530,1.22,1.14,1.22,90,90},  // #365
  {"Clamperl",2,255,2,3,0,0,10,0,86,91,345,1.11,1.05,1.11,85,55},  // #366
  {"Huntail",2,255,3,3,0,2,10,0,95,100,485,1.27,1.27,1.22,105,75},  // #367
  {"Gorebyss",2,255,3,3,0,0,10,0,95,100,485,1.33,1.16,1.33,105,75},  // #368
  {"Relicanth",2,12,3,3,0,0,10,0,115,101,485,1.2,1.2,0.95,130,65},  // #369
  {"Luvdisc",2,255,2,3,0,0,10,0,89,119,330,0.92,0.86,0.92,55,65},  // #370
  {"Bagon",14,255,1,3,0,8,44,0,90,99,300,1.11,1.11,0.92,60,30},  // #371
  {"Shelgon",14,255,3,3,0,0,44,0,99,99,420,1.22,1.22,1.03,100,50},  // #372
  {"Salamence",14,9,4,3,0,8,44,0,113,120,600,1.44,1.44,1.31,80,80},  // #373
  {"Beldum",16,10,1,3,0,0,48,0,88,91,300,1,1,0.89,80,60},  // #374
  {"Metang",16,10,3,3,0,5,48,0,97,99,420,1.11,1.11,1,100,80},  // #375
  {"Metagross",16,10,4,3,0,2,48,0,106,107,600,1.44,1.44,1.22,130,90},  // #376
  {"Regirock",12,255,5,3,1,11,36,0,106,99,580,1.25,1.25,0.97,200,100},  // #377
  {"Regice",5,255,5,3,1,8,38,0,106,99,580,1.25,0.97,1.25,100,200},  // #378
  {"Registeel",16,255,5,3,1,1,48,0,106,99,580,1.11,1.11,1.11,150,150},  // #379
  {"Latias",14,10,5,3,1,0,44,0,106,124,600,1.31,1.14,1.31,90,130},  // #380
  {"Latios",14,10,5,3,1,0,44,0,106,124,600,1.42,1.2,1.42,80,110},  // #381
  {"Kyogre",2,255,5,3,1,0,10,0,115,116,670,1.52,1.25,1.52,90,140},  // #382
  {"Groudon",8,255,5,3,1,1,25,0,115,116,670,1.52,1.52,1.25,140,90},  // #383
  {"Rayquaza",14,9,5,3,1,8,44,0,117,118,680,1.52,1.52,1.52,90,90},  // #384
  {"Jirachi",16,10,5,3,1,2,48,0,115,120,600,1.25,1.25,1.25,100,100},  // #385
  {"Deoxys",10,255,5,3,1,0,21,0,92,141,600,1.52,1.52,1.52,50,50},  // #386
  {"Turtwig",4,255,1,4,0,0,14,0,95,91,318,1.07,1.07,0.95,64,55},  // #387
  {"Grotle",4,255,2,4,0,0,14,0,104,93,405,1.19,1.19,1,85,65},  // #388
  {"Torterra",4,8,4,4,0,9,14,0,113,102,525,1.3,1.3,1.11,105,85},  // #389
  {"Chimchar",1,255,1,4,0,9,6,0,90,104,309,1.02,1.02,1.02,44,44},  // #390
  {"Monferno",1,6,2,4,0,9,6,0,99,112,405,1.13,1.13,1.13,52,52},  // #391
  {"Infernape",1,6,4,4,0,0,6,0,104,123,534,1.27,1.27,1.27,71,71},  // #392
  {"Piplup",2,255,1,4,0,0,11,0,94,95,314,1.04,0.98,1.04,53,56},  // #393
  {"Prinplup",2,255,2,4,0,0,10,0,99,99,405,1.15,1.06,1.15,68,76},  // #394
  {"Empoleon",2,16,4,4,0,1,10,0,108,103,530,1.31,1.17,1.31,88,101},  // #395
  {"Starly",0,9,1,4,0,1,0,0,88,103,245,1,1,0.86,30,30},  // #396
  {"Staravia",0,9,2,4,0,1,0,0,95,112,340,1.11,1.11,0.92,50,40},  // #397
  {"Staraptor",0,9,3,4,0,1,0,0,108,120,485,1.36,1.36,0.97,70,60},  // #398
  {"Bidoof",0,255,1,4,0,1,0,0,97,91,250,0.95,0.95,0.89,40,40},  // #399
  {"Bibarel",0,2,3,4,0,10,0,0,106,108,410,1.17,1.17,1,60,60},  // #400
  {"Kricketot",11,255,1,4,0,10,33,0,87,88,194,0.84,0.84,0.84,41,41},  // #401
  {"Kricketune",11,255,2,4,0,0,33,0,105,105,384,1.17,1.17,1,51,51},  // #402
  {"Shinx",3,255,1,4,0,2,18,0,90,97,263,1.06,1.06,0.92,34,34},  // #403
  {"Luxio",3,255,2,4,0,2,18,0,97,103,363,1.17,1.17,1.03,49,49},  // #404
  {"Luxray",3,255,4,4,0,6,18,403,106,107,523,1.36,1.36,1.22,79,79},  // #405
  {"Budew",4,7,1,4,0,0,14,0,88,101,280,0.97,0.86,0.97,35,70},  // #406
  {"Roserade",4,7,4,4,0,0,14,0,97,116,515,1.39,1.08,1.39,65,105},  // #407
  {"Cranidos",12,255,2,4,0,1,36,0,100,102,350,1.39,1.39,0.86,40,30},  // #408
  {"Rampardos",12,255,4,4,0,0,36,0,114,102,495,1.61,1.61,1.06,60,50},  // #409
  {"Shieldon",12,16,2,4,0,5,36,0,84,91,350,0.93,0.93,0.93,118,88},  // #410
  {"Bastiodon",12,16,4,4,0,5,36,0,97,91,495,0.99,0.99,0.96,168,138},  // #411
  {"Burmy",11,255,1,4,0,0,33,0,88,93,224,0.86,0.86,0.86,45,45},  // #412
  {"Wormadam",11,4,3,4,0,6,33,0,97,93,424,1.13,1.02,1.13,85,105},  // #413
  {"Mothim",11,9,3,4,0,0,33,0,102,106,424,1.22,1.22,1.22,50,50},  // #414
  {"Combee",11,9,1,4,0,0,33,0,84,107,244,0.86,0.86,0.86,42,42},  // #415
  {"Vespiquen",11,9,3,4,0,6,33,415,102,95,474,1.14,1.14,1.14,102,102},  // #416
  {"Pachirisu",3,255,2,4,0,2,18,0,97,118,405,0.95,0.95,0.95,70,90},  // #417
  {"Buizel",2,255,2,4,0,0,10,0,95,114,330,1.06,1.06,1.03,35,30},  // #418
  {"Floatzel",2,255,4,4,0,2,10,0,108,126,495,1.28,1.28,1.17,55,50},  // #419
  {"Cherubi",4,255,1,4,0,0,14,0,90,93,275,1.04,0.89,1.04,45,53},  // #420
  {"Cherrim",4,255,3,4,0,0,14,0,102,114,450,1.18,1.03,1.18,70,78},  // #421
  {"Shellos",2,255,2,4,0,0,10,0,104,92,325,1.01,0.96,1.01,48,62},  // #422
  {"Gastrodon",2,8,3,4,0,3,10,0,120,94,475,1.21,1.16,1.21,68,82},  // #423
  {"Ambipom",0,255,3,4,0,0,0,0,104,126,482,1.25,1.25,1.03,66,66},  // #424
  {"Drifloon",13,9,2,4,0,0,43,0,110,107,348,1.03,0.97,1.03,34,44},  // #425
  {"Drifblim",13,9,4,4,0,2,43,0,138,112,498,1.2,1.14,1.2,44,54},  // #426
  {"Buneary",0,255,2,4,0,0,0,0,95,114,350,1.06,1.06,0.94,44,56},  // #427
  {"Lopunny",0,255,3,4,0,0,0,0,99,122,480,1.12,1.12,1,84,96},  // #428
  {"Mismagius",13,255,4,4,0,0,43,0,97,122,495,1.28,1.03,1.28,60,105},  // #429
  {"Honchkrow",15,9,4,4,0,1,50,0,115,108,505,1.39,1.39,1.28,52,52},  // #430
  {"Glameow",0,255,1,4,0,1,0,0,92,114,310,1,1,0.93,42,37},  // #431
  {"Purugly",0,255,3,4,0,0,0,0,102,125,452,1.15,1.15,1.05,64,59},  // #432
  {"Chingling",10,255,1,4,0,2,21,0,90,97,285,1.06,0.86,1.06,50,50},  // #433
  {"Stunky",7,15,2,4,0,0,24,0,98,109,329,1.05,1.05,0.93,47,41},  // #434
  {"Skuntank",7,15,3,4,0,0,24,0,116,113,479,1.21,1.21,1.09,67,61},  // #435
  {"Bronzor",16,10,1,4,0,5,48,0,96,88,300,0.83,0.83,0.83,86,86},  // #436
  {"Bronzong",16,10,4,4,0,5,48,0,100,92,500,1.19,1.19,1.13,116,116},  // #437
  {"Bonsly",12,255,1,4,0,0,36,0,92,82,290,1.14,1.14,0.76,95,45},  // #438
  {"Mime Jr.",10,17,1,4,0,5,21,0,79,103,310,1.08,0.84,1.08,45,90},  // #439
  {"Happiny",0,255,1,4,0,4,0,0,115,91,220,0.78,0.73,0.78,5,65},  // #440
  {"Chatot",0,9,3,4,0,1,0,0,104,116,411,1.21,1.06,1.21,45,42},  // #441
  {"Spiritomb",13,15,3,4,0,2,43,0,92,93,485,1.21,1.21,1.21,108,108},  // #442
  {"Gible",14,8,1,4,0,0,44,0,96,96,300,1.08,1.08,0.92,45,45},  // #443
  {"Gabite",14,8,3,4,0,0,44,0,101,112,410,1.2,1.2,0.97,65,55},  // #444
  {"Garchomp",14,8,4,4,0,8,44,0,119,121,600,1.42,1.42,1.14,95,85},  // #445
  {"Munchlax",0,255,2,4,0,3,0,0,131,80,390,1.17,1.17,0.92,40,85},  // #446
  {"Riolu",6,255,1,4,0,0,40,0,88,103,285,1.08,1.08,0.89,40,40},  // #447
  {"Lucario",6,16,4,4,0,1,40,0,102,116,525,1.33,1.31,1.33,70,70},  // #448
  {"Hippopotas",8,255,2,4,0,0,25,0,101,91,330,1.1,1.1,0.91,78,42},  // #449
  {"Hippowdon",8,255,4,4,0,9,25,0,119,98,525,1.32,1.32,1.07,118,72},  // #450
  {"Skorupi",7,11,2,4,0,0,24,0,88,105,330,0.97,0.97,0.86,90,55},  // #451
  {"Drapion",7,15,4,4,0,9,24,0,102,118,500,1.2,1.2,1.03,110,75},  // #452
  {"Croagunk",7,6,1,4,0,0,24,0,92,99,300,1.04,1.04,1.04,40,40},  // #453
  {"Toxicroak",7,6,3,4,0,9,24,0,107,114,490,1.28,1.28,1.17,65,65},  // #454
  {"Carnivine",4,255,3,4,0,0,14,0,103,97,454,1.25,1.25,1.2,72,72},  // #455
  {"Finneon",2,255,2,4,0,0,10,0,92,106,330,0.97,0.97,0.97,56,61},  // #456
  {"Lumineon",2,255,3,4,0,0,10,0,101,116,460,1.08,1.08,1.08,76,86},  // #457
  {"Mantyke",2,9,2,4,0,0,10,0,90,99,345,1.03,0.81,1.03,50,120},  // #458
  {"Snover",4,5,2,4,0,0,14,0,97,95,334,1.04,1.04,1.04,50,60},  // #459
  {"Abomasnow",4,5,3,4,0,10,14,0,110,103,494,1.21,1.21,1.21,75,85},  // #460
  {"Weavile",15,5,4,4,0,0,50,0,102,130,510,1.36,1.36,0.95,65,85},  // #461
  {"Magnezone",3,16,4,4,0,6,18,81,102,103,535,1.42,1.08,1.42,115,90},  // #462
  {"Lickilicky",0,255,4,4,0,1,0,0,120,99,515,1.17,1.17,1.14,95,95},  // #463
  {"Rhyperior",8,12,4,4,0,11,25,0,122,95,535,1.47,1.47,1,130,55},  // #464
  {"Tangrowth",4,255,4,4,0,0,14,0,115,99,535,1.31,1.25,1.31,125,50},  // #465
  {"Electivire",3,255,4,4,0,6,18,239,104,118,540,1.38,1.38,1.22,67,85},  // #466
  {"Magmortar",1,255,4,4,0,0,6,0,104,113,540,1.39,1.22,1.39,67,95},  // #467
  {"Togekiss",17,9,4,4,0,0,46,0,108,112,545,1.36,0.97,1.36,95,115},  // #468
  {"Yanmega",11,9,4,4,0,0,33,0,109,118,515,1.34,1.12,1.34,86,56},  // #469
  {"Leafeon",4,255,4,4,0,10,14,0,99,118,525,1.31,1.31,1.03,130,65},  // #470
  {"Glaceon",5,255,4,4,0,0,38,0,99,105,525,1.42,1.03,1.42,110,95},  // #471
  {"Gliscor",8,9,4,4,0,9,25,0,104,118,510,1.22,1.22,0.95,125,75},  // #472
  {"Mamoswine",5,8,4,4,0,8,38,0,120,112,530,1.42,1.42,1.08,80,60},  // #473
  {"Porygon-Z",0,255,4,4,0,0,0,0,108,116,535,1.44,1.14,1.44,70,75},  // #474
  {"Gallade",10,6,4,4,0,8,21,0,101,112,518,1.39,1.39,1.06,65,115},  // #475
  {"Probopass",12,16,4,4,0,5,36,0,97,95,525,1.11,1,1.11,145,150},  // #476
  {"Dusknoir",13,255,4,4,0,0,43,0,90,97,525,1.25,1.25,1.06,135,135},  // #477
  {"Froslass",5,13,3,4,0,2,38,0,102,124,480,1.14,1.14,1.14,70,70},  // #478
  {"Rotom",3,13,3,4,0,0,18,0,92,116,440,1.22,0.97,1.22,77,77},  // #479
  {"Uxie",10,255,5,4,1,8,21,0,104,118,580,1.11,1.11,1.11,130,130},  // #480
  {"Mesprit",10,255,5,4,1,0,21,0,106,112,580,1.28,1.28,1.28,105,105},  // #481
  {"Azelf",10,255,5,4,1,2,21,0,104,126,580,1.39,1.39,1.39,70,70},  // #482
  {"Dialga",16,14,5,4,1,0,48,0,115,116,680,1.52,1.36,1.52,120,100},  // #483
  {"Palkia",2,14,5,4,1,8,10,0,110,120,680,1.52,1.36,1.52,100,120},  // #484
  {"Heatran",1,16,5,4,1,0,6,0,111,110,600,1.42,1.2,1.42,106,106},  // #485
  {"Regigigas",0,255,5,4,1,11,0,0,120,120,670,1.58,1.58,1.14,110,110},  // #486
  {"Giratina",13,14,5,4,1,0,43,0,138,116,680,1.25,1.25,1.25,120,120},  // #487
  {"Cresselia",10,255,5,4,1,0,21,0,124,114,580,1.11,1.08,1.11,110,120},  // #488
  {"Phione",2,255,5,4,1,0,10,0,106,112,480,1.14,1.14,1.14,80,80},  // #489
  {"Manaphy",2,255,5,4,1,10,10,0,115,120,600,1.25,1.25,1.25,100,100},  // #490
  {"Darkrai",15,255,5,4,1,1,50,0,102,130,600,1.44,1.2,1.44,90,90},  // #491
  {"Shaymin",4,255,5,4,1,0,14,0,115,120,600,1.25,1.25,1.25,100,100},  // #492
  {"Arceus",0,255,5,4,1,11,0,0,124,128,720,1.36,1.36,1.36,120,120},  // #493
  {"Victini",10,1,5,5,1,0,21,0,115,120,600,1.25,1.25,1.25,100,100},  // #494
  {"Snivy",4,255,1,5,0,10,15,0,90,104,308,0.95,0.95,0.95,55,55},  // #495
  {"Servine",4,255,3,5,0,0,14,0,97,113,413,1.03,1.03,1.03,75,75},  // #496
  {"Serperior",4,255,4,5,0,10,14,0,104,125,528,1.11,1.11,1.11,95,95},  // #497
  {"Tepig",1,255,1,5,0,0,6,0,99,97,308,1.05,1.05,0.95,45,45},  // #498
  {"Pignite",1,6,3,5,0,11,6,0,110,101,418,1.21,1.21,1.08,55,55},  // #499
  {"Emboar",1,6,4,5,0,9,6,0,120,105,528,1.38,1.38,1.25,65,65},  // #500
  {"Oshawott",2,255,1,5,0,0,10,0,95,97,308,1.05,1,1.05,45,45},  // #501
  {"Dewott",2,255,3,5,0,2,10,0,104,103,413,1.16,1.11,1.16,60,60},  // #502
  {"Samurott",2,255,4,5,0,0,10,0,113,107,528,1.29,1.25,1.29,85,70},  // #503
  {"Patrat",0,255,1,5,0,11,0,0,90,96,255,1,1,0.89,39,39},  // #504
  {"Watchog",0,255,3,5,0,0,0,0,97,110,420,1.17,1.17,1.03,69,69},  // #505
  {"Lillipup",0,255,1,5,0,1,0,0,90,101,275,1.03,1.03,0.84,45,45},  // #506
  {"Herdier",0,255,2,5,0,0,0,0,99,103,370,1.14,1.14,0.89,65,65},  // #507
  {"Stoutland",0,255,4,5,0,0,0,0,108,112,500,1.31,1.31,0.95,90,90},  // #508
  {"Purrloin",15,255,1,5,0,0,50,0,88,106,281,0.97,0.97,0.97,37,37},  // #509
  {"Liepard",15,255,3,5,0,0,50,0,99,123,446,1.18,1.18,1.18,50,50},  // #510
  {"Pansage",4,255,1,5,0,0,14,0,92,105,316,0.99,0.99,0.99,48,48},  // #511
  {"Simisage",4,255,4,5,0,0,14,0,104,120,498,1.24,1.24,1.24,63,63},  // #512
  {"Pansear",1,255,1,5,0,9,6,0,92,105,316,0.99,0.99,0.99,48,48},  // #513
  {"Panpour",2,255,1,5,0,0,10,0,92,105,316,0.99,0.99,0.99,48,48},  // #515
  {"Munna",10,255,1,5,0,0,21,0,104,88,292,1.07,0.84,1.07,45,55},  // #517
  {"Musharna",10,255,3,5,0,3,21,0,122,90,487,1.29,1,1.29,85,95},  // #518
  {"Pidove",0,9,1,5,0,11,0,0,92,96,264,1,1,0.9,50,30},  // #519
  {"Unfezant",0,9,3,5,0,0,0,0,106,117,488,1.33,1.33,1.06,80,55},  // #521
  {"Roggenrola",12,255,1,5,0,1,36,0,95,84,280,1.11,1.11,0.84,85,25},  // #524
  {"Boldore",12,255,2,5,0,0,36,0,102,86,390,1.28,1.28,0.97,105,40},  // #525
  {"Gigalith",12,255,4,5,0,0,36,0,108,88,515,1.44,1.44,1.03,130,80},  // #526
  {"Woobat",10,9,2,5,0,8,21,0,99,108,323,1,0.95,1,43,43},  // #527
  {"Swoobat",10,9,3,5,0,8,21,0,100,126,425,1.12,1.01,1.12,55,55},  // #528
  {"Drilbur",8,255,2,5,0,0,25,0,97,107,328,1.17,1.17,0.86,40,45},  // #529
  {"Excadrill",8,16,4,5,0,9,25,0,120,115,508,1.44,1.44,0.97,60,65},  // #530
  {"Audino",0,255,3,5,0,4,0,0,116,99,445,1.03,1.03,1.03,86,86},  // #531
  {"Timburr",6,255,1,5,0,0,40,0,104,93,305,1.14,1.14,0.84,55,35},  // #532
  {"Gurdurr",6,255,2,5,0,11,40,0,108,95,405,1.28,1.28,0.92,85,50},  // #533
  {"Conkeldurr",6,255,4,5,0,11,40,0,117,97,505,1.47,1.47,1,95,65},  // #534
  {"Tympole",2,255,1,5,0,10,10,0,92,105,294,0.97,0.97,0.97,40,40},  // #535
  {"Palpitoad",2,8,2,5,0,0,10,0,104,107,384,1.06,1.06,1.06,55,55},  // #536
  {"Seismitoad",2,8,4,5,0,9,10,0,117,109,509,1.22,1.22,1.17,75,75},  // #537
  {"Sawk",6,255,3,5,0,0,40,0,104,114,465,1.39,1.39,0.86,75,75},  // #539
  {"Sewaddle",11,4,1,5,0,6,33,0,90,96,310,0.99,0.99,0.92,70,60},  // #540
  {"Swadloon",11,4,2,5,0,0,33,0,95,96,380,1.05,1.05,0.97,90,80},  // #541
  {"Leavanny",11,4,4,5,0,10,33,0,104,117,500,1.27,1.27,1.08,80,80},  // #542
  {"Venipede",11,7,1,5,0,0,33,0,84,102,260,0.95,0.95,0.86,59,39},  // #543
  {"Whirlipede",11,7,2,5,0,0,33,0,88,98,360,1,1,0.92,99,79},  // #544
  {"Scolipede",11,7,3,5,0,9,33,0,97,125,485,1.25,1.25,1,89,69},  // #545
  {"Cottonee",4,17,1,5,0,10,14,0,88,106,280,0.9,0.85,0.9,60,50},  // #546
  {"Whimsicott",4,17,3,5,0,0,14,0,97,127,480,1.12,1.07,1.12,85,75},  // #547
  {"Petilil",4,255,1,5,0,0,14,0,90,91,280,1.08,0.89,1.08,50,50},  // #548
  {"Lilligant",4,255,3,5,0,10,14,0,102,116,480,1.31,1.03,1.31,75,75},  // #549
  {"Basculin",2,255,3,5,0,10,10,0,102,119,460,1.21,1.21,1.14,65,55},  // #550
  {"Sandile",8,15,1,5,0,11,25,0,92,105,292,1.1,1.1,0.89,35,35},  // #551
  {"Krokorok",8,15,2,5,0,0,25,0,97,109,351,1.15,1.15,0.95,45,45},  // #552
  {"Krookodile",8,15,4,5,0,6,25,551,113,117,519,1.34,1.34,1.06,80,70},  // #553
  {"Darumaka",1,255,1,5,0,0,6,0,102,99,315,1.2,1.2,0.78,45,45},  // #554
  {"Darmanitan",1,255,3,5,0,9,6,0,117,118,480,1.47,1.47,0.86,55,55},  // #555
  {"Maractus",4,255,3,5,0,10,14,0,104,103,461,1.28,1.17,1.28,67,67},  // #556
  {"Dwebble",11,12,2,5,0,10,33,0,92,101,325,1.06,1.06,0.89,85,35},  // #557
  {"Scraggy",15,6,2,5,0,0,50,0,92,98,348,1.11,1.11,0.89,70,70},  // #559
  {"Scrafty",15,6,3,5,0,0,50,0,99,102,488,1.2,1.2,0.95,115,115},  // #560
  {"Sigilyph",10,9,3,5,0,2,21,0,102,119,490,1.27,1.02,1.27,80,80},  // #561
  {"Yamask",13,255,1,5,0,2,43,0,87,91,303,1,0.86,1,85,65},  // #562
  {"Cofagrigus",13,255,3,5,0,2,43,0,96,91,483,1.22,0.97,1.22,145,105},  // #563
  {"Archen",12,9,2,5,0,1,36,0,95,107,401,1.32,1.32,1.11,45,45},  // #566
  {"Archeops",12,9,4,5,0,1,36,0,104,124,567,1.47,1.47,1.32,65,65},  // #567
  {"Trubbish",7,255,2,5,0,0,24,0,92,105,329,0.97,0.97,0.92,62,62},  // #568
  {"Garbodor",7,255,3,5,0,0,24,0,106,110,474,1.22,1.22,1.03,82,82},  // #569
  {"Zorua",15,255,2,5,0,1,50,0,88,105,330,1.14,1.06,1.14,40,40},  // #570
  {"Zoroark",15,255,4,5,0,1,50,0,97,122,510,1.36,1.28,1.36,60,60},  // #571
  {"Minccino",0,255,1,5,0,0,0,0,95,110,300,0.97,0.97,0.92,40,40},  // #572
  {"Cinccino",0,255,3,5,0,1,0,0,104,126,470,1.22,1.22,1.06,60,60},  // #573
  {"Gothita",10,255,1,5,0,2,21,0,90,97,290,1,0.86,1,50,65},  // #574
  {"Gothorita",10,255,2,5,0,0,21,0,97,101,390,1.11,0.95,1.11,70,85},  // #575
  {"Gothitelle",10,255,3,5,0,2,21,0,102,105,490,1.22,1,1.22,95,110},  // #576
  {"Solosis",10,255,1,5,0,0,21,0,90,86,290,1.28,0.86,1.28,40,50},  // #577
  {"Duosion",10,255,2,5,0,0,21,0,99,91,370,1.39,0.92,1.39,50,60},  // #578
  {"Reuniclus",10,255,3,5,0,3,21,0,120,91,490,1.39,1.06,1.39,75,85},  // #579
  {"Ducklett",2,9,1,5,0,0,10,0,98,101,305,0.94,0.94,0.94,50,50},  // #580
  {"Swanna",2,9,3,5,0,0,10,0,104,119,473,1.18,1.18,1.18,63,63},  // #581
  {"Vanillite",5,255,1,5,0,8,38,0,86,96,305,1.06,0.97,1.06,50,60},  // #582
  {"Vanillish",5,255,2,5,0,0,38,0,93,103,395,1.14,1.06,1.14,65,75},  // #583
  {"Vanilluxe",5,255,4,5,0,0,38,0,102,111,535,1.31,1.22,1.31,85,95},  // #584
  {"Deerling",0,4,2,5,0,0,0,0,97,110,335,1.03,1.03,0.92,50,50},  // #585
  {"Sawsbuck",0,4,3,5,0,11,0,0,106,118,475,1.25,1.25,1.03,70,70},  // #586
  {"Emolga",3,9,3,5,0,2,18,0,95,121,428,1.11,1.11,1.11,60,60},  // #587
  {"Karrablast",11,255,1,5,0,10,33,0,92,103,315,1.11,1.11,0.92,45,45},  // #588
  {"Escavalier",11,16,4,5,0,0,33,0,102,86,495,1.44,1.44,1.03,105,105},  // #589
  {"Foongus",4,7,1,5,0,0,14,0,101,84,294,1,1,1,45,55},  // #590
  {"Alomomola",2,255,3,5,0,4,10,0,144,105,470,1.11,1.11,0.92,80,45},  // #594
  {"Joltik",11,3,1,5,0,10,33,0,92,105,319,1.01,0.96,1.01,50,50},  // #595
  {"Galvantula",11,3,3,5,0,8,33,0,102,123,472,1.23,1.12,1.23,60,60},  // #596
  {"Ferroseed",4,16,1,5,0,0,14,0,90,82,305,0.97,0.97,0.83,91,86},  // #597
  {"Ferrothorn",4,16,3,5,0,0,14,0,103,86,489,1.22,1.22,1,131,116},  // #598
  {"Klink",16,255,1,5,0,1,48,0,88,91,300,1,1,0.95,70,60},  // #599
  {"Klang",16,255,3,5,0,0,48,0,97,99,440,1.14,1.14,1.08,95,85},  // #600
  {"Klinklang",16,255,4,5,0,1,48,0,97,116,520,1.25,1.25,1.08,115,85},  // #601
  {"Tynamo",3,255,1,5,0,0,18,0,86,103,275,1,1,0.95,40,40},  // #602
  {"Eelektrik",3,255,2,5,0,0,18,0,99,95,405,1.17,1.17,1.11,70,70},  // #603
  {"Eelektross",3,255,4,5,0,2,18,0,108,99,515,1.33,1.33,1.28,80,80},  // #604
  {"Elgyem",10,255,2,5,0,2,21,0,95,91,335,1.17,1,1.17,55,55},  // #605
  {"Beheeyem",10,255,3,5,0,8,21,0,104,95,485,1.39,1.11,1.39,75,95},  // #606
  {"Litwick",13,1,1,5,0,9,43,0,92,86,275,1.06,0.86,1.06,55,55},  // #607
  {"Lampent",13,1,2,5,0,0,43,0,97,101,370,1.22,0.92,1.22,60,60},  // #608
  {"Chandelure",13,1,4,5,0,0,43,0,97,112,520,1.5,1,1.5,90,90},  // #609
  {"Axew",14,255,2,5,0,0,44,0,91,102,320,1.18,1.18,0.86,60,40},  // #610
  {"Fraxure",14,255,3,5,0,0,44,0,100,106,410,1.34,1.34,0.92,70,50},  // #611
  {"Haxorus",14,255,4,5,0,1,44,0,104,119,540,1.51,1.51,1.03,90,70},  // #612
  {"Cubchoo",5,255,1,5,0,0,38,0,95,95,305,1.08,1.08,1.03,40,40},  // #613
  {"Beartic",5,255,4,5,0,0,38,0,113,99,505,1.42,1.42,1.08,80,80},  // #614
  {"Cryogonal",5,255,4,5,0,0,38,0,106,122,515,1.22,0.97,1.22,50,135},  // #615
  {"Accelgor",11,255,4,5,0,0,33,0,106,139,495,1.25,1.08,1.25,40,60},  // #617
  {"Mienfoo",6,255,2,5,0,0,40,0,90,105,350,1.17,1.17,1,50,50},  // #619
  {"Mienshao",6,255,4,5,0,0,40,0,99,122,510,1.39,1.39,1.22,60,60},  // #620
  {"Druddigon",14,255,3,5,0,0,44,0,105,98,485,1.36,1.36,1.03,90,90},  // #621
  {"Golett",8,13,1,5,0,9,25,0,97,93,303,1.11,1.11,0.89,50,50},  // #622
  {"Golurk",8,13,3,5,0,0,25,0,110,101,483,1.38,1.38,1,80,80},  // #623
  {"Pawniard",15,16,2,5,0,0,50,0,90,103,340,1.17,1.17,0.92,70,40},  // #624
  {"Bisharp",15,16,3,5,0,0,50,0,99,107,490,1.39,1.39,1.03,100,70},  // #625
  {"Rufflet",0,9,2,5,0,1,0,0,102,103,350,1.16,1.16,0.9,50,50},  // #627
  {"Braviary",0,9,4,5,0,0,0,0,115,112,510,1.38,1.38,1.01,75,75},  // #628
  {"Vullaby",15,9,2,5,0,0,50,0,102,103,370,1,1,0.95,75,65},  // #629
  {"Mandibuzz",15,9,4,5,0,0,50,0,120,112,510,1.06,1.06,1,105,95},  // #630
  {"Heatmor",1,255,3,5,0,0,6,0,108,105,484,1.28,1.23,1.28,66,66},  // #631
  {"Durant",11,16,3,5,0,0,33,0,96,124,484,1.3,1.3,0.96,112,48},  // #632
  {"Deino",15,14,1,5,0,0,50,0,93,94,300,1.06,1.06,0.95,50,50},  // #633
  {"Zweilous",15,14,3,5,0,0,50,0,102,102,420,1.17,1.17,1.06,70,70},  // #634
  {"Hydreigon",15,14,4,5,0,8,50,0,111,119,600,1.39,1.28,1.39,90,90},  // #635
  {"Larvesta",11,1,2,5,0,6,33,0,95,103,360,1.17,1.17,0.97,55,55},  // #636
  {"Volcarona",11,1,4,5,0,6,33,636,108,120,550,1.44,1.03,1.44,65,105},  // #637
  {"Cobalion",16,6,5,5,1,1,48,0,111,123,580,1.2,1.2,1.2,129,72},  // #638
  {"Terrakion",12,6,5,5,1,1,36,0,111,123,580,1.41,1.41,1.1,90,90},  // #639
  {"Virizion",4,6,5,5,1,10,14,0,111,123,580,1.2,1.2,1.2,72,129},  // #640
  {"Tornadus",9,255,5,5,1,0,26,0,106,125,580,1.39,1.33,1.39,70,80},  // #641
  {"Thundurus",3,9,5,5,1,2,18,0,106,125,580,1.39,1.33,1.39,70,80},  // #642
  {"Reshiram",14,1,5,5,1,0,44,0,115,116,680,1.52,1.36,1.52,100,120},  // #643
  {"Zekrom",14,3,5,5,1,0,44,0,115,116,680,1.52,1.52,1.36,120,100},  // #644
  {"Landorus",8,9,5,5,1,9,25,0,110,120,600,1.39,1.39,1.33,90,80},  // #645
  {"Kyurem",14,5,5,5,1,0,44,0,126,118,660,1.42,1.42,1.42,90,90},  // #646
  {"Keldeo",2,6,5,5,1,0,10,0,111,123,580,1.41,1.1,1.41,90,90},  // #647
  {"Meloetta",0,10,5,5,1,11,0,0,115,116,600,1.4,1.12,1.4,77,128},  // #648
  {"Genesect",11,16,5,5,1,6,33,0,102,120,600,1.36,1.36,1.36,95,95},  // #649
  {"Chespin",4,255,1,6,0,10,14,0,95,94,313,1.04,1.04,0.96,65,45},  // #650
  {"Quilladin",4,255,2,6,0,10,14,0,97,102,405,1.13,1.13,1.01,95,58},  // #651
  {"Chesnaught",4,6,4,6,0,1,14,0,110,105,530,1.29,1.29,1.11,122,75},  // #652
  {"Fennekin",1,255,1,6,0,0,6,0,88,103,307,1.04,0.95,1.04,40,60},  // #653
  {"Braixen",1,255,2,6,0,0,6,0,97,109,409,1.2,1.02,1.2,58,70},  // #654
  {"Delphox",1,10,4,6,0,0,6,0,104,122,534,1.33,1.08,1.33,72,100},  // #655
  {"Froakie",2,255,1,6,0,0,10,0,88,108,314,1.04,1.01,1.04,40,44},  // #656
  {"Frogadier",2,255,2,6,0,0,10,0,94,119,405,1.16,1.05,1.16,52,56},  // #657
  {"Greninja",2,15,4,6,0,1,10,0,102,129,530,1.27,1.22,1.27,67,71},  // #658
  {"Bunnelby",0,255,1,6,0,0,0,0,87,102,237,0.9,0.9,0.88,38,36},  // #659
  {"Diggersby",0,8,3,6,0,0,0,0,108,111,423,1.01,1.01,0.97,77,77},  // #660
  {"Fletchling",0,9,1,6,0,0,0,0,90,104,278,0.97,0.97,0.92,43,38},  // #661
  {"Fletchinder",1,9,2,6,0,9,6,0,98,113,382,1.1,1.1,1.01,55,52},  // #662
  {"Talonflame",1,9,4,6,0,0,6,0,105,131,499,1.15,1.15,1.11,71,69},  // #663
  {"Scatterbug",11,255,1,6,0,6,33,0,87,93,200,0.89,0.89,0.85,40,25},  // #664
  {"Spewpa",11,255,1,6,0,0,33,0,90,90,213,0.85,0.82,0.85,60,30},  // #665
  {"Vivillon",11,9,3,6,0,6,33,0,106,115,411,1.2,0.99,1.2,50,50},  // #666
  {"Litleo",1,0,2,6,0,9,6,0,98,108,369,1.1,0.97,1.1,58,54},  // #667
  {"Flabébé",17,255,1,6,0,2,46,0,90,96,303,1.04,0.91,1.04,39,79},  // #669
  {"Floette",17,255,2,6,0,0,46,0,94,100,371,1.11,0.95,1.11,47,98},  // #670
  {"Florges",17,255,4,6,0,0,46,0,105,110,552,1.32,1.06,1.32,68,154},  // #671
  {"Skiddo",4,255,2,6,0,0,14,0,100,100,350,1.06,1.06,1.04,48,57},  // #672
  {"Gogoat",4,255,4,6,0,0,14,0,125,107,531,1.25,1.25,1.23,62,81},  // #673
  {"Pancham",6,255,2,6,0,0,40,0,100,96,348,1.15,1.15,0.95,62,48},  // #674
  {"Pangoro",6,15,4,6,0,1,40,0,113,102,495,1.38,1.38,1.08,78,71},  // #675
  {"Furfrou",0,255,3,6,0,0,0,0,104,121,472,1.14,1.14,1.06,60,90},  // #676
  {"Espurr",10,255,2,6,0,0,21,0,98,107,355,1.05,0.96,1.05,54,60},  // #677
  {"Meowstic",10,255,3,6,0,0,21,0,103,122,466,1.16,0.96,1.16,76,81},  // #678
  {"Honedge",16,13,2,6,0,2,48,0,90,90,325,1.14,1.14,0.89,100,37},  // #679
  {"Doublade",16,13,3,6,0,2,48,0,97,93,448,1.31,1.31,0.95,150,49},  // #680
  {"Aegislash",16,13,4,6,0,0,48,0,97,103,500,0.97,0.97,0.97,140,140},  // #681
  {"Spritzee",17,255,2,6,0,10,46,0,105,88,341,1.05,0.99,1.05,60,65},  // #682
  {"Swirlix",17,255,2,6,0,0,46,0,98,99,341,1.02,0.96,1.02,66,57},  // #684
  {"Slurpuff",17,255,3,6,0,2,46,0,107,108,480,1.17,1.14,1.17,86,75},  // #685
  {"Inkay",15,10,1,6,0,0,50,0,94,97,288,1,1,0.9,53,46},  // #686
  {"Malamar",15,10,3,6,0,8,50,0,109,109,482,1.21,1.21,1.07,88,75},  // #687
  {"Binacle",12,2,1,6,0,0,36,0,89,99,306,0.99,0.99,0.91,67,56},  // #688
  {"Barbaracle",12,2,4,6,0,10,36,0,102,107,500,1.28,1.28,1,115,86},  // #689
  {"Skrelp",7,2,2,6,0,0,24,0,92,91,320,1.03,1.03,1.03,60,60},  // #690
  {"Dragalge",7,14,3,6,0,0,24,0,99,96,494,1.23,1.11,1.23,90,123},  // #691
  {"Clauncher",2,255,2,6,0,10,10,0,92,96,330,1.02,0.99,1.02,62,63},  // #692
  {"Clawitzer",2,255,4,6,0,2,10,0,102,103,500,1.36,1.1,1.36,88,89},  // #693
  {"Helioptile",3,0,1,6,0,11,18,0,90,107,289,1.04,0.91,1.04,33,43},  // #694
  {"Heliolisk",3,0,3,6,0,8,18,0,98,124,481,1.3,1,1.3,52,94},  // #695
  {"Tyrunt",12,14,2,6,0,0,36,0,96,98,362,1.19,1.19,0.95,77,45},  // #696
  {"Tyrantrum",12,14,4,6,0,8,36,0,107,108,521,1.37,1.37,1.08,119,59},  // #697
  {"Amaura",12,5,2,6,0,11,36,0,105,97,362,1.07,1.02,1.07,50,63},  // #698
  {"Aurorus",12,5,4,6,0,1,36,0,125,102,521,1.24,1.12,1.24,72,92},  // #699
  {"Sylveon",17,255,4,6,0,4,46,0,113,103,525,1.31,1.06,1.31,65,130},  // #700
  {"Hawlucha",6,9,4,6,0,1,40,0,105,128,500,1.21,1.21,1.11,75,63},  // #701
  {"Dedenne",3,17,3,6,0,10,18,0,100,120,431,1.15,1.02,1.15,57,67},  // #702
  {"Carbink",12,17,4,6,0,5,36,0,92,99,500,0.97,0.97,0.97,150,150},  // #703
  {"Goomy",14,255,1,6,0,1,44,0,90,95,300,1,0.97,1,35,75},  // #704
  {"Sliggoo",14,255,3,6,0,0,44,0,101,103,452,1.16,1.11,1.16,53,113},  // #705
  {"Goodra",14,255,4,6,0,1,44,0,110,112,600,1.31,1.25,1.31,70,150},  // #706
  {"Klefki",16,17,3,6,0,2,48,0,96,110,470,1.14,1.14,1.14,91,87},  // #707
  {"Phantump",13,4,1,6,0,2,43,0,89,94,309,1.08,1.08,0.97,48,60},  // #708
  {"Trevenant",13,4,3,6,0,10,43,0,108,102,474,1.31,1.31,1.06,76,82},  // #709
  {"Pumpkaboo",13,4,2,6,0,10,43,0,92,99,335,1.06,1.06,0.94,70,55},  // #710
  {"Gourgeist",13,4,3,6,0,2,43,0,99,113,494,1.2,1.2,1.02,122,75},  // #711
  {"Bergmite",5,255,1,6,0,0,38,0,95,90,304,1.08,1.08,0.88,85,35},  // #712
  {"Avalugg",5,255,4,6,0,2,38,0,113,90,514,1.34,1.34,0.94,184,46},  // #713
  {"Noibat",9,14,1,6,0,0,26,0,88,101,245,0.95,0.86,0.95,35,40},  // #714
  {"Noivern",9,14,4,6,0,8,26,0,108,130,535,1.23,1.08,1.23,80,80},  // #715
  {"Xerneas",17,255,5,6,1,2,46,0,127,120,680,1.42,1.42,1.42,95,98},  // #716
  {"Yveltal",15,9,5,6,1,0,50,0,127,120,680,1.42,1.42,1.42,95,98},  // #717
  {"Zygarde",14,8,5,6,1,1,44,0,119,118,600,1.25,1.25,1.15,121,95},  // #718
  {"Diancie",12,17,5,6,1,0,36,0,92,99,600,1.25,1.25,1.25,150,150},  // #719
  {"Hoopa",10,13,5,6,1,0,21,0,106,107,600,1.52,1.31,1.52,60,130},  // #720
  {"Volcanion",1,2,5,6,1,10,6,0,106,107,600,1.42,1.31,1.42,120,90},  // #721
  {"Rowlet",4,9,2,7,0,0,15,0,101,96,320,1,1,0.97,55,50},  // #722
  {"Dartrix",4,9,3,7,0,0,14,0,105,100,420,1.11,1.11,1.08,75,70},  // #723
  {"Decidueye",4,13,4,7,0,2,14,0,105,107,530,1.29,1.29,1.25,75,100},  // #724
  {"Litten",1,255,2,7,0,0,6,0,90,107,320,1.06,1.06,1.03,40,40},  // #725
  {"Torracat",1,255,3,7,0,9,6,0,99,116,420,1.17,1.17,1.14,50,50},  // #726
  {"Incineroar",1,15,4,7,0,0,6,0,113,103,530,1.33,1.33,1.14,90,90},  // #727
  {"Popplio",2,255,2,7,0,0,11,0,92,95,320,1.06,1,1.06,54,56},  // #728
  {"Brionne",2,255,3,7,0,0,10,0,97,99,420,1.2,1.08,1.2,69,81},  // #729
  {"Primarina",2,17,4,7,0,0,10,0,106,103,530,1.39,1.11,1.39,74,116},  // #730
  {"Pikipek",0,9,1,7,0,0,0,0,86,105,265,1.11,1.11,0.86,30,30},  // #731
  {"Yungoos",0,255,1,7,0,0,0,0,92,97,253,1.08,1.08,0.86,30,30},  // #734
  {"Grubbin",11,255,1,7,0,0,33,0,91,97,300,1.04,1.04,1,45,45},  // #736
  {"Charjabug",11,3,2,7,0,10,33,0,96,93,400,1.15,1.15,1,95,75},  // #737
  {"Vikavolt",11,3,4,7,0,10,33,0,105,96,500,1.5,1.08,1.5,90,75},  // #738
  {"Crabrawler",6,255,2,7,0,1,40,0,91,104,338,1.15,1.15,0.93,57,47},  // #739
  {"Crabominable",6,5,3,7,0,3,40,0,114,96,478,1.43,1.43,1.04,77,67},  // #740
  {"Oricorio",1,9,3,7,0,0,6,0,104,117,476,1.24,1.08,1.24,70,70},  // #741
  {"Cutiefly",11,17,1,7,0,2,33,0,88,113,304,1,0.95,1,40,40},  // #742
  {"Ribombee",11,17,3,7,0,2,33,0,97,130,464,1.22,1,1.22,60,70},  // #743
  {"Rockruff",12,255,1,7,0,11,36,0,90,103,280,1.06,1.06,0.86,40,40},  // #744
  {"Lycanroc",12,255,3,7,0,0,36,0,104,125,487,1.33,1.33,1,65,65},  // #745
  {"Wishiwashi",2,255,1,7,0,10,10,0,90,95,175,0.84,0.81,0.84,20,25},  // #746
  {"Mareanie",7,2,1,7,0,0,24,0,92,97,305,0.99,0.99,0.94,62,52},  // #747
  {"Toxapex",7,2,4,7,0,0,24,0,92,93,495,1.05,1.05,0.99,152,142},  // #748
  {"Mudbray",8,255,2,7,0,0,25,0,102,97,385,1.25,1.25,0.95,70,55},  // #749
  {"Mudsdale",8,255,4,7,0,1,25,0,115,93,500,1.39,1.39,1,100,85},  // #750
  {"Dewpider",2,11,1,7,0,6,10,0,87,89,269,0.92,0.92,0.92,52,72},  // #751
  {"Araquanid",2,11,3,7,0,0,10,0,101,96,454,1.08,1.08,0.97,92,132},  // #752
  {"Fomantis",4,255,1,7,0,0,14,0,88,93,250,1,1,0.97,35,35},  // #753
  {"Lurantis",4,255,3,7,0,0,14,0,102,97,480,1.28,1.28,1.14,90,90},  // #754
  {"Morelull",4,17,1,7,0,0,14,0,88,84,285,1.06,0.89,1.06,55,75},  // #755
  {"Salandit",7,1,2,7,0,9,24,0,92,110,320,1.09,0.94,1.09,40,40},  // #757
  {"Salazzle",7,1,3,7,0,9,24,0,101,127,480,1.31,1.05,1.31,60,60},  // #758
  {"Stufful",0,6,2,7,0,0,0,0,102,99,340,1.11,1.11,0.95,50,50},  // #759
  {"Bewear",0,6,4,7,0,11,0,0,124,103,500,1.39,1.39,1,80,60},  // #760
  {"Bounsweet",4,255,1,7,0,0,14,0,89,91,210,0.86,0.86,0.86,38,38},  // #761
  {"Steenee",4,255,1,7,0,10,14,0,93,104,290,0.92,0.92,0.92,48,48},  // #762
  {"Tsareena",4,255,4,7,0,0,14,0,102,108,510,1.36,1.36,0.97,98,98},  // #763
  {"Comfey",17,255,3,7,0,4,46,0,93,120,485,1.15,0.99,1.15,90,110},  // #764
  {"Passimian",6,255,3,7,0,1,40,0,115,112,490,1.36,1.36,0.92,90,60},  // #766
  {"Wimpod",11,2,1,7,0,6,33,0,81,112,230,0.89,0.89,0.81,40,30},  // #767
  {"Golisopod",11,2,4,7,0,2,33,0,104,95,530,1.39,1.39,1.03,140,90},  // #768
  {"Sandygast",13,8,2,7,0,0,43,0,95,84,320,1.08,1,1.08,80,45},  // #769
  {"Palossand",13,8,3,7,0,2,43,0,108,93,480,1.25,1.11,1.25,110,75},  // #770
  {"Pyukumuku",2,255,3,7,0,0,10,0,95,80,410,1.03,1.03,0.86,130,130},  // #771
  {"Código Cero",0,255,5,7,1,0,0,0,113,103,534,1.22,1.22,1.22,95,95},  // #772
  {"Silvally",0,255,5,7,1,0,0,0,113,118,570,1.22,1.22,1.22,95,95},  // #773
  {"Minior",12,9,3,7,0,1,36,0,97,103,440,1.03,1.03,1.03,100,100},  // #774
  {"Komala",0,255,3,7,0,1,0,0,99,105,480,1.33,1.33,1.11,65,95},  // #775
  {"Turtonator",1,14,3,7,0,1,6,0,97,93,485,1.2,1.13,1.2,135,85},  // #776
  {"Togedemaru",3,16,3,7,0,2,18,0,99,118,435,1.24,1.24,0.92,63,73},  // #777
  {"Mimikyu",13,17,3,7,0,2,43,0,95,118,476,1.2,1.2,0.97,80,105},  // #778
  {"Bruxish",2,10,3,7,0,10,10,0,101,117,475,1.28,1.28,1.08,70,70},  // #779
  {"Drampa",0,14,3,7,0,0,0,0,105,93,485,1.44,1.03,1.44,85,91},  // #780
  {"Dhelmise",13,4,4,7,0,0,43,0,102,95,517,1.42,1.42,1.17,100,90},  // #781
  {"Jangmo-o",14,255,1,7,0,0,44,0,90,97,300,1,1,0.95,65,45},  // #782
  {"Hakamo-o",14,6,3,7,0,0,44,0,95,105,420,1.11,1.11,1.06,90,70},  // #783
  {"Kommo-o",14,6,5,7,0,0,44,0,104,114,600,1.31,1.31,1.25,125,105},  // #784
  {"Tapu Koko",3,17,5,7,1,0,18,0,102,133,570,1.33,1.33,1.22,85,75},  // #785
  {"Tapu Lele",10,17,5,7,1,0,21,0,102,118,570,1.42,1.17,1.42,75,115},  // #786
  {"Tapu Bulu",4,17,5,7,1,0,14,0,102,110,570,1.42,1.42,1.17,115,95},  // #787
  {"Tapu Fini",2,17,5,7,1,0,10,0,102,114,570,1.22,1.11,1.22,115,130},  // #788
  {"Cosmog",10,255,5,7,1,0,21,0,89,94,200,0.86,0.86,0.86,31,31},  // #789
  {"Cosmoem",10,255,5,7,1,8,21,0,89,94,400,0.86,0.86,0.86,131,131},  // #790
  {"Solgaleo",10,16,5,7,1,0,21,0,132,119,680,1.45,1.45,1.32,107,89},  // #791
  {"Lunala",10,13,5,7,1,0,21,0,132,119,680,1.45,1.32,1.45,89,107},  // #792
  {"Nihilego",12,7,4,7,0,0,36,0,119,121,570,1.4,0.99,1.4,47,131},  // #793
  {"Buzzwole",11,6,4,7,0,0,33,0,118,111,570,1.46,1.46,0.99,139,53},  // #794
  {"Pheromosa",11,6,4,7,0,11,33,0,102,141,570,1.45,1.45,1.45,37,37},  // #795
  {"Xurkitree",3,255,4,7,0,0,18,0,107,113,570,1.65,1.19,1.65,71,71},  // #796
  {"Celesteela",16,9,4,7,0,1,48,0,114,104,570,1.29,1.26,1.29,103,101},  // #797
  {"Kartana",4,16,4,7,0,0,14,0,97,124,570,1.7,1.7,1.02,131,31},  // #798
  {"Guzzlord",15,14,4,7,0,3,50,0,170,96,570,1.26,1.26,1.23,53,53},  // #799
  {"Necrozma",10,255,5,7,1,0,21,0,114,111,600,1.4,1.29,1.4,101,89},  // #800
  {"Magearna",16,17,5,7,1,0,48,0,106,105,600,1.42,1.22,1.42,115,115},  // #801
  {"Marshadow",6,13,5,7,1,2,40,0,110,130,600,1.39,1.39,1.2,80,90},  // #802
  {"Poipole",7,255,3,7,0,0,24,0,100,109,420,1.1,1.1,1.1,67,67},  // #803
  {"Naganadel",7,14,4,7,0,0,24,0,103,129,540,1.4,1.1,1.4,73,73},  // #804
  {"Stakataka",12,16,4,7,0,0,36,0,97,83,570,1.42,1.42,0.99,211,101},  // #805
  {"Blacephalon",1,13,4,7,0,9,6,0,94,123,570,1.53,1.4,1.53,53,79},  // #806
  {"Zeraora",3,255,5,7,1,8,18,0,110,138,600,1.32,1.32,1.26,75,80},  // #807
  {"Meltan",16,255,1,7,0,0,48,0,91,92,300,1.06,1.06,1,65,35},  // #808
  {"Melmetal",16,255,2,7,0,3,48,0,131,92,600,1.49,1.49,1.14,143,65},  // #809
  {"Grookey",4,255,1,8,0,0,14,0,92,105,310,1.06,1.06,0.92,50,40},  // #810
  {"Thwackey",4,255,3,8,0,0,14,0,102,112,420,1.17,1.17,1,70,60},  // #811
  {"Rillaboom",4,255,4,8,0,0,14,0,115,114,530,1.39,1.39,1.03,90,70},  // #812
  {"Scorbunny",1,255,1,8,0,2,6,0,92,107,310,1.09,1.09,0.92,40,40},  // #813
  {"Raboot",1,255,3,8,0,0,6,0,99,117,420,1.17,1.17,1,60,60},  // #814
  {"Cinderace",1,255,4,8,0,0,6,0,106,128,530,1.34,1.34,1.06,75,75},  // #815
  {"Sobble",2,255,1,8,0,0,10,0,92,107,310,1.08,0.92,1.08,40,40},  // #816
  {"Drizzile",2,255,3,8,0,0,10,0,99,116,420,1.22,1.03,1.22,55,55},  // #817
  {"Inteleon",2,255,4,8,0,0,10,0,102,128,530,1.39,1.17,1.39,65,65},  // #818
  {"Skwovet",0,255,1,8,0,1,0,0,102,88,275,1,1,0.89,55,35},  // #819
  {"Greedent",0,255,3,8,0,11,0,0,124,86,460,1.22,1.22,1,95,75},  // #820
  {"Rookidee",9,255,1,8,0,0,26,0,87,102,245,0.96,0.96,0.88,35,35},  // #821
  {"Corvisquire",9,255,2,8,0,0,26,0,101,110,365,1.07,1.07,0.94,55,55},  // #822
  {"Corviknight",9,16,4,8,0,0,26,0,114,106,495,1.18,1.18,0.99,105,85},  // #823
  {"Blipbug",11,255,1,8,0,0,33,0,81,97,180,0.84,0.81,0.84,20,45},  // #824
  {"Dottler",11,10,2,8,0,0,33,0,92,91,335,0.97,0.89,0.97,80,90},  // #825
  {"Orbeetle",11,10,4,8,0,2,33,0,97,116,505,1.14,0.95,1.14,110,120},  // #826
  {"Nickit",15,255,1,8,0,1,50,0,88,99,245,0.96,0.85,0.96,28,52},  // #827
  {"Thievul",15,255,3,8,0,1,50,0,102,116,455,1.18,1.02,1.18,58,92},  // #828
  {"Gossifleur",4,255,1,8,0,0,14,0,88,82,250,0.92,0.92,0.92,60,60},  // #829
  {"Eldegoss",4,255,3,8,0,0,14,0,97,103,460,1.14,0.97,1.14,90,120},  // #830
  {"Wooloo",0,255,1,8,0,0,0,0,89,98,270,0.92,0.92,0.92,55,45},  // #831
  {"Dubwool",0,255,3,8,0,1,0,0,102,115,490,1.14,1.14,1.03,100,90},  // #832
  {"Chewtle",2,255,1,8,0,10,10,0,92,96,284,1.05,1.05,0.91,50,38},  // #833
  {"Drednaw",2,12,3,8,0,1,10,0,110,109,485,1.33,1.33,0.96,90,68},  // #834
  {"Yamper",3,255,1,8,0,0,18,0,97,89,270,0.95,0.95,0.92,50,50},  // #835
  {"Boltund",3,255,3,8,0,8,18,0,101,129,490,1.2,1.2,1.2,60,60},  // #836
  {"Applin",4,14,1,8,0,0,14,0,88,86,260,0.92,0.92,0.92,80,40},  // #840
  {"Flapple",4,14,3,8,0,1,14,0,102,107,485,1.31,1.31,1.22,80,60},  // #841
  {"Appletun",4,14,3,8,0,10,14,0,120,91,485,1.25,1.17,1.25,80,80},  // #842
  {"Silicobra",8,255,1,8,0,0,25,0,93,97,315,1.01,1.01,0.89,75,50},  // #843
  {"Sandaconda",8,255,4,8,0,11,25,0,102,108,510,1.29,1.29,1.06,125,70},  // #844
  {"Cramorant",9,2,3,8,0,10,26,0,102,114,475,1.17,1.17,1.17,55,95},  // #845
  {"Arrokuda",2,255,1,8,0,10,10,0,88,106,280,1.05,1.05,0.92,40,30},  // #846
  {"Barraskewda",2,255,3,8,0,2,10,0,97,135,490,1.38,1.38,1.03,60,50},  // #847
  {"Toxel",3,7,1,8,0,0,18,0,88,95,242,1,0.91,1,35,35},  // #848
  {"Toxtricity",3,7,4,8,0,2,18,0,104,110,502,1.33,1.24,1.33,70,70},  // #849
  {"Sizzlipede",1,11,1,8,0,0,6,0,92,97,305,1.06,1.06,0.97,45,50},  // #850
  {"Centiskorch",1,11,4,8,0,9,6,0,115,105,525,1.33,1.33,1.2,65,90},  // #851
  {"Clobbopus",6,255,1,8,0,1,40,0,92,91,310,1.07,1.07,0.97,60,50},  // #852
  {"Grapploct",6,255,3,8,0,1,40,0,106,96,480,1.35,1.35,1.08,90,80},  // #853
  {"Sinistea",13,255,1,8,0,0,43,0,88,99,308,1.11,0.95,1.11,45,54},  // #854
  {"Polteageist",13,255,4,8,0,0,43,0,97,107,508,1.44,1.06,1.44,65,114},  // #855
  {"Hatenna",10,255,1,8,0,0,21,0,89,94,265,1.01,0.86,1.01,45,53},  // #856
  {"Hattrem",10,255,2,8,0,8,21,0,96,99,370,1.17,0.92,1.17,65,73},  // #857
  {"Hatterene",10,17,4,8,0,4,21,0,96,90,510,1.45,1.2,1.45,95,103},  // #858
  {"Impidimp",15,17,1,8,0,2,50,0,90,99,265,1,0.95,1,30,40},  // #859
  {"Morgrem",15,17,2,8,0,0,50,0,99,107,370,1.11,1.03,1.11,45,55},  // #860
  {"Grimmsnarl",15,17,4,8,0,10,50,0,113,103,510,1.36,1.36,1.22,65,75},  // #861
  {"Obstagoon",15,0,4,8,0,0,50,0,112,118,520,1.2,1.2,1.03,101,81},  // #862
  {"Perrserker",16,255,3,8,0,0,48,0,102,99,440,1.31,1.31,0.97,100,60},  // #863
  {"Cursola",13,255,4,8,0,0,43,0,97,91,510,1.5,1.22,1.5,50,130},  // #864
  {"Runerigus",8,13,3,8,0,11,25,0,96,91,483,1.22,1.22,0.97,145,105},  // #867
  {"Milcery",17,255,1,8,0,10,46,0,90,92,270,0.97,0.92,0.97,40,61},  // #868
  {"Alcremie",17,255,4,8,0,0,46,0,99,105,495,1.31,1.03,1.31,75,121},  // #869
  {"Pincurchin",3,255,3,8,0,8,18,0,92,84,435,1.26,1.26,1.2,95,85},  // #871
  {"Snom",5,11,1,8,0,10,38,0,84,86,185,0.95,0.84,0.95,35,30},  // #872
  {"Frosmoth",5,11,3,8,0,0,38,0,102,105,475,1.39,1.06,1.39,60,90},  // #873
  {"Stonjourner",12,255,3,8,0,0,36,0,115,107,470,1.39,1.39,0.81,135,20},  // #874
  {"Eiscue",5,255,3,8,0,0,38,0,104,99,470,1.14,1.14,1.06,110,90},  // #875
  {"Indeedee",10,0,3,8,0,0,21,0,97,118,475,1.28,1.06,1.28,55,95},  // #876
  {"Morpeko",3,15,3,8,0,0,18,0,96,119,436,1.22,1.22,1.08,58,58},  // #877
  {"Dracozolt",3,14,4,8,0,0,18,0,110,110,505,1.25,1.25,1.14,90,70},  // #880
  {"Arctozolt",3,5,4,8,0,0,18,0,110,101,505,1.25,1.25,1.2,90,80},  // #881
  {"Dracovish",2,14,4,8,0,8,10,0,110,110,505,1.2,1.2,1.08,100,80},  // #882
  {"Arctovish",2,5,4,8,0,0,10,0,110,101,505,1.2,1.2,1.14,100,90},  // #883
  {"Duraludon",16,14,4,8,0,0,48,0,102,114,535,1.36,1.22,1.36,115,50},  // #884
  {"Dreepy",14,13,1,8,0,2,44,0,83,112,270,1.03,1.03,0.92,30,30},  // #885
  {"Drakloak",14,13,3,8,0,8,44,0,101,121,410,1.14,1.14,1.03,50,50},  // #886
  {"Dragapult",14,13,5,8,0,0,44,0,110,138,600,1.36,1.36,1.25,75,75},  // #887
  {"Zacian",17,255,5,8,1,2,46,0,111,136,660,1.36,1.36,1.14,115,115},  // #888
  {"Zamazenta",6,255,5,8,1,0,40,0,111,136,660,1.36,1.36,1.14,115,115},  // #889
  {"Eternatus",7,14,5,8,1,2,24,0,133,133,690,1.5,1.17,1.5,95,95},  // #890
  {"Kubfu",6,255,5,8,1,0,40,0,97,108,385,1.2,1.2,0.99,60,50},  // #891
  {"Urshifu",6,15,5,8,1,0,40,0,115,119,550,1.42,1.42,1.05,100,60},  // #892
  {"Regieleki",3,255,5,8,1,0,18,0,106,162,580,1.25,1.25,1.25,50,50},  // #894
  {"Regidrago",14,255,5,8,1,0,44,0,160,112,580,1.25,1.25,1.25,50,50},  // #895
  {"Glastrier",5,255,5,8,1,3,38,0,115,91,580,1.5,1.5,1.06,130,110},  // #896
  {"Spectrier",13,255,5,8,1,0,43,0,115,133,580,1.5,1.06,1.5,60,80},  // #897
  {"Calyrex",10,4,5,8,1,0,21,0,115,112,500,1.14,1.14,1.14,80,80},  // #898
  {"Wyrdeer",0,10,4,8,0,0,0,0,116,105,525,1.28,1.28,1.28,72,75},  // #899
  {"Kleavor",11,12,4,8,0,6,33,0,102,114,500,1.44,1.44,0.95,95,70},  // #900
  {"Ursaluna",8,0,4,8,0,1,25,0,128,99,550,1.47,1.47,0.95,105,80},  // #901
  {"Basculegion",2,13,4,8,0,0,10,0,124,111,530,1.32,1.32,1.14,65,75},  // #902
  {"Sneasler",6,7,4,8,0,0,40,0,106,128,510,1.42,1.42,0.92,60,80},  // #903
  {"Overqwil",15,7,4,8,0,0,50,0,108,114,510,1.33,1.33,1.06,95,65},  // #904
  {"Enamorus",17,9,5,8,1,10,46,0,103,123,580,1.44,1.33,1.44,70,80},  // #905
  {"Sprigatito",4,255,1,9,0,0,15,0,88,105,310,1.04,1.04,0.95,54,45},  // #906
  {"Floragato",4,255,3,9,0,0,14,0,97,113,410,1.14,1.14,1.03,63,63},  // #907
  {"Meowscarada",4,15,4,9,0,10,14,0,104,130,530,1.31,1.31,1.15,70,70},  // #908
  {"Fuecoco",1,255,1,9,0,0,6,0,100,93,310,1.05,0.95,1.05,59,40},  // #909
  {"Crocalor",1,255,3,9,0,0,6,0,106,99,411,1.2,1,1.2,78,58},  // #910
  {"Skeledirge",1,13,4,9,0,0,6,0,117,106,530,1.31,1.11,1.31,100,75},  // #911
  {"Quaxly",2,255,1,9,0,2,10,0,95,99,310,1.06,1.06,0.97,45,45},  // #912
  {"Quaxwell",2,255,3,9,0,0,10,0,102,105,410,1.17,1.17,1.06,65,60},  // #913
  {"Quaquaval",2,6,4,9,0,0,10,0,108,114,530,1.36,1.36,1.17,80,75},  // #914
  {"Lechonk",0,255,1,9,0,1,0,0,94,93,254,0.95,0.95,0.89,40,45},  // #915
  {"Oinkologne",0,255,3,9,0,1,0,0,120,105,489,1.25,1.25,1.02,75,80},  // #916
  {"Tarountula",11,255,1,9,0,6,33,0,86,86,210,0.93,0.93,0.86,45,40},  // #917
  {"Spidops",11,255,2,9,0,0,33,0,97,93,404,1.13,1.13,0.99,92,86},  // #918
  {"Nymble",11,255,1,9,0,0,33,0,85,97,210,0.95,0.95,0.82,40,25},  // #919
  {"Lokix",11,15,3,9,0,10,33,0,102,117,450,1.26,1.26,0.99,78,55},  // #920
  {"Pawmi",3,255,1,9,0,0,18,0,90,103,240,0.97,0.97,0.92,20,25},  // #921
  {"Pawmo",3,6,2,9,0,0,18,0,97,114,350,1.11,1.11,0.97,40,40},  // #922
  {"Pawmot",3,6,3,9,0,11,18,0,102,122,490,1.33,1.33,1.08,70,60},  // #923
  {"Tandemaus",0,255,1,9,0,0,0,0,92,110,305,0.97,0.97,0.92,45,45},  // #924
  {"Maushold",0,255,3,9,0,1,0,0,103,125,470,1.11,1.11,1.06,70,75},  // #925
  {"Fidough",17,255,1,9,0,0,46,0,87,105,312,1,1,0.86,70,55},  // #926
  {"Dachsbun",17,255,3,9,0,0,46,0,96,118,477,1.14,1.14,0.97,115,80},  // #927
  {"Smoliv",4,0,1,9,0,1,14,0,88,91,260,1.02,0.89,1.02,45,51},  // #928
  {"Arboliva",4,0,4,9,0,0,14,0,105,94,510,1.39,1.08,1.39,90,109},  // #930
  {"Nacli",12,255,1,9,0,1,36,0,95,88,280,1,1,0.89,75,35},  // #932
  {"Naclstack",12,255,2,9,0,0,36,0,97,93,355,1.03,1.03,0.89,100,65},  // #933
  {"Garganacl",12,255,4,9,0,3,36,0,115,93,500,1.25,1.25,0.95,130,90},  // #934
  {"Charcadet",1,255,1,9,0,2,6,0,88,93,255,0.97,0.97,0.97,40,40},  // #935
  {"Armarouge",1,10,4,9,0,8,6,0,108,110,525,1.39,1.03,1.39,100,80},  // #936
  {"Ceruledge",1,13,4,9,0,9,6,0,104,114,525,1.39,1.39,1.03,80,100},  // #937
  {"Tadbulb",3,255,1,9,0,0,18,0,97,97,272,1.02,0.87,1.02,41,35},  // #938
  {"Bellibolt",3,255,4,9,0,8,18,0,119,97,495,1.27,1.05,1.27,91,83},  // #939
  {"Wattrel",3,9,1,9,0,0,18,0,88,107,280,1,0.92,1,35,40},  // #940
  {"Kilowattrel",3,9,3,9,0,2,18,0,102,130,490,1.28,1.08,1.28,60,60},  // #941
  {"Bramblin",4,13,1,9,0,0,14,0,88,103,275,1.06,1.06,0.95,30,35},  // #946
  {"Capsakid",4,255,1,9,0,0,14,0,92,99,304,1.04,1.04,1.04,40,40},  // #951
  {"Scovillain",4,1,3,9,0,9,14,0,99,110,486,1.29,1.29,1.29,65,65},  // #952
  {"Rellor",11,255,1,9,0,10,33,0,88,91,270,0.97,0.97,0.87,60,58},  // #953
  {"Flittle",10,255,1,9,0,0,21,0,84,110,255,1,0.89,1,30,30},  // #955
  {"Tinkatink",17,16,1,9,0,2,46,0,92,102,297,0.95,0.95,0.89,45,64},  // #957
  {"Tinkatuff",17,16,2,9,0,0,46,0,99,111,380,1,1,0.95,55,82},  // #958
  {"Tinkaton",17,16,4,9,0,0,46,0,108,117,506,1.11,1.11,1.08,77,105},  // #959
  {"Wiglett",2,255,1,9,0,0,10,0,74,118,245,1,1,0.89,25,25},  // #960
  {"Wugtrio",2,255,3,9,0,0,10,0,86,128,425,1.25,1.25,0.97,50,70},  // #961
  {"Finizen",2,255,1,9,0,2,10,0,102,110,315,0.95,0.95,0.95,40,40},  // #963
  {"Palafin",2,255,3,9,0,0,10,0,115,120,457,1.08,1.08,0.99,72,62},  // #964
  {"Varoom",16,7,1,9,0,0,48,0,90,98,300,1.08,1.08,0.86,63,45},  // #965
  {"Revavroom",16,7,4,9,0,0,48,0,106,116,500,1.35,1.35,1,90,67},  // #966
  {"Cyclizar",14,0,4,9,0,0,44,0,102,129,501,1.22,1.22,1.17,65,65},  // #967
  {"Orthworm",16,255,3,9,0,1,48,0,102,105,480,1.17,1.17,1.03,145,55},  // #968
  {"Glimmet",12,7,2,9,0,2,36,0,92,103,350,1.28,0.89,1.28,42,60},  // #969
  {"Glimmora",12,7,4,9,0,1,36,0,107,114,525,1.42,1,1.42,90,81},  // #970
  {"Greavard",13,255,1,9,0,0,43,0,92,92,290,1.04,1.04,0.86,60,55},  // #971
  {"Houndstone",13,255,3,9,0,0,43,0,102,107,488,1.26,1.26,0.97,100,97},  // #972
  {"Cetoddle",5,255,2,9,0,8,38,0,119,96,334,1.07,1.07,0.86,45,40},  // #974
  {"Cetitan",5,255,4,9,0,2,38,0,146,109,521,1.32,1.32,0.95,65,55},  // #975
  {"Veluza",2,10,3,9,0,10,10,0,110,107,478,1.26,1.26,1.13,73,65},  // #976
  {"Dondozo",2,255,4,9,0,3,10,0,138,93,530,1.25,1.25,1.06,115,65},  // #977
  {"Tatsugiri",14,2,3,9,0,8,44,0,101,112,475,1.36,0.97,1.36,60,95},  // #978
  {"Annihilape",6,13,4,9,0,11,40,0,120,116,535,1.33,1.33,0.97,80,90},  // #979
  {"Clodsire",7,8,3,9,0,3,24,0,128,86,430,1.11,1.11,0.95,60,100},  // #980
  {"Farigiraf",0,10,4,9,0,0,0,0,124,103,520,1.31,1.2,1.31,70,70},  // #981
  {"Dudunsparce",0,255,4,9,0,1,0,0,126,101,520,1.25,1.25,1.17,80,75},  // #982
  {"Kingambit",15,16,4,9,0,0,50,0,115,99,550,1.44,1.44,1.03,120,85},  // #983
  {"Colmilargo",8,6,4,9,0,0,25,0,122,115,570,1.42,1.42,0.99,131,53},  // #984
  {"Colagrito",17,10,4,9,0,0,46,0,122,125,570,1.06,1.06,1.06,99,115},  // #985
  {"Melenaleteo",13,17,4,9,0,0,43,0,95,135,570,1.44,1,1.44,55,135},  // #987
  {"Reptalada",11,6,4,9,0,6,33,0,108,112,570,1.44,1.44,1.17,79,105},  // #988
  {"Pelarena",3,8,4,9,0,8,18,0,108,120,570,1.37,1.15,1.37,97,85},  // #989
  {"Ferrosaco",5,2,4,9,0,10,38,0,95,135,570,1.38,1.14,1.38,114,60},  // #991
  {"Ferropalmas",6,3,4,9,0,8,40,0,139,99,570,1.47,1.47,0.97,108,68},  // #992
  {"Ferropolilla",1,7,4,9,0,9,6,0,106,124,570,1.47,1.08,1.47,60,110},  // #994
  {"Ferropúas",12,3,4,9,0,0,36,0,115,108,570,1.44,1.44,1.08,110,84},  // #995
  {"Frigibax",14,5,2,9,0,1,44,0,99,101,320,1.11,1.11,0.89,45,45},  // #996
  {"Arctibax",14,5,3,9,0,0,44,0,110,104,423,1.22,1.22,0.95,66,65},  // #997
  {"Baxcalibur",14,5,5,9,0,0,44,0,122,115,600,1.5,1.5,1.11,92,86},  // #998
  {"Gholdengo",16,13,4,9,0,2,48,0,109,113,550,1.43,1.03,1.43,95,91},  // #1000
  {"Chi-Yu",15,1,5,9,1,1,50,0,95,120,570,1.44,1.14,1.44,80,120},  // #1004
  {"Bramaluna",14,15,5,9,0,0,44,0,117,128,590,1.46,1.46,1,71,101},  // #1005
  {"Ferropaladín",17,6,5,9,0,0,46,0,103,127,590,1.42,1.42,1.36,90,60},  // #1006
  {"Koraidon",6,14,5,9,1,8,40,0,115,135,670,1.44,1.44,1.17,115,100},  // #1007
  {"Ondulagua",2,14,5,9,0,0,10,0,115,124,590,1.39,1.16,1.39,91,83},  // #1009
  {"Ferroverdor",4,10,5,9,0,2,14,0,110,122,590,1.42,1.42,1.08,88,108},  // #1010
  {"Dipplin",4,14,3,9,0,0,14,0,106,95,485,1.22,1.14,1.22,110,80},  // #1011
  {"Poltchageist",4,13,1,9,0,10,14,0,88,99,308,1.11,0.95,1.11,45,54},  // #1012
  {"Sinistcha",4,13,4,9,0,2,14,0,102,107,508,1.37,1.03,1.37,106,80},  // #1013
  {"Munkidori",7,10,5,9,1,8,24,0,110,123,555,1.42,1.11,1.42,66,90},  // #1015
  {"Fezandipiti",7,17,5,9,1,2,24,0,110,120,555,1.2,1.2,1.08,82,125},  // #1016
  {"Ogerpon",4,255,5,9,1,0,14,0,106,124,550,1.36,1.36,1.03,84,96},  // #1017
  {"Archaludon",16,14,5,9,0,0,48,0,110,114,600,1.39,1.28,1.39,130,65},  // #1018
  {"Hydrapple",4,14,4,9,0,10,14,0,118,96,540,1.36,1.14,1.36,110,80},  // #1019
  {"Terapagos",0,255,5,9,1,1,0,0,110,103,450,1.06,1.06,1.06,85,85},  // #1024
  {"Rattata de Alola",15,0,1,7,0,0,50,0,84,108,253,1.01,1.01,0.84,35,35},  // #1026
  {"Raticate de Alola",15,0,3,7,0,0,50,0,104,110,413,1.09,1.09,0.92,70,80},  // #1027
  {"Raichu de Alola",3,10,3,7,0,0,18,0,97,124,485,1.22,1.17,1.22,50,85},  // #1028
  {"Sandshrew de Alola",5,16,1,7,0,0,38,0,92,95,300,1.11,1.11,0.76,90,35},  // #1029
  {"Sandslash de Alola",5,16,3,7,0,1,38,0,104,105,450,1.25,1.25,0.84,120,65},  // #1030
  {"Vulpix de Alola",5,255,1,7,0,8,38,0,87,105,299,0.97,0.93,0.97,40,65},  // #1031
  {"Ninetales de Alola",5,17,4,7,0,10,38,0,103,124,505,1.15,1.07,1.15,75,100},  // #1032
  {"Diglett de Alola",8,16,1,7,0,0,25,0,74,116,265,1,1,0.89,30,45},  // #1033
  {"Dugtrio de Alola",8,16,3,7,0,0,25,0,86,124,425,1.25,1.25,0.97,60,70},  // #1034
  {"Meowth de Alola",15,255,1,7,0,1,50,0,88,116,290,0.97,0.89,0.97,35,40},  // #1035
  {"Meowth de Galar",16,255,1,8,0,0,48,0,92,95,290,1.06,1.06,0.92,55,40},  // #1036
  {"Persian de Alola",15,255,3,7,0,0,50,0,99,126,440,1.11,1.03,1.11,60,65},  // #1037
  {"Growlithe de Hisui",1,12,2,8,0,0,6,0,97,101,350,1.11,1.11,1.06,45,50},  // #1038
  {"Arcanine de Hisui",1,12,4,8,0,11,6,0,113,116,555,1.33,1.33,1.22,80,80},  // #1039
  {"Geodude de Alola",12,3,1,7,0,0,36,0,88,86,300,1.14,1.14,0.86,100,30},  // #1040
  {"Graveler de Alola",12,3,2,7,0,0,36,0,95,93,390,1.22,1.22,0.95,115,45},  // #1041
  {"Golem de Alola",12,3,4,7,0,0,36,0,106,97,495,1.36,1.36,1,130,65},  // #1042
  {"Ponyta de Galar",10,255,3,8,0,0,21,0,92,116,410,1.17,1.17,1.06,55,65},  // #1043
  {"Rapidash de Galar",10,17,4,8,0,0,21,0,99,122,500,1.25,1.25,1.14,70,80},  // #1044
  {"Slowpoke de Galar",10,255,1,8,0,8,21,0,110,84,315,1.06,1.06,0.92,65,40},  // #1045
  {"Slowbro de Galar",7,10,3,8,0,3,24,0,113,91,490,1.25,1.25,1.25,95,70},  // #1046
  {"Farfetch’d de Galar",6,255,2,8,0,1,40,0,93,101,377,1.22,1.22,1.02,55,62},  // #1047
  {"Grimer de Alola",7,15,2,7,0,2,24,0,106,88,325,1.14,1.14,0.92,50,50},  // #1048
  {"Muk de Alola",7,15,4,7,0,9,24,0,117,99,500,1.28,1.28,1.06,75,100},  // #1049
  {"Voltorb de Hisui",3,4,2,8,0,10,18,0,88,120,330,1,0.86,1,50,55},  // #1050
  {"Electrode de Hisui",3,4,3,8,0,0,18,0,97,141,490,1.14,0.97,1.14,70,80},  // #1051
  {"Exeggutor de Alola",4,14,4,7,0,3,14,0,113,97,530,1.39,1.28,1.39,85,75},  // #1052
  {"Marowak de Alola",1,13,3,7,0,9,6,0,97,97,425,1.14,1.14,0.97,110,80},  // #1053
  {"Weezing de Galar",7,17,3,8,0,2,24,0,99,103,490,1.2,1.2,1.17,120,70},  // #1054
  {"Mr. Mime de Galar",5,10,3,8,0,0,38,0,92,120,460,1.2,1.06,1.2,65,90},  // #1055
  {"Tauros de Paldea (Raza Acuática)",6,2,3,9,0,10,40,0,104,120,490,1.31,1.31,0.86,105,70},  // #1056
  {"Tauros de Paldea (Raza Ardiente)",6,1,3,9,0,9,40,0,104,120,490,1.31,1.31,0.86,105,70},  // #1057
  {"Tauros de Paldea (Raza Combatiente)",6,255,3,9,0,11,40,0,104,120,490,1.31,1.31,0.86,105,70},  // #1058
  {"Articuno de Galar",10,9,5,8,1,8,21,0,110,118,580,1.39,1.17,1.39,85,100},  // #1059
  {"Zapdos de Galar",6,9,5,8,1,11,40,0,110,120,580,1.39,1.39,1.17,90,90},  // #1060
  {"Moltres de Galar",15,9,5,8,1,1,50,0,110,116,580,1.25,1.17,1.25,90,125},  // #1061
  {"Typhlosion de Hisui",1,13,4,8,0,0,6,0,103,118,534,1.35,1.16,1.35,78,85},  // #1062
  {"Wooper de Paldea",7,8,1,9,0,9,24,0,95,84,210,0.95,0.95,0.84,45,25},  // #1063
  {"Slowking de Galar",7,10,3,8,0,2,24,0,113,91,490,1.31,1.06,1.31,80,110},  // #1064
  {"Qwilfish de Hisui",15,7,3,8,0,9,50,0,99,114,440,1.22,1.22,1,85,55},  // #1065
  {"Sneasel de Hisui",6,7,3,8,0,1,40,0,95,126,430,1.22,1.22,0.89,55,75},  // #1066
  {"Corsola de Galar",13,255,3,8,0,2,43,0,97,91,410,1.06,1,1.06,100,100},  // #1067
  {"Zigzagoon de Galar",15,0,1,8,0,1,50,0,87,103,240,0.86,0.86,0.86,41,41},  // #1068
  {"Linoone de Galar",15,0,3,8,0,1,50,0,105,120,420,1.08,1.08,0.97,61,61},  // #1069
  {"Samurott de Hisui",2,15,4,8,0,0,10,0,110,114,528,1.29,1.29,1.25,80,65},  // #1070
  {"Simisear",1,255,4,5,0,0,6,0,104,120,498,1.24,1.24,1.24,63,63},  // #514
  {"Simipour",2,255,4,5,0,10,10,0,104,120,498,1.24,1.24,1.24,63,63},  // #516
  {"Tranquill",0,9,2,5,0,0,0,0,98,105,358,1.12,1.12,0.97,62,42},  // #520
  {"Blitzle",3,255,1,5,0,0,18,0,90,110,295,1.03,1.03,0.97,32,32},  // #522
  {"Zebstrika",3,255,4,5,0,0,18,0,104,127,497,1.25,1.25,1.14,63,63},  // #523
  {"Throh",6,255,3,5,0,1,40,0,124,97,465,1.25,1.25,0.86,85,85},  // #538
  {"Lilligant de Hisui",4,6,3,8,0,0,14,0,102,122,480,1.28,1.28,0.97,75,75},  // #1071
  {"Darumaka de Galar",5,255,1,8,0,0,38,0,102,99,315,1.2,1.2,0.78,45,45},  // #1072
  {"Darmanitan de Galar",5,255,3,8,0,8,38,0,117,118,480,1.47,1.47,0.86,55,55},  // #1073
  {"Crustle",11,12,3,5,0,1,33,0,102,97,485,1.28,1.28,1.06,125,75},  // #558
  {"Yamask de Galar",8,13,1,8,0,2,25,0,87,91,303,1,1,0.86,85,65},  // #1074
  {"Tirtouga",2,12,2,5,0,1,10,0,94,87,355,1.13,1.13,0.99,103,45},  // #564
  {"Carracosta",2,12,4,5,0,2,10,0,103,91,495,1.29,1.29,1.16,133,65},  // #565
  {"Zorua de Hisui",0,13,2,8,0,2,0,0,86,107,330,1.17,1.03,1.17,40,40},  // #1075
  {"Zoroark de Hisui",0,13,4,8,0,0,0,0,95,124,510,1.39,1.25,1.39,60,60},  // #1076
  {"Amoonguss",4,7,3,5,0,3,14,0,121,91,464,1.17,1.17,1.17,70,80},  // #591
  {"Frillish",2,13,2,5,0,0,10,0,95,95,335,1.06,0.92,1.06,50,85},  // #592
  {"Jellicent",2,13,3,5,0,2,10,0,115,103,480,1.17,1.03,1.17,70,105},  // #593
  {"Shelmet",11,255,1,5,0,0,33,0,92,88,305,0.92,0.92,0.92,85,65},  // #616
  {"Stunfisk",8,3,3,5,0,11,25,0,119,91,471,1.15,1.06,1.15,84,99},  // #618
  {"Stunfisk de Galar",8,16,3,8,0,9,25,0,119,91,471,1.15,1.15,1.06,99,84},  // #1077
  {"Bouffalant",0,255,3,5,0,11,0,0,113,101,490,1.31,1.31,0.92,95,95},  // #626
  {"Braviary de Hisui",10,9,4,8,0,0,21,0,120,105,510,1.32,1.16,1.32,70,70},  // #1078
  {"Pyroar",1,0,4,6,0,0,6,0,109,123,507,1.3,1.07,1.3,72,66},  // #668
  {"Aromatisse",17,255,3,6,0,3,46,0,115,90,462,1.24,1.1,1.24,72,89},  // #683
  {"Sliggoo de Hisui",16,14,3,8,0,0,48,0,96,95,452,1.16,1.11,1.16,83,113},  // #1079
  {"Goodra de Hisui",16,14,5,8,0,8,48,0,106,103,600,1.31,1.25,1.31,100,150},  // #1080
  {"Avalugg de Hisui",5,12,4,8,0,1,38,0,113,94,514,1.4,1.4,0.89,184,36},  // #1081
  {"Decidueye de Hisui",4,6,4,8,0,0,14,0,110,103,530,1.32,1.32,1.22,80,95},  // #1082
  {"Trumbeak",0,9,2,7,0,0,0,0,95,110,355,1.17,1.17,0.92,50,50},  // #732
  {"Toucannon",0,9,3,7,0,0,0,0,106,103,485,1.36,1.36,1.11,75,75},  // #733
  {"Gumshoos",0,255,3,7,0,1,0,0,110,97,418,1.31,1.31,1,60,60},  // #735
  {"Shiinotic",4,17,2,7,0,10,14,0,97,91,405,1.2,0.95,1.2,80,100},  // #756
  {"Oranguru",0,10,3,7,0,0,0,0,110,103,490,1.2,1.03,1.2,80,110},  // #765
  {"Rolycoly",12,255,1,8,0,1,36,0,84,91,240,0.92,0.92,0.92,50,50},  // #837
  {"Carkol",12,1,3,8,0,9,36,0,106,99,410,1.03,1.03,1.03,90,70},  // #838
  {"Coalossal",12,1,4,8,0,9,36,0,120,91,510,1.14,1.14,1.14,120,90},  // #839
  {"Sirfetch’d",6,255,4,8,0,0,40,0,98,105,507,1.44,1.44,1.07,95,82},  // #865
  {"Mr. Rime",5,10,4,8,0,2,38,0,106,107,520,1.31,1.17,1.31,75,100},  // #866
  {"Falinks",6,255,3,8,0,0,40,0,99,110,470,1.25,1.25,1.08,100,60},  // #870
  {"Cufant",16,255,2,8,0,0,48,0,102,95,330,1.14,1.14,0.92,49,49},  // #878
  {"Copperajah",16,255,4,8,0,3,48,0,125,91,500,1.42,1.42,1.14,69,69},  // #879
  {"Zarude",15,4,5,8,1,10,50,0,117,122,600,1.36,1.36,1.08,105,95},  // #893
  {"Dolliv",4,0,2,9,0,0,14,0,93,92,354,1.13,0.99,1.13,60,78},  // #929
  {"Squawkabilly",0,9,3,9,0,0,0,0,107,117,417,1.23,1.23,0.95,51,51},  // #931
  {"Maschiff",15,255,2,9,0,1,50,0,97,99,340,1.13,1.13,0.92,60,51},  // #942
  {"Mabosstiff",15,255,4,9,0,0,50,0,106,114,505,1.36,1.36,1.03,90,70},  // #943
  {"Shroodle",7,0,1,9,0,1,24,0,88,110,290,1.06,1.06,0.92,35,35},  // #944
  {"Grafaiai",7,0,3,9,0,0,24,0,98,124,485,1.22,1.22,1.14,65,72},  // #945
  {"Brambleghast",4,13,3,9,0,0,14,0,95,116,480,1.33,1.33,1.14,70,70},  // #947
  {"Toedscool",8,4,2,9,0,0,25,0,88,107,335,0.97,0.92,0.97,35,100},  // #948
  {"Toedscruel",8,4,4,9,0,0,25,0,106,120,515,1.14,1.08,1.14,65,120},  // #949
  {"Klawf",12,255,3,9,0,1,36,0,102,110,450,1.25,1.25,0.89,115,55},  // #950
  {"Rabsca",11,10,3,9,0,0,33,0,104,97,470,1.33,0.97,1.33,85,100},  // #954
  {"Espathra",10,255,3,9,0,0,21,0,113,122,481,1.26,1.03,1.26,60,60},  // #956
  {"Bombirdier",9,15,3,9,0,0,26,0,102,112,485,1.27,1.27,1.03,85,85},  // #962
  {"Flamigo",9,6,4,9,0,0,26,0,107,116,500,1.33,1.33,1.11,74,64},  // #973
  {"Furioseta",4,15,4,9,0,0,14,0,120,101,570,1.4,1.4,1.13,99,99},  // #986
  {"Ferrodada",8,16,4,9,0,9,25,0,110,123,570,1.32,1.32,1.1,120,70},  // #990
  {"Ferrocuello",15,9,4,9,0,1,50,0,112,123,570,1.37,1.14,1.37,86,80},  // #993
  {"Gimmighoul",13,255,1,9,0,2,43,0,90,82,300,1.11,0.86,1.11,70,70},  // #999
  {"Wo-Chien",15,4,5,9,1,0,50,0,108,107,570,1.22,1.17,1.22,100,135},  // #1001
  {"Chien-Pao",15,5,5,9,1,0,50,0,106,135,570,1.36,1.36,1.2,80,65},  // #1002
  {"Ting-Lu",15,8,5,9,1,3,50,0,140,97,570,1.31,1.31,1,125,80},  // #1003
  {"Miraidon",3,14,5,9,1,0,18,0,115,135,670,1.44,1.17,1.44,100,115},  // #1008
  {"Okidogi",7,6,5,9,1,9,24,0,110,112,555,1.4,1.4,1.02,115,86},  // #1014
  {"Flamariete",1,14,5,9,0,1,6,0,117,116,590,1.33,1.33,1.06,121,93},  // #1020
  {"Electrofuria",3,14,5,9,0,8,18,0,126,110,590,1.45,1.1,1.45,91,89},  // #1021
  {"Ferromole",12,10,5,9,0,0,36,0,110,130,590,1.36,1.36,1.07,80,108},  // #1022
  {"Ferrotesta",16,10,5,9,0,8,48,0,110,119,590,1.37,1.1,1.37,100,108},  // #1023
  {"Pecharunt",7,13,5,9,1,0,24,0,110,115,600,1.18,1.18,1.18,160,88},  // #1025
};

static const short DEX_NUM[DEX_N] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,433,434,435,436,437,438,439,440,441,442,443,444,445,446,447,448,449,450,451,452,453,454,455,456,457,458,459,460,461,462,463,464,465,466,467,468,469,470,471,472,473,474,475,476,477,478,479,480,481,482,483,484,485,486,487,488,489,490,491,492,493,494,495,496,497,498,499,500,501,502,503,504,505,506,507,508,509,510,511,512,513,515,517,518,519,521,524,525,526,527,528,529,530,531,532,533,534,535,536,537,539,540,541,542,543,544,545,546,547,548,549,550,551,552,553,554,555,556,557,559,560,561,562,563,566,567,568,569,570,571,572,573,574,575,576,577,578,579,580,581,582,583,584,585,586,587,588,589,590,594,595,596,597,598,599,600,601,602,603,604,605,606,607,608,609,610,611,612,613,614,615,617,619,620,621,622,623,624,625,627,628,629,630,631,632,633,634,635,636,637,638,639,640,641,642,643,644,645,646,647,648,649,650,651,652,653,654,655,656,657,658,659,660,661,662,663,664,665,666,667,669,670,671,672,673,674,675,676,677,678,679,680,681,682,684,685,686,687,688,689,690,691,692,693,694,695,696,697,698,699,700,701,702,703,704,705,706,707,708,709,710,711,712,713,714,715,716,717,718,719,720,721,722,723,724,725,726,727,728,729,730,731,734,736,737,738,739,740,741,742,743,744,745,746,747,748,749,750,751,752,753,754,755,757,758,759,760,761,762,763,764,766,767,768,769,770,771,772,773,774,775,776,777,778,779,780,781,782,783,784,785,786,787,788,789,790,791,792,793,794,795,796,797,798,799,800,801,802,803,804,805,806,807,808,809,810,811,812,813,814,815,816,817,818,819,820,821,822,823,824,825,826,827,828,829,830,831,832,833,834,835,836,840,841,842,843,844,845,846,847,848,849,850,851,852,853,854,855,856,857,858,859,860,861,862,863,864,867,868,869,871,872,873,874,875,876,877,880,881,882,883,884,885,886,887,888,889,890,891,892,894,895,896,897,898,899,900,901,902,903,904,905,906,907,908,909,910,911,912,913,914,915,916,917,918,919,920,921,922,923,924,925,926,927,928,930,932,933,934,935,936,937,938,939,940,941,946,951,952,953,955,957,958,959,960,961,963,964,965,966,967,968,969,970,971,972,974,975,976,977,978,979,980,981,982,983,984,985,987,988,989,991,992,994,995,996,997,998,1000,1004,1005,1006,1007,1009,1010,1011,1012,1013,1015,1016,1017,1018,1019,1024,1026,1027,1028,1029,1030,1031,1032,1033,1034,1035,1036,1037,1038,1039,1040,1041,1042,1043,1044,1045,1046,1047,1048,1049,1050,1051,1052,1053,1054,1055,1056,1057,1058,1059,1060,1061,1062,1063,1064,1065,1066,1067,1068,1069,1070,514,516,520,522,523,538,1071,1072,1073,558,1074,564,565,1075,1076,591,592,593,616,618,1077,626,1078,668,683,1079,1080,1081,1082,732,733,735,756,765,837,838,839,865,866,870,878,879,893,929,931,942,943,944,945,947,948,949,950,954,956,962,973,986,990,993,999,1001,1002,1003,1008,1014,1020,1021,1022,1023,1025};   // número de pokédex de cada fila
struct MegaDef { short base, sprite; unsigned char slot, t1, t2, own; const char* name; short hp, spd; float atk, pa, sa; unsigned char df, sd; };
#define NMEGAS 91
static const MegaDef MEGAS[NMEGAS] = {
  {3,3000,0,4,7,1,"Mega-Venusaur",106,112,1.37,1.25,1.37,123,120},
  {6,3001,0,1,14,1,"Mega-Charizard X",105,120,1.42,1.42,1.42,111,85},
  {6,3002,1,1,9,1,"Mega-Charizard Y",105,120,1.57,1.27,1.57,78,115},
  {9,3003,0,2,255,1,"Mega-Blastoise",106,111,1.44,1.27,1.44,120,115},
  {15,3004,0,11,7,1,"Mega-Beedrill",99,139,1.52,1.52,0.78,40,80},
  {18,3005,0,0,9,1,"Mega-Pidgeot",107,129,1.44,1.14,1.44,80,80},
  {26,3006,0,3,255,1,"Mega-Raichu X",97,124,1.44,1.44,1.2,95,95},
  {26,3007,1,3,255,1,"Mega-Raichu Y",97,133,1.58,1.25,1.58,55,80},
  {36,3008,0,17,9,1,"Mega-Clefable",113,107,1.44,1.14,1.44,93,110},
  {65,3009,0,10,255,1,"Mega-Alakazam",95,141,1.66,0.97,1.66,65,105},
  {71,3010,0,4,7,1,"Mega-Victreebel",106,107,1.44,1.39,1.44,85,95},
  {80,3011,0,2,10,1,"Mega-Slowbro",113,91,1.42,1.11,1.42,180,80},
  {94,3012,0,13,7,1,"Mega-Gengar",97,133,1.64,1.06,1.64,80,95},
  {115,3013,0,0,255,1,"Mega-Kangaskhan",117,120,1.39,1.39,1.03,100,100},
  {121,3014,0,2,10,1,"Mega-Starmie",97,128,1.42,1.25,1.42,105,105},
  {127,3015,0,11,9,1,"Mega-Pinsir",99,122,1.55,1.55,1.06,120,90},
  {130,3016,0,2,15,1,"Mega-Gyarados",113,112,1.55,1.55,1.08,109,130},
  {142,3017,0,12,9,1,"Mega-Aerodactyl",106,141,1.44,1.44,1.08,85,95},
  {149,3018,0,14,9,1,"Mega-Dragonite",111,120,1.5,1.38,1.5,115,125},
  {150,3019,0,10,6,1,"Mega-Mewtwo X",118,133,1.74,1.74,1.55,100,100},
  {150,3020,1,10,255,1,"Mega-Mewtwo Y",118,137,1.77,1.52,1.77,70,120},
  {154,3021,0,4,17,1,"Mega-Meganium",106,112,1.49,1.21,1.49,115,115},
  {160,3022,0,2,14,1,"Mega-Feraligatr",108,111,1.58,1.58,1.19,125,93},
  {181,3023,0,3,14,1,"Mega-Ampharos",110,97,1.61,1.22,1.61,105,110},
  {208,3024,0,16,8,1,"Mega-Steelix",104,91,1.39,1.39,1,230,95},
  {212,3025,0,11,16,1,"Mega-Scizor",102,110,1.52,1.52,1.06,140,100},
  {214,3026,0,11,6,1,"Mega-Heracross",106,110,1.72,1.72,0.92,115,105},
  {227,3027,0,16,9,1,"Mega-Skarmory",99,124,1.47,1.47,0.92,110,100},
  {229,3028,0,15,1,1,"Mega-Houndoom",104,126,1.47,1.2,1.47,90,90},
  {248,3029,0,12,15,1,"Mega-Tyranitar",115,108,1.6,1.6,1.22,150,120},
  {254,3030,0,4,14,1,"Mega-Sceptile",102,139,1.5,1.31,1.5,75,85},
  {257,3031,0,1,6,1,"Mega-Blaziken",106,120,1.58,1.58,1.42,80,80},
  {260,3032,0,2,8,1,"Mega-Swampert",115,107,1.52,1.52,1.22,110,110},
  {282,3033,0,10,17,1,"Mega-Gardevoir",101,120,1.61,1.17,1.61,65,135},
  {302,3034,0,15,13,1,"Mega-Sableye",92,86,1.17,1.17,1.17,125,115},
  {303,3035,0,16,17,1,"Mega-Mawile",92,99,1.28,1.28,1,125,95},
  {306,3036,0,16,255,1,"Mega-Aggron",102,99,1.47,1.47,1.03,230,80},
  {308,3037,0,6,10,1,"Mega-Medicham",97,120,1.25,1.25,1.14,85,85},
  {310,3038,0,3,255,1,"Mega-Manectric",102,135,1.44,1.11,1.44,80,80},
  {319,3039,0,2,15,1,"Mega-Sharpedo",102,122,1.47,1.47,1.31,70,65},
  {323,3040,0,1,8,1,"Mega-Camerupt",102,86,1.5,1.36,1.5,100,105},
  {334,3041,0,14,17,1,"Mega-Altaria",104,112,1.31,1.31,1.31,110,105},
  {354,3042,0,13,255,1,"Mega-Banette",99,110,1.61,1.61,1.21,75,83},
  {358,3043,0,10,16,1,"Mega-Chimecho",104,105,1.44,0.97,1.44,110,120},
  {359,3044,0,15,255,1,"Mega-Absol",99,126,1.52,1.52,1.33,60,60},
  {359,3045,1,15,13,1,"Mega-Absol Z",99,141,1.55,1.55,1.11,60,60},
  {362,3046,0,5,255,1,"Mega-Glalie",106,120,1.36,1.36,1.36,80,80},
  {373,3047,0,14,9,1,"Mega-Salamence",113,128,1.5,1.5,1.36,130,90},
  {376,3048,0,16,10,1,"Mega-Metagross",106,124,1.5,1.5,1.28,150,110},
  {380,3049,0,14,10,1,"Mega-Latias",106,124,1.47,1.25,1.47,120,150},
  {381,3050,0,14,10,1,"Mega-Latios",106,124,1.58,1.42,1.58,100,120},
  {384,3051,0,14,9,1,"Mega-Rayquaza",117,126,1.69,1.69,1.69,100,100},
  {398,3052,0,6,9,1,"Mega-Staraptor",108,124,1.47,1.47,1.03,100,90},
  {428,3053,0,0,6,1,"Mega-Lopunny",99,135,1.45,1.45,1,94,96},
  {445,3054,0,14,8,1,"Mega-Garchomp",119,117,1.64,1.64,1.36,115,95},
  {445,3055,1,14,255,1,"Mega-Garchomp Z",119,141,1.48,1.42,1.48,85,85},
  {448,3056,0,6,16,1,"Mega-Lucario",102,125,1.5,1.5,1.47,88,70},
  {448,3057,1,6,16,1,"Mega-Lucario Z",102,141,1.6,1.25,1.6,70,70},
  {460,3058,0,4,5,1,"Mega-Abomasnow",110,91,1.43,1.43,1.43,105,105},
  {475,3059,0,10,6,1,"Mega-Gallade",101,124,1.61,1.61,1.06,95,115},
  {478,3060,0,5,13,1,"Mega-Froslass",102,128,1.47,1.14,1.47,70,100},
  {485,3061,0,1,16,1,"Mega-Heatran",111,106,1.66,1.36,1.66,106,141},
  {491,3062,0,15,255,1,"Mega-Darkrai",102,114,1.61,1.36,1.61,130,130},
  {500,3063,0,1,6,1,"Mega-Emboar",120,110,1.51,1.51,1.31,75,110},
  {530,3064,0,8,16,1,"Mega-Excadrill",120,121,1.61,1.61,1.06,100,65},
  {531,3065,0,0,17,1,"Mega-Audino",116,99,1.14,1.03,1.14,126,126},
  {545,3066,0,11,7,1,"Mega-Scolipede",97,104,1.47,1.47,1.11,149,99},
  {560,3067,0,15,6,1,"Mega-Scrafty",99,107,1.42,1.42,1,135,135},
  {604,3068,0,3,255,1,"Mega-Eelektross",108,112,1.5,1.5,1.44,80,90},
  {609,3069,0,13,1,1,"Mega-Chandelure",97,116,1.66,1.11,1.66,110,110},
  {623,3070,0,8,13,1,"Mega-Golurk",110,101,1.57,1.57,1.08,105,105},
  {652,3071,0,4,6,1,"Mega-Chesnaught",110,96,1.45,1.45,1.11,172,115},
  {655,3072,0,1,10,1,"Mega-Delphox",104,134,1.57,1.08,1.57,72,125},
  {658,3073,0,2,15,1,"Mega-Greninja",102,138,1.43,1.39,1.43,77,81},
  {670,3074,0,17,255,1,"Mega-Floette",103,121,1.55,1.17,1.55,87,148},
  {678,678,0,10,255,0,"Mega-Meowstic",103,130,1.49,0.96,1.49,76,101},
  {687,3076,0,15,10,1,"Mega-Malamar",109,115,1.26,1.26,1.24,88,120},
  {689,3077,0,12,6,1,"Mega-Barbaracle",102,115,1.47,1.47,1.05,130,106},
  {691,3078,0,7,14,1,"Mega-Dragalge",99,96,1.43,1.17,1.43,105,163},
  {701,3079,0,6,9,1,"Mega-Hawlucha",105,128,1.45,1.45,1.11,100,93},
  {718,3080,0,14,8,1,"Mega-Zygarde",167,120,1.89,1.08,1.89,91,85},
  {719,3081,0,12,17,1,"Mega-Diancie",92,124,1.58,1.58,1.58,110,110},
  {740,3082,0,6,5,1,"Mega-Crabominable",114,92,1.56,1.56,1.04,122,107},
  {768,768,0,11,16,0,"Mega-Golisopod",104,95,1.52,1.52,1.08,175,120},
  {780,3084,0,0,14,1,"Mega-Drampa",105,93,1.58,1.17,1.58,110,116},
  {801,801,0,16,17,0,"Mega-Magearna",106,118,1.64,1.39,1.64,115,115},
  {807,3086,0,3,255,1,"Mega-Zeraora",110,142,1.56,1.56,1.51,75,80},
  {952,3087,0,4,1,1,"Mega-Scovillain",99,110,1.46,1.46,1.46,85,85},
  {970,3088,0,12,7,1,"Mega-Glimmora",107,120,1.52,1.2,1.52,105,96},
  {978,3089,0,14,2,1,"Mega-Tatsugiri",101,117,1.44,1.06,1.44,90,125},
  {998,3090,0,14,5,1,"Mega-Baxcalibur",122,115,1.66,1.66,1.28,117,101},
};

static const short STARTERS_IDX[] = {0,3,6,151,154,157,251,254,257,386,389,392,494,497,500,634,637,640,704,707,710,787,790,793,874,877,880,53,78};
#define NSTARTERS 29

#define NTRAITS 16
#define NQUIZ 8
static const char* TRAIT_NAME[NTRAITS] = {"Valiente","Impulsivo","Prudente","Leal","Paciente","Dulce","Tímido","Travieso","Sereno","Astuto","Alegre","Tenaz","Orgulloso","Solitario","Tranquilo","Caótico"};
static const char* TRAIT_TXT[NTRAITS] = {"No te lo piensas dos veces cuando alguien necesita ayuda.","Actúas primero y piensas después. ¡A veces sale bien!","Mides cada paso antes de darlo.","Tus amigos saben que pueden contar contigo siempre.","Sabes esperar el momento justo.","Tu amabilidad tranquiliza a todos los que te rodean.","Te cuesta dar el primer paso, pero sientes mucho.","Siempre tienes una broma preparada.","Mantienes la calma cuando todo se complica.","Ves soluciones donde otros ven problemas.","Contagias energía allá donde vas.","Rendirse no entra en tus planes.","Te exiges ser el mejor, y casi siempre lo consigues.","Vas a tu aire y no te importa.","Nada te altera. Nada.","Ni tú sabes qué vas a hacer después."};
static const unsigned char STARTER_TRAITS[NSTARTERS][2] = {{3,4},{0,1},{2,3},{5,4},{6,1},{7,0},{8,9},{10,0},{11,3},{4,11},{7,10},{12,2},{12,9},{11,10},{0,7},{7,11},{9,8},{8,9},{8,5},{13,12},{10,5},{10,7},{1,10},{6,9},{13,9},{14,11},{12,2},{15,6},{14,4}};
struct QuizA { const char* t; signed char p[NTRAITS]; };
struct QuizQ { const char* q; QuizA a[4]; };
static const QuizQ QUIZ[NQUIZ] = {{"¡Hay una pelea en mitad del pueblo! ¿Qué haces?",{{"Me meto a ayudar sin pensarlo.",{2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},{"Busco a alguien que pueda pararla.",{0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0}},{"Lo observo todo desde lejos.",{0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0}},{"Me río y animo a los dos.",{0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,1}}}},
{"Te encuentras una cartera en el suelo.",{{"La llevo enseguida a la policía.",{0,0,0,2,0,1,0,0,0,0,0,0,0,0,0,0}},{"Busco a su dueño aunque tarde horas.",{0,0,0,0,1,0,0,0,0,0,0,2,0,0,0,0}},{"Primero miro qué hay dentro…",{0,0,0,0,0,0,0,1,0,2,0,0,0,0,0,0}},{"Ni la toco, no vaya a ser.",{0,0,1,0,0,0,2,0,0,0,0,0,0,0,0,0}}}},
{"Tu día libre ideal es…",{{"Una aventura sin ningún plan.",{0,2,0,0,0,0,0,0,0,0,1,0,0,0,0,0}},{"Leer, pensar, estar tranquilo.",{0,0,0,0,0,0,0,0,2,0,0,0,0,0,1,0}},{"Quedar con todos mis amigos.",{0,0,0,1,0,0,0,0,0,0,2,0,0,0,0,0}},{"Entrenar para ser mejor.",{0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0}}}},
{"Mañana tienes un examen importante.",{{"Estudio hasta las tantas.",{0,0,1,0,0,0,0,0,0,0,0,2,0,0,0,0}},{"Repaso lo justo: confío en mí.",{0,0,0,0,0,0,0,0,1,0,0,0,2,0,0,0}},{"Me agobio muchísimo.",{0,0,0,0,0,1,2,0,0,0,0,0,0,0,0,0}},{"¿Examen? Ya veré mañana.",{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2}}}},
{"¿Qué dicen de ti tus amigos?",{{"Que soy lo más divertido del grupo.",{0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0}},{"Que siempre pueden contar conmigo.",{0,0,0,2,0,1,0,0,0,0,0,0,0,0,0,0}},{"Que soy un poco misterioso.",{0,0,0,0,0,0,0,0,0,1,0,0,0,2,0,0}},{"Que no me rindo nunca.",{1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0}}}},
{"El camino se divide: uno oscuro y corto, otro largo y soleado.",{{"El oscuro, ¡más emoción!",{2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},{"El largo, sin prisa.",{0,0,1,0,2,0,0,0,0,0,0,0,0,0,0,0}},{"Me siento a pensarlo un rato.",{0,0,0,0,0,0,0,0,1,0,0,0,0,0,2,0}},{"Ninguno: abro un atajo nuevo.",{0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,1}}}},
{"Alguien se burla de ti delante de todos.",{{"Le contesto en el acto.",{0,1,0,0,0,0,0,0,0,0,0,0,2,0,0,0}},{"Le ignoro por completo.",{0,0,0,0,0,0,0,0,2,0,0,0,0,1,0,0}},{"Me afecta, aunque no lo diga.",{0,0,0,0,0,1,2,0,0,0,0,0,0,0,0,0}},{"Le devuelvo una broma mejor.",{0,0,0,0,0,0,0,2,0,1,0,0,0,0,0,0}}}},
{"¿Qué es lo más importante para ti?",{{"La amistad.",{0,0,0,2,0,0,0,0,0,0,1,0,0,0,0,0}},{"La libertad.",{0,1,0,0,0,0,0,0,0,0,0,0,0,2,0,0}},{"La calma.",{0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0}},{"Ser el mejor.",{0,0,0,0,0,0,0,0,0,0,0,1,2,0,0,0}}}}};

#define NITEMS 11
static const char* ITEM_NAMES[NITEMS] = {"Restos","Cinta Elección","Garra Rápida","Banda Focus","Cascabel Concha","Moneda Amuleto","Huevo Suerte","Vidasfera","Pañuelo Elección","Casco Dentado","Chaleco Asalto"};
static const char* ITEM_DESCS[NITEMS] = {"Recuperas un 1,5% de tu vida por segundo.","+40% de daño, pero no puedes cambiar de movimiento.","-20% de recarga en todos tus movimientos.","Un golpe que te dejaría KO te deja con 1 de vida (cada 60 s).","Recuperas vida con el daño que haces.","+50% de Pokémonedas al acabar la run.","+30% de experiencia.","+30% de daño, pero cada ataque te quita un poco de vida.","+35% de velocidad.","Los que te golpean cuerpo a cuerpo reciben daño.","+20% de reducción de daño recibido."};
struct PermUp { const char* name; const char* unit; unsigned char max; float base, grow; };
#define NPERM 15
static const PermUp PERM[NPERM] = {{"Vitalidad","+8 vida",10,60,1.35},{"Fuerza","+4% daño",10,80,1.38},{"Zancada","+3% velocidad",8,70,1.4},{"Reflejos","-3% recarga",8,90,1.42},{"Coraza","+2% defensa",8,80,1.4},{"Síntesis","+0.2 vida/s",5,120,1.5},{"Imán","+12% recogida",6,50,1.4},{"Sabiduría","+5% experiencia",8,100,1.42},{"Fortuna","+8% Pokémonedas",8,120,1.45},{"Repertorio","Empiezas con 2 movimientos",1,1500,1},{"Golpe Crítico","+3% de críticos (x1,5 de daño)",10,90,1.4},{"Cambio de cartas","+1 cambio de cartas de nivel por run",5,150,1.6},{"Veto","Bloquea 1 movimiento: no te sale en las cartas",3,300,1.9},{"Movimiento inicial","Eliges con qué ataque empiezas la partida",1,400,1},{"Segundo movimiento inicial","Eliges el segundo ataque con el que empiezas (necesita Repertorio)",1,400,1}};
static const char* PERM_IDS[NPERM] = {"hp","atk","spd","cd","def","regen","magnet","xp","coins","moves","crit","reroll","ban","start","start2"};

// nombres: [es, en, fr, it, zh-Hans, zh-Hant]
enum { NS_PA, NS_SA, NS_DF, NS_SD, NS_SPD };
struct NatureE { const char* n[6]; signed char up, down; };
#define NNAT 25
static const NatureE NATURES[NNAT] = {
  {{"Fuerte","Hardy","Hardi","Ardita","勤奋","勤奮"},-1,-1},
  {{"Osada","Bold","Assuré","Sicura","大胆","大膽"},2,0},
  {{"Modesta","Modest","Modeste","Modesta","内敛","內斂"},1,0},
  {{"Serena","Calm","Calme","Calma","温和","溫和"},3,0},
  {{"Miedosa","Timid","Timide","Timida","胆小","膽小"},4,0},
  {{"Huraña","Lonely","Solo","Schiva","怕寂寞","怕寂寞"},0,2},
  {{"Dócil","Docile","Docile","Docile","坦率","坦率"},-1,-1},
  {{"Afable","Mild","Doux","Mite","慢吞吞","慢吞吞"},1,2},
  {{"Amable","Gentle","Gentil","Gentile","温顺","溫順"},3,2},
  {{"Activa","Hasty","Pressé","Lesta","急躁","急躁"},4,2},
  {{"Firme","Adamant","Rigide","Decisa","固执","固執"},0,1},
  {{"Agitada","Impish","Malin","Scaltra","淘气","淘氣"},2,1},
  {{"Tímida","Bashful","Pudique","Ritrosa","害羞","害羞"},-1,-1},
  {{"Cauta","Careful","Prudent","Cauta","慎重","慎重"},3,1},
  {{"Alocada","Rash","Foufou","Ardente","马虎","馬虎"},1,3},
  {{"Alegre","Jolly","Jovial","Allegra","爽朗","爽朗"},4,1},
  {{"Pícara","Naughty","Mauvais","Birbona","顽皮","頑皮"},0,3},
  {{"Floja","Lax","Lâche","Fiacca","乐天","樂天"},2,3},
  {{"Rara","Quirky","Bizarre","Furba","浮躁","浮躁"},-1,-1},
  {{"Ingenua","Naive","Naïf","Ingenua","天真","天真"},4,3},
  {{"Audaz","Brave","Brave","Audace","勇敢","勇敢"},0,4},
  {{"Plácida","Relaxed","Relax","Placida","悠闲","悠閒"},2,4},
  {{"Mansa","Quiet","Discret","Quieta","冷静","冷靜"},1,4},
  {{"Grosera","Sassy","Malpoli","Vivace","自大","自大"},3,4},
  {{"Seria","Serious","Sérieux","Seria","认真","認真"},-1,-1},
};

enum { AO_OUT_TYPE=0,AO_OUT_PINCH=1,AO_OUT_CAT=2,AO_OUT_ALL=3,AO_OUT_HALFCAT=4,AO_OUT_STAB=5,AO_OUT_KIND=6,AO_OUT_BOSS=7,AO_OUT_ELOW=8,AO_OUT_ETYPE=9,AO_OUT_WX=10,AO_OUT_DEFEAT=11,AO_OUT_HIGH=12,AO_IN_ALL=13,AO_IN_TYPE=14,AO_IN_CAT=15,AO_IN_FULL=16,AO_IN_SE=17,AO_IN_WONDER=18,AO_ABSORB=19,AO_SPEED=20,AO_SPEED_WX=21,AO_REGEN=22,AO_REGEN_WX=23,AO_CRIT=24,AO_CRITMUL=25,AO_MAGNET=26,AO_COINS=27,AO_DODGE=28,AO_DODGE_WX=29,AO_CD=30,AO_HP=31,AO_SUMMON=32,AO_MOXIE=33,AO_STURDY=34 };
struct AbTerm { unsigned char op; signed char a; float k; };
struct AbilE { const char* n[6]; const char* desc; unsigned char nt, plus; AbTerm t[3]; };
#define NABIL 271
static const AbilE ABIL[NABIL] = {
  {{"Adaptable","Adaptability","Adaptabilité","Adattabilità","适应力","適應力"},"+25 % de daño con los movimientos de sus tipos.",1,0,{{5,0,1.25}}},  // adaptability
  {{"Detonación","Aftermath","Boom Final","Scoppio","引爆","引爆"},"",0,0,{}},  // aftermath
  {{"Bucle Aire","Air Lock","Air Lock","Riparo","气闸","氣閘"},"",0,0,{}},  // air-lock
  {{"Cálculo Final","Analytic","Analyste","Ponderazione","分析","分析"},"+15 % de daño a enemigos con menos de la mitad de vida.",1,1,{{8,0,1.15}}},  // analytic
  {{"Irascible","Anger Point","Colérique","Grancollera","愤怒穴位","憤怒穴位"},"",0,0,{}},  // anger-point
  {{"Anticipación","Anticipation","Anticipation","Presagio","危险预知","危險預知"},"Presiente el peligro: esquiva el 6 % de los golpes.",1,1,{{28,0,0.06}}},  // anticipation
  {{"Trampa Arena","Arena Trap","Piège Sable","Trappoarena","沙穴","沙穴"},"",0,0,{}},  // arena-trap
  {{"Cola Armadura","Armor Tail","Armure Caudale","Codarmatura","尾甲","尾甲"},"",0,0,{}},  // armor-tail
  {{"Velo Aroma","Aroma Veil","Aroma-Voile","Aromavelo","芳香幕","芳香幕"},"",0,0,{}},  // aroma-veil
  {{"Rompeaura","Aura Break","Aura Inversée","Frangiaura","气场破坏","氣場破壞"},"",0,0,{}},  // aura-break
  {{"Mal Sueño","Bad Dreams","Mauvais Rêve","Sogniamari","梦魇","夢魘"},"",0,0,{}},  // bad-dreams
  {{"Recogebolas","Ball Fetch","Ramasse Ball","Raccattapalle","捡球","撿球"},"",0,0,{}},  // ball-fetch
  {{"Batería","Battery","Batterie","Batteria","蓄电池","蓄電池"},"",0,0,{}},  // battery
  {{"Armadura Batalla","Battle Armor","Armurbaston","Lottascudo","战斗盔甲","戰鬥盔甲"},"Recibe un 8 % menos de daño.",1,0,{{13,0,0.92}}},  // battle-armor
  {{"Abalorio Debacle","Beads of Ruin","Perles du Fléau","Monile Nefasto","灾祸之玉","災禍之玉"},"",0,0,{}},  // beads-of-ruin
  {{"Ultraimpulso","Beast Boost","Boost Chimère","Ultraboost","异兽提升","異獸提升"},"Cada enemigo derrotado le da +0,5 % de daño (hasta +15 %).",1,0,{{33,0,0.005}}},  // beast-boost
  {{"Cólera","Berserk","Folle Furie","Furore","怒火冲天","怒火沖天"},"",0,0,{}},  // berserk
  {{"Sacapecho","Big Pecks","Cœur de Coq","Pettinfuori","健壮胸肌","健壯胸肌"},"Recibe un 8 % menos de daño físico.",1,1,{{15,0,0.92}}},  // big-pecks
  {{"Mar Llamas","Blaze","Brasier","Aiutofuoco","猛火","猛火"},"+35 % de daño de tipo Fuego con poca vida (menos de 1/3).",1,0,{{1,1,1.35}}},  // blaze
  {{"Antibalas","Bulletproof","Pare-Balles","Antiproiettile","防弹","防彈"},"Recibe un 15 % menos de daño especial.",1,1,{{15,1,0.85}}},  // bulletproof
  {{"Carrillo","Cheek Pouch","Bajoues","Guancegonfie","颊囊","頰囊"},"",0,0,{}},  // cheek-pouch
  {{"Relincho Blanco","Chilling Neigh","Blanche Ruade","Nitrito Bianco","苍白嘶鸣","蒼白嘶鳴"},"Cada enemigo derrotado le da +0,5 % de daño (hasta +15 %).",1,0,{{33,0,0.005}}},  // chilling-neigh
  {{"Clorofila","Chlorophyll","Chlorophylle","Clorofilla","叶绿素","葉綠素"},"+50 % de velocidad con sol.",1,0,{{21,1,1.5}}},  // chlorophyll
  {{"Cuerpo Puro","Clear Body","Corps Sain","Corpochiaro","恒净之躯","恆淨之軀"},"",0,0,{}},  // clear-body
  {{"Aclimatación","Cloud Nine","Ciel Gris","Antimeteo","无关天气","無關天氣"},"",0,0,{}},  // cloud-nine
  {{"Cambio Color","Color Change","Homochromie","Cambiacolore","变色","變色"},"",0,0,{}},  // color-change
  {{"Letargo Perenne","Comatose","Hypersommeil","Sonno Assoluto","绝对睡眠","絕對睡眠"},"",0,0,{}},  // comatose
  {{"Comandar","Commander","Commandant","Torre di Comando","发号施令","發號施令"},"",0,0,{}},  // commander
  {{"Tenacidad","Competitive","Battant","Tenacia","好胜","好勝"},"",0,0,{}},  // competitive
  {{"Ojo Compuesto","Compound Eyes","Œil Composé","Insettocchi","复眼","複眼"},"+6 % de probabilidad de golpe crítico.",1,0,{{24,0,0.06}}},  // compound-eyes
  {{"Respondón","Contrary","Contestation","Inversione","唱反调","唱反調"},"",0,0,{}},  // contrary
  {{"Corrosión","Corrosion","Corrosion","Corrosione","腐蚀","腐蝕"},"",0,0,{}},  // corrosion
  {{"Pelusa","Cotton Down","Effilochage","Lanugine","棉絮","棉絮"},"",0,0,{}},  // cotton-down
  {{"Rumia","Cud Chew","Ruminant","Ruminante","反刍","反芻"},"",0,0,{}},  // cud-chew
  {{"Cuerpo Maldito","Cursed Body","Corps Maudit","Corpofunesto","诅咒之躯","詛咒之軀"},"",0,0,{}},  // cursed-body
  {{"Gran Encanto","Cute Charm","Joli Sourire","Incantevole","迷人之躯","迷人之軀"},"",0,0,{}},  // cute-charm
  {{"Humedad","Damp","Moiteur","Umidità","湿气","濕氣"},"",0,0,{}},  // damp
  {{"Pareja de Baile","Dancer","Danseuse","Sincrodanza","舞者","舞者"},"",0,0,{}},  // dancer
  {{"Aura Oscura","Dark Aura","Aura Ténébreuse","Auratetra","暗黑气场","暗黑氣場"},"",0,0,{}},  // dark-aura
  {{"Escudo Recio","Dauntless Shield","Égide Inflexible","Scudo Saldo","不屈之盾","不屈之盾"},"",0,0,{}},  // dauntless-shield
  {{"Cuerpo Vívido","Dazzling","Corps Coloré","Corposgargiante","鲜艳之躯","鮮艷之軀"},"",0,0,{}},  // dazzling
  {{"Flaqueza","Defeatist","Défaitiste","Sconforto","软弱","軟弱"},"Cañón de cristal: +15 % de daño con más de la mitad de vida; con menos, −25 %.",1,0,{{11,0,1}}},  // defeatist
  {{"Competitivo","Defiant","Acharné","Agonismo","不服输","不服輸"},"",0,0,{}},  // defiant
  {{"Disfraz","Disguise","Fantômasque","Fantasmanto","画皮","畫皮"},"",0,0,{}},  // disguise
  {{"Descarga","Download","Télécharge","Download","下载","下載"},"",0,0,{}},  // download
  {{"Mandíbula Dragón","Dragon’s Maw","Dent de Dragon","Dragomascelle","龙颚","龍顎"},"+20 % de daño con movimientos de tipo Dragón.",1,0,{{0,14,1.2}}},  // dragons-maw
  {{"Llovizna","Drizzle","Crachin","Piovischio","降雨","降雨"},"Pone lluvia al empezar la partida y cada 3 minutos.",1,0,{{32,2,0}}},  // drizzle
  {{"Sequía","Drought","Sécheresse","Siccità","日照","日照"},"Pone sol al empezar la partida y cada 3 minutos.",1,0,{{32,1,0}}},  // drought
  {{"Piel Seca","Dry Skin","Peau Sèche","Pellearsa","干燥皮肤","乾燥皮膚"},"El Agua le cura y con lluvia recupera vida, pero el Fuego le hace un 25 % más.",3,0,{{19,2,0},{14,1,1.25},{23,2,0.012}}},  // dry-skin
  {{"Madrugar","Early Bird","Matinal","Sveglialampo","早起","早起"},"",0,0,{}},  // early-bird
  {{"Geofagia","Earth Eater","Absorbe-Terre","Mangiaterra","食土","食土"},"Los ataques de tipo Tierra no le hacen daño: le curan un poco.",1,0,{{19,8,0}}},  // earth-eater
  {{"Efecto Espora","Effect Spore","Pose Spore","Spargispora","孢子","孢子"},"",0,0,{}},  // effect-spore
  {{"Electrogénesis","Electric Surge","Créa-Élec","Elettrogenesi","电气制造者","電氣製造者"},"",0,0,{}},  // electric-surge
  {{"Dinamo","Electromorphosis","Grecharge","Convertivolt","电力转换","電力轉換"},"",0,0,{}},  // electromorphosis
  {{"Retirada","Emergency Exit","Repli Tactique","Passoindietro","危险回避","危險迴避"},"",0,0,{}},  // emergency-exit
  {{"Aura Feérica","Fairy Aura","Aura Féérique","Aurafolletto","妖精气场","妖精氣場"},"",0,0,{}},  // fairy-aura
  {{"Filtro","Filter","Filtre","Filtro","过滤","過濾"},"Los ataques muy eficaces le hacen un 25 % menos.",1,0,{{17,0,0.75}}},  // filter
  {{"Cuerpo Llama","Flame Body","Corps Ardent","Corpodifuoco","火焰之躯","火焰之軀"},"",0,0,{}},  // flame-body
  {{"Ímpetu Ardiente","Flare Boost","Rage Brûlure","Bruciaimpeto","受热激升","受熱激升"},"",0,0,{}},  // flare-boost
  {{"Absorbe Fuego","Flash Fire","Torche","Fuocardore","引火","引火"},"Los ataques de tipo Fuego no le hacen daño: le curan un poco.",1,0,{{19,1,0}}},  // flash-fire
  {{"Don Floral","Flower Gift","Don Floral","Regalfiore","花之礼","花之禮"},"",0,0,{}},  // flower-gift
  {{"Velo Flor","Flower Veil","Flora-Voile","Fiorvelo","花幕","花幕"},"",0,0,{}},  // flower-veil
  {{"Peluche","Fluffy","Boule de Poils","Morbidone","毛茸茸","毛茸茸"},"Recibe un 30 % menos de daño físico.",1,0,{{15,0,0.7}}},  // fluffy
  {{"Predicción","Forecast","Météo","Previsioni","阴晴不定","陰晴不定"},"",0,0,{}},  // forecast
  {{"Alerta","Forewarn","Prédiction","Premonizione","预知梦","預知夢"},"Presiente el peligro: esquiva el 6 % de los golpes.",1,1,{{28,0,0.06}}},  // forewarn
  {{"Compiescolta","Friend Guard","Garde-Ami","Amicoscudo","友情防守","友情防守"},"Recibe un 6 % menos de daño.",1,1,{{13,0,0.94}}},  // friend-guard
  {{"Cacheo","Frisk","Fouille","Indagine","察觉","察覺"},"Atrae los objetos desde más lejos (+20 % de imán).",1,1,{{26,0,1.2}}},  // frisk
  {{"Guardia Metálica","Full Metal Body","Métallo-Garde","Metalprotezione","金属防护","金屬防護"},"",0,0,{}},  // full-metal-body
  {{"Pelaje Recio","Fur Coat","Toison Épaisse","Foltopelo","毛皮大衣","毛皮大衣"},"Recibe un 40 % menos de daño físico.",1,0,{{15,0,0.6}}},  // fur-coat
  {{"Alas Vendaval","Gale Wings","Ailes Bourrasque","Aliraffica","疾风之翼","疾風之翼"},"",0,0,{}},  // gale-wings
  {{"Gula","Gluttony","Gloutonnerie","Voracità","贪吃鬼","貪吃鬼"},"",0,0,{}},  // gluttony
  {{"Cuerpo Áureo","Good as Gold","Corps en Or","Corpo Aureo","黄金之躯","黃金之軀"},"",0,0,{}},  // good-as-gold
  {{"Baba","Gooey","Poisseux","Viscosità","黏滑","黏滑"},"",0,0,{}},  // gooey
  {{"Manto Frondoso","Grass Pelt","Toison Herbue","Peloderba","草之毛皮","草之毛皮"},"",0,0,{}},  // grass-pelt
  {{"Herbogénesis","Grassy Surge","Créa-Herbe","Erbogenesi","青草制造者","青草製造者"},"",0,0,{}},  // grassy-surge
  {{"Relincho Negro","Grim Neigh","Sombre Ruade","Nitrito Nero","漆黑嘶鸣","漆黑嘶鳴"},"Cada enemigo derrotado le da +0,5 % de daño (hasta +15 %).",1,0,{{33,0,0.005}}},  // grim-neigh
  {{"Tragamisil","Gulp Missile","Dégobage","Inghiottimissile","一口导弹","一口飛彈"},"",0,0,{}},  // gulp-missile
  {{"Agallas","Guts","Cran","Dentistretti","毅力","毅力"},"+30 % de daño físico con menos de la mitad de vida.",1,0,{{4,0,1.3}}},  // guts
  {{"Cosecha","Harvest","Récolte","Coglibacche","收获","收穫"},"",0,0,{}},  // harvest
  {{"Alma Cura","Healer","Cœur Soin","Curacuore","治愈之心","治癒之心"},"Recupera un 0,3 % de su vida por segundo.",1,1,{{22,0,0.003}}},  // healer
  {{"Ignífugo","Heatproof","Ignifugé","Antifuoco","耐热","耐熱"},"Recibe la mitad de daño de Fuego.",1,0,{{14,1,0.5}}},  // heatproof
  {{"Metal Pesado","Heavy Metal","Heavy Metal","Metalpesante","重金属","重金屬"},"",0,0,{}},  // heavy-metal
  {{"Recogemiel","Honey Gather","Cherche Miel","Mielincetta","采蜜","採蜜"},"+15 % de Pokémonedas en la partida.",1,0,{{27,0,1.15}}},  // honey-gather
  {{"Hospitalidad","Hospitality","Aux Petits Soins","Ospitalità","款待","款待"},"",0,0,{}},  // hospitality
  {{"Potencia","Huge Power","Coloforce","Macroforza","大力士","大力士"},"+50 % de daño con movimientos físicos.",1,0,{{2,0,1.5}}},  // huge-power
  {{"Mutapetito","Hunger Switch","Déclic Fringale","Pancialterna","饱了又饿","飽了又餓"},"",0,0,{}},  // hunger-switch
  {{"Entusiasmo","Hustle","Agitation","Tuttafretta","活力","活力"},"",0,0,{}},  // hustle
  {{"Hidratación","Hydration","Hydratation","Idratazione","湿润之躯","濕潤之軀"},"",0,0,{}},  // hydration
  {{"Corte Fuerte","Hyper Cutter","Hyper Cutter","Ipertaglio","怪力钳","怪力鉗"},"+6 % de daño con movimientos físicos.",1,1,{{2,0,1.06}}},  // hyper-cutter
  {{"Gélido","Ice Body","Corps Gel","Corpogelo","冰冻之躯","冰凍之軀"},"Con nieve recupera un 1,5 % de vida por segundo.",1,0,{{23,4,0.015}}},  // ice-body
  {{"Cara de Hielo","Ice Face","Tête de Gel","Gelofaccia","结冻头","結凍頭"},"",0,0,{}},  // ice-face
  {{"Escama de Hielo","Ice Scales","Écailles Glacées","Geloscaglie","冰鳞粉","冰鱗粉"},"Recibe un 40 % menos de daño especial.",1,0,{{15,1,0.6}}},  // ice-scales
  {{"Iluminación","Illuminate","Lumiattirance","Risplendi","发光","發光"},"Atrae los objetos desde más lejos (+10 % de imán).",1,1,{{26,0,1.1}}},  // illuminate
  {{"Ilusión","Illusion","Illusion","Illusione","幻觉","幻覺"},"",0,0,{}},  // illusion
  {{"Inmunidad","Immunity","Vaccin","Immunità","免疫","免疫"},"",0,0,{}},  // immunity
  {{"Impostor","Imposter","Imposteur","Sosia","变身者","變身者"},"",0,0,{}},  // imposter
  {{"Allanamiento","Infiltrator","Infiltration","Intrapasso","穿透","穿透"},"",0,0,{}},  // infiltrator
  {{"Revés","Innards Out","Expuls’Organes","Espellinterno","飞出的内在物","飛出的內在物"},"",0,0,{}},  // innards-out
  {{"Fuerza Mental","Inner Focus","Attention","Forza Interiore","精神力","精神力"},"",0,0,{}},  // inner-focus
  {{"Insomnio","Insomnia","Insomnia","Insonnia","不眠","不眠"},"",0,0,{}},  // insomnia
  {{"Intimidación","Intimidate","Intimidation","Prepotenza","威吓","威嚇"},"Los enemigos le hacen un 12 % menos de daño físico.",1,0,{{15,0,0.88}}},  // intimidate
  {{"Espada Indómita","Intrepid Sword","Lame Indomptable","Spada Indomita","不挠之剑","不撓之劍"},"",0,0,{}},  // intrepid-sword
  {{"Punta Acero","Iron Barbs","Épine de Fer","Spineferrate","铁刺","鐵刺"},"",0,0,{}},  // iron-barbs
  {{"Puño Férreo","Iron Fist","Poing de Fer","Ferropugno","铁拳","鐵拳"},"",0,0,{}},  // iron-fist
  {{"Justiciero","Justified","Cœur Noble","Giustizia","正义之心","正義之心"},"+15 % de daño a los Pokémon de tipo Siniestro.",1,1,{{9,15,1.15}}},  // justified
  {{"Vista Lince","Keen Eye","Regard Vif","Sguardofermo","锐利目光","銳利目光"},"+5 % de probabilidad de golpe crítico.",1,1,{{24,0,0.05}}},  // keen-eye
  {{"Zoquete","Klutz","Maladresse","Impaccio","笨拙","笨拙"},"",0,0,{}},  // klutz
  {{"Defensa Hoja","Leaf Guard","Feuille Garde","Fogliamanto","叶子防守","葉子防守"},"",0,0,{}},  // leaf-guard
  {{"Levitación","Levitate","Lévitation","Levitazione","飘浮","飄浮"},"Flota: no le afectan el agua, la lava ni las trampas, y la Tierra le hace muy poco.",1,0,{{14,8,0.3}}},  // levitate
  {{"Líbero","Libero","Libéro","Libero","自由者","自由者"},"+12 % de daño con todos sus movimientos.",1,0,{{3,0,1.12}}},  // libero
  {{"Metal Liviano","Light Metal","Light Metal","Metalleggero","轻金属","輕金屬"},"",0,0,{}},  // light-metal
  {{"Pararrayos","Lightning Rod","Paratonnerre","Parafulmine","避雷针","避雷針"},"Los ataques de tipo Eléctrico no le hacen daño: le curan un poco.",1,0,{{19,3,0}}},  // lightning-rod
  {{"Flexibilidad","Limber","Échauffement","Scioltezza","柔软","柔軟"},"",0,0,{}},  // limber
  {{"Olor Persistente","Lingering Aroma","Odeur Tenace","Odore Tenace","甩不掉的气味","甩不掉的氣味"},"",0,0,{}},  // lingering-aroma
  {{"Lodo Líquido","Liquid Ooze","Suintement","Melma","污泥浆","污泥漿"},"",0,0,{}},  // liquid-ooze
  {{"Voz Fluida","Liquid Voice","Hydrata-Son","Idrovoce","湿润之声","濕潤之聲"},"",0,0,{}},  // liquid-voice
  {{"Remoto","Long Reach","Longue Portée","Distacco","远隔","遠隔"},"",0,0,{}},  // long-reach
  {{"Espejo Mágico","Magic Bounce","Miroir Magik","Magispecchio","魔法镜","魔法鏡"},"",0,0,{}},  // magic-bounce
  {{"Muro Mágico","Magic Guard","Garde Magik","Magicscudo","魔法防守","魔法防守"},"",0,0,{}},  // magic-guard
  {{"Prestidigitador","Magician","Magicien","Prestigiatore","魔术师","魔術師"},"",0,0,{}},  // magician
  {{"Escudo Magma","Magma Armor","Armumagma","Magmascudo","熔岩铠甲","熔岩鎧甲"},"",0,0,{}},  // magma-armor
  {{"Imán","Magnet Pull","Magnépiège","Magnetismo","磁力","磁力"},"Atrae los objetos desde más lejos (+20 % de imán).",1,1,{{26,0,1.2}}},  // magnet-pull
  {{"Escama Especial","Marvel Scale","Écaille Spéciale","Pelledura","神奇鳞片","神奇鱗片"},"",0,0,{}},  // marvel-scale
  {{"Megadisparador","Mega Launcher","Méga Blaster","Megalancio","超级发射器","超級發射器"},"",0,0,{}},  // mega-launcher
  {{"Ensañamiento","Merciless","Cruauté","Spietatezza","不仁不义","不仁不義"},"",0,0,{}},  // merciless
  {{"Menos","Minus","Moins","Meno","负电","負電"},"+10 % de daño con movimientos especiales.",1,0,{{2,1,1.1}}},  // minus
  {{"Coraza Reflejo","Mirror Armor","Armure Miroir","Blindospecchio","镜甲","鏡甲"},"",0,0,{}},  // mirror-armor
  {{"Nebulogénesis","Misty Surge","Créa-Brume","Nebbiogenesi","薄雾制造者","薄霧製造者"},"",0,0,{}},  // misty-surge
  {{"Rompemoldes","Mold Breaker","Brise Moule","Rompiforma","破格","破格"},"+12 % de daño a los jefes.",1,1,{{7,0,1.12}}},  // mold-breaker
  {{"Veleta","Moody","Lunatique","Altalena","心情不定","心情不定"},"",0,0,{}},  // moody
  {{"Electromotor","Motor Drive","Motorisé","Elettrorapid","电气引擎","電氣引擎"},"Los ataques de tipo Eléctrico no le hacen daño: le curan un poco.",1,0,{{19,3,0}}},  // motor-drive
  {{"Autoestima","Moxie","Impudence","Arroganza","自信过度","自信過度"},"Cada enemigo derrotado le da +0,5 % de daño (hasta +15 %).",1,0,{{33,0,0.005}}},  // moxie
  {{"Multiescamas","Multiscale","Multiécaille","Multisquame","多重鳞片","多重鱗片"},"Con la vida casi llena recibe la mitad de daño.",1,0,{{16,0,0.5}}},  // multiscale
  {{"Multitipo","Multitype","Multi-Type","Multitipo","多属性","多屬性"},"",0,0,{}},  // multitype
  {{"Momia","Mummy","Momie","Mummia","木乃伊","木乃伊"},"",0,0,{}},  // mummy
  {{"Cura Natural","Natural Cure","Médic Nature","Alternacura","自然回复","自然回復"},"Recupera un 0,3 % de su vida por segundo.",1,1,{{22,0,0.003}}},  // natural-cure
  {{"Gas Reactivo","Neutralizing Gas","Gaz Inhibiteur","Gas Reagente","化学变化气体","化學變化氣體"},"",0,0,{}},  // neutralizing-gas
  {{"Indefenso","No Guard","Annule Garde","Nullodifesa","无防守","無防守"},"Todo acierta: +15 % de daño hecho, pero recibe un 10 % más.",2,0,{{3,0,1.15},{13,0,1.1}}},  // no-guard
  {{"Normalidad","Normalize","Normalise","Normalità","一般皮肤","一般皮膚"},"",0,0,{}},  // normalize
  {{"Despiste","Oblivious","Benêt","Indifferenza","迟钝","遲鈍"},"",0,0,{}},  // oblivious
  {{"Latido Oricalco","Orichalcum Pulse","Pouls Orichalque","Ritmo d’Oricalco","绯红脉动","緋紅脈動"},"Pone sol al empezar la partida y cada 3 minutos.",1,0,{{32,1,0}}},  // orichalcum-pulse
  {{"Funda","Overcoat","Envelocape","Copricapo","防尘","防塵"},"Recibe un 5 % menos de daño especial.",1,1,{{15,1,0.95}}},  // overcoat
  {{"Espesura","Overgrow","Engrais","Erbaiuto","茂盛","茂盛"},"+35 % de daño de tipo Planta con poca vida (menos de 1/3).",1,0,{{1,4,1.35}}},  // overgrow
  {{"Ritmo Propio","Own Tempo","Tempo Perso","Mente Locale","我行我素","我行我素"},"",0,0,{}},  // own-tempo
  {{"Cuerpo Mortal","Perish Body","Corps Condamné","Ultimotocco","灭亡之躯","滅亡之軀"},"",0,0,{}},  // perish-body
  {{"Hurto","Pickpocket","Pickpocket","Arraffalesto","顺手牵羊","順手牽羊"},"",0,0,{}},  // pickpocket
  {{"Recogida","Pickup","Ramassage","Raccolta","捡拾","撿拾"},"+15 % de Pokémonedas en la partida.",1,0,{{27,0,1.15}}},  // pickup
  {{"Piel Feérica","Pixilate","Peau Féérique","Pellefolletto","妖精皮肤","妖精皮膚"},"",0,0,{}},  // pixilate
  {{"Más","Plus","Plus","Più","正电","正電"},"+10 % de daño con movimientos especiales.",1,0,{{2,1,1.1}}},  // plus
  {{"Antídoto","Poison Heal","Soin Poison","Velencura","毒疗","毒療"},"",0,0,{}},  // poison-heal
  {{"Punto Tóxico","Poison Point","Point Poison","Velenopunto","毒刺","毒刺"},"",0,0,{}},  // poison-point
  {{"Toque Tóxico","Poison Touch","Toxitouche","Velentocco","毒手","毒手"},"",0,0,{}},  // poison-touch
  {{"Fuente Energía","Power Spot","Cercle d’Énergie","Fonte Energetica","能量点","能量點"},"",0,0,{}},  // power-spot
  {{"Bromista","Prankster","Farceur","Burla","恶作剧之心","惡作劇之心"},"",0,0,{}},  // prankster
  {{"Presión","Pressure","Pression","Pressione","压迫感","壓迫感"},"Recibe un 8 % menos de daño.",1,0,{{13,0,0.92}}},  // pressure
  {{"Armadura Prisma","Prism Armor","Prisme-Armure","Scudoprisma","棱镜装甲","稜鏡裝甲"},"Los ataques muy eficaces le hacen un 25 % menos.",1,0,{{17,0,0.75}}},  // prism-armor
  {{"Hélice Caudal","Propeller Tail","Propulseur","Elicopinna","螺旋尾鳍","螺旋尾鰭"},"",0,0,{}},  // propeller-tail
  {{"Mutatipo","Protean","Protéen","Mutatipo","变幻自如","變幻自如"},"+12 % de daño con todos sus movimientos.",1,0,{{3,0,1.12}}},  // protean
  {{"Paleosíntesis","Protosynthesis","Paléosynthèse","Paleoattivazione","古代活性","古代活性"},"Con sol, +20 % de daño.",1,1,{{10,1,1.2}}},  // protosynthesis
  {{"Psicogénesis","Psychic Surge","Créa-Psy","Psicogenesi","精神制造者","精神製造者"},"",0,0,{}},  // psychic-surge
  {{"Punk Rock","Punk Rock","Punk Rock","Punk Rock","庞克摇滚","龐克搖滾"},"",0,0,{}},  // punk-rock
  {{"Energía Pura","Pure Power","Force Pure","Forzapura","瑜伽之力","瑜伽之力"},"+50 % de daño con movimientos físicos.",1,0,{{2,0,1.5}}},  // pure-power
  {{"Sal Purificadora","Purifying Salt","Sel Purificateur","Sale Purificante","洁净之盐","潔淨之鹽"},"",0,0,{}},  // purifying-salt
  {{"Carga Cuark","Quark Drive","Charge Quantique","Carica Quark","夸克充能","夸克充能"},"",0,0,{}},  // quark-drive
  {{"Regia Presencia","Queenly Majesty","Prestance Royale","Regalità","女王的威严","女王的威嚴"},"",0,0,{}},  // queenly-majesty
  {{"Pies Rápidos","Quick Feet","Pied Véloce","Piedisvelti","飞毛腿","飛毛腿"},"",0,0,{}},  // quick-feet
  {{"Cura Lluvia","Rain Dish","Cuvette","Copripioggia","雨盘","雨盤"},"Con lluvia recupera un 1,5 % de vida por segundo.",1,0,{{23,2,0.015}}},  // rain-dish
  {{"Cobardía","Rattled","Phobique","Paura","胆怯","膽怯"},"",0,0,{}},  // rattled
  {{"Receptor","Receiver","Receveur","Ricezione","接球手","接球手"},"",0,0,{}},  // receiver
  {{"Audaz","Reckless","Téméraire","Temerarietà","舍身","捨身"},"+25 % de daño con las embestidas.",1,0,{{6,12,1.25}}},  // reckless
  {{"Piel Helada","Refrigerate","Peau Gelée","Pellegelo","冰冻皮肤","冰凍皮膚"},"",0,0,{}},  // refrigerate
  {{"Regeneración","Regenerator","Régé-Force","Rigenergia","再生力","再生力"},"Recupera un 0,6 % de su vida por segundo.",1,0,{{22,0,0.006}}},  // regenerator
  {{"Maduración","Ripen","Mûrissement","Maturazione","熟成","熟成"},"",0,0,{}},  // ripen
  {{"Rivalidad","Rivalry","Rivalité","Antagonismo","斗争心","鬥爭心"},"",0,0,{}},  // rivalry
  {{"Sistema Alfa","RKS System","Système Alpha","Sistema Primevo","ＡＲ系统","ＡＲ系統"},"",0,0,{}},  // rks-system
  {{"Cabeza Roca","Rock Head","Tête de Roc","Testadura","坚硬脑袋","堅硬腦袋"},"",0,0,{}},  // rock-head
  {{"Piel Tosca","Rough Skin","Peau Dure","Cartavetro","粗糙皮肤","粗糙皮膚"},"",0,0,{}},  // rough-skin
  {{"Fuga","Run Away","Fuite","Fugafacile","逃跑","逃跑"},"+8 % de velocidad.",1,0,{{20,0,1.08}}},  // run-away
  {{"Poder Arena","Sand Force","Force Sable","Silicoforza","沙之力","沙之力"},"",0,0,{}},  // sand-force
  {{"Ímpetu Arena","Sand Rush","Baigne Sable","Remasabbia","拨沙","撥沙"},"+50 % de velocidad con tormenta de arena.",1,0,{{21,3,1.5}}},  // sand-rush
  {{"Expulsarena","Sand Spit","Expul’Sable","Sputasabbia","吐沙","吐沙"},"",0,0,{}},  // sand-spit
  {{"Chorro Arena","Sand Stream","Sable Volant","Sabbiafiume","扬沙","揚沙"},"Pone una tormenta de arena al empezar la partida y cada 3 minutos.",1,0,{{32,3,0}}},  // sand-stream
  {{"Velo Arena","Sand Veil","Voile Sable","Sabbiavelo","沙隐","沙隱"},"Con tormenta de arena esquiva el 15 % de los golpes.",1,1,{{29,3,0.15}}},  // sand-veil
  {{"Herbívoro","Sap Sipper","Herbivore","Mangiaerba","食草","食草"},"Los ataques de tipo Planta no le hacen daño: le curan un poco.",1,0,{{19,4,0}}},  // sap-sipper
  {{"Banco","Schooling","Banc","Banco","鱼群","魚群"},"Forma banco: +25 % de vida y, con más de 1/4 de vida, +50 % de daño.",2,0,{{31,0,1.25},{12,0,1.5}}},  // schooling
  {{"Intrépido","Scrappy","Querelleur","Nervisaldi","胆量","膽量"},"",0,0,{}},  // scrappy
  {{"Disemillar","Seed Sower","Semencier","Spargisemi","掉出种子","掉出種子"},"",0,0,{}},  // seed-sower
  {{"Dicha","Serene Grace","Sérénité","Leggiadro","天恩","天恩"},"",0,0,{}},  // serene-grace
  {{"Guardia Espectro","Shadow Shield","Spectro-Bouclier","Spettroguardia","幻影防守","幻影防守"},"Con la vida casi llena recibe la mitad de daño.",1,0,{{16,0,0.5}}},  // shadow-shield
  {{"Sombra Trampa","Shadow Tag","Marque Ombre","Pedinombra","踩影","踩影"},"",0,0,{}},  // shadow-tag
  {{"Cortante","Sharpness","Incisif","Affilama","锋锐","鋒銳"},"",0,0,{}},  // sharpness
  {{"Mudar","Shed Skin","Mue","Muta","蜕皮","蛻皮"},"",0,0,{}},  // shed-skin
  {{"Potencia Bruta","Sheer Force","Sans Limite","Forzabruta","强行","強行"},"",0,0,{}},  // sheer-force
  {{"Caparazón","Shell Armor","Coque Armure","Guscioscudo","硬壳盔甲","硬殼盔甲"},"Recibe un 8 % menos de daño.",1,0,{{13,0,0.92}}},  // shell-armor
  {{"Polvo Escudo","Shield Dust","Écran Poudre","Polvoscudo","鳞粉","鱗粉"},"",0,0,{}},  // shield-dust
  {{"Escudo Limitado","Shields Down","Bouclier-Carcan","Scudosoglia","界限盾壳","界限盾殼"},"",0,0,{}},  // shields-down
  {{"Simple","Simple","Simple","Disinvoltura","单纯","單純"},"",0,0,{}},  // simple
  {{"Encadenado","Skill Link","Multi-Coups","Abillegame","连续攻击","連續攻擊"},"",0,0,{}},  // skill-link
  {{"Inicio Lento","Slow Start","Début Calme","Lentoinizio","慢启动","慢啟動"},"",0,0,{}},  // slow-start
  {{"Quitanieves","Slush Rush","Chasse-Neige","Spalaneve","拨雪","撥雪"},"+50 % de velocidad con nieve.",1,0,{{21,4,1.5}}},  // slush-rush
  {{"Francotirador","Sniper","Sniper","Cecchino","狙击手","狙擊手"},"Sus golpes críticos hacen ×2 de daño (en vez de ×1,5).",1,0,{{25,0,2}}},  // sniper
  {{"Manto Níveo","Snow Cloak","Rideau Neige","Mantelneve","雪隐","雪隱"},"Con nieve esquiva el 15 % de los golpes.",1,1,{{29,4,0.15}}},  // snow-cloak
  {{"Nevada","Snow Warning","Alerte Neige","Scendineve","降雪","降雪"},"Pone nieve al empezar la partida y cada 3 minutos.",1,0,{{32,4,0}}},  // snow-warning
  {{"Poder Solar","Solar Power","Force Soleil","Solarpotere","太阳之力","太陽之力"},"",0,0,{}},  // solar-power
  {{"Roca Sólida","Solid Rock","Solide Roc","Solidroccia","坚硬岩石","堅硬岩石"},"Los ataques muy eficaces le hacen un 25 % menos.",1,0,{{17,0,0.75}}},  // solid-rock
  {{"Coránima","Soul-Heart","Animacœur","Cuoreanima","魂心","魂心"},"",0,0,{}},  // soul-heart
  {{"Insonorizar","Soundproof","Anti-Bruit","Antisuono","隔音","隔音"},"Recibe un 10 % menos de daño especial.",1,1,{{15,1,0.9}}},  // soundproof
  {{"Impulso","Speed Boost","Turbo","Acceleratore","加速","加速"},"",0,0,{}},  // speed-boost
  {{"Vigilante","Stakeout","Filature","Sorveglianza","蹲守","監視"},"",0,0,{}},  // stakeout
  {{"Rezagado","Stall","Frein","Rallentatore","慢出","慢出"},"",0,0,{}},  // stall
  {{"Acérrimo","Stalwart","Nerfs d’Acier","Volontà di Ferro","坚毅","堅毅"},"",0,0,{}},  // stalwart
  {{"Firmeza","Stamina","Endurance","Sopportazione","持久力","持久力"},"",0,0,{}},  // stamina
  {{"Cambio Táctico","Stance Change","Déclic Tactique","Accendilotta","战斗切换","戰鬥切換"},"",0,0,{}},  // stance-change
  {{"Electricidad Estática","Static","Statik","Statico","静电","靜電"},"",0,0,{}},  // static
  {{"Impasible","Steadfast","Impassible","Cuordeciso","不屈之心","不屈之心"},"",0,0,{}},  // steadfast
  {{"Acero Templado","Steelworker","Expert Acier","Tempracciaio","钢能力者","鋼能力者"},"+20 % de daño con movimientos de tipo Acero.",1,0,{{0,16,1.2}}},  // steelworker
  {{"Alma Acerada","Steely Spirit","Boost Acier","Spiritoferreo","钢之意志","鋼之意志"},"+20 % de daño con movimientos de tipo Acero.",1,0,{{0,16,1.2}}},  // steely-spirit
  {{"Hedor","Stench","Puanteur","Tanfo","恶臭","惡臭"},"",0,0,{}},  // stench
  {{"Viscosidad","Sticky Hold","Glu","Antifurto","黏着","黏著"},"Atrae los objetos desde más lejos (+20 % de imán).",1,1,{{26,0,1.2}}},  // sticky-hold
  {{"Colector","Storm Drain","Lavabo","Acquascolo","引水","引水"},"Los ataques de tipo Agua no le hacen daño: le curan un poco.",1,0,{{19,2,0}}},  // storm-drain
  {{"Mandíbula Fuerte","Strong Jaw","Prognathe","Ferromascella","强壮之颚","強壯之顎"},"",0,0,{}},  // strong-jaw
  {{"Robustez","Sturdy","Fermeté","Vigore","结实","結實"},"Un golpe que le dejaría KO le deja con 1 de vida (cada 90 s).",1,0,{{34,0,0}}},  // sturdy
  {{"Ventosas","Suction Cups","Ventouse","Ventose","吸盘","吸盤"},"",0,0,{}},  // suction-cups
  {{"Afortunado","Super Luck","Chanceux","Supersorte","超幸运","超幸運"},"+10 % de probabilidad de golpe crítico.",1,0,{{24,0,0.1}}},  // super-luck
  {{"Néctar Dulce","Supersweet Syrup","Nectar Mielleux","Sciroppo Sublime","甘露之蜜","甘露之蜜"},"",0,0,{}},  // supersweet-syrup
  {{"General Supremo","Supreme Overlord","Général Suprême","Generale Supremo","大将","大將"},"",0,0,{}},  // supreme-overlord
  {{"Enjambre","Swarm","Essaim","Aiutinsetto","虫之预感","蟲之預感"},"+35 % de daño de tipo Bicho con poca vida (menos de 1/3).",1,0,{{1,11,1.35}}},  // swarm
  {{"Velo Dulce","Sweet Veil","Gluco-Voile","Dolcevelo","甜幕","甜幕"},"",0,0,{}},  // sweet-veil
  {{"Nado Rápido","Swift Swim","Glissade","Nuotovelox","悠游自如","悠游自如"},"+50 % de velocidad con lluvia.",1,0,{{21,2,1.5}}},  // swift-swim
  {{"Simbiosis","Symbiosis","Symbiose","Simbiosi","共生","共生"},"",0,0,{}},  // symbiosis
  {{"Sincronía","Synchronize","Synchro","Sincronismo","同步","同步"},"",0,0,{}},  // synchronize
  {{"Tumbos","Tangled Feet","Pieds Confus","Intricopiedi","蹒跚","蹣跚"},"",0,0,{}},  // tangled-feet
  {{"Experto","Technician","Technicien","Tecnico","技术高手","技術高手"},"",0,0,{}},  // technician
  {{"Telepatía","Telepathy","Télépathe","Telepatia","心灵感应","心靈感應"},"Lee las intenciones: esquiva el 8 % de los golpes.",1,1,{{28,0,0.08}}},  // telepathy
  {{"Teracambio","Tera Shift","Téramorphose","Teramorfosi","太晶变形","太晶變形"},"",0,0,{}},  // tera-shift
  {{"Terravoltaje","Teravolt","Téra-Voltage","Teravolt","兆级电压","兆級電壓"},"",0,0,{}},  // teravolt
  {{"Termoconversión","Thermal Exchange","Thermodynamique","Termoscambio","热交换","熱交換"},"",0,0,{}},  // thermal-exchange
  {{"Sebo","Thick Fat","Isograisse","Grassospesso","厚脂肪","厚脂肪"},"Recibe un 40 % menos de daño de Fuego y Hielo.",2,0,{{14,1,0.6},{14,5,0.6}}},  // thick-fat
  {{"Cromolente","Tinted Lens","Lentiteintée","Lentifumé","有色眼镜","有色眼鏡"},"",0,0,{}},  // tinted-lens
  {{"Torrente","Torrent","Torrent","Acquaiuto","激流","激流"},"+35 % de daño de tipo Agua con poca vida (menos de 1/3).",1,0,{{1,2,1.35}}},  // torrent
  {{"Garra Dura","Tough Claws","Griffe Dure","Unghiedure","硬爪","硬爪"},"+25 % de daño con ataques cuerpo a cuerpo y embestidas.",2,0,{{6,1,1.25},{6,12,1.25}}},  // tough-claws
  {{"Ímpetu Tóxico","Toxic Boost","Rage Poison","Velenimpeto","中毒激升","中毒激升"},"",0,0,{}},  // toxic-boost
  {{"Cadena Tóxica","Toxic Chain","Chaîne Toxique","Catena Tossica","毒锁链","毒鎖鏈"},"",0,0,{}},  // toxic-chain
  {{"Capa Tóxica","Toxic Debris","Dépôt Toxique","Mantossina","毒满地","毒滿地"},"",0,0,{}},  // toxic-debris
  {{"Calco","Trace","Calque","Traccia","复制","複製"},"",0,0,{}},  // trace
  {{"Transistor","Transistor","Transistor","Transistor","电晶体","電晶體"},"+20 % de daño con movimientos de tipo Eléctrico.",1,0,{{0,3,1.2}}},  // transistor
  {{"Primer Auxilio","Triage","Prioguérison","Primacura","先行治疗","先行治療"},"",0,0,{}},  // triage
  {{"Ausente","Truant","Absentéisme","Pigrone","懒惰","懶惰"},"Golpes sueltos y fuertes: tarda un 60 % más en recargar, pero cada golpe hace +35 %.",2,0,{{30,0,1.6},{3,0,1.35}}},  // truant
  {{"Turbollama","Turboblaze","Turbo Brasier","Piroturbina","涡轮火焰","渦輪火焰"},"",0,0,{}},  // turboblaze
  {{"Ignorante","Unaware","Inconscient","Imprudenza","纯朴","純樸"},"No se deja impresionar: recibe un 8 % menos de daño.",1,1,{{13,0,0.92}}},  // unaware
  {{"Liviano","Unburden","Délestage","Agiltecnica","轻装","輕裝"},"",0,0,{}},  // unburden
  {{"Nerviosismo","Unnerve","Tension","Agitazione","紧张感","緊張感"},"Pone nerviosos a los enemigos: le hacen un 6 % menos de daño.",1,1,{{13,0,0.94}}},  // unnerve
  {{"Puño Invisible","Unseen Fist","Poing Invisible","Pugni Invisibili","无形拳","無形拳"},"",0,0,{}},  // unseen-fist
  {{"Tinovictoria","Victory Star","Victorieux","Vittorstella","胜利之星","勝利之星"},"",0,0,{}},  // victory-star
  {{"Espíritu Vital","Vital Spirit","Esprit Vital","Spiritovivo","干劲","幹勁"},"",0,0,{}},  // vital-spirit
  {{"Absorbe Electricidad","Volt Absorb","Absorbe-Volt","Assorbivolt","蓄电","蓄電"},"Los ataques de tipo Eléctrico no le hacen daño: le curan un poco.",1,0,{{19,3,0}}},  // volt-absorb
  {{"Alma Errante","Wandering Spirit","Âme Vagabonde","Anima Errante","游魂","遊魂"},"",0,0,{}},  // wandering-spirit
  {{"Absorbe Agua","Water Absorb","Absorbe-Eau","Assorbacqua","储水","儲水"},"Los ataques de tipo Agua no le hacen daño: le curan un poco.",1,0,{{19,2,0}}},  // water-absorb
  {{"Pompa","Water Bubble","Aquabulle","Bolladacqua","水泡","水泡"},"+40 % de daño de tipo Agua y recibe la mitad de daño de Fuego.",2,0,{{0,2,1.4},{14,1,0.5}}},  // water-bubble
  {{"Hidrorrefuerzo","Water Compaction","Sable Humide","Idrorinforzo","遇水凝固","遇水凝固"},"",0,0,{}},  // water-compaction
  {{"Velo Agua","Water Veil","Ignifu-Voile","Idrovelo","水幕","水幕"},"",0,0,{}},  // water-veil
  {{"Armadura Frágil","Weak Armor","Armurouillée","Sottilguscio","碎裂铠甲","碎裂鎧甲"},"",0,0,{}},  // weak-armor
  {{"Cuerpo Horneado","Well-Baked Body","Bien Cuit","Bentostato","焦香之躯","焦香之軀"},"Los ataques de tipo Fuego no le hacen daño: le curan un poco.",1,0,{{19,1,0}}},  // well-baked-body
  {{"Humo Blanco","White Smoke","Écran Fumée","Fumochiaro","白色烟雾","白色煙霧"},"",0,0,{}},  // white-smoke
  {{"Huida","Wimp Out","Escampette","Fuggifuggi","跃跃欲逃","躍躍欲逃"},"",0,0,{}},  // wimp-out
  {{"Energía Eólica","Wind Power","Turbine Éolienne","Energia Eolica","风力发电","風力發電"},"",0,0,{}},  // wind-power
  {{"Surcavientos","Wind Rider","Aéroporté","Vento Propizio","乘风","乘風"},"",0,0,{}},  // wind-rider
  {{"Superguarda","Wonder Guard","Garde Mystik","Magidifesa","神奇守护","神奇守護"},"Lo que no es muy eficaz apenas le hace daño (35 %); lo muy eficaz, un 50 % más.",1,0,{{18,0,0}}},  // wonder-guard
  {{"Piel Milagro","Wonder Skin","Peau Miracle","Splendicute","奇迹皮肤","奇跡皮膚"},"",0,0,{}},  // wonder-skin
  {{"Modo Daruma","Zen Mode","Mode Transe","Stato Zen","达摩模式","達摩模式"},"",0,0,{}},  // zen-mode
  {{"Cambio Heroico","Zero to Hero","Supermutation","Supercambio","全能变身","全能變身"},"",0,0,{}},  // zero-to-hero
};
static const char* GENERIC_DESC[NTYPES] = {"+8 % de daño con movimientos de tipo Normal.","+8 % de daño con movimientos de tipo Fuego.","+8 % de daño con movimientos de tipo Agua.","+8 % de daño con movimientos de tipo Eléctrico.","+8 % de daño con movimientos de tipo Planta.","+8 % de daño con movimientos de tipo Hielo.","+8 % de daño con movimientos de tipo Lucha.","+8 % de daño con movimientos de tipo Veneno.","+8 % de daño con movimientos de tipo Tierra.","+8 % de daño con movimientos de tipo Volador.","+8 % de daño con movimientos de tipo Psíquico.","+8 % de daño con movimientos de tipo Bicho.","+8 % de daño con movimientos de tipo Roca.","+8 % de daño con movimientos de tipo Fantasma.","+8 % de daño con movimientos de tipo Dragón.","+8 % de daño con movimientos de tipo Siniestro.","+8 % de daño con movimientos de tipo Acero.","+8 % de daño con movimientos de tipo Hada."};
// [habilidad 1, habilidad 2, oculta]: índice en ABIL + 1 (0 = no tiene)
static const unsigned short DEX_ABIL[DEX_N][3] = {{143,0,23},{143,0,23},{143,0,23},{19,0,204},{19,0,204},{19,0,204},{240,0,167},{240,0,167},{240,0,167},{195,0,178},{192,0,0},{30,0,239},{195,0,178},{192,0,0},{227,0,201},{106,232,18},{106,232,18},{106,232,18},{178,78,87},{178,78,87},{106,0,201},{106,0,201},{101,192,252},{101,192,252},{214,0,112},{214,0,112},{183,0,180},{183,0,180},{151,174,87},{151,174,87},{151,174,193},{151,174,87},{151,174,87},{151,174,193},{36,119,66},{36,119,250},{60,0,48},{60,0,48},{36,29,66},{36,29,67},{99,0,97},{99,0,97},{23,0,178},{23,0,218},{23,0,52},{52,49,37},{52,49,37},{30,239,178},{195,239,269},{183,7,179},{183,7,179},{147,233,252},{113,233,252},{37,25,229},{37,25,229},{255,5,43},{255,5,43},{101,60,105},{101,60,105},{258,37,229},{258,37,229},{258,37,229},{231,99,119},{231,99,119},{231,99,119},{78,138,215},{78,138,215},{78,138,215},{23,0,71},{23,0,71},{23,0,71},{24,115,167},{24,115,167},{176,222,183},{176,222,183},{176,222,183},{178,60,58},{178,60,58},{140,144,172},{140,144,172},{122,222,4},{122,222,4},{106,99,43},{178,50,232},{178,50,232},{238,88,90},{238,88,90},{218,219,152},{218,219,152},{194,198,142},{194,198,142},{109,0,0},{109,0,0},{35,0,0},{176,222,262},{100,65,99},{100,65,99},{89,194,193},{89,194,193},{207,214,2},{207,214,2},{23,0,79},{23,0,79},{176,112,14},{176,112,14},{113,170,251},{106,104,99},{144,140,25},{109,137,218},{109,137,218},{112,176,170},{112,176,170},{136,188,80},{23,108,172},{50,186,99},{229,201,37},{151,201,37},{229,261,112},{229,261,112},{93,136,4},{93,136,4},{207,57,233},{227,233,215},{140,65,49},{214,0,255},{58,0,255},{89,129,132},{101,5,193},{229,0,168},{101,0,132},{258,194,88},{113,0,96},{178,1,6},{258,0,88},{256,0,166},{60,0,78},{245,45,4},{229,194,262},{229,194,262},{229,14,262},{229,14,262},{176,155,252},{95,238,71},{155,0,202},{155,0,214},{155,0,58},{192,0,123},{192,0,123},{99,0,133},{155,0,252},{231,0,0},{143,0,108},{143,0,108},{143,0,108},{19,0,60},{19,0,60},{19,0,60},{240,0,193},{240,0,193},{240,0,193},{178,106,67},{178,106,67},{100,106,239},{100,106,239},{227,50,168},{227,50,104},{227,100,201},{227,100,201},{99,0,97},{256,93,258},{256,93,258},{214,0,112},{36,119,66},{36,29,66},{87,188,224},{87,188,224},{231,50,118},{231,50,118},{214,0,149},{214,0,149},{214,0,149},{23,0,80},{238,85,184},{238,85,184},{222,176,168},{258,37,47},{23,108,97},{23,108,97},{23,108,97},{178,147,198},{23,204,50},{23,204,50},{208,30,67},{37,258,250},{37,258,250},{231,0,118},{231,0,99},{100,224,154},{140,144,172},{109,0,0},{109,0,0},{190,0,234},{99,50,184},{222,0,142},{222,0,142},{188,178,168},{89,183,95},{176,222,193},{101,178,168},{101,166,168},{151,229,101},{227,233,111},{222,71,31},{227,78,132},{99,106,146},{147,166,83},{78,166,252},{121,58,262},{121,58,262},{140,202,238},{140,202,238},{87,136,172},{87,201,130},{223,201,130},{255,87,100},{229,258,261},{106,222,262},{50,60,252},{50,60,252},{229,201,37},{147,0,183},{222,0,183},{245,45,4},{101,67,184},{144,233,130},{78,215,255},{101,233,215},{140,65,88},{214,0,255},{58,0,255},{238,186,184},{136,188,80},{155,0,99},{155,0,99},{155,0,99},{78,0,183},{192,0,0},{182,0,252},{155,0,133},{155,0,172},{136,0,0},{143,0,251},{143,0,251},{143,0,251},{19,0,208},{19,0,208},{19,0,208},{240,0,37},{240,0,37},{240,0,37},{178,166,168},{101,166,132},{147,71,166},{147,71,166},{195,0,178},{192,0,0},{227,0,174},{192,0,0},{195,0,30},{229,167,144},{229,167,144},{229,167,144},{23,50,146},{23,50,146},{23,267,146},{78,0,186},{78,0,186},{106,88,167},{106,47,167},{231,245,234},{231,245,234},{231,245,234},{229,0,167},{101,0,252},{52,150,166},{52,150,233},{248,0,0},{255,0,0},{248,0,0},{30,0,178},{208,0,97},{268,0,0},{207,0,168},{207,0,186},{207,0,186},{238,78,193},{238,78,193},{238,85,184},{222,122,179},{36,139,269},{36,139,269},{106,210,154},{89,101,193},{222,176,82},{222,176,82},{222,176,82},{162,0,234},{162,0,234},{214,112,126},{214,112,126},{149,0,112},{126,0,256},{93,227,154},{140,239,154},{136,151,108},{115,219,71},{115,219,71},{177,0,208},{177,0,208},{261,140,155},{261,140,155},{140,197,144},{121,205,5},{264,48,194},{238,144,71},{238,144,71},{144,232,31},{89,7,193},{109,0,0},{109,0,0},{183,0,258},{183,0,258},{136,0,25},{136,0,25},{95,0,242},{192,0,97},{109,0,0},{109,0,0},{140,6,88},{140,6,88},{89,194,1},{89,194,1},{109,0,0},{109,0,0},{223,0,220},{223,0,220},{14,0,229},{14,0,229},{229,140,1},{123,29,36},{64,0,0},{26,0,158},{100,67,35},{100,67,35},{109,0,67},{155,0,67},{23,204,79},{109,0,0},{155,224,105},{190,0,234},{99,90,130},{99,90,130},{238,90,140},{238,90,140},{238,90,140},{194,0,168},{229,0,261},{229,0,88},{229,176,222},{229,0,88},{176,0,193},{176,0,142},{101,0,132},{24,0,111},{24,0,111},{24,0,111},{24,0,222},{24,0,90},{24,0,111},{109,0,0},{109,0,0},{47,0,0},{48,0,0},{3,0,0},{188,0,0},{155,0,0},{143,0,194},{143,0,194},{143,0,194},{19,0,104},{19,0,104},{19,0,104},{240,0,29},{240,0,29},{240,0,29},{106,0,170},{101,0,170},{101,0,170},{197,250,130},{197,250,130},{192,0,178},{227,0,233},{174,101,78},{174,101,78},{174,101,78},{136,151,108},{136,151,233},{129,0,193},{129,0,193},{222,0,207},{222,0,207},{192,0,142},{6,0,142},{227,0,239},{83,0,87},{155,0,252},{178,147,256},{229,0,261},{229,0,261},{23,0,0},{61,0,0},{219,220,179},{219,220,179},{233,147,198},{2,251,59},{2,251,59},{178,107,113},{36,107,113},{109,0,0},{100,224,132},{113,144,106},{238,144,43},{109,0,0},{218,2,106},{218,2,106},{109,81,82},{109,81,82},{222,176,168},{207,57,233},{136,188,66},{106,232,18},{155,0,97},{183,0,177},{183,0,177},{183,0,177},{147,238,71},{215,99,154},{215,99,105},{182,0,179},{182,0,179},{14,201,106},{14,201,106},{6,49,152},{6,49,152},{109,0,0},{229,220,261},{229,220,261},{229,258,261},{203,0,207},{203,0,207},{155,0,146},{122,222,4},{144,140,25},{112,205,170},{23,108,172},{131,0,255},{58,0,255},{87,188,224},{208,239,67},{108,0,23},{202,0,90},{89,183,150},{140,202,238},{1,45,4},{215,191,105},{222,122,179},{155,0,67},{202,0,35},{109,0,0},{109,0,0},{109,0,0},{109,0,0},{155,0,234},{155,0,234},{60,0,58},{199,0,0},{155,0,234},{109,0,0},{88,0,0},{88,0,0},{11,0,0},{136,0,0},{134,0,0},{254,0,0},{143,0,31},{143,0,31},{143,0,31},{19,0,238},{19,0,238},{19,0,170},{240,0,194},{240,0,194},{240,0,194},{178,106,4},{93,106,4},{255,147,178},{101,180,186},{101,180,186},{113,251,154},{113,251,154},{71,0,143},{71,0,143},{71,0,19},{71,0,240},{65,231,234},{65,231,234},{18,224,174},{18,224,174},{222,262,179},{222,262,179},{222,182,179},{250,107,197},{250,107,197},{180,179,129},{180,179,129},{80,172,107},{78,193,104},{78,193,104},{78,193,104},{229,88,258},{229,88,258},{229,152,258},{222,99,129},{227,23,142},{108,23,142},{227,23,142},{151,227,208},{151,227,208},{151,227,208},{154,97,23},{154,97,23},{23,144,108},{23,144,108},{170,1,129},{101,132,5},{101,132,5},{101,132,5},{87,0,99},{193,0,270},{258,23,220},{222,194,262},{192,132,101},{192,132,101},{269,119,239},{135,0,0},{135,0,0},{42,0,0},{42,0,0},{218,219,2},{218,262,2},{94,0,0},{94,0,0},{36,233,198},{36,233,198},{67,29,190},{67,29,190},{67,29,190},{142,119,172},{142,119,172},{142,119,172},{106,18,88},{106,18,88},{90,202,262},{90,202,262},{90,203,262},{23,184,188},{23,184,188},{214,0,131},{227,192,138},{227,194,142},{52,0,172},{80,88,172},{30,252,227},{30,252,227},{103,0,0},{103,0,6},{149,126,24},{149,126,24},{149,126,24},{109,0,0},{109,0,0},{109,0,0},{234,231,4},{234,231,4},{60,58,97},{60,58,97},{60,58,97},{174,129,252},{174,129,252},{174,129,252},{202,200,168},{202,200,229},{109,0,0},{88,219,251},{99,172,170},{99,172,170},{177,193,129},{104,107,138},{104,107,138},{43,99,155},{43,99,155},{106,193,87},{106,193,43},{18,142,262},{18,142,262},{71,60,264},{227,87,248},{87,0,0},{87,0,0},{109,0,0},{58,0,227},{58,0,227},{105,0,0},{105,0,0},{105,0,0},{154,0,43},{154,0,43},{249,0,0},{236,0,0},{179,0,193},{155,0,0},{105,0,0},{188,0,0},{45,0,0},{143,0,20},{143,0,20},{143,0,20},{19,0,120},{19,0,120},{19,0,120},{240,0,158},{240,0,158},{240,0,158},{147,21,85},{147,21,85},{18,0,70},{58,0,70},{58,0,70},{195,30,66},{192,0,66},{195,30,66},{174,252,132},{62,0,230},{62,0,230},{62,0,230},{184,0,74},{184,0,74},{104,129,186},{104,129,186},{69,0,0},{106,97,144},{106,97,154},{138,0,0},{138,0,0},{213,0,0},{80,0,9},{228,0,251},{228,0,251},{31,223,97},{31,223,97},{241,201,146},{241,201,146},{151,152,1},{151,152,1},{124,0,0},{124,0,0},{49,183,204},{49,183,204},{221,0,222},{221,0,176},{171,0,203},{171,0,203},{36,0,148},{113,251,129},{21,147,149},{24,0,222},{184,88,73},{184,88,73},{184,88,73},{154,0,120},{136,67,79},{136,67,79},{147,67,100},{147,67,100},{144,90,222},{144,90,222},{67,97,234},{67,97,234},{56,0,0},{39,0,0},{10,0,0},{24,0,0},{120,0,0},{258,0,0},{143,0,117},{143,0,117},{143,0,117},{19,0,101},{19,0,101},{19,0,101},{240,0,116},{240,0,116},{240,0,116},{106,198,147},{209,221,1},{227,0,0},{13,0,0},{109,0,0},{89,104,5},{89,104,5},{38,0,0},{83,195,228},{83,195,228},{106,255,215},{106,180,215},{185,0,0},{125,113,172},{125,113,172},{144,212,99},{144,212,99},{259,0,258},{259,0,258},{108,0,31},{108,0,31},{93,52,167},{32,0,140},{32,0,140},{63,107,36},{63,107,252},{108,140,228},{108,140,228},{108,165,228},{62,247,136},{169,0,43},{265,0,0},{55,0,0},{260,0,183},{260,0,183},{98,0,250},{14,0,0},{175,0,0},{196,0,0},{27,0,0},{194,0,0},{103,112,222},{44,0,0},{41,221,269},{17,184,25},{216,0,0},{20,207,142},{20,207,142},{20,207,142},{53,0,234},{160,0,234},{75,0,234},{128,0,234},{250,0,0},{222,0,0},{68,0,0},{189,0,0},{16,0,0},{16,0,0},{16,0,0},{16,0,0},{16,0,0},{16,0,0},{16,0,0},{156,0,0},{206,0,0},{233,0,0},{16,0,0},{16,0,0},{16,0,0},{16,0,0},{256,0,0},{122,0,0},{104,0,0},{143,0,75},{143,0,75},{143,0,75},{19,0,110},{19,0,110},{19,0,110},{240,0,201},{240,0,201},{240,0,201},{21,0,71},{21,0,71},{106,252,18},{106,252,18},{155,252,127},{227,30,234},{227,30,234},{227,67,234},{178,251,209},{178,251,209},{33,172,52},{33,172,52},{63,178,20},{63,215,20},{221,194,229},{221,194,229},{12,0,168},{221,0,29},{173,71,20},{173,71,87},{173,71,238},{181,192,183},{181,192,183},{77,0,0},{229,0,157},{229,0,157},{168,214,107},{161,149,233},{60,264,58},{60,264,58},{113,0,233},{113,0,233},{262,0,35},{262,0,35},{80,6,118},{80,6,118},{80,6,118},{154,67,146},{154,67,146},{154,67,146},{170,78,43},{14,241,217},{262,0,145},{257,0,0},{228,0,9},{228,0,9},{112,0,53},{195,0,92},{195,0,92},{153,0,0},{91,0,0},{99,231,160},{86,0,0},{256,87,180},{256,214,200},{258,221,180},{258,90,200},{111,82,211},{24,97,35},{24,97,35},{24,97,35},{102,0,0},{40,0,0},{155,0,0},{99,0,0},{253,0,0},{246,0,0},{46,0,0},{22,0,0},{76,0,0},{252,0,0},{101,67,184},{227,193,191},{78,20,252},{229,1,129},{155,251,152},{151,229,101},{36,0,31},{143,0,158},{143,0,158},{143,0,158},{19,0,250},{19,0,250},{19,0,250},{240,0,132},{240,0,132},{240,0,132},{9,71,238},{114,71,238},{100,0,209},{100,0,209},{227,0,239},{227,0,239},{214,136,104},{256,136,104},{256,136,104},{178,147,144},{66,21,233},{144,0,107},{263,0,9},{50,0,79},{187,0,79},{163,222,24},{163,222,24},{163,222,24},{60,0,58},{60,0,262},{60,0,262},{144,214,37},{54,214,37},{266,256,29},{266,256,29},{267,0,97},{23,100,107},{23,100,130},{30,0,192},{6,67,208},{129,144,146},{129,144,146},{129,144,146},{73,168,183},{73,168,183},{261,0,0},{271,0,0},{142,0,199},{142,0,57},{192,0,172},{51,0,183},{244,0,32},{244,0,32},{147,0,63},{180,0,63},{238,202,193},{238,200,193},{129,0,191},{250,140,261},{28,0,220},{255,99,43},{151,258,250},{34,8,184},{188,178,168},{43,226,155},{159,0,0},{159,0,0},{159,0,0},{159,0,0},{159,0,0},{164,0,0},{164,0,0},{164,0,0},{164,0,0},{237,0,90},{237,0,90},{237,0,90},{72,0,0},{15,0,0},{159,0,0},{164,0,0},{141,0,0},{159,0,0},{164,0,0},{225,71,219},{84,0,81},{84,0,81},{243,0,67},{243,0,233},{43,0,0},{212,222,211},{225,172,219},{235,0,0},{178,78,87},{178,78,87},{214,0,112},{183,0,180},{183,0,180},{60,0,48},{60,0,48},{183,7,179},{183,7,179},{147,233,252},{147,233,252},{113,233,252},{101,60,105},{101,60,105},{176,222,183},{176,222,183},{176,222,183},{178,60,58},{178,60,58},{140,144,172},{140,144,172},{106,99,43},{218,219,152},{218,219,152},{207,214,2},{207,214,2},{23,0,79},{176,112,14},{109,137,218},{207,57,233},{101,5,193},{101,5,193},{101,5,193},{155,0,202},{155,0,214},{155,0,58},{19,0,60},{37,258,250},{140,144,172},{151,229,101},{99,106,146},{87,136,172},{147,71,166},{147,71,166},{240,0,194},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{23,144,108},{87,0,99},{193,0,270},{0,0,0},{135,0,0},{0,0,0},{0,0,0},{94,0,0},{94,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{106,193,43},{0,0,0},{0,0,0},{184,88,73},{184,88,73},{144,90,222},{143,0,117},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

#define NTM 92
static const short TM_MOVE[NTM] = {76,61,4,80,41,28,33,35,32,51,47,98,94,45,96,73,70,8,67,7,49,17,100,57,9,64,12,65,29,38,16,48,25,3,52,95,97,85,22,23,54,37,83,77,69,43,71,55,60,2,72,20,31,56,82,89,68,59,154,103,152,164,105,150,140,165,153,142,147,107,148,157,163,104,156,160,108,145,162,161,146,106,158,155,159,144,141,143,149,135,134,151};   // índice en MOVES (-1 = no está en la 3DS)
static const short TM_PRICE[NTM] = {540,660,400,750,780,810,660,840,660,780,780,540,780,400,600,660,840,510,600,840,780,750,660,400,870,690,960,1200,840,840,1080,600,630,400,400,1020,840,780,690,840,720,750,660,510,780,780,1020,400,400,400,400,840,400,400,720,540,510,400,630,960,780,400,810,750,900,1800,780,960,750,960,750,780,400,1020,870,400,780,400,400,400,400,780,660,840,900,400,840,960,750,660,780,780};
static const char* TM_ID[NTM] = {"acid-spray","aerial-ace","agility","air-slash","aura-sphere","body-slam","bug-bite","bug-buzz","bulldoze","dark-pulse","dazzling-gleam","disarming-voice","dragon-claw","dragon-dance","draining-kiss","electro-ball","energy-ball","fire-spin","flame-charge","flamethrower","flash-cannon","giga-drain","gyro-ball","hail","heat-wave","hex","hydro-pump","hyper-beam","hyper-voice","ice-beam","leaf-storm","metal-claw","mud-shot","nasty-plot","night-shade","outrage","play-rough","power-gem","psybeam","psychic","psycho-cut","rock-slide","rock-tomb","sand-tomb","seed-bomb","shadow-ball","solar-beam","spikes","substitute","swords-dance","thunder-wave","thunderbolt","toxic","toxic-spikes","u-turn","vacuum-wave","whirlpool","will-o-wisp","acrobatics","blizzard","crunch","double-team","dragon-pulse","drain-punch","earthquake","explosion","extreme-speed","fire-blast","fire-punch","hurricane","ice-punch","lava-plume","light-screen","megahorn","moonblast","protect","psyshock","rain-dance","reflect","rest","sandstorm","scald","silver-wind","sludge-bomb","stone-edge","sunny-day","surf","thunder","thunder-punch","water-pulse","waterfall","x-scissor"};
// bit i = el Pokémon aprende la MT i (dos palabras de 64 bits)
static const unsigned long long TM_MASK[DEX_N][2] = {{2311278995777323041ull,2672896ull},{2311278995777323041ull,2672896ull},{2311278995911541025ull,2672897ull},{8503647155000324128ull,18925592ull},{8503647152852840480ull,18925592ull},{8503717521731236138ull,18991161ull},{7566328853862285344ull,105048128ull},{7566328853862285344ull,105048128ull},{8719256955674165808ull,105048129ull},{0ull,0ull},{0ull,0ull},{2612475361860075656ull,2418720ull},{0ull,0ull},{0ull,0ull},{2613002577685512194ull,137152512ull},{2324138882699886594ull,2156544ull},{2324138882699886594ull,2156544ull},{2324138882834104322ull,2156544ull},{2885998121123315712ull,11053056ull},{2886561071210954752ull,11053056ull},{2324138882699886594ull,2140160ull},{2324138882834104322ull,2140160ull},{3472580981232239105ull,2664449ull},{3472580981366457121ull,2664449ull},{2309502261220395044ull,29419776ull},{2309502261354612772ull,29419776ull},{2306843571241615654ull,137463809ull},{2306843571375833382ull,137463809ull},{4046765740705972256ull,44623872ull},{4046765740705972256ull,44623872ull},{8730559969529168160ull,66709593ull},{2893844236099125280ull,44623872ull},{2893844236099125280ull,44623872ull},{7577638464922321184ull,66710105ull},{12109441437524315168ull,60882264ull},{12109441437658532896ull,60882264ull},{2450239680907510308ull,2148360ull},{2450345251337863716ull,2152456ull},{12109441154060733984ull,60946776ull},{12109441154194951712ull,60946776ull},{3765325956439343116ull,2664448ull},{3765325956573560844ull,2664448ull},{2311278995777323009ull,2673664ull},{11534651032632098817ull,2673664ull},{11534651032766317601ull,2673664ull},{2306757802890100738ull,136890624ull},{2306757803024384002ull,136890624ull},{2319706493632446661ull,2672640ull},{2625951268427858125ull,2934784ull},{2306702831601582372ull,3770369ull},{2306702831735800100ull,3770369ull},{2327569576142832166ull,44083200ull},{2327569576277049894ull,44083200ull},{2990672465673322528ull,105036096ull},{2990672603246493728ull,105036096ull},{11838017319135609120ull,28354641ull},{11874046116288790816ull,28354641ull},{3603161279970017316ull,2148360ull},{8214917667544236326ull,2148364ull},{2954643385186517280ull,105031680ull},{2954643385186517280ull,105031745ull},{12214050816264241440ull,105031745ull},{11530658155079992352ull,18938192ull},{11530659254591620128ull,18938192ull},{11530659263315772448ull,18938192ull},{2306131081260695840ull,18917721ull},{2306131081260695840ull,18917721ull},{2306131081394913568ull,19966297ull},{2311278995777323009ull,2672640ull},{2311278995777323105ull,2672640ull},{2311278995911540833ull,2672640ull},{2968716584301888513ull,105572352ull},{2968716584436106241ull,105572352ull},{2306131085559857440ull,20023323ull},{2306131085559857440ull,20023323ull},{2306131085694075168ull,20023323ull},{2450310109747347492ull,2148360ull},{2450873059834986532ull,2148872ull},{2955804744343879968ull,107149577ull},{12179176789922808096ull,107149641ull},{2309502183916208128ull,10610946ull},{2309502184050425856ull,10610946ull},{2612932208821796908ull,2148352ull},{2594917810295537702ull,2156544ull},{2594917810429755430ull,2156544ull},{2954642831135735840ull,104901120ull},{2954642899989430304ull,104901120ull},{11536293706259234849ull,27895898ull},{11545300905648194081ull,27896922ull},{2963790772173799424ull,104916994ull},{2963790772308017184ull,104917250ull},{2457030831640741377ull,27830354ull},{2466038030895482369ull,27830354ull},{11690535967791318561ull,27830354ull},{6917825895785832736ull,3246083ull},{11535162055355024416ull,18938192ull},{11535162055522796576ull,18938192ull},{2955212382395170852ull,172140544ull},{2955212382596497444ull,172140544ull},{2309502183915159556ull,8448258ull},{2309502184049377284ull,8448258ull},{2306776220783673344ull,2676994ull},{2306776220917891360ull,2676995ull},{2883154784054411552ull,18974745ull},{2883154818548367648ull,20023321ull},{2342722828232556848ull,3188737ull},{11566094865087332660ull,19966033ull},{2957569731223617824ull,65120345ull},{2466037730216772129ull,11053066ull},{2466037730367767073ull,11053066ull},{8650014111197298976ull,11643401ull},{8650014145758363936ull,32615001ull},{12109447673951030560ull,60942681ull},{2306775396284170272ull,2672640ull},{13333300357099946272ull,65120345ull},{7566328883923918852ull,105031680ull},{7566328884058136580ull,105031680ull},{2955205785392513060ull,105032192ull},{2955205785526730788ull,105032192ull},{2958021218064663552ull,113436928ull},{2958022317710509060ull,113441024ull},{11532980332362007584ull,27326800ull},{2648961005958201550ull,136620288ull},{12105994116526063648ull,33618240ull},{2309502733800996896ull,25225552ull},{2450240222173986849ull,18909336ull},{2306694031347810592ull,137406465ull},{2884949221524898080ull,49392137ull},{0ull,0ull},{8722628088384987936ull,116647977ull},{7568581233895024928ull,113306113ull},{0ull,0ull},{2306159668830928928ull,2156544ull},{2954678015910477856ull,107145216ull},{2309537368685707300ull,10545408ull},{2450274857058435104ull,2156680ull},{2886069314635431940ull,10549248ull},{2963797369256149024ull,105113600ull},{4116718873997213728ull,106162176ull},{2954649432510955552ull,106162176ull},{2955213482110222368ull,240379904ull},{8070738604445937924ull,3270697ull},{4037888318586224928ull,65136729ull},{2900599635674398734ull,35776800ull},{2615746958723153926ull,10610976ull},{2756554815823544334ull,2222120ull},{7497648989740343332ull,115403016ull},{7497648989740343332ull,115403016ull},{7497655586826891566ull,133294461ull},{12253563299878765364ull,61995385ull},{18446742974189535231ull,268434299ull},{2306775396149952544ull,2148608ull},{2306775396149952544ull,2148608ull},{2306775430643908896ull,2148609ull},{2450239741003431970ull,2132104ull},{2450239741003431970ull,2132104ull},{2450351908541301026ull,18909337ull},{4108133884913266690ull,105031744ull},{4108133884913266690ull,105031744ull},{8719819937834610982ull,105031745ull},{2902974649644613664ull,65054800ull},{2902974649778831396ull,65054800ull},{2594390895402942478ull,2419744ull},{2594390895537160238ull,2419744ull},{11836374614406070402ull,19188032ull},{11836374614540288130ull,19188032ull},{2319706218788028613ull,136873984ull},{2320269168875667653ull,136873984ull},{3765325956607115788ull,136882208ull},{2958020805734204420ull,113420288ull},{2958020805868422148ull,113420288ull},{2309502261220378656ull,29419776ull},{2307356830835690528ull,35716360ull},{2307356555957783584ull,35711240ull},{2307356564547716128ull,35716360ull},{11530728601553486880ull,35978504ull},{2325370885497685000ull,2423040ull},{2325370885631902728ull,2423040ull},{2309502321349919780ull,10545408ull},{2309502321349919780ull,27322704ull},{6921188374271264036ull,27322704ull},{11534651101485794305ull,2657280ull},{2954642904418634016ull,105032000ull},{2954642904552851744ull,105032000ull},{11529652793564463392ull,20023379ull},{2954643385589170464ull,105031745ull},{2613020170811147266ull,2418944ull},{2613020170811147266ull,2410752ull},{2613020170945364994ull,2418944ull},{2615870116759339014ull,60860496ull},{2306212446196531200ull,2664704ull},{2306775396284171264ull,2664704ull},{2324807935527485642ull,2394112ull},{2959293769616195873ull,106670145ull},{12191673005859930401ull,106670145ull},{2307286530944680992ull,2160896ull},{3464711222862021152ull,2156800ull},{2613530918840697354ull,2140192ull},{12179183524431528224ull,123926873ull},{2453653544637646336ull,10532864ull},{0ull,0ull},{0ull,0ull},{3462459706516243748ull,10549505ull},{2315375775032803808ull,2222339ull},{2316501675074912736ull,3270915ull},{2889452791393681708ull,45197321ull},{3779520649387574022ull,137996289ull},{8070747400526897952ull,3246083ull},{3462529310622483744ull,61401177ull},{3462535942186206496ull,62449753ull},{4122939910678118405ull,105555970ull},{2648961008106733774ull,136685824ull},{2306139881652355360ull,3770369ull},{2342863565855130082ull,3189249ull},{2883183382093627910ull,174123072ull},{3459633199141880098ull,18917457ull},{3459633199276097826ull,19966033ull},{2450246411087642912ull,3262857ull},{2450325576063254816ull,3262859ull},{2882600634488455456ull,1173761ull},{2882600634622673184ull,1173761ull},{2954685299780747552ull,41150723ull},{2955786877414146048ull,107128840ull},{2955786877415260160ull,107653128ull},{3170973942991028270ull,33597504ull},{3242897396685865260ull,105031713ull},{2306843567077720590ull,136415264ull},{3607770342787777056ull,2664456ull},{3607770342921994784ull,2664456ull},{7566328884058136612ull,105031712ull},{2306157542822117664ull,3254273ull},{2306157542960529696ull,3254273ull},{2886069314635431940ull,10532864ull},{2309608561795203364ull,10549505ull},{0ull,0ull},{2342155480232624416ull,2140161ull},{2342155480236818726ull,3254273ull},{2882620979756941344ull,33618240ull},{2309502733666779168ull,25209168ull},{2450240222039769121ull,18909336ull},{2958132749833077024ull,65120337ull},{12109447673951030560ull,60926297ull},{3462458873024118836ull,10742020ull},{3603266730141286692ull,3270796ull},{4107599520248889388ull,107210756ull},{3459061420748972832ull,3254273ull},{3459061420748972834ull,3254273ull},{8650586029243773730ull,66168921ull},{7856846760061173802ull,115472673ull},{2452597575374471210ull,10610985ull},{2325952536929960976ull,36038912ull},{12971305910833053702ull,18909184ull},{13007334707852017670ull,153126912ull},{17619020760773374246ull,153126913ull},{2450809219307143206ull,2131976ull},{2486838016326107174ull,18909208ull},{2793153159865696566ull,19957785ull},{2954649432500469792ull,105031680ull},{2954658228593492256ull,105031745ull},{2954658263087448352ull,106080321ull},{3459081250747187712ull,2140160ull},{3459081250881405472ull,2140160ull},{2958073311910690848ull,48277504ull},{2958073380764385312ull,48277504ull},{0ull,0ull},{0ull,0ull},{2612475361860059266ull,2394112ull},{0ull,0ull},{2616978961487429762ull,2918656ull},{2955293741954435104ull,40019968ull},{12178665783439722528ull,123906128ull},{12178665784647682080ull,123906128ull},{2306247639158554656ull,2140162ull},{2306817186181743136ull,2140162ull},{2495968370715853354ull,136620066ull},{2324138882699886594ull,2140160ull},{2324138882834104322ull,2140160ull},{3260887605796929550ull,105031712ull},{3260905198117191726ull,105031712ull},{2453653381261052960ull,18938192ull},{2453653381395270688ull,18938192ull},{2489682195594169392ull,18939216ull},{3170921445540757700ull,107128832ull},{3188935844184522958ull,107391008ull},{11534088081604935712ull,2664448ull},{11534657634131050786ull,20490240ull},{2884966854378913826ull,195078232ull},{12109464825768706338ull,195078233ull},{12109464825902924066ull,195078233ull},{2306230037308768384ull,136415232ull},{2613037762057601164ull,136677376ull},{2450345225552396420ull,136415232ull},{2882690790415925280ull,52471896ull},{2882697387485692192ull,52471897ull},{4107676520691532064ull,56666201ull},{11565531919428878624ull,24160337ull},{11565531919563096352ull,24160337ull},{2882585241594118176ull,105031936ull},{2309517714513724704ull,28411987ull},{2886068498457427968ull,44083200ull},{2886068498591645696ull,44083200ull},{11674778185905538594ull,186706256ull},{3459721158328861216ull,20555848ull},{2306131081260171552ull,35760129ull},{2306139877353193760ull,36808705ull},{8722713850292998944ull,66168921ull},{11529539144300625954ull,18938192ull},{11565567941453873202ull,18938192ull},{3462423688518336548ull,8431872ull},{3462423688920989732ull,8431872ull},{2309502261220376580ull,25209088ull},{2309502261220376580ull,25209088ull},{2613600780596282602ull,61122880ull},{2615852580409986250ull,61122880ull},{2315958517265138720ull,2664448ull},{2321447283069026337ull,52996178ull},{2321447283203244321ull,52996179ull},{4107564335750971908ull,105031680ull},{4107568733931700996ull,105031681ull},{2954647229459071264ull,105031681ull},{2954647229593288992ull,105031681ull},{2450246273649738016ull,3254409ull},{2450316642528133408ull,3254411ull},{2450316638236311840ull,3770507ull},{2307286547722929184ull,2160896ull},{11530676190051370272ull,18938192ull},{11529538852242849792ull,35694592ull},{3459061386391322976ull,3246081ull},{8088832206448890346ull,3508225ull},{8124861003468517870ull,20285465ull},{11539295378337760032ull,18982912ull},{11539330562844066592ull,18982912ull},{7206111317055245350ull,2141216ull},{7350226539625725222ull,2141225ull},{2886655631358951478ull,199272536ull},{3464130130700927777ull,136882177ull},{3170866886648791328ull,1178883ull},{2739154494562107680ull,3275019ull},{2954649466860216576ull,108242945ull},{2954799000575811872ull,108242945ull},{4108133889208229920ull,239773696ull},{4108133897932382752ull,239773696ull},{2306245980799894784ull,2226435ull},{2306245989524047104ull,3275011ull},{2306781996440944672ull,2721792ull},{2306781996575162656ull,3770369ull},{2306694035508559904ull,169969664ull},{2306694035643826464ull,171018241ull},{7566328853790982144ull,105031936ull},{7566328853992335648ull,105031936ull},{2886068489876471808ull,44279816ull},{12109447132382494722ull,44083208ull},{2453653406795957760ull,10528768ull},{2454216356883596800ull,10528768ull},{3026736176447881728ull,2140160ull},{3026736176582099488ull,18917457ull},{6936475847580786986ull,2402337ull},{2307286393371577344ull,2160896ull},{3030684024630149672ull,179415560ull},{0ull,0ull},{4035682663531544608ull,33597696ull},{4035682663669957408ull,33597699ull},{2954649428146782496ull,104900609ull},{2954649428146782496ull,104900609ull},{4108133882908377376ull,104900609ull},{2882585237039087616ull,105031680ull},{2882589635219816448ull,105031680ull},{2882620971301208064ull,105031680ull},{2954649432643076384ull,106145793ull},{2954642831135752196ull,105031680ull},{8070738638990356512ull,2140168ull},{8070738638990356512ull,2140168ull},{8070738639141351722ull,3188777ull},{0ull,0ull},{2306166817675018534ull,19528003ull},{2306166817675018534ull,20576579ull},{11532889751502717216ull,28411987ull},{2885969533956260128ull,25208899ull},{2309517579356471584ull,27371587ull},{6993351934279252286ull,115472641ull},{6921294340241305918ull,115472641ull},{2958027128060248352ull,113420289ull},{8219014350963740962ull,28412057ull},{8741282402934534442ull,116500525ull},{11550924697135809584ull,60946768ull},{11532987222027469318ull,60881232ull},{3459705701144789280ull,2148608ull},{3459705701144789280ull,2148608ull},{3459712332976947488ull,3262721ull},{2793082799577235460ull,18909208ull},{12016454836432011268ull,18909208ull},{12016525205310406966ull,19957785ull},{2954647229182248966ull,105031680ull},{2954647231329732614ull,105031680ull},{2991241177460640046ull,105031681ull},{2612369258868375566ull,2140192ull},{2612369258868375566ull,2140192ull},{2612369259002593294ull,2140192ull},{2886561071076737024ull,10528768ull},{2886561071210955008ull,115517440ull},{64ull,0ull},{2306687434548576450ull,136620032ull},{3462423757237288960ull,10529024ull},{3462423757237288960ull,10529024ull},{3462423757371506724ull,10529024ull},{2306951318010397696ull,2664448ull},{2315958517399356448ull,2664448ull},{8650014106902331680ull,28420121ull},{8650014141396291872ull,32614425ull},{2884852567447699744ull,11642889ull},{2884852601941655840ull,11659273ull},{0ull,2048ull},{2306230587198865536ull,2140160ull},{2612475361860059266ull,2402304ull},{192ull,0ull},{2626020932828790990ull,137144352ull},{2327534247755153414ull,27306240ull},{4107568733789093892ull,105031744ull},{4107568733923311652ull,105031744ull},{2306775395076228096ull,2131968ull},{2306775463929922560ull,2131968ull},{2954649432500470048ull,106145792ull},{2954798966216065312ull,106670081ull},{2615870116893556742ull,60860496ull},{2741883774361927682ull,10790914ull},{2741883774496145450ull,10790914ull},{11532979843406757892ull,52471888ull},{12415685370505592852ull,60860496ull},{2453653544637646336ull,10532864ull},{2613530918840697354ull,2140192ull},{2326425866885660674ull,44083200ull},{2326425867019878658ull,44083200ull},{2307286118493651968ull,2160896ull},{3472592049394942497ull,2664458ull},{3472592049529291297ull,2664458ull},{2306237321610002720ull,2226433ull},{2306237613801996576ull,2226435ull},{2306280756575469856ull,3246083ull},{11532980332227724288ull,10549504ull},{11530728524092540928ull,35694856ull},{2324138891289821186ull,2140160ull},{2454783704883528224ull,35960832ull},{6918388886536720672ull,3254281ull},{8071310528582521122ull,3254281ull},{8071451266205094178ull,7448585ull},{4037888284092268832ull,65120345ull},{12719016380431597830ull,18917441ull},{17330738133122155318ull,53520453ull},{3459061386255008032ull,36800513ull},{3459061386657661216ull,36800513ull},{3468655720424014468ull,136882176ull},{3468666715674510212ull,136882177ull},{11570070712018272515ull,153659457ull},{11570633662105912067ull,154708033ull},{2306757803024384000ull,2656256ull},{3260887880674837508ull,105293824ull},{3260887880809055244ull,105293824ull},{3242875406319091980ull,105031681ull},{2883236148990246944ull,33597760ull},{2883242780553969952ull,33597761ull},{2883183382227845638ull,174123072ull},{2309502184050425888ull,10610946ull},{2957569731227812128ull,65120347ull},{8650014147906896160ull,32615001ull},{2306781993353937184ull,2672641ull},{2309509330871288096ull,25225553ull},{2452568988070052129ull,18909337ull},{11530728601553486904ull,35978508ull},{3477729440268550346ull,2394112ull},{2306810585219661858ull,136357888ull},{2882620426100408352ull,35694592ull},{3779520649521791750ull,137996289ull},{2882600634622673184ull,1173761ull},{2886069323225367044ull,10532864ull},{11713623779505687870ull,154204497ull},{2309517714647942432ull,28411987ull},{3026742773651866144ull,18917457ull},{4183176118397845536ull,42002752ull},{2453652582430704128ull,10545408ull},{11839225450622698496ull,60946768ull},{12415615834716718080ull,60946768ull},{11839155081876947968ull,60946778ull},{7497655726598787376ull,11642889ull},{7569713318555291954ull,116500489ull},{8214924300853838624ull,3246219ull},{11532880817969692960ull,28354641ull},{7065339159338095408ull,11839489ull},{2309608699771028512ull,10550528ull},{2972657229645220864ull,105032704ull},{2972693238785313792ull,105049344ull},{12251803668956840448ull,145274880ull},{2306776014759463944ull,2131968ull},{7642439965472274365ull,251525421ull},{2471737873520067584ull,27302168ull},{2306775396149952514ull,2148608ull},{2306775396149952514ull,2148608ull},{6918461449071296546ull,2148608ull},{2450314439078838304ull,2131992ull},{11673688674956869920ull,19957784ull},{11673688675091087648ull,20088857ull},{2955205781089157130ull,239249408ull},{2991234578108121098ull,239249408ull},{2991234578242339626ull,239249408ull},{2313478017956970496ull,2140160ull},{2314603917998555136ull,10529024ull},{3462463339924291584ull,2140160ull},{3462463339924291584ull,6334464ull},{3462463340058509312ull,14723072ull},{2325317636742709760ull,2140160ull},{2325318736388555264ull,2140160ull},{2598933226760241152ull,2131968ull},{2598935425917714432ull,2131968ull},{2743048414836817920ull,2131976ull},{3175323610864680960ull,71477248ull},{2307292715299177472ull,64768ull},{2307292715433395200ull,64768ull},{2324138882716663820ull,2140160ull},{2324138882850881548ull,2140192ull},{2306139877354242304ull,1148931ull},{2306140014793195776ull,1148931ull},{2306210383671591168ull,1148931ull},{2613532001011040264ull,63744ull},{2613532001145257992ull,63744ull},{2306702833749065986ull,136939521ull},{2306702833883283746ull,136939521ull},{12109441076881277984ull,31521112ull},{11529503118114947072ull,19966032ull},{11529503118114947072ull,19966032ull},{11529503118249165088ull,19966033ull},{2306124488829304832ull,4892672ull},{2306124488829305088ull,4892672ull},{11529503122888065280ull,4892737ull},{2306131081260171520ull,19966033ull},{2306212445122789568ull,2140416ull},{2306212445122789568ull,2140416ull},{2306775396284170444ull,136374528ull},{2315342789715427332ull,2656256ull},{2315342789715427332ull,2656256ull},{2315912336872833284ull,136874497ull},{2306212445122790400ull,2131968ull},{2324262646613869568ull,2133280ull},{2306212446196531200ull,2131968ull},{2306775396284170240ull,2132224ull},{4107564340171767812ull,105031680ull},{3459061386255008544ull,1673217ull},{3459061386255012642ull,1673217ull},{8070747439176356642ull,1673217ull},{2468331036611313664ull,2131992ull},{2468331586501345568ull,3180569ull},{11529725220808097792ull,2140160ull},{2306913933539148032ull,135366657ull},{17294110641149194753ull,20490320ull},{17294673625596572193ull,20490320ull},{2307357587169936904ull,63744ull},{2459282614272459264ull,43008ull},{2459282614406676992ull,43008ull},{8376983378972381444ull,1148929ull},{8376983413466337548ull,1148929ull},{11538662049976418816ull,2664450ull},{11540984768424313376ull,2664450ull},{2324737043097190916ull,2664448ull},{3482162697221964326ull,2664448ull},{2327534243594372096ull,2140160ull},{2327534243728589824ull,10529024ull},{2309544798576509440ull,63744ull},{2309544798576509440ull,63744ull},{2309544798710727200ull,63744ull},{2307293007358001152ull,10549506ull},{2307293007358001152ull,10549506ull},{11530665044346994720ull,27326802ull},{2378182078765205514ull,37922848ull},{2666412455118243850ull,37922848ull},{2882585237308571648ull,43266ull},{2882585237308571648ull,43266ull},{2882585237442789376ull,43266ull},{2307373599194939684ull,2140416ull},{2307936549282578724ull,2140416ull},{2615817327316402188ull,8431872ull},{2306687434145988736ull,134261248ull},{2306687434280206468ull,134261248ull},{2310716045823901728ull,2664448ull},{3242909010269044768ull,105031936ull},{2309502183913128132ull,142649600ull},{2309502184047345860ull,142649600ull},{2309730882336915456ull,2131970ull},{2310293832424554752ull,10586114ull},{2309502321485152256ull,100352ull},{2309502321485152256ull,100352ull},{2309502321485152256ull,8488960ull},{1125899906842624ull,0ull},{3768668463182151713ull,8431872ull},{17603733150062121249ull,27306256ull},{2309544523698602500ull,63744ull},{2309544523833868804ull,63744ull},{2450345792369525248ull,2131976ull},{2450345792369525248ull,2131976ull},{2450345792503742976ull,2131976ull},{8071299389584322818ull,140552192ull},{8071299389584322818ull,140552192ull},{8071301588741796130ull,140552193ull},{4035513413869240610ull,172009536ull},{4036076363956879650ull,173058113ull},{3170885982061854752ull,33614082ull},{11556658860729106596ull,632832ull},{11836308643706306582ull,3205120ull},{11872337440859488278ull,3205120ull},{8070738638806717216ull,23635985ull},{11529538869997338912ull,18999377ull},{11531861038690468128ull,20047953ull},{2307817734245712394ull,135374848ull},{2307817734379930122ull,135374848ull},{2612375855938142254ull,2140192ull},{2612375858219843630ull,2140192ull},{2328682073352569352ull,2140160ull},{2616912449638498826ull,2205728ull},{11673686475931254816ull,18917400ull},{3460178485774974980ull,135366656ull},{8071857950349591072ull,2140160ull},{8071857950349591072ull,2140160ull},{8378109322300367648ull,7399433ull},{2756555365447237856ull,2132232ull},{2756555365581455592ull,2140456ull},{2343842133352382522ull,137488896ull},{2306694031347810618ull,135383553ull},{2342804193303134266ull,137415424ull},{3765291321955189292ull,2730016ull},{3768669021660021284ull,27830272ull},{8214959930022440992ull,3205384ull},{8074152072906321952ull,28371200ull},{3477639327557615904ull,3778563ull},{7494313621419208738ull,3205376ull},{2342716231364116506ull,175303168ull},{11839718023508331520ull,28358992ull},{2904048253898654336ull,142657794ull},{11529731824051880226ull,20506624ull},{11529731824056074530ull,20506624ull},{12683216278750564642ull,20506625ull},{2450310869956820996ull,2144520ull},{2450310869956820996ull,18921752ull},{2450346080534922244ull,18938136ull},{3197984549866831874ull,105031680ull},{3198547499820253186ull,105031744ull},{3198547499954471426ull,105031744ull},{2324849171506397444ull,5867521ull},{2324857967733637412ull,22644817ull},{2612932208822059022ull,2140192ull},{2757047396898570254ull,2140200ull},{2757117765776965646ull,2140200ull},{64ull,0ull},{64ull,2048ull},{2612440452365893832ull,2140448ull},{3891461922055127328ull,2140168ull},{2306212994878622720ull,2141440ull},{2306212994878622720ull,2141440ull},{2306212995012840448ull,2141440ull},{2306214718234231072ull,6334464ull},{2306214718368448802ull,6334465ull},{12682987572943651616ull,24684624ull},{12682987607437611808ull,158902353ull},{2329768382234100224ull,6334464ull},{2309538270226221568ull,2160896ull},{2309538270360439296ull,2160896ull},{2306690732683952128ull,59392ull},{2306690732683952128ull,59392ull},{2306725917190258696ull,2156544ull},{2308376842355164160ull,2157824ull},{2308376902479987712ull,6334720ull},{11531748939468981248ull,14723328ull},{2308379316251525634ull,2160896ull},{2308379316385743362ull,2160896ull},{2883154788348854528ull,140224513ull},{2955212382521004288ull,140224513ull},{7005665987164897281ull,105555968ull},{7005665987299115009ull,113944576ull},{7512850807307371024ull,105555968ull},{7512885991813677616ull,105555968ull},{2327523179490214660ull,12691712ull},{6939279567064433412ull,31566096ull},{8070738707642069792ull,3246081ull},{8070738707776287520ull,3246081ull},{2885969572887790368ull,1173760ull},{2885970122643604256ull,9562369ull},{2306160287440456736ull,2161920ull},{11836310842863779878ull,154183696ull},{2327534243460203524ull,27306240ull},{2306281302175777824ull,3271938ull},{6920064540109439008ull,36218880ull},{7501028892577103905ull,44607488ull},{7501028892778959137ull,65710105ull},{2307391740196176896ull,2226432ull},{2450365583563227904ull,2156544ull},{11678241221253333760ull,136374273ull},{2450365566388077056ull,2656522ull},{2450365575112229376ull,2657546ull},{4035513338711507232ull,5285888ull},{4035513338913882400ull,5285889ull},{7224161414796022286ull,136349728ull},{7224161414930772526ull,169904160ull},{2309505036181324832ull,10551040ull},{2612407192422191656ull,2140192ull},{8070734241010295072ull,3246085ull},{2306281370895271200ull,3276034ull},{11532914636542247424ull,19003728ull},{2450316642599436576ull,37464075ull},{2306775421919756298ull,2140416ull},{2306775421919756298ull,2140416ull},{2613059779167322138ull,2140448ull},{3909968944455090208ull,2131976ull},{3909968944455090208ull,2131976ull},{13133340981444084514ull,18909209ull},{3242873276275378176ull,105032704ull},{3242873276275378208ull,105032704ull},{3242909010537565216ull,105049344ull},{2612932209090494474ull,2131968ull},{3477082381834256640ull,2205697ull},{3750654068964458560ull,134260992ull},{3750654068964491328ull,142649600ull},{3750724437844001228ull,142649600ull},{11529503122409914656ull,20097089ull},{12105963875384426784ull,20097089ull},{2612932208805019662ull,2205728ull},{2612369877326972096ull,2148608ull},{2612440246205367492ull,2148608ull},{3459615604808352032ull,1148928ull},{3459615604808352036ull,3246080ull},{2396196481645150464ull,71477249ull},{2896096040274886657ull,38447104ull},{2896096040442658849ull,38447360ull},{2306139877353193760ull,3246081ull},{2306139881782378784ull,3246081ull},{4035506741706752192ull,239249408ull},{4035506741840969952ull,239265792ull},{2306775396149952576ull,136349696ull},{2306775396284170304ull,136357888ull},{2307338345029649408ull,2657536ull},{7076562398089842693ull,2656264ull},{7364792774644215845ull,2656264ull},{2306694031213592832ull,16812097ull},{11530066068202590496ull,16812097ull},{2306212514916025344ull,2148608ull},{2306212514916025344ull,2148608ull},{2612457289711436800ull,2148608ull},{2612457288637697024ull,2132224ull},{11871829466491715872ull,2140161ull},{2306265225982115968ull,71477248ull},{2883295525979816576ull,206219264ull},{2306175632992698624ull,3778561ull},{2306175633126916384ull,3778561ull},{2306124484198793216ull,59648ull},{2325829931726016520ull,136423424ull},{3481038455702032392ull,140617730ull},{2612446911998723328ull,1165571ull},{2612956469062009120ull,2107393ull},{7062000492265214240ull,3180555ull},{2327516582558859268ull,8439808ull},{11677588178992121344ull,144746752ull},{4108127835586035716ull,105052416ull},{7497756810884493568ull,14723369ull},{2378852780563562752ull,6334465ull},{6918380084000731424ull,134318081ull},{16177780920021954850ull,136415233ull},{16177780920426180914ull,153200721ull},{2615746958974813188ull,25225472ull},{2308413186497397760ull,10542336ull},{938983066502144ull,3197696ull},{2954678084361536512ull,71494976ull},{0ull,0ull},{0ull,0ull},{3461375341096730916ull,11589897ull},{3317288721308451854ull,10550528ull},{2318516667463762976ull,9033984ull},{11529503152478880032ull,17860673ull},{2900599670034137220ull,34816ull},{2309572552789427200ull,27322624ull},{2594445020437741864ull,1083915ull},{2306688533657550856ull,134252544ull},{17294110675664638752ull,1607689ull},{6918451142511829794ull,137484545ull},{2309749368545201204ull,2152706ull},{11961883901242114068ull,17860688ull},{4620974701248774144ull,559104ull},{7235455056970527240ull,134776840ull},{288072051720480ull,1165569ull},{2450345775289991680ull,2136346ull},{11821104700130885652ull,25200656ull},{3659174702481408ull,34816ull},{3736141187514400ull,25200705ull},{9530549198452228128ull,2131968ull},{9530549198452228128ull,2131968ull},{9530549203149848864ull,2131969ull},{306526249655631876ull,2131976ull},{307089203904020484ull,2131976ull},{451239576486182916ull,2131992ull},{90353471886196736ull,104917248ull},{90353471886196736ull,104917248ull},{991671532356895244ull,105048320ull},{1153220576337199136ull,34816ull},{1153783526424838432ull,2140161ull},{18295882076127246ull,34816ull},{18295882076127246ull,2132000ull},{18295884358877230ull,2156832ull},{0ull,0ull},{387577848856704ull,55552ull},{18403076006281348ull,55552ull},{281556581089284ull,34816ull},{1459483570111250948ull,34816ull},{351845065228288ull,2132224ull},{369437385490432ull,2132224ull},{1407374883586052ull,34816ull},{1970324971225124ull,34816ull},{1225260577983561760ull,104900608ull},{1802299674074284320ull,106146305ull},{1156580748023595008ull,8423424ull},{1156580748426248196ull,8423424ull},{0ull,0ull},{4918300264565383179ull,2131968ull},{4612055489908375840ull,2156801ull},{296872434467104ull,1148929ull},{296906928423200ull,1148961ull},{937030198207971342ull,37922848ull},{1225260573688594436ull,105031680ull},{1801721326663106564ull,105031680ull},{281474976710656ull,34816ull},{9240542010870366209ull,27830288ull},{1153202979600466048ull,2263040ull},{1297388536555241600ull,136480776ull},{281479271677984ull,67143744ull},{9295711110365708320ull,71338048ull},{144432697863832064ull,38912ull},{144432697998049792ull,55552ull},{1408268238867968ull,55552ull},{1408268238867968ull,55552ull},{2006402698595844ull,55552ull},{9224779489047758336ull,51456ull},{9224779489047758336ull,51456ull},{10377700993788823072ull,16828752ull},{652230302831214624ull,165718096ull},{1174084984282022432ull,144746496ull},{792957478812778784ull,7596289ull},{4765141016783160064ull,1157121ull},{281474976728064ull,34816ull},{9223724499187354624ull,39168ull},{12807111675248672ull,12756992ull},{281474976710848ull,34816ull},{882987071333991624ull,51488ull},{297005712671008ull,3246081ull},{648799822056259620ull,104917056ull},{9223689589825293344ull,38912ull},{1156598314439836164ull,25200640ull},{4615351824689041696ull,28354569ull},{580126525085483296ull,30451712ull},{5836953223679705376ull,72525825ull},{1801727923741261856ull,72394752ull},{4615985145538679328ull,9488640ull},{1407374883553280ull,34816ull},{5065740391874568196ull,14862600ull},{5065810760752967716ull,14862600ull},{1153766000807642156ull,35840ull},{1153273419598398500ull,3271936ull},{4625583879898144804ull,2681096ull},{307089201738809378ull,16812112ull},{10683389340270199346ull,17860688ull},{291889550983200804ull,8448260ull},{5764889032504913952ull,51457ull},{1730226721166197024ull,35328ull},{1297353932019876644ull,34816ull},{370266045759492ull,2152704ull},{3765552581509412ull,10549505ull},{343124593814274254ull,137464064ull},{10413191023936143650ull,19966033ull},{1801756566903324676ull,104900608ull},{356670587805892615ull,136882192ull},{1743913407620317700ull,71870464ull},{282127945976868ull,2665472ull},{306614288953444356ull,34816ull},{306614288953444358ull,16812032ull},{315797547641801238ull,16812032ull},{1297335794491328544ull,2131976ull},{1297335794491328544ull,2131976ull},{1297441364955236384ull,2131977ull},{360287970256750602ull,4237312ull},{360287970256750602ull,37791744ull},{379146793830582286ull,37791776ull},{299140445636896ull,2140160ull},{299140579920160ull,2140160ull},{9429411721904352ull,136357888ull},{27448208277897442ull,136357888ull},{18295873486192836ull,136357888ull},{18858823439614662ull,136357888ull},{1156580750171078660ull,10528768ull},{1156580750171078660ull,27305984ull},{1156602740537851908ull,27306064ull},{1172360943468806150ull,35694592ull},{1172360943603023878ull,35694592ull},{1153203052598002724ull,2140160ull},{1153203052732236836ull,2140160ull},{369436982837248ull,2131968ull},{369437385491456ull,2148608ull},{283815734935840ull,3254273ull},{283815869153568ull,3254273ull},{288213915664672ull,20031569ull},{144396680250130432ull,2099336ull},{4756189076428620305ull,2152840ull},{181023611628163072ull,136366472ull},{3659179260674049ull,42002688ull},{8162779022262273ull,42002688ull},{309903949358465038ull,8423456ull},{309903949492682766ull,8423456ull},{545376056705024ull,34816ull},{1153290941589684224ull,2197504ull},{1297406129800282112ull,2197512ull},{285877318189248ull,134776832ull},{18314290305959940ull,2226432ull},{1976992774766592ull,1100032ull},{1976992774766592ull,1100032ull},{1976992774766848ull,1100032ull},{648799826217009412ull,37857280ull},{648799826351227140ull,37857280ull},{864972604035844132ull,104900608ull},{10160402269690939444ull,104900672ull},{13792273864065313ull,2697216ull},{13792273998283041ull,2729984ull},{6073385611543187494ull,2140160ull},{437610058088736ull,100353ull},{13948546243888129ull,3795200ull},{14018915123397633ull,3795200ull},{1153238254183514368ull,2205696ull},{1297353442393587968ull,2205696ull},{576742296939135264ull,33597441ull},{576742296939135264ull,33597505ull},{1729664282380992548ull,104900608ull},{1153205213167878432ull,104900609ull},{4684025130593034240ull,37791744ull},{9568238308627054880ull,28354641ull},{13939612913238305ull,106539009ull},{1156616714482418980ull,10549505ull},{583609816539726124ull,11642921ull},{1974725166236170ull,135374848ull},{288145196187936ull,3250177ull},{10956418760806237216ull,60946776ull},{3694789002350080ull,10525696ull},{450641437867114722ull,2205729ull},{3808850147836192ull,10602753ull},{955044665436930084ull,33597504ull},{9226474927522054432ull,25200721ull},{320107967173035149ull,2132264ull},{1733760652470169888ull,28420185ull},{6341912735164403744ull,43008ull},{6341912735164403746ull,43008ull},{6341912735298629922ull,43009ull},{3695072202753024ull,25286912ull},{1297318726190629376ull,2148744ull},{6071136008689824298ull,137398313ull},{9263658967966483478ull,151051600ull},{15295139167031136548ull,2131976ull},{5836946630905442340ull,107128864ull},{914794884431886ull,134252544ull},{4612055489908375648ull,2148352ull},{387054972239872ull,182272ull},{387055106457600ull,182272ull},{22835508056948737ull,563456ull},{311628061084749327ull,560416ull},{19091989700083712ull,2205696ull},{4615985145538679344ull,9488641ull},{4612055498565419104ull,2156545ull},{5771717103335311024ull,49326081ull},{2905138419539640832ull,2664448ull},{2905701369627279872ull,2664448ull},{2314006410737795108ull,29423872ull},{2887658385842372898ull,136349761ull},{2887799123464945958ull,136349761ull},{2887088914009443876ull,59392ull},{2887159282887839268ull,63488ull},{2311206433377485094ull,3770369ull},{2311206433511702822ull,3770369ull},{2332073175770202662ull,10528768ull},{1174084984148853282ull,144746496ull},{2332073175904420390ull,10528768ull},{1297324936545566756ull,3246088ull},{5909081324119785766ull,3246088ull},{2314012384907755808ull,28411931ull},{2314012384907755808ull,28411931ull},{2314012385041973536ull,28411931ull},{282093452002340ull,34816ull},{846143051269156ull,35328ull},{649961735138574624ull,107133193ull},{9877837517783826721ull,107723081ull},{844424930132000ull,2131968ull},{12689215211000300065ull,28944474ull},{12689215211000300065ull,28944474ull},{3747136707592196ull,8448000ull},{3747136841809924ull,8448000ull},{6922965873332912416ull,2676995ull},{3034060590488093474ull,28420121ull},{160194789873550881ull,11053064ull},{9803598075996996640ull,10549568ull},{72345700645470496ull,38905857ull},{144403294617207072ull,3254281ull},{288106540433696ull,7448577ull},{18332982406283276ull,2160928ull},{306526249772122118ull,2205984ull},{306561443036135950ull,2205728ull},{144504501281095970ull,18909209ull},{13939612779020577ull,106539009ull},{9886844717072122145ull,124434777ull},{1743913407519654405ull,105424896ull},{50419215940714503ull,136882176ull},{792957478678561056ull,7596289ull},{652230302696996896ull,14723072ull},{652230302831214624ull,14723072ull},{685391569028645674ull,239118336ull},{2743050613994291200ull,2131976ull},{3175325810022154240ull,71477248ull},{2328642482344034318ull,2140160ull},{2314005783538597924ull,10529024ull},{2314005783672815908ull,10529024ull},{2310634680887542048ull,19966033ull},{325191560241152010ull,2140192ull},{738948780237914112ull,2132056ull},{738949330127946016ull,3180633ull},{2311417533300736258ull,135366657ull},{153446202128531968ull,108545ull},{4112074536734687520ull,72591361ull},{4112074536868905248ull,72591361ull},{162446271871713796ull,567296ull},{1315931276456755750ull,567296ull},{2310716045991673888ull,2664448ull},{3103297353010972160ull,72001536ull},{3103297353145189888ull,72001536ull},{2319776024858001568ull,567296ull},{2314012384903037184ull,14395393ull},{1154335480856183040ull,6006785ull},{2311197669495669026ull,7383553ull},{342597672479228974ull,2144288ull},{3895965521816716064ull,2140168ull},{11536252478971528192ull,10550528ull},{5190686681787793441ull,44673024ull},{5190686681989648673ull,65644569ull},{1729670329632031008ull,1157121ull},{18951209396273178ull,2140416ull},{2617435808717864970ull,2131968ull},{2617453401039175690ull,2132000ull},{3481585981595844896ull,18982993ull},{11535213981646013440ull,2665728ull},{2312918100653179168ull,10549505ull},{144552931146858784ull,1165312ull},{144552931164553504ull,3393544ull},{144623300042948896ull,3393561ull},{844424930132000ull,2131968ull},{9803598075996996640ull,10549568ull},{851022134116388ull,2140672ull},{288145061970208ull,1148929ull},{288179555926304ull,1148929ull},{10683477313416397346ull,2131968ull},{369436982837248ull,2131968ull},{18295873905623050ull,2132000ull},{1153203048303034912ull,2140160ull},{1153203083065426464ull,2140160ull},{311592812103598081ull,2664448ull},{311592812103598081ull,136882176ull},{545376190922752ull,34816ull},{14020977682875393ull,583936ull},{14020977817093121ull,583936ull},{851166015521056ull,137472000ull},{322023897269440ull,136968448ull},{18349492295240742ull,2226432ull},{306532993155990026ull,3221536ull},{307089199725543438ull,33589280ull},{1153290976117195296ull,2131968ull},{288076480938272ull,9537537ull},{6071138205566501416ull,2140200ull},{316822591111168ull,51456ull},{369441445577248ull,2156800ull},{2018457058159886850ull,43008ull},{437610090595104ull,3246081ull},{6075144963024262180ull,8440064ull},{10381083050753654816ull,17336400ull},{5764889032522608928ull,3180681ull},{5768337101238075424ull,10520577ull},{849372866674990ull,135370753ull},{844976968696108ull,134256640ull},{4820284779528193ull,559104ull}};
