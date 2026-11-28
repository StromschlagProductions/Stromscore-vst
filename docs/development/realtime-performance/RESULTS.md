# Abschließende Echtzeit-Messergebnisse

Einheiten: Mikrosekunden. p999 bezeichnet p99.9. Jede Rohzeile enthält Durchschnitt, Median, p95, p99, p999, Maximum und Budgetüberschreitungen für CPU und Wandzeit. Die folgenden Einzelwerte sind Wiederholung 0; die zweite Wiederholung ist vollständig in den JSONL-Dateien enthalten. Keine gepoolten Quantile.

## Gesamtprozessor: schnelle XYZ-Fahrt, 128 Samples

| Profil / Stand | Mittel | Median | p95 | p99 | p99.9 | Maximum | CPU-Budgetüberschreitungen |
|---|---:|---:|---:|---:|---:|---:|---:|
| Neutral SCORE / before | 21.318 | 13.832 | 41.306 | 108.735 | 258.778 | 1182.310 | 0 |
| Neutral SCORE / after | 20.430 | 11.821 | 44.189 | 112.060 | 308.519 | 987.827 | 0 |
| John Barry / before | 50.881 | 17.042 | 245.641 | 338.809 | 1321.470 | 3070.610 | 2 |
| John Barry / after | 35.049 | 15.574 | 107.111 | 205.898 | 777.105 | 3172.710 | 4 |
| Bernard Herrmann / before | 39.470 | 33.793 | 70.059 | 125.649 | 322.086 | 1902.310 | 0 |
| Bernard Herrmann / after | 38.605 | 31.559 | 85.316 | 148.511 | 383.639 | 2905.140 | 1 |
| John Williams / before | 27.209 | 18.928 | 58.802 | 126.401 | 743.415 | 3505.360 | 1 |
| John Williams / after | 23.820 | 16.478 | 44.260 | 113.642 | 458.538 | 2820.090 | 1 |
| Ennio Morricone / before | 23.898 | 15.777 | 45.088 | 104.606 | 282.881 | 1424.290 | 0 |
| Ennio Morricone / after | 20.951 | 14.427 | 41.090 | 81.462 | 181.616 | 1394.540 | 0 |
| Dark Synth / before | 16.364 | 13.182 | 28.427 | 80.148 | 195.458 | 1470.560 | 0 |
| Dark Synth / after | 14.025 | 11.457 | 23.450 | 68.194 | 157.365 | 433.515 | 0 |
| Neutral POP/ROCK / before | 19.737 | 9.439 | 88.939 | 158.686 | 364.929 | 1279.260 | 0 |
| Neutral POP/ROCK / after | 15.670 | 7.912 | 85.549 | 138.510 | 317.553 | 909.962 | 0 |

## Gepaarte Gesamtprozessor-Zusammenfassung

Die Verhältniswerte sind der Median der einzelnen Nachher/Vorher-Verhältnisse über die Hauptmatrix einschließlich beider Wiederholungen. Sie sind keine gepoolten Blockquantile und keine Garantie für jedes Szenario. Maxima und Überschreitungen bleiben ungekürzt ausgewiesen.

| Profil | Fälle inkl. Wiederholungen | Median Mittelwertverhältnis | Median p99.9-Verhältnis | größtes CPU-Maximum vorher / nachher (µs) | CPU-Überschreitungen vorher / nachher | Wandzeit-Überschreitungen vorher / nachher |
|---|---:|---:|---:|---|---|---|
| Neutral SCORE | 70 | 0.937 | 1.001 | 8334.280 / 25382.400 | 363 / 355 | 378 / 380 |
| John Barry | 70 | 0.658 | 0.707 | 53107.300 / 34524.900 | 1431 / 753 | 1463 / 778 |
| Bernard Herrmann | 70 | 0.889 | 0.888 | 8317.360 / 6436.660 | 930 / 935 | 953 / 953 |
| John Williams | 70 | 0.885 | 0.885 | 12301.700 / 74774.600 | 1192 / 968 | 1215 / 985 |
| Ennio Morricone | 70 | 0.915 | 0.912 | 53955.300 / 30133.700 | 482 / 390 | 507 / 409 |
| Dark Synth | 70 | 0.906 | 0.882 | 4708.720 / 5280.100 | 434 / 449 | 450 / 465 |
| Neutral POP/ROCK | 70 | 0.949 | 0.955 | 20992.800 / 5290.070 | 334 / 336 | 362 / 352 |

