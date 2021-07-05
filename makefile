# =========================================================================== #
# user variables setup.
# feel free to adjust to your requirements

# --------------------------------------------------------------------------- #
# Compiler setup

CXX      = g++
CXXFLAGS = -std=c++2a -O3 -Wextra -Wall -Wpedantic -Wimplicit-fallthrough -I $(LIBDIR)
LDFLAGS  = -lm

LIBDIR = lib
SRCDIR = src
INCDIR = inc
OBJDIR = obj
EXEDIR = .

# --------------------------------------------------------------------------- #
# Project Data setup

EXTENSION_CODE   = .cpp
EXTENSION_HEADER = .hpp

EXENAME = TheBlueChameleonGlobals

# --------------------------------------------------------------------------- #
# Runtime setup

RUNTIME_PARAM = "settings.ini"

# =========================================================================== #
# Path Setup. Be sure that you really understand what you're doint if you edit anything below this line

DIRECTORIES = $(subst $(SRCDIR),$(OBJDIR),$(shell find $(SRCDIR) -type d))
	# pathes for files to be included into the compile/link procedure.
	# subst: "substitute PARAMETER_1 by PARAMETER_2 in PARAMETER_3.
	# shell find -type d lists only directories. find works recursively.
	# => load from SRCDIR and OBJDIR with all subdirectories

SRC     = $(wildcard $(SRCDIR)/*$(EXTENSION_CODE)) $(wildcard $(SRCDIR)/**/*$(EXTENSION_CODE))
	# list of all files in src, including subdirectories
INC     = $(wildcard $(INCDIR)/*$(EXTENSION_HEADER)) $(wildcard $(INCDIR)/**/*$(EXTENSION_HEADER))
	# same for includes
OBJ     = $(SRC:$(SRCDIR)/%$(EXTENSION_CODE)=$(OBJDIR)/%.o)
	# defines analogy relation?

# --------------------------------------------------------------------------- #
# Colour constants

