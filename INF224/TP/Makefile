##########################################
#
#  Exemple de Makefile
#  Eric Lecolinet - Reda Dehak - Telecom ParisTech 2015
#  INF224 - TP C++ - http://www.telecom-paristech.fr/~elc/inf224
#'C:\Program Files (x86)\GnuWin32\bin\make.exe'
#
##########################################

#
# Nom du programme
#
PROG = monProgramme

#
# Fichiers sources (NE PAS METTRE les .h ni les .o seulement les .cpp)
#
SOURCES = Multimedia.cpp main.cpp

#
# Fichiers objets (ne pas modifier sauf si l'extension n'est pas .cpp)
#
OBJETS = ${SOURCES:%.cpp=%.obj}

#
# Compilateur C++
#
CXX = 'C:\VisualStudio\VC\Tools\MSVC\14.42.34433\bin\Hostx86\x86\cl.exe'



#
# Options du compilateur C++
#   -g pour debugger, -O optimise, -Wall affiche les erreurs, -I pour les headers
#   -std=c++11 pour C++11
# Exemple: CXXFLAGS= -std=c++11 -Wall -O -I/usr/local/qt/include
#
CXXFLAGS = -std=c++11 -Wall -g -I'C:\VisualStudio\Community\VC\Tools\MSVC\14.28.29333\include'

#
# Options de l'editeur de liens
#
LDFLAGS = 

# Librairies a utiliser
# Exemple: LDLIBS = -L/usr/local/qt/lib -lqt
#
LDLIBS = /LIBPATH:'C:\VisualStudio\VC\Tools\MSVC\14.28.29333\lib\x86' /LIBPATH:'C:\VisualStudio\Community\VC\Tools\MSVC\14.28.29333\lib\x64' 


##########################################
#
# Regles de construction/destruction des .o et de l'executable
# depend-${PROG} sera un fichier contenant les dependances
#
 
all: ${PROG}

run: ${PROG}
	./${PROG}

${PROG}: depend-${PROG} ${OBJETS}
	${CXX} -o $@ ${CXXFLAGS} ${LDFLAGS} ${OBJETS} ${LDLIBS}

clean:
	-@$(RM) *.o depend-${PROG} core 1>/dev/null 2>&1

clean-all: clean
	-@$(RM) ${PROG} 1>/dev/null 2>&1
  
tar:
	tar cvf ${PROG}.tar.gz ${SOURCES}

# Gestion des dependances : creation automatique des dependances en utilisant 
# l'option -MM de g++ (attention tous les compilateurs n'ont pas cette option)
#
depend-${PROG}:
	${CXX} ${CXXFLAGS} -MM ${SOURCES} > depend-${PROG}


###########################################
#
# Regles implicites
#

.SUFFIXES: .cpp .cxx .c .obj

.cpp.obj:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.obj:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.obj:
	$(CC) -c (CFLAGS) $(INCPATH) -o $@ $<


#############################################
#
# Inclusion du fichier des dependances
#
-include depend-${PROG}
