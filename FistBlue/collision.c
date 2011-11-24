/*
 *  collision.c
 *  GLUTBasics
 *
 *  Created by Ben on 20/10/10.
 *  Copyright 2010 Ben Torkington. All rights reserved.
 *
 */

#include "sf2types.h"
#include "sf2macros.h"
#include "sf2const.h"

#include "structs.h"
#include "player.h"

#include "lib.h"
#include "rules.h"
#include "particle.h"
#include "actions_198a.h"
#include "gfxlib.h"
#include "sound.h"


#include "playerstate.h"
#include "reactmode.h"
#include "actions.h"
#include "collision.h"

extern struct game g;

/* globals */
short hitresult[5];
//HitBoxAct *g_hitbox;		/* %a3 */
//HitBoxAct *g_hitbox4;

short g_d5; // XXX

static void set_blockstun_react(Player *vict);

static void _CDCheckPlayer(Player *ply, Player *vict);						/* 7cf38 */
static void _CDSpecialReactMode(Player *ply, Player *vict, const HitBoxAct *a3);	/* 7d02e */
static void _CDTurnToFaceMe(Player *ply, Player *vict);						/* 7d0a8 */

static int lookup_damage_and_score(Player *ply, Player *vict, const HitBoxAct *a3);	/* 7d378 */
static int damage_multiplier(Player *vict, int d6);								/* 7d40e */
static short randomize_damage(Player *ply,  int damage, const HitBoxAct *a3);			/* 7d476 */
static void _CDStartAction38Vict(Player *ply);		/* 0x7d720  something to do with falling over */
static void _CDKillDecor(Player *a2, Object *a6);								/* 7e39e */
static void _CDDecorSoundPts(Object *a6);				/* make the sound, reward points */
static short _CDPushOverlap(Player *a2, Object *a6);							/* 7e460 */

static const HitBox *_CDGetHitBoxHead(Object *obj);
static const HitBox *_CDGetHitBoxBody(Object *obj);
static const HitBox *_CDGetHitBoxFoot(Object *obj);
static const HitBox *_CDGetHitBoxWeak(Object *obj);
static const HitBox *_CDGetPushBox(Object *obj);
static const HitBoxAct *get_active_hitbox(Object *obj);

static void mac_stunme3(Object *proj);          /* 7d7d4 */
static void mac_stun2005(Player *ply, Player *opp);
static int sub_7d4fa(Player *vict, const HitBoxAct *a3);
static void sub_7e314(void);
static void set_reel_react(Player *vict);
static void start_timewarp_action (Player *vict);

/* main entry to check collisions between players */
void CDCheckPlayers(void) {       /* 7cee0, called from fighttick. */
    debughook(6);
    if(g.PlayersThrowing) { return; }
    if(g.Player1.CompImmune) {g.Player1.CompImmune--;}
    if(g.Player2.CompImmune) {g.Player2.CompImmune--;}
	
    if(g.Player1.Human || g.DebugNoCollide==0) {
        _CDCheckPlayer(PLAYER1, PLAYER2);
    }
	
    if(g.Player2.Human || g.DebugNoCollide==0) {
        _CDCheckPlayer(PLAYER2, PLAYER1);
    }
}
void CDCheckProjectile(Object *obj, int d7) {   /* 0x7d0c0 check for projectile collision */
	/* d7 as far as I can tell is a leftover loop counter, hmm */
	/* d5 is also significant, but not sure why yet */
    Player *ply, *opp;
	const HitBoxAct *a3;
    short damage;
    
    if(obj->exists != 1) { return; }
	
	/* XXX */
//    if((g.libsplatter + d7) & 1) {
//        projectile_to_projectile((Player *)obj);     /* check for collision with opponents projectile */
//        return;
//    }
    ply = obj->Owner;
    opp = ply->Opponent;
    
    if(opp->exists != 1) { return; }
    if(g.PlayersThrowing || opp->CompImmune || opp->TCollDis || opp->Invincible) {
        return;
    }
    if(ply->Human == 0 && g.DebugNoCollide)  { return; }
	a3 = get_active_hitbox(obj);
    if(a3==0)         { return; }       /* sets hitbox in a3 */
    if(check_main_hitboxes(obj, (Object *)opp, a3)==0) { return; } /* return if no collision */
    
    /* projectile has collided */
    
    opp->NextReactMode2 = a3->ReactMode2;
    ply->Timer2 = opp->Timer2 = 14;             
    opp->Direction = obj->Flip;
    
	
    damage=lookup_damage_and_score(ply, opp, a3);
    if(sub_7d4fa(opp, a3) == 0) {
        damage=damage_multiplier(opp, damage);
        damage=randomize_damage(opp,damage, a3);   
        damage=diminishing_damage(damage, opp);
        
        if(g.GPHitBlocked) {
            damage /= 4;
            if (damage == 0) { damage = 1; }
        }
        
        opp->Energy -= damage;
        if(opp->Energy < 0) {
            opp->Energy      = -1;
            g.GPHitBlocked   = 0;
            opp->BlockStun   = 0; 
        }
    }
    opp->x0071 = 1;
    
    set_newreact(opp, ply, a3);       
    make_collision_sound(opp, a3);
    
    if(opp->Energy < 0 || g.GPHitBlocked == 0) {
        _CDStartAction38Vict(opp);
    }
    obj->Energy = -2;
    mac_stunme3(obj);
    if(opp->BlockStun || g.OnBonusStage) { return; }
    QueueEffect(g.GPPointsReward, ply->Side);
}

/* check for collision between projectile and enemy projectile,  supports only one projectile per player
 bound to be completely different in hacks with mutli fireballs */

void projectile_to_projectile(Player *obj) {				// 7d1c0
    Object *enemyProjectile;
    const HitBox *a3,*a4;
	
    if(!(a3=_CDGetPushBox((Object *)obj)))		{ return; }
    if(obj->Owner->Opponent->Projectile==0)		{ return; }
    enemyProjectile = (Object *)obj->Owner->Opponent->Projectile;
	if(!(a4=_CDGetPushBox(enemyProjectile)))	{ return; }
    if(check_hitbox_overlap((Object *)obj, (Object *)obj->Opponent,(HitBoxAct *)a3,a4)) {
        obj->Energy = -1;
        enemyProjectile->Energy = -1;
    }
}


/* d6 = sub_7d378 (Player *a6, Player *a2)  calculate damage of hit to victim 
 and score reward                    */

