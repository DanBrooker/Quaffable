APP = FantasyRL

DOTH = main.cpp
SOURCES = Ascii.cpp Colour.cpp Rect.cpp Point.cpp Display.cpp Heightmap.cpp Roguelike.cpp Stringer.cpp Image.cpp Label.cpp LabelValue.cpp Lightmap.cpp Map.cpp Menu.cpp ExitMenu.cpp Object.cpp Monster.cpp Player.cpp Perlin.cpp Random.cpp SDLWindow.cpp Sprite.cpp Tile.cpp Timer.cpp Voronoi.cpp Window.cpp World.cpp mtrand.cpp FantasyRL.cpp
OBJS = $(SOURCES:.cpp=.o) SDLMain.o

# ----------------------------------------------------------------------

CC = g++
CFLAGS = -arch i386 -c
INCLUDE = -I/Library/Frameworks/SDL.framework/Headers/

LD	= $(CC)
LDFLAGS = -arch i386 -framework SDL -framework SDL_image -framework OpenGL -framework Cocoa
    
VPATH = Code/

BUNDLE = $(APP).app/Contents
EXECUTABLE_PATH = $(BUNDLE)/MacOS
RESOURCES_PATH = $(BUNDLE)/Resources
FRAMEWORKS_PATH = $(BUNDLE)/Resources
FRAMEWORKS = /Library/Frameworks/SDL.framework /Library/Frameworks/SDL_image.framework

# ----------------------------------------------------------------------

all: $(SOURCES) $(APP)

$(APP):	$(OBJS) $(DOTH)
	$(LD) -o $@ $(LDFLAGS) $(INCLUDE) $^ 
	@mkdir -p $(EXECUTABLE_PATH) $(RESOURCES_PATH)
	# bundle
	#@ProcessInfoPlistFile $(BUNDLE)/Info.plist $(APP)-Info.plist
	#@builtin-infoPlistUtility $(APP)-Info.plist -genpkginfo $(BUNDLE)/PkgInfo -expandbuildsettings -platform macosx -o $(BUNDLE)/Info.plist
	# binary
	@mv $(APP) $(EXECUTABLE_PATH)
	@chmod 755 $(EXECUTABLE_PATH)
	# resources
	@cp $(VPATH)Images/* $(RESOURCES_PATH)
	# frameworks
	@touch $(APP).app

%.o:	%.cpp
	$(CC) $(CFLAGS) $< $(INCLUDE)

%.o:	%.m
	$(CC) $(CFLAGS) $< $(INCLUDE)

clean:
	rm -f $(APP) $(APP).app/$(APP) *.o f? 