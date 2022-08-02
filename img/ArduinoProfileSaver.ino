
//---секция профиля---//
struct pr {                                     // основные поля профиля
  byte profileSteps;                            //количество шагов профиля
  int Setpoint2;                                //установленная температура(уставка)НИ
  byte pwr_BOTTOM;                              //максимальная мощность нижнего нагревателя
  byte min_pwr_TOPStep[4];                      //минимальная мощность верхнего нагревателя
  byte max_pwr_TOPStep[4];                      //максимальная мощность верхнего нагревателя
  byte rampRateStep[4];                         //скорости роста температуры по шагам
  byte temperatureStep[4];                      //заданные температуры для шагов профиля ВИ
  byte dwellTimerStep[4];                       //установленное время перехода на следующий шаг (полочка на шаге)
  byte kp1;                                     //пропорциональный коэффициент ПИД для ВИ
  byte ki1;                                     //интегральный коэффициент ПИД для ВИ
  byte kd1;                                     //дифференциальный коэффициент ПИД для ВИ
  byte kp2;                                     //пропорциональный коэффициент ПИД для НИ
  byte ki2;                                     //интегральный коэффициент ПИД для НИ
  byte kd2;                                     //дифференциальный коэффициент ПИД для НИ
};
byte SizeProfile = sizeof(pr);                  //длина поля данных
pr profile;


void setup() {
Serial.begin(9600);

profile.profileSteps=4; //1
profile.Setpoint2=200;  //2
profile.pwr_BOTTOM=160; //3
profile.min_pwr_TOPStep[0]=40; //4
profile.min_pwr_TOPStep[1]=60; //5
profile.min_pwr_TOPStep[2]=70; //6
profile.min_pwr_TOPStep[3]=80; //7
profile.max_pwr_TOPStep[0] = 55; //8
profile.max_pwr_TOPStep[1] = 65; //9
profile.max_pwr_TOPStep[2] = 75; //10
profile.max_pwr_TOPStep[3] = 85; //11
profile.rampRateStep[0] = 5; //12
profile.rampRateStep[1] = 10; //13
profile.rampRateStep[2] = 15; //14
profile.rampRateStep[3] = 20; //15
profile.temperatureStep[0]=5; //16
profile.temperatureStep[1]=6; //17
profile.temperatureStep[2]=7; //18
profile.temperatureStep[3]=8; //19
profile.dwellTimerStep[0] = 4; //20
profile.dwellTimerStep[1] = 6; //21
profile.dwellTimerStep[2] = 9; //22
profile.dwellTimerStep[3] = 7; //23
profile.kp1=30; //24
profile.ki1=40; //25
profile.kd1=55; //26
profile.kp2 = 55; //27
profile.ki2 = 54; //28
profile.kd2 = 34; //29


}
//======================================================================

void loop() {
 serialParser();  // добавить в loop
}

//======================================================================
void serialParser()  // здесь распознаются команды из телефона
{
  if (Serial.available()>0) {
    String data = Serial.readStringUntil('\n');
        
    if (data.indexOf("COMMAND_GET_PROFILE")!=-1){exportProfile(); serialPrintReady(); }
    if (data.indexOf("SHORT_PROFILE")!=-1){/*parsingShort(data);*/serialPrintReady();}
    if (data.indexOf("JSON_PROFILE")!=-1){parsingJSON(data); serialPrintReady(); }
    if (data.indexOf("COMMAND_SAVE_PROFILE")!=-1){saveProfile(); serialPrintReady();  }
    
  } 
}

void serialPrintStart(){
  Serial.print(F("{\"command\":\"REPLACE\",\"array\":["));
  }
  
void serialPrintProfileItem(String key, int value){
 Serial.print("{\"key\":\"" +  key + "\",\"value\":\"" + String(value)+ "\"}," );
 }

void serialPrintStop(String key, int value){
  Serial.print("{\"key\":\"" +  key + "\",\"value\":\"" + String(value)+ "\"}]}" );
  Serial.println();
  }

void serialPrintReady(){
     Serial.println(F("{\"command\":\"READY\"}"));
  }
  
//======================================================================

//https://jsonlint.com  проверка валидности JSON