static int lookup_damage_and_score(Player *ply, Player *vict, const HitBoxAct *a3) { /* 7d378 */
	
	static char data_99324[16][32] = {
		{   4,   5,   5,   5,   5,   6,   6,   6,   6,   6,   6,   7,   7,   7,   7,   7,   7,   8,   8,   8,   8,   8,   8,   9,   9,   9,   9,   9,  10,  10,  10,  12,  },
		{   5,   6,   6,   6,   6,   7,   7,   7,   7,   7,   7,   8,   8,   8,   8,   8,   8,   9,   9,   9,   9,   9,   9,  10,  10,  10,  11,  11,  11,  12,  12,  14,  },
		{   5,   6,   6,   7,   7,   7,   8,   8,   8,   8,   9,   9,   9,   9,  10,  10,  10,  11,  11,  11,  12,  12,  12,  13,  13,  13,  14,  14,  15,  15,  16,  18,  },
		{   7,   8,   8,   9,   9,   9,  10,  10,  10,  11,  11,  11,  11,  12,  12,  12,  12,  13,  13,  13,  14,  14,  14,  15,  15,  16,  16,  17,  17,  18,  18,  20,  },
		{   8,   9,  10,  10,  11,  11,  12,  12,  12,  13,  13,  13,  13,  14,  14,  14,  14,  15,  15,  15,  16,  16,  16,  17,  17,  18,  18,  19,  19,  20,  20,  23,  },
		{  10,  11,  12,  12,  13,  13,  14,  14,  14,  15,  15,  15,  15,  16,  16,  16,  16,  17,  17,  17,  18,  18,  18,  19,  19,  20,  20,  21,  21,  22,  22,  24,  },
		{  10,  13,  14,  14,  15,  15,  16,  16,  16,  17,  17,  17,  17,  18,  18,  18,  18,  19,  19,  19,  20,  20,  20,  21,  21,  22,  22,  23,  23,  24,  24,  26,  },
		{  12,  15,  16,  16,  17,  17,  18,  18,  18,  19,  19,  19,  19,  20,  20,  20,  20,  21,  21,  21,  22,  22,  22,  23,  23,  24,  24,  25,  25,  26,  26,  28,  },
		{  12,  13,  14,  15,  16,  16,  17,  17,  18,  18,  19,  19,  20,  20,  22,  22,  22,  23,  23,  24,  24,  25,  25,  26,  26,  27,  28,  29,  30,  31,  32,  34,  },
		{  15,  16,  17,  18,  19,  19,  20,  20,  21,  21,  22,  22,  23,  23,  24,  24,  24,  25,  25,  26,  26,  27,  27,  28,  28,  29,  30,  31,  32,  33,  34,  36,  },
		{  15,  16,  17,  18,  19,  19,  20,  20,  21,  21,  22,  22,  23,  23,  24,  24,  24,  25,  25,  26,  26,  27,  27,  28,  28,  29,  30,  31,  32,  33,  34,  36,  },
		{  17,  18,  19,  20,  21,  21,  22,  22,  23,  23,  24,  24,  25,  25,  26,  26,  26,  27,  27,  28,  28,  29,  29,  30,  30,  31,  32,  33,  34,  35,  36,  38,  },
		{  18,  19,  20,  21,  22,  23,  23,  24,  24,  25,  25,  26,  26,  27,  27,  28,  28,  29,  29,  30,  30,  31,  31,  32,  32,  33,  34,  35,  36,  37,  38,  40,  },
		{  22,  23,  24,  25,  26,  27,  27,  28,  28,  29,  29,  30,  30,  31,  31,  32,  32,  33,  33,  34,  34,  35,  35,  36,  36,  37,  38,  39,  40,  41,  42,  44,  },
		{  26,  27,  28,  29,  30,  31,  31,  32,  32,  33,  33,  34,  34,  35,  35,  36,  36,  37,  37,  38,  38,  39,  39,  40,  40,  41,  42,  43,  44,  45,  46,  48,  },
		{  30,  31,  32,  33,  34,  35,  35,  36,  36,  37,  37,  38,  38,  39,  39,  40,  40,  41,  41,  42,  42,  43,  43,  44,  44,  45,  46,  47,  48,  49,  50,  52,  },
	};
	
	
	static const u16 data_99544[16]={
		0x2002, 0x2002, 0x2002, 0x2004, 0x2004, 0x201c, 0x201e, 0x201e, 
		0x2006, 0x2006, 0x2006, 0x2006, 0x2006, 0x2008, 0x2008, 0x2020,  
	};
	static const u16 data_99566[4][8] = {
		{ 0x0001, 0x0014, 0x000a, 0x003c, 0x001e, 0x0000, 0x0000, 0x0000,  },
		{ 0x0001, 0x001a, 0x000d, 0x0050, 0x0028, 0x0000, 0x0000, 0x0000,  },
		{ 0x0001, 0x001e, 0x000f, 0x0064, 0x0032, 0x0000, 0x0000, 0x0000,  },
		{ 0x0002, 0x0028, 0x001e, 0x0064, 0x004b, 0x0000, 0x0000, 0x0000,  },
	};
	/* next address 000995a6 */
	
	static const u16 data_995a6[4]={0x200a, 0x200a, 0x2022, 0x2022,  };
	
	
    g_d5=vict->MoreBoxes[vict->Difficulty];
    if((a3->Damage & 0x7f) < 0x20) {
        g.GPPointsReward = data_99544[ a3->Damage ];
        return data_99324[ a3->Damage ][ ply->Difficulty ];
    } 
	g.GPPointsReward = data_995a6[ a3->Damage - 0x20 ];
	
	if(ply->Energy < data_99566[ a3->Damage - 0x20 ][ 1 ]) {
		return data_99566[ a3->Damage - 0x20 ][2];
	}
	if(ply->Energy >= data_99566[ a3->Damage - 0x20 ][ 3 ]) {
		return data_99566[ a3->Damage - 0x20 ][4];
	}
	return (vict->Energy - (vict->Energy >> data_99566[ a3->Damage - 0x20 ][0]));
}
static int damage_multiplier(Player *vict, int d6) {   /* 7d40e */
    int xx;
    if(g.GPHitBox4Hit) {
        g.Diff_WeakBoxCnt++;
        xx=vict->ActionScript->YOffset & 0xff; /* XXX variable sharing nastiness workaround */
    } else {
        xx=vict->HitBoxUnused[g.GPHitBoxHit / 2];		// unused, always 0
    }
    switch (xx) {
		case 2:
			d6 += d6/2;
			break;
		case 4:
			d6 *= 2;
			break;
		case 6:
			d6 *= 3;
			break;
		case 8:
			d6 += d6 / 4;
			break;
	}
    return d6;
}
static short randomize_damage(Player *ply,  int damage, const HitBoxAct *a3) {     /* 7d476 */
    int d2;
	static const signed char data_93300[9][32] = {		// XXX redo as signed char
		{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  },
		{   1,   2,   3,   1,   2,   1,   2,   1,   1,   1,   1,   2,   1,   1,   1,   1,   2,   1,   3,   1,   3,   1,   2,   3,   1,   1,   2,   1,   1,   2,   1,   1,  },
		{   2,   1,   1,   1,   1,   1,   1,   1,   1,   3,   1,   4,   2,   2,   4,   2,   2,   1,   2,   1,   6,   1,   5,   1,   1,   1,   1,   3,   1,   1,   1,   1,  },
		{   0,   0,   0,   0,   0,  10,   0,   0,   0,   0,  10,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  15,   0,   0,   0,  },
		{   0, 246,   0,   0,   0,   0,   0,   0,   0,   0,  10,   0,   0,   0,  10,   0,   0,   0,   0,   0, 241,   0,   0,   0,   0,  15,   0,   0,   0,   0,   0, 246,  },
		{   0,  10, 241, 246,  10,   0, 241,  15,  15,  15,   0, 241,  15, 241,  10,  15, 241,   0, 241,  10, 246,  15,  15, 246, 246,  15, 241,  15, 241,  15, 241, 241,  },
		{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  10,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  },
		{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  },
		{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  },
	};
	/* next address 00093420 */
	
	
    if (ply->Energy >= 0x60) {
        d2=a3->Random1;
    } else {
        d2=a3->Random2;
    }
    
    damage += data_93300[d2][RAND32];
    if(damage <= 0) { damage = 1; }
    
    g_d5 *= damage;        /* MULU instruction! */
    g_d5 = g_d5 >> 5;
    damage -= g_d5;
    if(damage == 0) {damage = 1;}
    return damage;
}
short diminishing_damage(int damage, Player *vict) {  /* 7d4b6 */
	static const char data_93420[31]={
		24,  24,  24,  24,  24,  24,  20,  20,  20,  20,  20,  16,  16,  16,  16,  16, 
		12,  12,  12,  12,  12,   8,   8,   8,   8,   8,   4,   4,   4,   4,   4, 
	};
	
    if(vict->Energy >= 0x1f) { return damage; }
    damage -= (damage * data_93420[vict->Energy]) >> 5;
    if (damage==0) {damage = 1; }
    return damage;
}

static int sub_7d594(short d0, Player *vict) {		// 7d594
	vict->BlockStun = TRUE;
	if(d0 >= 0) {
		bump_difficulty_4816();
		return TRUE;
	}
	g.GPHitBlocked = TRUE;
	return FALSE;
}

