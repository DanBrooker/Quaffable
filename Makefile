APP = FantasyRL

DOTH = main.cpp
SOURCES = Ascii.cpp Colour.cpp Display.cpp Heightmap.cpp Roguelike.cpp Image.cpp Label.cpp LabelValue.cpp Lightmap.cpp Map.cpp Menu.cpp ExitMenu.cpp Object.cpp Monster.cpp Player.cpp Perlin.cpp Random.cpp SDLWindow.cpp Sprite.cpp Tile.cpp Timer.cpp Voronoi.cpp Window.cpp World.cpp mtrand.cpp FantasyRL.cpp
OBJS = $(SOURCES:.cpp=.o) SDLMain.o

# ----------------------------------------------------------------------

CC = g++
CFLAGS = -c
INCLUDE = -I/Library/Frameworks/SDL.framework/Headers/

LD	= $(CC)
LDFLAGS = -framework SDL -framework SDL_image -framework OpenGL -framework Cocoa
    
VPATH = Code/

# ----------------------------------------------------------------------

all: $(SOURCES) $(APP)

$(APP):	$(OBJS) $(DOTH)
	$(LD) -o $@ $(LDFLAGS) $(INCLUDE) $^ 
	cp $(APP) $(APP).app/
	@chmod 755 $(APP).app/$(APP)
	@touch $(APP).app

%.o:	%.cpp
	$(CC) $(CFLAGS) $< $(INCLUDE)

%.o:	%.m
	$(CC) $(CFLAGS) $< $(INCLUDE)

clean:
	rm -f $(APP) $(APP).app/$(APP) *.o f? 