void exportProfile() {  
 serialPrintStart();  // начало передачи
 serialPrintProfileItem(F("profileSteps"), profile.profileSteps);   //1
 serialPrintProfileItem(F("Setpoint2"), profile.Setpoint2);         //2
 serialPrintProfileItem(F("pwr_BOTTOM"), profile.pwr_BOTTOM);       //3
 serialPrintProfileItem(F("min_pwr_TOPStep[0]"), profile.min_pwr_TOPStep[0]);  //4
 serialPrintProfileItem(F("min_pwr_TOPStep[1]"), profile.min_pwr_TOPStep[1]);  //5
 serialPrintProfileItem(F("min_pwr_TOPStep[2]"), profile.min_pwr_TOPStep[2]);  //6
 serialPrintProfileItem(F("min_pwr_TOPStep[3]"), profile.min_pwr_TOPStep[3]);  //7
 serialPrintProfileItem(F("max_pwr_TOPStep[0]"), profile.max_pwr_TOPStep[0]);  //8
 serialPrintProfileItem(F("max_pwr_TOPStep[2]"), profile.max_pwr_TOPStep[1]);  //9
 serialPrintProfileItem(F("max_pwr_TOPStep[3]"), profile.max_pwr_TOPStep[2]);  //10
 serialPrintProfileItem(F("max_pwr_TOPStep[4]"), profile.max_pwr_TOPStep[3]);  //11
 serialPrintProfileItem(F("rampRateStep[0]"), profile.rampRateStep[0]);        //12
 serialPrintProfileItem(F("rampRateStep[1]"), profile.rampRateStep[1]);        //13
 serialPrintProfileItem(F("rampRateStep[2]"), profile.rampRateStep[2]);        //14
 serialPrintProfileItem(F("rampRateStep[3]"), profile.rampRateStep[3]);        //15
 serialPrintProfileItem(F("temperatureStep[0]"), profile.temperatureStep[0]);  //16
 serialPrintProfileItem(F("temperatureStep[1]"), profile.temperatureStep[1]);  //17
 serialPrintProfileItem(F("temperatureStep[2]"), profile.temperatureStep[2]);  //18
 serialPrintProfileItem(F("temperatureStep[3]"), profile.temperatureStep[3]);  //19
 serialPrintProfileItem(F("dwellTimerStep[0]"), profile.dwellTimerStep[0]);    //20
 serialPrintProfileItem(F("dwellTimerStep[1]"), profile.dwellTimerStep[1]);    //21
 serialPrintProfileItem(F("dwellTimerStep[2]"), profile.dwellTimerStep[2]);    //22
 serialPrintProfileItem(F("dwellTimerStep[3]"), profile.dwellTimerStep[3]);    //23
 serialPrintProfileItem(F("kp1"), profile.kp1);  //24
 serialPrintProfileItem(F("ki1"), profile.ki1);  //25
 serialPrintProfileItem(F("kd1"), profile.kd1);  //26
 serialPrintProfileItem(F("kp2"), profile.kp2);  //27
 serialPrintProfileItem(F("ki2"), profile.ki2);  //28
 serialPrintStop(F("kd2"), profile.kd2);         //29 и завершение передачи
}

// пример входящей строки: SHORT_PROFILE:1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,
void parsingShort (String input) {
 int end;
 int outputArray[29];
 int counter = 0;
 input.remove(0,input.indexOf(":")+1);

 while((end=input.indexOf(","))!=-1){
  String num = input.substring(0,end);
  input= input.substring(end+1,input.length());
  outputArray[counter]=num.toInt();
  counter++;
 }

profile.profileSteps=outputArray[0]; // 1
profile.Setpoint2=outputArray[1]; // 2
profile.pwr_BOTTOM=outputArray[2]; //3
profile.min_pwr_TOPStep[0]=outputArray[3]; //4
profile.min_pwr_TOPStep[1]=outputArray[4]; //5
profile.min_pwr_TOPStep[2]=outputArray[5]; //6
profile.min_pwr_TOPStep[3]=outputArray[6]; //7
profile.max_pwr_TOPStep[0] = outputArray[7]; //8
profile.max_pwr_TOPStep[1] = outputArray[8]; //9
profile.max_pwr_TOPStep[2] = outputArray[9]; //10
profile.max_pwr_TOPStep[3] = outputArray[10]; //11
profile.rampRateStep[0] = outputArray[11]; //12
profile.rampRateStep[1] = outputArray[12]; //13
profile.rampRateStep[2] = outputArray[13]; //14
profile.rampRateStep[3] = outputArray[14]; //15
profile.temperatureStep[0]=outputArray[15]; //16
profile.temperatureStep[1]=outputArray[16]; //17
profile.temperatureStep[2]=outputArray[17]; //18
profile.temperatureStep[3]=outputArray[18]; //19
profile.dwellTimerStep[0] = outputArray[19];  //20
profile.dwellTimerStep[1] = outputArray[20];  //21
profile.dwellTimerStep[2] = outputArray[21];  //22
profile.dwellTimerStep[3] = outputArray[22];  //23
profile.kp1=outputArray[23]; //24
profile.ki1=outputArray[24]; //25
profile.kd1=outputArray[25]; //26
profile.kp2 = outputArray[26]; //27
profile.ki2 = outputArray[27]; //28
profile.kd2 = outputArray[28]; //29
}

// пример входящей строки:  {"JSON_PROFILE":{"profileSteps":4,"Setpoint2":20,"min_pwr_TOPStep[1]":10,"min_pwr_TOPStep[2]":20,"min_pwr_TOPStep[3]":30,"min_pwr_TOPStep[4]":40,"max_pwr_TOPStep[1]":40,"max_pwr_TOPStep[2]":50,"max_pwr_TOPStep[3]":60,"max_pwr_TOPStep[4]":70,"rampRateStep[1]":5,"rampRateStep[2]":6,"rampRateStep[3]":7,"rampRateStep[4]":8,"temperatureStep[1]":6,"temperatureStep[2]":7,"temperatureStep[3]":8,"temperatureStep[4]":9,"dwellTimerStep[1]":5,"dwellTimerStep[2]":5,"dwellTimerStep[3]":5,"dwellTimerStep[4]":5,"kp1":100,"ki1":100,"kd1":100,"kp2":100,"ki2":100,"kd2":100}}
void parsingJSON (String data) {
  //
  }

void saveProfile (){
  //
 }
