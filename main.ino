int ThermistorPin = A0;
int Vo;
float R1 = 10000; // value of R1 on board
float logR2, R2, T;
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741; //steinhart-hart coeficients for thermistor

void setup() {
	Serial.begin(9600);
}

float readTemp(int thermistorPin){
	Vo = analogRead(ThermistorPin);
	R2 = R1 * (1023.0 / (float)Vo - 1.0); //calculate resistance on thermistor
	logR2 = log(R2);
	T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // temperature in Kelvin
	return T - 273.15; //convert Kelvin to Celcius
}

float readAverageTemp(int thermistorPin, int maxDelay, int delayAmount = 1 ){ //Delay amount in polling per half second
	float average = 0;
	int delayTime = maxDelay / delayAmount;
	for ( uint8_t i = 0; i < delayAmount; i++){
		average += readTemp(ThermistorPin);
    	delay(delayTime);
	};
	return average / delayAmount;
}

void loop() {
	T = readAverageTemp(ThermistorPin, 4, 500);
	Serial.print("Average Temperature: "); 
	Serial.print(T);
	Serial.println(" C");
}