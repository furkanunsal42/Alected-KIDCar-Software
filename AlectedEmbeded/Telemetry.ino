
extern float chart_values[];

extern int pwm;
extern float battery_voltage;
extern float battery_percentage;
extern float throttle_percent;
extern float motor_temperature;
extern float driver_temperature;
extern float velocity; 

char seperation_character = ',';
char termination_character = '\n';

void telemetry_setup(){
	Serial1.begin(9600);

}

// data format; velocity(float) motor_temperature(float) driver_temperature(float) current(float) voltage(float) battary_persentage(float) 6th_parameter(float) termination_character(1byte) 

void telemetry_loop(){
  // pwm
  Serial1.print(pwm);
  Serial1.print(seperation_character);

  // velocity
  Serial1.print(velocity);
  Serial1.print(seperation_character);

  // battery voltage
  Serial1.print(battery_voltage);
  Serial1.print(seperation_character);

  // battery persentage
  Serial1.print(battery_percentage);
  Serial1.print(seperation_character);


  // driver temperature
  Serial1.print(driver_temperature);
  Serial1.print(seperation_character);

  // motor temperature
  Serial1.print(motor_temperature);
  //Serial1.print(seperation_character);

  //direction state

  Serial1.print(termination_character);
}