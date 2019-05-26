#include <MFRC522.h>
#include <SPI.h>

#define RST_PIN 9
#define SS_PIN 10

typedef struct {
  byte credit;
  byte point;
} NFCValue;

class NFC {
 public:
  NFC() {}
  ~NFC() {}
  void read(NFCValue& buffer);
  void update(char credit, char point);
  bool available();

 private:
  MFRC522 rc522 = MFRC522(SS_PIN, RST_PIN);
  void write(NFCValue& buffer);
};

bool NFC::available() {}