static int sub_7d4fa(Player *vict, const HitBoxAct *a3) {		// 7d4fa
	static const signed char data_7d5b0[3][16]={
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
		{  1,  1,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0, -1, -1,  0,  0 },
		{  1,  1,  1,  0,  1,  1,  1,  0,  0,  0,  0,  0, -1, -1, -1,  0 }
	};
	
	short temp;
    if (vict->Human && vict->Airborne==AIR_ONGROUND &&
        vict->mode2 != 0x14                  &&
        vict->mode2 != PLSTAT_TUMBLE &&
        vict->BlockStun == FALSE             &&
        vict->Energy >= 0                    &&
        vict->Energy == vict->EnergyDash     &&
        vict->DizzyStun == FALSE
		) {
        if(LBRareChance()) {                
            vict->BlockStun  = TRUE;     /* 7d4da */
            g.GPHitBlocked   = FALSE;
            if(a3->Attack != 3) {
                return TRUE;
            }
            g.GPHitBlocked = TRUE;
            return FALSE;
        }
    } 
	/* 7d534 */
    g.GPHitBlocked = FALSE;
    temp = vict->ActionScript->Block;
    
    if(    a3->Attack != 3 || a3->ReactMode != RM_0x26) {
		/* 7d55c */
		
        if(a3->Attack == 4 && a3->ReactMode == RM_0x24) {
            temp=2;
        }
        temp = ((temp & 0x3) << 2) + (g.GPHitBoxHit / 2);
		
        temp =  data_7d5b0[vict->ActionScript->Block / 2][temp];
        if (temp) {
            return sub_7d594(temp, vict);
        } else {
            return FALSE;
        }
    } else {
        if(temp == 1) {
            return sub_7d594(-1, vict);
        } else {
			return sub_7d594(temp, vict);
		}
    }
}
void center_collision_coords(void) {		//7d974 checked
    g.GPCollX = g.VictimLeftEdge 
	    + ((g.GPLeftEdge - g.VictimLeftEdge) / 2);
    g.GPCollY = g.VictimTopEdge  
	    + ((g.GPTopEdge  - g.VictimTopEdge ) / 2);
}

void sub_7d74e(Player *ply, Player *opp, const HitBoxAct *a3) {
    Object *obj;
    if(obj=AllocActor()) {
        center_collision_coords();
        obj->exists = TRUE;
        obj->Sel    = SF2ACT_HITSTUN;     /* hitstuns */
        obj->XPI    = g.GPCollX;
        obj->YPI    = g.GPCollY;
        obj->Owner = ply;
        obj->Flip   = ply->Flip;
        obj->SubSel = opp->NextReactMode2;
        if(g.GPHitBlocked == 0 && opp->BlockStun) {
            obj->SubSel = 3;
            return;
        }
    } else {
        return;
    }
	
    if(ply->FighterID == FID_VEGA && a3->Damage > 128) {
		if(obj=AllocActor()) {
			obj->exists = TRUE;				// some blood from Vega's claw
			obj->Sel    = SF2ACT_VOMIT; 
			obj->SubSel = 0x8;
			obj->XPI    = g.GPCollX;
			obj->YPI    = g.GPCollY;        
			obj->Owner = ply;
			obj->Flip   = ply->Flip;
		}
    }
}
void sub_7d7fc(Player *ply, Object *obj) {		// 7d7fc
    switch(ply->Sel) {
		case 1:
		case 2:
		case 4:
			obj->SubSel = 5;
			break;
		default:
			obj->SubSel = 4;
			break;
    }
}        

static void mac_stunme3(Object *proj) {           /* 7d7d4 */
    Object *obj;
    if(obj = AllocActor()) {
        center_collision_coords();
        obj->exists = TRUE;
        obj->Sel    = SF2ACT_HITSTUN;     /* hitstuns */
        obj->XPI    = g.GPCollX;
        obj->YPI    = g.GPCollY;
        obj->Flip   = proj->Flip;   
        sub_7d7fc((Player *)proj, obj);
    }
}
static void mac_stunme2(Player *ply, Player *opp) {		//7d824
    Object *obj;
    if(obj = AllocActor()) {
        center_collision_coords();
        obj->exists = TRUE;
        obj->Sel    = SF2ACT_HITSTUN;     /* hitstuns */
        obj->XPI    = g.GPCollX;
        obj->YPI    = g.GPCollY;
        obj->Flip   = ply->Flip;       /*hmm */
        if(g.GPWasProjectile) {		/* projectile? */
            obj->Owner = ply->Owner;
            obj->SubSel = 3;
            if(opp->BlockStun) {
                sub_7d7fc(ply, obj);
            }    
        } else {
            obj->Owner = ply;
            obj->SubSel = opp->NextReactMode2;
            if(opp->BlockStun) {
                obj->SubSel = 3;
            }    
			
        }
		
    }
}
static void mac_stun_from76(Player *ply, Player *opp) {			//7d884
    Object *obj;
    if(obj = AllocActor()) {
        center_collision_coords();
        obj->exists = TRUE;
        obj->Sel    = SF2ACT_HITSTUN;     /* hitstuns */
        obj->XPI    = g.GPCollX;
        obj->YPI    = g.GPCollY;
        obj->Flip   = ply->Flip;       /*hmm */
        if(g.GPWasProjectile) {		/* projectile ? */
            obj->Owner = ply->Owner;
            obj->SubSel = 3;    
        } else {
            obj->Owner = ply;
            obj->SubSel = opp->NextReactMode2;
        }
		
    }
}
static void mac_stun2005(Player *ply, Player *opp) {		//7d8d4
    Object *obj;
    if(obj = AllocActor()) {
        center_collision_coords();
        obj->exists = TRUE;
        obj->Sel    = SF2ACT_HITSTUN;     /* hitstuns */
        obj->XPI    = g.GPCollX;
        obj->YPI    = g.GPCollY;
        obj->Owner = opp;
        obj->Flip   = ply->Flip;       /*hmm */
        obj->SubSel = 5;
    }
}

static void mac_stunhim_from76(Object *obj1, Player *vict) {		//7d908
	/* 7d884 obj1 %a6 vict %a2 */
    Object *obj2;
    if(obj2 = AllocActor()) {
        center_collision_coords();
        obj2->exists = TRUE;
        obj2->Sel    = SF2ACT_HITSTUN;		
        obj2->XPI    = g.GPCollX;
        obj2->YPI    = g.GPCollY;
        obj2->Owner = vict;
        obj2->Flip   = obj1->Flip;      
        obj2->SubSel = vict->NextReactMode2;
    }
}

static void mac_stun_oppopp(Player *ply, Player *opp) {		//7d93c checked
    Object *obj;
    if(obj = AllocActor()) {
        center_collision_coords();
        obj->exists = TRUE;
        obj->Sel    = SF2ACT_HITSTUN;     /* hitstuns */
        obj->XPI    = g.GPCollX;
        obj->YPI    = g.GPCollY;
        obj->Owner = opp->Opponent;  
        obj->Flip   = ply->Flip;       
        obj->SubSel = 2;
    }
}
/*
 Function RectsOverlap:Int(x0, y0, w0, h0, x2, y2, w2, h2)
 If x0 > (x2 + w2) Or (x0 + w0) < x2 Then Return False
 If y0 > (y2 + h2) Or (y0 + h0) < y2 Then Return False
 Return True
 End Function
 */

#pragma mark ---- HitBox Overlap Checking ----

/* hitbox overlap checker 
 *      int dunno      %d0
 *      HitBox *hit    %a3
 *      HitBox *target %a4
 *      Object *obj    %a6
 *      Object *vict   %a2
 *   R  res[]          %d3, %d4, %d5, %d6  XX may include %d2
 */

