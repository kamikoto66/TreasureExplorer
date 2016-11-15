#pragma once
#include "cocos2d.h"
#include "enumData.h"
#include "Macro.h"

USING_NS_CC;


#define TAG_BACKIMAGE 0
#define TAG_TREASURE 1
#define TAG_UI_BUTTON 2

#define TAG_UPGRADE 0
#define TAG_EXIT 1
#define SHABBYUPGRADECOIN 300
#define NOMALUPGRADECOIN 500
#define UPGRADEACTION 20

class CTreasure;

class CTreasureUpgrade : public Layer
{
private:
	CREATEWINSIZE;
	TreasureIndex treasureIndex;
	TreasureType treasureType;
	CTreasure* treasure;
	std::string xmlTag;
	std::string treasureName;
	Sprite* backImage;
	Menu* upgradeUi;
	Label* curCoinLabel;
	Label* useCoinLabel;
	bool isUpgrade;

private:
	void enterRemove();
	void enterUpgradeShabby();
	void enterUpgradeNomal();
	void generaterTreasureUpgrade();
	void generaterCoinLabel();
	void enterUpgradeUi(Ref* sender);

public:
	CTreasureUpgrade();
	~CTreasureUpgrade();
	
	virtual bool init(TreasureIndex _index, TreasureType _type, std::string _xmlTag, std::string _treasureName);
	void update(float dt);
	CREATE_FUNC_ARGS(CTreasureUpgrade);
};

