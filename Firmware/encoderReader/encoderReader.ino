//     A0 - PC0 - BUTA
//     A1 - PC1 - BUTB
//     A2 - PC2 - BUTC
//     A3 - PC3 - BUTD
//      - 
//     D2 - PD2 - ENCA1
//     D3 - PD3 - ENCA2
//     D4 - PD4 - ENCB1
//     D5 - PD5 - ENCB2
//     D6 - PD6 - ENCC1
//     D7 - PD7 - ENCC2
//     D8 - PB0 - ENCD1
//     D9 - PB1 - ENCD2

const int BUTA = A0;
const int BUTB = A1;
const int BUTC = A2;
const int BUTD = A3;

const int ENCA1 = 2;
const int ENCA2 = 3;
const int ENCB1 = 4;
const int ENCB2 = 5;
const int ENCC1 = 6;
const int ENCC2 = 7;
const int ENCD1 = 8;
const int ENCD2 = 9;

int encState[8] = {0,0,0,0,0,0,0,0};
int encDeb[8] = {100,100,100,100,100,100,100,100}; //debounce < duracao do pulso em millis
int encDel[8] = {100,100,100,100,100,100,100,100}; //del > duracao do pulso em millis
int encLast[8] = {0,0,0,0,0,0,0,0};

int encVal[8] = {};

int knobMode = 0; 	//0 = raw(cada encoder controla 1 grupo de led
					//1 = grupos, encoder A = todos os LEDs, B = Frios

float offVtg = 0.25;
float onVtg = 1.3;
float refVtg = 3.3;

byte offByte;
byte onByte;
int encConstraints = 1000;


void setup(){

	Wire.begin();

	//pinMode(2, INPUT);
    //pinMode(3, INPUT);
    //pinMode(4, INPUT);
    //pinMode(5, INPUT);
    //pinMode(6, INPUT);
    //pinMode(7, INPUT);
    DDRD &= 0b11111011;
	//DDRD &= ~(1 << PD2);
	//DDRD &= ~(1 << PD3);
	//DDRD &= ~(1 << PD4);
	//DDRD &= ~(1 << PD5);
	//DDRD &= ~(1 << PD6);

    //pinMode(8, INPUT);
    //pinMode(9, INPUT);
	DDRB &= ~(1 << PB0);
	DDRB &= ~(1 << PB1);

	//pinMode(BUTA ,INPUT);
	//pinMode(BUTB ,INPUT);
	//pinMode(BUTC ,INPUT);
	//pinMode(BUTD ,INPUT);
	DDRC &= ~(1 << PC0);
	DDRC &= ~(1 << PC1);
	DDRC &= ~(1 << PC2);
	DDRC &= ~(1 << PC3);


	offByte = (offVtg/refVtg) * 4096;
	onByte = (onVtg/refVtg) * 4096;

}

void loop(){

	//1001000 broadcast address

	//0x0C	#12	0001100	ADR1 NC		ADR0 NC
	//0x0D	#13 0001101	ADR1 NC		ADR0 GND
	//0x0E	#14	0001110	ADR1 NC		ADR0 VA
	//0x08	#8	0001000	ADR1 GND	ADR0 NC

	Wire.beginTransmission(12);		// transmit to device
	Wire.write("0000" + string(4096,BIN));

	Wire.write(byte(0x00));			// 
	Wire.write(byte(0x00));			// 
	Wire.endTransmission();

	Wire.beginTransmission(13);		// transmit to device
	Wire.write(byte(0x00));			// 
	Wire.write(byte(0x00));			// 
	Wire.endTransmission();

	Wire.beginTransmission(14);		// transmit to device
	Wire.write(byte(0x00));			// 
	Wire.write(byte(0x00));			// 
	Wire.endTransmission();

	Wire.beginTransmission(8);		// transmit to device
	Wire.write(byte(0x00));			// 
	Wire.write(byte(0x00));			// 
	Wire.endTransmission();

/*
For a write operation, the master follows the ACK by sending the upper eight data bits to the DAC121C081. Then the DAC121C081 ACKs the transfer by driving SDA low. Next, the lower eight data bits are sent by the master. The DAC121C081 then ACKs the transfer. At this point, the DAC output updates to reflect the contents of the 16-bit DAC register. Next, the master either sends another pair of data bytes, generates a Stop condition to end communication, or generates a Repeated Start condition to communicate with another device on the bus.
*/

	encState[0] = (PIND & (1<<PD2));    //Read the PORTD pin 2 value and put it in the variable
	encState[1] = (PIND & (1<<PD3));
	encState[2] = (PIND & (1<<PD4));
	encState[3] = (PIND & (1<<PD5));
	encState[4] = (PIND & (1<<PD6));
	encState[5] = (PIND & (1<<PD7));
	encState[6] = (PINB & (1<<PB0));
	encState[7] = (PINB & (1<<PB1));

	for(int i =0;i<8;i++){
		if(encState[i] && encLast[i] - millis() > encDel[i]){
			encLast[i] = millis();
			encTrig == false;
		}

		if(encState[i] && encLast[i] - millis() > endDeb[i] && encTrig == false){
			encTrig[i] == true;
		}


	}


	if(knobMode == 0){
		if(encTrig[0]) encVal[0]++;
		if(encTrig[1]) encVal[1]--;
		if(encTrig[2]) encVal[2]++;
		if(encTrig[3]) encVal[3]--;
		if(encTrig[4]) encVal[4]++;
		if(encTrig[5]) encVal[5]--;
		if(encTrig[6]) encVal[6]++;
		if(encTrig[7]) encVal[7]--;

		for(int i =0;i<8;i++){
			encVal[i] = constrain(encVal, -1*encConstraints, encConstraints)
			encTrig[i] = false;
		}
	}
	else if(knobMode == 1){

	}

}