short sub_7e094(int shove_x, Object *a6, Player *vict, const HitBox *a3, const HitBox *a4) {
    short d1,d3,d4,d5,d6;
    if(a6->Flip) { shove_x = -shove_x; }
    shove_x += a6->XPI;
    g.GPLeftEdge = shove_x;			/* x0 + w0 */
	
	// %d2:
    g.VictimLeftEdge = vict->XPI + (vict->Flip ? -a4->X : a4->X) ;
								/* d2 is x2 */
	
	d4 = a3->width+a4->width;		/* d4 = w1+w2  */
	d5 = shove_x - g.VictimLeftEdge;	/* d5 = (x0+w0)-x2 */
	shove_x = d5 + d4;					/* d0 = (x0+w0)-x2+w0+w2 */
	d6 = d4;
	//printf("sub_7e094: d4 %d d0 %d ", d4, d0);
	if (shove_x > (d4 * 2) || shove_x < 0) {
		hitresult[1]=0;
		//printf("\n");
		return 0;
	}
	if (d5>=0) {
		d6=-d6;
	}
	d5 += d6;
	hitresult[4] = d5;			/* we forgot %d2, so it's hitresult[4] */
	g.GPTopEdge = d1 = a3->Y + a6->YPI;
	d3 = a4->Y + vict->YPI;
	g.VictimTopEdge = d3;
	d4 = a3->height+a4->height;
	d1 -= d3;
	d5 = d1;		// XXX never read
	d1 += d4;
	d6 = d4;		// XXX never read
	//printf("* d4 %d d1 %d ", d4, d1);
	if (d1 > (d4*2) || d1 < 0) {
		hitresult[1]=0;
		//printf("\n");
		return 0;
	}
	if (hitresult[2] < 0) {
		hitresult[3] = -hitresult[3];
	}
	hitresult[2] += hitresult[3];
	hitresult[0] = hitresult[2];
	hitresult[1] = 1;
	return 1;
}

/*check_hitbox_overlap()        0x7e082 
 *      HitBox *hit    %a3
 *      HitBox *target %a4
 *      Object *obj    %a6
 *      Object *vict   %a2
 *   R  res[]          %d3, %d4, %d5, %d6
 */


short check_hitbox_overlap (Object *obj, Object *vict, const HitBoxAct *active, const HitBox *a4) {       /* 0x7e082 */
	
    if (active->Shove >= 0) {
		return slib_check_overlap(obj,(Player *) vict, (const HitBox *)active, a4);
    } else {
        return sub_7e094(-active->Shove, obj,(Player *) vict, (const HitBox *)active, a4);
    }
}

/* slib_check_overlap()   0x7e08e
 *      HitBox *hit    %a3
 *      HitBox *target %a4
 *      Object *obj    %a6
 *      Object *vict   %a2
 *   R  res[]          %d3, %d4, %d5, %d6
 */

short slib_check_overlap(Object *obj, Player *vict, const HitBox *a3, const HitBox *a4) {		/* 7e08e */
	//printf("slib_check_overlap\n");
	return sub_7e094(a3->X, obj, vict, (HitBox *)a3, a4);
}


#pragma mark HitBox Lookup
/* used to be lookup_hitbox_8,9,10 etc. */
/* lookup for victim in %a2 */
static const HitBox *_CDGetHitBoxHead (Object *obj) {			/* 7e01c */
    if (obj->ActionScript->HB_Head) {
		return obj->HitBoxes->head+obj->ActionScript->HB_Head;
    } else {
        return NULL;
    }
}
static const HitBox *_CDGetHitBoxBody (Object *obj) {
    if (obj->ActionScript->HB_Body) {
		return obj->HitBoxes->body+obj->ActionScript->HB_Body;
    } else {
        return NULL;
    }
}
static const HitBox *_CDGetHitBoxFoot (Object *obj) {
    if (obj->ActionScript->HB_Foot) {
		return obj->HitBoxes->foot+obj->ActionScript->HB_Foot;
    } else {
        return NULL;
    }
}
static const HitBox *_CDGetHitBoxWeak (Object *obj) {
    if (obj->ActionScript->HB_Weak) {
		return obj->HitBoxes->weak+obj->ActionScript->HB_Weak;
    } else {
        return NULL;
    }
}
static const HitBox *_CDGetPushBox (Object *obj) {
    if (obj->ActionScript->HB_Push) {
		return obj->HitBoxes->push+obj->ActionScript->HB_Push;
    } else {
        return NULL;
    }
}
static const HitBoxAct *get_active_hitbox(Object *obj) {      /* 7dff2 */
    if(obj->ActionScript->HB_Active) {
        return (HitBoxAct *)obj->HitBoxes->active + obj->ActionScript->HB_Active;	
    } else {
        return NULL;
    }
}
	

static void sub_7e2a0(int d1, int d2, int d6) {
	if (d1==1) {
		d2 = -ABS(d2);
	} else {
		d2 = ABS(d2);
	}
	//sub_7e2f8(d2);
	g.Player2.XPI += d2;
	PLAYER_PUSH(d2 >= 0);
	// 7e31c 
	g.Player1.XPI -= d2;
	PLAYER_PUSH(d6 >= 0);
	
}


