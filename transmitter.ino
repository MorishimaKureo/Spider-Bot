// ==========================================
// KODE UNTUK REMOTE (TRANSMITTER)
// ==========================================

#include <ESP8266WiFi.h>
#include <espnow.h>

// MASUKKAN MAC ADDRESS NODEMCU ROBOT KAMU DI SINI
uint8_t broadcastAddress[] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC}; 

// Definisi Pin Tombol di NodeMCU Remote (Silakan sesuaikan dengan seleramu)
#define PIN_UP    D0
#define PIN_DOWN  D3
#define PIN_LEFT  D4
#define PIN_RIGHT D5
#define PIN_Q     D6
#define PIN_E     D7
#define PIN_A     D8
#define PIN_B     D1
#define PIN_C     D2
#define PIN_D     SD3 // Atau pin digital lain yang tersedia

struct DataPaket {
  char perintah;
};

DataPaket dataKirim;
char perintahTerakhir = 'S'; // 'S' artinya Stop / Diam

void OnDataSent(uint8_t *mac_addr, uint8_t status) {
  // Callback status pengiriman jika diperlukan untuk debugging
}

void setup() {
  Serial.begin(9600);

  // Inisialisasi semua pin tombol sebagai INPUT_PULLUP
  pinMode(PIN_UP, INPUT_PULLUP);
  pinMode(PIN_DOWN, INPUT_PULLUP);
  pinMode(PIN_LEFT, INPUT_PULLUP);
  pinMode(PIN_RIGHT, INPUT_PULLUP);
  pinMode(PIN_Q, INPUT_PULLUP);
  pinMode(PIN_E, INPUT_PULLUP);
  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  pinMode(PIN_C, INPUT_PULLUP);
  pinMode(PIN_D, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != 0) {
    Serial.println("Gagal menginisialisasi ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  
  Serial.println("Remote Tombol Siap...");
}

void loop() {
  char perintahSekarang = 'S'; // Default jika tidak ada tombol ditekan

  // Cek tombol mana yang sedang ditekan (Active LOW karena PULLUP)
  if (digitalRead(PIN_UP) == LOW) {
    perintahSekarang = 'U'; // Maju
  } else if (digitalRead(PIN_DOWN) == LOW) {
    perintahSekarang = 'N'; // Mundur (N dari dowN)
  } else if (digitalRead(PIN_LEFT) == LOW) {
    perintahSekarang = 'L'; // Strafe Kiri
  } else if (digitalRead(PIN_RIGHT) == LOW) {
    perintahSekarang = 'R'; // Strafe Kanan
  } else if (digitalRead(PIN_Q) == LOW) {
    perintahSekarang = 'Q'; // Putar Kiri
  } else if (digitalRead(PIN_E) == LOW) {
    perintahSekarang = 'E'; // Putar Kanan
  } else if (digitalRead(PIN_A) == LOW) {
    perintahSekarang = 'A'; // Jump
  } else if (digitalRead(PIN_B) == LOW) {
    perintahSekarang = 'B'; // Dance
  } else if (digitalRead(PIN_C) == LOW) {
    perintahSekarang = 'C'; // Stretch
  } else if (digitalRead(PIN_D) == LOW) {
    perintahSekarang = 'D'; // Stand (Sama dengan UP di kode lama)
  }

  // Kirim data hanya jika ada perubahan status tombol untuk menghemat bandwidth
  if (perintahSekarang != perintahTerakhir) {
    perintahTerakhir = perintahSekarang;
    dataKirim.perintah = perintahTerakhir;
    esp_now_send(broadcastAddress, (uint8_t *) &dataKirim, sizeof(dataKirim));
    
    Serial.print("Mengirim Perintah: ");
    Serial.println(perintahTerakhir);
  }
  
  delay(30); // Delay kecil untuk stabilitas reading pembacaan tombol
}