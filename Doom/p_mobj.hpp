#ifndef __P_MOBJ_HPP__
#define __P_MOBJ_HPP__

#include "p_tick.hpp"

extern "C"
{
#include "doomstat.h"
#include "m_random.h"
#include "p_local.h"
#include "sounds.h"
}

extern mobjtype_t P_GetActorType(Type^ type);

ref class Actor : LegacyThinker
{
private:
	static Actor^ MobjToActor(mobj_t *mobj);
	int speed;
	int mass;
	int damage;
	int painchance;
	int seesoundnum;
	int activesoundnum;
	int attacksoundnum;
	int painsoundnum;
	int deathsoundnum;
	Dictionary<String^,int>^ states;
	Object^ species;
public:
	mobj_t *mobj;

	Actor(fixed_t x,fixed_t y,fixed_t z) : LegacyThinker(sizeof(mobj_t))
	{
		mobj = (mobj_t *)ptr;
		memset(mobj,0,sizeof(mobj_t));
		mobj->thinker.function.acp1 = (actionf_p1)P_MobjThinker;
		mobj->type = P_GetActorType(GetType());
		mobj->info = NULL;
		X = Fixed(x);
		Y = Fixed(y);
		Z = Fixed(z);
		Radius = Fixed::FromInt(20);
		Height = Fixed::FromInt(16);
		mobj->flags = 0;
		Health = 1000;
		ReactionTime = 8;
		speed = 0;
		mass = 100;
		damage = 0;
		painchance = 0;
		seesoundnum = sfx_None;
		activesoundnum = sfx_None;
		attacksoundnum = sfx_None;
		painsoundnum = sfx_None;
		deathsoundnum = sfx_None;
		states = gcnew Dictionary<String^,int>();
		DefineState("Spawn",0);
		species = GetType();
	}

	property Fixed X
	{
		Fixed get() { return Fixed(mobj->x); }
		void set(Fixed value) { mobj->x = value.Value; }
	}

	property Fixed Y
	{
		Fixed get() { return Fixed(mobj->y); }
		void set(Fixed value) { mobj->y = value.Value; }
	}

	property Fixed Z
	{
		Fixed get() { return Fixed(mobj->z); }
		void set(Fixed value) { mobj->z = value.Value; }
	}

	property unsigned int Angle
	{
		unsigned int get() { return mobj->angle; }
		void set(unsigned int value) { mobj->angle = value; }
	}

	property int SpriteNum
	{
		int get() { return mobj->sprite; }
		void set(int value) { mobj->sprite = (spritenum_t)value; }
	}

	property int SpriteFrame
	{
		int get() { return mobj->frame; }
		void set(int value) { mobj->frame = value; }
	}

	property Fixed Radius
	{
		Fixed get() { return Fixed(mobj->radius); }
		void set(Fixed value) { mobj->radius = value.Value; }
	}

	property Fixed Height
	{
		Fixed get() { return Fixed(mobj->height); }
		void set(Fixed value) { mobj->height = value.Value; }
	}

	property Fixed XMomentum
	{
		Fixed get() { return Fixed(mobj->momx); }
		void set(Fixed value) { mobj->momx = value.Value; }
	}

	property Fixed YMomentum
	{
		Fixed get() { return Fixed(mobj->momy); }
		void set(Fixed value) { mobj->momy = value.Value; }
	}

	property Fixed ZMomentum
	{
		Fixed get() { return Fixed(mobj->momz); }
		void set(Fixed value) { mobj->momz = value.Value; }
	}

	property int Tics
	{
		int get() { return mobj->tics; }
		void set(int value) { mobj->tics = value; }
	}

	property int StateNum
	{
		int get() { return mobj->state - ::states; }
		void set(int value) { mobj->state = &::states[value]; }
	}

#define LEGACYFLAG(propname,legacyname) \
	property bool propname \
	{ \
		bool get() { return mobj->flags & legacyname; } \
		void set(bool value) \
		{ \
			if (value) \
				mobj->flags |= legacyname; \
			else \
				mobj->flags &= ~legacyname; \
		} \
	}

	LEGACYFLAG(Special,MF_SPECIAL)
	LEGACYFLAG(Solid,MF_SOLID)
	LEGACYFLAG(Shootable,MF_SHOOTABLE)
	LEGACYFLAG(NoSector,MF_NOSECTOR)
	LEGACYFLAG(NoBlockmap,MF_NOBLOCKMAP)
	LEGACYFLAG(Ambush,MF_AMBUSH)
	LEGACYFLAG(JustHit,MF_JUSTHIT)
	LEGACYFLAG(JustAttacked,MF_JUSTATTACKED)
	LEGACYFLAG(SpawnCeiling,MF_SPAWNCEILING)
	LEGACYFLAG(NoGravity,MF_NOGRAVITY)
	LEGACYFLAG(DropOff,MF_DROPOFF)
	LEGACYFLAG(Pickup,MF_PICKUP)
	LEGACYFLAG(NoClip,MF_NOCLIP)
	LEGACYFLAG(Slide,MF_SLIDE)
	LEGACYFLAG(Float,MF_FLOAT)
	LEGACYFLAG(Teleport,MF_TELEPORT)
	LEGACYFLAG(Missile,MF_MISSILE)
	LEGACYFLAG(Dropped,MF_DROPPED)
	LEGACYFLAG(Shadow,MF_SHADOW)
	LEGACYFLAG(NoBlood,MF_NOBLOOD)
	LEGACYFLAG(Corpse,MF_CORPSE)
	LEGACYFLAG(InFloat,MF_INFLOAT)
	LEGACYFLAG(CountKill,MF_COUNTKILL)
	LEGACYFLAG(CountItem,MF_COUNTITEM)
	LEGACYFLAG(SkullFly,MF_SKULLFLY)
	LEGACYFLAG(NotDMatch,MF_NOTDMATCH)
#undef LEGACYFLAG

	property int Health
	{
		int get() { return mobj->health; }
		void set(int value) { mobj->health = value; }
	}

	property int MovementDirection
	{
		int get() { return mobj->movedir; }
		void set(int value) { mobj->movedir = value; }
	}

	property int MovementCount
	{
		int get() { return mobj->movecount; }
		void set(int value) { mobj->movecount = value; }
	}

	property Actor^ Target
	{
		Actor^ get() { return MobjToActor(mobj->target); }
		void set(Actor^ value) { mobj->target = value ? value->mobj : NULL; }
	}

	property int ReactionTime
	{
		int get() { return mobj->reactiontime; }
		void set(int value) { mobj->reactiontime = value; }
	}

	property int LastLook
	{
		int get() { return mobj->lastlook; }
		void set(int value) { mobj->lastlook = value; }
	}

	property Actor^ Tracer
	{
		Actor^ get() { return MobjToActor(mobj->tracer); }
		void set(Actor^ value) { mobj->tracer = value ? value->mobj : NULL; }
	}

	property int Speed
	{
		int get() { return speed; }
		void set(int value) { speed = value; }
	}

	property int Mass
	{
		int get() { return mass; }
		void set(int value) { mass = value; }
	}

	property int Damage
	{
		int get() { return damage; }
		void set(int value) { damage = value; }
	}

	property int PainChance
	{
		int get() { return painchance; }
		void set(int value) { painchance = value; }
	}

	property int SeeSoundNum
	{
		int get() { return seesoundnum; }
		void set(int value) { seesoundnum = value; }
	}

	property int ActiveSoundNum
	{
		int get() { return activesoundnum; }
		void set(int value) { activesoundnum = value; }
	}

	property int AttackSoundNum
	{
		int get() { return attacksoundnum; }
		void set(int value) { attacksoundnum = value; }
	}

	property int PainSoundNum
	{
		int get() { return painsoundnum; }
		void set(int value) { painsoundnum = value; }
	}

	property int DeathSoundNum
	{
		int get() { return deathsoundnum; }
		void set(int value) { deathsoundnum = value; }
	}

	property Object^ Species
	{
		Object^ get() { return species; }
		void set(Object^ value) { species = value; }
	}

	void DefineState(String^ name,int statenum)
	{
		if (states->ContainsKey(name))
		{
			states[name] = statenum;
		}
		else
		{
			states->Add(name,statenum);
		}
	}

	bool HasState(String^ name)
	{
		return states->ContainsKey(name);
	}

	int GetStateNum(String^ name)
	{
		return states[name];
	}
};