// sub_7e2cc is the same with a different reg, %d0
static void sub_7e2b6(int d1, int d2, int d6) {
	if (d1==1) {
		d2 = ABS(d2);
	} else {
		d2 = -ABS(d2);
	}
	//sub_7e2f8(d2);
	g.Player2.XPI += d2;
	PLAYER_PUSH(d2 >= 0);
	// 7e31c 
	g.Player1.XPI -= d2;
	PLAYER_PUSH(d6 >= 0);
	
}
static void sub_7e2e2(int d0, int d2, int d6) {
	if (d0 != 1) {
		d2=(ABS(d2));
	}
	if (d2 > 0) {
		d2=-d2;
	}
	// 7e31c 
	g.Player1.XPI -= d2;
	PLAYER_PUSH(d6 >= 0);
}
static void sub_7e274(int d0, int d2, int d6) {
	int d1;
	d1 = g.Player1.BoundCheck;
	if (d2 == 0) {
		if (g.Player1.PlatformFallDir == 0) {
			sub_7e2e2(d0,d2,d6);
			return;
		}
		d1 = g.Player1.PlatformFallDir;
	}
	if (d0 != d1) {
		return;
	}
	
	// 7e296 inlined
	if(g.Player1.YPI >= g.Player2.YPI) {
		sub_7e2a0(d1, d2, d6);
	} else {
		sub_7e2b6(d1, d2, d6);
	}
}
static void sub_7e286(int d0, int d2, int d6) {
	int d1;
	d1 = g.Player2.BoundCheck;
	if (d2 == 0) {
		if (g.Player2.PlatformFallDir == 0) {
			sub_7e2b6(d0,d2, d6);
			return;
		}
		d1 = g.Player2.PlatformFallDir;
	}
	if (d0 != d1) {
		return;
	}
	
	if(g.Player1.YPI >= g.Player2.YPI) {
		sub_7e2a0(d1, d2, d6);
	} else {
		sub_7e2b6(d1, d2, d6);
	}
}
static void sub_7e23c(int d2) {
	g.Player2.XPI += d2/2;
	g.Player1.XPI -= d2/2;
	PLAYER_PUSH(d2>=0);
}
static void sub_7e19a(int d6) {		/* resolve a ground collision between player */
	/* checked */
	short d0,d2,d3,d4;
	/* 0x7e19a */
	
	d4 = d6;
	d6=ABS(d6);
	
	d0 = 0;
	if (d6 & 0x1) {
		d0=1;
	}
	d6 >>= 1;
	if (d4 < 0) {
		d0 = -d0;
		d6 = -d6;
	}
	
	d2 = ABS(g.Player1.DeltaX.part.integer);
	d3 = ABS(g.Player2.DeltaX.part.integer);
	if (d2 <= d3) { /* 7e1c0 */
		g.Player2.XPI += d6;
		g.Player2.XPI += d0;
		g.Player1.XPI -= d6;
	} else {
		g.Player1.XPI -= d6;
		g.Player1.XPI -= d0;
		g.Player2.XPI += d6;
	}
	PLAYER_PUSH(d6<0);
}
static void sub_7e264(int d2, int d6) {
	if (g.Player1.VelX.full == 0) {
		sub_7e23c(d2);
	} else if (g.Player2.VelX.full == 0) {
		sub_7e23c(d2);
	} else {
		sub_7e19a(d6);
	}
}
static void sub_7e218 (int d2, int d6) {
	/* 7e218 resolve an in-air collision between player */
	
	int d0;
	
	if (g.Player1.BoundCheck) {
		sub_7e274(g.Player1.BoundCheck,d2,d6);
	} else if (g.Player1.PlatformFallDir) {
		sub_7e274(g.Player1.PlatformFallDir,d2,d6);
	} else if (g.Player2.BoundCheck) {
		sub_7e286(g.Player2.BoundCheck,d2,d6);
	} else if (g.Player2.PlatformFallDir) {
		sub_7e286(g.Player2.PlatformFallDir,d2,d6);
	} else {
		d0 = g.Player1.Airborne & g.Player2.Airborne;
		if (d0) {
			sub_7e264(d2, d6);
		} else {
			sub_7e23c(d2);
		}
	}
}
void sub_7e16e(int d2) {  /* collision resolution between p1 and p2 pushboxes */
	int d6;
	
	if (d2) {
		g.GPCollDetect = TRUE;
	}
	d6 = d2;
	if (d2 < -8) {
		d2 = -8;
	}
		
	if(g.Player1.Airborne || g.Player2.Airborne) {
		sub_7e218(d2,d6);
    } else {
		sub_7e19a(d6);
    }
}
int check_main_hitboxes(Object *obj, Object *vict, const HitBoxAct *a3) {         /* 0x7de5a */
    const HitBox *a4;
	
    g.GPReg1  = 0;
    g.GPHitBox4Hit = 0;
	
    if (a4=_CDGetHitBoxHead(vict)) {
        if(check_hitbox_overlap(obj, vict, a3, a4)) {
            g.GPReg1 |= 1;
			g.GPHitBoxCoords[0][0]=g.VictimLeftEdge;
			g.GPHitBoxCoords[0][1]=g.VictimTopEdge;
            g.GPHitBoxDamage[0] = ABS(hitresult[0]);
        }
    }
    if (a4=_CDGetHitBoxBody(vict)) {
        if(check_hitbox_overlap(obj, vict, a3, a4)) {
            g.GPReg1 |= 2;
			g.GPHitBoxCoords[1][0]=g.VictimLeftEdge;
			g.GPHitBoxCoords[1][1]=g.VictimTopEdge;
            g.GPHitBoxDamage[1] = ABS(hitresult[0]);
        }
    }
    if (a4=_CDGetHitBoxFoot(vict)) {
        if(check_hitbox_overlap(obj, vict, a3, a4)) {
            g.GPReg1 |= 4;
			g.GPHitBoxCoords[2][0]=g.VictimLeftEdge;
			g.GPHitBoxCoords[2][1]=g.VictimTopEdge;
            g.GPHitBoxDamage[2] = ABS(hitresult[0]);
        }
    }
    if (g.GPReg1 == 0) { return 0; }
    switch (g.GPReg1){
		case 0:
			/* can't happen, special-cased out */
			return 0;
			break;
		case 1:
			/* Hitbox 1 only */
			g.GPHitBoxHit = 0;
			g.VictimLeftEdge = g.GPHitBoxCoords[0][0];
			g.VictimTopEdge = g.GPHitBoxCoords[0][1];
			break;
		case 2:
			/* Hitbox 2 only */
			g.GPHitBoxHit = 2;
			g.VictimLeftEdge = g.GPHitBoxCoords[1][0];
			g.VictimTopEdge = g.GPHitBoxCoords[1][1];
			break;
		case 3:
			/* Hitbox 1 and 2 */
			if (g.GPHitBoxDamage[0] > g.GPHitBoxDamage[1]) {
				g.GPHitBoxHit = 0;
				g.VictimLeftEdge = g.GPHitBoxCoords[0][0];
				g.VictimTopEdge = g.GPHitBoxCoords[0][1];
			} else {
				g.GPHitBoxHit = 2;
				g.VictimLeftEdge = g.GPHitBoxCoords[1][0];
				g.VictimTopEdge = g.GPHitBoxCoords[1][1];
			}
			break;
		case 4:
			/* Hitbox 3 only */            
			g.GPHitBoxHit = 4;
			g.VictimLeftEdge = g.GPHitBoxCoords[2][0];
			g.VictimTopEdge = g.GPHitBoxCoords[2][1];
			break;
		case 5:
			/* Hitbox 3 and 1 */
			if (g.GPHitBoxDamage[0] > g.GPHitBoxDamage[2]) {
				g.GPHitBoxHit = 0;
				g.VictimLeftEdge = g.GPHitBoxCoords[0][0];
				g.VictimTopEdge = g.GPHitBoxCoords[0][1];
			} else {
				g.GPHitBoxHit = 4;
				g.VictimLeftEdge = g.GPHitBoxCoords[2][0];
				g.VictimTopEdge = g.GPHitBoxCoords[2][1];
			}
			break;
		case 6:
			/* Hitbox 3 and 2 */
			if (g.GPHitBoxDamage[1] > g.GPHitBoxDamage[2]) {
				g.GPHitBoxHit = 2;
				g.VictimLeftEdge = g.GPHitBoxCoords[1][0];
				g.VictimTopEdge = g.GPHitBoxCoords[1][1];
			} else {
				g.GPHitBoxHit = 4;
				g.VictimLeftEdge = g.GPHitBoxCoords[2][0];
				g.VictimTopEdge = g.GPHitBoxCoords[2][1];
			}
			break;
		case 7:
			/* All three */
			if (g.GPHitBoxDamage[0] > g.GPHitBoxDamage[1]) {
				if (g.GPHitBoxDamage[0] > g.GPHitBoxDamage[2]) {
					g.GPHitBoxHit = 0;
					g.VictimLeftEdge = g.GPHitBoxCoords[0][0];
					g.VictimTopEdge = g.GPHitBoxCoords[0][1];
				} else {
					g.GPHitBoxHit = 4;
					g.VictimLeftEdge = g.GPHitBoxCoords[2][0];
					g.VictimTopEdge = g.GPHitBoxCoords[2][1];
				}
			} else {
				if (g.GPHitBoxDamage[2] > g.GPHitBoxDamage[1]) {
					g.GPHitBoxHit = 4;
					g.VictimLeftEdge = g.GPHitBoxCoords[2][0];
					g.VictimTopEdge = g.GPHitBoxCoords[2][1];
				} else {
					g.GPHitBoxHit = 2;
					g.VictimLeftEdge = g.GPHitBoxCoords[1][0];
					g.VictimTopEdge = g.GPHitBoxCoords[1][1];
				}
			}
			break;
	}
	
	if(a4=_CDGetHitBoxWeak(vict)) {
		if(check_hitbox_overlap(obj, vict,a3,a4)) {
			g.GPHitBox4Hit = TRUE;
		}
	}
	return 1;
}


#pragma mark ---- ReactMode Setting ----

