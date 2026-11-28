# Dark Synth P2 – konkrete MIDI-Beispiele

Alle folgenden Noten stammen aus dem Produktionsrenderer. MIDI-Zahlen vermeiden unterschiedliche Oktavnamen der DAWs. Zeit in Viertelnoten bei D / 100 BPM; Rollen sind unabhängig von der Instrumentierung. Die zugehörigen kompletten A/B-Dateien liegen in `P2_MIDI_LISTENING.zip`.

## Feste Oberstimmen und Bassrotation

Der gezielte physische H07-Regressionstest wählt H07 regulär über XYZ/Variation. In jeder der zwölf Tonarten erklingen vier LF-Anschläge ausschließlich am Anfang, ihre vier Note-offs erst am Ende von 16 Takten. Bass-Tonklassen relativ zur Tonart: `0, 8, 5, 8, 0, 1, 10, 0`. Kein erneuter LF-Anschlag bei diesen Basswechseln. Die gehörte Wirkung hängt vom gehaltene Noten unterstützenden Patch ab.

## 01-warm-pulseless

Harmonieauswahl (Sampleposition : stabile ID): `0:61052, 921600:61055, 2764800:61010, 4608000:61004, 6451200:61010, 8294400:61055, 10137600:61053, 11980800:61032, 13824000:61055`.

Erste tatsächliche TU-Noten (Viertelposition / MIDI / Dauer in Vierteln / Velocity):

```
4.000 / 78 / 1.000 / 96
5.000 / 81 / 1.000 / 92
6.000 / 85 / 2.000 / 96
24.000 / 78 / 1.000 / 96
25.000 / 81 / 1.000 / 92
26.000 / 85 / 2.000 / 96
44.000 / 90 / 1.000 / 96
45.000 / 93 / 1.000 / 92
64.000 / 78 / 1.000 / 96
65.000 / 81 / 1.000 / 92
66.000 / 85 / 2.000 / 96
84.500 / 74 / 0.500 / 72
```

Physische Quellen: `DS-TU01: 3, DS-TU02: 3, DS-TU19: 49, DS-TU28: 1`.

Erste Aufnahme-/Wiederkehrdiagnosen (Sample, Rolle, Quelle, Identität, Materialanzahl, komplett, Basis, Antwortquelle, Operation, Tickbeginn, Tickende):

```
115200,5,4219,0,1,0,50,-1,0,3840,7680
144000,5,4219,0,2,0,50,-1,0,3840,7680
172800,5,4219,0,3,0,50,-1,0,3840,7680
691200,5,4219,282825889327914417,3,1,50,-1,0,23040,26880
720000,5,4219,282825889327914417,3,1,50,-1,0,23040,26880
748800,5,4219,282825889327914417,3,1,50,-1,0,23040,26880
1267200,5,4219,282825889327914417,3,1,62,-1,7,42240,44160
1296000,5,4219,282825889327914417,3,1,62,-1,7,42240,44160
```

Gemeinsame Identität ist eine Materialreferenz, kein geteilter Stimmenfortschritt. Eine Transposition kann die absoluten Tonhöhen ändern; Intervall-/Rhythmusbezug und ausdrücklich erlaubte Anpassung werden getrennt geprüft.

## 02-shadow-rotation

Harmonieauswahl (Sampleposition : stabile ID): `0:61016, 1382400:61009, 3225600:61018, 5068800:61030, 6912000:60029, 7833600:61005, 9676800:61006, 11520000:61030, 13363200:61007`.

Erste tatsächliche TU-Noten (Viertelposition / MIDI / Dauer in Vierteln / Velocity):

```
4.000 / 74 / 0.500 / 96
4.500 / 79 / 1.500 / 96
6.000 / 77 / 2.000 / 92
24.000 / 74 / 0.500 / 96
24.500 / 79 / 1.500 / 96
26.000 / 75 / 2.000 / 92
44.000 / 86 / 0.500 / 96
44.500 / 91 / 1.500 / 96
64.000 / 74 / 0.500 / 96
64.500 / 79 / 1.500 / 96
66.000 / 77 / 2.000 / 92
84.000 / 74 / 0.500 / 96
```

Physische Quellen: `DS-TU18: 71`.

