# linux-licence

Program za zadavanje trail perioda na linux sistemima u maksimalnom periodu od 12 meseci.
Use case: Bilo kakve masine koje kosite linux sisteme, kao na primer CNC ruteri.

	Pre korišćenja promeni sve pathove do baze podataka kao i pathove do exe fajlova.
	Program treba kompjlirati na sledeći naćin:
		1. cd to_Licenca_Dir | g++ main.cpp operacije_baza.cpp -o <naziv_exe_fajla>
		2. cd to_Licenca_Check_Dir |  g++ main.cpp operacije_baza.cpp -o <naziv_exe_fajla>
		3. cd to_Licenca_Repeat_Dir | g++ main.cpp -o <naziv_exe_fajla>

	Nakon toga postaviti sifru za bios i namestiti linux service kao root user na sledeci nacin:
		1. cd /etc/systemd/system
		2. Napraviti fajl pod nazivom linux-service.service i u njega ubaciti sledece: 
		(Paznja: ako izaberete drugi .service naziv to morate promeniti i u Licenca_Check main.cpp fajlu i ponovo kompajlirati)
	
			[Unit]
			Description= Linux_Service

			[Service]
			User=<user e.g. root>
			WorkingDirectory=<path do direktorijuma gde se nalazi Licenca_Repeat exe fajl>
			ExecStart=<naziv Licenca_Repeat exe fajla>
			Restart=always

			[Install]
			WantedBy=multi-user.target
			
	3. Osvezavanje fajla za servisima da bi dodali novi servis:
			sudo systemctl daemon-reload
			
	4. Pokretanje vaseg novog servisa:
			sudo systemctl start your-service.service
			
	5. Provera statusa servisa, trebalo bi da bude pokrenut:
			sudo systemctl status linux-service.service
			
	6. Omogućavanje servisu da se pokrene pri svakom pokretanju linuxa: 
		(Pažnja: Ovo je veoma važno za dobro funkcionisanje programa)
			sudo systemctl enable linux-service.service

I to je to, sada bi trebalo da program radi u pozadini bez problema.