static void set_special_reactmode(Player *vict, Player *ply, const HitBoxAct *hbact) {	//7d64a checked
	vict->NextReactMode = hbact->ReactMode;     /* 0x7d64a */
	if (hbact->Attack == ATTACK_PRIORITY) {		
		if(vict->NextReactMode == RM_0x24) {		// 7d6a6
													/* 7d6bc() */
			ply->UserData[0x10] = -1;				/* XXX userdata */
			if(vict->Airborne != AIR_ONGROUND) {
				ply->NextReactMode = RM_HITINAIR;
			} else if(vict->BlockStun) {
				set_blockstun_react(vict);
			} else {
				/* 7d6d0 */
				ply->UserData[0x10] = 1;
				vict->NextReactMode = RM_0x0c;
				if(vict->Energy < 0) {
					ply->UserData[0x10] = -1;
				}
				set_reel_react(vict);   
			}
		} else {
			if(vict->Airborne) {    
				ply->NextReactMode = RM_HITINAIR;
			} else if (vict->BlockStun) {
				set_blockstun_react(vict);
			}
		}
	} else if (vict->NextReactMode == RM_0x26) {
		if (vict->Airborne != AIR_ONGROUND) {		// 7d692
			vict->NextReactMode = RM_FIREBALLDOWN;
		} else if (vict->BlockStun == FALSE) {
			set_reel_react(vict);
		} else {
			vict->NextReactMode = RM_0x06;
		}
	} else if ((vict->NextReactMode == RM_HURRICANE || 
			    vict->NextReactMode == RM_0x14 ||
			    vict->NextReactMode == RM_MULTIHIT 
			   ) && vict->Airborne) {
		vict->NextReactMode = RM_FIREBALLDOWN;
	} else {
		vict->IsBlockingSuper = TRUE;            /* 7d684 */
		if(vict->BlockStun) {
			set_blockstun_react(vict);
		}
	}
}	
void set_newreact(Player *vict, Player *ply, const HitBoxAct *hbact) {     /* checked 0x7d5e6 public */   
    vict->IsBlockingSuper = FALSE;
    vict->NextReactMode   = g.GPHitBoxHit;
	
    if (hbact->Attack >= ATTACK_SPECIAL) {
		set_special_reactmode(vict, ply, hbact);
	} else if (vict->Airborne) {
        vict->NextReactMode = RM_HITINAIR;
    } else if (vict->BlockStun) {
        set_blockstun_react(vict);
	} else {
		switch (hbact->Attack) {
			case ATTACK_STAND:
				if(vict->ActionScript->Crouch) {
					vict->NextReactMode = RM_0x0a;
				}
				break;
			case ATTACK_SWEEP:
				vict->NextReactMode = RM_FOOTSWEPT;
				break;
			case ATTACK_JUMP:
				set_reel_react(vict);
				break;
			FATALDEFAULT;
		}
	}
}
static void set_reel_react(Player *vict) {    // 7d634 checked
    if(vict->ActionScript->Crouch) {   /* standing / crouching */
		vict->NextReactMode = RM_0x0a;
    } else {
		vict->NextReactMode = RM_0x0c;
    }
}
static void set_blockstun_react(Player *vict) {		/* 7d6ec  checked */
    if (vict->ActionScript->Crouch) {
        vict->NextReactMode = RM_0x08;
    } else {
        vict->NextReactMode = RM_0x06;
    }    
}
void make_collision_sound(Player *ply, const HitBoxAct *a3) {         /* 7d700 checked */
    if(ply->BlockStun || g.GPHitBlocked) {
		queuesound(SOUND_HIT_BLOCKED);  /* blocked hit thud */
    } else {
        queuesound(a3->Sound);
    }
}

static void _CDStartAction38Vict(Player *vict) {      
	/* 0x7d720  Slow down gameplay for effect */
    Object *obj;
    if(obj=AllocActor()) {
        g.FlagTimeWarp = TRUE;
        obj->exists = TRUE;
        obj->Sel    = SF2ACT_TIMEWARP;      
        obj->Owner = vict;
        obj->UserByte  = 0;
        if(vict->Energy < 0) {
            obj->SubSel = 1;
        }
    }
}
static void sub_7dccc(Player *ply, Object *a2) {	// 7dccc a6 a2 
	short x=(ply->Side);
	struct ud_s {
		u16 a;
		u16 b;
		u16 x0084;
	};
	struct ud_s *ud = (struct ud_s *)a2->UserData;
	if(g.GPWasProjectile) {		// projectile? 
		x = (ply->Owner->Side);
	}
	if (ply->Energy < 0) {
		// 7dcf0
		if (ud->x0084 == 0) {
			ud->x0084 = 1;
			action_1286e((Object *)ply, x);
		}
		LBAddPoints(8, x);
	} else {
		LBAddPoints(2, x);
	}
	
}

#pragma mark BONUS0 - The car

static void _CDSplashBonus0(Object *obja2) {		// 7db9c
	Object *nobj;
	if (nobj = AllocActor()) {
		nobj->exists = TRUE;
		nobj->Sel = 0x32;
		if (obja2->Direction) {
			nobj->SubSel = 0;
		} else {
			nobj->SubSel = 1;
		}
	}
}
static void _CDSoundBonus0(Object *obja2) {						// 7dafc
	if (obja2->BlockStun) {
		queuesound(0x72);
	} else {
		queuesound(0x33);
	}
}

static void sub_7db12 (Object *obja6, Object_G2 *obja2) {
	const static short data_7db7e[] = {
		6, 6, 6, 8, 8, 8, 8, 8, 8, 10, 10, 34, 34, 34, 34
	};
	
	if (obja2->BlockStun == FALSE) {
		if (g.x8aec > 0) {
			if (g.GPWasProjectile) {
				LBAddPoints(2, ((Player *)obja6)->Side);
			} else {
				LBAddPoints(2, obja6->Owner->Side);
			}
			//todo sub_132fe(1);
		} else {
			if(++obja2->UD.UDcar.h0093c == 15) {
				obja2->UD.UDcar.h0093c = 14;
			}
			if (g.GPWasProjectile) {
				LBAddPoints(data_7db7e[obja2->UD.UDcar.h0093c], ((Player *)obja6)->Side);
			} else {
				LBAddPoints(data_7db7e[obja2->UD.UDcar.h0093c], obja6->Owner->Side);
			}
			//todo sub_132fe(0);
		}

	}
}

static void _CDCheckObjBonus0(Player *plya6, Object_G2 *obja2, char *a1) {		// 7da44
	HitBoxAct *hba3;
	int d4, d0;
	
	if(hba3 = get_active_hitbox(plya6)) {
		if (hba3->Shove < 0) {
			d4 = 1;
		} else {
			d4 = hba3->Shove;
		}
		if (d4 == *a1) {
			return;
		}
		if (check_main_hitboxes(obja2,plya6 , hba3)) {
			*a1 = hba3->Shove;
			if (*a1 < 0) {
				*a1 = 1;
			}
			
			obja2->NextReactMode2 = hba3->ReactMode2;
			obja2->Timer2 = 14;
			plya6->Timer2 = 14;
			obja2->Direction = plya6->Flip;
			obja2->BlockStun = FALSE;  
		
			if (g.TimeRemainBCD != 1 && g.TimeOut == FALSE && obja2->UD.UDcar.boxes[g.GPHitBoxHit] < 0) {
				obja2->BlockStun = TRUE;
			} else {
				d0 = obja2->UD.UDcar.boxes[g.GPHitBoxHit];
				d0 -= (hba3->ReactMode2 + 1);
				if (d0 < 0) {
					d0 = -1;
				}
				obja2->UD.UDcar.boxes[g.GPHitBoxHit] = d0;
				g.x8aec = d0;
			}
			if (g.GPWasProjectile) {
				plya6->Energy = -2;
			}
			_CDSoundBonus0(obja2);
			mac_stunme2(plya6, obja2);
			_CDSplashBonus0(obja2);
			sub_7db12(plya6, obja2);
			return;
		}
	}
	*a1=0;
}
void _CDCheckBonus0(Player *plya6, Object_G2 *obja2) {		// 7d9f6
	char *a1;
	
	if (plya6->Side) {
		a1 = &obja2->UD.UDcar.h008cc;
	} else {
		a1 = &obja2->UD.UDcar.h008dc;
	}
	if (plya6->OnPlatform) {
		*a1 = 0;
	} else {
		g.GPWasProjectile = FALSE;
		_CDCheckObjBonus0(plya6, obja2, a1);
	}
	if (plya6->Side) {
		a1 = &obja2->UD.UDcar.h008ec;
	} else {
		a1 = &obja2->UD.UDcar.h008fc;
	}
	if (plya6->Projectile && plya6->Projectile->exists == 1) {
		g.GPWasProjectile = TRUE;
		_CDCheckObjBonus0(plya6, obja2, a1);
	} else {
		*a1 = 0;
	}
}