Erste Aufnahme-/Wiederkehrdiagnosen (Sample, Rolle, Quelle, Identität, Materialanzahl, komplett, Basis, Antwortquelle, Operation, Tickbeginn, Tickende):

```
115200,5,4218,0,1,0,50,-1,0,3840,7680
129600,5,4218,0,2,0,50,-1,0,3840,7680
172800,5,4218,0,3,0,50,-1,0,3840,7680
691200,5,4218,10656681160682882655,3,1,50,-1,5,23040,26880
705600,5,4218,10656681160682882655,3,1,50,-1,5,23040,26880
748800,5,4218,10656681160682882655,3,1,50,-1,5,23040,26880
1267200,5,4218,10656681160682882655,3,1,62,-1,7,42240,44160
1281600,5,4218,10656681160682882655,3,1,62,-1,7,42240,44160
```

Gemeinsame Identität ist eine Materialreferenz, kein geteilter Stimmenfortschritt. Eine Transposition kann die absoluten Tonhöhen ändern; Intervall-/Rhythmusbezug und ausdrücklich erlaubte Anpassung werden getrennt geprüft.

## 03-two-periods

Harmonieauswahl (Sampleposition : stabile ID): `0:60063, 921600:61042, 2764800:60023, 3686400:61016, 5068800:61020, 6681600:60017, 7603200:61042, 11289600:60063, 12211200:61042`.

Erste tatsächliche TU-Noten (Viertelposition / MIDI / Dauer in Vierteln / Velocity):

```
4.000 / 62 / 6.000 / 110
24.000 / 84 / 0.250 / 100
24.250 / 89 / 0.750 / 100
44.000 / 81 / 0.250 / 100
44.250 / 86 / 0.750 / 100
61.000 / 63 / 0.225 / 45
62.000 / 75 / 0.225 / 45
84.000 / 81 / 0.250 / 100
84.250 / 86 / 0.750 / 100
104.000 / 89 / 0.250 / 100
104.250 / 94 / 0.750 / 100
124.000 / 91 / 0.250 / 100
```

Physische Quellen: `DS-TO02: 1, DS-TO04: 4, DS-TU04: 1, DS-TU27: 44`.

Erste Aufnahme-/Wiederkehrdiagnosen (Sample, Rolle, Quelle, Identität, Materialanzahl, komplett, Basis, Antwortquelle, Operation, Tickbeginn, Tickende):

```
115200,5,4204,0,0,0,50,-1,0,3840,9600
691200,5,4227,0,1,0,53,-1,0,23040,24000
698400,5,4227,0,2,0,53,-1,0,23040,24000
1267200,5,4227,1707404804993724796,2,1,50,-1,6,42240,43200
1274400,5,4227,1707404804993724796,2,1,50,-1,6,42240,43200
1756800,5,4304,1707404804993724796,2,1,63,7,4,58560,59736
1785600,5,4304,1707404804993724796,2,1,63,7,4,58560,59736
2419200,5,4227,1707404804993724796,2,1,50,-1,6,80640,81600
```

Gemeinsame Identität ist eine Materialreferenz, kein geteilter Stimmenfortschritt. Eine Transposition kann die absoluten Tonhöhen ändern; Intervall-/Rhythmusbezug und ausdrücklich erlaubte Anpassung werden getrennt geprüft.

## 04-ritual

Harmonieauswahl (Sampleposition : stabile ID): `0:60033, 921600:60066, 1843200:60033, 3686400:60066, 4608000:60033, 8294400:60066, 9216000:60033, 10137600:60066, 11980800:60033, 12902400:60066`.

Erste tatsächliche TU-Noten (Viertelposition / MIDI / Dauer in Vierteln / Velocity):

```
4.000 / 74 / 0.500 / 96
4.500 / 86 / 1.500 / 96
24.000 / 81 / 0.500 / 96
24.500 / 93 / 1.500 / 96
44.000 / 74 / 0.500 / 96
44.500 / 86 / 1.500 / 96
64.000 / 74 / 0.500 / 96
64.500 / 86 / 1.500 / 96
84.000 / 82 / 0.500 / 96
84.500 / 94 / 1.500 / 96
104.000 / 84 / 0.500 / 96
104.500 / 96 / 1.500 / 96
```

