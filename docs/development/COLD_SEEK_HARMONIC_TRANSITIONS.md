# Separater Hinweis: Übergangsstimmführung bei kaltem Seek

Unverändert seit `0b9281a`: Die Stimmführung am Eintritt einer neuen Score-Wendung
verwendet den zuvor tatsächlich erklungenen Flächensatz und Bass. Die letzten 64
bekannten Wendungsgrenzen behalten ihren Quellkontext für erneuten Seek/Loop.

Beim kalten Einstieg gibt es diese gespielte Vorgeschichte nicht. Auch aus dem Ring
verdrängte Grenzen sind unbekannt. Dort gilt der zyklische Plan der Zielwendung;
die Lage kann deshalb vom vollständigen vorherigen Durchlauf abweichen. Neustart
beginnt eine neue Szene und leert diesen Performance-Zustand.

Der Auftrag „Motivische Weiterentwicklung“ ändert oder behebt diese Einschränkung
nicht. Sie betrifft harmonische Eintrittslagen, nicht die Identität eines bereits
aufgenommenen Motivs. Siehe auch [Wendungsübergänge](WENDUNG_TRANSITIONS.md).
