#include "PCH.h"
#include "Animation.h"


CAnimation::CAnimation()
{
	frameImage.clear();
	frameRate = 0;
	frameSize = 0;
	curDeltaTime = 0;
	curFrameCount = 0;
	isLoopEnd = false;

}


CAnimation::~CAnimation()
{
}

bool CAnimation::init(float FrameRate, bool loop)
{
	frameImage.reserve(10);
	frameRate = FrameRate;
	isLoop = loop;
	isLoopEnd = true;

	return true;
}

void CAnimation::addFrame(const std::string anipath)
{
	Sprite* spr = Sprite::create(anipath.c_str());
	spr->setTag(frameSize);
	frameSize++;
	frameImage.pushBack(spr);
}

Sprite* CAnimation::run(float dt)
{
	Sprite* spr = nullptr;
	
	curDeltaTime += dt;

	//루프가 끝나지 않았다면
	if (isLoopEnd)
	{
		//현재 카운트 델타타임이 간격보다 크면
		if (curDeltaTime > frameRate)
		{
			// 현재 프레임을 받아와서 
			for (Sprite* pSprite : frameImage)
			{
				if (pSprite->getTag() == curFrameCount)
				{
					spr = pSprite;
					curFrameCount++;
					curDeltaTime = 0.0f;
					break;
				}
			}
			// 현재 카운트가 간격을 넘었을때
			if (curFrameCount >= frameSize)
			{
				if (isLoop)
				{
					curFrameCount = 0;
				}
				else
				{
					isLoopEnd = false;
					spr = LOOPEND;
					curFrameCount = 0;
					curDeltaTime = 0.0f;
				}
			}
		}
		else
		{
			spr = LOOPACTIVE;
		}
	}
	else
	{
		spr = LOOPEND;
	}
	
	return spr;
}

CAnimation* CAnimation::create(float FrameRate, bool loop)
{
	CAnimation* ani = new CAnimation();
	if (!ani->init(FrameRate, loop))
	{
		delete ani;
		ani = nullptr;
		return nullptr;
	}
	return ani;
}

void CAnimation::setAnimationFrame(Sprite* spr, int index)
{
	for (Sprite* pSprite : frameImage)
	{
		if (pSprite->getTag() == index)
		{
			pSprite = spr;
			break;
		}
	}
}

Sprite* CAnimation::getAnimationFrame(int index)
{
	for (Sprite* pSprite : frameImage)
	{
		if (pSprite->getTag() == index)
		{
			return pSprite;
		}
	}
}