Physische Quellen: `DS-TU25: 52`.

Erste Aufnahme-/Wiederkehrdiagnosen (Sample, Rolle, Quelle, Identität, Materialanzahl, komplett, Basis, Antwortquelle, Operation, Tickbeginn, Tickende):

```
115200,5,4225,0,1,0,50,-1,0,3840,5760
129600,5,4225,0,2,0,50,-1,0,3840,5760
691200,5,4225,3341619374096773133,2,1,57,-1,6,23040,24960
705600,5,4225,3341619374096773133,2,1,57,-1,6,23040,24960
1267200,5,4225,3341619374096773133,2,1,50,-1,0,42240,44160
1281600,5,4225,3341619374096773133,2,1,50,-1,0,42240,44160
1843200,5,4225,3341619374096773133,2,1,50,-1,0,61440,63360
1857600,5,4225,3341619374096773133,2,1,50,-1,0,61440,63360
```

Gemeinsame Identität ist eine Materialreferenz, kein geteilter Stimmenfortschritt. Eine Transposition kann die absoluten Tonhöhen ändern; Intervall-/Rhythmusbezug und ausdrücklich erlaubte Anpassung werden getrennt geprüft.

## 05-high-unrest

Harmonieauswahl (Sampleposition : stabile ID): `0:61060, 921600:61062, 1843200:61058, 2764800:60035, 3686400:61061, 5529600:60015, 6451200:60035, 8294400:61062, 9216000:60015, 10137600:61061, 11980800:61058, 12902400:61061`.

Erste tatsächliche TU-Noten (Viertelposition / MIDI / Dauer in Vierteln / Velocity):

```
4.000 / 81 / 0.500 / 94
4.500 / 82 / 0.500 / 90
5.000 / 85 / 2.000 / 96
24.000 / 73 / 6.000 / 110
44.000 / 94 / 0.500 / 94
44.500 / 95 / 0.500 / 90
64.000 / 86 / 2.000 / 100
84.000 / 81 / 0.500 / 94
84.500 / 82 / 0.500 / 90
85.000 / 85 / 2.000 / 96
104.000 / 104 / 0.500 / 94
104.500 / 105 / 0.500 / 90
```

Physische Quellen: `DS-HM05: 5, DS-TO02: 1, DS-TO04: 2, DS-TU03: 1, DS-TU04: 1, DS-TU12: 44, DS-TU20: 3, DS-TU21: 1`.

Erste Aufnahme-/Wiederkehrdiagnosen (Sample, Rolle, Quelle, Identität, Materialanzahl, komplett, Basis, Antwortquelle, Operation, Tickbeginn, Tickende):

```
115200,5,4212,0,1,0,50,-1,0,3840,6720
129600,5,4212,0,2,0,50,-1,0,3840,6720
144000,5,4212,0,3,0,50,-1,0,3840,6720
691200,5,4204,13197703324659399740,3,1,61,-1,0,23040,28800
1267200,5,4212,13197703324659399740,3,1,63,-1,7,42240,43200
1281600,5,4212,13197703324659399740,3,1,63,-1,7,42240,43200
1843200,5,4220,13197703324659399740,3,1,50,-1,0,61440,63360
2419200,5,4212,13197703324659399740,3,1,50,-1,0,80640,83520
```

Gemeinsame Identität ist eine Materialreferenz, kein geteilter Stimmenfortschritt. Eine Transposition kann die absoluten Tonhöhen ändern; Intervall-/Rhythmusbezug und ausdrücklich erlaubte Anpassung werden getrennt geprüft.

## 06-bright-unease

Harmonieauswahl (Sampleposition : stabile ID): `0:61050`.

Erste tatsächliche TU-Noten (Viertelposition / MIDI / Dauer in Vierteln / Velocity):

```
4.000 / 74 / 0.500 / 88
5.500 / 74 / 0.500 / 60
7.000 / 74 / 0.500 / 40
24.000 / 80 / 0.500 / 88
25.500 / 80 / 0.500 / 60
27.000 / 80 / 0.500 / 40
44.000 / 86 / 0.500 / 88
45.500 / 86 / 0.500 / 60
64.000 / 74 / 0.500 / 88
65.500 / 74 / 0.500 / 60
67.000 / 74 / 0.500 / 40
84.000 / 80 / 0.500 / 88
```

