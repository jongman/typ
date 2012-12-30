all: compile
compile:
	./compile.py
deploy: compile
	rsync -Lavh --progress -e ssh output/* jongman@jmk.pe.kr:www/typ 
