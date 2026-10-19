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

enum { NK_ = 25 };
enum { K_CD=0,K_DMG=1,K_SPEED=2,K_COUNT=3,K_SPREAD=4,K_PIERCE=5,K_LIFE=6,K_SIZE=7,K_RADIUS=8,K_ARC=9,K_KNOCK=10,K_WIDTH=11,K_DUR=12,K_RATE=13,K_RANGE=14,K_AMOUNT=15,K_STACKS=16,K_CHARGE=17,K_PULL=18,K_BOUNCE=19,K_SLOW=20,K_STUN=21,K_HOMING=22,K_BURN=23,K_POISON=24 };
enum { MK_PROJECTILE=0,MK_MELEE=1,MK_BEAM=2,MK_ORBIT=3,MK_NOVA=4,MK_AURA=5,MK_BUFF=6,MK_BOOMERANG=7,MK_CHAIN=8,MK_MINE=9,MK_METEOR=10,MK_TURRET=11,MK_DASH=12,MK_TRAIL=13,MK_CONE=14,MK_HOMING=15,MK_BOUNCE=16,MK_CHARGE=17,MK_SPIN=18,MK_QUAKE=19,MK_VORTEX=20,MK_SHOVE=21,MK_STUN=22 };
enum { ST_ATK=0,ST_PATK=1,ST_SATK=2,ST_SPD=3,ST_DEF=4,ST_REGEN=5 };
struct UpMod { unsigned char key, op; float v; };   // op 0 ×, 1 +, 2 =
struct MoveUp { UpMod m[4]; unsigned char n; const char* text; };
struct MoveDef { const char* name; const char* desc; unsigned char type, kind, cat, stat; float v[NK_]; MoveUp ups[4]; };
#define NMOVES 103
static const MoveDef MOVES[NMOVES] = {
  {"Placaje","Embiste en arco a todo lo que tengas delante.",0,1,0,0,{0.5,16,0,0,0,0,0,0,60,2.13,90,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // tackle
  {"Ataque Rápido","Cruzas como un rayo hacia el enemigo y golpeas todo el camino.",0,12,0,0,{0.75,20,0,0,0,0,0,0,110,0,40,34,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% distancia"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.6},{11,0,1.4}},2,"+60% daño y más ancho"}}},  // quick-attack
  {"Danza Espada","No hace daño: acumula ATAQUE (físico) mientras esté activo.",0,6,2,1,{0.85,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0.13,5,0,0,0,0,0,0,0,0},{{{{16,1,1}},1,"+1 acumulación máxima"},{{{15,0,1.4}},1,"+40% potencia"},{{{12,0,1.5}},1,"+50% duración"},{{{16,1,1},{15,0,1.4}},2,"+1 acumulación y +40% potencia"}}},  // swords-dance
  {"Maquinación","No hace daño: acumula ATAQUE ESPECIAL mientras esté activo.",0,6,2,2,{0.85,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0.13,5,0,0,0,0,0,0,0,0},{{{{16,1,1}},1,"+1 acumulación máxima"},{{{15,0,1.4}},1,"+40% potencia"},{{{12,0,1.5}},1,"+50% duración"},{{{16,1,1},{15,0,1.4}},2,"+1 acumulación y +40% potencia"}}},  // nasty-plot
  {"Agilidad","No hace daño: acumula VELOCIDAD mientras esté activo.",0,6,2,3,{0.85,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0.1,5,0,0,0,0,0,0,0,0},{{{{16,1,1}},1,"+1 acumulación máxima"},{{{15,0,1.4}},1,"+40% potencia"},{{{12,0,1.5}},1,"+50% duración"},{{{16,1,1},{15,0,1.4}},2,"+1 acumulación y +40% potencia"}}},  // agility
  {"Fortaleza","No hace daño: acumula DEFENSA mientras esté activo.",0,6,2,4,{0.85,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0.07,5,0,0,0,0,0,0,0,0},{{{{16,1,1}},1,"+1 acumulación máxima"},{{{15,0,1.4}},1,"+40% potencia"},{{{12,0,1.5}},1,"+50% duración"},{{{16,1,1},{15,0,1.4}},2,"+1 acumulación y +40% potencia"}}},  // harden
  {"Ascuas","Bola de fuego al enemigo más cercano.",1,0,1,0,{0.52,18,310,1,0.12,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // ember
  {"Lanzallamas","Chorro de llamas en abanico corto que quema.",1,14,1,0,{0.7,7,380,7,0,1,0.42,6,0,0.9,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},{{{{3,1,3}},1,"+3 disparos"},{{{1,0,1.4}},1,"+40% daño"},{{{6,0,1.3}},1,"+30% alcance"},{{{3,1,3},{5,1,1}},2,"+3 disparos y +1 perforación"}}},  // flamethrower
  {"Giro Fuego","Llamas que giran a tu alrededor. Defensa constante.",1,3,1,0,{0.3,14,2.4,3,0,0,0,9,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},{{{{3,1,1}},1,"+1 orbe"},{{{1,0,1.55}},1,"+55% daño"},{{{8,0,1.25},{2,0,1.35}},2,"+25% radio y gira más rápido"},{{{3,1,1},{1,0,1.55}},2,"+1 orbe y +55% daño"}}},  // fire-spin
  {"Onda Ígnea","Explota en llamas en todas las direcciones.",1,4,1,0,{1.25,13,250,10,0,1,1.1,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},{{{{3,1,4}},1,"+4 proyectiles"},{{{1,0,1.4}},1,"+40% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,4},{5,1,1}},2,"+4 proyectiles y +1 perforación"}}},  // heat-wave
  {"Pistola Agua","Chorro perforante. Fiable a cualquier distancia.",2,0,1,0,{0.44,14,350,1,0.1,1,1.5,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // water-gun
  {"Burbuja","Burbujas en abanico que ralentizan a quien tocan.",2,4,1,0,{1,9,210,8,0,0,1.3,8,0,0,0,0,0,0,0,0,0,0,0,0,0.45,0,0,0,0},{{{{3,1,4}},1,"+4 proyectiles"},{{{1,0,1.4}},1,"+40% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,4},{5,1,1}},2,"+4 proyectiles y +1 perforación"}}},  // bubble
  {"Hidrobomba","Cañonazo de agua lento pero devastador.",2,2,1,0,{1.5,29,0,0,0,0,0,0,250,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // hydro-pump
  {"Acua Aro","No hace daño: acumula REGENERACIÓN de vida.",2,6,2,5,{0.9,0,0,0,0,0,0,0,0,0,0,0,8,0,0,1.6,4,0,0,0,0,0,0,0,0},{{{{16,1,1}},1,"+1 acumulación máxima"},{{{15,0,1.4}},1,"+40% potencia"},{{{12,0,1.5}},1,"+50% duración"},{{{16,1,1},{15,0,1.4}},2,"+1 acumulación y +40% potencia"}}},  // aqua-ring
  {"Látigo Cepa","Látigos de largo alcance en arco amplio.",4,1,0,0,{0.62,19,0,0,0,0,0,0,85,1.63,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // vine-whip
  {"Hoja Afilada","Dos hojas que van y vuelven cortando a la ida y a la vuelta.",4,7,0,0,{0.9,10,330,2,0.5,0,0,6,210,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 bumerán"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% alcance"},{{{3,1,1},{1,0,1.4}},2,"+1 bumerán y +40% daño"}}},  // razor-leaf
  {"Tormenta Floral","Un ciclón de hojas gira amplio a tu alrededor.",4,3,1,0,{0.26,14,2.6,4,0,0,0,8,74,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 orbe"},{{{1,0,1.55}},1,"+55% daño"},{{{8,0,1.25},{2,0,1.35}},2,"+25% radio y gira más rápido"},{{{3,1,1},{1,0,1.55}},2,"+1 orbe y +55% daño"}}},  // leaf-storm
  {"Hierba Lazo","Raíces que atrapan y machacan todo lo que tienes cerca.",4,5,1,0,{0.55,9,0,0,0,0,0,0,76,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{8,0,1.3}},1,"+30% radio"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.7}},1,"Golpea un 40% más a menudo"},{{{8,0,1.3},{1,0,1.5}},2,"+30% radio y +50% daño"}}},  // giga-drain
  {"Impactrueno","Descarga rapidísima que atraviesa varios enemigos.",3,0,1,0,{0.4,13,480,1,0.08,2,1.1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // thunder-shock
  {"Chispazo","Campo eléctrico permanente alrededor de ti.",3,5,1,0,{0.45,8,0,0,0,0,0,0,70,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{8,0,1.3}},1,"+30% radio"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.7}},1,"Golpea un 40% más a menudo"},{{{8,0,1.3},{1,0,1.5}},2,"+30% radio y +50% daño"}}},  // discharge
  {"Rayo","Un rayo que salta de un enemigo a otro.",3,8,1,0,{0.95,21,0,4,0,0,0,0,140,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,2}},1,"+2 saltos"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,2},{1,0,1.4}},2,"+2 saltos y +40% daño"}}},  // thunderbolt
  {"Confusión","Onda que persigue sola a su objetivo.",10,0,1,0,{0.58,13,280,1,0.1,0,2.2,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // confusion
  {"Psicorrayo","Rayo psíquico ancho y contundente.",10,2,1,0,{1.15,17,0,0,0,0,0,0,215,0,0,40,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // psybeam
  {"Psíquico","Estallido mental radial que busca enemigos.",10,4,1,0,{1.35,10,230,12,0,1,1.6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},{{{{3,1,4}},1,"+4 proyectiles"},{{{1,0,1.4}},1,"+40% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,4},{5,1,1}},2,"+4 proyectiles y +1 perforación"}}},  // psychic
  {"Residuos","Lodo tóxico que envenena al impactar.",7,0,1,0,{0.6,17,290,1,0.12,0,1.5,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // sludge
  {"Disparo Lodo","Salpica lodo alrededor y ralentiza.",8,4,1,0,{1.1,11,200,7,0,0,1,9,0,0,0,0,0,0,0,0,0,0,0,0,0.4,0,0,0,0},{{{{3,1,4}},1,"+4 proyectiles"},{{{1,0,1.4}},1,"+40% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,4},{5,1,1}},2,"+4 proyectiles y +1 perforación"}}},  // mud-shot
  {"Tornado","Remolinos de viento que te escoltan.",9,3,1,0,{0.26,13,2.8,3,0,0,0,8,72,0,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 orbe"},{{{1,0,1.55}},1,"+55% daño"},{{{8,0,1.25},{2,0,1.35}},2,"+25% radio y gira más rápido"},{{{3,1,1},{1,0,1.55}},2,"+1 orbe y +55% daño"}}},  // gust
  {"Ataque Ala","Barrido de alas amplio que empuja.",9,1,0,0,{0.55,17,0,0,0,0,0,0,73,2.38,70,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // wing-attack
  {"Golpe Cuerpo","Placaje con todo el peso: lento, corto y brutal.",0,1,0,0,{0.95,36,0,0,0,0,0,0,58,2.75,140,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // body-slam
  {"Vozarrón","Onda sonora que sale en todas direcciones.",0,4,1,0,{1.15,12,260,9,0,1,0.9,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,4}},1,"+4 proyectiles"},{{{1,0,1.4}},1,"+40% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,4},{5,1,1}},2,"+4 proyectiles y +1 perforación"}}},  // hyper-voice
  {"Picotazo Veneno","Aguijón rápido que envenena.",7,0,0,0,{0.34,8,420,1,0.08,0,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // poison-sting
  {"Tóxico","Vas dejando charcos de veneno que intoxican a quien los pisa.",7,13,1,0,{0.3,6,0,0,0,0,0,0,26,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1},{{{{1,0,1.4}},1,"+40% daño"},{{{12,0,1.4}},1,"+40% duración"},{{{8,0,1.3}},1,"Charcos un 30% más grandes"},{{{1,0,1.5},{8,0,1.3}},2,"+50% daño y +30% radio"}}},  // toxic
  {"Terratemblor","Sacude el suelo: daña y frena a lo cercano.",8,5,0,0,{0.7,11,0,0,0,0,0,0,80,0,0,0,0,0,0,0,0,0,0,0,0.35,0,0,0,0},{{{{8,0,1.3}},1,"+30% radio"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.7}},1,"Golpea un 40% más a menudo"},{{{8,0,1.3},{1,0,1.5}},2,"+30% radio y +50% daño"}}},  // bulldoze
  {"Picadura","Mordisco rápido en arco corto.",11,1,0,0,{0.42,13,0,0,0,0,0,0,55,2,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // bug-bite
  {"Disparo Demora","Deja telarañas en el suelo que atrapan y frenan mucho al que las pisa.",11,9,0,0,{1.1,14,0,2,0,0,0,0,56,0,0,0,7,0,0,0,0,0,0,0,0.6,0,0,0,0},{{{{3,1,1}},1,"+1 mina"},{{{1,0,1.5}},1,"+50% daño"},{{{8,0,1.3}},1,"+30% radio de explosión"},{{{3,1,1},{0,0,0.75}},2,"+1 mina y -25% recarga"}}},  // string-shot
  {"Zumbido","Vibración constante que machaca lo cercano.",11,5,1,0,{0.45,8,0,0,0,0,0,0,66,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{8,0,1.3}},1,"+30% radio"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.7}},1,"Golpea un 40% más a menudo"},{{{8,0,1.3},{1,0,1.5}},2,"+30% radio y +50% daño"}}},  // bug-buzz
  {"Lanzarrocas","Pedrusco pesado que empuja al enemigo.",12,0,0,0,{0.7,24,260,1,0.12,0,1.4,9,0,0,90,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // rock-throw
  {"Avalancha","Caen rocas del cielo sobre los enemigos cercanos.",12,10,0,0,{1.3,21,0,3,0,0,0,0,46,0,50,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 meteoro"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{3,1,2},{0,0,0.8}},2,"+2 meteoros y -20% recarga"}}},  // rock-slide
  {"Rayo Hielo","Rayo helado que congela casi del todo.",5,2,1,0,{1.1,20,0,0,0,0,0,0,220,0,0,30,0,0,0,0,0,0,0,0,0.7,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // ice-beam
  {"Nieve Polvo","Ventisca a tu alrededor que ralentiza.",5,5,1,0,{0.55,8,0,0,0,0,0,0,76,0,0,0,0,0,0,0,0,0,0,0,0.45,0,0,0,0},{{{{8,0,1.3}},1,"+30% radio"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.7}},1,"Golpea un 40% más a menudo"},{{{8,0,1.3},{1,0,1.5}},2,"+30% radio y +50% daño"}}},  // powder-snow
  {"Golpe Kárate","Golpe seco y potente al frente.",6,1,0,0,{0.5,22,0,0,0,0,0,0,63,1.5,110,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // karate-chop
  {"Esfera Aural","Esfera de energía que nunca falla.",6,0,1,0,{0.62,17,300,1,0.1,0,2,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // aura-sphere
  {"Lengüetazo","Lametazo espectral que paraliza un poco.",13,1,0,0,{0.48,14,0,0,0,0,0,0,60,2.25,0,0,0,0,0,0,0,0,0,0,0.4,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // lick
  {"Bola Sombra","Esfera oscura que atraviesa a varios.",13,0,1,0,{0.66,19,280,1,0.1,2,1.6,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1},{4,0,1.4}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{5,1,1},{4,0,1.2}},3,"+1 proyectil y +1 perforación"}}},  // shadow-ball
  {"Furia Dragón","Llamarada dracónica en línea recta.",14,2,1,0,{1,24,0,0,0,0,0,0,230,0,0,34,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // dragon-rage
  {"Danza Dragón","No hace daño: acumula ATAQUE (físico) más rápido que Danza Espada.",14,6,2,1,{0.7,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0.11,5,0,0,0,0,0,0,0,0},{{{{16,1,1}},1,"+1 acumulación máxima"},{{{15,0,1.4}},1,"+40% potencia"},{{{12,0,1.5}},1,"+50% duración"},{{{16,1,1},{15,0,1.4}},2,"+1 acumulación y +40% potencia"}}},  // dragon-dance
  {"Viento Feérico","Brisa mágica en todas direcciones.",17,4,1,0,{1,11,230,10,0,0,1.2,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,4}},1,"+4 proyectiles"},{{{1,0,1.4}},1,"+40% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,4},{5,1,1}},2,"+4 proyectiles y +1 perforación"}}},  // fairy-wind
  {"Brillo Mágico","Destello a tu alrededor.",17,5,1,0,{0.5,9,0,0,0,0,0,0,72,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{8,0,1.3}},1,"+30% radio"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.7}},1,"Golpea un 40% más a menudo"},{{{8,0,1.3},{1,0,1.5}},2,"+30% radio y +50% daño"}}},  // dazzling-gleam
  {"Garra Metal","Zarpazo de acero en arco.",16,1,0,0,{0.5,18,0,0,0,0,0,0,63,2,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // metal-claw
  {"Foco Resplandor","Rayo de luz metálica que perfora.",16,2,1,0,{1.05,23,0,0,0,0,0,0,220,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // flash-cannon
  {"Mordisco","Dentellada rápida que hace retroceder.",15,1,0,0,{0.45,17,0,0,0,0,0,0,58,1.88,70,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // bite
  {"Pulso Umbrío","Onda de energía oscura en todas direcciones.",15,4,1,0,{1.15,14,240,10,0,1,1.1,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,4}},1,"+4 proyectiles"},{{{1,0,1.4}},1,"+40% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,4},{5,1,1}},2,"+4 proyectiles y +1 perforación"}}},  // dark-pulse
  {"Tinieblas","Una sombra te rodea y consume lo cercano.",15,5,1,0,{0.5,9,0,0,0,0,0,0,72,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{8,0,1.3}},1,"+30% radio"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.7}},1,"Golpea un 40% más a menudo"},{{{8,0,1.3},{1,0,1.5}},2,"+30% radio y +50% daño"}}},  // night-shade
  {"Huesomerang","Un hueso que va y vuelve golpeando fuerte.",8,7,0,0,{0.95,16,300,1,0,0,0,8,230,0,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 bumerán"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% alcance"},{{{3,1,1},{1,0,1.4}},2,"+1 bumerán y +40% daño"}}},  // bonemerang
  {"Psicocorte","Cuchillas psíquicas que vuelven a ti.",10,7,0,0,{0.8,9,360,2,0.6,0,0,7,200,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 bumerán"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% alcance"},{{{3,1,1},{1,0,1.4}},2,"+1 bumerán y +40% daño"}}},  // psycho-cut
  {"Púas","Siembra púas que estallan al pisarlas.",8,9,0,0,{1.2,18,0,2,0,0,0,0,60,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 mina"},{{{1,0,1.5}},1,"+50% daño"},{{{8,0,1.3}},1,"+30% radio de explosión"},{{{3,1,1},{0,0,0.75}},2,"+1 mina y -25% recarga"}}},  // spikes
  {"Púas Tóxicas","Púas venenosas que envenenan mucho al estallar.",7,9,0,0,{1.1,11,0,2,0,0,0,0,56,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,2},{{{{3,1,1}},1,"+1 mina"},{{{1,0,1.5}},1,"+50% daño"},{{{8,0,1.3}},1,"+30% radio de explosión"},{{{3,1,1},{0,0,0.75}},2,"+1 mina y -25% recarga"}}},  // toxic-spikes
  {"Granizo","Bolas de hielo caen sobre los enemigos y los frenan.",5,10,1,0,{1.2,18,0,4,0,0,0,0,40,0,0,0,0,0,0,0,0,0,0,0,0.4,0,0,0,0},{{{{3,1,1}},1,"+1 meteoro"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{3,1,2},{0,0,0.8}},2,"+2 meteoros y -20% recarga"}}},  // hail
  {"Puño Meteoro","Dos meteoros de acero que aplastan donde caen.",16,10,0,0,{1.4,34,0,2,0,0,0,0,54,0,80,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 meteoro"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{3,1,2},{0,0,0.8}},2,"+2 meteoros y -20% recarga"}}},  // meteor-mash
  {"Fuego Fatuo","Deja una llama flotante que dispara sola y quema.",1,11,1,0,{3.5,15,300,1,0,0,0,7,0,0,0,0,6,0.55,300,0,0,0,0,0,0,0,0,1,0},{{{{1,0,1.5}},1,"+50% daño"},{{{13,0,0.74}},1,"Dispara un 35% más rápido"},{{{3,1,1}},1,"+1 a la vez"},{{{12,0,1.5},{1,0,1.4}},2,"+50% duración y +40% daño"}}},  // will-o-wisp
  {"Sustituto","Un muñeco que se queda disparando por ti.",0,11,0,0,{4,14,320,1,0,0,0,6,0,0,0,0,6,0.4,280,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.5}},1,"+50% daño"},{{{13,0,0.74}},1,"Dispara un 35% más rápido"},{{{3,1,1}},1,"+1 a la vez"},{{{12,0,1.5},{1,0,1.4}},2,"+50% duración y +40% daño"}}},  // substitute
  {"Golpe Aéreo","Te lanzas en picado y cortas todo lo que cruzas.",9,12,0,0,{0.75,18,0,0,0,0,0,0,120,0,60,40,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% distancia"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.6},{11,0,1.4}},2,"+60% daño y más ancho"}}},  // aerial-ace
  {"Rueda Fuego","Corres envuelto en fuego y dejas un rastro de llamas.",1,13,0,0,{0.28,10,0,0,0,0,0,0,28,0,0,0,2.6,0,0,0,0,0,0,0,0,0,0,1,0},{{{{1,0,1.4}},1,"+40% daño"},{{{12,0,1.4}},1,"+40% duración"},{{{8,0,1.3}},1,"Charcos un 30% más grandes"},{{{1,0,1.5},{8,0,1.3}},2,"+50% daño y +30% radio"}}},  // flame-wheel
  {"Rayo Burbuja","Chorro de burbujas en abanico corto que frena.",2,14,1,0,{0.65,6,340,7,0,0,0.45,6,0,1,0,0,0,0,0,0,0,0,0,0,0.3,0,0,0,0},{{{{3,1,3}},1,"+3 disparos"},{{{1,0,1.4}},1,"+40% daño"},{{{6,0,1.3}},1,"+30% alcance"},{{{3,1,3},{5,1,1}},2,"+3 disparos y +1 perforación"}}},  // bubble-beam
  {"Infortunio","Maldición que salta entre enemigos. Mucho más daño si están quemados, envenenados o frenados.",13,8,1,0,{0.9,17,0,4,0,0,0,0,150,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,2}},1,"+2 saltos"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,2},{1,0,1.4}},2,"+2 saltos y +40% daño"}}},  // hex
  {"Hiperrayo","Se carga un momento y suelta un rayo enorme que lo atraviesa todo.",0,17,1,0,{2.2,58,0,0,0,0,0,0,300,0,0,44,0,0,0,0,0,0.75,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{17,0,0.7},{0,0,0.8}},2,"Carga más rápido y -20% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // hyper-beam
  {"Giro Rápido","Giras sobre ti mismo golpeando todo lo que te rodea varias veces.",0,18,0,0,{1,9,0,3,0,0,0,0,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{3,1,1}},1,"+1 vuelta"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // rapid-spin
  {"Nitrocarga","Te lanzas envuelto en llamas y quemas todo el camino.",1,12,0,0,{0.8,19,0,0,0,0,0,0,115,0,0,36,0,0,0,0,0,0,0,0,0,0,0,1,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% distancia"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.6},{11,0,1.4}},2,"+60% daño y más ancho"}}},  // flame-charge
  {"Torbellino","Un remolino que arrastra a los enemigos a su centro y los va dañando.",2,20,1,0,{3,8,0,0,0,0,0,0,72,0,0,0,2.6,0,0,0,0,0,150,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{12,0,1.5}},1,"+50% duración"},{{{18,0,1.4},{1,0,1.4}},2,"Atrae más fuerte y +40% daño"}}},  // whirlpool
  {"Bomba Germen","Una semilla que rebota de enemigo en enemigo.",4,16,0,0,{0.6,10,320,0,0,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // seed-bomb
  {"Energibola","Una bola de energía que persigue al enemigo.",4,15,1,0,{0.62,19,280,0,0,0,2,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // energy-ball
  {"Rayo Solar","Absorbe luz un momento y la suelta en un rayo enorme.",4,17,1,0,{2.3,62,0,0,0,0,0,0,290,0,0,40,0,0,0,0,0,0.85,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{17,0,0.7},{0,0,0.8}},2,"Carga más rápido y -20% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // solar-beam
  {"Onda Trueno","Una descarga que avisa en el suelo y deja paralizados a los que pilla.",3,22,1,0,{1.6,22,0,0,0,0,0,0,58,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{21,0,1.5}},1,"+50% aturdimiento"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // thunder-wave
  {"Bola Voltio","Una bola eléctrica que salta de enemigo en enemigo.",3,16,1,0,{0.62,10,340,0,0,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // electro-ball
  {"Paranormal","Una onda mental que daña y aparta a todos los que tienes cerca.",10,21,1,0,{1.2,16,0,0,0,0,0,0,92,0,320,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{0,0,0.75}},1,"-25% recarga"},{{{10,0,1.5},{1,0,1.4}},2,"+50% empuje y +40% daño"}}},  // extrasensory
  {"Bola Neblina","Una bola de bruma que persigue al enemigo y le frena.",10,15,1,0,{0.55,13,270,0,0,0,2,8,0,0,0,0,0,0,0,0,0,0,0,0,0.3,0,5,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // mist-ball
  {"Bomba Ácida","Un chorro ácido que salta entre enemigos y los envenena.",7,16,1,0,{0.66,8,310,0,0,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,1},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // acid-spray
  {"Bucle Arena","Un remolino de arena que atrapa y arrastra a los enemigos.",8,20,0,0,{3,9,0,0,0,0,0,0,70,0,0,0,2.6,0,0,0,0,0,140,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{12,0,1.5}},1,"+50% duración"},{{{18,0,1.4},{1,0,1.4}},2,"Atrae más fuerte y +40% daño"}}},  // sand-tomb
  {"Magnitud","El suelo revienta en línea delante de ti, onda tras onda.",8,19,0,0,{1.15,18,0,6,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,2}},1,"+2 ondas"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.25}},1,"+25% tamaño"},{{{0,0,0.75},{3,1,2}},2,"-25% recarga y +2 ondas"}}},  // magnitude
  {"Remolino","Un golpe de viento que barre a todos los que tienes cerca.",9,21,1,0,{1.1,14,0,0,0,0,0,0,96,0,360,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{0,0,0.75}},1,"-25% recarga"},{{{10,0,1.5},{1,0,1.4}},2,"+50% empuje y +40% daño"}}},  // whirlwind
  {"Tajo Aéreo","Dos cuchillas de aire que buscan al enemigo.",9,15,1,0,{0.55,9,330,2,0.35,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // air-slash
  {"Rayo Señal","Un destello que rebota entre los enemigos.",11,16,1,0,{0.6,10,340,0,0,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // signal-beam
  {"Ida y Vuelta","Cruzas entre los enemigos golpeando a todos los del camino.",11,12,0,0,{0.7,17,0,0,0,0,0,0,120,0,0,34,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% distancia"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.6},{11,0,1.4}},2,"+60% daño y más ancho"}}},  // u-turn
  {"Tumba Rocas","Caen rocas donde avisa el suelo y dejan atrapados a los que pilla.",12,22,0,0,{1.7,31,0,0,0,0,0,0,56,0,0,0,0,0,0,0,0,0,0,0,0,0.9,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{21,0,1.5}},1,"+50% aturdimiento"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // rock-tomb
  {"Poder Pasado","Rocas antiguas que giran a tu alrededor.",12,3,1,0,{0.28,13,2.6,3,0,0,0,9,70,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 orbe"},{{{1,0,1.55}},1,"+55% daño"},{{{8,0,1.25},{2,0,1.35}},2,"+25% radio y gira más rápido"},{{{3,1,1},{1,0,1.55}},2,"+1 orbe y +55% daño"}}},  // ancient-power
  {"Joya de Luz","Un destello de gema que rebota de enemigo en enemigo.",12,16,1,0,{0.66,11,320,0,0,0,1.6,8,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // power-gem
  {"Canto Helado","Esquirlas rapidísimas que persiguen al enemigo.",5,15,0,0,{0.32,9,380,0,0,0,1.5,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // ice-shard
  {"Liofilización","Un frío repentino que avisa en el suelo y deja congelados a los que pilla.",5,22,1,0,{1.6,24,0,0,0,0,0,0,60,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{21,0,1.5}},1,"+50% aturdimiento"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // freeze-dry
  {"Patada Giro","Patadas en giro que golpean todo lo que tienes alrededor.",6,18,0,0,{0.95,11,0,3,0,0,0,0,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{3,1,1}},1,"+1 vuelta"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // rolling-kick
  {"Onda Vacío","Un puñetazo al aire que lanza una onda y aparta a los enemigos.",6,21,1,0,{1.1,17,0,0,0,0,0,0,88,0,330,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{0,0,0.75}},1,"-25% recarga"},{{{10,0,1.5},{1,0,1.4}},2,"+50% empuje y +40% daño"}}},  // vacuum-wave
  {"Puño Dinámico","Un puñetazo tremendo donde avisa el suelo: deja aturdidos a los que pilla.",6,22,0,0,{1.7,33,0,0,0,0,0,0,54,0,0,0,0,0,0,0,0,0,0,0,0,0.9,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{21,0,1.5}},1,"+50% aturdimiento"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // dynamic-punch
  {"Sombra Vil","Una sombra que se escurre por el suelo hasta el enemigo.",13,15,0,0,{0.45,14,300,0,0,0,1.8,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // shadow-sneak
  {"Viento Aciago","Un viento maldito que arremolina a los enemigos y los va dañando.",13,20,1,0,{3,9,0,0,0,0,0,0,74,0,0,0,2.6,0,0,0,0,0,140,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{12,0,1.5}},1,"+50% duración"},{{{18,0,1.4},{1,0,1.4}},2,"Atrae más fuerte y +40% daño"}}},  // ominous-wind
  {"Dragoaliento","Un aliento de dragón en abanico corto que frena.",14,14,1,0,{0.7,7,330,7,0,0,0.5,7,0,0.95,0,0,0,0,0,0,0,0,0,0,0.25,0,0,0,0},{{{{3,1,3}},1,"+3 disparos"},{{{1,0,1.4}},1,"+40% daño"},{{{6,0,1.3}},1,"+30% alcance"},{{{3,1,3},{5,1,1}},2,"+3 disparos y +1 perforación"}}},  // dragon-breath
  {"Garra Dragón","Un zarpazo de dragón en arco.",14,1,0,0,{0.52,23,0,0,0,0,0,0,65,2.5,70,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // dragon-claw
  {"Enfado","Una furia de golpes en giro que no deja a nadie en pie.",14,18,0,0,{1.1,12,0,4,0,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{3,1,1}},1,"+1 vuelta"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // outrage
  {"Beso Drenaje","Un beso que persigue al enemigo y te cura un poco al darle.",17,15,1,0,{0.55,13,280,0,0,0,2,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // draining-kiss
  {"Carantoña","Un ataque juguetón pero muy fuerte en arco.",17,1,0,0,{0.6,26,0,0,0,0,0,0,63,2.5,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // play-rough
  {"Voz Cautivadora","Un grito encantador que daña y aparta a los que tienes cerca.",17,21,1,0,{1.15,15,0,0,0,0,0,0,94,0,300,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{0,0,0.75}},1,"-25% recarga"},{{{10,0,1.5},{1,0,1.4}},2,"+50% empuje y +40% daño"}}},  // disarming-voice
  {"Disparo Espejo","Un destello metálico que rebota entre los enemigos.",16,16,1,0,{0.64,10,340,0,0,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // mirror-shot
  {"Giro Bola","Giras como una bola de acero golpeando todo alrededor.",16,18,0,0,{1.05,12,0,3,0,0,0,0,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{3,1,1}},1,"+1 vuelta"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // gyro-ball
  {"Golpe Bajo","Un golpe a traición que busca al enemigo.",15,15,0,0,{0.7,22,330,0,0,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // sucker-punch
  {"Tajo Umbrío","Cortes en giro que alcanzan a todo lo que te rodea.",15,18,0,0,{1,11,0,3,0,0,0,0,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{3,1,1}},1,"+1 vuelta"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // night-slash
};

static const short POOL_ALL[] = {0,1,2,3,4,5,28,29,60,65,66,6,7,8,9,59,62,67,10,11,12,13,63,68,18,19,20,72,73,14,15,16,17,69,70,71,38,39,57,86,87,40,41,88,89,90,24,30,31,56,76,25,32,53,55,77,78,26,27,61,79,80,21,22,23,54,74,75,33,34,35,81,82,36,37,83,84,85,42,43,64,91,92,44,45,93,94,95,50,51,52,101,102,48,49,58,99,100,46,47,96,97,98};
struct PoolRef { short off, n; };
static const PoolRef POOL_BY_TYPE[NTYPES] = {{0,11},{11,7},{18,6},{24,5},{29,7},{36,5},{41,5},{46,5},{51,6},{57,5},{62,6},{68,5},{73,5},{78,5},{83,5},{88,5},{93,5},{98,5}};

enum { B_CHASE=0,B_CHARGER=1,B_RANGED=2,B_TANK=3,B_HEALER=4,B_SHIELDER=5,B_SUMMONER=6,B_BOMBER=7,B_BEAMER=8,B_ZONER=9,B_FAN=10,B_JUMPER=11,B_RUNNER=12 };
struct DexE { const char* name; unsigned char t1, t2, rarity, gen, leg, beh, start; short minion; unsigned short hp, spd, bst; float atk, pa, sa; unsigned char df, sd; };
#define DEX_N 966
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
  {"Dragonite",14,9,5,1,0,0,44,0,111,112,600,1.44,1.44,1.25,95,100},  // #149
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
  {"Tyranitar",12,15,5,2,0,0,36,0,115,104,600,1.44,1.44,1.22,110,100},  // #248
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
  {"Slaking",0,255,5,3,0,1,0,0,138,120,670,1.58,1.58,1.22,100,65},  // #289
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
  {"Salamence",14,9,5,3,0,8,44,0,113,120,600,1.44,1.44,1.31,80,80},  // #373
  {"Beldum",16,10,1,3,0,0,48,0,88,91,300,1,1,0.89,80,60},  // #374
  {"Metang",16,10,3,3,0,5,48,0,97,99,420,1.11,1.11,1,100,80},  // #375
  {"Metagross",16,10,5,3,0,2,48,0,106,107,600,1.44,1.44,1.22,130,90},  // #376
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
  {"Garchomp",14,8,5,4,0,8,44,0,119,121,600,1.42,1.42,1.14,95,85},  // #445
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
  {"Hydreigon",15,14,5,5,0,8,50,0,111,119,600,1.39,1.28,1.39,90,90},  // #635
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
  {"Goodra",14,255,5,6,0,1,44,0,110,112,600,1.31,1.25,1.31,70,150},  // #706
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
  {"Meltan",16,255,5,7,1,0,48,0,91,92,300,1.06,1.06,1,65,35},  // #808
  {"Melmetal",16,255,5,7,1,3,48,0,131,92,600,1.49,1.49,1.14,143,65},  // #809
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
};

static const short DEX_NUM[DEX_N] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,433,434,435,436,437,438,439,440,441,442,443,444,445,446,447,448,449,450,451,452,453,454,455,456,457,458,459,460,461,462,463,464,465,466,467,468,469,470,471,472,473,474,475,476,477,478,479,480,481,482,483,484,485,486,487,488,489,490,491,492,493,494,495,496,497,498,499,500,501,502,503,504,505,506,507,508,509,510,511,512,513,515,517,518,519,521,524,525,526,527,528,529,530,531,532,533,534,535,536,537,539,540,541,542,543,544,545,546,547,548,549,550,551,552,553,554,555,556,557,559,560,561,562,563,566,567,568,569,570,571,572,573,574,575,576,577,578,579,580,581,582,583,584,585,586,587,588,589,590,594,595,596,597,598,599,600,601,602,603,604,605,606,607,608,609,610,611,612,613,614,615,617,619,620,621,622,623,624,625,627,628,629,630,631,632,633,634,635,636,637,638,639,640,641,642,643,644,645,646,647,648,649,650,651,652,653,654,655,656,657,658,659,660,661,662,663,664,665,666,667,669,670,671,672,673,674,675,676,677,678,679,680,681,682,684,685,686,687,688,689,690,691,692,693,694,695,696,697,698,699,700,701,702,703,704,705,706,707,708,709,710,711,712,713,714,715,716,717,718,719,720,721,722,723,724,725,726,727,728,729,730,731,734,736,737,738,739,740,741,742,743,744,745,746,747,748,749,750,751,752,753,754,755,757,758,759,760,761,762,763,764,766,767,768,769,770,771,772,773,774,775,776,777,778,779,780,781,782,783,784,785,786,787,788,789,790,791,792,793,794,795,796,797,798,799,800,801,802,803,804,805,806,807,808,809,810,811,812,813,814,815,816,817,818,819,820,821,822,823,824,825,826,827,828,829,830,831,832,833,834,835,836,840,841,842,843,844,845,846,847,848,849,850,851,852,853,854,855,856,857,858,859,860,861,862,863,864,867,868,869,871,872,873,874,875,876,877,880,881,882,883,884,885,886,887,888,889,890,891,892,894,895,896,897,898,899,900,901,902,903,904,905,906,907,908,909,910,911,912,913,914,915,916,917,918,919,920,921,922,923,924,925,926,927,928,930,932,933,934,935,936,937,938,939,940,941,946,951,952,953,955,957,958,959,960,961,963,964,965,966,967,968,969,970,971,972,974,975,976,977,978,979,980,981,982,983,984,985,987,988,989,991,992,994,995,996,997,998,1000,1004,1005,1006,1007,1009,1010,1011,1012,1013,1015,1016,1017,1018,1019,1024};   // número de pokédex de cada fila
static const short STARTERS_IDX[] = {0,3,6,151,154,157,251,254,257,386,389,392,494,497,500,634,637,640,704,707,710,787,790,793,874,877,880,53,78};
#define NSTARTERS 29

#define NITEMS 11
static const char* ITEM_NAMES[NITEMS] = {"Restos","Cinta Elección","Garra Rápida","Banda Focus","Cascabel Concha","Moneda Amuleto","Huevo Suerte","Vidasfera","Pañuelo Elección","Casco Dentado","Chaleco Asalto"};
static const char* ITEM_DESCS[NITEMS] = {"Recuperas un 1,5% de tu vida por segundo.","+40% de daño, pero no puedes cambiar de movimiento.","-20% de recarga en todos tus movimientos.","Un golpe que te dejaría KO te deja con 1 de vida (cada 60 s).","Recuperas vida con el daño que haces.","+50% de Pokémonedas al acabar la run.","+30% de experiencia.","+30% de daño, pero cada ataque te quita un poco de vida.","+35% de velocidad.","Los que te golpean cuerpo a cuerpo reciben daño.","+20% de reducción de daño recibido."};
struct PermUp { const char* name; const char* unit; unsigned char max; float base, grow; };
#define NPERM 14
static const PermUp PERM[NPERM] = {{"Vitalidad","+8 vida",10,60,1.35},{"Fuerza","+4% daño",10,80,1.38},{"Zancada","+3% velocidad",8,70,1.4},{"Reflejos","-3% recarga",8,90,1.42},{"Coraza","+2% defensa",8,80,1.4},{"Síntesis","+0.2 vida/s",5,120,1.5},{"Imán","+12% recogida",6,50,1.4},{"Sabiduría","+5% experiencia",8,100,1.42},{"Fortuna","+8% Pokémonedas",8,120,1.45},{"Repertorio","Empiezas con 2 movimientos",1,1500,1},{"Golpe Crítico","+3% de críticos (x1,5 de daño)",10,90,1.4},{"Cambio de cartas","+1 cambio de cartas de nivel por run",5,150,1.6},{"Veto","Bloquea 1 movimiento: no te sale en las cartas",3,300,1.9},{"Movimiento inicial","Eliges con qué ataque empiezas la partida",1,400,1}};
static const char* PERM_IDS[NPERM] = {"hp","atk","spd","cd","def","regen","magnet","xp","coins","moves","crit","reroll","ban","start"};
