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
  {"Puño Meteoro","Dos meteoros de acero que aplastan donde caen.",16,10,0,0,{1.4,24,0,2,0,0,0,0,48,0,70,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 meteoro"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{3,1,2},{0,0,0.8}},2,"+2 meteoros y -20% recarga"}}},  // meteor-mash
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
  {"Bomba Germen","Una semilla que rebota de enemigo en enemigo.",4,16,0,0,{0.6,10,320,1,0.12,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // seed-bomb
  {"Energibola","Una bola de energía que persigue al enemigo.",4,15,1,0,{0.62,19,280,1,0.12,0,2,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // energy-ball
  {"Rayo Solar","Absorbe luz un momento y la suelta en un rayo enorme.",4,17,1,0,{2.3,62,0,0,0,0,0,0,290,0,0,40,0,0,0,0,0,0.85,0,0,0,0,0,0,0},{{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.3},{11,0,1.3}},2,"+30% alcance y grosor"},{{{17,0,0.7},{0,0,0.8}},2,"Carga más rápido y -20% recarga"},{{{1,0,1.5}},1,"+50% daño"}}},  // solar-beam
  {"Onda Trueno","Una descarga que avisa en el suelo y deja paralizados a los que pilla.",3,22,1,0,{1.6,22,0,0,0,0,0,0,58,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{21,0,1.5}},1,"+50% aturdimiento"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // thunder-wave
  {"Bola Voltio","Una bola eléctrica que salta de enemigo en enemigo.",3,16,1,0,{0.62,10,340,1,0.12,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // electro-ball
  {"Paranormal","Una onda mental que daña y aparta a todos los que tienes cerca.",10,21,1,0,{1.2,16,0,0,0,0,0,0,92,0,320,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{0,0,0.75}},1,"-25% recarga"},{{{10,0,1.5},{1,0,1.4}},2,"+50% empuje y +40% daño"}}},  // extrasensory
  {"Bola Neblina","Una bola de bruma que persigue al enemigo y le frena.",10,15,1,0,{0.55,13,270,1,0.12,0,2,8,0,0,0,0,0,0,0,0,0,0,0,0,0.3,0,5,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // mist-ball
  {"Bomba Ácida","Un chorro ácido que salta entre enemigos y los envenena.",7,16,1,0,{0.66,8,310,1,0.12,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,1},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // acid-spray
  {"Bucle Arena","Un remolino de arena que atrapa y arrastra a los enemigos.",8,20,0,0,{3,9,0,0,0,0,0,0,70,0,0,0,2.6,0,0,0,0,0,140,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{12,0,1.5}},1,"+50% duración"},{{{18,0,1.4},{1,0,1.4}},2,"Atrae más fuerte y +40% daño"}}},  // sand-tomb
  {"Magnitud","El suelo revienta en línea delante de ti, onda tras onda.",8,19,0,0,{1.15,18,0,6,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,2}},1,"+2 ondas"},{{{1,0,1.45}},1,"+45% daño"},{{{8,0,1.25}},1,"+25% tamaño"},{{{0,0,0.75},{3,1,2}},2,"-25% recarga y +2 ondas"}}},  // magnitude
  {"Remolino","Un golpe de viento que barre a todos los que tienes cerca.",9,21,1,0,{1.1,14,0,0,0,0,0,0,96,0,360,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{0,0,0.75}},1,"-25% recarga"},{{{10,0,1.5},{1,0,1.4}},2,"+50% empuje y +40% daño"}}},  // whirlwind
  {"Tajo Aéreo","Dos cuchillas de aire que buscan al enemigo.",9,15,1,0,{0.55,9,330,2,0.35,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // air-slash
  {"Rayo Señal","Un destello que rebota entre los enemigos.",11,16,1,0,{0.6,10,340,1,0.12,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // signal-beam
  {"Ida y Vuelta","Cruzas entre los enemigos golpeando a todos los del camino.",11,12,0,0,{0.7,17,0,0,0,0,0,0,120,0,0,34,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% distancia"},{{{0,0,0.75}},1,"-25% recarga"},{{{1,0,1.6},{11,0,1.4}},2,"+60% daño y más ancho"}}},  // u-turn
  {"Tumba Rocas","Caen rocas donde avisa el suelo y dejan atrapados a los que pilla.",12,22,0,0,{1.7,31,0,0,0,0,0,0,56,0,0,0,0,0,0,0,0,0,0,0,0,0.9,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{21,0,1.5}},1,"+50% aturdimiento"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // rock-tomb
  {"Poder Pasado","Rocas antiguas que giran a tu alrededor.",12,3,1,0,{0.28,13,2.6,3,0,0,0,9,70,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{3,1,1}},1,"+1 orbe"},{{{1,0,1.55}},1,"+55% daño"},{{{8,0,1.25},{2,0,1.35}},2,"+25% radio y gira más rápido"},{{{3,1,1},{1,0,1.55}},2,"+1 orbe y +55% daño"}}},  // ancient-power
  {"Joya de Luz","Un destello de gema que rebota de enemigo en enemigo.",12,16,1,0,{0.66,11,320,1,0.12,0,1.6,8,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // power-gem
  {"Canto Helado","Esquirlas rapidísimas que persiguen al enemigo.",5,15,0,0,{0.32,9,380,1,0.12,0,1.5,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // ice-shard
  {"Liofilización","Un frío repentino que avisa en el suelo y deja congelados a los que pilla.",5,22,1,0,{1.6,24,0,0,0,0,0,0,60,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{21,0,1.5}},1,"+50% aturdimiento"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // freeze-dry
  {"Patada Giro","Patadas en giro que golpean todo lo que tienes alrededor.",6,18,0,0,{0.95,11,0,3,0,0,0,0,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{3,1,1}},1,"+1 vuelta"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // rolling-kick
  {"Onda Vacío","Un puñetazo al aire que lanza una onda y aparta a los enemigos.",6,21,1,0,{1.1,17,0,0,0,0,0,0,88,0,330,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{0,0,0.75}},1,"-25% recarga"},{{{10,0,1.5},{1,0,1.4}},2,"+50% empuje y +40% daño"}}},  // vacuum-wave
  {"Puño Dinámico","Un puñetazo tremendo donde avisa el suelo: deja aturdidos a los que pilla.",6,22,0,0,{1.7,33,0,0,0,0,0,0,54,0,0,0,0,0,0,0,0,0,0,0,0,0.9,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{21,0,1.5}},1,"+50% aturdimiento"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // dynamic-punch
  {"Sombra Vil","Una sombra que se escurre por el suelo hasta el enemigo.",13,15,0,0,{0.45,14,300,1,0.12,0,1.8,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // shadow-sneak
  {"Viento Aciago","Un viento maldito que arremolina a los enemigos y los va dañando.",13,20,1,0,{3,9,0,0,0,0,0,0,74,0,0,0,2.6,0,0,0,0,0,140,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.3}},1,"+30% radio"},{{{12,0,1.5}},1,"+50% duración"},{{{18,0,1.4},{1,0,1.4}},2,"Atrae más fuerte y +40% daño"}}},  // ominous-wind
  {"Dragoaliento","Un aliento de dragón en abanico corto que frena.",14,14,1,0,{0.7,7,330,7,0,0,0.5,7,0,0.95,0,0,0,0,0,0,0,0,0,0,0.25,0,0,0,0},{{{{3,1,3}},1,"+3 disparos"},{{{1,0,1.4}},1,"+40% daño"},{{{6,0,1.3}},1,"+30% alcance"},{{{3,1,3},{5,1,1}},2,"+3 disparos y +1 perforación"}}},  // dragon-breath
  {"Garra Dragón","Un zarpazo de dragón en arco.",14,1,0,0,{0.52,23,0,0,0,0,0,0,65,2.5,70,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // dragon-claw
  {"Enfado","Una furia de golpes en giro que no deja a nadie en pie.",14,18,0,0,{1.1,12,0,4,0,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{3,1,1}},1,"+1 vuelta"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // outrage
  {"Beso Drenaje","Un beso que persigue al enemigo y te cura un poco al darle.",17,15,1,0,{0.55,13,280,1,0.12,0,2,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // draining-kiss
  {"Carantoña","Un ataque juguetón pero muy fuerte en arco.",17,1,0,0,{0.6,26,0,0,0,0,0,0,63,2.5,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% alcance"},{{{0,0,0.75}},1,"-25% recarga"},{{{9,0,9},{1,0,1.5}},2,"Golpea en 360° y +50% daño"}}},  // play-rough
  {"Voz Cautivadora","Un grito encantador que daña y aparta a los que tienes cerca.",17,21,1,0,{1.15,15,0,0,0,0,0,0,94,0,300,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{0,0,0.75}},1,"-25% recarga"},{{{10,0,1.5},{1,0,1.4}},2,"+50% empuje y +40% daño"}}},  // disarming-voice
  {"Disparo Espejo","Un destello metálico que rebota entre los enemigos.",16,16,1,0,{0.64,10,340,1,0.12,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0},{{{{19,1,1}},1,"+1 rebote"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{19,1,1},{4,0,1.3}},3,"+1 proyectil y +1 rebote"}}},  // mirror-shot
  {"Giro Bola","Giras como una bola de acero golpeando todo alrededor.",16,18,0,0,{1.05,12,0,3,0,0,0,0,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{3,1,1}},1,"+1 vuelta"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // gyro-ball
  {"Golpe Bajo","Un golpe a traición que busca al enemigo.",15,15,0,0,{0.7,22,330,1,0.12,0,1.6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0},{{{{3,1,1},{4,0,1.3}},2,"+1 proyectil"},{{{1,0,1.45}},1,"+45% daño"},{{{0,0,0.75}},1,"-25% recarga"},{{{3,1,1},{1,0,1.4}},2,"+1 proyectil y +40% daño"}}},  // sucker-punch
  {"Tajo Umbrío","Cortes en giro que alcanzan a todo lo que te rodea.",15,18,0,0,{1,11,0,3,0,0,0,0,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{{{{1,0,1.4}},1,"+40% daño"},{{{8,0,1.25}},1,"+25% radio"},{{{3,1,1}},1,"+1 vuelta"},{{{0,0,0.75},{1,0,1.3}},2,"-25% recarga y +30% daño"}}},  // night-slash
};

static const short EVO_NEED[NMOVES] = {0,2,-1,-1,-1,-1,1,3,5,0,1,2,1,-1,1,3,5,0,1,4,3,3,1,6,1,1,2,1,1,3,2,5,1,1,3,5,1,3,1,2,1,3,1,3,1,-1,1,5,1,4,1,2,5,1,3,1,5,3,1,3,4,2,2,1,6,1,2,2,5,1,5,3,1,2,4,3,5,0,1,2,3,1,5,0,4,1,3,1,2,4,1,3,6,1,1,0,5,1,4,1,4,1,2};
static const char* EVO_NAME[NMOVES] = {"Placaje +","Ataque Rápido +","","","","","Ascuas +","Lanzallamas +","Giro Fuego +","Onda Ígnea +","Pistola Agua +","Burbuja +","Hidrobomba +","","Látigo Cepa +","Hoja Afilada +","Tormenta Floral +","Hierba Lazo +","Impactrueno +","Chispazo +","Rayo +","Confusión +","Psicorrayo +","Psíquico +","Residuos +","Disparo Lodo +","Tornado +","Ataque Ala +","Golpe Cuerpo +","Vozarrón +","Picotazo Veneno +","Tóxico +","Terratemblor +","Picadura +","Disparo Demora +","Zumbido +","Lanzarrocas +","Avalancha +","Rayo Hielo +","Nieve Polvo +","Golpe Kárate +","Esfera Aural +","Lengüetazo +","Bola Sombra +","Furia Dragón +","","Viento Feérico +","Brillo Mágico +","Garra Metal +","Foco Resplandor +","Mordisco +","Pulso Umbrío +","Tinieblas +","Huesomerang +","Psicocorte +","Púas +","Púas Tóxicas +","Granizo +","Puño Meteoro +","Fuego Fatuo +","Sustituto +","Golpe Aéreo +","Rueda Fuego +","Rayo Burbuja +","Infortunio +","Hiperrayo +","Giro Rápido +","Nitrocarga +","Torbellino +","Bomba Germen +","Energibola +","Rayo Solar +","Onda Trueno +","Bola Voltio +","Paranormal +","Bola Neblina +","Bomba Ácida +","Bucle Arena +","Magnitud +","Remolino +","Tajo Aéreo +","Rayo Señal +","Ida y Vuelta +","Tumba Rocas +","Poder Pasado +","Joya de Luz +","Canto Helado +","Liofilización +","Patada Giro +","Onda Vacío +","Puño Dinámico +","Sombra Vil +","Viento Aciago +","Dragoaliento +","Garra Dragón +","Enfado +","Beso Drenaje +","Carantoña +","Voz Cautivadora +","Disparo Espejo +","Giro Bola +","Golpe Bajo +","Tajo Umbrío +"};
struct EvoMod { UpMod m[6]; unsigned char n; const char* text; };
static const EvoMod EVO_MODS[23] = {
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
};

static const short DEX_NUM[DEX_N] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,433,434,435,436,437,438,439,440,441,442,443,444,445,446,447,448,449,450,451,452,453,454,455,456,457,458,459,460,461,462,463,464,465,466,467,468,469,470,471,472,473,474,475,476,477,478,479,480,481,482,483,484,485,486,487,488,489,490,491,492,493,494,495,496,497,498,499,500,501,502,503,504,505,506,507,508,509,510,511,512,513,515,517,518,519,521,524,525,526,527,528,529,530,531,532,533,534,535,536,537,539,540,541,542,543,544,545,546,547,548,549,550,551,552,553,554,555,556,557,559,560,561,562,563,566,567,568,569,570,571,572,573,574,575,576,577,578,579,580,581,582,583,584,585,586,587,588,589,590,594,595,596,597,598,599,600,601,602,603,604,605,606,607,608,609,610,611,612,613,614,615,617,619,620,621,622,623,624,625,627,628,629,630,631,632,633,634,635,636,637,638,639,640,641,642,643,644,645,646,647,648,649,650,651,652,653,654,655,656,657,658,659,660,661,662,663,664,665,666,667,669,670,671,672,673,674,675,676,677,678,679,680,681,682,684,685,686,687,688,689,690,691,692,693,694,695,696,697,698,699,700,701,702,703,704,705,706,707,708,709,710,711,712,713,714,715,716,717,718,719,720,721,722,723,724,725,726,727,728,729,730,731,734,736,737,738,739,740,741,742,743,744,745,746,747,748,749,750,751,752,753,754,755,757,758,759,760,761,762,763,764,766,767,768,769,770,771,772,773,774,775,776,777,778,779,780,781,782,783,784,785,786,787,788,789,790,791,792,793,794,795,796,797,798,799,800,801,802,803,804,805,806,807,808,809,810,811,812,813,814,815,816,817,818,819,820,821,822,823,824,825,826,827,828,829,830,831,832,833,834,835,836,840,841,842,843,844,845,846,847,848,849,850,851,852,853,854,855,856,857,858,859,860,861,862,863,864,867,868,869,871,872,873,874,875,876,877,880,881,882,883,884,885,886,887,888,889,890,891,892,894,895,896,897,898,899,900,901,902,903,904,905,906,907,908,909,910,911,912,913,914,915,916,917,918,919,920,921,922,923,924,925,926,927,928,930,932,933,934,935,936,937,938,939,940,941,946,951,952,953,955,957,958,959,960,961,963,964,965,966,967,968,969,970,971,972,974,975,976,977,978,979,980,981,982,983,984,985,987,988,989,991,992,994,995,996,997,998,1000,1004,1005,1006,1007,1009,1010,1011,1012,1013,1015,1016,1017,1018,1019,1024};   // número de pokédex de cada fila
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
static const unsigned short DEX_ABIL[DEX_N][3] = {{143,0,23},{143,0,23},{143,0,23},{19,0,204},{19,0,204},{19,0,204},{240,0,167},{240,0,167},{240,0,167},{195,0,178},{192,0,0},{30,0,239},{195,0,178},{192,0,0},{227,0,201},{106,232,18},{106,232,18},{106,232,18},{178,78,87},{178,78,87},{106,0,201},{106,0,201},{101,192,252},{101,192,252},{214,0,112},{214,0,112},{183,0,180},{183,0,180},{151,174,87},{151,174,87},{151,174,193},{151,174,87},{151,174,87},{151,174,193},{36,119,66},{36,119,250},{60,0,48},{60,0,48},{36,29,66},{36,29,67},{99,0,97},{99,0,97},{23,0,178},{23,0,218},{23,0,52},{52,49,37},{52,49,37},{30,239,178},{195,239,269},{183,7,179},{183,7,179},{147,233,252},{113,233,252},{37,25,229},{37,25,229},{255,5,43},{255,5,43},{101,60,105},{101,60,105},{258,37,229},{258,37,229},{258,37,229},{231,99,119},{231,99,119},{231,99,119},{78,138,215},{78,138,215},{78,138,215},{23,0,71},{23,0,71},{23,0,71},{24,115,167},{24,115,167},{176,222,183},{176,222,183},{176,222,183},{178,60,58},{178,60,58},{140,144,172},{140,144,172},{122,222,4},{122,222,4},{106,99,43},{178,50,232},{178,50,232},{238,88,90},{238,88,90},{218,219,152},{218,219,152},{194,198,142},{194,198,142},{109,0,0},{109,0,0},{35,0,0},{176,222,262},{100,65,99},{100,65,99},{89,194,193},{89,194,193},{207,214,2},{207,214,2},{23,0,79},{23,0,79},{176,112,14},{176,112,14},{113,170,251},{106,104,99},{144,140,25},{109,137,218},{109,137,218},{112,176,170},{112,176,170},{136,188,80},{23,108,172},{50,186,99},{229,201,37},{151,201,37},{229,261,112},{229,261,112},{93,136,4},{93,136,4},{207,57,233},{227,233,215},{140,65,49},{214,0,255},{58,0,255},{89,129,132},{101,5,193},{229,0,168},{101,0,132},{258,194,88},{113,0,96},{178,1,6},{258,0,88},{256,0,166},{60,0,78},{245,45,4},{229,194,262},{229,194,262},{229,14,262},{229,14,262},{176,155,252},{95,238,71},{155,0,202},{155,0,214},{155,0,58},{192,0,123},{192,0,123},{99,0,133},{155,0,252},{231,0,0},{143,0,108},{143,0,108},{143,0,108},{19,0,60},{19,0,60},{19,0,60},{240,0,193},{240,0,193},{240,0,193},{178,106,67},{178,106,67},{100,106,239},{100,106,239},{227,50,168},{227,50,104},{227,100,201},{227,100,201},{99,0,97},{256,93,258},{256,93,258},{214,0,112},{36,119,66},{36,29,66},{87,188,224},{87,188,224},{231,50,118},{231,50,118},{214,0,149},{214,0,149},{214,0,149},{23,0,80},{238,85,184},{238,85,184},{222,176,168},{258,37,47},{23,108,97},{23,108,97},{23,108,97},{178,147,198},{23,204,50},{23,204,50},{208,30,67},{37,258,250},{37,258,250},{231,0,118},{231,0,99},{100,224,154},{140,144,172},{109,0,0},{109,0,0},{190,0,234},{99,50,184},{222,0,142},{222,0,142},{188,178,168},{89,183,95},{176,222,193},{101,178,168},{101,166,168},{151,229,101},{227,233,111},{222,71,31},{227,78,132},{99,106,146},{147,166,83},{78,166,252},{121,58,262},{121,58,262},{140,202,238},{140,202,238},{87,136,172},{87,201,130},{223,201,130},{255,87,100},{229,258,261},{106,222,262},{50,60,252},{50,60,252},{229,201,37},{147,0,183},{222,0,183},{245,45,4},{101,67,184},{144,233,130},{78,215,255},{101,233,215},{140,65,88},{214,0,255},{58,0,255},{238,186,184},{136,188,80},{155,0,99},{155,0,99},{155,0,99},{78,0,183},{192,0,0},{182,0,252},{155,0,133},{155,0,172},{136,0,0},{143,0,251},{143,0,251},{143,0,251},{19,0,208},{19,0,208},{19,0,208},{240,0,37},{240,0,37},{240,0,37},{178,166,168},{101,166,132},{147,71,166},{147,71,166},{195,0,178},{192,0,0},{227,0,174},{192,0,0},{195,0,30},{229,167,144},{229,167,144},{229,167,144},{23,50,146},{23,50,146},{23,267,146},{78,0,186},{78,0,186},{106,88,167},{106,47,167},{231,245,234},{231,245,234},{231,245,234},{229,0,167},{101,0,252},{52,150,166},{52,150,233},{248,0,0},{255,0,0},{248,0,0},{30,0,178},{208,0,97},{268,0,0},{207,0,168},{207,0,186},{207,0,186},{238,78,193},{238,78,193},{238,85,184},{222,122,179},{36,139,269},{36,139,269},{106,210,154},{89,101,193},{222,176,82},{222,176,82},{222,176,82},{162,0,234},{162,0,234},{214,112,126},{214,112,126},{149,0,112},{126,0,256},{93,227,154},{140,239,154},{136,151,108},{115,219,71},{115,219,71},{177,0,208},{177,0,208},{261,140,155},{261,140,155},{140,197,144},{121,205,5},{264,48,194},{238,144,71},{238,144,71},{144,232,31},{89,7,193},{109,0,0},{109,0,0},{183,0,258},{183,0,258},{136,0,25},{136,0,25},{95,0,242},{192,0,97},{109,0,0},{109,0,0},{140,6,88},{140,6,88},{89,194,1},{89,194,1},{109,0,0},{109,0,0},{223,0,220},{223,0,220},{14,0,229},{14,0,229},{229,140,1},{123,29,36},{64,0,0},{26,0,158},{100,67,35},{100,67,35},{109,0,67},{155,0,67},{23,204,79},{109,0,0},{155,224,105},{190,0,234},{99,90,130},{99,90,130},{238,90,140},{238,90,140},{238,90,140},{194,0,168},{229,0,261},{229,0,88},{229,176,222},{229,0,88},{176,0,193},{176,0,142},{101,0,132},{24,0,111},{24,0,111},{24,0,111},{24,0,222},{24,0,90},{24,0,111},{109,0,0},{109,0,0},{47,0,0},{48,0,0},{3,0,0},{188,0,0},{155,0,0},{143,0,194},{143,0,194},{143,0,194},{19,0,104},{19,0,104},{19,0,104},{240,0,29},{240,0,29},{240,0,29},{106,0,170},{101,0,170},{101,0,170},{197,250,130},{197,250,130},{192,0,178},{227,0,233},{174,101,78},{174,101,78},{174,101,78},{136,151,108},{136,151,233},{129,0,193},{129,0,193},{222,0,207},{222,0,207},{192,0,142},{6,0,142},{227,0,239},{83,0,87},{155,0,252},{178,147,256},{229,0,261},{229,0,261},{23,0,0},{61,0,0},{219,220,179},{219,220,179},{233,147,198},{2,251,59},{2,251,59},{178,107,113},{36,107,113},{109,0,0},{100,224,132},{113,144,106},{238,144,43},{109,0,0},{218,2,106},{218,2,106},{109,81,82},{109,81,82},{222,176,168},{207,57,233},{136,188,66},{106,232,18},{155,0,97},{183,0,177},{183,0,177},{183,0,177},{147,238,71},{215,99,154},{215,99,105},{182,0,179},{182,0,179},{14,201,106},{14,201,106},{6,49,152},{6,49,152},{109,0,0},{229,220,261},{229,220,261},{229,258,261},{203,0,207},{203,0,207},{155,0,146},{122,222,4},{144,140,25},{112,205,170},{23,108,172},{131,0,255},{58,0,255},{87,188,224},{208,239,67},{108,0,23},{202,0,90},{89,183,150},{140,202,238},{1,45,4},{215,191,105},{222,122,179},{155,0,67},{202,0,35},{109,0,0},{109,0,0},{109,0,0},{109,0,0},{155,0,234},{155,0,234},{60,0,58},{199,0,0},{155,0,234},{109,0,0},{88,0,0},{88,0,0},{11,0,0},{136,0,0},{134,0,0},{254,0,0},{143,0,31},{143,0,31},{143,0,31},{19,0,238},{19,0,238},{19,0,170},{240,0,194},{240,0,194},{240,0,194},{178,106,4},{93,106,4},{255,147,178},{101,180,186},{101,180,186},{113,251,154},{113,251,154},{71,0,143},{71,0,143},{71,0,19},{71,0,240},{65,231,234},{65,231,234},{18,224,174},{18,224,174},{222,262,179},{222,262,179},{222,182,179},{250,107,197},{250,107,197},{180,179,129},{180,179,129},{80,172,107},{78,193,104},{78,193,104},{78,193,104},{229,88,258},{229,88,258},{229,152,258},{222,99,129},{227,23,142},{108,23,142},{227,23,142},{151,227,208},{151,227,208},{151,227,208},{154,97,23},{154,97,23},{23,144,108},{23,144,108},{170,1,129},{101,132,5},{101,132,5},{101,132,5},{87,0,99},{193,0,270},{258,23,220},{222,194,262},{192,132,101},{192,132,101},{269,119,239},{135,0,0},{135,0,0},{42,0,0},{42,0,0},{218,219,2},{218,262,2},{94,0,0},{94,0,0},{36,233,198},{36,233,198},{67,29,190},{67,29,190},{67,29,190},{142,119,172},{142,119,172},{142,119,172},{106,18,88},{106,18,88},{90,202,262},{90,202,262},{90,203,262},{23,184,188},{23,184,188},{214,0,131},{227,192,138},{227,194,142},{52,0,172},{80,88,172},{30,252,227},{30,252,227},{103,0,0},{103,0,6},{149,126,24},{149,126,24},{149,126,24},{109,0,0},{109,0,0},{109,0,0},{234,231,4},{234,231,4},{60,58,97},{60,58,97},{60,58,97},{174,129,252},{174,129,252},{174,129,252},{202,200,168},{202,200,229},{109,0,0},{88,219,251},{99,172,170},{99,172,170},{177,193,129},{104,107,138},{104,107,138},{43,99,155},{43,99,155},{106,193,87},{106,193,43},{18,142,262},{18,142,262},{71,60,264},{227,87,248},{87,0,0},{87,0,0},{109,0,0},{58,0,227},{58,0,227},{105,0,0},{105,0,0},{105,0,0},{154,0,43},{154,0,43},{249,0,0},{236,0,0},{179,0,193},{155,0,0},{105,0,0},{188,0,0},{45,0,0},{143,0,20},{143,0,20},{143,0,20},{19,0,120},{19,0,120},{19,0,120},{240,0,158},{240,0,158},{240,0,158},{147,21,85},{147,21,85},{18,0,70},{58,0,70},{58,0,70},{195,30,66},{192,0,66},{195,30,66},{174,252,132},{62,0,230},{62,0,230},{62,0,230},{184,0,74},{184,0,74},{104,129,186},{104,129,186},{69,0,0},{106,97,144},{106,97,154},{138,0,0},{138,0,0},{213,0,0},{80,0,9},{228,0,251},{228,0,251},{31,223,97},{31,223,97},{241,201,146},{241,201,146},{151,152,1},{151,152,1},{124,0,0},{124,0,0},{49,183,204},{49,183,204},{221,0,222},{221,0,176},{171,0,203},{171,0,203},{36,0,148},{113,251,129},{21,147,149},{24,0,222},{184,88,73},{184,88,73},{184,88,73},{154,0,120},{136,67,79},{136,67,79},{147,67,100},{147,67,100},{144,90,222},{144,90,222},{67,97,234},{67,97,234},{56,0,0},{39,0,0},{10,0,0},{24,0,0},{120,0,0},{258,0,0},{143,0,117},{143,0,117},{143,0,117},{19,0,101},{19,0,101},{19,0,101},{240,0,116},{240,0,116},{240,0,116},{106,198,147},{209,221,1},{227,0,0},{13,0,0},{109,0,0},{89,104,5},{89,104,5},{38,0,0},{83,195,228},{83,195,228},{106,255,215},{106,180,215},{185,0,0},{125,113,172},{125,113,172},{144,212,99},{144,212,99},{259,0,258},{259,0,258},{108,0,31},{108,0,31},{93,52,167},{32,0,140},{32,0,140},{63,107,36},{63,107,252},{108,140,228},{108,140,228},{108,165,228},{62,247,136},{169,0,43},{265,0,0},{55,0,0},{260,0,183},{260,0,183},{98,0,250},{14,0,0},{175,0,0},{196,0,0},{27,0,0},{194,0,0},{103,112,222},{44,0,0},{41,221,269},{17,184,25},{216,0,0},{20,207,142},{20,207,142},{20,207,142},{53,0,234},{160,0,234},{75,0,234},{128,0,234},{250,0,0},{222,0,0},{68,0,0},{189,0,0},{16,0,0},{16,0,0},{16,0,0},{16,0,0},{16,0,0},{16,0,0},{16,0,0},{156,0,0},{206,0,0},{233,0,0},{16,0,0},{16,0,0},{16,0,0},{16,0,0},{256,0,0},{122,0,0},{104,0,0},{143,0,75},{143,0,75},{143,0,75},{19,0,110},{19,0,110},{19,0,110},{240,0,201},{240,0,201},{240,0,201},{21,0,71},{21,0,71},{106,252,18},{106,252,18},{155,252,127},{227,30,234},{227,30,234},{227,67,234},{178,251,209},{178,251,209},{33,172,52},{33,172,52},{63,178,20},{63,215,20},{221,194,229},{221,194,229},{12,0,168},{221,0,29},{173,71,20},{173,71,87},{173,71,238},{181,192,183},{181,192,183},{77,0,0},{229,0,157},{229,0,157},{168,214,107},{161,149,233},{60,264,58},{60,264,58},{113,0,233},{113,0,233},{262,0,35},{262,0,35},{80,6,118},{80,6,118},{80,6,118},{154,67,146},{154,67,146},{154,67,146},{170,78,43},{14,241,217},{262,0,145},{257,0,0},{228,0,9},{228,0,9},{112,0,53},{195,0,92},{195,0,92},{153,0,0},{91,0,0},{99,231,160},{86,0,0},{256,87,180},{256,214,200},{258,221,180},{258,90,200},{111,82,211},{24,97,35},{24,97,35},{24,97,35},{102,0,0},{40,0,0},{155,0,0},{99,0,0},{253,0,0},{246,0,0},{46,0,0},{22,0,0},{76,0,0},{252,0,0},{101,67,184},{227,193,191},{78,20,252},{229,1,129},{155,251,152},{151,229,101},{36,0,31},{143,0,158},{143,0,158},{143,0,158},{19,0,250},{19,0,250},{19,0,250},{240,0,132},{240,0,132},{240,0,132},{9,71,238},{114,71,238},{100,0,209},{100,0,209},{227,0,239},{227,0,239},{214,136,104},{256,136,104},{256,136,104},{178,147,144},{66,21,233},{144,0,107},{263,0,9},{50,0,79},{187,0,79},{163,222,24},{163,222,24},{163,222,24},{60,0,58},{60,0,262},{60,0,262},{144,214,37},{54,214,37},{266,256,29},{266,256,29},{267,0,97},{23,100,107},{23,100,130},{30,0,192},{6,67,208},{129,144,146},{129,144,146},{129,144,146},{73,168,183},{73,168,183},{261,0,0},{271,0,0},{142,0,199},{142,0,57},{192,0,172},{51,0,183},{244,0,32},{244,0,32},{147,0,63},{180,0,63},{238,202,193},{238,200,193},{129,0,191},{250,140,261},{28,0,220},{255,99,43},{151,258,250},{34,8,184},{188,178,168},{43,226,155},{159,0,0},{159,0,0},{159,0,0},{159,0,0},{159,0,0},{164,0,0},{164,0,0},{164,0,0},{164,0,0},{237,0,90},{237,0,90},{237,0,90},{72,0,0},{15,0,0},{159,0,0},{164,0,0},{141,0,0},{159,0,0},{164,0,0},{225,71,219},{84,0,81},{84,0,81},{243,0,67},{243,0,233},{43,0,0},{212,222,211},{225,172,219},{235,0,0}};

#define NTM 58
static const short TM_MOVE[NTM] = {76,61,4,80,41,28,33,35,32,51,47,98,94,45,96,73,70,8,67,7,49,17,100,57,9,64,12,65,29,38,16,48,25,3,52,95,97,85,22,23,54,37,83,77,69,43,71,55,60,2,72,20,31,56,82,89,68,59};   // índice en MOVES (-1 = no está en la 3DS)
static const short TM_PRICE[NTM] = {540,660,400,750,780,810,660,840,660,780,780,540,780,400,600,660,840,510,600,840,780,750,660,400,870,690,960,1200,840,840,1080,600,630,400,400,1020,840,780,690,840,720,750,660,510,780,780,1020,400,400,400,400,840,400,400,720,540,510,400};
static const char* TM_ID[NTM] = {"acid-spray","aerial-ace","agility","air-slash","aura-sphere","body-slam","bug-bite","bug-buzz","bulldoze","dark-pulse","dazzling-gleam","disarming-voice","dragon-claw","dragon-dance","draining-kiss","electro-ball","energy-ball","fire-spin","flame-charge","flamethrower","flash-cannon","giga-drain","gyro-ball","hail","heat-wave","hex","hydro-pump","hyper-beam","hyper-voice","ice-beam","leaf-storm","metal-claw","mud-shot","nasty-plot","night-shade","outrage","play-rough","power-gem","psybeam","psychic","psycho-cut","rock-slide","rock-tomb","sand-tomb","seed-bomb","shadow-ball","solar-beam","spikes","substitute","swords-dance","thunder-wave","thunderbolt","toxic","toxic-spikes","u-turn","vacuum-wave","whirlpool","will-o-wisp"};
// bit i = el Pokémon aprende la MT i
static const unsigned long long TM_MASK[DEX_N] = {5435986563629089ull,5435986563629089ull,5435986697847073ull,144966246600683552ull,144966244453199904ull,145036613331595562ull,72339073917780000ull,72339073917780000ull,72345671122813488ull,0ull,0ull,18401976494669960ull,0ull,0ull,18929192320106498ull,18295873486192642ull,18295873486192642ull,18295873620410370ull,3694359606198272ull,4257309693837312ull,18295873486192642ull,18295873620410370ull,13816467411698177ull,13816467545916193ull,3659252006701092ull,3659252140918820ull,1000562027921702ull,1000562162139430ull,11540474582007840ull,11540474582007840ull,83648684977815840ull,11540474582007840ull,11540474582007840ull,83648684977815840ull,3765639152421920ull,3765639286639648ull,144396671693816356ull,144502242124169764ull,3765355688840736ull,3765355823058464ull,18331066467090444ull,18331066601308172ull,5435986563629057ull,5435986563629057ull,5435986697847841ull,914793676406786ull,914793810690050ull,13863484418752709ull,31877883062452429ull,859822387888420ull,859822522106148ull,21726566929138214ull,21726567063355942ull,108368704156205088ull,108368841729376288ull,20571896915427616ull,56600694068609312ull,144396766149476388ull,144467135296307494ull,72339623669399840ull,72339623669399840ull,108375017892348192ull,1443109011522592ull,1444208523150368ull,1444217247302688ull,288072047001888ull,288072047001888ull,288072181219616ull,5435986563629057ull,5435986563629153ull,5435986697846881ull,86412822784771073ull,86412822918988801ull,288076346163488ull,288076346163488ull,288076480381216ull,144467100533653540ull,145030050621292580ull,73500982826762528ull,73500991550914848ull,3659174702514176ull,3659174836731904ull,18858823456391212ull,844424930132006ull,844425064349734ull,72339069618618400ull,72339138472312864ull,7078660190765089ull,16085859579724321ull,81487010656681984ull,81487010790899744ull,151187822427047425ull,160195021681788417ull,161320921722848801ull,296868144750880ull,5947009286554656ull,5947009454326816ull,72908620878053412ull,72908621079380004ull,3659174701465604ull,3659174835683332ull,933211569979392ull,933211704197408ull,851022537294112ull,851057031250208ull,36879819018862896ull,36879819018862900ull,75265969706500384ull,160194721003078177ull,160194721154073121ull,3102826645946656ull,3102861207011616ull,3771875579137312ull,932387070476320ull,74703054121206048ull,72339103979413508ull,72339104113631236ull,72902023875395620ull,72902024009613348ull,75717456547546112ull,75718556193391620ull,3765286293537824ull,54887620592795854ull,318318154170400ull,3659724587302944ull,144397212960292897ull,851022134116640ull,2645460007780640ull,0ull,75716803833635616ull,74591453950519584ull,0ull,316659617234976ull,72374254393360416ull,3694359472013348ull,144431847844741152ull,3765553118314500ull,81493607739031584ull,81493607873249312ull,72345670993838112ull,72909720593104928ull,288072198009092ull,2663052462260512ull,18295874157281294ull,21673573357748230ull,162481430458138638ull,3659209795837988ull,3659209795837988ull,3665806882386222ull,147887501506872116ull,288229276631695359ull,932386936258592ull,932386936258592ull,932421430214944ull,144396731789738018ull,144396731789738018ull,144508899327607074ull,72908618789302274ull,72908618789302274ull,72908653283258662ull,20670888127496224ull,20670888261713956ull,317510037536782ull,317510171754542ull,18929192185888898ull,18929192320106626ull,13863209574334661ull,14426159661973701ull,18331066634863116ull,75717044217086980ull,75717044351304708ull,3659252006684704ull,1513821621996576ull,1513546744089632ull,1513555334022176ull,1513555485017120ull,19527876283991048ull,19527876418208776ull,3659312136225828ull,3659312136225828ull,3659346630182180ull,5436055417324545ull,72339142901516576ull,72339143035734304ull,437747495993632ull,72339624072053024ull,18946785445741570ull,18946785445741570ull,18946785579959298ull,21796731393933318ull,369436982837248ull,932387070477312ull,18964926313791690ull,76990008099078433ull,85997207488037153ull,1443521730987040ull,5946709041480224ull,19457533475291658ull,73507726059634976ull,147810535423952384ull,0ull,0ull,3695192695702820ull,9532765819109856ull,10658665861218784ull,7149029876564268ull,32525759415321350ull,296868278969120ull,3764796801942816ull,3771428365665568ull,87714644554153989ull,54887622741328078ull,296872438661408ull,37020556641436130ull,879620576510470ull,868685321339170ull,868685455556898ull,144403401873948960ull,144482566849560864ull,296872971338016ull,296873105555744ull,72381538263630112ull,73483115897028608ull,73483115898142720ull,439805322199086ull,72363259017036076ull,1000557864026638ull,149005828967236128ull,149005829101453856ull,72339104113631268ull,314533608423712ull,314533746835744ull,3765553118314500ull,3765552581509412ull,0ull,36312471018930464ull,36312471023124774ull,317218239823904ull,3659724453085216ull,144397212826075169ull,75828988315959584ull,3771875579137312ull,3694359203577908ull,144502216320745764ull,72374254124924972ull,296906928431904ull,296906928431906ull,3674744692421410ull,74626603964956714ull,146754566160777258ull,20109527716267024ull,938984006025222ull,36967781024989190ull,36967815518957862ull,144966210093449254ull,180995007112413222ull,199079774500290870ull,72345670983352352ull,72354467076374816ull,72354501570330912ull,316736926646784ull,316737060864544ull,75769550393573408ull,75769619247267872ull,0ull,0ull,18401976494653570ull,0ull,22905576122024066ull,72989980437317664ull,72989985067829280ull,72989986275788832ull,404629944860704ull,974176968049184ull,190125361502159402ull,18295873486192642ull,18295873620410370ull,90353468128100366ull,90371060448362542ull,147810372047359008ull,147810372181576736ull,183839186380475440ull,387307871928516ull,18401706515693774ull,4873035536465952ull,5442588062581026ull,2663092861796386ull,3789027396813090ull,3789027531030818ull,387028095074432ull,18964376692195468ull,144502216338702468ull,387028898807840ull,393625968574752ull,72451254567567648ull,36316873360408864ull,36316873494626592ull,281480077000736ull,3674705300030752ull,3764736940310528ull,3764737074528256ull,145563139837068834ull,956644508320288ull,288072046477600ull,296868139499808ull,75802565741646624ull,324098232156194ull,36352895385403442ull,3659174697795620ull,3659175100448804ull,3659252006682628ull,3659252006682628ull,19527395230876906ull,21779195044580554ull,10115508051444768ull,15604273855332385ull,15604273989550369ull,72339069627007492ull,72343467807736580ull,72343467941953824ull,72343468076171552ull,144403264436044064ull,144473633314439456ull,144473629022617888ull,1443538509235232ull,1461143982900512ull,323806174380032ull,296872570782048ull,18381674200961514ull,54410471220589038ull,10080332269290272ull,10115516775596832ull,351913262451750ull,144467135832931622ull,4351869841834038ull,5365616880386849ull,332748979962144ull,145081109196701984ull,72345705343099136ull,72495239058694432ull,72908623084265504ull,72908631808418336ull,402971586200832ull,402980310353152ull,938987227250720ull,938987361468704ull,851026294865952ull,851026430132512ull,72339073846476800ull,72339074047830304ull,3764728359354368ull,3771334010601474ull,147810397582263808ull,148373347669902848ull,144432414930764288ull,144432415064982048ull,18946819939705130ull,1443384157883392ull,148380263113032232ull,0ull,457397407580192ull,457397545992992ull,72345666629665056ull,72345666629665056ull,72908616784412960ull,281475521970176ull,285873702699008ull,317209784090624ull,72345671125958944ull,72339069618634756ull,288106742427680ull,288106742427680ull,288106893422890ull,0ull,323808461324582ull,323808461324582ull,3674705434247456ull,3665772439142688ull,3674570142777632ull,75822906638170430ull,3765312600224062ull,75723366543130912ull,148563818715812130ull,94371118383182122ull,21709651067339824ull,3772175958999558ull,941187324248352ull,941187324248352ull,947819156406560ull,199009414211829764ull,199009414211829764ull,199079783090225462ull,72343467665131526ull,72343469812615174ull,108937415943522606ull,18295873502969870ull,18295873502969870ull,18295873637187598ull,4257309559619584ull,4257309693837568ull,64ull,844425334882498ull,3659243416748032ull,3659243416748032ull,3659243550965796ull,1108308796703744ull,10115508185662496ull,3102822350979360ull,3102856844939552ull,2548805930582304ull,2548840424538400ull,0ull,387577985171584ull,18401976494653570ull,192ull,31947547463385294ull,21691238541459462ull,72343467665129476ull,72343467799347236ull,932385862534144ull,932454716228608ull,72345670983352608ull,72495204698947872ull,21796731528151046ull,147810388996521986ull,147810389130739754ull,3764797338288132ull,21779195981987860ull,147810535423952384ull,19457533475291658ull,20582857671966722ull,20582857806184706ull,1443109279958016ull,13827535574401569ull,13827535708750369ull,394312396308768ull,394604588302624ull,437747361775904ull,3765286159254528ull,1513478024071168ull,18295882076127234ull,148940695669834272ull,859858895638816ull,859996334592290ull,1000733957165346ull,2663017968304416ull,36879829756281094ull,36915564019450678ull,296872434467104ull,296872837120288ull,9891206603473540ull,9902201853969284ull,40855665949802755ull,41418616037442307ull,914793810690048ull,90353743006008324ull,90353743140226060ull,72341268650262796ull,932387473129504ull,939019036852512ull,879620710728198ull,3659174836731936ull,75265969710694688ull,3102863355543840ull,938984140243232ull,3666321657594144ull,146725978856358177ull,1513555485017144ull,18964926448009418ull,967576005967906ull,316664583290912ull,32525759549539078ull,296873105555744ull,3765561708249604ull,184408733437218110ull,3674705434248480ull,144439012134748704ull,147950852273881120ull,147809573217010176ull,21780028402516992ull,21709660193113088ull,21709659656766464ull,3665946654282032ull,75723538610786610ull,144473768605909792ull,3665771901223200ull,147810131697013552ull,3765690557334560ull,90353468128103424ull,90389477268196352ull,146127870584947200ull,933005545769992ull,148450185527769021ull,165894864306373632ull,932386936258562ull,932386936258562ull,932421430214690ull,144471429865144352ull,144473628888400160ull,144473629022617888ull,72902019572039690ull,108930816591003658ull,108930816725222186ull,7635008743276544ull,8760908784861184ull,3698826103750656ull,3698826103750656ull,3698826237968384ull,19474627529015808ull,19475727174861312ull,4859841394835456ull,4862040552308736ull,148975029471412224ull,4789473195851776ull,1449706085483520ull,1449706219701248ull,18295873502969868ull,18295873637187596ull,296868140548352ull,297005579501824ull,367374457897216ull,19458615645634568ull,19458615779852296ull,859824535372034ull,859824669589794ull,3765278509384736ull,288072046477312ull,288072046477312ull,288072180695328ull,281479615610880ull,281479615611136ull,288076819595520ull,288072046477568ull,369435909095616ull,369435909095616ull,932387070476492ull,9499780501733380ull,9499780501733380ull,10069327659139332ull,369435909096448ull,18419637400175616ull,369436982837248ull,932387070476288ull,72339074047803396ull,296872434467616ull,296872434471714ull,296906928427810ull,162488027397619712ull,162488577287651616ull,510174739628032ull,1070924325454080ull,288072046490113ull,851056493867553ull,1514577956242952ull,153439605058765312ull,153439605192983040ull,18302470572740868ull,18302505066696972ull,9447003907949056ull,11769722355843616ull,18894033883496964ull,23398183401423398ull,21691234380678144ull,21691234514895872ull,3701789362815488ull,3701789362815488ull,3701789497033248ull,1449998144307200ull,1449998144307200ull,1449998278524960ull,72339069551511562ull,72339069752838154ull,281475791454208ull,281475791454208ull,281475925671936ull,1530589981245732ull,2093540068884772ull,21743941950996492ull,844424932294784ull,844425066512516ull,4873036610207776ull,72374872600215584ull,3659174699434180ull,3659174833651908ull,3887873123221504ull,4450823210860800ull,3659312271458304ull,3659312271458304ull,3659312271458304ull,1125899906842624ull,21673573209899041ull,21680204807704865ull,3701514484908548ull,3701514620174852ull,144502783155831296ull,144502783155831296ull,144502783290049024ull,848857336393986ull,848857336393986ull,851056493867298ull,288147745276194ull,851097832915234ull,351844393025568ull,27443814660636836ull,18863221486125078ull,54892018639306774ull,288106558788384ull,323823928869152ull,2645992621998368ull,1974725032018442ull,1974725166236170ull,18302470572736558ull,18302472854437934ull,22839064138875400ull,22839064273093130ull,144471429862785056ull,1413971954434052ull,1407418101662240ull,1407418101662240ull,19428413900727072ull,162481980081832160ull,162481980216049896ull,37999124138688570ull,851022134116666ull,36961184089440314ull,18296431982936620ull,21674131687768612ull,144509397774512160ull,3701540658393120ull,18874813737074976ull,323841474703394ull,36873222150422554ull,22272601288150016ull,21744492381536896ull,516777983410466ull,516777987604770ull,1079728075247906ull,144467860743127044ull,144467860743127044ull,144503071321228292ull,27450412198002690ull,28013362151424002ull,28013362285642242ull,19006162292703492ull,19014958519943460ull,18858823456653326ull,162974011533164558ull,163044380411559950ull,64ull,64ull,18367067000488136ull,144467032082874656ull,369985664928768ull,369985664928768ull,369985799146496ull,371709020537120ull,371709154754850ull,851022268334880ull,851056762295072ull,23925373020406272ull,3695261012527616ull,3695261146745344ull,847723470258176ull,847723470258176ull,882907976564744ull,2533833141470208ull,2533893266293760ull,2533893400511488ull,2536307037831682ull,2536307172049410ull,851026831737088ull,72908621003886848ull,88136959523815425ull,88136959658033153ull,18861027362865680ull,18896211869172272ull,21680170276520708ull,21750539423351556ull,288175394140960ull,288175528358688ull,3665811370672928ull,3666361126486816ull,317278226762784ull,18865420643598374ull,21691234246509572ull,438292962083872ull,2535512468357152ull,7039112632598561ull,7039112834453793ull,1548730982482944ull,144522574349533952ull,149026175184864000ull,144522557174383104ull,144522565898535424ull,288072587542816ull,288072789917984ull,18402011003228686ull,18402011137978926ull,3662026967630880ull,18333807056785960ull,283708762366240ull,438361681577248ull,3699590473777664ull,144473633385742624ull,932412706062346ull,932412706062346ull,18986393801916442ull,162974054482837536ull,162974054482837536ull,162974054617056034ull,72339138606548992ull,72339138606549024ull,72374872868736032ull,18858823725088778ull,18317868013715712ull,3659178992205888ull,3659178992238656ull,3729547871748556ull,288076341444896ull,288077012533536ull,18858823439613966ull,18296491961566400ull,18366860839961796ull,851090987811104ull,851090987811108ull,90353472431456512ull,13792278757769217ull,13792278925541409ull,296868139499808ull,296872568684832ull,281475582787776ull,281475717005536ull,932386936258624ull,932387070476352ull,1495335815955456ull,159033370448760837ull,159033370851422245ull,851021999898880ull,851022134120736ull,369505702331392ull,369505702331392ull,18383904346031104ull,18383903272291328ull,54384044271534368ull,422216768422016ull,991764462699136ull,332623779004672ull,332623913222432ull,281474985099264ull,19986922512322568ull,22273941881491464ull,18373526633317632ull,18883083696603424ull,144471464624132384ull,21673573345165316ull,148373132923651584ull,72902569462071300ull,3767030939988224ull,73009771349868800ull,851056359649568ull,36879855526097186ull,36879855930323250ull,21673573609407492ull,2570177283703808ull,938983066502144ull,72374322844419072ull,0ull,0ull,2610827276189988ull,146754583639622670ull,12673658250069024ull,288106410410272ull,18295908517019780ull,3729543575733248ull,371635072336168ull,845524443856904ull,288106561934112ull,922114870747938ull,3906359331507252ull,144438479021932564ull,9288682821386240ull,29695653177733640ull,288072051720480ull,144502766076297728ull,3659277910704148ull,3659174702481408ull,3736141187514400ull,18946785445740576ull,18946785445740576ull,18946790143361312ull,18295873503920132ull,18858827752308740ull,163009200334471172ull,90353471886196736ull,90353471886196736ull,126980403901760012ull,299071730352160ull,862021817991456ull,18295882076127246ull,18295882076127246ull,18295884358877230ull,0ull,387577848856704ull,18403076006281348ull,281556581089284ull,18331689352692228ull,351845065228288ull,369437385490432ull,1407374883586052ull,1970324971225124ull,72339073376714784ull,72917417164013856ull,3659243416748032ull,3659243819401220ull,0ull,18383869986283531ull,369471480987936ull,296872434467104ull,296906928423200ull,72339069752836110ull,72339069081747460ull,72339069752836100ull,281474976710656ull,17169974015590401ull,281474993619072ull,144467031948394624ull,281479271677984ull,72339073510932512ull,144432697863832064ull,144432697998049792ull,1408268238867968ull,1408268238867968ull,2006402698595844ull,1407452192982528ull,1407452192982528ull,1407452327200288ull,75769550527791136ull,21163479675175456ull,216496726509355296ull,153454998355772160ull,281474976728064ull,352462332578816ull,12807111675248672ull,281474976710848ull,18295942878856392ull,297005712671008ull,72339069752836132ull,317552970517536ull,3676809832989188ull,3665806261653792ull,3665772782059808ull,72345700645470496ull,72345666830991392ull,4299127111291424ull,1407374883553280ull,165823997295468548ull,165894366173868068ull,844496200795180ull,351914991551524ull,13897861470756900ull,18858825587097634ull,18865422656864818ull,3659174831489060ull,281509470679072ull,844464255926560ull,144432427413029668ull,370266045759492ull,3765552581509412ull,54894217662562510ull,36897482474520866ull,72374309993054212ull,68440211654180871ull,14531150710047236ull,282127945976868ull,18383912801732612ull,18383912801732614ull,27567171490089494ull,144414289884481568ull,144414289884481568ull,144519860348389408ull,72057594105038858ull,72057594105038858ull,90916417678870542ull,299140445636896ull,299140579920160ull,9429411721904352ull,27448208277897442ull,18295873486192836ull,18858823439614662ull,3659245564231684ull,3659245564231684ull,3681235931004932ull,19439438861959174ull,19439438996176902ull,281547991155748ull,281548125389860ull,369436982837248ull,369437385491456ull,283815734935840ull,283815869153568ull,288213915664672ull,144396680250130432ull,144503058001232401ull,181023611628163072ull,3659179260674049ull,8162779022262273ull,21673573206753294ull,21673573340971022ull,545376056705024ull,369436982837248ull,144484625193435136ull,285877318189248ull,18314290305959940ull,1976992774766592ull,1976992774766592ull,1976992774766848ull,72339073913585924ull,72339074047803652ull,281475580708900ull,72339104381028404ull,13792273864065313ull,13792273998283041ull,20547712357240870ull,437610058088736ull,13948546243888129ull,14018915123397633ull,316749576667392ull,144431937786740992ull,281544635711776ull,281544635711776ull,282025470722084ull,283708561031456ull,72339112165646336ull,56635895620567328ull,13939612913238305ull,3695209875572004ull,7149064236302636ull,1974725166236170ull,288145196187936ull,3664467041190944ull,3694789002350080ull,162411061715402978ull,3808850147836192ull,90353536981794852ull,3102890667278624ull,31877591021323405ull,4378395559899424ull,844459826745376ull,844459826745378ull,844459960971554ull,3695072202753024ull,144397221583782400ull,18298109503877674ull,40286931111707670ull,18929230990414116ull,72339107871207460ull,914794884431886ull,369471480987744ull,387054972239872ull,387055106457600ull,22835508056948737ull,23397684933037583ull,19091989700083712ull,4299127111291440ull,369480138031200ull,7109580301076144ull};
