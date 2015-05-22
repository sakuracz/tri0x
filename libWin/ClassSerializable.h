#ifndef CLASSSERIALIZABLE_H_
#define CLASSSERIALIZABLE_H_

#include "ClassSerializer.h"

class Serializable
{
public:
	virtual void Serialize(Serializer & out) const = 0;
	virtual void DeSerialize(DeSerializer & in) = 0;
};

#endif