## Alle Puffergrößen – Thread-CPU, schnelle XYZ-Fahrt, Wiederholung 0

| Profil | Samples | Stand | Mittel | Median | p95 | p99 | p99.9 | Maximum | Überschreitungen |
|---|---:|---|---:|---:|---:|---:|---:|---:|---:|
| Neutral SCORE | 64 | before | 20.786 | 13.563 | 39.768 | 108.751 | 231.103 | 2264.790 | 1 |
| Neutral SCORE | 64 | after | 20.004 | 11.943 | 40.757 | 111.394 | 240.606 | 2241.260 | 1 |
| Neutral SCORE | 128 | before | 21.318 | 13.832 | 41.306 | 108.735 | 258.778 | 1182.310 | 0 |
| Neutral SCORE | 128 | after | 20.430 | 11.821 | 44.189 | 112.060 | 308.519 | 987.827 | 0 |
| Neutral SCORE | 256 | before | 24.067 | 13.758 | 59.157 | 125.639 | 672.090 | 3142.720 | 0 |
| Neutral SCORE | 256 | after | 22.885 | 12.183 | 56.130 | 124.364 | 668.392 | 2267.290 | 0 |
| Neutral SCORE | 512 | before | 24.032 | 14.236 | 67.309 | 141.783 | 358.336 | 1007.740 | 0 |
| Neutral SCORE | 512 | after | 22.807 | 12.890 | 67.402 | 137.415 | 272.077 | 1015.460 | 0 |
| Neutral SCORE | 1024 | before | 38.697 | 21.650 | 105.367 | 194.784 | 660.716 | 1630.820 | 0 |
| Neutral SCORE | 1024 | after | 33.609 | 18.841 | 99.429 | 179.674 | 385.041 | 950.610 | 0 |
| John Barry | 64 | before | 51.638 | 17.059 | 239.077 | 353.968 | 1385.830 | 3717.720 | 85 |
| John Barry | 64 | after | 34.408 | 15.373 | 110.427 | 222.211 | 617.698 | 3699.190 | 5 |
| John Barry | 128 | before | 50.881 | 17.042 | 245.641 | 338.809 | 1321.470 | 3070.610 | 2 |
| John Barry | 128 | after | 35.049 | 15.574 | 107.111 | 205.898 | 777.105 | 3172.710 | 4 |
| John Barry | 256 | before | 56.594 | 17.298 | 247.409 | 374.831 | 1405.120 | 41083.500 | 1 |
| John Barry | 256 | after | 34.834 | 15.468 | 107.489 | 199.546 | 850.553 | 3456.470 | 0 |
| John Barry | 512 | before | 56.797 | 17.748 | 261.341 | 414.993 | 1355.540 | 2420.530 | 0 |
| John Barry | 512 | after | 34.947 | 15.860 | 107.549 | 197.340 | 607.871 | 1424.610 | 0 |
| John Barry | 1024 | before | 82.994 | 26.458 | 376.892 | 588.379 | 2116.800 | 2403.670 | 0 |
| John Barry | 1024 | after | 52.322 | 24.062 | 158.256 | 319.774 | 920.917 | 1258.830 | 0 |
| Bernard Herrmann | 64 | before | 40.519 | 33.766 | 75.926 | 144.021 | 368.171 | 3193.600 | 15 |
| Bernard Herrmann | 64 | after | 36.684 | 31.006 | 69.111 | 129.740 | 287.428 | 1718.550 | 2 |
| Bernard Herrmann | 128 | before | 39.470 | 33.793 | 70.059 | 125.649 | 322.086 | 1902.310 | 0 |
| Bernard Herrmann | 128 | after | 38.605 | 31.559 | 85.316 | 148.511 | 383.639 | 2905.140 | 1 |
| Bernard Herrmann | 256 | before | 41.125 | 33.827 | 84.080 | 152.668 | 282.592 | 1503.820 | 0 |
| Bernard Herrmann | 256 | after | 37.891 | 30.691 | 76.287 | 143.023 | 323.181 | 2120.260 | 0 |
| Bernard Herrmann | 512 | before | 42.020 | 34.126 | 83.142 | 159.036 | 423.418 | 1940.490 | 0 |
| Bernard Herrmann | 512 | after | 42.428 | 31.893 | 93.958 | 182.141 | 693.258 | 2472.950 | 0 |
| Bernard Herrmann | 1024 | before | 56.451 | 41.847 | 126.333 | 211.241 | 431.371 | 1921.400 | 0 |
| Bernard Herrmann | 1024 | after | 49.534 | 37.169 | 106.497 | 182.660 | 392.534 | 1486.500 | 0 |
| John Williams | 64 | before | 24.765 | 18.382 | 45.138 | 109.027 | 292.094 | 2686.890 | 2 |
| John Williams | 64 | after | 23.503 | 16.577 | 43.588 | 113.159 | 404.486 | 2883.340 | 1 |
| John Williams | 128 | before | 27.209 | 18.928 | 58.802 | 126.401 | 743.415 | 3505.360 | 1 |
| John Williams | 128 | after | 23.820 | 16.478 | 44.260 | 113.642 | 458.538 | 2820.090 | 1 |
| John Williams | 256 | before | 28.484 | 18.846 | 63.963 | 142.734 | 816.775 | 3242.400 | 0 |
| John Williams | 256 | after | 32.786 | 17.756 | 62.502 | 149.235 | 764.547 | 74774.600 | 1 |
| John Williams | 512 | before | 48.931 | 19.052 | 100.058 | 818.119 | 2645.600 | 3851.220 | 0 |
| John Williams | 512 | after | 29.881 | 17.415 | 79.127 | 173.001 | 723.512 | 2795.770 | 0 |
| John Williams | 1024 | before | 49.511 | 29.217 | 125.495 | 245.860 | 1208.470 | 2860.040 | 0 |
| John Williams | 1024 | after | 46.280 | 26.445 | 120.804 | 262.153 | 936.314 | 2875.560 | 0 |
| Ennio Morricone | 64 | before | 23.386 | 16.114 | 44.318 | 99.838 | 250.485 | 1443.570 | 1 |
| Ennio Morricone | 64 | after | 21.065 | 14.349 | 41.588 | 72.617 | 190.000 | 2878.140 | 2 |
| Ennio Morricone | 128 | before | 23.898 | 15.777 | 45.088 | 104.606 | 282.881 | 1424.290 | 0 |
| Ennio Morricone | 128 | after | 20.951 | 14.427 | 41.090 | 81.462 | 181.616 | 1394.540 | 0 |
| Ennio Morricone | 256 | before | 23.785 | 16.287 | 45.076 | 97.480 | 233.204 | 441.707 | 0 |
| Ennio Morricone | 256 | after | 23.340 | 14.633 | 46.507 | 104.136 | 253.819 | 486.472 | 0 |
| Ennio Morricone | 512 | before | 25.218 | 16.355 | 51.455 | 111.060 | 329.095 | 977.686 | 0 |
| Ennio Morricone | 512 | after | 23.897 | 14.556 | 43.605 | 97.478 | 466.462 | 1890.940 | 0 |
| Ennio Morricone | 1024 | before | 40.785 | 24.234 | 79.214 | 129.713 | 2121.750 | 4063.760 | 0 |
| Ennio Morricone | 1024 | after | 34.544 | 21.664 | 87.575 | 145.454 | 264.094 | 486.881 | 0 |
| Dark Synth | 64 | before | 16.044 | 13.176 | 28.940 | 75.004 | 201.092 | 3836.930 | 1 |
| Dark Synth | 64 | after | 15.757 | 12.047 | 24.652 | 82.367 | 355.991 | 2232.600 | 9 |
| Dark Synth | 128 | before | 16.364 | 13.182 | 28.427 | 80.148 | 195.458 | 1470.560 | 0 |
| Dark Synth | 128 | after | 14.025 | 11.457 | 23.450 | 68.194 | 157.365 | 433.515 | 0 |
| Dark Synth | 256 | before | 16.580 | 13.098 | 29.940 | 79.113 | 196.264 | 2178.330 | 0 |
| Dark Synth | 256 | after | 14.821 | 11.901 | 25.416 | 77.922 | 194.027 | 474.562 | 0 |
| Dark Synth | 512 | before | 30.957 | 13.379 | 35.140 | 438.493 | 2338.750 | 3982.090 | 0 |
| Dark Synth | 512 | after | 20.593 | 12.667 | 34.046 | 122.536 | 1320.010 | 2950.200 | 0 |
| Dark Synth | 1024 | before | 23.895 | 18.934 | 45.551 | 104.428 | 207.866 | 418.155 | 0 |
| Dark Synth | 1024 | after | 20.825 | 16.871 | 39.223 | 82.460 | 167.538 | 308.691 | 0 |
| Neutral POP/ROCK | 64 | before | 15.585 | 8.873 | 82.130 | 131.655 | 268.020 | 1582.080 | 1 |
| Neutral POP/ROCK | 64 | after | 15.365 | 7.683 | 82.382 | 136.962 | 277.712 | 5290.070 | 2 |
| Neutral POP/ROCK | 128 | before | 19.737 | 9.439 | 88.939 | 158.686 | 364.929 | 1279.260 | 0 |
| Neutral POP/ROCK | 128 | after | 15.670 | 7.912 | 85.549 | 138.510 | 317.553 | 909.962 | 0 |
| Neutral POP/ROCK | 256 | before | 18.078 | 9.267 | 88.332 | 151.094 | 370.830 | 1038.830 | 0 |
| Neutral POP/ROCK | 256 | after | 16.640 | 7.880 | 84.036 | 149.595 | 365.104 | 960.546 | 0 |
| Neutral POP/ROCK | 512 | before | 20.817 | 9.415 | 93.910 | 190.436 | 459.412 | 1053.400 | 0 |
| Neutral POP/ROCK | 512 | after | 18.960 | 8.007 | 89.258 | 169.340 | 431.487 | 856.151 | 0 |
| Neutral POP/ROCK | 1024 | before | 31.912 | 13.724 | 143.542 | 314.059 | 517.418 | 871.697 | 0 |
| Neutral POP/ROCK | 1024 | after | 30.142 | 11.822 | 138.704 | 274.723 | 494.108 | 859.070 | 0 |

