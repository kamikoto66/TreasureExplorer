#include "PCH.h"
#include "Treasure.h"
#include "json.h"
#include "JsonManager.h"
#include "CollisionManager.h"

CTreasure::CTreasure()
{
	baseScale = 1.0f;
}


CTreasure::~CTreasure()
{
}

bool CTreasure::init(TreasureIndex _treasureIndex, const std::function<void(CTreasure*)> &onTriggered)
{
	treasureIndex = _treasureIndex;
	this->_onTriggered = onTriggered;

	if (!generaterTreasure())
	{
		return false;
	}
	treasureSeting();

	return true;
}

bool CTreasure::init(TreasureIndex _treasureIndex, std::string _xmlTag, std::string _treasureName)
{
	treasureIndex = _treasureIndex;
	xmlTag = _xmlTag;
	treasureName = _treasureName;

	if (!generaterTreasure())
	{
		return false;
	}
	treasureSeting();
	setScale(baseScale);

	return true;
}

bool CTreasure::generaterTreasure()
{
	std::string path;

	switch (treasureIndex)
	{
		case	eForestAccessoryShabby:	path = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestAccessoryShabby"]["FileName"].asString();	treasureType = eShabby; break;
		case	eRunisAccessoryShabby:	path = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisAccessoryShabby"]["FileName"].asString();		treasureType = eShabby; break;
		case	eSiteAccessoryShabby:	path = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteAccessoryShabby"]["FileName"].asString();		treasureType = eShabby; break;
		case	eForestCapShabby:		path = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestCapShabby"]["FileName"].asString();			treasureType = eShabby; break;
		case	eRunisCapShabby:		path = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisCapShabby"]["FileName"].asString();			treasureType = eShabby; break;
		case	eSiteCapShabby:			path = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteCapShabby"]["FileName"].asString();			treasureType = eShabby; break;
		case	eForestWearShabby:		path = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestWearShabby"]["FileName"].asString();			treasureType = eShabby; break;
		case	eRunisWearShabby:		path = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisWearShabby"]["FileName"].asString();			treasureType = eShabby; break;
		case	eSiteWearShabby:		path = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteWearShabby"]["FileName"].asString();			treasureType = eShabby; break;
		case	eForestAccessoryNomal:	path = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestAccessoryNomal"]["FileName"].asString();		treasureType = eNomal; break;
		case	eRunisAccessoryNomal:	path = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisAccessoryNomal"]["FileName"].asString();		treasureType = eNomal; break;
		case	eSiteAccessoryNomal:	path = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteAccessoryNomal"]["FileName"].asString();		treasureType = eNomal; break;
		case	eForestCapNomal:		path = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestCapNomal"]["FileName"].asString();			treasureType = eNomal; break;
		case	eRunisCapNomal:			path = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisCapNomal"]["FileName"].asString();			treasureType = eNomal; break;
		case	eSiteCapNomal:			path = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteCapNomal"]["FileName"].asString();				treasureType = eNomal; break;
		case	eForestWearNomal:		path = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestWearNomal"]["FileName"].asString();			treasureType = eNomal; break;
		case	eRunisWearNomal:		path = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisWearNomal"]["FileName"].asString();			treasureType = eNomal; break;
		case	eSiteWearNomal:			path = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteWearNomal"]["FileName"].asString();			treasureType = eNomal; break;
		case	eForestAccessoryGood:	path = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestAccessoryGood"]["FileName"].asString();		treasureType = eGood; break;
		case	eRunisAccessoryGood:	path = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisAccessoryGood"]["FileName"].asString();		treasureType = eGood; break;
		case	eSiteAccessoryGood:		path = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteAccessoryGood"]["FileName"].asString();		treasureType = eGood; break;
		case	eForestCapGood:			path = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestCapGood"]["FileName"].asString();			treasureType = eGood; break;
		case	eRunisCapGood:			path = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisCapGood"]["FileName"].asString();				treasureType = eGood; break;
		case	eSiteCapGood:			path = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteCapGood"]["FileName"].asString();				treasureType = eGood; break;
		case	eForestWearGood:		path = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestWearGood"]["FileName"].asString();			treasureType = eGood; break;
		case	eRunisWearGood:			path = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisWearGood"]["FileName"].asString();			treasureType = eGood; break;
		case	eSiteWearGood:			path = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteWearGood"]["FileName"].asString();				treasureType = eGood; break;
	}

	if (!Sprite::initWithFile(path))
	{
		return false;
	}

	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(CTreasure::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(CTreasure::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void CTreasure::treasureSeting()
{
	switch (treasureIndex)
	{	
	case	eForestAccessoryShabby:	baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestAccessoryShabby"]["Scale"].asFloat(); break;
	case	eRunisAccessoryShabby:	baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisAccessoryShabby"]["Scale"].asFloat(); break;
	case	eSiteAccessoryShabby:	baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteAccessoryShabby"]["Scale"].asFloat(); break;
	case	eForestCapShabby:		baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestCapShabby"]["Scale"].asFloat(); break;
	case	eRunisCapShabby:		baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisCapShabby"]["Scale"].asFloat(); break;
	case	eSiteCapShabby:			baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteCapShabby"]["Scale"].asFloat(); break;
	case	eForestWearShabby:		baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestWearShabby"]["Scale"].asFloat(); break;
	case	eRunisWearShabby:		baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisWearShabby"]["Scale"].asFloat(); break;
	case	eSiteWearShabby:		baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteWearShabby"]["Scale"].asFloat(); break;
	case	eForestAccessoryNomal:	baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestAccessoryNomal"]["Scale"].asFloat(); break;
	case	eRunisAccessoryNomal:	baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisAccessoryNomal"]["Scale"].asFloat(); break;
	case	eSiteAccessoryNomal:	baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteAccessoryNomal"]["Scale"].asFloat(); break;
	case	eForestCapNomal:		baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestCapNomal"]["Scale"].asFloat(); break;
	case	eRunisCapNomal:			baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisCapNomal"]["Scale"].asFloat(); break;
	case	eSiteCapNomal:			baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteCapNomal"]["Scale"].asFloat(); break;
	case	eForestWearNomal:		baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestWearNomal"]["Scale"].asFloat(); break;
	case	eRunisWearNomal:		baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisWearNomal"]["Scale"].asFloat(); break;
	case	eSiteWearNomal:			baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteWearNomal"]["Scale"].asFloat(); break;
	case	eForestAccessoryGood:   baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestAccessoryGood"]["Scale"].asFloat(); break;
	case	eRunisAccessoryGood:    baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisAccessoryGood"]["Scale"].asFloat(); break;
	case	eSiteAccessoryGood:	    baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteAccessoryGood"]["Scale"].asFloat(); break;
	case	eForestCapGood:		    baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestCapGood"]["Scale"].asFloat(); break;
	case	eRunisCapGood:		    baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisCapGood"]["Scale"].asFloat(); break;
	case	eSiteCapGood:		    baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteCapGood"]["Scale"].asFloat(); break;
	case	eForestWearGood:	    baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestWearGood"]["Scale"].asFloat(); break;
	case	eRunisWearGood:		    baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisWearGood"]["Scale"].asFloat(); break;
	case	eSiteWearGood:		    baseScale = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteWearGood"]["Scale"].asFloat(); break;
	}

	Vec2 pos;
	switch (treasureIndex)
	{	
	case	eForestAccessoryShabby:	pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestAccessoryShabby"]["PosX"].asFloat();	pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestAccessoryShabby"]["PosY"].asFloat();	break;
	case	eRunisAccessoryShabby:	pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisAccessoryShabby"]["PosX"].asFloat();		pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisAccessoryShabby"]["PosY"].asFloat();		break;
	case	eSiteAccessoryShabby:	pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteAccessoryShabby"]["PosX"].asFloat();		pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteAccessoryShabby"]["PosY"].asFloat();		break;
	case	eForestCapShabby:		pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestCapShabby"]["PosX"].asFloat();			pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestCapShabby"]["PosY"].asFloat();			break;
	case	eRunisCapShabby:		pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisCapShabby"]["PosX"].asFloat();			pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisCapShabby"]["PosY"].asFloat();			break;
	case	eSiteCapShabby:			pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteCapShabby"]["PosX"].asFloat();			pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteCapShabby"]["PosY"].asFloat();			break;
	case	eForestWearShabby:		pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestWearShabby"]["PosX"].asFloat();			pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestWearShabby"]["PosY"].asFloat();			break;
	case	eRunisWearShabby:		pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisWearShabby"]["PosX"].asFloat();			pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisWearShabby"]["PosY"].asFloat();			break;
	case	eSiteWearShabby:		pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteWearShabby"]["PosX"].asFloat();			pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteWearShabby"]["PosY"].asFloat();			break;
	case	eForestAccessoryNomal:	pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestAccessoryNomal"]["PosX"].asFloat();		pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestAccessoryNomal"]["PosY"].asFloat();		break;
	case	eRunisAccessoryNomal:	pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisAccessoryNomal"]["PosX"].asFloat();		pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisAccessoryNomal"]["PosY"].asFloat();		break;
	case	eSiteAccessoryNomal:	pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteAccessoryNomal"]["PosX"].asFloat();		pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteAccessoryNomal"]["PosY"].asFloat();		break;
	case	eForestCapNomal:		pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestCapNomal"]["PosX"].asFloat();			pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestCapNomal"]["PosY"].asFloat();			break;
	case	eRunisCapNomal:			pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisCapNomal"]["PosX"].asFloat();			pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisCapNomal"]["PosY"].asFloat();			break;
	case	eSiteCapNomal:			pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteCapNomal"]["PosX"].asFloat();				pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteCapNomal"]["PosY"].asFloat();				break;
	case	eForestWearNomal:		pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestWearNomal"]["PosX"].asFloat();			pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestWearNomal"]["PosY"].asFloat();			break;
	case	eRunisWearNomal:		pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisWearNomal"]["PosX"].asFloat();			pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisWearNomal"]["PosY"].asFloat();			break;
	case	eSiteWearNomal:			pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteWearNomal"]["PosX"].asFloat();			pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteWearNomal"]["PosY"].asFloat();			break;
	case	eForestAccessoryGood:   pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestAccessoryGood"]["PosX"].asFloat();		pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestAccessoryGood"]["PosY"].asFloat();		break;
	case	eRunisAccessoryGood:    pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisAccessoryGood"]["PosX"].asFloat();		pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisAccessoryGood"]["PosY"].asFloat();		break;
	case	eSiteAccessoryGood:	    pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteAccessoryGood"]["PosX"].asFloat();		pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteAccessoryGood"]["PosY"].asFloat();		break;
	case	eForestCapGood:		    pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestCapGood"]["PosX"].asFloat();			pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestCapGood"]["PosY"].asFloat();			break;
	case	eRunisCapGood:		    pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisCapGood"]["PosX"].asFloat();				pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisCapGood"]["PosY"].asFloat();				break;
	case	eSiteCapGood:		    pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteCapGood"]["PosX"].asFloat();				pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteCapGood"]["PosY"].asFloat();				break;
	case	eForestWearGood:	    pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestWearGood"]["PosX"].asFloat();			pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["ForestWearGood"]["PosY"].asFloat();			break;
	case	eRunisWearGood:		    pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisWearGood"]["PosX"].asFloat();			pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["RunisWearGood"]["PosY"].asFloat();			break;
	case	eSiteWearGood:		    pos.x = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteWearGood"]["PosX"].asFloat();				pos.y = JSON_MGR->getFilePathRootWithTag("Treasure")["SiteWearGood"]["PosY"].asFloat();				break;
	}

	setAnchorPoint(Vec2(0, 1));
	setScale(baseScale);
	setPosition(pos);
}

