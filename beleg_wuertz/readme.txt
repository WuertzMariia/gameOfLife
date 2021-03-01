>>>>>>>>>>>>>>>>>>    GAME OF LIFE
Version: Mariia Würtz
Das Menü und die Hinweise in jedem Schritt sind selbsterklärend und der Nutzer kommt(hoffentlich) auch ohne README klar. 


-- Starten: .exe Datei ausführen
-- Auswahl: Enter
-- Editieren: Space(löschen/hinzufügen)
-- Escape: jederzeit kann man das Spiel neustarten.
-- Prozentangabe: 0-100 mit Pfeilen[bei Verletzung des Wertebereichs kommt eine Meldung]
-- Spielfeldgröße: 25x25 [kann unter #define widhth und #define length geändert werden]
-- Farben: Startzustand alle Zellen rot; danach je nach Anzahl der Nachbarnzellen rot oder grün; EditModus- neu hinzugefügte Zellen weiß. 

>>>>    Im Hauptmenü kann man: 

-3 verschiedene Startzustände laden(glider, pulsar and gosper_glider_gun) laden
-per Zufallszahlengenerator (mit Prozentangabe im nächsten Menüschritt - zu  wieviel Prozent das Spielfeld mit lebenden Zellen zu füllen ist) ein Startzustand generieren
-eine nach der Edition gespeicherte Datei laden
   ---> Bei erstmaliger Ausführung ist Storage leer. Man muss erst einen der o.g. Zustände laden>editieren>speichern. Danach erscheint die Datei im Storage.
        Man kann maximal 10 editierte Dateien speichern und anschließend den Zustand laden. Ab der Anzahl von 10 kommt eine Meldung und das Spiel startet neu. 
	

>>>>    Im zweiten Menüschritt:

Der Nutzer kann auswählen:
- Editieren (Ecp - Neustart)
- Editieren überspringen (Ecp - Neustart)
Editieren: SPACE; Navigation: Pfeile; Zustand speichern: Enter; Neustart: ESCAPE;
Bei der Eingabe des Dateinamens beachten: man kann beliebige Dateinamen speichern außer einer Leerzeichenkette. Extension ist nicht notwendig. 

>>>>    Im dritten Menüschirtt: 

-Schrittweise Abarbeitung (Enter-neue Generation, beliebige Taste - Neustart - Neustart)
-Fließende Animation(beliebige Taste - Neustart);





--------------------------------realisierte Funktionalität:-------------------------------------------------------------------------------------------
- Startzustände aus 3 Dateien  (Note 2)
- Startzustand per Zufallszahlengenerator(Prozentangabe nur im Bereich 0-100) (Note 2)
- Schrittweise und fließende Animation (Note 3)
- Editieren von jedem Zustand ist möglich(glider, pulsar and gosper_glider_gun). Auch per Zufallszahlengenerator ein (gefülltes oder leeres je nach Prozentangabe) Spielfeld erstellen und editieren. (Note 1)
- Speichern von editiertem Zustand(max. 10 Dateien) (Note 1)
- Anschließend im Hauptmenü "Den von Ihnen gespecheirten Zustand laden" (Note 1)
zustätzlich:
- mehrstufiges,nutzerfreundliches Menü mit Farbhilfen. 
- minimale Fehlerwahrscheinlichkeit(Menü/DAUEingabe und Umleitung zum Neustart bei Falscheingabe/Error/Escape)
- Anzeige und Head: lebende Zellen, Generation, Spielfeldgröße
- Lebende Zellen werden gefärbt, je nach der Anzahl der Nachbarnzellen. (lila bei 3 oder mehr Nachbarnzellen und grün bei genau 2 Nachbarnzellen). Im Edit-Modus: neue Zellen weiß. 


