/* this sketch is used for adjusting raw data of H3LIS331DL to make it more precise
 * auth : lawliet(lawliet.zou@gmail.com)
 * version : 0.1
 */

#include <H3LIS331DL.h>
#include <Wire.h>

H3LIS331DL h3lis;

char* tag[] = {"Z+","Z-","Y+","Y-","X+","X-"};
int16_t dataBuf[6][3] = {0};

void setup(){
  Serial.begin(9600);
  h3lis.init();
  getAdjParameter();
}

void loop(){
  //nothing to do
}

void getAdjParameter()
{
    AxesRaw_t data;
    int32_t sum[3] = {0};
  	
    Serial.println("Start ...");
    delay(3000);
    for(int timer = 0; timer < 6; timer++){
      Serial.print("please turn ");
      Serial.print(tag[timer]);
      Serial.println(" up");
      delay(3000);
      for(int i = 0; i < 5; i++){
        Serial.print("start will be in ");
        Serial.print(5-i);
        Serial.println(" seconds");
        delay(1000);
      }
      Serial.println("calculating ... ");
      for(int i = 0 ; i < 100; i++){
        status_t response = h3lis.getAccAxesRaw(&data);
        if(MEMS_SUCCESS == response){
          sum[0] += data.AXIS_X;
    	  sum[1] += data.AXIS_Y;
    	  sum[2] += data.AXIS_Z;
        }
        delay(20);
     }
     dataBuf[timer][0] = sum[0]/100;
     dataBuf[timer][1] = sum[1]/100;
     dataBuf[timer][2] = sum[2]/100;
     sum[0] = sum[1] = sum[2] = 0;
     Serial.println("calculate success");
     delay(1000);
   }
   int16_t axis_x = (dataBuf[4][0] + dataBuf[5][0])*0.3 + (dataBuf[0][0]+dataBuf[1][0]+dataBuf[2][0]+dataBuf[3][0])/10;   
   Serial.print("adjust value of X axis is ");
   Serial.println(axis_x);
   int16_t axis_y = (dataBuf[2][1] + dataBuf[3][1])*0.3 + (dataBuf[0][1]+dataBuf[1][1]+dataBuf[4][1]+dataBuf[5][1])/10;
   Serial.print("adjust value of Y axis is ");
   Serial.println(axis_y);
   int16_t axis_z = (dataBuf[0][2] + dataBuf[1][2])*0.3 + (dataBuf[2][2]+dataBuf[3][2]+dataBuf[4][2]+dataBuf[5][2])/10;
   Serial.print("adjust value of Z axis is ");
   Serial.println(axis_z);
   Serial.println("note: these data can be used in H3LISDL_Demo sketch");
}
