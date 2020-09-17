#ifndef JOYSTICK
#define JOYSTICK

#define PWMMAX 180
#define PWMMIN 0

#define PWMMAX 180
#define PWMMIN 0

class Joystick{
public:
	Joystick(uint16_t x, uint16_t y, uint16_t button, uint8_t minV = 0, uint8_t maxV = 1023)
	: _x(x), _y(y), _button(button), _minV(minV), _maxV(maxV){
		pinMode(_x, INPUT);
		pinMode(_y, INPUT);
		pinMode(_button, INPUT);
	}
	uint16_t getX(){
		return analogRead(_x);
	}
	uint16_t getY(){
		return analogRead(_y);
	}
	uint8_t getButton(){
		return _button;
	}
	uint8_t getPwmValueX(){
		return map(analogRead(_x), _minV, _maxV, PWMMIN, PWMMAX);
	}
	uint8_t getPwmValueY(){
		return map(analogRead(_y), _minV, _maxV, PWMMIN, PWMMAX);
	}
private:
	uint16_t _x;
	uint16_t _y;
	uint8_t _button;
	uint8_t _minV;
	uint8_t _maxV;
};

#endif JOYSTICK
