.PHONE: all clean

all: img/aim.h img/bird.h img/scenes.h js/responce.h templates/responce.h

img/aim.h: img/aim.png
	xxd -i img/aim.png > img/aim.h

img/bird.h: img/bird.png
	xxd -i img/bird.png > img/bird.h

img/scenes.h: img/scenes.png
	xxd -i img/scenes.png > img/scenes.h

js/responce.h: js/responce.js
	xxd -i js/responce.js > js/responce.h

templates/responce.h: templates/responce.html
	xxd -i templates/responce.html > templates/responce.h

clean:
	rm */*.h