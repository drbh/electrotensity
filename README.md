# electrotensity

Measuring AC Voltage with a ESP8266. This is a project to measure AC voltage using a ESP8266 and a simple circuit.

The goal is to create a simple non-invasive realtime monitor for AC voltage - this is useful for monitoring the voltage of a solar panel, AC sources or household wiring.

This repo only incudes the code for the microcontroller and a small script to process the values on a cpu over serial.

## Prior Art

- This is an example converting an analog current into a binary signal using a 555 timer. Was fun to build but isn't helpful in terms of measuring small changes since we only return a HIGH/LOW signal. Additionally if we are going to use a micro controller we should just read the analog vales from there. https://www.instructables.com/Contactless-Voltage-Detector/
- This is the exact kind of solution we are looking for! Lets process all of the values via a CPU (less energy efficient) which is much easier to iterate on and make smart. This way we can have a dynamic voltage baseline to account for environmental variances https://www.instructables.com/Contactless-AC-Detector/