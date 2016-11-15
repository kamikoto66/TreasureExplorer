#pragma once
#include "cocos2d.h"
USING_NS_CC;

class CKnife : public Node
{
private:
	bool isSelect;
	Menu* knifeMenu;

public:

	CKnife();
	~CKnife();

	virtual bool init();
	void enterKnife();
	CREATE_FUNC_ARGS(CKnife);

public:
	void setIsSelect(bool _isSelect) { isSelect = _isSelect; }
	void setMenu(Menu* _menu) { knifeMenu = _menu; }

	Menu* getMenu() const { return knifeMenu; }
	bool getIsSelect() const { return isSelect; }
};