#pragma mark BONUS1
static void _CDSoundBonus1(Object *obja2, HitBoxAct *hba3) {		// 7dcba
	if (obja2->Energy < 0) {
		queuesound(0x32);
	} else {
		make_collision_sound((Player *)obja2, hba3);
	}
}
void _CDCheckObjBonus1(Player *plya6, Object_G2 *obja2, char *a1) {		// 7dc2e
	const HitBoxAct *hb;
	const HitBox *hb2;
	int d4;
	
	if ((hb = get_active_hitbox((Object *)plya6)) == 0) {
		*a1 = 0;
	} else {
		d4 = hb->Shove;
		if (d4 < 0) {
			d4 = 1;
		}
		if (d4 == *a1) {
			return;
		}
		if (hb2 = _CDGetHitBoxHead(obja2)) {
			if (check_hitbox_overlap((Object *)plya6, (Object *)obja2, hb, hb2)) {
				if (hb->Shove < 0) {
					*a1 = 1;
				} else {
					*a1 = hb->Shove;
				}
				obja2->NextReactMode2 = hb->ReactMode2;
				obja2->Timer2 = 14;
				plya6->Timer2 = 14;
				obja2->Direction = plya6->Flip;
				obja2->BlockStun = FALSE;
				obja2->Energy -= (hb->ReactMode2 + 1);
				if (obja2->Energy < 0) {
					obja2->Energy = -1;
					obja2->exists = 2;
				}
				if (g.GPWasProjectile) {
					obja2->Energy = -2;
				}
				_CDSoundBonus1((Object *)obja2, hb);
				mac_stunme2(plya6, (Object *)obja2);
				sub_7dccc(plya6, (Object *)obja2);
				return;
			}
		}
		*a1 = 0;
	}
}
void _CDCheckBonus1(Player *plya6, Object_G2 *obja2) {		// 7dbea
	char *a1;
	if (plya6->Side) {
		a1 = &obja2->UD.UDbonus1.h008cc;
	} else {
		a1 = &obja2->UD.UDbonus1.h008dc;
	}
	g.GPWasProjectile = FALSE;
	_CDCheckObjBonus1(plya6, obja2, a1);
	if (plya6->Side) {
		a1 = &obja2->UD.UDbonus1.h008ec;
	} else {
		a1 = &obja2->UD.UDbonus1.h008fc;
	}
	if (plya6->Projectile && plya6->Projectile->exists == 1) {
		g.GPWasProjectile = TRUE;
		_CDCheckObjBonus1(plya6, obja2, a1);
	} else {
		*a1 = 0;
	}
}
void _CDBonus1(Object_G2 *a6) {		// 7dbc2
	if (g.Player1.exists) {
		_CDCheckBonus1(&g.Player1, a6);
	}
	if (g.Player2.exists) {
		_CDCheckBonus1(&g.Player2, a6);
	}
}


#pragma mark BONUS2
static void _CDCheckObjBonus2(Object *obj, Player *ply) {			// 7d2ae
	HitBoxAct *hb;
	if (g.PlayersThrowing || g.DebugNoCollide) {
		return;
	}
	if(hb=get_active_hitbox(obj)==0) { return; }
	if (ply->TimerInvincible) {
		return;
	}
	if (check_main_hitboxes(obj, ply, hb)==0) {
		return;
	}
	ply->TimerInvincible = 120;
	ply->DidCollide = TRUE;
	ply->NextReactMode2 = hb->ReactMode2;
	obj->Timer2 = 14;
	ply->Timer2 = 14;
	ply->Direction = obj->Flip;
	ply->Energy--;
	ply->x0071 = 0;
	ply->NextReactMode = RM_HITINAIR;
	queuesound(45);
	mac_stunhim_from76(obj, ply);
}
static void sub_7d284(Object_G2 *obj) {
	// XXX userdata;
	if (g.Player1.UserData[4] == 0 || g.Player2.UserData[4] == 0) {
		return;
	}
	if (g.Player1.exists ) {
		_CDCheckObjBonus2(obj, PLAYER1);
	}
	if (g.Player2.exists) {
		_CDCheckObjBonus2(obj, PLAYER2);
	}
}
static void _CDCheckBonus2(Player *a6, Object_G2 *a2) {		// 7dd38
	char *a1;
	/* XXX access userdata in A2 */
	if (a6->Side) {
		a1 = &a2->UD.UDbonus2.h008dc;
	} else {
		a1 = &a2->UD.UDbonus2.h008cc;
	}
	g.GPWasProjectile = FALSE;
	//todo sub_7dd7c(a6, a2, a1);
	if (a6->Side) {
		a1 = &a2->UD.UDbonus2.h008fc;
	} else {
		a1 = &a2->UD.UDbonus2.h008ec;
	}
	if (a6->Projectile) {
		if (a6->Projectile->exists == 1) {
			g.GPWasProjectile = TRUE;
			//todo sub_7dd7c(a6, a2, a1);
			return;
		}
	}
	*a1 = 0;
}

static void _CDBonus2(Object_G2 *a6) {		// 7dd0c
	sub_7d284(a6);
	if (g.Player1.exists) {
		_CDCheckBonus2(&g.Player1, a6);
	}
	if (g.Player2.exists) {
		_CDCheckBonus2(&g.Player2, a6);
	}
}


static void _CDBonus3(Object_G2 *a6) {			// 7d20a
	
	
}
void sub_7d99a(Object *a6) {		// 7dd9a - entry for Bonus objects
	// disable collision detection for most objects
	char data_7d9ba[]={-1, -1, -1, -1, 6, 4, 0, -1, -1, 2, -1, -1, -1, -1, -1, -1};
	
	// Subsel    BonusX
	//  4			3
	//  5			2
	//	6			0
	//  9           1
	
	if (a6->exists == 1 && data_7d9ba[a6->Sel] >= 0) {
		switch (data_7d9ba[a6->Sel]) {
			case 0:		// collision bonus obj 0
				//g.x8aea = a6; only temp?
				if (g.Player1.exists) {
					_CDCheckBonus0(&g.Player1, a6);
				}
				if (g.Player2.exists) {
					_CDCheckBonus0(&g.Player2, a6);
				}
				break;
			case 2:		// collision bonus obj 1
				_CDBonus1(a6);
				break;
			case 4:
				_CDBonus2(a6);
				break;
			case 6:
				_CDBonus3(a6);
				break;
			FATALDEFAULT;
		}
	}
}

void CDCheckPushBoxes () {			/* 7e136 check pushboxes, take action */
    if(g.BattleOver) {return;}
    g.GPCollDetect = FALSE;
	const HitBox *a3,*a4;
	
    if(g.Player1.exists == FALSE) { return; }
	
    if(a3=_CDGetPushBox((Object *)PLAYER1)) {
        if(a4=_CDGetPushBox((Object*)PLAYER2)) {
            if(slib_check_overlap((Object *)PLAYER1, PLAYER2,a3,a4)) {
                sub_7e16e(hitresult[4]);
            }
        }
    }
}
void slib_ply_overlap() {		// 7e12a
	// CPS todo
	/* wrapper function, in game saves A6 to g.8af2 */
	CDCheckPushBoxes();
}
static void sub_7d314(Object *a6, Player *a2) {
	const HitBoxAct *a3;
	/* 0x7d314  Object %a6, Player %a2, HitBoxAct %a3 */
	if (g.PlayersThrowing || g.DebugNoCollide) {
		return;
	}
	a3 = get_active_hitbox(a6);
	if (a3 == NULL) {
		return;
	}
	if (a2->TimerInvincible != 0) {
		return;
	}
	if (check_main_hitboxes(a6, (Object *)a2, a3)==0) {
		return;
	}
	a2->TimerInvincible = 120;
	a2->DidCollide = TRUE;
	a2->NextReactMode2 = a3->ReactMode2;
	a6->Timer2 = 14;
	a2->Timer2 = 14;
	a2->Direction = a6->Flip;
	--a2->Energy;
	a2->x0071 = 0;
	set_newreact(a2, (Player *)a6, a3);
	soundsting(SOUND_IMPACT5);
	mac_stunhim_from76(a6, a2);
}
static void _CDKillDecor2(Object *a6, Player *a2) {		// 7e424 checked
	mac_stun_oppopp((Player *)a6, a2);
	a6->exists=2;
	a6->Energy = -1;
	a6->Timer2 = 6;
	action_1286e((Object *)a6, a2->Side ^ 1);
	LBAddPoints(8,a2->Side ^ 1);
	_CDDecorSoundPts(a6);		/* Make sound, reward points */
}
	
	
/* CDCheckDecor		@7e340
 Check for collision from a player, but only if falling or being thrown.
 Stage decorations such as Ryu's signs, Ken's drums call this detect when to break */
 
