#include "secured_control.h"

SecuredControl::SecuredControl() {
    // Constructor implementation (if needed)
}

//  Routine to dump a byte array as hex values to Serial.
String SecuredControl::printHex(byte *buffer, byte bufferSize) {
    String card_id = "";

    for (byte i = 0; i < bufferSize; i++) {
        card_id.concat(String(buffer[i], HEX));
    }

    card_id.toUpperCase();

    return card_id;
}

void SecuredControl::authorizedAccess() {
    Serial.println();
    Serial.println("Message: Authorized Access");
    myservo.write(90);

    Serial.println("Playing track 1...");
    fxPlayer.play(1);
    delay(3000);
    myservo.write(0);
    delay(500);
}

void SecuredControl::accessDenied() {
    Serial.println();
    Serial.println("Message: Access Denied");
    if (count < 2) {
        Serial.println("Playing track 2...");
        fxPlayer.play(2);
        delay(2500);
    }
}