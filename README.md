# UWB_Robot-X

```
ProjectStartYear: 2021  
Author: SeanChang
```


##  Problem and Solution  
### -2021.02.05-  
○問題:  開始測距後，無法寫入（Serial.read()）  

○判斷:  厘清問題後，猜測是“使用計時器傳送檔案”所造成之問題，通常不會應該這樣寫，所以接下來我將嘗試寫換成“計次傳送”的方法（例如:每1000筆傳送一次才不會造成刷屏的現象），不過這應不影響最終測距結果，只是顯示出來會更方便做判斷。  

○相關檔案:  [ESP32-BU01_UWB_Read.ino](firmware/ESP32/ESP32-BU01_UWB_Read/ESP32-BU01_UWB_Read.ino)  

##  

### -2021.02.26-  
○特殊進度:  已將三點定位公式程式化，並成功測試其運作狀況(運用GeoGebra繪製模擬圖並驗證其準確度)  

○問題:  
1)  繼上次計時器問題，這次嘗試將計時器替換成計數器，但其無法寫入（Serial.read()）的問題仍無法解決，但我認為這並不是太大的問題，因為透過BU01重置即可結束測距並恢復初始狀態。  
2)  **[自我提醒] 在定義座標變數時，我定義的y1變數出現"'double y1' redeclared as different kind of symbol"的問題，我想是與ESP32開發版本身定義的變數有所衝突，所以更換為y_1即可解決。**  

○判斷:  
1)  接下來我應開始查詢有關RST腳位相關的資訊，因為曾經在使用USB_Host_Shield_2.0做手把控制時有印象因為其本身無reset鈕，所以會將ESP8266的RST腳位與其RST腳位相連即可同時重置，希望能使用BU01的RST嘗試看看。  而且這個功能僅是為顯示出數值而已，方便除錯，並不會對變數本身產生影響，所以我決定暫且使用定時器就好，不應耽誤其進度，希望在未來精修階段再做最終處理。  

○相關檔案:  [ESP32-BU01_UWB_FormulaTest.ino](firmware/ESP32/ESP32-BU01_UWB_FormulaTest/ESP32-BU01_UWB_FormulaTest.ino)  

<img align="center" alt="Banner" width="100%" src="images/20210226_1.png" />  
<img align="center" alt="Banner" width="100%" src="images/20210226_2.png" />  
<img align="center" alt="Banner" width="100%" src="images/20210226_3.png" />  


### -2021.02.27-  
○假日記錄: 今天是二二八連假第一天，在空閑之餘，我突然產生一種想法。一開始使用的MCU為ESP32是考量到功能支援與運算速度的問題，但在一開始其實我寫了兩個程式，一個拿ESP32當中繼另一個是拿ESP8266，其實都可以，但是ESP8266是模擬出來的RX/TX，不太確定之後其中可能產生什麽技術上的問題 **[提醒]模擬的RX/TX與原生的差別？**。  

○之後計劃:  我可能會做兩種版本兼容ESP32及ESP8266，應該會先從ESP8266開始做Prototype是因爲先前我已有之前做的[MBT-Mini_Battlebot_2020](https://github.com/SeanChangX/MBT-Mini_Battlebot_2020)車體，所以可提高一點效率，在測試之後再做修改。  

○相關檔案:  [ESP32_UWB_Serial.ino](firmware/ESP32_UWB_Serial/ESP32_UWB_Serial.ino)   |   [ESP8266_UWB_Serial.ino](firmware/ESP8266_UWB_Serial/ESP8266_UWB_Serial.ino)  


------

## Data Source
MATHEMATICS: https://math.stackexchange.com/questions/884807/find-x-location-using-3-known-x-y-location-using-trilateration?fbclid=IwAR0-ItWKvf_oIQb9h2dPdxvq0jh5Q0_adl6m6USx5nw01NzVlef1XaJ_v0o  
