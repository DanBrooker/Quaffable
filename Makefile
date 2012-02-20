APP = FantasyRL

SOURCES = SDLMain.m Ascii.cpp Colour.cpp Container.cpp Display.cpp ExitMenu.cpp FantasyRL.cpp Heightmap.cpp Holdable.cpp Image.cpp Label.cpp LabelValue.cpp Lightmap.cpp Map.cpp Menu.cpp Monster.cpp Object.cpp Perlin.cpp Random.cpp Range.cpp Roguelike.cpp SDLWindow.cpp Sprite.cpp Throwable.cpp Tile.cpp Timer.cpp Voronoi.cpp Weapon.cpp Window.cpp World.cpp mtrand.cpp
OBJS = $(SOURCES:.cpp=.o) SDLMain.o

# ----------------------------------------------------------------------

CC = g++
CFLAGS = -c -Wall

LD	= $(CC)
LDFLAGS =\
  	-lSDLmain\
	-fraework SDL\
	-framework SDL_image\
   -framework OpenGL\
	-framework Cocoa
    
VPATH = Code/

# ----------------------------------------------------------------------

all: $(SOURCES) $(APP)

$(APP):	$(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^
	cp $(APP) $(APP).app
	@chmod 755 $(APP).app/$(APP)
	@touch $(APP).app
     
clean:
	rm -f $(APP) $(APP).app/$(APP) *.o f?