## Alle Puffergrößen – Wandzeit, schnelle XYZ-Fahrt, Wiederholung 0

| Profil | Samples | Stand | Mittel | Median | p95 | p99 | p99.9 | Maximum | Überschreitungen |
|---|---:|---|---:|---:|---:|---:|---:|---:|---:|
| Neutral SCORE | 64 | before | 21.103 | 13.804 | 40.424 | 109.646 | 250.526 | 2266.620 | 1 |
| Neutral SCORE | 64 | after | 20.333 | 12.217 | 41.064 | 111.710 | 251.077 | 2242.540 | 2 |
| Neutral SCORE | 128 | before | 21.612 | 14.082 | 41.574 | 109.841 | 272.781 | 1182.930 | 0 |
| Neutral SCORE | 128 | after | 20.719 | 12.128 | 45.244 | 112.868 | 308.904 | 989.837 | 0 |
| Neutral SCORE | 256 | before | 24.489 | 13.996 | 60.079 | 126.261 | 690.598 | 3143.620 | 0 |
| Neutral SCORE | 256 | after | 23.170 | 12.427 | 57.214 | 124.692 | 669.511 | 2268.460 | 0 |
| Neutral SCORE | 512 | before | 24.307 | 14.472 | 68.145 | 142.104 | 358.955 | 1008.080 | 0 |
| Neutral SCORE | 512 | after | 23.139 | 13.144 | 68.059 | 138.679 | 272.856 | 1015.780 | 0 |
| Neutral SCORE | 1024 | before | 39.007 | 21.933 | 105.861 | 195.077 | 662.604 | 1632.940 | 0 |
| Neutral SCORE | 1024 | after | 33.930 | 19.096 | 100.104 | 180.023 | 385.961 | 950.982 | 0 |
| John Barry | 64 | before | 51.936 | 17.310 | 239.455 | 354.631 | 1386.540 | 3718.940 | 85 |
| John Barry | 64 | after | 34.718 | 15.613 | 110.775 | 222.923 | 618.383 | 3700.360 | 5 |
| John Barry | 128 | before | 51.203 | 17.282 | 246.012 | 339.632 | 1322.140 | 3074.260 | 2 |
| John Barry | 128 | after | 35.344 | 15.846 | 107.563 | 208.523 | 777.611 | 3173.710 | 4 |
| John Barry | 256 | before | 56.993 | 17.534 | 249.714 | 377.384 | 1405.820 | 41082.800 | 1 |
| John Barry | 256 | after | 35.122 | 15.710 | 107.995 | 203.377 | 852.785 | 3457.660 | 0 |
| John Barry | 512 | before | 57.096 | 17.991 | 261.615 | 415.902 | 1356.210 | 2426.780 | 0 |
| John Barry | 512 | after | 35.249 | 16.107 | 107.861 | 197.569 | 608.616 | 1425.070 | 0 |
| John Barry | 1024 | before | 83.510 | 26.772 | 377.378 | 588.657 | 2117.690 | 2605.280 | 0 |
| John Barry | 1024 | after | 52.719 | 24.337 | 158.669 | 323.849 | 921.670 | 1259.860 | 0 |
| Bernard Herrmann | 64 | before | 40.850 | 34.026 | 76.685 | 145.283 | 368.870 | 3196.430 | 15 |
| Bernard Herrmann | 64 | after | 37.095 | 31.298 | 70.057 | 130.710 | 293.697 | 5007.860 | 3 |
| Bernard Herrmann | 128 | before | 39.771 | 34.041 | 70.459 | 126.155 | 333.967 | 1903.410 | 0 |
| Bernard Herrmann | 128 | after | 38.927 | 31.830 | 85.982 | 149.467 | 384.146 | 2907.630 | 1 |
| Bernard Herrmann | 256 | before | 41.428 | 34.087 | 84.567 | 153.920 | 283.198 | 1504.290 | 0 |
| Bernard Herrmann | 256 | after | 38.230 | 30.948 | 77.174 | 145.654 | 327.935 | 2122.280 | 0 |
| Bernard Herrmann | 512 | before | 42.327 | 34.379 | 83.522 | 159.831 | 424.858 | 1946.430 | 0 |
| Bernard Herrmann | 512 | after | 42.748 | 32.163 | 94.891 | 182.878 | 693.668 | 2473.960 | 0 |
| Bernard Herrmann | 1024 | before | 56.910 | 42.111 | 128.979 | 215.094 | 432.011 | 1926.350 | 0 |
| Bernard Herrmann | 1024 | after | 49.838 | 37.447 | 106.936 | 182.976 | 393.264 | 1487.060 | 0 |
| John Williams | 64 | before | 25.059 | 18.620 | 45.484 | 110.161 | 292.782 | 2687.940 | 2 |
| John Williams | 64 | after | 23.798 | 16.820 | 43.956 | 114.378 | 405.558 | 2884.450 | 1 |
| John Williams | 128 | before | 27.528 | 19.180 | 59.405 | 127.308 | 743.622 | 3506.680 | 1 |
| John Williams | 128 | after | 24.108 | 16.722 | 44.577 | 114.423 | 460.437 | 2821.240 | 1 |
| John Williams | 256 | before | 28.765 | 19.096 | 65.010 | 144.606 | 818.789 | 3242.860 | 0 |
| John Williams | 256 | after | 33.064 | 17.997 | 63.000 | 149.937 | 764.880 | 74772.400 | 1 |
| John Williams | 512 | before | 49.235 | 19.286 | 100.423 | 818.633 | 2646.050 | 3852.270 | 0 |
| John Williams | 512 | after | 30.196 | 17.656 | 79.585 | 177.516 | 724.233 | 2796.380 | 0 |
| John Williams | 1024 | before | 49.940 | 29.474 | 126.163 | 264.043 | 1214.360 | 2865.910 | 0 |
| John Williams | 1024 | after | 46.575 | 26.703 | 121.063 | 262.862 | 937.054 | 2876.480 | 0 |
| Ennio Morricone | 64 | before | 23.684 | 16.357 | 44.594 | 100.889 | 252.829 | 1444.610 | 1 |
| Ennio Morricone | 64 | after | 21.343 | 14.589 | 41.907 | 73.312 | 197.365 | 2893.630 | 2 |
| Ennio Morricone | 128 | before | 24.183 | 16.017 | 45.408 | 105.385 | 283.715 | 1427.890 | 0 |
| Ennio Morricone | 128 | after | 21.256 | 14.667 | 41.586 | 82.399 | 197.300 | 1395.630 | 0 |
| Ennio Morricone | 256 | before | 24.050 | 16.522 | 45.324 | 97.898 | 233.909 | 448.177 | 0 |
| Ennio Morricone | 256 | after | 23.893 | 14.881 | 48.873 | 106.141 | 294.578 | 2191.840 | 0 |
| Ennio Morricone | 512 | before | 25.476 | 16.595 | 51.809 | 111.697 | 329.591 | 978.735 | 0 |
| Ennio Morricone | 512 | after | 24.391 | 14.794 | 44.045 | 103.884 | 476.529 | 1896.110 | 0 |
| Ennio Morricone | 1024 | before | 41.205 | 24.489 | 80.150 | 132.551 | 2124.350 | 4064.920 | 0 |
| Ennio Morricone | 1024 | after | 34.861 | 21.915 | 88.028 | 147.590 | 264.856 | 487.579 | 0 |
| Dark Synth | 64 | before | 16.421 | 13.428 | 29.294 | 76.372 | 206.506 | 4630.960 | 2 |
| Dark Synth | 64 | after | 16.077 | 12.301 | 24.963 | 83.328 | 370.387 | 2233.740 | 9 |
| Dark Synth | 128 | before | 16.692 | 13.427 | 28.801 | 81.897 | 197.540 | 1472.580 | 0 |
| Dark Synth | 128 | after | 14.304 | 11.699 | 23.784 | 68.906 | 158.432 | 434.441 | 0 |
| Dark Synth | 256 | before | 16.864 | 13.345 | 30.301 | 79.932 | 196.538 | 2180.060 | 0 |
| Dark Synth | 256 | after | 15.095 | 12.144 | 25.719 | 78.840 | 194.605 | 475.365 | 0 |
| Dark Synth | 512 | before | 31.305 | 13.625 | 35.401 | 457.133 | 2340.700 | 3983.080 | 0 |
| Dark Synth | 512 | after | 21.128 | 12.915 | 34.494 | 122.946 | 1333.220 | 2951.400 | 0 |
| Dark Synth | 1024 | before | 24.159 | 19.178 | 45.816 | 105.371 | 208.119 | 418.546 | 0 |
| Dark Synth | 1024 | after | 21.087 | 17.112 | 39.521 | 82.766 | 167.837 | 309.635 | 0 |
| Neutral POP/ROCK | 64 | before | 15.845 | 9.100 | 82.365 | 132.390 | 268.436 | 1584.490 | 1 |
| Neutral POP/ROCK | 64 | after | 15.681 | 7.913 | 82.620 | 137.735 | 283.981 | 5301.870 | 2 |
| Neutral POP/ROCK | 128 | before | 20.243 | 9.674 | 89.257 | 160.101 | 377.899 | 3400.830 | 1 |
| Neutral POP/ROCK | 128 | after | 15.950 | 8.151 | 85.936 | 138.888 | 318.287 | 910.471 | 0 |
| Neutral POP/ROCK | 256 | before | 18.330 | 9.499 | 88.575 | 151.499 | 371.131 | 1040.250 | 0 |
| Neutral POP/ROCK | 256 | after | 16.915 | 8.116 | 84.279 | 149.908 | 369.435 | 960.991 | 0 |
| Neutral POP/ROCK | 512 | before | 21.073 | 9.648 | 94.663 | 190.703 | 459.921 | 1054.530 | 0 |
| Neutral POP/ROCK | 512 | after | 19.214 | 8.248 | 89.496 | 169.769 | 431.724 | 856.478 | 0 |
| Neutral POP/ROCK | 1024 | before | 32.216 | 13.975 | 144.037 | 314.353 | 518.247 | 871.997 | 0 |
| Neutral POP/ROCK | 1024 | after | 30.437 | 12.066 | 138.931 | 275.134 | 494.784 | 859.396 | 0 |

