all: compile
compile:
	./compile.py
deploy: 
	./compile.py --deploying
	rsync -Lavh --progress -e ssh output/* jongman@metallica.jmk.pe.kr:www/typ 
