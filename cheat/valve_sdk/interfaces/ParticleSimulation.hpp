#pragma once
#include "../misc/UtlString.hpp"
#include "../misc/Color.hpp"

#define PARTICLE_ATTRIBUTE_TINT_RGB 6
#define PARTICLE_ATTRIBUTE_ALPHA	7

#define MAX_PARTICLE_ATTRIBUTES 24

template<typename T>
struct CUtlReference
{
	CUtlReference* m_next;
	CUtlReference* m_prev;
	T* m_obj;
};

struct CParticleAttributeAddressTable
{
	float* m_pAttributes[MAX_PARTICLE_ATTRIBUTES];
	size_t m_nFloatStrides[MAX_PARTICLE_ATTRIBUTES];

	float* floatAttribute(int attribute, int particleNum) const
	{
		int blockofs = particleNum / 4;
		return m_pAttributes[attribute] +
			m_nFloatStrides[attribute] * blockofs +
			(particleNum & 3);
	}

	void modulateColor(const Color& color, int num)
	{
		auto rgb = floatAttribute(PARTICLE_ATTRIBUTE_TINT_RGB, num);

		rgb[0] = (float)color[0] / 255.f;
		rgb[4] = (float)color[1] / 255.f;
		rgb[8] = (float)color[2]/ 255.f;
	}

	void modulateAlpha(float alpha, int num)
	{
		auto a = floatAttribute(PARTICLE_ATTRIBUTE_ALPHA, num);
		*a = alpha;
	}
};

class CParticleSystemDefinition
{
public:
	char pad[308];
	CUtlStringg m_name;
};

class CParticleCollection
{
public:
	char pad[48];
	int m_activeParticles;
	char pad1[12];
	CUtlReference<CParticleSystemDefinition> m_def;
	char pad2[60];
	CParticleCollection* m_parent;
	char pad3[84];
	CParticleAttributeAddressTable m_particleAttributes;
};