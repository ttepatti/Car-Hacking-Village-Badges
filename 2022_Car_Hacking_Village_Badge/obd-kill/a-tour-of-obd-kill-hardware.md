# A Tour of OBD-Kill Hardware

### 3. A Tour of OBD-Kill Hardware

### **3.1 Case and Overall Design**

The OBD-Kill is enclosed in a lightweight circuit board. 13 LEDs, 2 buttons, CAN interface, and a Pulse Width Modulator are all built into this board. They can be easily controlled by using the Pin class and the pin numbers listed below.

### **3.2 Front Side and Pinout of Case**

![image](https://user-images.githubusercontent.com/93162463/184357970-c7b6a546-1e8f-4b8e-bd6a-b00f62a22489.png)

{% hint style="info" %}
#### Note

The pinout printed on the OBD-Kill for the Left and Right Buttons is reversed. The correct GPIO Pin for the left button is Pin 18 and the correct GPIO Pin for the right button is Pin 15.
{% endhint %}

### **3.3 Back Side and Pinout of Case**

![image](https://user-images.githubusercontent.com/93162463/184426546-d15a3054-99f5-46de-9feb-b2c2e88b0a5e.png)

{% hint style="info" %}
#### Note

The pinout printed on the OBD-Kill for the Pusle Width Modulator (Buzzer) is incorrect. The correct GPIO Pin is 20.
{% endhint %}

***
