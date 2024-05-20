#include <Arduino.h>
#include <Servo.h>

// Pin Ultrasonik
const int trigPin = D1;  // Pin D1 pada NodeMCU untuk Trig
const int echoPin = D0;  // Pin D0 pada NodeMCU untuk Echo

// Pin Servo
const int servoPin = D4; // Pin D4 pada NodeMCU untuk Servo

// Membuat objek servo
Servo myServo;

// Waktu jeda sebelum kembali ke posisi awal (dalam milidetik)
const int delayTime = 3000;

// Variabel untuk jarak dan durasi
long duration;
long distance;

// Fungsi untuk mengukur jarak menggunakan sensor ultrasonik
long readUltrasonicDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);            // Mengatur pin Trig ke LOW
  delayMicroseconds(5);                     // Menunggu 5 mikrodetik
  digitalWrite(triggerPin, HIGH);           // Mengatur pin Trig ke HIGH
  delayMicroseconds(10);                    // Menunggu 10 mikrodetik
  digitalWrite(triggerPin, LOW);            // Mengatur pin Trig kembali ke LOW
  
  duration = pulseIn(echoPin, HIGH);        // Mengukur durasi PSW di pin Echo
  distance = (duration / 2) * 0.034;        // Menghitung jarak berdasarkan durasi PSW
  return distance;                          // Mengembalikan jarak yang dihitung
}

void setup() {
  Serial.begin(9600);                       // Inisialisasi komunikasi serial pada baud rate 9600
  
  myServo.attach(servoPin);                 // Menghubungkan servo ke pin yang ditentukan
  
  myServo.write(0);                         // Mengatur posisi awal servo di 0 derajat

  pinMode(trigPin, OUTPUT);                 // Mengatur pin Trig sebagai output
  pinMode(echoPin, INPUT);                  // Mengatur pin Echo sebagai input
}

void loop() {
  long distance = readUltrasonicDistance(trigPin, echoPin);  // Membaca jarak dari sensor ultrasonik
  
  Serial.print("Jarak: ");                  // Menampilkan teks "Jarak: " di Serial Monitor
  Serial.print(distance);                   // Menampilkan jarak yang diukur di Serial Monitor
  Serial.println(" cm");                    // Menampilkan teks " cm" di Serial Monitor
  
  if (distance < 50) {                      // Jika jarak kurang dari 50 cm
    myServo.write(90);                      // Menggerakkan servo ke 90 derajat
  } else {                                  // Jika tidak ada objek terdeteksi
    delay(delayTime);                       // Menunggu selama 3 detik
    myServo.write(0);                       // Menggerakkan servo kembali ke 0 derajat
  }
  
  delay(1000);                              // Jeda sejenak sebelum pengukuran berikutnya
}