Physische Quellen: ``.

Erste Aufnahme-/Wiederkehrdiagnosen (Sample, Rolle, Quelle, Identität, Materialanzahl, komplett, Basis, Antwortquelle, Operation, Tickbeginn, Tickende):

```
115200,5,3004,0,1,0,50,-1,0,3840,7200
158400,5,3004,0,2,0,50,-1,0,3840,7200
201600,5,3004,0,3,0,50,-1,0,3840,7200
691200,5,3004,18056734580519875963,3,1,56,-1,6,23040,26400
734400,5,3004,18056734580519875963,3,1,56,-1,6,23040,26400
777600,5,3004,18056734580519875963,3,1,56,-1,6,23040,26400
1267200,5,3004,18056734580519875963,3,1,62,-1,7,42240,44160
1310400,5,3004,18056734580519875963,3,1,62,-1,7,42240,44160
```

Gemeinsame Identität ist eine Materialreferenz, kein geteilter Stimmenfortschritt. Eine Transposition kann die absoluten Tonhöhen ändern; Intervall-/Rhythmusbezug und ausdrücklich erlaubte Anpassung werden getrennt geprüft.

## 07-slow-xyz

Harmonieauswahl (Sampleposition : stabile ID): `0:61037, 1843200:61036, 4550400:61039, 4953600:60027, 5673600:61041, 7804800:60033, 8726400:60006, 10454400:60074, 11088000:61028, 11491200:61024, 12182400:61047, 13046400:61050`.

Erste tatsächliche TU-Noten (Viertelposition / MIDI / Dauer in Vierteln / Velocity):

```
4.000 / 74 / 0.250 / 100
4.250 / 74 / 0.250 / 90
4.500 / 74 / 0.500 / 100
24.000 / 78 / 0.250 / 100
24.250 / 78 / 0.250 / 90
24.500 / 78 / 0.500 / 100
44.000 / 86 / 0.250 / 100
44.250 / 86 / 0.250 / 90
64.000 / 74 / 0.250 / 100
64.250 / 74 / 0.250 / 90
64.500 / 74 / 0.500 / 100
84.000 / 74 / 0.250 / 100
```

Physische Quellen: `DS-HM10: 5, DS-TU26: 64`.

Erste Aufnahme-/Wiederkehrdiagnosen (Sample, Rolle, Quelle, Identität, Materialanzahl, komplett, Basis, Antwortquelle, Operation, Tickbeginn, Tickende):

```
115200,5,4226,0,1,0,50,-1,0,3840,4800
122400,5,4226,0,2,0,50,-1,0,3840,4800
129600,5,4226,0,3,0,50,-1,0,3840,4800
691200,5,4226,8099340824369325003,3,1,54,-1,6,23040,24000
698400,5,4226,8099340824369325003,3,1,54,-1,6,23040,24000
705600,5,4226,8099340824369325003,3,1,54,-1,6,23040,24000
1267200,5,4226,8099340824369325003,3,1,62,-1,7,42240,42720
1274400,5,4226,8099340824369325003,3,1,62,-1,7,42240,42720
```

Gemeinsame Identität ist eine Materialreferenz, kein geteilter Stimmenfortschritt. Eine Transposition kann die absoluten Tonhöhen ändern; Intervall-/Rhythmusbezug und ausdrücklich erlaubte Anpassung werden getrennt geprüft.

## 08-fast-xyz

Harmonieauswahl (Sampleposition : stabile ID): `0:61037, 576000:60027, 720000:61038, 950400:60003, 1008000:60033, 1296000:60032, 1468800:61024, 1526400:60068, 1584000:60041, 1612800:61050, 2044800:60084, 2131200:61036`.

Erste tatsächliche TU-Noten (Viertelposition / MIDI / Dauer in Vierteln / Velocity):

