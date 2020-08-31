#ifndef POTENTIOMETER
#define POTENTIOMETER

#define PWMMAX uint8_t(180)
#define PWMMIN uint8_t(0)

class Potentiometer{
public:
	Potentiometer(uint8_t pin, uint8_t minV = 0, uint8_t maxV = 1023)
	: _pin(pin), _maxV(maxV), _minV(minV){
	  pinMode(pin, INPUT_PULLUP);
	}
	uint16_t getVoltage(){
		return analogRead(_pin);
	}
	uint8_t getPwmValue(){
		return map(analogRead(_pin), _minV, _maxV, PWMMIN, PWMMAX);
	}
	uint8_t getPin(){
		return _pin;
	}
private:
	uint8_t _pin;
	uint8_t _maxV;
	uint8_t _minV;
};

#endif 
