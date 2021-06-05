# DPV
dive propulsion vehicle
Arduino Nano + Display SSD1306 + Brushlessmotor mit ESC

Anschluss Arduino:
A0 = analog Eingang Poti
A1 = analog Eingang Spannungsteiler => Voltmeter
A4 = Display SDA
A5 = Display SCK
D2 = Taster "LEER, noch nicht vorgesehen" => Reedkontakt schaltet ueber GND
D3 = Taster "LEER, noch nicht vorgesehen" => Reedkontakt schaltet ueber GND
D4 = Taster "Gas geben" => Reedkontakt schaltet ueber GND
D5 = Taster "LEER, noch nicht vorgesehen" => Reedkontakt schaltet ueber GND
D6 = Steuerleitung ESC Brushless Motor

Daten ESC:
Rechtecksignal
Periodendauer: 20ms
min Pulsdauer: 1ms => servo.write(0)
max. Pulsdauer: 2ms => servo.write(180)

Programmbeschreibung (Forderung)
Einschalten von Arduino => Display zeigt aktuelle Spannung an (richtige Zellenspannung wird angezeigt => 40,4V)
Das ESC wird initialisiert (funktioniert)
ueber Poti kann die Geschwindigkeit eingestellt werden funktioniert, jedoch dreht der Motor direkt in der eingestellten Geschwindigkeit los)
Motor dreht nur, wenn Taster D4 (Gas geben) betätigt wird (Funktioniert nicht)
Wenn Taster D4 nicht betaetigt ist, dann muss die Pulsdauer von 1ms an D6 anliegen
Wenn Taster D4 betätigt ist liegt am D6 die am Poti eingestellte Pulsdauer an