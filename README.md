# Vectorclone


Vector bibliotekos kopija c++ kalba

Turi visas funkcijas reikiamas 2 užduočiai ir dar daugiau!


2 užduoties vykdymo laikas su std::vector ir su mano Vector su 100000 studentų:

| Versija  | nuskaitymas | skirstymas | rezultato rašymas| visas laikas |
| ------------- | ------------- | ------------- | ------------- | ------------- |
| std::vector | 0.360002  | 0.050907  | 0.100674 |  0.511583 |
| Vector| 0.321807 |  0.050884  | 0.091755 | 0.464446 |


push_back laiko testavimas faile test1.cpp:

| Versija  | 10000| 100000 | 1000000| 10000000 | 100000000 |
| ------------- | ------------- | ------------- | ------------- | ------------- | ------------- |
| std::vector | 0  | 0.000998  | 0.012969|  0.136373 | 1.34282 |
| Vector| 0|  0.001995  |0.016953 | 0.163229 | 1.52043 |


kiek kartu įveyksta perskirstymas testavimas faile test1.cpp:

| Versija  | 10000| 100000 | 1000000| 10000000 | 100000000 |
| ------------- | ------------- | ------------- | ------------- | ------------- | ------------- |
| std::vector | 14  | 17  | 20|  24 | 27 |
| Vector| 14|  17  | 20 | 24| 27 |


Pasirinktinių funkcijų testai test.cpp faile
