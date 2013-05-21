cs: login.o auth.o user.o user_mod.o material.o material_mod.o main.o init_db.o
	gcc -o cs login.o auth.o user.o user_mod.o material.o material_mod.o main.o init_db.o -lsqlite3 `pkg-config --cflags --libs gtk+-3.0 gmodule-export-2.0`

main.o: main.c material.h user.h auth.h login.h
	gcc -g -c main.c login.h `pkg-config --cflags --libs gtk+-3.0 gmodule-export-2.0`


material.o: material.c material.h
	gcc -g -c material.c material.h  `pkg-config --cflags --libs gtk+-3.0 gmodule-export-2.0`
material_mod.o: material_mod.c material_mod.h material.h
	gcc -g -c material_mod.c material_mod.h material.h `pkg-config --cflags --libs gtk+-3.0 gmodule-export-2.0`


user.o: user.c user.h
	gcc -g -c user.c user.h  `pkg-config --cflags --libs gtk+-3.0 gmodule-export-2.0`
user_mod.o: user_mod.c user_mod.h user.h common.h
	gcc -g -c user_mod.c user_mod.h user.h common.h `pkg-config --cflags --libs gtk+-3.0 gmodule-export-2.0`

auth.o: auth.c auth.h user.h user_mod.h 
	gcc -g -c auth.c user.h user_mod.h `pkg-config --cflags --libs gtk+-3.0 gmodule-export-2.0`

init_db.o: init_db.c init_db.h 
	gcc -g -c init_db.c init_db.h  

login.o: login.c login.h user.h
	gcc -g -c login.c login.h user.h `pkg-config --cflags --libs gtk+-3.0 gmodule-export-2.0`
