/*
Work by Vignesh Ravichandran (hello@rvignesh.xyz).

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Color definitions
#define  BLACK          0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

#include <MQTT.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1331.h"
#include "TSL2561.h"
#include "application.h"
#include "Particle-GPS.h"

Gps _gps = Gps(&Serial1);	// TX and RX pins on the Photon and Electron.
TSL2561 tsl(TSL2561_ADDR_FLOAT); 
Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, rst);
Timer _timer = Timer(1, onSerialData);
double lat, long;
int ir=4;
int red=3;
uint16_t ired,iir,iredmax,iirmax,iredsum,iirsum;
uint16_t transred,transir,cci;
uint32_t tsLastReport = 0;
uint32_t tsLastReport1 = 0;
char *IOT_CLIENT = "Enter client id";  
char *IOT_HOST = "Enter Host link";  
char *IOT_PASSWORD = "Enter password";
char *IOT_PUBLISH = "";  
char *IOT_USERNAME = "use-token-auth";
int count = 0;

MQTT client( IOT_HOST, 1883, callback );

void setup()
{

    Serial.begin(115200);
    // Initialize the PulseOximeter instance and register a beat-detected callback
    _gps.begin(9600);
    _gps.sendCommand(PMTK_SET_NMEA_OUTPUT_ALLDATA);
    
    client.connect( 
    IOT_CLIENT, 
    IOT_USERNAME, 
    IOT_PASSWORD 
  );
  display.begin();
  display.fillScreen(BLACK);
  display.setCursor(0,0);
  display.print("FarmCorder     boot-check:");
  delay(2000);
  display.fillScreen(BLACK);
  display.setCursor(0,10);
  if( client.isConnected() ) {
    Serial.println( "Connected." );
    Particle.publish("Connected. ");
    client.subscribe( IOT_SUBSCRIBE );
    display.print("Connected to IBM server");
    delay(1000);
    display.fillScreen(BLACK);
    display.setCursor(0,0);
    display.setTextColor(BLUE,BLACK);
    display.setTextSize(1);
    do
    {
    display.print("Press button to begin  measurement");
    }
    while(!digitalRead(D2))  //Push button pull down
    delay(1000);
    display.fillScreen(BLACK);
    display.setCursor(0,0);
    display.setTextColor(GREEN, BLACK);
    display.setTextSize(1);    
    do
   {
   display.print("Please connect:Leaf Probe     sensor");   
   }
   while(!tsl.begin());
   
   display.fillScreen(BLACK);
   display.setTextColor(WHITE, BLACK);
   display.setCursor(0,10);
   display.print("Calibrating    Sensor!");   
  }
  delay(1000);
  digitalWrite(red,HIGH);
           ired = tsl.getLuminosity(TSL2561_VISIBLE);     
           iredmax=ired;
           ired=0;
  display.fillScreen(BLACK);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0,0);
  display.print("RedVal=");
  display.print(iredmax);
  digitalWrite(red , LOW);   
  delay(1000);
  digitalWrite(ir,HIGH);   
           iir = tsl.getLuminosity(TSL2561_INFRARED);     
           iirmax=iir;
           iir=0;
  display.fillScreen(BLACK);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0,0);
  display.print("IRVAL=");
  display.print(iirmax);
  digitalWrite(ir,LOW); 
  display.fillScreen(BLACK);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0,0);
  display.print("DONE, Finding GPS coordinates");
  delay(5000);
  
}

void loop()
{
Pgtop pgtop = Pgtop(_gps);
if (gga.parse())

Gga gga = Gga(_gps);
lat= gga.latitude;
long=gga.longitude;
display.fillScreen(BLACK);
display.setTextColor(WHITE, BLACK);
display.setCursor(0,0);
display.print("lat=");
display.print(lat);
display.setCursor(0,20);
display.print("long=");
display.print(long);
delay(3000);
display.fillScreen(BLACK);
display.setTextColor(WHITE, BLACK);
display.setCursor(0,0);
display.print("DONE, Clip leaf");
delay(5000);
display.fillScreen(BLACK);
do
{
 display.print("Press button to begin  measurement");
}
while(!digitalRead(D2))  //Push button pull down
digitalWrite(red,HIGH);
ired = tsl.getLuminosity(TSL2561_VISIBLE);            
digitalWrite(red , LOW);   
digitalWrite(ir,HIGH);   
iir = tsl.getLuminosity(TSL2561_INFRARED);     
digitalWrite(ir,LOW); 
transred=(ired/(iredmax))*100;
transir=(iir/iirmax)*100;
cci=transir/transred;
display.fillScreen(BLACK); 
display.setTextColor(GREEN, BLACK);
display.setCursor(0,10);  
display.print("Chlorophyll    Index:");
display.setCursor(0,30);
display.print(cci);
delay(2000);
display.fillScreen(BLACK); 
do
{
 display.print("Press button to begin  send");
}
while(!digitalRead(D2))  //Push button pull down
delay(1000);
display.fillScreen(BLACK); 
display.setCursor(0,10);
display.print("Sending...");
Particle.publish("CCI", String(cci));
Particle.publish("lat", String(lat));
Particle.publish("long", String(long));
String data = "{";
  data+="\"CCI\": ";
  data+=(int)cci;
  data+= ",";
  data+="\n";
  data+="\"la\": ";
  data+=(int)lat;
  data+= ",";
  data+="\n";
  data+="\"lo\": ";
  data+=(int)long;
  data+="\n";
  data+="}";
client.loop();

if(client.publish(IOT_PUBLISH,data))
{
display.fillScreen(BLACK); 
display.setCursor(0,0);
display.print("Sent");
}

void callback( char* topic, byte* payload, unsigned int length ) {  
  char p[length + 1];

  memcpy( p, payload, length );
  p[length] = NULL;

  String message( p );
}
