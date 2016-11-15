#pragma once
#include "cocos2d.h"
#include "enumData.h"
#include "Macro.h"

class CTreasure : public Sprite
{
	float baseScale;
	TreasureType treasureType;
	TreasureIndex treasureIndex;
	std::function<void(CTreasure*)> _onTriggered;
	std::string xmlTag;
	std::string treasureName;

private:
	bool generaterTreasure();
	void treasureSeting();
	bool onTouchBegan(Touch  *touch, Event  *unused);
	void onTouchEnded(Touch  *touch, Event  *unused);
	void onTouchCancelled(Touch  *touch, Event  *unused);

	bool touchHits(cocos2d::Touch  *touch);
	void scaleButtonTo(float scale);

public:
	CTreasure();
	~CTreasure();

	virtual bool init(TreasureIndex _treasureIndex, const std::function<void(CTreasure*)> &onTriggered);
	virtual bool init(TreasureIndex _treasureIndex, std::string _jsonName, std::string _treasureName); 

	CREATE_FUNC_ARGS(CTreasure);

public:
	void setXMLTag(const std::string _xmlTag)  { xmlTag = _xmlTag.c_str(); }
	void setTreasureName(const  std::string _treasureName)  { treasureName = _treasureName; }

	std::string getXMLTag() const { return xmlTag; }
	std::string getTreasureName() const { return treasureName; }

	TreasureIndex getTreasureIndex() const { return treasureIndex; }
	TreasureType getTreasureType() const { return treasureType; }
	float getBaseScale() const { return baseScale; }
};