void CDCheckDecor (Object *a6) {		/* 7e340 check if collision with player */
	if(a6->exists & 0x01) {
		switch (a6->Sel) {
			case 1:
			case 2:
			case 3:
			case 7:
				/* 7e372 see if player fell onto barrels  / signs, etc. make sound */
				if(g.Player1.exists && g.Player1.Airborne < 0) {
					if(_CDPushOverlap(PLAYER1, a6)) {		/* check for a collision */
						_CDKillDecor(PLAYER1, a6);		/* kill the object */
					}
				}
				if(g.Player2.exists && g.Player2.Airborne < 0) {
					if(_CDPushOverlap(PLAYER2, a6)) {
						_CDKillDecor(PLAYER2, a6);
					}
				}
				break;
			case 9:
				/* 7e3ea */
				if (g.Player1.exists) {
					sub_7d314(a6, PLAYER1);
					if(g.Player1.Airborne == AIR_REEL2) {
						if(_CDPushOverlap(PLAYER1, a6)) {
							_CDKillDecor2(a6, PLAYER1);
							return;
						}
					}
				}
				/* 7e406 */
				if (g.Player2.exists) {
					sub_7d314(a6, PLAYER2);
					if(g.Player1.Airborne == AIR_REEL2) {
						if(_CDPushOverlap(PLAYER2, a6)) {
							_CDKillDecor2(a6, PLAYER2);
							return;
						}
					}
				}
				
			default:
				break;
		}
	}
}
static void _CDCheckPlayer(Player *ply, Player *vict) {     /* 7cf38 */
    int temp;
	short damage;
	
	const HitBoxAct *active;		// %a3
    
    if(!(active=get_active_hitbox((Object *)ply))) {
        vict->SufferHB5 = 0;
        return;
    }
    if (vict->CompImmune || vict->TCollDis || vict->Invincible) { return; }
    temp = active->Shove;
    if(temp < 0) { temp = 1; }
    if(temp == vict->SufferHB5) { return; }
    if((active->ReactMode == RM_MULTIHIT ||  active->ReactMode == RM_ELECTROCUTED) 
	   && vict->MultiHoldoff ) {
        return;
    }
    if(!check_main_hitboxes((Object *)ply, (Object *)vict, active))   { return; }
    if(active->ReactMode == RM_MULTIHIT	|| 
	   active->ReactMode == RM_ELECTROCUTED) {
        vict->MultiHoldoff = 18;     
    }
    if(vict->Human == 0) {
        g.x0ae4++;
    }
    vict->SufferHB5 = active->Shove;
    if(vict->SufferHB5 < 0) {
        vict->SufferHB5 = 1;
    }
    vict->NextReactMode2 = active->ReactMode2;
    ply->Timer2  = 14;
    vict->Timer2 = 14;
    _CDSpecialReactMode(ply, vict, active);
	
    damage = lookup_damage_and_score(ply, vict, active);
    if(sub_7d4fa(vict, active) == 0) {
        damage=damage_multiplier(vict, damage);
        damage=randomize_damage(vict, damage, active);
        damage=diminishing_damage(damage, vict);
        if(g.GPHitBlocked) {
            damage /= 4;
            if (damage == 0) { damage = 1; }
        }
        vict->Energy -= damage;
        if(vict->Energy < 0) {
            vict->Energy    = -1;
			start_timewarp_action(vict);
            g.GPHitBlocked    = FALSE;
            vict->BlockStun   = FALSE; 
        }  
    }
    vict->x0071 = 0;						//7d000
    set_newreact(vict, ply, active);       
    make_collision_sound(vict, active);
    sub_7d74e(ply, vict, active);		     /* splash, see if vega loses claw */
    if(vict->BlockStun || g.OnBonusStage) { return; }
    QueueEffect(g.GPPointsReward, ply->Side);                    /* award points */
}
static void _CDKillDecor(Player *a2, Object *a6) {	/* 7e39e */
	/* Kill the object, make a sound, reward points */
	a6->Energy     = -1;
	a6->Timer2     = 6;
	a2->ReactTimer = 6;
	_CDDecorSoundPts(a6);		// make smash sound, reward points.
}
static void _CDDecorSoundPts(Object *a6){		// 7e3b0
	soundsting((u16 []){
		0, 
		SOUND_CAR_BREAK,
		SOUND_BARRELS_BREAK,
		SOUND_BARRELS_BREAK,
		SOUND_BARRELS_BREAK,
		0, 0, 0,
		SOUND_BARRELS_BREAK,
		0, 0}[a6->Sel]);
	QueueEffect(0x8200, 0);		// Both players get points
	QueueEffect(0x8200, 1);
}
static short _CDPushOverlap(Player *a2, Object *a6) {	
	/* 7e460 test if player %a2 push hit object %a6 push */
	const HitBox *hb;
	const HitBox *plyhb;
	short d4;
	
	if (a2->ActionScript->HB_Push == 0) {return 0;} 
	hb = a2->HitBoxes->push + a2->ActionScript->HB_Push;  /* XXX use globals */
	if (a6->ActionScript->HB_Push == 0) {return 0;}
	plyhb = a6->HitBoxes->push + a2->ActionScript->HB_Push;
	if(a2->ZDepth) {
		/* 0x7e4b2 */
		g.x8af6 = a2->XPI;
		a2->XPI = a2->x0044;
		d4 = slib_check_overlap((Object *)a2, (Player *)a6, hb, plyhb);	
		a2->XPI = g.x8af6;
	} else {
		d4 = slib_check_overlap((Object *)a2, (Player *)a6, hb, plyhb);
	}
	if (d4) {
		a6->Step = a2->Direction;
		a6->Direction = a2->Direction;
	}
	return d4;
}	
static void _CDSpecialReactMode(Player *ply, Player *vict, const HitBoxAct *a3) {	/* 0x7d02e */
	vict->Direction = ply->Flip;
	switch (ply->FighterID) {
		case FID_RYU:
		case FID_KEN:
			if(a3->ReactMode == RM_HURRICANE)		{ _CDTurnToFaceMe(ply, vict); }
			break;
		case FID_E_HONDA:
			if(a3->ReactMode == RM_MULTIHIT)		{ _CDTurnToFaceMe(ply, vict); }
			break;
		case FID_BLANKA:
			if(a3->ReactMode == RM_ELECTROCUTED)	{_CDTurnToFaceMe(ply, vict); }
			break;
		case FID_CHUN_LI:
			if(a3->ReactMode == RM_MULTIHIT ||
			   a3->ReactMode == RM_HURRICANE)		{ _CDTurnToFaceMe(ply, vict); }
			break;
		case FID_ZANGEIF:
			if(a3->ReactMode == RM_0x14)				{ _CDTurnToFaceMe(ply, vict); }
			break;
		case FID_M_BISON:
			if((ply->AnimFlags & 0xff) == 0x17) { vict->Direction ^= 1; }
			break;
	/* no special processing for these guys */
	/*	case FID_GUILE:
		case FID_DHALSIM:
		case FID_SAGAT:
		case FID_BALROG:
		case FID_VEGA:		*/
		default:
			break;
	}
}
static void _CDTurnToFaceMe(Player *ply, Player *vict) {	/* 7d0a8 */
	if(ply->XPI < vict->XPI) {
		vict->Direction = FACING_LEFT;
	} else {
		vict->Direction = FACING_RIGHT;
	}
}


static void start_timewarp_action (Player *vict) {	/* 7d720 */
	Object *obj;
	if(obj=AllocActor()) {
		g.FlagTimeWarp = TRUE;
		obj->exists = TRUE;
		obj->Sel    = SF2ACT_TIMEWARP;
		obj->Owner	= vict;
		obj->UserByte  = 0;
		if(vict->Energy < 0) {
			obj->SubSel = 1;
		}
	}
}


static void sub_7e314(void) {		// 7e314
	g.Player2.PushDirection = 1;
}
