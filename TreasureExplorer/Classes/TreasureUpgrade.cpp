#include "PCH.h"
#include "TreasureRoomScene.h"
#include "TreasureUpgrade.h"
#include "Treasure.h"
#include "soundManager.h"

CTreasureUpgrade::CTreasureUpgrade()
{
	treasureIndex = (TreasureIndex)-1;
	treasureType = (TreasureType)-1;
	treasure = nullptr;
	xmlTag = "";
	treasureName = "";
	backImage = nullptr;
	upgradeUi = nullptr;
	curCoinLabel = nullptr;
	useCoinLabel = nullptr;
	isUpgrade = false;
}


CTreasureUpgrade::~CTreasureUpgrade()
{
}

bool CTreasureUpgrade::init(TreasureIndex _index, TreasureType _type, std::string _xmlTag, std::string _treasureName)
{
	if (!Layer::init())
	{
		return false;
	}

	treasureIndex = _index;
	treasureType = _type;
	xmlTag = _xmlTag;
	treasureName = _treasureName;

	generaterTreasureUpgrade();
	generaterCoinLabel();
	scheduleUpdate();

	return true;
}

void CTreasureUpgrade::update(float dt)
{
	if (treasure->getActionByTag(UPGRADEACTION) == nullptr && isUpgrade == true)
	{
		if (treasureType == eShabby)
		{
			enterUpgradeShabby();
			isUpgrade = false;
		}
		else if (treasureType == eNomal)
		{
			enterUpgradeNomal();
			isUpgrade = false;
		}
	}
}