bool CTreasure::onTouchBegan(Touch  *touch, Event  *unused)
{
	auto hits = touchHits(touch);
	if (hits){
		scaleButtonTo(baseScale-0.1f);
		return true;
	}
	return false;
}

void CTreasure::onTouchEnded(Touch  *touch, Event  *unused)
{
	auto hits = touchHits(touch);
	if (hits && _onTriggered){
		_onTriggered(this);
	}

	scaleButtonTo(baseScale);
}

void CTreasure::onTouchCancelled(Touch  *touch, Event  *unused)
{
	scaleButtonTo(baseScale);
}

bool CTreasure::touchHits(cocos2d::Touch  *touch)
{
	auto hitPos = touch->getLocation();
	auto thisPos = this->getPosition();
	auto ImageRect = this->getTextureRect();

	ImageRect.size.width /= baseScale;
	ImageRect.size.height /= baseScale;

	if ((hitPos.x >= thisPos.x && hitPos.x <= thisPos.x + ImageRect.size.width) && (hitPos.y <= thisPos.y && hitPos.y >= thisPos.y - ImageRect.size.height))
	{
		return true;
	}

	return false;
}

void CTreasure::scaleButtonTo(float scale)
{
	auto action = cocos2d::ScaleTo::create(0.05f, scale);
	action->setTag(10000);
	this->stopActionByTag(10000);
	this->runAction(action);
}