#pragma once
#include "cocos2d.h"
#include "Macro.h"
#include <list>

USING_NS_CC;

#define LOOPACTIVE (Sprite*)-1
#define LOOPEND (Sprite*)-2

class CAnimation
{
private:
	Vector<Sprite*> frameImage;
	
	//애니매이션이 루프인가
	bool isLoop;
	//루프가 끝났는가
	bool isLoopEnd;

	//프레임 사이즈
	float frameSize;
	//프래임 간격
	float frameRate;
	//현재 누적시간
	float curDeltaTime;
	//현재 누적 프레임 카운트
	int curFrameCount;

public:
	CAnimation();
	~CAnimation();

	bool init(float FrameRate, bool loop);
	void addFrame(const std::string anipath);
	Sprite* run(float dt);
	static CAnimation* create(float FrameRate, bool loop);
	
public:
	//set
	void setCurFrame(int count) { curFrameCount = count;}
	void setAniEnd(bool _isLoopEnd) { isLoopEnd = _isLoopEnd; }
	void setAniLoop(bool _Loop) { isLoop = _Loop; }
	void setAnimationFrame(Sprite* spr, int index);

	//get
	int getCurFrame() const { return curFrameCount; }
	bool getAniEnd() const { return isLoopEnd; }
	bool getAniLoop() const { return isLoop; }
	Sprite* getAnimationFrame(int index);
};

