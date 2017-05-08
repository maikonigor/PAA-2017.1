#------------------------------------------------------------------------------

SOURCE=main.cpp convex-hull.cpp convex-hull.h
MYPROGRAM=convexHull

#MYINCLUDES=/home/scale/g++Projects/gLib/
#MYLIBRARIES=gl -lglu -lglut
CC=g++

#------------------------------------------------------------------------------



all: $(MYPROGRAM)



$(MYPROGRAM): $(SOURCE)

#   $(CC) -I$(MYINCLUDES) $(SOURCE) -o$(MYPROGRAM) -l$(MYLIBRARIES)
	$(CC) $(SOURCE) -o$(MYPROGRAM) -l GL -l GLU -l glut
clean:

	rm -f $(MYPROGRAM)



