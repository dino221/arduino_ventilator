#include 

int pinDHT11 = 2;
int DHTpower = 3;
int Fan = 13;
SimpleDHT11 dht11;

void setup() {
    pinMode(Fan, OUTPUT);
    pinMode(DHTpower, OUTPUT);
    digitalWrite(DHTpower, LOW);
    digitalWrite(Fan, LOW);
    Serial.begin(9600);
}

void loop() {
    delay(1000);
    RHcheck();
    delay(15000);
}

void RHcheck() {
    digitaLWrite (DHTpower, HIGH);
    delay(5000);
    Serial.println("============ Check Humidity ============");
    delay(1000);
    Serial.println("DHT11 readings...");

    byte temperature = 0;
    byte humidity = 0;
    int err = SimpleDHTErrSuccess;

    if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
        Serial.print("No reading, err="); Serial.println(err); delay(1000);
        return;
    }
    Serial.print("Readings: ");
    Serial.print((int)temperature); Serial.print(" C, ");
    Serial.print((int)humidity); Serial.println(" %");
    delay(500);
    if ((int)humidity < 50) {
        digitalWrite(DHTpower, LOW);
        delay(500);
        Serial.println("Fan OFF");
        delay(500);
        digitalWrite(Fan, LOW);
    
    } else {
        if ((int)humidity > 58) {
            Serial.println("Humidity > 58%");
            digitalWrite(DHTpower, LOW);
            delay(500);
            Serial.println("Fan ON @ full speed");
            delay(500);
            digitalWrite(Fan, HIGH);
        } else {
            Serial.println("50% < Humidity < 58%");
            digitalWrite(DHTpower, LOW);
            delay(500);
            Serial.println("Fan ON @ low speed");
            delay(500);
            analogWrite(Fan, 150);
        }
    }
    }