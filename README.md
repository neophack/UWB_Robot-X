# UWB_Robot-X

```
ProjectStartYear: 2021  
Author: SeanChang
```

```
= Problem and Solution =  
```
##2021.02.05  
問題: 開始測距後，無法寫入（Serial.read()）  
判斷: 厘清問題後，猜測是“使用計時器傳送檔案”所造成之問題，通常不會應該這樣寫，所以接下來我將嘗試寫換成“計次傳送”的方法（例如:每1000筆傳送一次才不會造成刷屏的現象），不過這應不影響最終測距結果，只是顯示出來會更方便做判斷。  

相關檔案: ESP32-BU01_UWB_Read.ino  