ref class LegacyActor : Actor
{
public:
	LegacyActor(fixed_t x,fixed_t y,fixed_t z,mobjtype_t type) : Actor(x,y,z)
	{
		Species = (int)type;
		mobjinfo_t &info = mobjinfo[type];
		mobj->type = type;
		mobj->info = &info;
		Radius = Fixed(info.radius);
		Height = Fixed(info.height);
		mobj->flags = info.flags;
		Health = info.spawnhealth;
		ReactionTime = info.reactiontime;
		Speed = info.speed;
		Mass = info.mass;
		Damage = info.damage;
		PainChance = info.painchance;
		SeeSoundNum = info.seesound;
		ActiveSoundNum = info.activesound;
		AttackSoundNum = info.attacksound;
		PainSoundNum = info.painsound;
		DeathSoundNum = info.deathsound;
		if (info.spawnstate)
			DefineState("Spawn",info.spawnstate);
		if (info.seestate)
			DefineState("See",info.seestate);
		if (info.meleestate)
			DefineState("Melee",info.meleestate);
		if (info.missilestate)
			DefineState("Missile",info.missilestate);
		if (info.painstate)
			DefineState("Pain",info.painstate);
		if (info.deathstate)
			DefineState("Death",info.deathstate);
		if (info.xdeathstate)
			DefineState("XDeath",info.xdeathstate);
		if (info.raisestate)
			DefineState("Raise",info.raisestate);
	}
};

extern Actor^ P_MobjToActor(mobj_t *mobj);

#endif