## Vier Instanzen und tatsächliche GUI

Alle Eingaben identisch; Instanzen müssen unabhängige, identische musikalische Ergebnisse erzeugen. Serielle Gesamtsummen enthalten die verschachtelten Messhüllen. Bei parallel4 zeigt jede Spalte den größten Einzelinstanzwert; dies ist weder ein gepooltes Quantil noch die Summe der Überschreitungen. Parallele Worker bilden den kritischen DAW-Threadpfad nicht nach. GUI läuft zeitlich getaktet. Hier Wiederholung 0.

| Profil | Modus | Stand | CPU Mittel | CPU p99.9 | CPU Maximum | CPU Überschreitungen | Wand Maximum | Wand Überschreitungen |
|---|---|---|---:|---:|---:|---:|---:|---:|
| Neutral SCORE | serial4 | before | 93.620 | 1261.860 | 7985.050 | 12 | 7984.990 | 13 |
| Neutral SCORE | serial4 | after | 87.232 | 1282.790 | 12671.500 | 20 | 12671.300 | 23 |
| Neutral SCORE | parallel4 | before | 41.805 | 456.467 | 6735.460 | 6 | 42557.600 | 113 |
| Neutral SCORE | parallel4 | after | 40.294 | 485.758 | 5155.740 | 4 | 42390.200 | 88 |
| Neutral SCORE | gui | before | 23.687 | 295.714 | 1353.730 | 0 | 1354.700 | 0 |
| Neutral SCORE | gui | after | 23.860 | 507.227 | 3943.250 | 1 | 7964.200 | 1 |
| John Barry | serial4 | before | 120.283 | 4840.700 | 15047.900 | 138 | 15047.600 | 145 |
| John Barry | serial4 | after | 96.031 | 1914.620 | 17379.600 | 22 | 17379.100 | 24 |
| John Barry | parallel4 | before | 46.120 | 2114.710 | 5102.180 | 19 | 41872.900 | 221 |
| John Barry | parallel4 | after | 44.494 | 868.290 | 9672.180 | 11 | 38822.700 | 108 |
| John Barry | gui | before | 113.404 | 2281.730 | 5342.380 | 8 | 5345.250 | 9 |
| John Barry | gui | after | 71.813 | 945.162 | 6825.740 | 2 | 6827.450 | 2 |
| Bernard Herrmann | serial4 | before | 172.932 | 2236.450 | 44259.100 | 71 | 44273.300 | 80 |
| Bernard Herrmann | serial4 | after | 151.211 | 1559.030 | 7285.950 | 20 | 7298.300 | 25 |
| Bernard Herrmann | parallel4 | before | 81.487 | 2065.440 | 30748.300 | 72 | 91836.600 | 315 |
| Bernard Herrmann | parallel4 | after | 67.884 | 563.212 | 8904.930 | 7 | 41980.700 | 162 |
| Bernard Herrmann | gui | before | 63.641 | 1403.500 | 3688.140 | 2 | 3703.080 | 6 |
| Bernard Herrmann | gui | after | 51.815 | 776.260 | 3313.940 | 1 | 4806.270 | 2 |
| John Williams | serial4 | before | 111.556 | 2042.600 | 10659.800 | 34 | 17952.000 | 35 |
| John Williams | serial4 | after | 102.883 | 1968.210 | 12293.900 | 25 | 12637.300 | 30 |
| John Williams | parallel4 | before | 48.388 | 818.765 | 9323.730 | 10 | 65945.700 | 114 |
| John Williams | parallel4 | after | 46.710 | 804.381 | 5592.970 | 5 | 39399.200 | 105 |
| John Williams | gui | before | 33.713 | 1220.620 | 10176.100 | 3 | 17407.000 | 4 |
| John Williams | gui | after | 28.979 | 891.708 | 11208.700 | 2 | 11209.500 | 2 |
| Ennio Morricone | serial4 | before | 94.229 | 585.514 | 17181.800 | 7 | 17181.300 | 9 |
| Ennio Morricone | serial4 | after | 89.263 | 605.246 | 3585.710 | 5 | 4141.500 | 9 |
| Ennio Morricone | parallel4 | before | 42.212 | 360.852 | 3912.630 | 8 | 36991.300 | 79 |
| Ennio Morricone | parallel4 | after | 40.271 | 809.172 | 12533.800 | 11 | 40549.500 | 93 |
| Ennio Morricone | gui | before | 27.308 | 663.339 | 2137.310 | 0 | 2140.330 | 0 |
| Ennio Morricone | gui | after | 25.424 | 481.108 | 1766.060 | 0 | 4129.350 | 1 |
| Dark Synth | serial4 | before | 71.725 | 1868.410 | 5422.890 | 20 | 11366.300 | 21 |
| Dark Synth | serial4 | after | 58.882 | 406.547 | 3570.830 | 4 | 9144.690 | 5 |
| Dark Synth | parallel4 | before | 28.555 | 219.875 | 7606.460 | 3 | 37421.000 | 56 |
| Dark Synth | parallel4 | after | 26.265 | 262.267 | 3982.180 | 1 | 37547.100 | 50 |
| Dark Synth | gui | before | 58.493 | 2073.430 | 2864.080 | 1 | 3545.330 | 3 |
| Dark Synth | gui | after | 52.811 | 2023.600 | 2881.050 | 2 | 2882.330 | 2 |
| Neutral POP/ROCK | serial4 | before | 176.843 | 5403.900 | 11585.700 | 1571 | 15117.100 | 1579 |
| Neutral POP/ROCK | serial4 | after | 170.220 | 5349.500 | 9371.670 | 1603 | 9371.680 | 1611 |
| Neutral POP/ROCK | parallel4 | before | 85.834 | 3475.790 | 63751.800 | 391 | 77265.600 | 911 |
| Neutral POP/ROCK | parallel4 | after | 79.922 | 3336.100 | 7394.880 | 352 | 45012.100 | 879 |
| Neutral POP/ROCK | gui | before | 24.822 | 1712.940 | 2985.290 | 3 | 5360.940 | 5 |
| Neutral POP/ROCK | gui | after | 21.301 | 549.057 | 2312.520 | 0 | 2314.140 | 0 |

