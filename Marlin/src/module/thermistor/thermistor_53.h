// added by Reece Kibble, not public
// 100k Cartridge Thermistor (104GTA-2)
// ATC Semitec 104GTA-2 (Use if 104GT-2 thermistor table is not giving correct readings)
// Verified by Reece Kibble. Source: http://www.semitec.co.jp/uploads/english/sites/2/2017/03/P18-NT-Thermistor.pdf
// Listed as Product Number: 104NT-4-R025H43G by the source
// Calculated using 4.7kohm pullup, voltage divider math, and manufacturer provided temp/resistance
const short temptable_53[][2] PROGMEM = {
  { OV(    1), 640 },
  { OV(   15), 300 }, // top rating 300C
  { OV(   17), 290 },
  { OV(   20), 280 },
  { OV(   23), 270 },
  { OV(   27), 260 },
  { OV(   32), 250 },
  { OV(   37), 240 },
  { OV(   44), 230 },
  { OV(   53), 220 },
  { OV(   63), 210 },
  { OV(   76), 200 },
  { OV(   93), 190 },
  { OV(  113), 180 },
  { OV(  139), 170 },
  { OV(  171), 160 },
  { OV(  210), 150 },
  { OV(  258), 140 },
  { OV(  316), 130 },
  { OV(  383), 120 },
  { OV(  459), 110 },
  { OV(  541), 100 },
  { OV(  625),  90 },
  { OV(  707),  80 },
  { OV(  782),  70 },
  { OV(  846),  60 },
  { OV(  897),  50 },
  { OV(  937),  40 },
  { OV(  966),  30 },
  { OV(  986),  20 },
  { OV( 1000),  10 },
  { OV( 1009),   0 }
};