
// raw
int _sensor_throttle;
int _sensor_motor_temp;
int _sensor_driver_temp;
int _sensor_voltage;

// interpreted
float throttle_percent;
float motor_temperature;
float driver_temperature;
float battery_voltage;
float battery_percentage;

#define BATTERY_HISTORY_SIZE 100
float battery_voltage_history[BATTERY_HISTORY_SIZE];
unsigned int battery_voltage_history_iterator = 0;

#define throttle_pin A0
#define motor_temp_pin A1
#define driver_temp_pin A2
#define voltage_pin A3

void sensors_setup(){
  
  pinMode(throttle_pin, INPUT);
  pinMode(motor_temp_pin, INPUT);
  pinMode(driver_temp_pin, INPUT);
  pinMode(voltage_pin, INPUT);

  //Serial.begin(9600);
}

float interprete_temperature(int sensor_input){
  float VCC = 5;
  float R = 10000;
  float B = 3977;
  float RT0 = 10000;
  float T0 = 25 + 273.15;

  float VRT = (5.00 / 1023.00) * sensor_input;    //Conversion to voltage
  float VR = VCC - VRT;
  float RT = VRT / (VR / R);                      //Resistance of RT
  float ln = log(RT / RT0);
  float TX = (1 / ((ln / B) + (1 / T0)));         //Temperature from thermistor
  return TX - 273.15;    
}

float interperate_throttle(int sensor_input) {    // NOT TESTED
  return map(_sensor_throttle, 175, 850, 0, 100);
}

float interprete_battery_volatage(int sensor_input){
  return 13.318 * (5.0 / 1023.0) * sensor_input;
}

float interprete_battery_percentage(float voltage){
  float charge_left = -3142.3*pow(voltage,6) + 54836*pow(voltage,5) - 389293*pow(voltage,4) + 1*pow(10,6)*pow(voltage,2) + 3*pow(10,6) * voltage - 1E+06;
  charge_left = 3325 - charge_left;
  return (charge_left / 3325) * 100; 
}

void sensors_loop(){
  _sensor_throttle = analogRead(throttle_pin);
  _sensor_motor_temp = analogRead(motor_temp_pin);
  _sensor_driver_temp = analogRead(driver_temp_pin);
  _sensor_voltage = analogRead(voltage_pin);
  
  throttle_percent = map(_sensor_throttle, 175, 850, 0, 100);
  motor_temperature = interprete_temperature(_sensor_motor_temp);
  driver_temperature = interprete_temperature(_sensor_driver_temp);
  battery_voltage = interprete_battery_volatage(_sensor_voltage);
  battery_percentage = interprete_battery_percentage(battery_voltage);


  //Serial.println("senrsor: " + String(sensor_throttle));
  //Serial.println("motor_temp_raw: " + String(sensor_motor_temp));
  //Serial.println("driver_temp_raw: " + String(sensor_driver_temp));

  //Serial.println("motor_temp: " + String(interperate_temperature(sensor_motor_temp)));
  //Serial.println("driver_temp: " + String(interperate_temperature(sensor_driver_temp)));

}
