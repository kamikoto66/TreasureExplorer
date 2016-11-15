#pragma once
#include "cocos2d.h"
USING_NS_CC;

class CTorch :
	public Node
{
private:
	bool isSelect;
	Menu* torchMenu;

public:

	CTorch();
	~CTorch();

	virtual bool init();
	void enterTorch();
	CREATE_FUNC_ARGS(CTorch);

public:
	void setIsSelect(bool _isSelect) { isSelect = _isSelect; }
	void setMenu(Menu* _menu) { torchMenu = _menu; }

	Menu* getMenu() const { return torchMenu; }
	bool getIsSelect() const { return isSelect; }
};