```
4.000 / 74 / 0.250 / 100
4.250 / 74 / 0.250 / 90
4.500 / 74 / 0.500 / 100
24.000 / 74 / 0.250 / 100
24.250 / 74 / 0.250 / 90
24.500 / 74 / 0.500 / 100
44.000 / 96 / 0.250 / 100
44.250 / 96 / 0.250 / 90
64.000 / 74 / 0.250 / 100
64.250 / 74 / 0.250 / 90
64.500 / 74 / 0.500 / 100
84.000 / 74 / 0.250 / 100
```

Physische Quellen: `DS-TO01: 2, DS-TU26: 62`.

Erste Aufnahme-/Wiederkehrdiagnosen (Sample, Rolle, Quelle, Identität, Materialanzahl, komplett, Basis, Antwortquelle, Operation, Tickbeginn, Tickende):

```
115200,5,4226,0,1,0,50,-1,0,3840,4800
122400,5,4226,0,2,0,50,-1,0,3840,4800
129600,5,4226,0,3,0,50,-1,0,3840,4800
691200,5,4226,8099340824369325003,3,1,50,-1,0,23040,24000
698400,5,4226,8099340824369325003,3,1,50,-1,0,23040,24000
705600,5,4226,8099340824369325003,3,1,50,-1,0,23040,24000
1267200,5,4226,8099340824369325003,3,1,72,-1,7,42240,42720
1274400,5,4226,8099340824369325003,3,1,72,-1,7,42240,42720
```

Gemeinsame Identität ist eine Materialreferenz, kein geteilter Stimmenfortschritt. Eine Transposition kann die absoluten Tonhöhen ändern; Intervall-/Rhythmusbezug und ausdrücklich erlaubte Anpassung werden getrennt geprüft.

## 09-TU-alone

Harmonieauswahl (Sampleposition : stabile ID): `0:61019, 1612800:61022, 3456000:60054, 4377600:61064, 5760000:60029, 7603200:61064, 8985600:61005, 9907200:61003, 10828800:61027, 13132800:60054, 14054400:61064`.

Erste tatsächliche TU-Noten (Viertelposition / MIDI / Dauer in Vierteln / Velocity):

```
4.000 / 74 / 0.500 / 96
4.500 / 79 / 1.500 / 96
6.000 / 77 / 2.000 / 92
24.000 / 84 / 0.500 / 96
24.500 / 88 / 1.500 / 96
26.000 / 84 / 2.000 / 92
44.000 / 86 / 0.500 / 96
44.500 / 91 / 1.500 / 96
64.000 / 74 / 0.500 / 96
64.500 / 79 / 1.500 / 96
66.000 / 77 / 2.000 / 92
84.000 / 74 / 0.500 / 96
```

Physische Quellen: `DS-TU01: 1, DS-TU02: 1, DS-TU18: 66`.

Erste Aufnahme-/Wiederkehrdiagnosen (Sample, Rolle, Quelle, Identität, Materialanzahl, komplett, Basis, Antwortquelle, Operation, Tickbeginn, Tickende):

```
115200,5,4218,0,1,0,50,-1,0,3840,7680
129600,5,4218,0,2,0,50,-1,0,3840,7680
172800,5,4218,0,3,0,50,-1,0,3840,7680
691200,5,4218,10656681160682882655,3,1,60,-1,5,23040,26880
705600,5,4218,10656681160682882655,3,1,60,-1,5,23040,26880
748800,5,4218,10656681160682882655,3,1,60,-1,5,23040,26880
1267200,5,4218,10656681160682882655,3,1,62,-1,7,42240,44160
1281600,5,4218,10656681160682882655,3,1,62,-1,7,42240,44160
```

Gemeinsame Identität ist eine Materialreferenz, kein geteilter Stimmenfortschritt. Eine Transposition kann die absoluten Tonhöhen ändern; Intervall-/Rhythmusbezug und ausdrücklich erlaubte Anpassung werden getrennt geprüft.

## Kontrollierter Freeze-Nachweis (kein Atlasbeispiel)

Q13 / H61, 4/4, Tonart A (Test-Standard): letzter Sechzehntelanschlag vor Viertelposition 96 auf MIDI 76. Derselbe physische Ton bleibt bis Viertelposition 128 gehalten, ohne erneutes Note-on an Position 96. Genau ein Note-off an 128. Die kontrollierte Prüfung ergänzt die normalen Hörbeispiele; deren Q13-Gates waren ausschließlich kurz.
