// This #include statement was automatically added by the Particle IDE.
#include <ThingSpeak.h>

// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT_Particle.h>

#define DHTPIN D2     // what pin we're connected to

#define DHTTYPE DHT11		// DHT 11 

int counter = 0;

DHT dht(DHTPIN, DHTTYPE);

TCPClient client;

unsigned long myChannelNumber = 2497723;
const char * myWriteAPIKey = "WZDEDJ6LKG9E7J71";

void setup() {
    
    ThingSpeak.begin(client);
    
    pinMode(D7, OUTPUT);
	Serial.begin(9600); 
	Serial.println("DHT11 test!");
	Particle.publish("state", "DHT11 test start");
    Particle.subscribe("Test", l, ALL_DEVICES);
	dht.begin();
	
}

void loop() {
    if (counter > 0 && counter <= 10)
    {
        delay(2000);
        
        //Read humidity
        float h = dht.getHumidity();
        // Read temperature as Celsius
        float t = dht.getTempCelcius();
        // Read temperature as Farenheit
        float f = dht.getTempFarenheit();
        
        // Check if any reads failed and exit early (to try again).
        if (isnan(h) || isnan(t) || isnan(f)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
        }
        
        Particle.publish("Test", String (t), PUBLIC);
        Particle.publish("Test", String (h), PUBLIC);
        
        ThingSpeak.setField(1,h);
        ThingSpeak.setField(2,t);
        
        Serial.print(dht.getTempCelcius());
        Serial.println("t");
        Serial.print(dht.getHumidity());
        Serial.println("h");
        
        ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);  
        
        counter++;
        delay(30000);
    }
    
}

void l(const char *event, const char *data) {
        
    digitalWrite(D7, HIGH);
    delay(2000);
    digitalWrite(D7, LOW);
    delay(1000);
       
}
