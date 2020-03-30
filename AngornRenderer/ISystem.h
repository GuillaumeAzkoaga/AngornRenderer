#ifndef ISYSTEM_H_
#define ISYSTEM_H_


class ISystem
{
public:
	virtual ~ISystem() {};
	virtual void Initialize() = 0;
	virtual void Update(float dt = 0) = 0;
	virtual void Shutdown() = 0;
};
#endif