#pragma once

#include "Button.h"
#include "enumData.h"
#include "SingleTon.h"

class CButtonData: public SingleTon<CButtonData>
{
private:
	ButtonState buttonState;
	CButton* button;

public:
	CButtonData()
	{
		buttonState = (ButtonState)-1;
		button = nullptr;
	}

public:
	void setButtonState(ButtonState _buttonState) { buttonState = _buttonState; }
	void setButton(CButton* _button) { button = _button; }

	ButtonState getButtonState() const { return buttonState; }
	CButton* getButton() const { return button; }
};
#define ButtonData CButtonData::getInstance()