COLOR_END	= \033[m

COLOR_RED	= \033[0;31m
COLOR_GREEN	= \033[0;32m
COLOR_YELLOW	= \033[0;33m
COLOR_BLUE	= \033[0;34m
COLOR_PURPLE	= \033[0;35m
COLOR_CYAN	= \033[0;36m
COLOR_GREY	= \033[0;37m

COLOR_LRED	= \033[1;31m
COLOR_LGREEN	= \033[1;32m
COLOR_LYELLOW	= \033[1;33m
COLOR_LBLUE	= \033[1;34m
COLOR_LPURPLE	= \033[1;35m
COLOR_LCYAN	= \033[1;36m
COLOR_LGREY	= \033[1;37m

MSG_OK		= $(COLOR_LGREEN)[SUCCES]$(COLOR_END)
MSG_WARNING	= $(COLOR_LYELLOW)[WARNING]$(COLOR_END)
MSG_ERROR	= $(COLOR_LRED)[ERROR]$(COLOR_END)

# =========================================================================== #
# procs

define fatboxtop
	@printf "$(COLOR_BLUE)"
	@printf "#=============================================================================#\n"
	@printf "$(COLOR_END)"
endef
# ........................................................................... #
define fatboxbottom
	@printf "$(COLOR_BLUE)"
	@printf "#=============================================================================#\n"
	@printf "$(COLOR_END)"
endef
# ........................................................................... #
define fatboxtext
	@printf "$(COLOR_BLUE)"
	@printf "# "
	@printf "$(COLOR_LGREY)"
	@printf "%-75b %s" $(1)
	@printf "$(COLOR_BLUE)"
	@printf "#\n"
	@printf "$(COLOR_END)"
	
endef
# --------------------------------------------------------------------------- #
define boxtop
	@printf "$(COLOR_BLUE)"
	@printf "+-----------------------------------------------------------------------------+\n"
	@printf "$(COLOR_END)"
endef
# ........................................................................... #
define boxbottom
	@printf "$(COLOR_BLUE)"
	@printf "+-----------------------------------------------------------------------------+\n"
	@printf "$(COLOR_END)"
endef
# ........................................................................... #
define boxtext
	@printf "$(COLOR_BLUE)"
	@printf "| "
	@printf "$(COLOR_LGREY)"
	@printf "%-75b %s" $(1)
	@printf "$(COLOR_BLUE)"
	@printf "|\n"
	@printf "$(COLOR_END)"
endef
# --------------------------------------------------------------------------- #
define fatbox
	$(call fatboxtop)
	$(call fatboxtext, $(1))
	$(call fatboxbottom)
endef
# ........................................................................... #
define box
	$(call boxtop)
	$(call boxtext, $(1))
	$(call boxbottom)
endef

# =========================================================================== #
# targets

.PHONY: intro all 

# --------------------------------------------------------------------------- #
# compound targets

all:   intro generate extro
new:   clean intro generate extro
run:   intro generate extro execute
grind: intro generate extro valgrind

# --------------------------------------------------------------------------- #
# visual feedback

intro:
	@clear
	$(call fatbox, "attempting to make")
	@printf "$(COLOR_GREY)  "
	@date
	@echo ""
	
# ........................................................................... #
extro:
	$(call fatbox, "make done")
	@printf "$(COLOR_GREY)  "
	@date
	@echo ""
	
	
# --------------------------------------------------------------------------- #
# create executable file

generate: $(EXENAME)
# ........................................................................... #
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXTENSION_CODE)                         # compile #
	$(call boxtop)
	$(call boxtext, "attempting to compile...")
	
	@mkdir -p $(DIRECTORIES)
	
	@printf "$(COLOR_BLUE)"
	@printf "| "
	@printf "$(COLOR_LBLUE)"
	@printf "%-85b %s" "  Compiling:  $(COLOR_LYELLOW)$<$(COLOR_END)"
	@printf "$(COLOR_BLUE)|\n"
	
	@$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(INCDIR) \
		|| (echo "$(MSG_ERROR)"; exit 1)
	
	$(call boxtext, "done.")
	$(call boxbottom)
	
# ........................................................................... #
$(EXENAME): $(OBJ)                                                     # link #
	$(call boxtop)
	$(call boxtext, "attempting to link...")
	
	@mkdir -p $(EXEDIR)
	
	@printf "$(COLOR_BLUE)"
	@printf "| "
	@printf "$(COLOR_LBLUE)"
	@printf "%-85b %s" "  Linking:  $(COLOR_LYELLOW)$<$(COLOR_END)"
	@printf "$(COLOR_BLUE)|\n"
	
	@$(CXX) $^ -o $(EXEDIR)/$(EXENAME) $(LDFLAGS)
	
	$(call boxtext, "done.")
	$(call boxtop)
	
	
	@printf "$(COLOR_BLUE)"
	@printf "| "
	@printf "$(COLOR_LBLUE)"
	@printf "%-81b %s " "Executable: $(COLOR_LYELLOW)$(EXEDIR)/$(EXENAME)"
	@printf "$(COLOR_BLUE)|\n"
	
	$(call boxbottom)
	
# --------------------------------------------------------------------------- #
# run variations

execute:
	@./$(EXEDIR)/$(EXENAME) $(RUNTIME_PARAM)
	
# ........................................................................... #
valgrind :
	@valgrind ./$(EXEDIR)/$(EXENAME)
	
# --------------------------------------------------------------------------- #
# delete the object directory

clean:
	@printf "$(COLOR_LCYAN)"
	@echo "#=============================================================================#"
	@echo "# attempting to clean...                                                      #"
	
	@rm -rf $(OBJDIR)
	@rm -f $(EXEDIR)/$(EXENAME)
	
	@echo "# done.                                                                       #"
	@echo "#=============================================================================#"
	@echo ""
	
# --------------------------------------------------------------------------- #
# help section

vars :
	@clear
	$(call fatbox, "variables dump:")
	
	@echo "source code extension    : $(EXTENSION_CODE)"
	@echo "header files extension   : $(EXTENSION_HEADER)"
	@echo ""
	
	@echo "executable file name     : $(EXENAME)"
	@echo ""
	@echo "source code  directory   : $(SRCDIR)"
	@echo "include file directory   : $(INCDIR)"
	@echo "object file  directory   : $(OBJDIR)"
	@echo "binary       directory   : $(EXEDIR)"
	@echo ""
	
	@echo "binary source directories: $(DIRECTORIES)"
	@echo "source code files        :"
	@echo "   $(SRC)"
	@echo "header files             :"
	@echo "   $(INC)"
	@echo "object code files        :"
	@echo "   $(OBJ)"
	@echo ""
	
	$(call fatbox, "done.")
# ........................................................................... #
help :
	@echo "This makefile supports the following targets:"
	@echo "$(COLOR_YELLOW)Compile targets$(COLOR_END)"
	@echo "* $(COLOR_LCYAN)clean$(COLOR_END)"
	@echo "   removes $(OBJDIR) and its contents."
	@echo "* $(COLOR_LCYAN)all$(COLOR_END)"
	@echo "   compiles any files that may have changed since the last time this was run"
	@echo "* $(COLOR_LCYAN)new$(COLOR_END)"
	@echo "   compiles all files, regardless of whether they may have changed since the last time this was run"
	@echo "* $(COLOR_LCYAN)run$(COLOR_END)"
	@echo "   compiles all files and runs the program thereafter"
	@echo "* $(COLOR_LCYAN)grind$(COLOR_END)"
	@echo "   compiles all files and runs the program via valgrind"
	@echo ""
	@echo "$(COLOR_YELLOW)Info targets$(COLOR_END)"
	@echo "* $(COLOR_LCYAN)vars$(COLOR_END)"
	@echo "   show variables generated and set by this script"
	@echo "* $(COLOR_LCYAN)help$(COLOR_END)"
	@echo "   show this help"
	@echo ""
	
	@echo "Note that you can create compound targets such as:"
	@echo "   $(COLOR_LCYAN)make clean run$(COLOR_END)" 
