#ifndef __Stage2_H_
#define __Stage2_H_

#include "cocos2d.h"
#include "Macro.h"
#include "json.h"

USING_NS_CC;

class CStage2 : public CMainLogic
{
public:

	CStage2();
	~CStage2();

	virtual bool init();
	void update(float dt);
	CREATE_FUNC_ARGS(CStage2);
};
#endif