## Wiederholungsprüfung der drei größten Nachher-Maxima

Die drei Fälle mit den größten CPU-Maxima der vollständigen Nachher-Hauptmatrix wurden anschließend jeweils fünfmal zusätzlich gepaart wiederholt. Die ursprünglichen Ausreißer bleiben oben und in den Rohdaten erhalten. Werte: Minimum / Median / Maximum der fünf Laufmaxima, keine gepoolten Blockquantile. Alle Wiederholungen müssen dieselben MIDI-Prüfsummen vor/nach liefern.

| Profil | Samples / Szenario | Stand | CPU-Maxima (µs) | Wandzeit-Maxima (µs) |
|---|---|---|---|---|
| John Williams | 256 / 3 | before | 2666.320 / 2821.410 / 2918.060 | 2812.330 / 3188.400 / 4725.470 |
| John Williams | 256 / 3 | after | 2768.530 / 3225.230 / 5116.280 | 2769.470 / 3226.020 / 5118.700 |
| John Williams | 512 / 6 | before | 2837.300 / 2865.740 / 3463.330 | 2838.400 / 2900.920 / 5709.560 |
| John Williams | 512 / 6 | after | 2719.910 / 3086.540 / 63938.100 | 2720.350 / 3087.730 / 68967.400 |
| John Barry | 128 / 4 | before | 2440.890 / 3147.880 / 26688.900 | 2459.090 / 3880.530 / 26689.000 |
| John Barry | 128 / 4 | after | 1476.330 / 2111.650 / 6124.420 | 1482.810 / 2252.630 / 6126.000 |
