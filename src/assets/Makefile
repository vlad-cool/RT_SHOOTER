.PHONY: all clean

IMAGES = img/aim.h img/ducks.h img/scenes.h img/transscenes.h
JS_FILES = js/responce.h
HTML_FILES = templates/responce.h templates/calibration.h

all: assets.h

assets.h: $(IMAGES) $(JS_FILES) $(HTML_FILES)
	cat $(IMAGES) $(JS_FILES) $(HTML_FILES) > assets.h

img/%.h: img/%.png
	xxd -i $< > $@

js/%.h: js/%.js
	xxd -i $< > $@

templates/%.h: templates/%.html
	xxd -i $< > $@

clean:
	rm -f img/*.h js/*.h templates/*.h