void CTreasureUpgrade::generaterTreasureUpgrade()
{
	backImage = Sprite::create("background/TreasureUpgrade/backImage.png");
	backImage->setAnchorPoint(Vec2(0.5, 0.5));
	backImage->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(backImage, TAG_BACKIMAGE);

	treasure = CTreasure::create(treasureIndex, xmlTag, treasureName);
	treasure->setAnchorPoint(Vec2(0.5, 0.5));
	treasure->setPosition(Vec2(backImage->getPosition().x - 200, backImage->getPosition().y+100));
	this->addChild(treasure, TAG_TREASURE);

	auto upgradeButton = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["Upgrade_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["Upgrade_1"].asString(), CC_CALLBACK_1(CTreasureUpgrade::enterUpgradeUi, this));
	auto exitButton = MenuItemImage::create(JSON_MGR->getFilePathRootWithTag("Button")["Upgrade_back_0"].asString(), JSON_MGR->getFilePathRootWithTag("Button")["Upgrade_back_1"].asString(), CC_CALLBACK_1(CTreasureUpgrade::enterUpgradeUi, this));
	upgradeButton->setTag(TAG_UPGRADE);
	exitButton->setTag(TAG_EXIT);

	upgradeButton->setPosition(backImage->getPosition().x+250, backImage->getPosition().y - 100);
	exitButton->setPosition(backImage->getPosition().x + 430, backImage->getPosition().y + 200);
	upgradeUi = Menu::create(upgradeButton, exitButton, NULL);
	upgradeUi->setPosition(Vec2(0, 0));
	this->addChild(upgradeUi, TAG_UI_BUTTON);
}

void CTreasureUpgrade::generaterCoinLabel()
{
	if (treasureType == eShabby)
	{
		int curCoin = UserDefault::getInstance()->getIntegerForKey("Coin");
		curCoinLabel = Label::createWithTTF(StringUtils::toString(curCoin), "fonts/MoebiusBold.ttf", 50);
		useCoinLabel = Label::createWithTTF("300", "fonts/MoebiusBold.ttf", 50);
		
		if (curCoin > SHABBYUPGRADECOIN)
			curCoinLabel->setColor(Color3B(0, 0, 0));
		else
			curCoinLabel->setColor(Color3B(255, 0, 0));
		curCoinLabel->setPosition(backImage->getPosition().x + 200, backImage->getPosition().y + 200);
		useCoinLabel->setPosition(backImage->getPosition().x + 200, backImage->getPosition().y);
		this->addChild(curCoinLabel, 10);
		this->addChild(useCoinLabel, 11);
	}
	else if (treasureType == eNomal)
	{
		int curCoin = UserDefault::getInstance()->getIntegerForKey("Coin");
		curCoinLabel = Label::createWithTTF(StringUtils::toString(curCoin), "fonts/MoebiusBold.ttf", 50);
		useCoinLabel = Label::createWithTTF("500", "fonts/MoebiusBold.ttf", 50);

		if (curCoin > SHABBYUPGRADECOIN)
			curCoinLabel->setColor(Color3B(0, 0, 0));
		else
			curCoinLabel->setColor(Color3B(255, 0, 0));
		curCoinLabel->setPosition(backImage->getPosition().x + 200, backImage->getPosition().y + 200);
		useCoinLabel->setPosition(backImage->getPosition().x + 200, backImage->getPosition().y);
		this->addChild(curCoinLabel, 10);
		this->addChild(useCoinLabel, 11);
	}
}

void CTreasureUpgrade::enterUpgradeUi(Ref* sender)
{
	CSoundManager::getInstance()->playEffect("sound/button_1.mp3");
	auto item = (MenuItem*)sender;

	if (item->getTag() == TAG_UPGRADE)
	{
		if (treasure->getActionByTag(UPGRADEACTION) == nullptr)
		{
			if (treasureType == eShabby)
			{
				if (UserDefault::getInstance()->getIntegerForKey("Coin") >= SHABBYUPGRADECOIN)
				{
					auto ref = Repeat::create(Sequence::create(ScaleBy::create(0.2f, 0.8f), ScaleBy::create(0.2f, 1.2f), NULL), 4);
					ref->setTag(UPGRADEACTION);
					treasure->runAction(ref);
					isUpgrade = true;
				}

			}
			else if (treasureType == eNomal)
			{
				if (UserDefault::getInstance()->getIntegerForKey("Coin") >= NOMALUPGRADECOIN)
				{
					auto ref = Repeat::create(Sequence::create(ScaleBy::create(0.2f, 0.8f), ScaleBy::create(0.2f, 1.2f), NULL), 4);
					ref->setTag(UPGRADEACTION);
					treasure->runAction(ref);
					isUpgrade = true;
				}
			}
		}
	}
	else if (item->getTag() == TAG_EXIT)
	{
		runAction(Sequence::create(MoveTo::create(0.3f, Vec2(0,100)), MoveTo::create(0.5f, Vec2(0, -650)), 
			CallFunc::create(CC_CALLBACK_0(CTreasureUpgrade::enterRemove, this)), NULL));
	}
}

void CTreasureUpgrade::enterRemove()
{
	auto scene = static_cast<CTreasureRoomScene*>(Director::getInstance()->getRunningScene()->getChildByName("CTreasureRoomScene"));
	scene->treasureResume();
	this->removeFromParentAndCleanup(true);
}

void CTreasureUpgrade::enterUpgradeShabby()
{
	int treasureIndexInt = (int)treasureIndex;
	treasureIndexInt += 9;
	treasureIndex = (TreasureIndex)treasureIndexInt;

	//코인 사용 
	int coin = UserDefault::getInstance()->getIntegerForKey("Coin");
	coin -= 300;
	curCoinLabel->setString(StringUtils::toString(coin));
	useCoinLabel->setString(StringUtils::toString(500));
	
	if (coin > NOMALUPGRADECOIN)
		curCoinLabel->setColor(Color3B(0, 0, 0));
	else
		curCoinLabel->setColor(Color3B(255, 0, 0));

	UserDefault::getInstance()->setIntegerForKey("Coin", coin);
	UserDefault::getInstance()->setIntegerForKey(xmlTag.c_str(), (int)treasureIndex);

	int  _treasureType = treasureType;
	_treasureType += 1;
	treasure->setTexture(CTreasure::create(treasureIndex, xmlTag, treasureName)->getTexture());
	treasureType = (TreasureType)_treasureType;
	float scale = treasure->getBaseScale();
	treasure->setScale(scale);
}

void CTreasureUpgrade::enterUpgradeNomal()
{
	int treasureIndexInt = (int)treasureIndex;
	treasureIndexInt += 9;
	treasureIndex = (TreasureIndex)treasureIndexInt;

	//코인 사용 
	int coin = UserDefault::getInstance()->getIntegerForKey("Coin");
	coin -= 500;
	curCoinLabel->setString(StringUtils::toString(coin));
	useCoinLabel->setString("MAX");
	
	UserDefault::getInstance()->setIntegerForKey("Coin", coin);
	UserDefault::getInstance()->setIntegerForKey(xmlTag.c_str(), (int)treasureIndex);

	int  _treasureType = treasureType;
	_treasureType += 1;
	treasure->setTexture(CTreasure::create(treasureIndex, xmlTag, treasureName)->getTexture());
	treasureType = (TreasureType)_treasureType;
}