# Compilers
FC=gfortran -g
FFLAGS=-Wall -W
CXX=g++ -O3 -std=c++0x
#CXX=g++ -g -std=c++0x
CXXFLAGS = -Wall -W
CC = gcc
CCFLAGS = -Wall -W

# Linker
LD=g++
LDFLAGS= $(LIB)/libcuba.a $(LIB)/minuit.a -lgfortran
EXE=reSolve.out

# Dirs

VPATH=$(DIRS)

SOURCE_DIR=$(PWD)
CODE_DIR=$(dir $(PWD))

LIB=$(CODE_DIR)/lib
OBJ_DIR=$(CODE_DIR)/obj

MAIN_DIR=$(SOURCE_DIR)/Main

UTIL_DIR=$(SOURCE_DIR)/Utility
INT_DIR=$(SOURCE_DIR)/Integral
PDF_DIR=$(SOURCE_DIR)/PDFfit
DIPH_DIR=$(SOURCE_DIR)/Process/Diphoton_Res
DY_DIR=$(SOURCE_DIR)/Process/DrellYan_Res
RES_DIR=$(SOURCE_DIR)/Resummation
HISTO_DIR=$(SOURCE_DIR)/Histogrammer

USER_DIR=$(SOURCE_DIR)/User


DIRS= $(MAIN_DIR):$(UTIL_DIR):$(INT_DIR):$(PDF_DIR):\
	$(USER_DIR):$(RES_DIR):$(DIPH_DIR):$(DY_DIR):$(OBJ_DIR):\
	$(HISTO_DIR)


INC=-I$(MAIN_DIR) -I$(UTIL_DIR) -I$(INT_DIR) -I$(PDF_DIR)\
	-I$(USER_DIR) -I$(RES_DIR) -I$(DIPH_DIR) -I$(DY_DIR) -I$(HISTO_DIR)


# Objects, divided by dir

MAIN_FILES=main.o InputPars.o PostProc.o PreProc.o cuba_interface.o\
	k_vegas_interface.o
UTIL_FILES=lorentz.o phase_space.o alphaS.o mstwpdf.o events_out.o read_data.o \
alphaS_ellis.o newton1.o polylogs.o
INT_FILES=events_readin.o k_vegas.o random.o
PDF_FILES= partons_cc.o partons.o pdffit.o
USER_FILES=USER.o
RES_FILES=resu_preproc.o pdffit_in.o pdfmellin.o resu_procindep.o \
	mellinspace_fns.o intde2.o inv_fourier.o xsection.o \
	inv_mellin.o sudakov.o hardfns.o evolution.o resummation_input.o resu_PS.o
DIPH_FILES=diphoton_input.o diphoton_integrand.o diphoton_ps.o \
	diphoton_cuts.o diphoton_hard.o
DY_FILES=drellyan_input.o drellyan_integrand.o drellyan_ps.o \
	drellyan_cuts.o drellyan_hard.o
HISTO_FILES=histogrammer.o observables.o \
	histogram.o event_reader.o events_to_histograms.o


OBJS= $(MAIN_FILES) $(UTIL_FILES) $(INT_FILES) $(PDF_FILES) \
	$(USER_FILES) $(DIPH_FILES) $(DY_FILES) $(RES_FILES) $(HISTO_FILES)

# General compilation instruction for .cc sources
%.o: %.cc
	$(CXX) -c -o $(patsubst %,$(OBJ_DIR)/%,$@) $<  $(INC) $(CXXFLAGS)


# Link the main executable
main: $(OBJS)
	$(LD) -o $(EXE) $(patsubst %,$(OBJ_DIR)/%,$(OBJS)) $(LDFLAGS)
	mv $(EXE) ../../



#
# SPECIFIC RULES FOR FORTRAN FILES
#
# For MSTW08 alphas fortran code
alphaS.o : alphaS.f
	$(FC) -c $(FFLAGS) $< -o $(patsubst %,$(OBJ_DIR)/%,$@)

random.o : random.f
	$(FC) -c $(FFLAGS) $< -o $(patsubst %,$(OBJ_DIR)/%,$@)
#
# For alphas evolution fortran code taken from DYres
alphaS_ellis.o : alphaS_ellis.f
	$(FC) -c $(FFLAGS) $< -o $(patsubst %,$(OBJ_DIR)/%,$@)
newton1.o : newton1.f
	$(FC) -c $(FFLAGS) $< -o $(patsubst %,$(OBJ_DIR)/%,$@)
#
# For pdffit code
partons.o : partons.f
	$(FC) -c $(FFLAGS) $< -o $(patsubst %,$(OBJ_DIR)/%,$@)

pdffit.o : pdffit.f
	$(FC) -c $(FFLAGS) $< -o $(patsubst %,$(OBJ_DIR)/%,$@)

# Clean
clean:
	rm $(OBJ_DIR)/*.o ../../$(EXE)
