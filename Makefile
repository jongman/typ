all:
	./compile.py
deploy:
	rsync -Lavh --progress -e ssh output/* jongman@jmk.pe.kr:www/typ 
