# linux-trial

Program za zadavanje trial perioda na linux sistemima u maksimalnom periodu od 12 meseci.

Use case: Bilo kakve mašine koje koriste linux sistem, kao na primer CNC ruteri.

	Pre korišćenja promeni sve pathove do baze podataka kao i pathove do exe fajlova.
	Program treba kompjlirati na sledeći naćin:
		1. cd to_Licenca_Dir | g++ main.cpp operacije_baza.cpp -o <naziv_exe_fajla>
		2. cd to_Licenca_Check_Dir |  g++ main.cpp operacije_baza.cpp -o <naziv_exe_fajla>
