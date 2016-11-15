#pragma once
#include "cocos2d.h"
#include "Macro.h"

USING_NS_CC;

class CRope : public Node
{
private:
	bool isSelect;
	Menu* ropeMenu;

public:

	CRope();
	~CRope();

	virtual bool init();
	void enterRope();
	CREATE_FUNC_ARGS(CRope);
public:
	void setIsSelect(bool _isSelect) { isSelect = _isSelect; }
	void setMenu(Menu* _menu) { ropeMenu = _menu; }

	Menu* getMenu() const { return ropeMenu; }
	bool getIsSelect() const { return isSelect; }
};