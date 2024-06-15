

#include "cg_local.h"

#ifdef USE_WEAPON_ORDER


int weaponOrder[WP_NUM_WEAPONS]; 
int weaponRawOrder[WP_NUM_WEAPONS]; 
int NextWeapon (int curr);

int RateWeapon (int weapon) 
{ 
  weapon--; 

  if (weapon > 8 || weapon < 0) 
    return 0; //bad weapon 

  return weaponOrder[weapon]; 
}

extern int weaponOrder[WP_NUM_WEAPONS]; 
extern int weaponRawOrder[WP_NUM_WEAPONS]; 

int contains(int *list, int size, int number) 
{ 
  int i; 

  for (i = 0; i < size; i++) 
    if (list[i] == number) return 1; 

  return 0; 
} 


void UpdateWeaponOrder (void) 
{ 
  char *order = cg_weaponOrder.string; 
  char weapon[3]; 
  int i, start; 
  int tempOrder[WP_NUM_WEAPONS]; 
  int weapUsed[WP_NUM_WEAPONS]; 
  int temp; 

  weapon[1] = '\0'; 
  memset(tempOrder, 0, sizeof(tempOrder)); 
  memset(weapUsed, 0, sizeof(weapUsed)); 

  i = 0; 
  while (order != NULL && *order != '\0' && i < WP_NUM_WEAPONS) 
  { 
    weapon[0] = *order; 
    order++; 

    if (*order != '\\' && *order != '/') 
    { 
      weapon[1] = *order; 
      weapon[2] = '\0'; 
      order++; 
    } else { 
      weapon[1] = '\0'; 
    } 

    if (*order != '\0') 
      order++; 

    temp = atoi( weapon ); 
    if (temp < 1 || temp > WP_NUM_WEAPONS) 
    { 
      CG_Printf( "Error: %i is out of range. Ignoring..\n", temp ); 
    } 
    else if ( contains( tempOrder, sizeof(tempOrder)/sizeof(tempOrder[0]), temp ) )

    { 
      CG_Printf( "Error: %s (%i) already in list. Ignoring..\n",
        (BG_FindItemForWeapon( temp ))->pickup_name, temp );

    } else { 
      tempOrder[i] = temp; 
      weapUsed[temp - 1] = 1; 
      i++; 
    } 
  } 

  //error checking.. 
  start = 0; 
  for (i = 0; i < WP_NUM_WEAPONS - 1; i++) 
  { 
    if (weapUsed[i]) 
      continue; 
    CG_Printf( "Error: %s (%i) not in list. Adding it to front of the list..\n",
      (BG_FindItemForWeapon( i + 1 ))->pickup_name, i + 1 );

    weaponRawOrder[start++] = i + 1; 
  } 
  //build the raw order list 
  for (i = start; i < WP_NUM_WEAPONS; i++) 
    weaponRawOrder[i] = tempOrder[i - start]; 

  //built the remaping table 
  for (i = 0; i < WP_NUM_WEAPONS; i++) 
    weaponOrder[weaponRawOrder[i] - 1] = i + 1; 

}

//</WarZone>
//<WarZone> 
int NextWeapon (int curr) 
{ 
  int i; 
  int w = -1; 

  for (i = 0; i < WP_NUM_WEAPONS; i++) 
  { 
    if (weaponRawOrder[i] == curr) 
    { 
      w = i; 
      break; 
    } 
  } 

  if (w == -1) 
    return curr; //shouldn't happen 

  return weaponRawOrder[(w + 1) % WP_NUM_WEAPONS]; 
} 

int PrevWeapon (int curr) 
{ 
  int i; 
  int w = -1; 

  for (i = 0; i < WP_NUM_WEAPONS; i++) 
  { 
    if (weaponRawOrder[i] == curr) 
    { 
      w = i; 
      break; 
    } 
  } 

  if (w == -1) 
    return curr; //shouldn't happen 

  return weaponRawOrder[w - 1 >= 0 ? w - 1 : WP_NUM_WEAPONS - 1]; 
} 

#endif

#ifdef USE_3D_WEAPONS

void hud_weapons(float x, float y, weaponInfo_t *weapon) {
  vec3_t		    angles;
  vec3_t		    origin;
  float         rotation;
  refdef_t		  refdef;
  //refEntity_t		hand;
	refEntity_t		ent;
  refEntity_t   barrel;
  float         w = 48, h = 48;
  VectorClear( angles );
  origin[0] = 90;
  origin[1] = 20;
  origin[2] = 10;
  rotation = ( cg.time & 4095 ) * 40 / 4096.0;
  if(rotation <= 20) {
    angles[YAW] = 270 + rotation;
  } else {
    angles[YAW] = 270 + (40 - rotation);
  }
	if ( !cg_draw3dIcons.integer || !cg_drawIcons.integer ) {
		return;
	}
  
  // dont draw world if model is missing
  if(!weapon->weaponModel) {
    return;
  }
  
  //memset( &hand, 0, sizeof( hand ) );
  //VectorCopy( origin, hand.origin );
  //CG_PositionEntityOnTag( &gun, hand, hand->hModel, "tag_weapon");

	memset( &ent, 0, sizeof( ent ) );
	AnglesToAxis( angles, ent.axis );
  VectorSubtract(origin, weapon->weaponMidpoint, ent.origin);
	//VectorCopy( weapon->weaponMidpoint, ent.origin );
	ent.hModel = weapon->weaponModel;
	ent.customSkin = 0;
	ent.renderfx = RF_NOSHADOW;		// no stencil shadows

	CG_AdjustFrom640( &x, &y, &w, &h );
	memset( &refdef, 0, sizeof( refdef ) );
	refdef.rdflags = RDF_NOWORLDMODEL;
	AxisClear( refdef.viewaxis );
	refdef.fov_x = 30;
	refdef.fov_y = 30;
	refdef.x = x;
	refdef.y = y;
	refdef.width = w;
	refdef.height = h;
	refdef.time = cg.time;

	trap_R_ClearScene();
	trap_R_AddRefEntityToScene( &ent );
  if(weapon->barrelModel) {
    memset( &barrel, 0, sizeof( barrel ) );
    angles[YAW] = 0;
		angles[PITCH] = 0;
		angles[ROLL] = 0;
    AnglesToAxis( angles, barrel.axis );
  	VectorCopy( origin, barrel.origin );
  	barrel.hModel = weapon->barrelModel;
  	barrel.customSkin = 0;
  	barrel.renderfx = RF_NOSHADOW;		// no stencil shadows
    CG_PositionRotatedEntityOnTag( &barrel, &ent, weapon->weaponModel, "tag_barrel" );
    AxisCopy( ent.axis, barrel.axis );
    trap_R_AddRefEntityToScene( &barrel );
  }
	trap_R_RenderScene( &refdef );
}
#endif
