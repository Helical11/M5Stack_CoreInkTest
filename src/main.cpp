/*
*******************************************************************************
*M5Stack_CoreInk
*Watering_sensor
*ver.0.0.1
*******************************************************************************
*/
#include "M5CoreInk.h"
#include "esp_adc_cal.h"

//LGFX基本設定
  #define LGFX_M5STACK_COREINK       // M5Stack CoreInk
  #define LGFX_AUTODETECT // 自動認識 (D-duino-32 XS, PyBadge はパネルID読取りが出来ないため自動認識の対象から外れています)
  #define LGFX_USE_V1 // v1.0.0 を有効にします(v0からの移行期間の特別措置です。これを書かない場合は旧v0系で動作します。)
  #include <LovyanGFX.hpp>
  #include <LGFX_AUTODETECT.hpp>  // クラス"LGFX"を準備します

  static LGFX lcd;                 // LGFXのインスタンスを作成。
  static LGFX_Sprite sprite(&lcd); // スプライトを使う場合はLGFX_Spriteのインスタンスを作成。

//LGFX関連変数宣言
  uint32_t brack = 0x000000; //カラーコード黒
  uint32_t white = 0xFFFFFF; //カラーコード白


//センサー基本設定

float getBatVoltage()
{
    analogSetPinAttenuation(35,ADC_11db);
    esp_adc_cal_characteristics_t *adc_chars = (esp_adc_cal_characteristics_t *)calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 3600, adc_chars);
    uint16_t ADCValue = analogRead(35);

    uint32_t BatVolmV  = esp_adc_cal_raw_to_voltage(ADCValue,adc_chars);
    float BatVol = float(BatVolmV) * 25.1 / 5.1 / 1000;
    return BatVol;
}


void setup(void)
{
  lcd.init(); //LGXF初期化
//  lcd.setRotation(0); //画面回転
//  lcd.setBrightness(0); //バックライト設定
//  lcd.setColorDepth(16);  // カラーモード設定

  Serial.begin(115200);//ビットレート設定

//グラフ作成
  lcd.fillScreen(white);
  lcd.drawFastVLine( 25,  50, 100, brack);
  lcd.drawFastHLine( 25, 150, 150, brack);
  delay(2000);

}

void loop(void)
{
//バッテリー表示更新
  lcd.fillScreen(white);
  float count = getBatVoltage();
  lcd.setTextColor(brack);
  lcd.setTextSize(2);
  lcd.setCursor(150,10);
  lcd.print(count);
  delay(1000);

  Serial.print(count);
  lcd.print("TEST");
  delay(1000);

}
