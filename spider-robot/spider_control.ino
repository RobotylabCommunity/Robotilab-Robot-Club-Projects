#include <Servo.h>

Servo myServos[8];

/*
  تقسيم المحركات على المنافذ:
  الرجل 1 (أمامية يمين): ورك -> 2 ، ركبة -> 3
  الرجل 2 (أمامية يسار): ورك -> 4 ، ركبة -> 5
  الرجل 3 (خلفية يمين): ورك -> 6 ، ركبة -> 7
  الرجل 4 (خلفية يسار): ورك -> 8 ، ركبة -> 9
*/
int pins[] = {2, 3, 4, 5, 6, 7, 8, 9};

// الإعدادات الاحترافية للمدى ونقطة المنتصف
const int minPulse = 500;  
const int maxPulse = 2500; 
const int midPulse = 1500; // زاوية 90 درجة بالظبط (وضعية الاستعداد)

void setup() {
  // تشغيل الـ 8 محركات تتابعياً للأمان وتقليل سحب التيار المفاجئ
  for (int i = 0; i < 8; i++) {
    myServos[i].attach(pins[i], minPulse, maxPulse);
    myServos[i].writeMicroseconds(midPulse);
    delay(200); // تأخير بسيط بين كل محرك ومحرك
  }
  delay(2000); // انتظار ثانيتين بعد تشغيل كل المحركات قبل بدء الحركة
}

void loop() {
  // 1. تحرك خطوة للأمام
  stepForward();
  delay(1500); // انتظار استقرار الروبوت بعد الخطوة
  
  // 2. حركة التسليم (التلويح بالرجل الأمامية اليمنى)
  waveGoodbye();
  delay(3000); // انتظار 3 ثواني قبل إعادة تكرار الدورة كاملة
}

// دالة التحرك خطوة للأمام (تحريك الأرجل بشكل قطري لتوازن أفضل)
void stepForward() {
  // ارفع الركب للأرجل (أمامية يمين وخلفية يسار)
  myServos[1].writeMicroseconds(midPulse - 300); // ركبة أمامية يمين
  myServos[7].writeMicroseconds(midPulse - 300); // ركبة خلفية يسار
  delay(200);

  // حرك الأوراك للأمام
  myServos[0].writeMicroseconds(midPulse + 300); // ورك أمامية يمين
  myServos[6].writeMicroseconds(midPulse - 300); // ورك خلفية يسار
  delay(200);

  // نزل الركب للأرض لتثبيت الخطوة
  myServos[1].writeMicroseconds(midPulse); 
  myServos[7].writeMicroseconds(midPulse); 
  delay(200);

  // الآن اسحب الجسم للأمام عن طريق إرجاع الأوراك لوضعها الطبيعي وتجهيز الأرجل الأخرى
  myServos[0].writeMicroseconds(midPulse);
  myServos[6].writeMicroseconds(midPulse);
  delay(300);
}

void waveGoodbye() {
  // 1. ارفع الركبة الأمامية اليمنى للأعلى بالكامل
  myServos[1].writeMicroseconds(midPulse - 500);
  delay(300);
  
  // 2. حرك الورك يميناً ويساراً 3 مرات (حركة التلويح)
  for (int i = 0; i < 3; i++) {
    myServos[0].writeMicroseconds(midPulse + 400); // تحريك الورك لجهة
    delay(250);
    myServos[0].writeMicroseconds(midPulse - 400); // تحريك الورك للجهة الأخرى
    delay(250);
  }
  
  // 3. إعادة الرجل إلى وضعية التصفير (الاستقرار على الأرض)
  myServos[0].writeMicroseconds(midPulse);
  myServos[1].writeMicroseconds(midPulse);
  delay(500);
}
